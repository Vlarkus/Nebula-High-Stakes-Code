/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "main.h"
#include "lemlib/api.hpp"





/*
 * ╭───────╮
 * │ SETUP │
 * ╰───────╯
 */

// -=- CONTROLLER -=-
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// -=- BUTTONS -=-
// const pros::controller_digital_e_t INTAKE_IN = pros::E_CONTROLLER_DIGITAL_L1;
// const pros::controller_digital_e_t INTAKE_OUT = pros::E_CONTROLLER_DIGITAL_R1;

// -=- MOTORS -=-
pros::Motor intake(20);

// -=- INERTIAL SENSOR -=-
pros::Imu imu(10);

// -=- DRIVETRAIN -=-
pros::MotorGroup leftMotors({-17, -19, -20}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({11, 12, 13}, pros::MotorGearset::blue);
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              13, // inch track width
                              lemlib::Omniwheel::NEW_325, // omniwheels
                              360, // rpm
                              1 // horizontal drift
);

// -=- TRACKING WHEELS -=-
pros::Rotation horizontalEnc(1);
pros::Rotation verticalEnc(-2);
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75);
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);

// -=- ODOMETRY -=-
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral motion controller
lemlib::ControllerSettings linearController(10, // proportional gain (kP)
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
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
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
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// -=- CHASSIS -=-
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);







/*
 * ╭─────────╮
 * │ METHODS │
 * ╰─────────╯
 */

// -=-=- INITIALIZE -=-=-
void initialize() {
    pros::lcd::initialize();
    chassis.calibrate();

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        while (true) {

            pros::lcd::print(0, "X: %f", chassis.getPose().x);
            pros::lcd::print(1, "Y: %f", chassis.getPose().y);
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);

            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());

            pros::delay(50);
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
void opcontrol() {

    while (true) {

        // -=-=- Joysticks -=-=- 
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.arcade(leftY, rightX);



        // -=-=- Buttons -=-=-

        if(controller.get_digital(DIGITAL_A)){
            intake.move_voltage(12000);
        } else if(controller.get_digital(DIGITAL_UP)){
            intake.move_voltage(-12000);
        } else {
            intake.move_voltage(0);
        }

        pros::delay(10);
    }
}

// -=-=- DISABLED -=-=-
void disabled() {}