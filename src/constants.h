// Motor channels [chan1, chan2]
#define DRIVE_LEFT_CHAN [8, 9] // Left motor channels
#define DRIVE_RIGHT_CHAN [10, 11] // Right motor channels
#define INTAKE_CHAN [12, 13] // Intake motor channels
#define SHOOTER_CHAN [14, 15] // Shooter motor channels

// Servo channels
#define SERIALIZER_CHAN 2 //Serializer servo
#define LOADER_CHAN 3 // Water loader servo
#define HOOD_CHAN 4 // Adjustable hood servo
#define DUMPER_CHAN 5 // Waste dumper servo

// Distance sensor pin
#define TRIGPIN 36 // Trigger pin
#define ECHOPIN 39 // Echo pin

// Gamepad setup
#define PS2_CLK 14
#define PS2_CMD 13 
#define PS2_SEL 15
#define PS2_DAT 12
#define PRESSURES false
#define RUMBLE false

// These constant below need to tuned to use in real life, so these a pseudo-constants
// Servo constant
#define T_on_0deg 1 // On cycle time microsec for 0deg rotation
#define Ts 20 // Dutycycle time microsec

