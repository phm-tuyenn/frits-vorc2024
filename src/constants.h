// Motor channels [chan1, chan2]
static const int DRIVE_LEFT_CHAN[2] = {8, 9}; // Left motor channels
static const int DRIVE_RIGHT_CHAN[2] = {10, 11}; // Right motor channels
static const int INTAKE_CHAN[2] = {12, 13}; // Intake motor channels
static const int SHOOTER_CHAN[2] = {14, 15}; // Shooter motor channels

// Servo channels
static const int SERIALIZER_CHAN = 2; //Serializer servo
static const int LOADER_CHAN = 3; // Water loader servo
static const int HOOD_CHAN = 4; // Adjustable hood servo
static const int DUMPER_CHAN = 5; // Waste dumper servo

// Distance sensor pin
static const int TRIGPIN = 36; // Trigger pin
static const int ECHOPIN = 39; // Echo pin

// Gamepad setup
static const int PS2_CLK = 14;
static const int PS2_CMD = 13; 
static const int PS2_SEL = 15;
static const int PS2_DAT = 12;
static const bool PRESSURES = false;
static const bool RUMBLE = false;

// These constant don't need to tuned
static const float WHEEL_RADIUS = 0.10795; // Wheel radius in meter
static const float FLYWHEEL_VELOCITY_METER_PER_SEC = 13.565397078200727; // Flywheel velocity in m/s
static const float FLYWHEEL_VELOCITY_PERCENT = 0.8; // Flywheel velocity in percent for `void setMotorSpeed()`
static const float SHOOTER_HEIGHT = 0.5; // Shooter height (meter)
static const float GOAL_HEIGHT = 1.8; // Goal height (meter)

// These constant below need to tuned to use in real life, so these a pseudo-constants
// Servo constant
static const int T_on_0deg = 1; // On cycle time microsec for 0deg rotation
static const int Ts = 20; // Dutycycle time microsec

