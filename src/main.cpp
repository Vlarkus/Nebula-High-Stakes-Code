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
    ladybrown_rotation.reset_position();
    ladybrown.set_brake_mode(E_MOTOR_BRAKE_HOLD);

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
    LED::rainbow();
    
}





/*
 * ╭────────────────╮
 * │ DRIVER CONTROL │
 * ╰────────────────╯
 */

void opcontrol() {

    int8_t led_mode = 0; 

    while (true) {

        drivetrain_control();
        intake_control();
        mogo_control();
        // ladybrown_control(); // NOT WORKING YET
        turn_180_control();

        if(controller.get_digital(E_CONTROLLER_DIGITAL_X)){
            led_mode = 1;
        } else if(controller.get_digital(E_CONTROLLER_DIGITAL_Y)){
            led_mode = 2;
        } else if(controller.get_digital(E_CONTROLLER_DIGITAL_B)){
            led_mode = 0;
        }

        switch (led_mode)
        {
        case 0:
            LED::off();
            break;

        case 1:
            show_ring_color_with_led();
            break;

        case 2:
            LED::rainbow();
            break;
        
        default:
            LED::off();
            break;
        }

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