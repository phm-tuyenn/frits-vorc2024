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

}

// Intake main run: use this in `void loop()`
void Intake::run() {
    
}