cmake_minimum_required(VERSION 3.5)
project(test_workbench)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(dynamixel_workbench_toolbox REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(model_scan src/a_Model_Scan.cpp)
ament_target_dependencies(model_scan
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(ping src/b_Ping.cpp)
ament_target_dependencies(ping
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(id_change src/c_ID_Change.cpp)
ament_target_dependencies(id_change
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(bps_change src/d_BPS_Change.cpp)
ament_target_dependencies(bps_change
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(mode_change src/e_Mode_Change.cpp)
ament_target_dependencies(mode_change
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(reboot src/f_Reboot.cpp)
ament_target_dependencies(reboot
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(reset src/g_Reset.cpp)
ament_target_dependencies(reset
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(position src/h_Position.cpp)
ament_target_dependencies(position
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(velocity src/i_Velocity.cpp)
ament_target_dependencies(velocity
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(current_based_position src/j_Current_Based_Position.cpp)
ament_target_dependencies(current_based_position
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(read_write src/k_Read_Write.cpp)
ament_target_dependencies(read_write
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(sync_write src/l_Sync_Write.cpp)
ament_target_dependencies(sync_write
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(sync_read_write src/m_Sync_Read_Write.cpp)
ament_target_dependencies(sync_read_write
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(bulk_read_write src/n_Bulk_Read_Write.cpp)
ament_target_dependencies(bulk_read_write
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(find_dynamixel src/o_Find_Dynamixel.cpp)
ament_target_dependencies(find_dynamixel
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)
add_executable(monitor src/p_Monitor.cpp)
ament_target_dependencies(monitor
  rclcpp
  std_msgs
  dynamixel_workbench_toolbox
)

install(TARGETS
  model_scan
  ping
  id_change
  bps_change
  mode_change
  reboot
  reset
  position
  velocity
  current_based_position
  read_write
  sync_write
  sync_read_write
  bulk_read_write
  find_dynamixel
  monitor
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
