// Motor channels [chan1, chan2]
static const int DRIVE_LEFT_CHAN[2] = {8, 9}; // Left motor channels
static const int DRIVE_RIGHT_CHAN[2] = {10, 11}; // Right motor channels
static const int INTAKE_CHAN[2] = {12, 13}; // Intake motor channels
static const int SHOOTER_CHAN[2] = {14, 15}; // Shooter motor channels

// Servo channels
static const int SERIALIZER_WATER_GATE_CHAN = 2; //Serializer, water gate servo
static const int SERIALIZER_WASTE_GATE_CHAN = 3; //Serializer, waste gate servo
static const int LOADER_CHAN = 4; // Water loader servo
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
static const float GRAVITATIONAL_ACCELERATION = 9.8; // g = 9.8m/s^2
static const float WHEEL_RADIUS = 0.09; // Wheel radius in meter
static const float SHOOTER_HEIGHT = 0.5; // Shooter height (meter)
static const float GOAL_HEIGHT = 1.8; // Goal height (meter)
static const float MAX_RPM = 1500; // Max RPM of shooter

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
static const int SERIALIZER_WATER_CLOSE = 135; // The angle value when Serializer servo turns to water processor
static const int SERIALIZER_GABBAGE_CLOSE = 45;// The angle value when Serializer servo turns to gabbage processor
static const int SERIALIZER_WATER_OPEN = 45; // The angle value when Serializer servo turns to water processor
static const int SERIALIZER_GABBAGE_OPEN = 135;// The angle value when Serializer servo turns to gabbage processor
// Dumper angle values (degrees)
static const int DUMPER_CLOSED_STATE = 0; // The angle value when Dumper servo is closed
static const int DUMPER_OPEN_STATE = 90; // The angle value when Dumper servo is open

// Color detection variables (read function in serializer.cpp)
static const int COLOR_THRESHOLD = 128; // Threshold to determine black or white