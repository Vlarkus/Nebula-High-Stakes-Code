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

ASSET(example_txt); // replace '.' with "_"





/*
 * ╭──────────╮
 * │ ROUTINES │
 * ╰──────────╯
 */

Routine routines[] = {

    Routine("Do Nothing", "Do nothing...", []() {}),

    Routine("PID Test: Turn", "Turning around in a circle to the following angles: 45deg, 90deg, 270 deg, 180 deg, and 360deg respectively",
    []() {

        chassis.setPose(0, 0, 0);

        chassis.turnToHeading(45, 3000);
        chassis.turnToHeading(90, 3000);
        chassis.turnToHeading(270, 3000);
        chassis.turnToHeading(180, 3000);
        chassis.turnToHeading(360, 3000);

    }),

    Routine("PID Test: Drive (1)", "Driving around in a straight line to the following vertical positions: 5in, 15in, 7.5in, -5in, and 0in respectively",
    []() {

        chassis.setPose(0, 0, 0);

        chassis.moveToPoint(0, 15, 5000);
        chassis.moveToPoint(0, 25, 5000);
        chassis.moveToPoint(0, 7.5, 5000, {.forwards = false});
        chassis.moveToPoint(0, 0, 5000, {.forwards = false});

    }),

    Routine("PID Test: Drive (2)", "Driving around to the following points in a plane: (5, 5), (10, 0), (0, 7.5), (0, 10), (0, 0) respectively",
    []() {

        chassis.setPose(0, 0, 0);

        chassis.moveToPoint(10, 20, 5000);
        chassis.moveToPoint(5, 5, 5000, {.forwards = false});
        chassis.moveToPoint(0, 15, 5000);
        chassis.moveToPoint(0, 0, 5000, {.forwards = false});

    }),

    Routine("Systems Test", "Driving around and using robot systems to check their functionality.",
    []() {

        chassis.setPose(0, 0, 0);

        intake.move_voltage(12000);
        chassis.moveToPoint(15, 15, 5000);

        chassis.waitUntilDone();
        intake.move_voltage(0);

        chassis.moveToPoint(0, 15, 5000, {.forwards = false});
        chassis.waitUntil(7.5);
        mogoPiston.set_value(true);
        chassis.waitUntilDone();
        mogoPiston.set_value(false);

    })

};

Routine getRoutine(int i){
    return routines[i];
}

int getNumRoutines(){
    return sizeof(routines) / sizeof(routines[0]);
}