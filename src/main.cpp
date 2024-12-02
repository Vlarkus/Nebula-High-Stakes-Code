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

    init_bui();
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

    getRoutine(0).run();
    
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
        turn_180_control();
        screen::print(E_TEXT_MEDIUM, 6, "R: %f", optical.get_rgb().red);
        screen::print(E_TEXT_MEDIUM, 7, "G: %f", optical.get_rgb().green);
        screen::print(E_TEXT_MEDIUM, 8, "B: %f", optical.get_rgb().blue);
        screen::print(E_TEXT_MEDIUM, 9, "P: %f", optical.get_proximity());

        show_ring_color_with_led();
        // LED::rainbow();

        delay(10);


    }

}





/*
 * ╭──────────╮
 * │ DISABLED │
 * ╰──────────╯
 */

void disabled() {

}