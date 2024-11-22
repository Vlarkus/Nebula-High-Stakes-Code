#include "systems.hpp"

void intake_control(){
    if(controller.get_digital(INTAKE_IN)){
        intake.move_voltage(12000);
    } else if(controller.get_digital(INTAKE_OUT)){
        intake.move_voltage(-12000);
    } else {
        intake.move_voltage(0);
    }
}

void mogo_control(){
    if(controller.get_digital(MOGO_IN)){
        mogo.set_value(true);
    } else if(controller.get_digital(MOGO_OUT)){
        mogo.set_value(false);
    }
}