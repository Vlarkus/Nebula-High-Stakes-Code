#pragma once

#include "modules/config.hpp"
#include "modules/led.hpp"

void drivetrain_control();
void intake_control();
void mogo_control();
int32_t getTarget();
void ladybrown_control();
void turn_180_control();
void show_ring_color_with_led();