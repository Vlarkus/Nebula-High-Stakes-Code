/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "modules/controls.hpp"





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
    if(controller.get_digital(INTAKE_IN_BTN)){
        intake.move_voltage(12000);
    } else if(controller.get_digital(INTAKE_OUT_BTN)){
        intake.move_voltage(-12000);
    } else {
        intake.move_voltage(0);
    }
}





/*
 * ╭────────────────╮
 * │ OPTICAL SENSOR │
 * ╰────────────────╯
 */

enum RING_COLOR{

    NONE = 0,
    RED,
    BLUE

};

int8_t getRingColor(){

    auto rgb = optical.get_rgb();
    
    if(400 < rgb.blue){
        return RING_COLOR::BLUE;
    } else if (500 < rgb.red) {
        return RING_COLOR::RED;
    } else {
        return RING_COLOR::NONE;
    }

}





/*
 * ╭──────────────────────────╮
 * │ SELECTIVE INTAKE CONTROL │
 * ╰──────────────────────────╯
 */

namespace SELECTIVE_INTAKE{

    bool isActive = true;
    bool isEliminateRed = true;
    bool wasTogglePressed = false;
    bool isPistonExtended = false;

};

void selective_intake_control(){

    if(!controller.get_digital(SELECTIVE_INTAKE_TOGGLE_ACTIVE_BTN)){
        SELECTIVE_INTAKE::wasTogglePressed = false;
    } else if(!SELECTIVE_INTAKE::wasTogglePressed){
        
        SELECTIVE_INTAKE::wasTogglePressed = true;

        if(is_ctrl_pressed()){
            SELECTIVE_INTAKE::isEliminateRed = !SELECTIVE_INTAKE::isEliminateRed;
        } else {
            SELECTIVE_INTAKE::isActive = !SELECTIVE_INTAKE::isActive;
        }
    }



    if(SELECTIVE_INTAKE::isActive){

        int8_t ringColor = getRingColor();

        if(SELECTIVE_INTAKE::isEliminateRed){

            LED::blue();
            SELECTIVE_INTAKE::isPistonExtended = (ringColor == RING_COLOR::RED && ringColor != RING_COLOR::NONE);

        } else {

            LED::red();
            SELECTIVE_INTAKE::isPistonExtended = (ringColor == RING_COLOR::BLUE && ringColor != RING_COLOR::NONE);

        }

    } else {
        LED::purple();
        SELECTIVE_INTAKE::isPistonExtended = false;
    }



    selectiveIntake.set_value(SELECTIVE_INTAKE::isPistonExtended);

}





/*
 * ╭──────────────╮
 * │ MOGO CONTROL │
 * ╰──────────────╯
 */

void mogo_control(){
    if(controller.get_digital(MOGO_IN_BTN)){
        mogo.set_value(true);
    } else if(controller.get_digital(MOGO_OUT_BTN)){
        mogo.set_value(false);
    }
}





/*
 * ╭───────────────────╮
 * │ LADYBROWN CONTROL │
 * ╰───────────────────╯
 */

pros::Task* ladybrown_current_task = nullptr;
int32_t ladybrown_current_target = 0;

int32_t getTarget(){
    return ladybrown_current_target;
}

// The PID control task
void motor_control_task(void* param) {
    const double kP = 0.5;
    const double kI = 0.0;
    const double kD = 0.1;
    const double tolerance = 2.0; // degrees

    double error, prev_error = 0, integral = 0, derivative = 0;

    while (true) {

        pros::Task::delay(20);

        error = ladybrown_current_target - (ladybrown_rotation.get_angle()/100);

        if (std::abs(error) <= tolerance) {
            ladybrown.brake();
            pros::Task::delay(20);
            continue;
        }

        integral += error;
        derivative = error - prev_error;
        double power = kP * error + kI * integral + kD * derivative;

        ladybrown.move(power);
        prev_error = error;

    }
}

void start_motor_control_task() {
    if (ladybrown_current_task == nullptr) {
        ladybrown_current_task = new pros::Task(motor_control_task, nullptr, "MotorControl");
    }
}

void stop_motor_control_task() {
    if (ladybrown_current_task != nullptr) {
        ladybrown_current_task->remove();
        delete ladybrown_current_task;
        ladybrown_current_task = nullptr;
    }
}

void ladybrown_to_rest() {
    ladybrown_current_target = 157;
    start_motor_control_task();
}

void ladybrown_to_intake() {
    ladybrown_current_target = 147;
    start_motor_control_task();
}

void ladybrown_extend() {
    ladybrown_current_target = 254;
    start_motor_control_task();
}


void ladybrown_control(){

    // CODE NOT WORKING DUE TO ROTATION SENSOR WRONG MEASUREMENTS

    // if(controller.get_digital(LADYBROWN_EXTEND_BTN)){
    //     ladybrown_extend();
    // } else if(controller.get_digital(LADYBROWN_REST_BTN)){
    //     ladybrown_to_rest();
    // } else if(controller.get_digital(LADYBROWN_INTAKE_BTN)){
    //     ladybrown_to_intake();
    // }

}





/*
 * ╭────────────────╮
 * │ RING COLOR LED │
 * ╰────────────────╯
 */

bool is_ctrl_pressed(){

    return controller.get_digital(CTRL_BTN);

}





/*
 * ╭──────────────────╮
 * │ TURN 180 CONTROL │
 * ╰──────────────────╯
 */

void turn_180_control(){
    if(controller.get_digital(TURN_180_BTN)){
        chassis.turnToHeading(chassis.getPose(false, false).theta + 180, 500);
    }
}





/*
 * ╭────────────────╮
 * │ RING COLOR LED │
 * ╰────────────────╯
 */

void show_ring_color_with_led(){
    
    auto rgb = optical.get_rgb();
    
    if(400 < rgb.blue){
        LED::blue();
    } else if (500 < rgb.red) {
        LED::red();
    } else {
        LED::white();
    }

}