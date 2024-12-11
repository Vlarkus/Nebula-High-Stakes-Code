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

ASSET(nr1_txt);




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

    Routine("Danny's auton", "Testing...",
    []() {

        chassis.setPose(-58.526, 23.439, 107.722);

        chassis.follow(nr1_txt, 7, 5000, false);        

    })

    // Routine("Move Back and Score", "No description...",
    // []() {

    //     chassis.setPose(0, 0, 0);


    //     chassis.moveToPoint(0, -5, 1000, {.forwards = false});
    //     intake.move_voltage(-12000);
    //     chassis.waitUntilDone();
    //     pros::delay(1000);
    //     intake.move_voltage(0);
    //     chassis.moveToPoint(0, 10, 2000);
        

    // })

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