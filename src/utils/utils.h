#include "libs.h"

struct color {
    int r, g, b;
};

// Utilities class
class Utilities {
    public:
        void setHardware(Adafruit_PWMServoDriver pwm, PS2X ps2x, Adafruit_TCS34725 tcs);
        void setMotorSpeed(int chan1, int chan2, float speed);
        void setServo(int chan, float angle);
        struct color getColor();
        float getDistance();
    private:
        Adafruit_PWMServoDriver pwm;
        PS2X ps2x;
        Adafruit_TCS34725 tcs;
};
