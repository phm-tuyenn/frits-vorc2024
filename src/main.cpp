#include <Arduino.h>
#include <PS2X_lib.h>
#include <Adafruit_PWMServoDriver.h>
// ************************************************
//                    DEBUG PRINT
// ************************************************

//#define DBG_PRINT

#define PS2_CLK 14
#define PS2_CMD 13
#define PS2_SEL 15
#define PS2_DAT 12
#define pressures false
#define rumble false

#define TIMER_LENGTH1 20000
#define TIMER_LENGTH2 500000

uint8_t tempgnd = 0;
#define LeftServoGround 6
#define RightServoGround 2
#define LeftServoPulley 5
#define RightServoPulley 4

#define LeftPullState1 1550   //  45*
#define RightPullState1 1500     
#define LeftPullState2 1050 // home
#define RightPullState2 1950 // home
#define LeftPullState3 2400 // 135*
#define RightPullState3 600 // 135*

#define NERFINPIN 12

#define SPEED_CONST 4095

PS2X ps2x;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
//hw timer definition
hw_timer_t *ContTimer0;
hw_timer_t *ContTimer1;
hw_timer_t *ContTimer2;
hw_timer_t *ContTimer3;

byte error = -1;
uint16_t tryNum = 0;

// door and pull variables
bool doorState = true;
int prevDoor;

byte pullState = 1;
int prevPull;
bool delayPullState = true;

uint8_t Lmotor = 0;
uint8_t Rmotor = 0;

uint8_t Lstick_Y;
uint8_t Rstick_X;

struct 
{
    bool DoorState;
    bool DoorMode;
    bool PullState;
    bool GroundPos;
    signed int  RightMotVal;
    signed int LeftMotVal;
    int mappedLJoyY;
    int mappedRJoyX;
    int mappedLJoyYTurning;
    int mappedRJoyXTurning;
    bool DelayState = true;
    bool PullDelayState = true;
    int NERFSTATE = 0;

} ContDataDecode;

struct 
{
    uint16_t Lstick_Y;
    uint16_t Rstick_X;
    bool Button_Circle;
    bool Button_Triangle;
    bool Button_Cross;
    bool Button_Square;
    bool Button_L1;
    bool Button_L2;
    bool Button_R1;
    bool Button_R2;
} ContData;

bool ContCheckFlag = false;



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

void MapMotor(int LJoyY,int RJoyX){
    int TempLeftMotVal ;
    int TempRightMotVal ;
    ContDataDecode.mappedLJoyY = map(constrain(LJoyY, 0, 255), 255, 0, -4000, 4000);
    ContDataDecode.mappedRJoyX = map(constrain(RJoyX, 0, 255), 0, 255, -4000, 4000);
    ContDataDecode.mappedLJoyYTurning = map(LJoyY, 255, 0, -2000, 2000);
    ContDataDecode.mappedRJoyXTurning = map(RJoyX, 0, 255, -2000, 2000);
    if (ContDataDecode.mappedRJoyX) // Turning
    {
        TempLeftMotVal = ContDataDecode.mappedLJoyYTurning + ContDataDecode.mappedRJoyXTurning;
        TempRightMotVal = ContDataDecode.mappedLJoyYTurning - ContDataDecode.mappedRJoyXTurning;
    }
    else // Forward or Reverse
    {
        TempLeftMotVal =  ContDataDecode.mappedLJoyY;
        TempRightMotVal = ContDataDecode.mappedLJoyY;
    }
    ContDataDecode.LeftMotVal = TempLeftMotVal;
    ContDataDecode.RightMotVal = TempRightMotVal;
}

void IRAM_ATTR NERFMODEXD(){
    if(ContData.Button_Circle){
        pwm.setPWM(NERFINPIN,0,100);
        pwm.setPWM(13, 0, 0);
        ContDataDecode.NERFSTATE = 2;
    }
    else{
        timerDetachInterrupt(ContTimer3);
        timerEnd(ContTimer3);
        ContDataDecode.NERFSTATE = 0;
    }
}

void IRAM_ATTR ControllerReadTimed(){  //IRAM_ATTR makes the function resides in ram which is nescessary in fast timer ISR's (may reach the RAM limit)
    ps2x.read_gamepad(0,0);
    ContData.Lstick_Y =  ps2x.Analog(PSS_LY) - 1;
    ContData.Rstick_X =  ps2x.Analog(PSS_RX) - 1;
    ContData.Button_Circle = ps2x.ButtonPressed(PSB_CIRCLE);
    ContData.Button_Cross = ps2x.ButtonPressed(PSB_CROSS);
    ContData.Button_Square = ps2x.ButtonPressed(PSB_SQUARE);
    ContData.Button_Triangle = ps2x.ButtonPressed(PSB_TRIANGLE);
    ContData.Button_L1 = ps2x.ButtonPressed(PSB_L1);
    ContData.Button_L2 = ps2x.ButtonPressed(PSB_L2);
    ContData.Button_R1 = ps2x.Button(PSB_R1);
    ContData.Button_R2 = ps2x.Button(PSB_R2);
    ContData.Button_Circle = ps2x.Button(PSB_CIRCLE);

    if(ContData.Button_Circle){
        ContTimer3 = timerBegin(3, 80, true);
        timerAttachInterrupt(ContTimer3,&NERFMODEXD, true);
        timerAlarmWrite(ContTimer3, 2000000, false);
        timerAlarmEnable(ContTimer3);
        ContDataDecode.NERFSTATE = 1;
    }
    
    ContCheckFlag = true;

}

void ServoDecd(){
    if(ContData.Button_L1 & ContDataDecode.DelayState){
        ContDataDecode.DelayState = false;
        ContDataDecode.DoorState = !ContDataDecode.DoorState;
        if(ContDataDecode.DoorMode){
            ContDataDecode.DoorMode = false;
        }
    }
        
    if(ContData.Button_L2 & ContDataDecode.DelayState){
        ContDataDecode.DelayState = false;
        ContDataDecode.DoorMode = !ContDataDecode.DoorMode;
        if(!ContDataDecode.DoorState){
            ContDataDecode.DoorState = !ContDataDecode.DoorState;
        }
    }
}

void IRAM_ATTR ServoLock(){
    if(ContDataDecode.DelayState == false){
        ContDataDecode.DelayState = true;
    }
}

void ServoCont(){
    unsigned long time = 5000L;
    int LeftOpenServoVal;
    int RightOpenServoVal;
    if (ContDataDecode.DoorMode)
    {
        LeftOpenServoVal = LeftPullState1;
        RightOpenServoVal = RightPullState1;
    } 
    else {
        LeftOpenServoVal = LeftPullState3;
        RightOpenServoVal = RightPullState3;
    }
    
    if(ContDataDecode.DoorState){
        pwm.writeMicroseconds(LeftServoGround, LeftOpenServoVal);
        pwm.writeMicroseconds(RightServoGround, RightOpenServoVal);
        
    }
    else
    {
        pwm.writeMicroseconds(LeftServoGround, LeftPullState2);
        pwm.writeMicroseconds(RightServoGround, RightPullState2);
    }
    
    if(ContData.Button_R1){
        pwm.writeMicroseconds(LeftServoPulley, 1000);
        pwm.writeMicroseconds(RightServoPulley, 2200);
    }
    if(ContData.Button_R2){
        pwm.writeMicroseconds(LeftServoPulley, 2200);
        pwm.writeMicroseconds(RightServoPulley, 1000);
    }
    if(!ContData.Button_R1 & !ContData.Button_R2){
        pwm.writeMicroseconds(LeftServoPulley, 0);
        pwm.writeMicroseconds(RightServoPulley, 0);
    }

}
    
void IRAM_ATTR PullstateChange(){
    ContDataDecode.PullState = false;

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

    pwm.setPin(8,0);
    pwm.setPin(9,0);
    pwm.setPin(10,0);
    pwm.setPin(11,0);

    ContTimer0 = timerBegin(0, 80, true);
    timerAttachInterrupt(ContTimer0, &ControllerReadTimed, true);
    timerAlarmWrite(ContTimer0, TIMER_LENGTH1, true);
    timerAlarmEnable(ContTimer0);

    ContTimer1 = timerBegin(1, 80, true);
    timerAttachInterrupt(ContTimer1, &ServoLock, true);
    timerAlarmWrite(ContTimer1, TIMER_LENGTH2, true);
    timerAlarmEnable(ContTimer1);

    ContTimer2 = timerBegin(2, 80, true);
    timerAttachInterrupt(ContTimer2, &PullstateChange, true);
    timerAlarmWrite(ContTimer2,750000 , true);
    timerAlarmEnable(ContTimer2);

    Serial.println("isr timers enabled");
}

void loop()
{   
    MapMotor(ContData.Lstick_Y, ContData.Rstick_X);
    setSpeed(ContDataDecode.LeftMotVal, ContDataDecode.RightMotVal);
    ServoDecd();
    ServoCont();
    #ifdef DBG_PRINT
    if(ContCheckFlag == true){

        Serial.print("ContLY:");
        Serial.print(ContData.Lstick_Y);
        Serial.print(",");
        Serial.print("ContRX:");
        Serial.println(ContData.Rstick_X);

        Serial.print("MappedContLY:");
        Serial.print(ContDataDecode.mappedLJoyY);
        Serial.print(",");
        Serial.print("MappedContRX:");
        Serial.println(ContDataDecode.mappedRJoyX);
    
        Serial.print("MotLeft:");
        Serial.print(ContDataDecode.LeftMotVal);
        Serial.print(",");
        Serial.print("MotRight:");
        Serial.println(ContDataDecode.RightMotVal);
        ContCheckFlag = false;

        Serial.print("Cross: ");
        Serial.print(ContData.Button_Cross);
        Serial.print(", ");
        Serial.print("Triangle: ");
        Serial.print(ContData.Button_Triangle);
        Serial.print(", ");
        Serial.print("Circle: ");
        Serial.print(ContData.Button_Circle);
        Serial.print(", ");
        Serial.print("Square: ");
        Serial.println(ContData.Button_Square);

        Serial.print("L1: ");
        Serial.print(ContData.Button_L1);
        Serial.print(", ");
        Serial.print("L2: ");
        Serial.print(ContData.Button_L2);
        Serial.print(", ");
        Serial.print("R1: ");
        Serial.println(ContData.Button_R1);

        Serial.print("DoorState:");
        Serial.print(ContDataDecode.DoorState);
        Serial.print(", ");
        Serial.print("DoorMode:");
        Serial.println(ContDataDecode.DoorMode);

        Serial.print("PullState:");
        Serial.print(ContDataDecode.PullState);
        Serial.print(", ");
        Serial.print("PullPos:");
        Serial.println(ContDataDecode.GroundPos);

        Serial.print("LauncherStage:")
        Serial.println(ContDataDecode.NERFSTATE);

        Serial.println("\n");
        Serial.println("\n");
        Serial.println("\n");
        Serial.println("\n");
        Serial.println("\n");
        Serial.println("\n");   
        } 
    #endif
}
