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

    BUI::initialize();
    run_connectivity_check();
    chassis.calibrate();
    optical.set_led_pwm(100);

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

    BUI::getSelectedRoutine().run();
    BUI::set_screen(BUI::SCREEN::DURING_MATCH);
    LED::rainbow();
    
}





/*
 * ╭────────────────╮
 * │ DRIVER CONTROL │
 * ╰────────────────╯
 */

void opcontrol() { 

    BUI::set_screen(BUI::SCREEN::DURING_MATCH);
    controller.print(0, 0, "%s", BUI::getSelectedRoutine().getName());

    while (true) {

        drivetrain_control();
        intake_control();
        selective_intake_control();
        mogo_control();
        turn_180_control();

        delay(10);

    }

}





/*
 * ╭──────────╮
 * │ DISABLED │
 * ╰──────────╯
 */

void disabled() {}