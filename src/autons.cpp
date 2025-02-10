/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "autons.hpp"
#include "lemlib-tarball/api.hpp"
ASSET(new_goal_txt);
ASSET(janSkillsPath_txt);
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
    int8_t selectedRoutineIndex = 1;
}

Routine routines[] = {

    Routine("DO NOTHING", "Do nithing...", []() {}),

    Routine("Skills", "Skills routine. Credit to Faaz :)", []() {
        lemlib_tarball::Decoder decoder(janSkillsPath_txt);
        chassis.setPose(-56.5, 0.058, 270);
        chassis.turnToHeading(205,1000);    
        chassis.follow(decoder["Path 1"], 15, 1000, false);
        pros::delay(1000);
        MOGO::close();
        chassis.turnToHeading(90, 1000);
        INTAKE::in();
        chassis.follow(decoder["Path 2"], 15, 1000);
        pros::delay(2000);
        chassis.turnToHeading(0,1000);
        chassis.follow(decoder["Path 3"], 15, 1000);
        pros::delay(2000);
        chassis.turnToHeading(270,1000);
        chassis.follow(decoder["Path 4"], 15, 1000);
        chassis.follow(decoder["Path 5"], 15, 1000);
        pros::delay(2000);
        chassis.turnToHeading(35,1000);
        chassis.follow(decoder["Path 6"], 15, 1000);
        pros::delay(2000);
        chassis.turnToHeading(110,1000);
        pros::delay(2000);
        MOGO::open();
        pros::delay(1000);
        chassis.follow(decoder["Path 7"], 15, 1000, false);
        chassis.follow(decoder["Path 8"], 15, 1000);
        pros::delay(1000);
        chassis.turnToHeading(358,1000);
        chassis.follow(decoder["Path 9"], 15, 1000, false);
        pros::delay(2000);
        MOGO::close();
        chassis.turnToHeading(90,1000);
        INTAKE::in();
        chassis.follow(decoder["Path 10"], 7, 1000);
        pros::delay(2000);
        chassis.turnToHeading(180, 1000);
        chassis.follow(decoder["Path 11"], 15, 1000);
        pros::delay(2000);
        chassis.turnToHeading(270,1000);
        chassis.follow(decoder["Path 12"], 15, 1000);
        chassis.follow(decoder["Path 13"], 15, 1000);
        chassis.turnToHeading(145,1000);
        chassis.follow(decoder["Path 14"], 15, 1000);
        pros::delay(2000);
        chassis.turnToHeading(70,1000);
        chassis.follow(decoder["Path 15"], 15, 1000, false);
        pros::delay(2000);
        MOGO::open();
        chassis.follow(decoder["Path 16"], 15, 1000);
        // pros::delay(2000);
        // MOGO::open();
        // pros::delay(1000);
        // chassis.follow(decoder["Path 17"], 15, 1000);
        // chassis.turnToHeading(80,1000);
        // chassis.follow(decoder["Path 18"], 15, 1000); //intake and hold ring 1 (no mogo yet)
        // pros::delay(1000);
        // INTAKE::in();
        // pros::delay(500);
        // INTAKE::stop();
        // chassis.turnToHeading(0,1000);
        // chassis.follow(decoder["Path 19"], 15, 1000); //intake and hold ring 2 (no mogo yet)
        // pros::delay(1000);
        // INTAKE::in();
        // pros::delay(200);
        // INTAKE::stop();
        // chassis.turnToHeading(225, 1000);   
        // chassis.follow(decoder["Path 20"], 15, 1000, false);
        // pros::delay(2000);
        // MOGO::close();
        // INTAKE::in();
        // chassis.turnToHeading(315,1000);
        // chassis.follow(decoder["Path 21"], 15, 1000);
        // pros::delay(1000);
        // chassis.turnToHeading(0, 1000);
        // chassis.follow(decoder["Path 22"], 15, 1000);
        // pros::delay(1000);
        // chassis.turnToHeading(295,1000);
        // chassis.follow(decoder["Path 23"], 15, 1000);
        // pros::delay(1000);
        // chassis.turnToHeading(84,1000);
        // chassis.follow(decoder["Path 24"], 15, 1000);
        // pros::delay(1000);
        // chassis.follow(decoder["Path 25"], 15, 1000, false);
        // chassis.turnToHeading(264, 1000);
        // chassis.follow(decoder["Path 26"], 15, 1000, false);
        // pros::delay(2000);
        // MOGO::open();
        // pros::delay(500);
        // chassis.follow(decoder["Path 27"], 15, 1000);
        // chassis.turnToHeading(330, 100);
        // chassis.follow(decoder["Path 28"], 15, 1000, false);
        // pros::delay(2000);
        // MOGO::close();
        // chassis.turnToHeading(350, 1000);
        // chassis.follow(decoder["Path 29"], 15, 1000, false);
        // pros::delay(2000);
        // MOGO::open();
        // chassis.turnToHeading(315, 1000);
        // chassis.follow(decoder["Path 30"], 15, 1000);
        // chassis.follow(decoder["Path 31"], 15, 1000, false);
        // INTAKE::stop();
    }),


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