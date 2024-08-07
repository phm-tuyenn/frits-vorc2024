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
    // Set button pressed state
    if (TRIANGLEInput == 1){
        switch (state){
            case 0:
                state = 1;
                break;
            case 1:
                state = 0;
                break;
        }   
    }
    
    switch (state){
        case 1:
            if (digitalRead(LIMIT_SWITCH_2_PIN)) 
                utils.setServo(DUMPER_CHAN, DUMPER_OPEN_SPEED);
            break;
        case 0:
            if (digitalRead(LIMIT_SWITCH_1_PIN))
                utils.setServo(DUMPER_CHAN, DUMPER_CLOSE_SPEED);
            break;
    }   
}