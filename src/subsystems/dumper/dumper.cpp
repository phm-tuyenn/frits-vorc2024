#include "includes.h"

/*
    @brief Init Dumper class
    @param pwm PWM controller
    @param ps2x Gamepad
    @param tcs Color sensor
*/
Dumper::Dumper(Adafruit_PWMServoDriver pwm, PS2X ps2x, Adafruit_TCS34725 tcs) {
    Dumper::pwm = pwm;
    Dumper::ps2x = ps2x;
    Dumper::tcs = tcs;
}

// Dumper setup: use this in `void setup()`
void Dumper::setup() {
    utils.setHardware(pwm,ps2x,tcs);
}

// Dumper main run: use this in `void loop()`
void Dumper::run() {
    // Get TRIANGLE ButtonPressed value
    int TRIANGLEInput = ps2x.ButtonPressed(PSB_TRIANGLE);
    // Close/open dumper
    int state = 0;
    if (TRIANGLEInput == 1){
        switch (state){
            case 0:
                utils.setServo(DUMPER_CHAN,DUMPER_CLOSED_STATE);
                state = 1;
                break;
            case 1:
                utils.setServo(DUMPER_CHAN,DUMPER_CLOSED_STATE);
                state = 0;
                break;
        }   
    }
}