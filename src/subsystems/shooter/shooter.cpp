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
    utils.setServo(HOOD_CHAN, 45);
}

// Shooter main run: use this in `void loop()`
void Shooter::run() {
    // Rotate water loader servo clockwise
    utils.setServo(LOADER_CHAN, SERVO360_CLOCKWISE);
    // Set angle for hood
    utils.setServo(HOOD_CHAN, getOptimalHoodAngle(utils.getDistance()));
    // Check if R1 button is pressed to run motor in 1200RPM, else stop motor
    if (ps2x.ButtonPressed(PSB_R1)) {
        utils.setMotorSpeed(SHOOTER_CHAN[0], SHOOTER_CHAN[1], FLYWHEEL_VELOCITY_PERCENT);
    } else {
        utils.setMotorSpeed(SHOOTER_CHAN[0], SHOOTER_CHAN[1], 0);
    }
}

// Calculate optimal angle for accurate shooting
float Shooter::getOptimalHoodAngle(float distance) {
    float d = distance; // Distance sensor value in meter
    float b = pow(d, 2);
    float a = (-4.9 * b) / pow(FLYWHEEL_VELOCITY_METER_PER_SEC, 2);
    float c = (-1.8 + SHOOTER_HEIGHT + a);
    float delta = b - 4 * a * c; // Solve delta for equation
    float angle_tan = (-d + sqrt(delta)) / 2 * a; // Tangent of angle
    float angle = radToDeg(atan(angle_tan)); // Angle in radians, converted to degrees
    return angle; // Return angle value
}