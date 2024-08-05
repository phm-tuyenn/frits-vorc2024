class Intake {
    public:
        Intake(Adafruit_PWMServoDriver pwm, PS2X ps2x, Adafruit_TCS34725 tcs);
        void setup();
        void run();
    private:
        Adafruit_PWMServoDriver pwm;
        PS2X ps2x;
        Adafruit_TCS34725 tcs;
};