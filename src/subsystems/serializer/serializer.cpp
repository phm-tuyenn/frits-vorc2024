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
    // Close all gates
    utils.setServo(SERIALIZER_WASTE_GATE_CHAN, SERIALIZER_GABBAGE_CLOSE);
    utils.setServo(SERIALIZER_WATER_GATE_CHAN, SERIALIZER_WATER_CLOSE);
}

// Serializer main run: use this in `void loop()`
void Serializer::run() {
    // Get color input
    struct color colorInput = utils.getColor();
    // Run color cases
    switch(colorDetection(colorInput.r,colorInput.g,colorInput.b)){
        case 0: // If detect black then open garbagge gate, close water gate
            utils.setServo(SERIALIZER_WASTE_GATE_CHAN, SERIALIZER_GABBAGE_OPEN);
            utils.setServo(SERIALIZER_WATER_GATE_CHAN, SERIALIZER_WATER_CLOSE);
            break;
        case 1: // If detect black then close garbagge gate, open water gate
            utils.setServo(SERIALIZER_WASTE_GATE_CHAN, SERIALIZER_GABBAGE_CLOSE);
            utils.setServo(SERIALIZER_WATER_GATE_CHAN, SERIALIZER_WATER_OPEN);
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