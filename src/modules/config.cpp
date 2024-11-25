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

#define IMU_PORT 1
#define INTAKE_PORT 10
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

using namespace pros;
using namespace lemlib;
using namespace std;





/*
 * ╭────────────╮
 * │ CONTROLLER │
 * ╰────────────╯
 */

ExpoDriveCurve throttleCurve(3, 10, 1.019); // Fields: deadband, min, expo
ExpoDriveCurve steerCurve(3, 10, 1.019); // Fields: deadband, min, expo

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





/*
 * ╭────────╮
 * │ INTAKE │
 * ╰────────╯
 */

Motor intake(INTAKE_PORT);





/*
 * ╭──────╮
 * │ ADIs │
 * ╰──────╯
 */

extern pros::ADIMotor ledRed(1);
extern pros::ADIMotor ledGreen(2);
extern pros::ADIMotor ledBlue(3);

adi::DigitalOut mogo('D', false);
adi::DigitalOut doinker('E', false);





/*
 * ╭─────╮
 * │ IMU │
 * ╰─────╯
 */

Imu imu(IMU_PORT);





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

Rotation horizontalEnc(1);
Rotation verticalEnc(-2);
TrackingWheel horizontal(&horizontalEnc, Omniwheel::NEW_275, -5.75);
TrackingWheel vertical(&verticalEnc, Omniwheel::NEW_275, -2.5);

OdomSensors sensors(&vertical, nullptr, &horizontal, nullptr, &imu);





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
    2,      //kP
    0,      // kI
    10,     // kD
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

string find_disconnected_ports(){

    string disconnectedPorts = "";



    if (intake.get_port() != INTAKE_PORT) {
        disconnectedPorts += "Intake Motor: port " + INTAKE_PORT;
        disconnectedPorts += "\n";
    }

    if (leftMotors.get_port(0) != LEFT_DT_A_PORT) {
        disconnectedPorts += "DT Left Motor A: port " + LEFT_DT_A_PORT;
        disconnectedPorts += "\n";
    }

    if (leftMotors.get_port(1) != LEFT_DT_B_PORT) {
        disconnectedPorts += "DT Left Motor B: port " + LEFT_DT_B_PORT;
        disconnectedPorts += "\n";
    }

    if (leftMotors.get_port(2) != LEFT_DT_C_PORT) {
        disconnectedPorts += "DT Left Motor C: port " + LEFT_DT_C_PORT;
        disconnectedPorts += "\n";
    }

    if (rightMotors.get_port(0) != RIGHT_DT_A_PORT) {
        disconnectedPorts += "DT Right Motor A: port " + RIGHT_DT_A_PORT;
        disconnectedPorts += "\n";
    }

    if (rightMotors.get_port(1) != RIGHT_DT_B_PORT) {
        disconnectedPorts += "DT Right Motor B: port " + RIGHT_DT_B_PORT;
        disconnectedPorts += "\n";
    }

    if (rightMotors.get_port(2) != RIGHT_DT_C_PORT) {
        disconnectedPorts += "DT Right Motor C: port " + RIGHT_DT_C_PORT;
        disconnectedPorts += "\n";
    }



    if(disconnectedPorts.size() == 0){
        disconnectedPorts = nullptr;
    }

    return disconnectedPorts;

}