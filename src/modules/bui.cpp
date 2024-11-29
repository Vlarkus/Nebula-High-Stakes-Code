/*
 * ╭─────────────╮
 * │ DESCRIPTION │
 * ╰─────────────╯
 * 
 * This file contains methods that define Brain User Interface (BUI)
 * 
 */





/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "modules/bui.hpp"





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace std;
using namespace pros;
using namespace lemlib;





/*
 * ╭─────────╮
 * │ METHODS │
 * ╰─────────╯
 */

void init_bui(){

    update();
    LED::white();

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

    screen::touch_callback(handleTouch, E_TOUCH_PRESSED);

}

void handleTouch() {

        auto status = screen::touch_status();

        if (status.touch_status == E_TOUCH_PRESSED) {

            if (status.x < 240) {
                previousRoutine();
            } else {
                nextRoutine();
            }
            
        }

    }

    void update(){

        screen::erase();
        screen::print(E_TEXT_LARGE_CENTER, 1, getSelectedRoutine().getName().c_str());
        screen::print(E_TEXT_MEDIUM, 3, getSelectedRoutine().getDescription().c_str());

    }

    void nextRoutine(){

        if(routineIndex < getNumRoutines() - 1){
            routineIndex++;
        } else {
            routineIndex = 0;
        }

        update();

    }

    void previousRoutine(){

        if(routineIndex <= 0){
            routineIndex = getNumRoutines() - 1;
        } else {
            routineIndex--;
        }

        update();

    }

Routine getSelectedRoutine(){
    return getRoutine(routineIndex);
}