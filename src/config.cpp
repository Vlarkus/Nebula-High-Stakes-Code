/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "config.hpp"





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace pros;
using namespace lemlib;





/*
 * ╭───────╮
 * │ SETUP │
 * ╰───────╯
 */

// -=- CONTROLLER -=-

Controller controller(E_CONTROLLER_MASTER);



// -=- BUTTONS -=-

const controller_digital_e_t INTAKE_IN = E_CONTROLLER_DIGITAL_R1;
const controller_digital_e_t INTAKE_OUT = E_CONTROLLER_DIGITAL_L1;
const controller_digital_e_t MOGO_IN = E_CONTROLLER_DIGITAL_L2;
const controller_digital_e_t MOGO_OUT = E_CONTROLLER_DIGITAL_R2;




// -=- MOTORS -=-

Motor intake(10);



// -=- ADI -=-

extern pros::ADIMotor ledRed(1);
extern pros::ADIMotor ledGreen(2);
extern pros::ADIMotor ledBlue(3);

adi::DigitalOut mogo('D', false);
adi::DigitalOut doinker('E', false);



// -=- INERTIAL SENSOR -=-

Imu imu(10);



// -=- DRIVETRAIN -=-

auto omniwheels = Omniwheel::NEW_325;
float trackWidth = 13;
float rpm = 360;
float horizontalDrift = 360;

MotorGroup leftMotors({-16, -17, -19}, MotorGearset::blue);
MotorGroup rightMotors({11, 12, 13}, MotorGearset::blue);

Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              trackWidth, // inch track width
                              omniwheels, // omniwheels
                              rpm, // rpm
                              horizontalDrift // horizontal drift
);



// -=- TRACKING WHEELS -=-

Rotation horizontalEnc(1);
Rotation verticalEnc(-2);
TrackingWheel horizontal(&horizontalEnc, Omniwheel::NEW_275, -5.75);
TrackingWheel vertical(&verticalEnc, Omniwheel::NEW_275, -2.5);



// -=- ODOMETRY -=-

OdomSensors sensors(nullptr, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral motion controller
ControllerSettings linearController(10, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            3, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);



// input curve for throttle input during driver control

ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control

ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);



// -=- CHASSIS -=-

Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);
