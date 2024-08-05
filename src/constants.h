// Motor channels [chan1, chan2]
#define drive_left [8, 9] // Left motor channels
#define drive_right [10, 11] // Right motor channels
#define intake [12, 13] // Intake motor channels
#define shooter [14, 15] // Shooter motor channels

// Servo channels
#define serializer 2 //Serializer servo
#define loader 3 // Water loader servo
#define hood 4 // Adjustable hood servo
#define dumper 5 // Waste dumper servo

// Distance sensor pin
#define trigPin 36 // Trigger pin
#define echoPin 39 // Echo pin

// Gamepad setup
#define PS2_CLK 14
#define PS2_CMD 13 
#define PS2_SEL 15
#define PS2_DAT 12
#define pressures false
#define rumble false

// These constant below need to tuned to use in real life, so these a pseudo-constants
// Servo constant
#define T_on_0deg 1 // On cycle time microsec for 0deg rotation
#define Ts 20 // Dutycycle time microsec

