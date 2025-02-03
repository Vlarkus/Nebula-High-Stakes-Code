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

    BUI::initialize();

    string discPorts = find_disconnected_ports();

    if(!discPorts.empty()){

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

void drivetrain_control(){

    int leftY = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
    chassis.arcade(leftY, rightX);

}





/*
 * ╭────────────────╮
 * │ INTAKE CONTROL │
 * ╰────────────────╯
 */

void intake_control(){
    if(controller.get_digital(INTAKE_IN_BTN)){
        intake.move_voltage(MOTOR_MAX_VOLTAGE);
    } else if(controller.get_digital(INTAKE_OUT_BTN)){
        intake.move_voltage(-MOTOR_MAX_VOLTAGE);
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

#define RED_COLOR_THRESHOLD 900
#define BLUE_COLOR_THRESHOLD 800

int8_t getRingColor(){

    auto rgb = optical.get_rgb();
    
    if(BLUE_COLOR_THRESHOLD < rgb.blue){
        return RING_COLOR::BLUE;
    } else if (RED_COLOR_THRESHOLD < rgb.red) {
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

            if(ringColor == RING_COLOR::RED){
                SELECTIVE_INTAKE::isPistonExtended = true;
            } else if(ringColor == RING_COLOR::BLUE) {
                SELECTIVE_INTAKE::isPistonExtended = false;
            }

        } else {

            LED::red();

            if(ringColor == RING_COLOR::BLUE){
                SELECTIVE_INTAKE::isPistonExtended = true;
            } else if(ringColor == RING_COLOR::RED) {
                SELECTIVE_INTAKE::isPistonExtended = false;
            }

        }

    } else {

        LED::purple();
        SELECTIVE_INTAKE::isPistonExtended = false;

    }



    selectiveIntakePiston.set_value(SELECTIVE_INTAKE::isPistonExtended);

}

void set_selective_intake_is_eliminate_red(bool b){
    SELECTIVE_INTAKE::isEliminateRed = b;
}





/*
 * ╭──────────────╮
 * │ MOGO CONTROL │
 * ╰──────────────╯
 */

void mogo_control(){
    if(controller.get_digital(MOGO_IN_BTN)){
        mogoPiston.set_value(true);
    } else if(controller.get_digital(MOGO_OUT_BTN)){
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

};

void ladybrown_control(){

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





/*
 * ╭──────╮
 * │ CTRL │
 * ╰──────╯
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
    
    int8_t color = getRingColor();
    
    if(color == RING_COLOR::BLUE){
        LED::blue();
    } else if (color == RING_COLOR::RED) {
        LED::red();
    } else {
        LED::white();
    }

}