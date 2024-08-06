class Intake {
    public:
        Adafruit_PWMServoDriver pwm;
        PS2X ps2x;
        Adafruit_TCS34725 tcs;
        Utilities utils;
        int state;
        
        Intake(Adafruit_PWMServoDriver pwm, PS2X ps2x, Adafruit_TCS34725 tcs);
        void setup();
        void run();  
};