#include "includes.h"

/*
    @brief Init Intake class
    @param pwm PWM controller
    @param ps2x Gamepad
    @param tcs Color sensor
*/
Intake::Intake(Adafruit_PWMServoDriver pwm, PS2X ps2x, Adafruit_TCS34725 tcs) {
    Intake::pwm = pwm;
    Intake::ps2x = ps2x;
    Intake::tcs = tcs;
}

// Intake setup: use this in `void setup()`
void Intake::setup() {
    utils.setHardware(pwm,ps2x,tcs);
}

// Intake main run: use this in `void loop()`
void Intake::run() {
    // Get SQUARE ButtonPressed value
    int SQUAREInput = ps2x.ButtonPressed(PSB_SQUARE);
    // Turn on/off Intake
    if (SQUAREInput == 1){
        switch (state){
            case 0:
                utils.setMotorSpeed(INTAKE_CHAN[0],INTAKE_CHAN[1],INTAKE_SPEED);
                state = 1;
                break;
            case 1:
                utils.setMotorSpeed(INTAKE_CHAN[0],INTAKE_CHAN[1],0);
                state = 0;
                break;
        }   
    }
}