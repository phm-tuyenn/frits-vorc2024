#include <Arduino.h>
#include <PS2X_lib.h>
#include <Adafruit_PWMServoDriver.h>

#define PS2_CLK 14
#define PS2_CMD 13
#define PS2_SEL 15
#define PS2_DAT 12
#define pressures false
#define rumble false

PS2X ps2x;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

byte error = -1;
uint16_t tryNum = 0;

void setSpeed(int16_t left, int16_t right) {
    if(left >= 0) {
        pwm.setPWM(8, 0, left);
        pwm.setPWM(9, 0, 0);
    } else if(left < 0) {
        pwm.setPWM(8, 0, 0);
        pwm.setPWM(9, 0, -left);
    }

    if(right >= 0) {
        pwm.setPWM(10, 0, right);
        pwm.setPWM(11, 0, 0);
    } else if(right < 0) {
        pwm.setPWM(10, 0, 0);
        pwm.setPWM(11, 0, -right);
    }
}

void setup() {
    Serial.begin(115200);
    while (error != 0) {
        delay(1000);
        error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    }
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(60);
    Wire.setClock(400000);
}

void loop() {
    if(ps2x.Button(PSB_PAD_UP)) setSpeed(1023, 1023);
    else if(ps2x.Button(PSB_PAD_LEFT)) setSpeed(-1023, 1023);
    else if(ps2x.Button(PSB_PAD_RIGHT)) setSpeed(1023, -1023);
    else if(ps2x.Button(PSB_PAD_DOWN)) setSpeed(-1023, -1023);
    else setSpeed(0, 0);
    
    ps2x.read_gamepad();
    delay(10);
}