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
            utils.setServo(SERIALIZER_CHAN, SERIALIZER_NEUTRAL_STATE);
            break;
        case 2:
            utils.setServo(SERIALIZER_CHAN, SERIALIZER_WATER_STATE);
            break;
    }
}

/*
    @brief Serializer colorDetection: detects whether the input RGB code is white, black or neutral
    @param r Red code
    @param g Green code
    @param b Blue code
    @details
    - How this function works is that there are 4 barriers, determining which range the white
    color or black color RGB code should be in.
        0,0,0    |   r1,g1,b1   |   r2,g2,b2   | 255,255,255
        BlackMin |   BlackMax   |   WhiteMin   |  WhiteMax
    - If the input RGB code has either 3 of the indices in the range from BlackMax to WhiteMin,
    the output of the function is neutral color, neither black nor white.
    - BlackMin and WhiteMax are fixed-constants, and the other 2 are pseudo-constants.
    @return 0: black, 1: neutral color, 2: white
*/
int Serializer::colorDetection(int r, int g, int b){
    if ((r <= BLACK_MAX[0]) &&
        (g <= BLACK_MAX[1]) &&
        (b <= BLACK_MAX[2])) return 0;
    else if ((r >= WHITE_MIN[0]) &&
            (g >= WHITE_MIN[1]) &&
            (b >= WHITE_MIN[2])) return 2;
    else return 1;
}