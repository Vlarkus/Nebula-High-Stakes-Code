/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "modules/controls.hpp"





/*
 * ╭────────╮
 * │ DEFINE │
 * ╰────────╯
 */

#define MOTOR_MAX_VOLTAGE 12000





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace pros;
using namespace std;





/*
 * ╭────────────────────╮
 * │ DRIVETRAIN CONTROL │
 * ╰────────────────────╯
 */

void run_connectivity_check(){

    string discPorts = find_disconnected_ports();

    if(!discPorts.empty()){

        screen::set_pen(Color::white);
        screen::print(E_TEXT_MEDIUM, 7, discPorts.c_str());

        for(int8_t i = 0; i <= 2; i++){

            controller.rumble("-");

            LED::red();
            delay(250);
            LED::white();
            delay(250);

        }

    } else {

        LED::green();
    
    }

}





/*
 * ╭────────────────────╮
 * │ DRIVETRAIN CONTROL │
 * ╰────────────────────╯
 */

namespace DRIVETRAIN {

    void control(){

        int leftY = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.arcade(leftY, rightX);

    }

    void turn_180_control(){
        if(controller.get_digital(TURN_180_BTN)){
            chassis.turnToHeading(chassis.getPose(false, false).theta + 180, 500);
        }
    }

}





/*
 * ╭────────╮
 * │ INTAKE │
 * ╰────────╯
 */

namespace INTAKE {

void control(){

        if(controller.get_digital(INTAKE_IN_BTN)){
            in();
        } else if(controller.get_digital(INTAKE_OUT_BTN)){
            out();
        } else {
            stop();
        }
        
    }

    void in(){
        intake.move_voltage(MOTOR_MAX_VOLTAGE);
    }

    void out(){
        intake.move_voltage(-MOTOR_MAX_VOLTAGE);
    }

    void stop(){
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

#define RED_COLOR_THRESHOLD 900
#define BLUE_COLOR_THRESHOLD 800

int8_t getRingColor(){

    auto rgb = opticalSensor.get_rgb();
    
    if(BLUE_COLOR_THRESHOLD < rgb.blue){
        return RING_COLOR::BLUE;
    } else if (RED_COLOR_THRESHOLD < rgb.red) {
        return RING_COLOR::RED;
    } else {
        return RING_COLOR::NONE;
    }

}





/*
 * ╭───────────╮
 * │ COLORSORT │
 * ╰───────────╯
 */

namespace COLORSORT{

    bool isActive = true;
    bool isEliminateRed = true;
    bool wasTogglePressed = false;
    bool isPistonExtended = false;

    pros::Task* control_task = nullptr;

    void control(){

        if(!controller.get_digital(SELECTIVE_INTAKE_TOGGLE_ACTIVE_BTN)){
            COLORSORT::wasTogglePressed = false;
        } else if(!COLORSORT::wasTogglePressed){
            
            COLORSORT::wasTogglePressed = true;

            if(is_ctrl_pressed()){
                COLORSORT::isEliminateRed = !COLORSORT::isEliminateRed;
            } else {
                COLORSORT::isActive = !COLORSORT::isActive;
            }
        }



        if(COLORSORT::isActive){

            int8_t ringColor = getRingColor();

            if(COLORSORT::isEliminateRed){

                LED::blue();

                if(ringColor == RING_COLOR::RED){
                    COLORSORT::isPistonExtended = true;
                } else if(ringColor == RING_COLOR::BLUE) {
                    COLORSORT::isPistonExtended = false;
                }

            } else {

                LED::red();

                if(ringColor == RING_COLOR::BLUE){
                    COLORSORT::isPistonExtended = true;
                } else if(ringColor == RING_COLOR::RED) {
                    COLORSORT::isPistonExtended = false;
                }

            }

        } else {

            LED::purple();
            COLORSORT::isPistonExtended = false;

        }



        colorsortPiston.set_value(COLORSORT::isPistonExtended);

    }

    void task_function(void*) {
        control();
    }

    void run_async() {

        if (control_task == nullptr) {
            control_task = new pros::Task(task_function, nullptr, "Control Task");
        }

    }

    void stop_async() {
        if (control_task != nullptr) {
            control_task->remove();
            delete control_task;
            control_task = nullptr;
        }
    }

    void set_is_eliminate_red(bool b){
        COLORSORT::isEliminateRed = b;
    }

};





/*
 * ╭──────╮
 * │ MOGO │
 * ╰──────╯
 */

namespace MOGO {

#define DISTANCE_SENSOR_MOGO_THRESHOLD 65

    void control(){

        if(controller.get_digital(MOGO_IN_BTN)){

            screen::print(E_TEXT_MEDIUM_CENTER, 0, "Dist: %d", distanceSensor.get_distance());

            if(is_ctrl_pressed()){
                close();
                controller.rumble("..");
            } else {
                close_if_mogo_detected();
            }

        } else if(controller.get_digital(MOGO_OUT_BTN)){
            open();
            controller.rumble(".");
        }

    }

    bool is_mogo_detected(){
        return distanceSensor.get_distance() < DISTANCE_SENSOR_MOGO_THRESHOLD;
    }

    void close_if_mogo_detected(){

        if(is_mogo_detected()){
            close();
            controller.rumble("--");
        }

    }

    void close(){
        mogoPiston.set_value(true);
    }

    void open(){
        mogoPiston.set_value(false);
    }

}





/*
 * ╭───────────────────╮
 * │ LADYBROWN CONTROL │
 * ╰───────────────────╯
 */

namespace LADYBROWN{

    enum {
        RETRACTED = 0,
        INTAKE = 1,
        EXTENDED = 2
    };

    int8_t state = RETRACTED;

    void control(){

        // if(controller.get_digital(LADYBROWN_EXTEND_BTN)){
        //     LADYBROWN::state = LADYBROWN::EXTENDED;
        // } else if(controller.get_digital(LADYBROWN_RETRACT_BTN)){
        //     LADYBROWN::state = LADYBROWN::RETRACTED;
        // } else if(controller.get_digital(LADYBROWN_INTAKE_BTN)){
        //     LADYBROWN::state = LADYBROWN::INTAKE;
        // } else {
        //     ladybrownMotor.move_voltage(0);
        //     return;
        // }

        // switch (LADYBROWN::state){

        // case LADYBROWN::RETRACTED:

        //     ladybrownPiston.set_value(true);
        //     ladybrownMotor.move_voltage(-MOTOR_MAX_VOLTAGE);
            
        //     break;
        
        // case LADYBROWN::INTAKE:

        //     ladybrownPiston.set_value(false);
        //     ladybrownMotor.move_voltage(-MOTOR_MAX_VOLTAGE);

        //     break;

        // case LADYBROWN::EXTENDED:

        //     ladybrownMotor.move_voltage(MOTOR_MAX_VOLTAGE);

        //     break;

        // }

    }

};





/*
 * ╭──────╮
 * │ CTRL │
 * ╰──────╯
 */

bool is_ctrl_pressed(){

    return controller.get_digital(CTRL_BTN);

}





/*
 * ╭────────────────╮
 * │ RING COLOR LED │
 * ╰────────────────╯
 */

void show_ring_color_with_led(){
    
    int8_t color = getRingColor();
    
    if(color == RING_COLOR::BLUE){
        LED::blue();
    } else if (color == RING_COLOR::RED) {
        LED::red();
    } else {
        LED::white();
    }

}