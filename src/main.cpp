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
#define LeftServoGround 6
#define RightServoGround 3
// #define LeftServoPulley 4
#define RightServoPulley 4

#define LeftGroundState1 1800   //  45*
#define RightGroundState1 1200 // 45*
#define LeftGroundState2 1050 // home
#define RightGroundState2 1950 // home
#define LeftGroundState3 2400 // 135*
#define RightGroundState3 600 // 135*

PS2X ps2x;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

byte error = -1;
uint16_t tryNum = 0;

// door and pull variables
bool doorState = true;
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
    if (doorState == true)
    {
        // Serial.println(doorState); nút tam giác mở 45 độ, nút tròn mở 135 độ, 
        // cả hai nút bấm hai lần thì quay lại ban đầu
        doorState = false;
        pwm.writeMicroseconds(LeftServoGround, LeftGroundState2);
        pwm.writeMicroseconds(RightServoGround, RightGroundState2);
        //  Serial.println(doorState, LeftGroundState1);
    }
    else if (doorState == false)
    {
        // Serial.println(doorState);
        doorState = true;
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
    // R2 là đi thẳng, L1 là rẽ phải, 
    // R1 là rẽ phải, L2 là đi lùi
    // R2 cộng R1 = vừa đi thẳng vừa rẽ phải
    // R2 cộng L1 = vừa đi thẳng vừa rẽ trái
    // L2 cộng R1 = vừa đi lùi vừa rẽ phải
    // L2 cộng L1 = vừa đi lùi vừa rẽ trái
    // L2 + R2 = dừng
    
    bool stop = false;
    if (ps2x.Button(PSB_R1)) //
        setSpeed(2023, 2023);
    else if (ps2x.Button(PSB_L2))
        setSpeed(-2023, 2023);
    else if (ps2x.Button(PSB_R2))
        setSpeed(2023, -2023);
    else if (ps2x.Button(PSB_L1))
        setSpeed(-2023, -2023);
    else stop = true;
    
    if ((ps2x.Button(PSB_R1)) and (ps2x.Button(PSB_R2))) // R1 cộng R2 = vừa đi thẳng vừa rẽ phải           //
        setSpeed(2400, 1800);
    else if ((ps2x.Button(PSB_R1)) and (ps2x.Button(PSB_L2))) // L1 cộng R2 = vừa đi thẳng vừa rẽ trái     //
        setSpeed(1800, 2400);
    else if ((ps2x.Button(PSB_L1)) and (ps2x.Button(PSB_R2))) // R1 cộng L2 = vừa lùi vừa rẽ phải
        setSpeed(-2400, -1800);
    else if ((ps2x.Button(PSB_L1)) and (ps2x.Button(PSB_L2))) // L1 cộng L2 = vừa lùi vừa rẽ trái
        setSpeed(-1800, -2400);
    else if ((ps2x.Button(PSB_L2) and ps2x.Button(PSB_R2)))
        setSpeed(0, 0);
    else
        stop = true;

    if (stop) setSpeed(0, 0);
  

    // 2 SERVO CỔNG

    // ĐÓNG - MỞ
    if ((delayDoorState) and (ps2x.ButtonPressed(PSB_CIRCLE)))
    {
        delayDoorState = false;
        prevDoor = millis();
        // do something
        changeDoorState();
    }

    // MỞ 45 ĐỘ

    if ((delayDoorState) and (ps2x.ButtonPressed(PSB_TRIANGLE)))
    {
        doorState = true;
        // LƯU Ý: Sau khi mở 45 độ, khi nhấn CIRCLE (hàm ĐÓNG/MỞ), 2 servo sẽ luôn về 
        // trạng thái đóng, cần ấn CIRCLE 1 lần nữa để mở ra góc 135 độ.
        delayDoorState = false;
        prevDoor = millis();
        // do something
        pwm.writeMicroseconds(LeftServoGround, LeftGroundState1);
        pwm.writeMicroseconds(RightServoGround, RightGroundState1);
    }

    if (millis() - prevDoor > 500)
    {
        delayDoorState = true;
        {
            pwm.writeMicroseconds(LeftServoGround, 0);
            pwm.writeMicroseconds(RightServoGround, 0);
        }
    }

    //
    
    if ((delayPullState) and (ps2x.ButtonPressed(PSB_SQUARE))) {
            delayPullState = false;
            prevPull = millis();
            pwm.writeMicroseconds(RightServoPulley, 1000);
    };
   
     // pull up
    if ((delayPullState) and (ps2x.ButtonPressed(PSB_CROSS)))
        {
            delayPullState = false;
            prevPull = millis();
            // do something
            // pwm.writeMicroseconds(LeftServoPulley, 800);
            pwm.writeMicroseconds(RightServoPulley, 2200);
            
        }

    if (millis() - prevPull > 1500)
        {
            delayPullState = true;
            {
                // pwm.writeMicroseconds(LeftServoPulley, 0);
                pwm.writeMicroseconds(RightServoPulley, 0);
            }
        }
    
    ps2x.read_gamepad();
}