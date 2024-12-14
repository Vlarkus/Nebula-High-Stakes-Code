/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "autons.hpp"





/*
 * ╭───────╮
 * │ FILES │
 * ╰───────╯
 */





/*
 * ╭──────────╮
 * │ ROUTINES │
 * ╰──────────╯
 */

namespace {
    int8_t selectedRoutineIndex = 0;
}

Routine routines[] = {

    Routine("Do Nothing", "Do nothing...", []() {}),

    Routine("Red", "Do nothing...", []() {

        controller.rumble(".");
        
    }),

    Routine("Blue", "Do nothing...", []() {

        controller.rumble("..");

    }),
    
    Routine("Green", "Do nothing...", []() {

        controller.rumble("...");

    }),

};

void increaseSelectedRoutineIndex(){

    if(selectedRoutineIndex < getNumRoutines() - 1){
        selectedRoutineIndex++;
    } else {
        selectedRoutineIndex = 0;
    }

}

void decreaseSelectedRoutineIndex(){

    if(selectedRoutineIndex <= 0){
        selectedRoutineIndex = getNumRoutines() - 1;
    } else {
        selectedRoutineIndex--;
    }

}

int8_t getSelectedRoutineIndex(){
    return selectedRoutineIndex;
}


Routine getSelectedRoutine(){
    return getRoutine(selectedRoutineIndex);
}

Routine getRoutine(int i){
    return routines[i];
}

int getNumRoutines(){
    return sizeof(routines) / sizeof(routines[0]);
}