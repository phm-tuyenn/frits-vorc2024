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
    }
}

/*
    @brief Serializer colorDetection: detects whether the input RGB code is white or black 
    @param r Red code
    @param g Green code
    @param b Blue code
    @details
    - It convert RGB to grayscale and then decide if the color is white or black by a threshold
    @return 0: black, 1: white
*/
int Serializer::colorDetection(int r, int g, int b){
    float gray = 0.2126 * r + 0.7152 * g + 0.0722 * b; // Convert to grayscale
    return gray < COLOR_THRESHOLD ? 0 : 1; // 0 is black, 1 is white
}