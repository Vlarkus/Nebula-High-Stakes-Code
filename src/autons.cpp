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
ASSET(janSkillsPathExperimental_txt);
lemlib_tarball::Decoder autonSkills(janSkillsPathExperimental_txt);


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

        // -=-=- LEFT SIDE START -=-=- //

        lemlib_tarball::Decoder decoder(janSkillsPathExperimental_txt);
        chassis.setPose(-56.5, 0.058, 270);

        chassis.turnToHeading(205,1000);    
        chassis.follow(decoder["Path 1"], 15, 1000, false);
        
        chassis.waitUntilDone();
        delay(200);
        MOGO::close();
        
        chassis.turnToHeading(90, 1000);
        INTAKE::in();
        chassis.follow(decoder["Path 2"], 15, 1000);

        chassis.waitUntilDone();
        delay(200);

        chassis.turnToHeading(0,1000);
        chassis.follow(decoder["Path 3"], 15, 1000);
        
        chassis.waitUntilDone();
        delay(200);

        chassis.turnToHeading(270,1000);

        chassis.follow(decoder["Path 4"], 15, 1000);
        chassis.waitUntilDone();
        chassis.follow(decoder["Path 5"], 15, 1000);
        
        chassis.waitUntilDone();
        delay(500);

        chassis.turnToHeading(35,1000);
        chassis.follow(decoder["Path 6"], 15, 1000);
        
        chassis.waitUntilDone();
        delay(200);
        
        chassis.turnToHeading(110,1000);
        
        chassis.waitUntilDone();
        delay(1000);
        
        MOGO::open();
        
        delay(100);
        
        chassis.follow(decoder["Path 7"], 15, 1000, false);
        chassis.follow(decoder["Path 8"], 15, 1000);
        chassis.waitUntilDone();

        INTAKE::stop();

        // -=-=- LEFT SIDE FINNISHED -=-=- //



        // -=-=- TRANSITION TO RIGHT SIDE -=-=- //

        chassis.turnToHeading(358,1000);
        chassis.follow(decoder["Path 9"], 15, 4000, false);
        chassis.waitUntilDone();



        // -=-=- RIGHT SIDE START -=-=- //

        MOGO::close();
        chassis.turnToHeading(90,1000);
        INTAKE::in();

        chassis.follow(decoder["Path 10"], 7, 4000);

        
        chassis.waitUntilDone();

        chassis.turnToHeading(145, 1000);
        chassis.follow(decoder["Path 11"], 15, 4000);
        chassis.waitUntilDone();
        delay(1000);

        chassis.turnToHeading(285,1000);
        chassis.follow(decoder["Path 12"], 15, 4000);
        chassis.waitUntilDone();


        chassis.turnToHeading(270,1000);
        chassis.follow(decoder["Path 13"], 15, 4000);
        chassis.follow(decoder["Path 14"], 15, 4000);
        chassis.waitUntilDone();
        delay(1000);

        chassis.turnToHeading(145,1000);

        chassis.follow(decoder["Path 15"], 15, 4000);
        chassis.waitUntilDone();

        delay(1000);
        chassis.turnToHeading(70,1000);
        delay(1000);

        MOGO::open();
        chassis.follow(decoder["Path 16"], 15, 1000, false);
        chassis.follow(decoder["Path 17"], 15, 1000);
        chassis.waitUntilDone();

        INTAKE::stop();

        // -=-=- RIGHT SIDE FINNISHED -=-=- //



        // -=-=- TRANSITION TO OPPOSITE SIDE -=-=- //

        chassis.turnToHeading(75.4, 1000);

        chassis.follow(decoder["Path 18"], 15, 1000);
        chassis.waitUntilDone();
        INTAKE::in();
        delay(500);
        INTAKE::stop();

        chassis.turnToHeading(47, 1000);
        chassis.follow(decoder["Path 19"], 15, 1000);
        chassis.waitUntilDone();
        chassis.turnToHeading(170,1000);
        chassis.follow(decoder["Path 20"], 15, 1000);
        chassis.waitUntilDone();
        chassis.turnToHeading(170,1000);
        chassis.follow(decoder["Path 21"], 15, 4000, false);
        chassis.waitUntilDone();   
        delay(500);
        MOGO::close(); 


        chassis.turnToHeading(333, 1000);
        INTAKE::in();
        chassis.follow(decoder["Path 24"], 15, 1000);
        chassis.waitUntilDone();
        delay(1000);

        chassis.turnToHeading(130, 1000);
        chassis.follow(decoder["Path 29"], 15, 1000);
        chassis.waitUntilDone();

        MOGO::open();

        chassis.turnToHeading(225, 1000);
        chassis.follow(decoder["Path 30"], 15, 1000, false);
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