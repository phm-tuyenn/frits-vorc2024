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
}

// Shooter main run: use this in `void loop()`
void Shooter::run() {
    // Rotate water loader servo clockwise
    utils.setServo(LOADER_CHAN, SERVO360_COUNTER_CLOCKWISE);
    // Check if R1 button is pressed to run motor in 1200RPM, else stop motor
    if (ps2x.ButtonPressed(PSB_R1)) {
        utils.setMotorSpeed(SHOOTER_CHAN[0], SHOOTER_CHAN[1], getOptimalVelocity(utils.getDistance()));
    } else {
        utils.setMotorSpeed(SHOOTER_CHAN[0], SHOOTER_CHAN[1], 0);
    }
}

// Calculate optimal velocity for accurate shooting
float Shooter::getOptimalVelocity(float distance) {
    // Calculate the velocity in m/s
    float velocity_meter_per_sec = sqrtf((-GRAVITATIONAL_ACCELERATION * pow(distance, 2)) / (GOAL_HEIGHT - distance - SHOOTER_HEIGHT));
    // Convert to rpm
    float velocity_rpm = (60 * velocity_meter_per_sec) / (2 * PI * WHEEL_RADIUS);
    // Convert to speed percent
    float speed = velocity_rpm / MAX_RPM;
    return speed;
}