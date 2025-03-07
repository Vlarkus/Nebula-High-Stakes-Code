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
        chassis.setPose(-58.457, -0.249, 270);

        // Score alliance stake
        LADYBROWN::setTargetPosition(240);
        delay(1500);

        chassis.follow(autonSkills["Path 1"], 7, 1000, false);
        chassis.waitUntilDone();
        LADYBROWN::setTargetPosition(3);

        
        chassis.turnToHeading(0,1000);
        chassis.follow(autonSkills["Path 2"], 7, 1000, false);
        chassis.waitUntilDone();

        MOGO::close();
        INTAKE::in();
        chassis.turnToHeading(90,1000);
        chassis.follow(autonSkills["Path 3"], 7, 1000);
        chassis.waitUntilDone();

        chassis.turnToHeading(132,1000);
        chassis.follow(autonSkills["Path 4"], 7, 1000);
        chassis.waitUntil(12);
        LADYBROWN::setTargetPosition(35);
        chassis.waitUntilDone();

        chassis.turnToHeading(277,1000);
        INTAKE::stop();
        chassis.follow(autonSkills["Path 5"], 7, 1000);
        chassis.waitUntilDone();

        LADYBROWN::setTargetPosition(80);
        INTAKE::in();
        chassis.turnToHeading(180,1000);
        chassis.follow(autonSkills["Path 6"], 7, 1000);
        chassis.waitUntilDone();

        LADYBROWN::setTargetPosition(140);
        chassis.follow(autonSkills["Path 7"], 7, 1000, false);
        chassis.waitUntilDone();

        LADYBROWN::setTargetPosition(3);
        chassis.turnToHeading(265,1000);
        chassis.follow(autonSkills["Path 8"], 7, 1000);
        chassis.waitUntilDone();

        chassis.turnToHeading(271,1000);
        chassis.follow(autonSkills["Path 9"], 7, 1000);
        chassis.waitUntilDone();

        chassis.turnToHeading(268,1000);
        chassis.follow(autonSkills["Path 10"], 7, 1000);
        chassis.waitUntilDone();

        chassis.turnToHeading(150,1000);
        chassis.follow(autonSkills["Path 11"], 7, 1000);
        chassis.waitUntilDone();

        chassis.turnToHeading(80,1000);
        MOGO::open();
        chassis.follow(autonSkills["Path 12"], 7, 1000,false);
        chassis.waitUntilDone();

        chassis.turnToHeading(82,1000);
        LADYBROWN::setTargetPosition(35);
        chassis.follow(autonSkills["Path 13"], 7, 1000);
        chassis.waitUntilDone();

        delay(500);
        INTAKE::stop();
        chassis.turnToHeading(307,1000);
        chassis.follow(autonSkills["Path 14"], 7, 1000);
        chassis.waitUntilDone();

        chassis.turnToHeading(166,1000);
        chassis.follow(autonSkills["Path 15"], 7, 1000);
        chassis.waitUntilDone();

        chassis.follow(autonSkills["Path 16"], 7, 1000, false);
        chassis.waitUntilDone();

        MOGO::close();
        chassis.turnToHeading(90,1000);
        chassis.follow(autonSkills["Path 17"], 7, 1000);
        chassis.waitUntilDone();

        LADYBROWN::setTargetPosition(240);
        chassis.follow(autonSkills["Path 18"], 7, 1000, false);
        chassis.waitUntilDone();

        LADYBROWN::setTargetPosition(3);
        INTAKE::in();
        chassis.turnToHeading(225,1000);
        chassis.follow(autonSkills["Path 19"], 7, 1000);
        chassis.waitUntilDone();

        chassis.turnToHeading(315,1000);
        INTAKE::stop();
        chassis.follow(autonSkills["Path 20"], 7, 1000);
        chassis.waitUntilDone();

        chassis.follow(autonSkills["Path 21"], 7, 1000);
        INTAKE::in();
        chassis.waitUntilDone();

        chassis.turnToHeading(268,1000);
        chassis.follow(autonSkills["Path 22"], 7, 1000);
        chassis.waitUntilDone();

        chassis.turnToHeading(31,1000);
        chassis.follow(autonSkills["Path 23"], 7, 1000);
        chassis.waitUntilDone();

        chassis.turnToHeading(270,1000);
        chassis.follow(autonSkills["Path 24"], 7, 1000);
        chassis.waitUntilDone();
        
        chassis.turnToHeading(112,1000);
        MOGO::open();
        chassis.follow(autonSkills["Path 25"], 7, 1000);
        chassis.waitUntilDone();

        MOGO::close();
        chassis.turnToHeading(45,1000);
        chassis.follow(autonSkills["Path 26"], 7, 1000);
        chassis.waitUntilDone();

        chassis.turnToHeading(66,1000);
        chassis.follow(autonSkills["Path 27"], 7, 1000);
        chassis.waitUntilDone();
        chassis.turnToHeading(0,1000);
        chassis.follow(autonSkills["Path 28"], 7, 1000);
        chassis.waitUntilDone();
        chassis.follow(autonSkills["Path 29"], 7, 1000, false);
        chassis.waitUntilDone();
        chassis.turnToHeading(102,1000);
        chassis.follow(autonSkills["Path 30"], 7, 1000);
        chassis.waitUntilDone();
        chassis.turnToHeading(180,1000);
        chassis.follow(autonSkills["Path 31"], 7, 1000);
        chassis.waitUntilDone();
        chassis.turnToHeading(45,1000);
        chassis.follow(autonSkills["Path 32"], 7, 1000);
        chassis.waitUntilDone();
        chassis.turnToHeading(90,1000);
        chassis.follow(autonSkills["Path 33"], 7, 1000);
        chassis.waitUntilDone();
        chassis.turnToHeading(326,1000);
        chassis.follow(autonSkills["Path 34"], 7, 1000);
        chassis.waitUntilDone();
        chassis.turnToHeading(77,1000);
        chassis.follow(autonSkills["Path 35"], 7, 1000, false);
        chassis.waitUntilDone();
        chassis.follow(autonSkills["Path 36"], 7, 1000);
        chassis.waitUntilDone();
        chassis.turnToHeading(27,1000);
        chassis.follow(autonSkills["Path 37"], 7, 1000, false);
        chassis.waitUntilDone();
        chassis.turnToHeading(185,1000);
        chassis.follow(autonSkills["Path 38"], 7, 1000, false);
        chassis.waitUntilDone();
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