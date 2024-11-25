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

using namespace pros::lcd;
using namespace lemlib;





/*
 * ╭─────────╮
 * │ METHODS │
 * ╰─────────╯
 */

void init_bui(){

    initialize();
    update();

    register_btn1_cb(nextRoutine);

}

void update(){

    clear_line(0);
    clear_line(1);

    print(0, "%s\n",  getRoutine(routineIndex).getName());
    print(1, "%s\n", getRoutine(routineIndex).getDescription());

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