#pragma once

#include "modules/config.hpp"
#include "modules/led.hpp"
#include "modules/bui.hpp"
#include <string>

extern void run_connectivity_check();
extern void drivetrain_control();
extern void intake_control();
extern void selective_intake_control();
extern void set_selective_intake_is_eliminate_red(bool b);
extern void mogo_control();
extern void ladybrown_control();
int8_t getRingColor();
bool is_ctrl_pressed();
extern void turn_180_control();
extern void show_ring_color_with_led();