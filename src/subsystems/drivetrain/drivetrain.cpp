#include "includes.h"

/*
    @brief Init Drivetrain class
    @param pwm PWM controller
    @param ps2x Gamepad
    @param tcs Color sensor
*/
Drivetrain::Drivetrain(Adafruit_PWMServoDriver pwm, PS2X ps2x, Adafruit_TCS34725 tcs) {
    Drivetrain::pwm = pwm;
    Drivetrain::ps2x = ps2x;
    Drivetrain::tcs = tcs;
}

// Drivetrain setup: use this in `void setup()`
void Drivetrain::setup() {

}

// Drivetrain main run: use this in `void loop()`
void Drivetrain::run() {
    
}