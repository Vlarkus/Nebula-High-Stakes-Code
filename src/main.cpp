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
    ladybrownRotation.reset_position();
    ladybrownMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

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
    LED::off();

    while (true) {

        drivetrain_control();
        intake_control();
        selective_intake_control();
        mogo_control();
        ladybrown_control();
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