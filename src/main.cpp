#include <Arduino.h>
#include <PS2X_lib.h>
#include <Adafruit_PWMServoDriver.h>

#define PS2_CLK 14
#define PS2_CMD 13
#define PS2_SEL 15
#define PS2_DAT 12
#define pressures false
#define rumble false

int tempgnd = 0;
#define LeftServoGround 2
#define RightServoGround 3
#define LeftServoPulley 6
#define RightServoPulley 7

#define LeftGroundState1 1500
#define RightGroundState1 1500
#define LeftGroundState2 1050
#define RightGroundState2 1950
#define LeftGroundState3 2400
#define RightGroundState3 600

PS2X ps2x;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

byte error = -1;
uint16_t tryNum = 0;

// door and pull variables
byte doorState = 1;
int prevDoor;
bool delayDoorState = true;

byte pullState = 1;
int prevPull;
bool delayPullState = true;
//

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

void changeDoorState()
{
    // Serial.print("Da vao ben trong change doorstate");
    if ((doorState == 1) and ps2x.ButtonPressed(PSB_CIRCLE))
    {
        Serial.println(doorState);
        doorState++;
        pwm.writeMicroseconds(LeftServoGround, LeftGroundState1);
        pwm.writeMicroseconds(RightServoGround, RightGroundState1);
        //  Serial.println(doorState, LeftGroundState1);
    }

    else if ((doorState == 2) and ps2x.ButtonPressed(PSB_CIRCLE))
    {
        Serial.println(doorState);
        doorState++;
        pwm.writeMicroseconds(LeftServoGround, LeftGroundState2);
        pwm.writeMicroseconds(RightServoGround, RightGroundState2);
        // Serial.println("so 2 ");
    }

    else if ((doorState == 3) and ps2x.ButtonPressed(PSB_CIRCLE))
    {
        Serial.println(doorState);
        doorState = 1;
        pwm.writeMicroseconds(LeftServoGround, LeftGroundState3);
        pwm.writeMicroseconds(RightServoGround, RightGroundState3);
        // Serial.println("so 3 ");
    }
}

/*
    if true and pressed {
        true = false;
        prev = millis();
        do something
    }

    if millis() - prev > time {
        false = true
        stop do something
    }
    */

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
    pwm.writeMicroseconds(LeftServoGround, 1500);
    pwm.writeMicroseconds(RightServoGround, 1500);
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

    if ((delayDoorState) and (ps2x.ButtonPressed(PSB_CIRCLE)))
    {
        delayDoorState = false;
        prevDoor = millis();
        // do something
        changeDoorState();
        // Serial.println("running");
        // Serial.println(doorState);
        // Serial.println(ps2x.ButtonPressed(PSB_CIRCLE));
    }

    if (millis() - prevDoor > 500)
    {
        delayDoorState = true;
        {
            pwm.setPWM(LeftServoGround, 0, 0);
            pwm.setPWM(RightServoGround, 0, 0);
            // Serial.println("RUn2");
        }
    }

    /*CƠ CHẾ HOẠT ĐỘNG CỦA 2 SERVO TRÊN:
    - Có 2 chế độ: nâng lên và hạ thấp xuống.
    - Sử dụng 2 phím L1-L2 để luân chuyển giữa 3 chế độ.
     với 1 - nâng lên | 2 - tạm dừng | 3 - hạ thấp
    - L1 ++1 trạng thái
    - L2 --1 trạng thái*/

    { // pull up
        if ((delayPullState) and (ps2x.ButtonPressed(PSB_CROSS)))
        {
            delayPullState = false;
            prevPull = millis();
            // do something
            {
                pwm.writeMicroseconds(LeftServoPulley, 800);
                pwm.writeMicroseconds(RightServoPulley, 2200);
            }
        }

        if (millis() - prevPull > 1000)
        {
            delayPullState = true;
            {
                pwm.writeMicroseconds(LeftServoPulley, 0);
                pwm.writeMicroseconds(RightServoPulley, 0);
            }
        }
    }

    // if /*((pullState == 2 or pullState == 3) and*/ (ps2x.ButtonReleased(PSB_CROSS))
    // {
    //     // Serial.println(doorState);
    //     pullState--;
    //     pwm.writeMicroseconds(LeftServoPulley, 2000);
    //     pwm.writeMicroseconds(RightServoPulley, 2000);
    // }

    ps2x.read_gamepad();
}