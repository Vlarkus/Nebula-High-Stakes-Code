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
    LADYBROWN::initialize();
    led.initialize();
    run_connectivity_check();
    chassis.calibrate();
    opticalSensor.set_led_pwm(100);
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
    BUI::set_screen(BUI::SCREEN::LOGO_ONLY);
    
}





/*
 * ╭────────────────╮
 * │ DRIVER CONTROL │
 * ╰────────────────╯
 */

void opcontrol() { 

    BUI::set_screen(BUI::SCREEN::LOGO_ONLY);
    led.flow(0xFF00FF, 0x7722BB, 1);
    
    while (true) {

        DRIVETRAIN::control();
        DOINKER::control();
        LADYBROWN::control();   
        INTAKE::control();
        COLORSORT::control();
        MOGO::control();

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
    led.off();

}