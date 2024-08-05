struct color {
    int r, g, b;
};

// Utilities class
class Utilities {
    public:
        void setMotorSpeed(int chan1, int chan2, float speed);
        void setServoAngle(int chan, float angle);
        struct color getColor();
        float getDistance();
};
