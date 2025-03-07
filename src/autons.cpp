/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "autons.hpp"
#include "lemlib-tarball/api.hpp"





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
ASSET(autonSkillsRoute_txt);
lemlib_tarball::Decoder autonSkills(autonSkillsRoute_txt);


#define FORWARDS {.forwards = true}
#define BACKWARDS {.forwards = false}
#define EARLY_EXIT_FORWARDS {.forwards = true, .earlyExitRange = 2}
#define EARLY_EXIT_BACKWARDS {.forwards = false, .earlyExitRange = 2}

namespace {
    int8_t selectedRoutineIndex = 3;
}

Routine routines[] = {

    Routine("DO NOTHING", "Do nithing...", []() {
        
        chassis.setPose(0, 0, 0, 0);
        chassis.moveToPoint(0, 96, 3000, FORWARDS);

        screen::set_pen(Color::white);
        while(chassis.isInMotion()){
            screen::print(E_TEXT_MEDIUM, 1, "X: %f", chassis.getPose().x);
            screen::print(E_TEXT_MEDIUM, 2, "Y: %f", chassis.getPose().y);
            screen::print(E_TEXT_MEDIUM, 3, "Angle: %f", chassis.getPose().theta);
            screen::print(E_TEXT_MEDIUM, 3, "Dist: %f", vertical.getDistanceTraveled());
            delay(10);
        }

    }),


    Routine("Drive FWD RED/BLUE", "Drives forward 1 tile.", []() {

        chassis.setPose(0, 0, 0);
        chassis.moveToPoint(0, 24, 1000);

    }),


    Routine("Drive BKWRD 2.5 ONER RED/BLUE", "Drives backwards 2.5 tiles. Scores One Ring. Works on red or blue alliance", []() {

        chassis.setPose(0, 0, 0);
        chassis.moveToPoint(0, -40, 3000, BACKWARDS);
        while(chassis.isInMotion()){
            MOGO::close_if_mogo_detected();
        }

        INTAKE::in();

    }),

    Routine("Auton Skills", "Auton Skills Route", []() {

        // Setup
        LADYBROWN::initialize();
        chassis.setPose(0, 0, 180);

        LADYBROWN::setTargetPosition(240);
        delay(1500);
        
        chassis.moveToPose(0, 10, 90, 1000, BACKWARDS);
        chassis.waitUntilDone();
        
        chassis.moveToPose(-24, 10, 90, 1000, BACKWARDS);
        LADYBROWN::setTargetPosition(3);
        chassis.waitUntilDone();
        delay(500);
        
        MOGO::close();
        delay(1000);
        


        chassis.turnToPoint(-30, 32, 1000);
        chassis.waitUntilDone();
        INTAKE::in();

        chassis.moveToPose(-30, 32, 90, 1000, FORWARDS);
        chassis.waitUntilDone();
        delay(1000);


        chassis.turnToPoint(-48, 32, 1000);
        chassis.waitUntilDone();
        
        chassis.moveToPose(-48, 32, 90, 1000, FORWARDS);
        chassis.waitUntilDone();
        delay(1000);



        chassis.turnToPoint(-60, 54, 1000);
        chassis.waitUntilDone();

        chassis.moveToPose(-60, 52, 90, 1000, FORWARDS);
        chassis.waitUntilDone();
        delay(1000);



        chassis.turnToPoint(-60, 52, 1000);
        chassis.waitUntilDone();

        chassis.moveToPose(-60, 52, 90, 1000, FORWARDS);
        chassis.waitUntilDone();
        delay(1000);
        
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