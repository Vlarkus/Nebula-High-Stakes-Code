#pragma once

#include "modules/config.hpp"
#include "modules/led.hpp"

extern void drivetrain_control();
extern void intake_control();
extern void selective_intake_control();
extern void mogo_control();
extern int32_t getTarget();
extern void ladybrown_control();
extern int8_t getRingColor();
bool is_ctrl_pressed();
extern void turn_180_control();
extern void show_ring_color_with_led();