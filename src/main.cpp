/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "main.h"
#include "lemlib/api.hpp"





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace pros;
using namespace lemlib;





/* TODO: THIS SECTION WILL ENTIERLY GO TO CONFIG.CPP
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

// INTAKE
Motor intake(10);



// -=- SOLONOIDS -=-
ADIDigitalOut mogo('A', false);
ADIDigitalOut doinker('B', false);



// -=- INERTIAL SENSOR -=-
Imu imu(10);



// -=- DRIVETRAIN -=-
MotorGroup leftMotors({-16, -17, -19}, MotorGearset::blue);
MotorGroup rightMotors({11, 12, 13}, MotorGearset::blue);
Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              13, // inch track width
                              Omniwheel::NEW_325, // omniwheels
                              360, // rpm
                              1 // horizontal drift
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







/*
 * ╭─────────╮
 * │ METHODS │
 * ╰─────────╯
 */

// -=-=- INITIALIZE -=-=-
void initialize() {
    lcd::initialize();
    chassis.calibrate();

    // thread to for brain screen and position logging
    Task screenTask([&]() {
        while (true) {

            lcd::print(0, "X: %f", chassis.getPose().x);
            lcd::print(1, "Y: %f", chassis.getPose().y);
            lcd::print(2, "Theta: %f", chassis.getPose().theta);

            telemetrySink()->info("Chassis pose: {}", chassis.getPose());

            delay(50);
        }
    });
}





// -=-=- COMP INIT -=-=-
void competition_initialize() {}





// -=-=- AUTONOMOUS -=-=-

// -=- Paths -=-
ASSET(example_txt); // '.' replaced with "_"

// -=- Auton -=-
void autonomous() {
    
}





// -=-=- DRIVER CONTROL -=-=-

// -=- SYSTEMS -=-

void intake_control(){
    if(controller.get_digital(INTAKE_IN)){
        intake.move_voltage(12000);
    } else if(controller.get_digital(INTAKE_OUT)){
        intake.move_voltage(-12000);
    } else {
        intake.move_voltage(0);
    }
}

void mogo_control(){
    if(controller.get_digital(MOGO_IN)){
        mogo.set_value(true);
    } else if(controller.get_digital(MOGO_OUT)){
        mogo.set_value(false);
    }
}



// -=- OP CONTROL -=-
void opcontrol() {

    while (true) {

        // -=-=- DT -=-=- 
        int leftY = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.arcade(leftY, rightX);

        intake_control();
        mogo_control();
        
        delay(10);
    
    }
}





// -=-=- DISABLED -=-=-
void disabled() {}