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

}

// Dumper main run: use this in `void loop()`
void Dumper::run() {
    
}