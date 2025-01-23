/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "autons.hpp"
#include "lemlib-tarball/api.hpp"
ASSET(auton_goal_txt);
ASSET(test2_txt);





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
#define EARLY_EXIT_FORWARDS {.forwards = true, .earlyExitRange = 2}
#define EARLY_EXIT_BACKWARDS {.forwards = false, .earlyExitRange = 2}

namespace {
    int8_t selectedRoutineIndex = 0;
}

Routine routines[] = {



    Routine("Do Nothing", "Do nothing...", []() {}),


    Routine("Auton Goal", "Auton Goal", []() {
        lemlib_tarball::Decoder decoder(auton_goal_txt);
        chassis.setPose(-57.921, -57.268, 290);

        COLORSORT::run_async();
        INTAKE::in();
        while(chassis.isInMotion()){
            MOGO::close_if_mogo_detected();
        }

        chassis.follow(decoder["auton_goal_one"], 15, 2000, false);
        chassis.turnToHeading(270,2000);
        chassis.follow(decoder["auton_goal_two"], 15, 2000);
        chassis.turnToHeading(245,2000);
        chassis.follow(decoder["auton_goal_three"], 15, 2000);
        DOINKER::activate();
        chassis.turnToHeading(90,2000);
        DOINKER::deactivate();
        chassis.turnToHeading(-90,2000);
        chassis.turnToHeading(65,2000);
        chassis.follow(decoder["auton_goal_four"], 15, 2000, false);
        MOGO::open();
        chassis.follow(decoder["auton_goal_five"], 15, 2000);
        chassis.turnToHeading(165,2000);
        chassis.follow(decoder["auton_goal_six"], 15, 2000, false);
        chassis.turnToHeading(80,2000);
        chassis.follow(decoder["auton_goal_seven"], 15, 2000);

        chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);

        INTAKE::stop();
        COLORSORT::stop_async();
    }),



    Routine("Drive FWD", "Drives forward 1 tile.", []() {

        chassis.setPose(0, 0, 0);
        chassis.moveToPoint(0, 24, 1000);

    }),



    Routine("Drive BKWRD", "Drives backwards 1 tile.", []() {

        chassis.setPose(0, 0, 0);
        chassis.moveToPoint(0, 24, 1000);

    }),



    Routine("RED NEG 4R UNSAFE AWP", "Red, Negative Side, 4 rings, 1 Stake, Unsafe, AWP", []() {

        chassis.setPose(0, 0, 180);

        chassis.turnToHeading(200, 800);
        chassis.moveToPoint(16, 36, 2000, BACKWARDS);

        while(chassis.isInMotion()){
            MOGO::close_if_mogo_detected();
        }

        chassis.turnToPoint(2, 45, 1000);
        COLORSORT::run_async();
        INTAKE::in();
        chassis.moveToPoint(2, 45, 2000, FORWARDS);
        delay(400);
        chassis.moveToPoint(16, 32, 2000, BACKWARDS);

        chassis.turnToPoint(0, 32, 1000);
        chassis.moveToPoint(0, 32, 2000, FORWARDS);
        delay(400);

        chassis.turnToPoint(-7, 44, 1000);
        chassis.moveToPoint(7, 44, 2000, FORWARDS);

        chassis.turnToPoint(20, 44, 1000);
        chassis.moveToPoint(20, 44, 2000, FORWARDS);

        INTAKE::stop();
        COLORSORT::stop_async();
        
    }),



    Routine("RED NEG 5R SAFE", "Red, Negative Side, 5 rings, 1 Stake, Safe", []() {

        chassis.setPose(0, 10, 180);

        chassis.turnToHeading(225, 1000);
        chassis.moveToPoint(16, 32, 2000, BACKWARDS);

        while(chassis.isInMotion()){

            MOGO::close_if_mogo_detected();
            delay(20);

        }

        INTAKE::in();
        COLORSORT::run_async();

        chassis.turnToPoint(0, 32, 1000);
        chassis.moveToPoint(0, 32, 2000, FORWARDS);

        chassis.turnToPoint(5, 11.5, 1000);
        chassis.moveToPoint(5, 11.5, 2000, FORWARDS);

        chassis.turnToPoint(19, -5, 1000);
        chassis.moveToPoint(19, -5, 2000, FORWARDS);
        chassis.moveToPoint(14, 0, 2000, BACKWARDS);
        chassis.moveToPoint(19, -5, 2000, FORWARDS);

        chassis.moveToPoint(8, 7.5, 2000, BACKWARDS);
        chassis.turnToPoint(32, 7.5, 1000);
        chassis.moveToPoint(32, 7.5, 2000, FORWARDS);

        chassis.moveToPoint(28, 7.5, 2000, BACKWARDS);
        chassis.turnToPoint(28, 38, 1000);
        chassis.moveToPoint(28, 38, 2000, FORWARDS);
        
    }),



    Routine("SKILLS", "Skills route", []() {

        chassis.setPose(0, 0, 180);

        // -=-=- Red Positive Corner -=-=-

        chassis.moveToPoint(0, 4, 500, BACKWARDS);
        chassis.turnToHeading(270, 400);

        // Mogo

        chassis.moveToPoint(7.5, 4, 1000, BACKWARDS);
        delay(500);


        while(chassis.isInMotion()){

            MOGO::close_if_mogo_detected();
            delay(20);

        }

        // Rings

        chassis.turnToPoint(7.5, 24, 2000);
        INTAKE::in();
        chassis.moveToPoint(7.5, 24, 2000, FORWARDS);
        delay(500);

        chassis.turnToPoint(40, 24, 2000);
        chassis.moveToPoint(40, 24, 2000, FORWARDS);
        delay(500);

        chassis.turnToPoint(40, 2, 2000);
        chassis.moveToPoint(40, 2, 2000, FORWARDS);
        delay(500);

        chassis.moveToPoint(40, 11, 1000, BACKWARDS);

        // chassis.turnToPoint(46, 14, 1000);
        // chassis.moveToPoint(46, 14, 1000, FORWARDS);

        // // Scoring Corner

        // chassis.turnToPoint(50, 3.5, 1000, BACKWARDS);
        // INTAKE::stop();
        // MOGO::open();
        // chassis.moveToPoint(50, 3.5, 1000, FORWARDS);



        // // -=-=- Red Negative Corner -=-=-

        // // Mogo

        // chassis.moveToPoint(15, 8, 1000, EARLY_EXIT_BACKWARDS);
        // chassis.moveToPoint(-29, 8, 1000, BACKWARDS);

        // while(chassis.isInMotion()){

        //     MOGO::close_if_mogo_detected();
        //     delay(20);

        // }

        // // Rings

        // INTAKE::in();
        // chassis.turnToPoint(-30, 31, 1000);
        // chassis.moveToPoint(-30, 31, 1000, EARLY_EXIT_FORWARDS);
        // chassis.moveToPoint(-41.5, 45.5, 1000, EARLY_EXIT_FORWARDS);
        // chassis.moveToPoint(-59, 52, 1000, BACKWARDS);

        // chassis.turnToPoint(-55, 33, 1000);
        // chassis.moveToPoint(-55, 33, 1000, EARLY_EXIT_FORWARDS);
        // chassis.moveToPoint(-54, 18, 1000, EARLY_EXIT_FORWARDS);
        // chassis.moveToPoint(-54, -1.5, 1000, FORWARDS);

        // chassis.turnToPoint(-62, 5, 1000);
        // chassis.moveToPoint(-62, -5, 1000, FORWARDS);

        // chassis.turnToPoint(-65, 0, 1000, BACKWARDS);
        // MOGO::open();
        // chassis.moveToPoint(-65, 0, 1000, BACKWARDS);

        // // -=-=- Blue Empty Mogo -=-=-






        // COLORSORT::run_async();

        // INTAKE::stop();
        // COLORSORT::stop_async();
        
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