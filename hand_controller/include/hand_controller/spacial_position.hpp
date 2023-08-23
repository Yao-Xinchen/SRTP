class Wrist
{
public:
    float roll;
    float pitch;
    float yaw;
};

class Finger
{
public:
    float abuction;
    float proximal;
    float medial;
    float distal;
};

class SpacialPosition
{
public:
    Wrist wrist;
    Finger thumb;
    Finger index;
    Finger middle;
    Finger ring;
    Finger pinky;

    void interpreter(float linear[23])
    {
        linear[0] = this->wrist.roll;
        linear[1] = this->wrist.pitch;
        linear[2] = this->wrist.yaw;
        linear[3] = this->thumb.abuction;
        linear[4] = this->thumb.proximal;
        linear[5] = this->thumb.medial;
        linear[6] = this->thumb.distal;
        linear[7] = this->index.abuction;
        linear[8] = this->index.proximal;
        linear[9] = this->index.medial;
        linear[10] = this->index.distal;
        linear[11] = this->middle.abuction;
        linear[12] = this->middle.proximal;
        linear[13] = this->middle.medial;
        linear[14] = this->middle.distal;
        linear[15] = this->ring.abuction;
        linear[16] = this->ring.proximal;
        linear[17] = this->ring.medial;
        linear[18] = this->ring.distal;
        linear[19] = this->pinky.abuction;
        linear[20] = this->pinky.proximal;
        linear[21] = this->pinky.medial;
        linear[22] = this->pinky.distal;
    }
};
