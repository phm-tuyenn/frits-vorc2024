#include "includes.h"

// Driver init
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // PWM controller
PS2X ps2x; // Gamepad
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); // Color sensor

// Utilities class 
Utilities utils(pwm, ps2x, tcs);

// Subsystem class
Drivetrain drivetrain(pwm, ps2x, tcs);
Intake intake(pwm, ps2x, tcs);
Serializer serializer(pwm, ps2x, tcs);
Shooter shooter(pwm, ps2x, tcs);
Dumper dumper(pwm, ps2x, tcs);

void setup() {
    // Try to connect to gamepad, 1 sec each try
    int error = -1; 
    while (error != 0) {
        delay(1000);
        error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, PRESSURES, RUMBLE); 
    } 

    // Setup PWM controller
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50);
    Wire.setClock(400000);
    
    tcs.begin(); // Set up color sensor

    // Set up distance sensor
    pinMode(TRIGPIN, OUTPUT); // Sets the trigPin as an Output
    pinMode(ECHOPIN, INPUT);

    // Set pin state
    pwm.setPin(8, 0);
    pwm.setPin(9, 0);
    pwm.setPin(10, 0);
    pwm.setPin(11, 0);

    // Setup for subsystem
}

void loop() {
    
}