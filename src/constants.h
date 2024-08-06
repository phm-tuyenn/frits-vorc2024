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

// These constant below need to tuned to use in real life, so they are pseudo-constants
// Servo constant
static const int T_on_0deg = 1; // On cycle time microsec for 0deg rotation
static const int Ts = 20; // Dutycycle time microsec
static const float SERVO360_COUNTER_CLOCKWISE = 0; // Value for 360deg servo to rotate counter clockwise
static const float SERVO360_CLOCKWISE = 180; // Value for 360deg servo to rotate clockwise
static const float SERVO360_STOP = 60; // Value for 360deg servo to stop rotate
// Gamepad constant
static const int JOYSTICK_LEFT_CENTER_VAL = 127; // The analog value when left joystick in center
static const int JOYSTICK_RIGHT_CENTER_VAL = 127; // The analog value when right joystick in center
// Intake motor speed
static const float INTAKE_SPEED = 0.8; //  Motor speed for intake motor
// Serializer angle values (degrees)
static const int SERIALIZER_NEUTRAL_STATE = 90; // The angle value when Serializer servo is neutral/in the middle
static const int SERIALIZER_WATER_STATE = 0; // The angle value when Serializer servo turns to water processor
static const int SERIALIZER_GABBAGE_STATE = 180;// The angle value when Serializer servo turns to gabbage processor
// Dumper angle values (degrees)
static const int DUMPER_CLOSED_STATE = 0; // The angle value when Dumper servo is closed
static const int DUMPER_OPEN_STATE = 90; // The angle value when Dumper servo is open

// Color detection variables (read function in serializer.cpp)
// Fixed-constants
static const int BLACK_MIN = 0; // The R,G and B code for BLACK color code
static const int WHITE_MAX = 255; // The R,G and B code for WHITE color code
// Pseudo-constants
static const int BLACK_MAX[3] = {127,127,127}; // The R,G and B code for the limit of BLACK color
static const int WHITE_MIN[3] = {129,129,129}; // The R,G and B code for the limit of WHITE color
