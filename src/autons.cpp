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



    Routine("Drive FWD", "Drives forward 1 tile.", []() {

        chassis.setPose(0, 0, 0);
        chassis.moveToPoint(0, 24, 1000);

    }),



    Routine("RED NEG 4R UNSAFE AWP", "Red, Negative Side, 4 rings, 1 Stake, Unsafe, AWP", []() {

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



    Routine("RED NEG 5R SAFE", "Red, Negative Side, 5 rings, 1 Stake, Safe", []() {

        chassis.setPose(0, 0, 180);

        chassis.turnToHeading(225, 1000);
        chassis.moveToPoint(32, -16, 2000, BACKWARDS);

        while(chassis.isInMotion()){

            MOGO::close_if_mogo_detected();
            delay(20);

        }

        INTAKE::in();
        COLORSORT::run_async();

        chassis.turnToPoint(32, 0, 1000);
        chassis.moveToPoint(32, 0, 2000, FORWARDS);

        chassis.turnToPoint(11.5, 5, 1000);
        chassis.moveToPoint(11.5, 5, 2000, FORWARDS);

        chassis.turnToPoint(-5, 19, 1000);
        chassis.moveToPoint(-5, 19, 2000, FORWARDS);
        chassis.moveToPoint(0, 14, 2000, BACKWARDS);
        chassis.moveToPoint(-5, 19, 2000, FORWARDS);

        chassis.moveToPoint(7.5, 8, 2000, BACKWARDS);
        chassis.turnToPoint(7.5, 32, 1000);
        chassis.moveToPoint(7.5, 32, 2000, FORWARDS);

        chassis.moveToPoint(7.5, 28, 2000, BACKWARDS);
        chassis.turnToPoint(38, 28, 1000);
        chassis.moveToPoint(38, 28, 2000, FORWARDS);
        
    })



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