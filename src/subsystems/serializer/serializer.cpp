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
    utils.setHardware(pwm,ps2x,tcs);
    // Set neutral state for serializer
    utils.setServo(SERIALIZER_CHAN, SERIALIZER_NEUTRAL_STATE);
}

// Serializer main run: use this in `void loop()`
void Serializer::run() {
    // Get color input
    struct color colorInput = utils.getColor();
    // Run color cases
    switch(colorDetection(colorInput.r,colorInput.g,colorInput.b)){
        case 0:
            utils.setServo(SERIALIZER_CHAN, SERIALIZER_GABBAGE_STATE);
            break;
        case 1:
            utils.setServo(SERIALIZER_CHAN, SERIALIZER_WATER_STATE);
            break;
        case 2:
            utils.setServo(SERIALIZER_CHAN, SERIALIZER_NEUTRAL_STATE);
            break;
    }
}

/*
    @brief Serializer colorDetection: detects whether the input RGB code is white or black 
    @param r Red code
    @param g Green code
    @param b Blue code
    @details
    - This function converts RGB code to grayscale and then decide if the color is white or black or neutral.
    - The neutral color ranges somewhere in the middle on the grayscale (determined in constants.h).
    - Lower than this range is considered black, and higher is considered white.
    @return 0: black, 1: white, 2: neutral color
*/
int Serializer::colorDetection(int r, int g, int b){
    float gray = 0.2126 * r + 0.7152 * g + 0.0722 * b; // Convert to grayscale
    if (gray < NEUTRAL_ZONE_IN) return 0;
    if (gray > NEUTRAL_ZONE_OUT) return 1;
    return 2;
}