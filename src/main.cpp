#include "includes.h"

// Utilities class 
Utilities utils;

// Subsystem class


void setup() {
    // Try to connect to gamepad, 1 sec each try
    int error = -1; 
    while (error != 0) {
        delay(1000);
        error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble); 
    } 

    // Setup PWM controller
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(60);
    Wire.setClock(400000);
    
    tcs.begin(); // Set up color sensor

    // Set up distance sensor
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);

    // Set pin state
    pwm.setPin(8, 0);
    pwm.setPin(9, 0);
    pwm.setPin(10, 0);
    pwm.setPin(11, 0);

    // Setup for subsystem
}

void loop() {
    
}