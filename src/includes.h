#include <Arduino.h>
#include <PS2X_lib.h>
#include <Wire.h>
#include <math.h>

// Include driver
#include <Adafruit_PWMServoDriver.h>
#include "Adafruit_TCS34725.h"

// Driver init
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // PWM controller
PS2X ps2x; // Gamepad
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); // Color sensor

// Utilities for better coding
#include "utils/utils.h"

// Constant for robot
#include "constants.h"

// Here to includes subsystem headers