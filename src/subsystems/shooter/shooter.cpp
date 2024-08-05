#include "includes.h"

#define degToRad(a) (a * PI) / 180 // Convert degrees to radian 
#define radToDeg(a) (a * 180) / PI // Convert radian to degrees
#define velocToRPM(v) (60 * v) / (2 * PI * WHEEL_RADIUS)


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
    utils.setHardware(pwm, ps2x, tcs);
    utils.setServoAngle(HOOD_CHAN, 45);
}

// Shooter main run: use this in `void loop()`
void Shooter::run() {
    if (ps2x.ButtonPressed(PSB_L1))
}