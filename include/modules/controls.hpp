#pragma once

#include "modules/config.hpp"
#include "modules/led.hpp"
#include "modules/bui.hpp"
#include <string>

extern void run_connectivity_check();

namespace DRIVETRAIN{

    extern void control();
    extern void turn_180_control();

}

namespace INTAKE {

    extern void control();
    extern void in();
    extern void out();
    extern void stop();

}

namespace COLORSORT {

    extern void control();
    extern void run_async();
    extern void stop_async();
    extern void set_is_eliminate_red(bool b);

}

namespace MOGO{

    extern void control();
    extern bool is_mogo_detected();
    extern void close_if_mogo_detected();
    extern void close();
    extern void open();

}

namespace LADYBROWN{
    extern void control();
}

bool is_ctrl_pressed();

int8_t getRingColor();
extern void show_ring_color_with_led();