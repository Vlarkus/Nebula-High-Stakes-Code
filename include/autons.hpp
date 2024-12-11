#pragma once

#include "modules/led.hpp"
#include "lemlib/api.hpp"
#include "modules/config.hpp"
#include "modules/routine.hpp"

extern Routine routines[];

extern void increaseSelectedRoutineIndex();
extern void decreaseSelectedRoutineIndex();
extern int8_t getSelectedRoutineIndex();
extern Routine getSelectedRoutine();
extern Routine getRoutine(int i);
extern int getNumRoutines();