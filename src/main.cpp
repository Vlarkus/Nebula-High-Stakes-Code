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
    BUI::set_screen(BUI::AUTON_SELECTOR);
    LED::off();
    run_connectivity_check();
    chassis.calibrate();
    optical.set_led_pwm(100);
    controller.rumble("-.");


}





/*
 * ╭───────────╮
 * │ COMP INIT │
 * ╰───────────╯
 */

void competition_initialize() {

    controller.rumble(".-");
    BUI::set_screen(BUI::COLOR_SELECTOR);

}





/*
 * ╭────────────╮
 * │ AUTONOMOUS │
 * ╰────────────╯
 */

void autonomous() {

    getSelectedRoutine().run();
    // BUI::set_screen(BUI::SCREEN::LOGO_ONLY);
    LED::rainbow();
    
}





/*
 * ╭────────────────╮
 * │ DRIVER CONTROL │
 * ╰────────────────╯
 */

void opcontrol() { 

    BUI::set_screen(BUI::SCREEN::LOGO_ONLY);

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

void disabled() {

    controller.rumble("-.");
    BUI::set_screen(BUI::SCREEN::AUTON_SELECTOR);

}