/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "modules/actions.hpp"





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

namespace {
    bool isSelectiveIntakeOn = false;
}





/*
 * ╭────────────────────╮
 * │ DRIVETRAIN CONTROL │
 * ╰────────────────────╯
 */

void drivetrain_control(){

    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    chassis.arcade(leftY, rightX);

}





/*
 * ╭────────────────╮
 * │ INTAKE CONTROL │
 * ╰────────────────╯
 */

void intake_control(){
    if(controller.get_digital(INTAKE_IN)){
        intake.move_voltage(12000);
    } else if(controller.get_digital(INTAKE_OUT)){
        intake.move_voltage(-12000);
    } else {
        intake.move_voltage(0);
    }
}





/*
 * ╭──────────────╮
 * │ MOGO CONTROL │
 * ╰──────────────╯
 */

void mogo_control(){
    if(controller.get_digital(MOGO_IN)){
        mogo.set_value(true);
    } else if(controller.get_digital(MOGO_OUT)){
        mogo.set_value(false);
    }
}