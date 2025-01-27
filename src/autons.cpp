/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "autons.hpp"
#include "lemlib-tarball/api.hpp"
ASSET(new_goal_txt);
ASSET(auton_ring_v1_txt);
ASSET(new_goal_blue_txt);





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


    Routine("Auton Goal Red", "Auton Goal", []() {
        lemlib_tarball::Decoder decoder(new_goal_txt);
        chassis.setPose(-53.323, -59.246, 90);
        chassis.turnToHeading(95,1000);
        chassis.follow(decoder["auton_goal_one"], 15, 1000);
        pros::delay(1000);
        DOINKER::activate(); 
        pros::delay(1000);
        chassis.turnToHeading(57,1000);
        chassis.follow(decoder["auton_goal_two"], 15, 1000, false);
        DOINKER::deactivate();
        chassis.turnToHeading(0,1000);
        chassis.follow(decoder["auton_goal_three"], 15, 1000);
        INTAKE::in();
        pros::delay(1500);
        INTAKE::stop();
        chassis.turnToHeading(180,1000);
        chassis.follow(decoder["auton_goal_four"], 15, 1000, false);
        chassis.turnToHeading(90,1000);
        chassis.follow(decoder["auton_goal_five"], 15, 1000, false);
        MOGO::open();
        chassis.turnToHeading(35,1000);
        chassis.follow(decoder["auton_goal_six"], 15, 1000);

        chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);
    }),

    Routine("Auton Goal Blue", "Auton Goal", []() {
        lemlib_tarball::Decoder decoder(new_goal_blue_txt);
        chassis.setPose(53.323, -59.246, 90);
        chassis.turnToHeading(95,1000);
        chassis.follow(decoder["auton_goal_one"], 15, 1000);
        pros::delay(1000);
        DOINKER::activate(); 
        pros::delay(1000);
        chassis.turnToHeading(57,1000);
        chassis.follow(decoder["auton_goal_two"], 15, 1000, false);
        DOINKER::deactivate();
        chassis.turnToHeading(0,1000);
        chassis.follow(decoder["auton_goal_three"], 15, 1000);
        INTAKE::in();
        pros::delay(1500);
        INTAKE::stop();
        chassis.turnToHeading(180,1000);
        chassis.follow(decoder["auton_goal_four"], 15, 1000, false);
        chassis.turnToHeading(90,1000);
        chassis.follow(decoder["auton_goal_five"], 15, 1000, false);
        MOGO::open();
        chassis.turnToHeading(35,1000);
        chassis.follow(decoder["auton_goal_six"], 15, 1000);

        chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);
    }),


    Routine("Auton Ring V1", "Auton Goal", []() {
        lemlib_tarball::Decoder decoder(auton_ring_v1_txt);
        chassis.setPose(-58.642, 23.655, 270);

        COLORSORT::run_async();
        INTAKE::in();
        while(chassis.isInMotion()){
            MOGO::close_if_mogo_detected();
        }

        chassis.follow(decoder["auton_ring_v1_one"], 15, 2000, false);
        chassis.turnToHeading(45,2000);
        chassis.follow(decoder["auton_ring_v1_two"], 15, 2000);
        chassis.turnToHeading(19,2000);
        chassis.follow(decoder["auton_ring_v1_three"], 15, 2000);
        chassis.turnToHeading(290,2000);
        chassis.follow(decoder["auton_ring_v1_four"], 15, 2000);
        chassis.turnToHeading(225,2000);
        chassis.follow(decoder["auton_ring_v1_five"], 15, 2000);

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