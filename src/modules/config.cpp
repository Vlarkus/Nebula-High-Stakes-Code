/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "modules/config.hpp"





/*
 * ╭────────╮
 * │ DEFINE │
 * ╰────────╯
 */

#define IMU_PORT 16
#define OPTICAL_PORT 17
#define DISTANCE_PORT 14

#define STAGE_1_INTAKE 2
#define STAGE_2_INTAKE 1
#define INTAKE_GEARSET MotorGearset::blue

#define ROTATION_ODOM_VERT_PORT 5

#define ROTATIONAL_LB_PORT 10
#define LADYBROWN_PORT 9
#define LB_MOTOR_GEARSET MotorGearset::blue

#define LEFT_LED_ADI_PORT 1
#define RIGHT_LED_ADI_PORT 2
#define DOINKER_ADI_PORT 'G'
#define MOGO_ADI_PORT 'H'

#define LEFT_DT_A_PORT 18
#define LEFT_DT_B_PORT 19
#define LEFT_DT_C_PORT 20
#define RIGHT_DT_A_PORT 11
#define RIGHT_DT_B_PORT 12
#define RIGHT_DT_C_PORT 13
#define DT_MOTOR_GEARSET MotorGearset::blue





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace std;
using namespace pros;
using namespace lemlib;





/*
 * ╭─────╮
 * │ LED │
 * ╰─────╯
 */

stormlib::aRGB left_strand(LEFT_LED_ADI_PORT, 19);
stormlib::aRGB right_strand(RIGHT_LED_ADI_PORT, 19);
stormlib::aRGB_manager led(&left_strand, &right_strand, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);





/*
 * ╭────────────╮
 * │ CONTROLLER │
 * ╰────────────╯
 */

ExpoDriveCurve throttleCurve(3, 10, 1.015); // Fields: deadband, min, expo
ExpoDriveCurve steerCurve(3, 10, 1.015); // Fields: deadband, min, expo

Controller controller(E_CONTROLLER_MASTER);





/*
 * ╭─────────╮
 * │ BUTTONS │
 * ╰─────────╯
 */

const controller_digital_e_t INTAKE_IN_BTN = E_CONTROLLER_DIGITAL_L1;
const controller_digital_e_t INTAKE_OUT_BTN = E_CONTROLLER_DIGITAL_R1;
const controller_digital_e_t MOGO_IN_BTN = E_CONTROLLER_DIGITAL_L2;
const controller_digital_e_t MOGO_OUT_BTN = E_CONTROLLER_DIGITAL_R2;

const controller_digital_e_t SELECTIVE_INTAKE_TOGGLE_ACTIVE_BTN = E_CONTROLLER_DIGITAL_A;
const controller_digital_e_t SELECTIVE_INTAKE_TOGGLE_COLOR_BTN = E_CONTROLLER_DIGITAL_Y;

const pros::controller_digital_e_t LADYBROWN_LOADSCORETOGGLE_BTN = E_CONTROLLER_DIGITAL_DOWN;
const pros::controller_digital_e_t LADYBROWN_STORE_BTN = E_CONTROLLER_DIGITAL_B;

extern const pros::controller_digital_e_t DOINKER_ACTIVATE_BTN = E_CONTROLLER_DIGITAL_UP;
extern const pros::controller_digital_e_t DOINKER_DEACTIVATE_BTN = E_CONTROLLER_DIGITAL_X;
extern const pros::controller_digital_e_t CTRL_BTN = E_CONTROLLER_DIGITAL_LEFT;





/*
 * ╭────────╮
 * │ INTAKE │
 * ╰────────╯
 */

MotorGroup intake({STAGE_1_INTAKE, STAGE_2_INTAKE}, INTAKE_GEARSET);





/*
 * ╭──────╮
 * │ ADIs │
 * ╰──────╯
 */

adi::DigitalOut mogoPiston(MOGO_ADI_PORT, false);
adi::DigitalOut doinkerPiston(DOINKER_ADI_PORT, false);





/*
 * ╭─────╮
 * │ IMU │
 * ╰─────╯
 */

Imu imu(IMU_PORT);





/*
 * ╭───────────╮
 * │ LADYBROWN │
 * ╰───────────╯
 */
Rotation lbEncoderSensor(ROTATIONAL_LB_PORT);
Motor ladyBrown({LADYBROWN_PORT}, LB_MOTOR_GEARSET);





/*
 * ╭─────────╮
 * │ OPTICAL │
 * ╰─────────╯
 */

Optical opticalSensor(OPTICAL_PORT);





/*
 * ╭──────────╮
 * │ DISTANCE │
 * ╰──────────╯
 */

Distance distanceSensor(DISTANCE_PORT);





/*
 * ╭────────────╮
 * │ DRIVETRAIN │
 * ╰────────────╯
 */

auto omniwheels = Omniwheel::NEW_325;
float trackWidth = 13;
float rpm = 480;
float horizontalDrift = 8; //original was 360, lemlib said 2 or 8 for traction wheels

MotorGroup leftMotors({-LEFT_DT_A_PORT, -LEFT_DT_B_PORT, -LEFT_DT_C_PORT}, DT_MOTOR_GEARSET);
MotorGroup rightMotors({RIGHT_DT_A_PORT, RIGHT_DT_B_PORT, RIGHT_DT_C_PORT}, DT_MOTOR_GEARSET);

Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              trackWidth, // inch track width
                              omniwheels, // omniwheels
                              rpm, // rpm
                              horizontalDrift // horizontal drift
);





/*
 * ╭──────────╮
 * │ ODOMETRY │
 * ╰──────────╯
 */

Rotation verticalEnc(-ROTATION_ODOM_VERT_PORT);
TrackingWheel vertical(&verticalEnc, 1, 0.25);

OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, &imu);





/*
 * ╭─────╮
 * │ PID │
 * ╰─────╯
 */

ControllerSettings linearController(
    10,     // kP
    0,      // kI
    3,      // kD
    3,      // anti windup
    1,      // small error range, in inches
    100,    // small error range timeout, in milliseconds
    3,      // large error range, in inches
    500,    // large error range timeout, in milliseconds
    20      // maximum acceleration (slew)
);

ControllerSettings angularController(
    3.5,      //kP
    0,      // kI
    17,     // kD
    3,      // anti windup
    1,      // small error range, in degrees
    100,    // small error range timeout, in milliseconds
    3,      // large error range, in degrees
    500,    // large error range timeout, in milliseconds
    0       // maximum acceleration (slew)
);






/*
 * ╭─────────╮
 * │ CHASSIS │
 * ╰─────────╯
 */

Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);





/*
 * ╭─────────╮
 * │ METHODS │
 * ╰─────────╯
 */

std::string find_disconnected_ports() {

    std::string disconnectedPorts = "";

    if (!imu.is_installed()) {
        disconnectedPorts += "IMU " + to_string(IMU_PORT);
        disconnectedPorts += "; ";
    }

    if (!distanceSensor.is_installed()) {
        disconnectedPorts += "Distance " + to_string(DISTANCE_PORT);
        disconnectedPorts += "; ";
    }

    if (!opticalSensor.is_installed()) {
        disconnectedPorts += "Optical " + to_string(OPTICAL_PORT);
        disconnectedPorts += "; ";
    }

    if (!Motor(STAGE_1_INTAKE).is_installed()) {
        disconnectedPorts += "Stage 1 Intake " + to_string(STAGE_1_INTAKE);
        disconnectedPorts += "; ";
    }
    
    if (!Motor(STAGE_2_INTAKE).is_installed()) {
        disconnectedPorts += "Right Intake " + to_string(STAGE_2_INTAKE);
        disconnectedPorts += "; ";
    }

    if (!Motor(LEFT_DT_A_PORT).is_installed()) {
        disconnectedPorts += "DT Left A " + to_string(LEFT_DT_A_PORT);
        disconnectedPorts += "; ";
    }

    if (!Motor(LEFT_DT_B_PORT).is_installed()) {
        disconnectedPorts += "DT Left B " + to_string(LEFT_DT_B_PORT);
        disconnectedPorts += "; ";
    }

    if (!Motor(LEFT_DT_C_PORT).is_installed()) {
        disconnectedPorts += "DT Left C " + to_string(LEFT_DT_C_PORT);
        disconnectedPorts += "; ";
    }

    if (!Motor(RIGHT_DT_A_PORT).is_installed()) {
        disconnectedPorts += "DT Right A " + to_string(RIGHT_DT_A_PORT);
        disconnectedPorts += "; ";
    }

    if (!Motor(RIGHT_DT_B_PORT).is_installed()) {
        disconnectedPorts += "DT Right B " + to_string(RIGHT_DT_B_PORT);
        disconnectedPorts += "; ";
    }

    if (!Motor(RIGHT_DT_C_PORT).is_installed()) {
        disconnectedPorts += "DT Right C " + to_string(RIGHT_DT_C_PORT);
        disconnectedPorts += "; ";
    }

    return disconnectedPorts;

}