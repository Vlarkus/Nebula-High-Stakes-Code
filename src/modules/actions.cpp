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





/*
 * ╭───────────╮
 * │ LADYBROWN │
 * ╰───────────╯
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

    if(controller.get_digital(LADYBROWN_EXTEND)){
        ladybrown_extend();
    } else if(controller.get_digital(LADYBROWN_REST)){
        ladybrown_to_rest();
    } else if(controller.get_digital(LADYBROWN_INTAKE)){
        ladybrown_to_intake();
    }

}





/*
 * ╭──────────╮
 * │ TURN 180 │
 * ╰──────────╯
 */

void turn_180_control(){
    if(controller.get_digital(TURN_180)){
        chassis.turnToHeading(chassis.getPose(false, false).theta + 180, 500);
    }
}





/*
 * ╭──────────────────╮
 * │ SELECTIVE INTAKE │
 * ╰──────────────────╯
 */

void selective_intake(){

    auto rgb = optical.get_rgb();
    if(rgb.red > 6){
        LED::red();
    } else if(rgb.blue > 6){
        LED::blue();
    } else {
        LED::white();
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