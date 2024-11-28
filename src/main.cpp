/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "main.h"





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace pros;
using namespace lemlib;





/*
 * ╭────────────╮
 * │ INITIALIZE │
 * ╰────────────╯
 */

void initialize() {

    // init_bui();
    chassis.calibrate();


}





/*
 * ╭───────────╮
 * │ COMP INIT │
 * ╰───────────╯
 */

void competition_initialize() {}





/*
 * ╭────────────╮
 * │ AUTONOMOUS │
 * ╰────────────╯
 */

void autonomous() {

    getSelectedRoutine().run();
    
}





/*
 * ╭────────────────╮
 * │ DRIVER CONTROL │
 * ╰────────────────╯
 */

void opcontrol() {

    while (true) {

        drivetrain_control();
        intake_control();
        mogo_control();

        // if(controller.get_digital(E_CONTROLLER_DIGITAL_A)){
        //     LED::red();
        //     controller.rumble(".");
        // }
        // if(controller.get_digital(E_CONTROLLER_DIGITAL_B)){
        //     LED::blue();
        //     controller.rumble("..");
        // }
        // if(controller.get_digital(E_CONTROLLER_DIGITAL_X)){
        //     LED::blue();
        //     controller.rumble("...");
        // }
        // if(controller.get_digital(E_CONTROLLER_DIGITAL_B)){
        //     LED::blue();
        //     controller.rumble("..");
        // }
        // if(controller.get_digital(E_CONTROLLER_DIGITAL_UP)){
        //     LED::off();
        //     controller.rumble("-");
        // }
        // if(controller.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
        //     LED::rainbow();
        //     controller.rumble("--");
        // }

        delay(10);

    }

}





/*
 * ╭──────────╮
 * │ DISABLED │
 * ╰──────────╯
 */

void disabled() {}