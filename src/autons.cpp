/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "autons.hpp"





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace pros;





/*
 * ╭──────────╮
 * │ ROUTINES │
 * ╰──────────╯
 */

#define FORWARDS {.forwards = true}
#define BACKWARDS {.forwards = false}

namespace {
    int8_t selectedRoutineIndex = 0;
}

Routine routines[] = {

    Routine("Do Nothing", "Do nothing...", []() {}),

    Routine("RED NEG 4R AWP", "Red, Negative Side, 4 rings, 1 Stake, AWP", []() {

        chassis.setPose(0, 0, 180);

        chassis.turnToHeading(225, 1000);
        chassis.moveToPoint(32, -16, 2000, BACKWARDS);

        while(chassis.isInMotion()){

            MOGO::close_if_mogo_detected();
            delay(20);

        }

        chassis.turnToPoint(45, -2, 1000);
        INTAKE::in();
        COLORSORT::run_async();
        chassis.moveToPoint(45, -2, 2000, FORWARDS);
        delay(500);
        chassis.moveToPoint(45, -2, 2000, BACKWARDS);

        chassis.turnToPoint(32, 0, 1000);
        chassis.moveToPoint(32, 0, 2000, FORWARDS);
        delay(500);

        chassis.turnToPoint(32, 0, 1000);
        chassis.moveToPoint(44, 7, 2000, FORWARDS);

        chassis.turnToPoint(44, -20, 1000);
        chassis.moveToPoint(44, -20, 2000, FORWARDS);

        INTAKE::stop();
        COLORSORT::stop_async();
        
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