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

    update();

}

void update(){

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