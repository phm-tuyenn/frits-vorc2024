#include "includes.h"

/*
    @brief Init Serializer class
    @param pwm PWM controller
    @param ps2x Gamepad
    @param tcs Color sensor
*/
Shooter::Shooter(Adafruit_PWMServoDriver pwm, PS2X ps2x, Adafruit_TCS34725 tcs) {
    Shooter::pwm = pwm;
    Shooter::ps2x = ps2x;
    Shooter::tcs = tcs;
}

// Shooter setup: use this in `void setup()`
void Shooter::setup() {

}

// Shooter main run: use this in `void loop()`
void Shooter::run() {
    
}