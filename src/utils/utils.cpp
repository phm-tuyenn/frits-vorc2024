#include "includes.h"

/*
    @brief Set hardware driver
    @param pwm PWM controller
    @param ps2x Gamepad
    @param tcs Color sensor
*/
void Utilities::setHardware(Adafruit_PWMServoDriver pwm, PS2X ps2x, Adafruit_TCS34725 tcs) {
    Utilities::pwm = pwm;
    Utilities::ps2x = ps2x;
    Utilities::tcs = tcs;
}

/*
    @brief Set speed for motor
    @param chan1, chan2 Set motor channel pair
    @param speed Speed of motor, range -1 -> 1
*/
void Utilities::setMotorSpeed(int chan1, int chan2, float speed) {
    // Convert the range from -1 -> 1 (float) to -4095 -> 4095 (int)
    int pwm_val = static_cast<int>(speed * 4095);
    // Check if the speed is postive to rotate motor clockwise and vice versa
    if (pwm_val > 0) {
        pwm.setPWM(chan1, 0, pwm_val);
        pwm.setPWM(chan2, 0, 0);
    } else {
        pwm.setPWM(chan1, 0, 0);
        pwm.setPWM(chan2, 0, -pwm_val);
    }
}

/*
    @brief Set angle for 180deg servo of speed for 360deg servo
    @param chan Set servo channel pair
    @param angle Set servo angle or speed, range 0 -> 180
*/
void Utilities::setServo(int chan, float angle) {
    // Calculate angle change time in ms and convert to PWM
    float angle_change_ms = angle / 180;
    int pwm_val = static_cast<int>((T_on_0deg + angle_change_ms) / (Ts / 4096));
    // Set the calculated PWM
    pwm.setPWM(chan, 0, pwm_val);
}

/*
    @brief Read color sensor and return RGB value
    @return Color RGB value
*/
struct color Utilities::getColor() {
    struct color output;    
    float red, green, blue;
    tcs.setInterrupt(false);  // turn on LED
    delay(60);  // takes 50ms to read
    tcs.getRGB(&red, &green, &blue);
    tcs.setInterrupt(true);  // turn off LED

    output.r = static_cast<int>(red);
    output.g = static_cast<int>(green);
    output.b = static_cast<int>(blue);
    return output;
}

/*
    @brief Read distance sensor and return distance value
    @return Distance value in meter
*/
float Utilities::getDistance() {
    // Trigger signal
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    float duration = pulseIn(ECHO_PIN, HIGH); // Get pulse
    float distance = (duration * .343) / 2; // 0.343 is speed of sound in mm/microsec
    return distance / 1000; // Convert to meter 
}
