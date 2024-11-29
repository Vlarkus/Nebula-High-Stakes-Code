#pragma once

#include <string>
#include "modules/config.hpp"
#include "modules/led.hpp"
#include "autons.hpp"
#include "api.h"

int8_t routineIndex = 0;

extern void init_bui();
void update();
void handleTouch();
void nextRoutine();
void previousRoutine();

extern Routine getSelectedRoutine();

// TODO: include LGVL