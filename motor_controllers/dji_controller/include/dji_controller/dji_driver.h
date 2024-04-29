#ifndef DJI_DRIVER_H
#define DJI_DRIVER_H

#include "can_driver.hpp"
#include "dji_controller/motor_data.hpp"
#include "dji_controller/can_port.hpp"
#include <array>
#include <linux/can.h>
#include <memory>
#include <queue>

#define CALC_FREQ 1 // ms

#define I_MAX 20 // Ampere, current limit
#define V_MAX 300 // to be tuned, velocity limit

#define NaN std::nan("")

using std::array;
using std::unique_ptr;
using std::string;

enum MotorType
{
    M3508 = 0,
    M6020 = 1,
    M2006 = 2,
};

/**
 * @brief The DjiDriver class represents a driver for controlling a DJI motor.
 * 
 * This class provides methods for setting goals, configuring PID parameters, 
 * writing data to the motor, and processing received data.
 */
class DjiDriver
{
private:
    static array<unique_ptr<CanPort>, 2> can_ports; /**< Array of pointers to the CAN port instances. */

    uint8_t port; /**< CAN port number. */
    MotorType motor_type; /**< Type of the motor. */
    PidParam p2v_prm, v2c_prm; /**< PID parameters for position-to-velocity and velocity-to-current conversion. */
    PidOutput p2v_out, v2c_out; /**< PID outputs for position-to-velocity and velocity-to-current conversion. */

    MotorData present_data{}; /**< Data representing the current state of the motor. */

    float vel_error{}; /**< Error in velocity. */
    float pos_error{}; /**< Error in position. */
    float goal_pos{}; /**< Desired position of the motor. */
    float goal_vel{}; /**< Desired velocity of the motor. */
    float current{}; /**< Current value of the motor. */

    /**
     * @brief Convert velocity to current using PID control.
     * This depends on member variables `goal_vel`, `present_data.velocity`.
     * The result is stored in member variable `current`.
     */
    void vel2current();

    /**
     * @brief Convert position to velocity using PID control.
     * This depends on member variables `goal_pos`, `present_data.position`.
     * The result is stored in member variable `goal_vel`.
     * @note To realize position control, this function should be executed before vel2current().
     */
    void pos2velocity();

public:
    int hid; /**< Hardware ID of the motor. */
    string rid; /**< ROS ID of the motor. */

    /**
     * @brief Constructor for DjiDriver class.
     * @param rid The ROS ID of the motor.
     * @param hid The hardware ID of the motor.
     * @param type The type of the motor.
     * @param port The port name of the CAN bus.
     */
    DjiDriver(const string& rid, int hid, string type, string port);
    
    /**
     * @brief Set the desired position and velocity for the motor.
     * @param goal_pos The desired position.
     * @param goal_vel The desired velocity.
     */
    void set_goal(float goal_pos, float goal_vel, float goal_cur);

    /**
     * @brief Set the PID parameters for position-to-velocity conversion.
     * @param kp The desired proportional gain.
     * @param ki The desired integral gain.
     * @param kd The desired derivative gain.
     */
    void set_p2v_pid(float kp, float ki, float kd);

    /**
     * @brief Set the PID parameters for velocity-to-current conversion.
     * @param kp The desired proportional gain.
     * @param ki The desired integral gain.
     * @param kd The desired derivative gain.
     */
    void set_v2c_pid(float kp, float ki, float kd);

    /**
     * @brief Write the transmit frames.
     * PID control is executed in this function.
     * Position-to-velocity conversion is executed iff goal_pos is not zero.
     * @note This function should be executed before sending the transmit frame.
     */
    void write_tx();

    /**
     * @brief Send the transmit frame.
     * This would send all three transmit frames to the motor at once.
     * @note write_tx() should be executed before calling this function.
     */
    static void tx();

    /**
     * @brief Get the receive frame of CAN0.
     * This would write the received frame to the rx_frame variable.
     * @note This function should be executed before calling process_rx().
     */
    static void rx0();

    /**
     * @brief Get the receive frame of CAN1.
     * This would write the received frame to the rx_frame variable.
     * @note This function should be executed before calling process_rx().
     */
    static void rx1();

    /**
     * @brief Process the receive frame.
     * This updates the present data of the motor according to the rx_frame variable.
     * @note rx() should be executed before calling this function.
     */
    void process_rx();

    /**
     * @brief Get the current state of the motor.
     * @return A tuple containing the position, velocity, and current of the motor.
     */
    [[nodiscard]] std::tuple<float, float, float> get_state();

    /**
     * @brief Limits the value of a variable to a specified range.
     * @param val Reference to the variable to be limited.
     * @param limit The upper and lower limit for the value.
     * @note Limit must be positive.
     */
    void curb(float &val, float limit);

    /**
     * @brief Get the port number of the CAN bus.
     * @return The port number.
     */
    [[nodiscard]] int get_port() const { return port; }
};

#endif // DJI_DRIVER_H