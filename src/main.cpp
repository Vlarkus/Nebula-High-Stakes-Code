/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "main.h"
#include "config.hpp"
#include "systems.hpp"
#include "autons.hpp"




/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace pros;
using namespace lemlib;





/*
 * ╭─────────╮
 * │ METHODS │
 * ╰─────────╯
 */

// -=-=- INIT -=-=-

void initialize() {
    lcd::initialize();
    chassis.calibrate();

    // thread to for brain screen and position logging
    Task screenTask([&]() {
        while (true) {

            lcd::print(0, "X: %f", chassis.getPose().x);
            lcd::print(1, "Y: %f", chassis.getPose().y);
            lcd::print(2, "Theta: %f", chassis.getPose().theta);

            delay(50);
        }
    });
}





// -=-=- COMP INIT -=-=-

void competition_initialize() {}





// -=-=- AUTONOMOUS -=-=-

void autonomous() {
    
}





// -=-=- DRIVER CONTROL -=-=-

void opcontrol() {

    while (true) {


        // -=- DRIVE TRAIN -=-

        int leftY = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.arcade(leftY, rightX);


        // -=- SYSTEMS -=-

        intake_control();
        mogo_control();


        // -=- DELAY -=-

        delay(10);


    }

}





// -=-=- DISABLED -=-=-

void disabled() {}