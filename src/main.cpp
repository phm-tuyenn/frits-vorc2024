#include <Arduino.h>
#include <PS2X_lib.h>
#include <Adafruit_PWMServoDriver.h>

#define PS2_CLK 14
#define PS2_CMD 13
#define PS2_SEL 15
#define PS2_DAT 12
#define pressures false
#define rumble false

#define TIMER_LENGTH 800

uint8_t tempgnd = 0;
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

uint8_t Lmotor = 0;
uint8_t Rmotor = 0;

uint8_t Lstick_Y;
uint8_t Rstick_X;

struct 
{
    bool DoorState135;
    bool Doorstate45;
    bool GroundState;
    uint16_t RightMotVal;
    uint16_t LeftMotVal;
} ContDataDecode;

struct 
{
    uint16_t Lstick_Y;
    uint16_t Rstick_X;
    bool Button_Circle;
    bool Button_Triangle;
    bool Button_Cross;
    bool Button_Square;
} ContData;


//hw timer definition
hw_timer_t *ContTimer;

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


void MapMotor(int StickLY, int StickRX){

    if(StickRX >= 0){
        ContDataDecode.RightMotVal = ContDataDecode.LeftMotVal = map(StickLY, -255, 255, 0, 3072);
        ContDataDecode.LeftMotVal += 1024;
    }
    if(StickRX <= 0){
        ContDataDecode.RightMotVal = ContDataDecode.LeftMotVal = map(StickLY, -255, 255, 0, 3072);
        ContDataDecode.RightMotVal += 1024;
    }  
}

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


void IRAM_ATTR ControllerReadTimed(){  //IRAM_ATTR makes the function resides in ram which is nescessary in fast timer ISR's (may reach the RAM limit)
        // R2 là đi thẳng, L1 là rẽ phải, 
    // R1 là rẽ phải, L2 là đi lùi
    // R2 cộng R1 = vừa đi thẳng vừa rẽ phải
    // R2 cộng L1 = vừa đi thẳng vừa rẽ trái
    // L2 cộng R1 = vừa đi lùi vừa rẽ phải
    // L2 cộng L1 = vừa đi lùi vừa rẽ trái
    // L2 + R2 = dừng
    ContData.Lstick_Y = ps2x.Analog(PSS_LY);
    ContData.Rstick_X = ps2x.Analog(PSS_RX);
    ContData.Button_Circle = ps2x.ButtonPressed(PSB_CIRCLE);
    ContData.Button_Cross = ps2x.ButtonPressed(PSB_CROSS);
    ContData.Button_Square = ps2x.ButtonPressed(PSB_SQUARE);
    ContData.Button_Triangle = ps2x.ButtonPressed(PSB_TRIANGLE);
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
    pwm.writeMicroseconds(LeftServoGround, 1500);
    pwm.writeMicroseconds(RightServoGround, 1500);

    // ContTimer = timerBegin(0, 80, true);
    // timerAttachInterrupt(ContTimer, &ControllerReadAndExecuteTimed, true);
    // timerAlarmWrite(ContTimer, TIMER_LENGTH, true);
    // timerAlarmEnable(ContTimer);


    ContTimer = timerBegin(0, 80, true);
    timerAttachInterrupt(ContTimer, &ControllerReadTimed, true);
    timerAlarmWrite(ContTimer, TIMER_LENGTH, true);
    timerAlarmEnable(ContTimer);
    Serial.println("isr timer enabled");
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


void loop()
{
    MapMotor(ContData.Lstick_Y, ContData.Rstick_X);
    setSpeed(ContDataDecode.LeftMotVal, ContDataDecode.RightMotVal);
}
