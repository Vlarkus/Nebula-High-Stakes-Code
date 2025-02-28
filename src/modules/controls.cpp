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

    if(!discPorts.empty())
    {
        screen::set_pen(Color::white);
        screen::print(E_TEXT_MEDIUM, 7, discPorts.c_str());

        for(int8_t i = 0; i <= 2; i++)
        {
            controller.rumble("-");

            // LED::red();
            delay(250);
            // LED::white();
            delay(250);

        }

    } else {

        // LED::green();
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
        intake.move_voltage(-MOTOR_MAX_VOLTAGE);
    }

    void out(){
        intake.move_voltage(MOTOR_MAX_VOLTAGE);
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

#define RED_COLOR_THRESHOLD 1100
#define BLUE_COLOR_THRESHOLD 900

int8_t getRingColor(){

    auto rgb = opticalSensor.get_rgb();
    screen::set_pen(Color::white);
    // screen::print(E_TEXT_MEDIUM, 1, "R: %f", rgb.red);
    // screen::print(E_TEXT_MEDIUM, 2, "G: %f", rgb.blue);
    // screen::print(E_TEXT_MEDIUM, 3, "B: %f", rgb.green);
    if(BLUE_COLOR_THRESHOLD < rgb.blue && rgb.red < RED_COLOR_THRESHOLD){
        
        // screen::set_pen(Color::blue);
        // screen::fill_rect(240, 0, 480, 120);
        // screen::set_pen(Color::white);
        return RING_COLOR::BLUE;
    
    } else if (RED_COLOR_THRESHOLD < rgb.red) {
    
        // screen::set_pen(Color::red);
        // screen::fill_rect(240, 0, 480, 120);
        // screen::set_pen(Color::white);
        return RING_COLOR::RED;
    
    } else {
    
        // screen::set_pen(Color::gray);
        return RING_COLOR::NONE;
    
    }

}


namespace DOINKER {

    void control(){

        if(controller.get_digital(DOINKER_DEACTIVATE_BTN)){
            activate();
        } else if(controller.get_digital(DOINKER_ACTIVATE_BTN)){
            deactivate();
        }

    }

    void activate(){
        doinkerPiston.set_value(true);
    }

    void deactivate(){
        doinkerPiston.set_value(false);
    }

}





/*
 * ╭───────────╮
 * │   HANG    │
 * ╰───────────╯
 */
//no hang anymore - integrated with lb

// namespace HANG{

//     void control(){

//         if(is_ctrl_pressed() && controller.get_digital(HANG_ACTIVATE_BTN)){
//             activate();
//         }

//     }

//     void activate(){
//         hangPiston.set_value(true);
//     }

// }




/*
 * ╭───────────╮
 * │ COLORSORT │
 * ╰───────────╯
 */

namespace COLORSORT{

    bool isActive = true;
    bool isEliminateRed = false;
    bool wasTogglePressed = false;

    pros::Task* control_task = nullptr;

    void control(){

        if(!controller.get_digital(SELECTIVE_INTAKE_TOGGLE_ACTIVE_BTN)){
            COLORSORT::wasTogglePressed = false; // Check for pressing the button only once
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

            // TESTING
            // if(ringColor == RING_COLOR::RED){
            //     screen::set_pen(Color::red);
            //     controller.rumble(".");
            // }
            
            // if(ringColor == RING_COLOR::BLUE) {
            //     screen::set_pen(Color::blue);
            //     controller.rumble("-");
            // }
            
            // if(ringColor == RING_COLOR::NONE) {
            //     screen::set_pen(Color::white);
            // }

            // screen::fill_rect(0, 0, 480, 240);
            // END TESTING

            if(COLORSORT::isEliminateRed){

                // LED::blue();

                if(ringColor == RING_COLOR::RED){
                    pros::delay(100);
                    intake.move_voltage(0);
                    pros::delay(100);
                    intake.move_voltage(MOTOR_MAX_VOLTAGE);
                } else if(ringColor == RING_COLOR::BLUE) {
                    //dont do anything, not supposed to sort out blue
                }

            } else {

                // LED::red();

                if(ringColor == RING_COLOR::BLUE){
                    pros::delay(100);
                    intake.move_voltage(0);
                    pros::delay(100);
                    intake.move_voltage(MOTOR_MAX_VOLTAGE);
                } else if(ringColor == RING_COLOR::RED) {
                    //dont do anything, not supposed to sort out red
                }

            }

        } else {}
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

#define DISTANCE_SENSOR_MOGO_THRESHOLD 66
#define DISTANCE_SENSOR_EMPTY_SPACE_THRESHOLD 100

    // State variables
    bool is_autoclamp_on = true;
    bool previous_is_autoclamp_on = true;
    bool is_closed = false;
    bool is_space_cleared_before = true;

    void control() {

        // Provide feedback when autoclamp state changes
        if (previous_is_autoclamp_on != is_autoclamp_on) {
            controller.rumble("--");
            previous_is_autoclamp_on = is_autoclamp_on;
        }

        // Toggle autoclamp state only if control key is pressed
        if (is_ctrl_pressed()) {
            if (controller.get_digital(INTAKE_OUT_BTN)) {
                is_autoclamp_on = false;
            } else if (controller.get_digital(INTAKE_IN_BTN)) {
                is_autoclamp_on = true;
            }

        } else {

            // Manual override for open/close
            if (controller.get_digital(MOGO_OUT_BTN)) {
                open();
            } else if (controller.get_digital(MOGO_IN_BTN)) {
                close();
            } 
            // Automatic clamping behavior
            else if (is_autoclamp_on) {
                close_if_mogo_detected();
            }

        }

        // Update space clearance state
        if (distanceSensor.get_distance() > DISTANCE_SENSOR_EMPTY_SPACE_THRESHOLD) {
            is_space_cleared_before = true;
        }

    }

    // Detect if a mobile goal (MOGO) is within the threshold distance
    bool is_mogo_detected() {
        return distanceSensor.get_distance() < DISTANCE_SENSOR_MOGO_THRESHOLD;
    }

    // Close the clamp if a MOGO is detected and space was previously clear
    void close_if_mogo_detected() {
        if (is_mogo_detected() && is_space_cleared_before) {
            close();
            is_space_cleared_before = false;
        }
    }

    // Close the clamp
    void close() {
        if (is_closed) return; // Do nothing if already closed

        mogoPiston.set_value(true);
        controller.rumble("-");
        is_closed = true;
    }

    // Open the clamp
    void open() {
        if (!is_closed) return; // Do nothing if already open

        mogoPiston.set_value(false);
        controller.rumble(".");
        is_closed = false;
    }
}






/*
 * ╭───────────────────╮
 * │ LADYBROWN CONTROL │
 * ╰───────────────────╯
 */

 namespace LADYBROWN {

    #define STATE_REST 0
    #define STATE_GRAB 30
    #define STATE_PRESCORE 180
    #define STATE_SCORE 360

    const int numStates = 4;

    int states[numStates] = {STATE_REST, STATE_GRAB, STATE_PRESCORE, STATE_SCORE}; //tune degrees to set to
    int target = STATE_REST;
    int currentState = 0;

    pros::Task* control_task = nullptr;

    void nextState() {
        currentState++;
        if (currentState >= numStates) {
            currentState = 0;
        }
        target = states[currentState];
    }

    void initialize() {
        lbEncoderSensor.set_reversed(false);
        lbEncoderSensor.set_position(STATE_REST);
        run_async();
    }

    void task_function() {
        double kp = 0.2; //tune
        double error = target - lbEncoderSensor.get_position();
        double velocity = kp * error;
        ladyBrown.move(velocity);
    }

    void run_async() {
        if (control_task == nullptr) {
            control_task = new pros::Task(task_function, "Control Task");
        }
    }

    void stop_async() {
        if (control_task != nullptr) {
            control_task->remove();
            delete control_task;
            control_task = nullptr;
        }
    }

    void control() {
        if (controller.get_digital(LADYBROWN_LOADSCORETOGGLE_BTN)) {
            currentState++;
            if (currentState > 3) {
                currentState = 1;
            }
            target = states[currentState];
        } else if (controller.get_digital(LADYBROWN_STORE_BTN)) {
            currentState = 0;
            target = states[currentState];
        } else {
            ladyBrown.move_velocity(0);
        }
    }

    // New function to move to a specific state
    void moveToState(int state) {
        if (state >= 0 && state < numStates) {
            target = states[state];
            while (abs(target - lbEncoderSensor.get_position()) > 1) {
                task_function();
                pros::delay(20); // Small delay to prevent CPU overload
            }
        }
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
        // LED::blue();
    } else if (color == RING_COLOR::RED) {
        // LED::red();
    } else {
        // LED::white();
    }

}