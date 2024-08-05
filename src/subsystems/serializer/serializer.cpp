#include "includes.h"

/*
    @brief Init Serializer class
    @param pwm PWM controller
    @param ps2x Gamepad
    @param tcs Color sensor
*/
Serializer::Serializer(Adafruit_PWMServoDriver pwm, PS2X ps2x, Adafruit_TCS34725 tcs) {
    Serializer::pwm = pwm;
    Serializer::ps2x = ps2x;
    Serializer::tcs = tcs;
}

// Serializer setup: use this in `void setup()`
void Serializer::setup() {

}

// Serializer main run: use this in `void loop()`
void Serializer::run() {
    
}