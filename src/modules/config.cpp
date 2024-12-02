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

#define IMU_PORT 2
#define OPTICAL_PORT 9

#define INTAKE_MOTOR_PORT 10
#define LADYBROWN_MOTOR_PORT 1

#define ROTATION_ODOM_HOR_PORT 15
#define LADYBROWN_ROTATION_PORT 5

#define MOGO_ADI_PORT 'A'
#define DOINKER_ADI_PORT 'B'
#define SELECTIVE_INTAKE_ADI_PORT 'C'

#define LED_RED_ADI_PORT 'E'
#define LED_BLUE_ADI_PORT 'F'
#define LED_GREEN_ADI_PORT 'G'
#define LED_BRIGHT_ADI_PORT 'H'

#define LEFT_DT_A_PORT 16
#define LEFT_DT_B_PORT 17
#define LEFT_DT_C_PORT 19
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

const controller_digital_e_t INTAKE_IN = E_CONTROLLER_DIGITAL_R1;
const controller_digital_e_t INTAKE_OUT = E_CONTROLLER_DIGITAL_L1;
const controller_digital_e_t MOGO_IN = E_CONTROLLER_DIGITAL_L2;
const controller_digital_e_t MOGO_OUT = E_CONTROLLER_DIGITAL_R2;
const controller_digital_e_t TURN_180 = E_CONTROLLER_DIGITAL_DOWN;
const pros::controller_digital_e_t LADYBROWN_REST = E_CONTROLLER_DIGITAL_Y;
const pros::controller_digital_e_t LADYBROWN_INTAKE = E_CONTROLLER_DIGITAL_B;
const pros::controller_digital_e_t LADYBROWN_EXTEND = E_CONTROLLER_DIGITAL_X;





/*
 * ╭────────╮
 * │ INTAKE │
 * ╰────────╯
 */

Motor intake(INTAKE_MOTOR_PORT);





/*
 * ╭──────╮
 * │ ADIs │
 * ╰──────╯
 */

adi::DigitalOut mogo(MOGO_ADI_PORT, false);
adi::DigitalOut doinker(DOINKER_ADI_PORT, false);
adi::DigitalOut selectiveIntake(SELECTIVE_INTAKE_ADI_PORT, false);

pros::adi::AnalogOut ledRed(LED_RED_ADI_PORT);
pros::adi::AnalogOut ledGreen(LED_GREEN_ADI_PORT);
pros::adi::AnalogOut ledBlue(LED_BLUE_ADI_PORT);
pros::adi::AnalogOut ledBrightness(LED_BRIGHT_ADI_PORT);





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

Rotation ladybrown_rotation(LADYBROWN_ROTATION_PORT);
Motor ladybrown(-LADYBROWN_MOTOR_PORT);





/*
 * ╭─────────╮
 * │ OPTICAL │
 * ╰─────────╯
 */

Optical optical(OPTICAL_PORT);





/*
 * ╭────────────╮
 * │ DRIVETRAIN │
 * ╰────────────╯
 */

auto omniwheels = Omniwheel::NEW_325;
float trackWidth = 13;
float rpm = 360;
float horizontalDrift = 360;

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

Rotation horizontalEnc(ROTATION_ODOM_HOR_PORT);
TrackingWheel horizontal(&horizontalEnc, Omniwheel::NEW_2, 2.65);

OdomSensors sensors(nullptr, nullptr, &horizontal, nullptr, &imu);





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
    0.075,      // kI
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

    if (!ladybrown_rotation.is_installed()) {
        disconnectedPorts += "Rotation (Ladybrown) " + to_string(LADYBROWN_ROTATION_PORT);
        disconnectedPorts += "; ";
    }

    if (!Motor(LADYBROWN_MOTOR_PORT).is_installed()) {
        disconnectedPorts += "Ladybrown " + to_string(LADYBROWN_MOTOR_PORT);
        disconnectedPorts += "; ";
    }

    if (!horizontalEnc.is_installed()) {
        disconnectedPorts += "Rotation (Odometry Horizontal) " + to_string(ROTATION_ODOM_HOR_PORT);
        disconnectedPorts += "; ";
    }

    if (!optical.is_installed()) {
        disconnectedPorts += "Optical " + to_string(OPTICAL_PORT);
        disconnectedPorts += "; ";
    }

    if (!intake.is_installed()) {
        disconnectedPorts += "Intake " + to_string(INTAKE_MOTOR_PORT);
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