#include <Arduino.h>
#include <PS2X_lib.h>
#include <Adafruit_PWMServoDriver.h>

#define PS2_CLK 14
#define PS2_CMD 13
#define PS2_SEL 15
#define PS2_DAT 12
#define pressures false
#define rumble false

#define LeftServoGround 2
#define RightServoGround 3
#define LeftServoPulley 4
#define RightServoPulley 5

float timeOn = 2000;

PS2X ps2x;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

byte error = -1;
uint16_t tryNum = 0;
byte doorState = 1;

void setSpeed(int16_t left, int16_t right)
{
    if (left >= 0)
    {
        pwm.setPWM(8, 0, left);
        pwm.setPWM(9, 0, 0);
    }
    else if (left < 0)
    {
        pwm.setPWM(8, 0, 0);
        pwm.setPWM(9, 0, -left);
    }

    if (right >= 0)
    {
        pwm.setPWM(10, 0, right);
        pwm.setPWM(11, 0, 0);
    }
    else if (right < 0)
    {
        pwm.setPWM(10, 0, 0);
        pwm.setPWM(11, 0, -right);
    }
}

float servoConverter(float angle, float timeOn)
{
    return timeOn / (20 * (angle / 180) / 4096);
}

void setup()
{
    Serial.begin(115200);
    while (error != 0)
    {
        delay(1000);
        error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    }
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(60);
    Wire.setClock(400000);
}

void loop()
{
    if (ps2x.Button(PSB_PAD_UP))
        setSpeed(1023, 1023);
    else if (ps2x.Button(PSB_PAD_LEFT))
        setSpeed(-1023, 1023);
    else if (ps2x.Button(PSB_PAD_RIGHT))
        setSpeed(1023, -1023);
    else if (ps2x.Button(PSB_PAD_DOWN))
        setSpeed(-1023, -1023);
    else
        setSpeed(0, 0);

    /*CƠ CHẾ HOẠT ĐỘNG CỦA 2 SERVO CỔNG:
    - Kênh 2 và kênh 3.
    - Có 3 chế độ: đóng, mở vừa, mở rộng.
    - Sử dụng 2 phím R1-R2 để luân chuyển giữa các chế độ.
        với 1 - đóng | 2 - mở vừa | 3 - mở rộng
    - R1 ++1 trạng thái
    - R2 --1 trạng thái*/

    if ((doorState == 1 or doorState == 2) and ps2x.ButtonPressed(PSB_R2))
    {
        doorState++;
        //      // Extend door outwards
        //     pwm.writeMicroseconds(LeftServoGround, timeOn);
        //  // Extend door outwards
        //     pwm.writeMicroseconds(RightServoGround, timeOn);

        pwm.setPWM(LeftServoGround, 0, 410);  // chọn kênh servo số 5
        pwm.setPWM(RightServoGround, 0, 410); // chọn kênh servo số 5
    }
    if ((doorState == 2 or doorState == 3) and ps2x.ButtonPressed(PSB_R1))
    {
        doorState--;
        pwm.setPWM(LeftServoGround, 0, 205);  // chọn kênh servo số 5
        pwm.setPWM(RightServoGround, 0, 205); // chọn kênh servo số 5
    }
    /*CƠ CHẾ HOẠT ĐỘNG CỦA 2 SERVO TRÊN:
    - Có 2 chế độ: nâng lên và hạ thấp xuống.
    - Sử dụng 2 phím L1-L2 để luân chuyển giữa 3 chế độ.
     với 1 - nâng lên | 2 - tạm dừng | 3 - hạ thấp
    - L1 ++1 trạng thái
    - R2 --1 trạng thái*/

    ps2x.read_gamepad();
    delay(10);
}