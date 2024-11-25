#pragma once

#include "lemlib/api.hpp"
#include "modules/config.hpp"
#include "modules/routine.hpp"

extern Routine routines[];

extern Routine getRoutine(int i);
extern int getNumRoutines();