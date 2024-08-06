#include "includes.h"

// Map joystick range from 0-255 to -1 -> 1
#define mapJoystick(joystickVal, centeredJoystickVal) (static_cast<float>(joystickVal) - static_cast<float>(centeredJoystickVal)) / 128.0

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
    utils.setHardware(pwm, ps2x, tcs);
}

// Drivetrain main run: use this in `void loop()`
void Drivetrain::run() {
    // Get joystick value
    int LYInput = ps2x.Analog(PSS_LY);
    int RXInput = ps2x.Analog(PSS_RX);
    float leftYJoystick = mapJoystick(LYInput, JOYSTICK_LEFT_CENTER_VAL);
    float rightXJoystick = mapJoystick(RXInput, JOYSTICK_RIGHT_CENTER_VAL);
    // Calculate motor speed
    float leftSpeed = leftYJoystick + rightXJoystick;
    float rightSpeed = leftYJoystick - rightXJoystick;
    // Set motor speed, left go counter clockwise and vice versa
    utils.setMotorSpeed(DRIVE_LEFT_CHAN[0], DRIVE_LEFT_CHAN[1], -leftSpeed);
    utils.setMotorSpeed(DRIVE_RIGHT_CHAN[0], DRIVE_RIGHT_CHAN[1], rightSpeed);
}