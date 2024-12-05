#pragma once

#include "modules/config.hpp"
#include "modules/led.hpp"
#include "controls.hpp"
#include "autons.hpp"
#include "api.h"

namespace BUI{

    enum SCREEN{

        COLOR_SELECTOR = 0,
        AUTON_SELECTOR,
        DURING_MATCH

    };

    extern void initialize();
    void handleTouch();
    void set_screen(SCREEN newScreen);
    void render();

    void render_color_selector();
    void handle_touch_color_selector();

    void render_auton_selector();
    void handle_touch_auton_selector();
    void nextRoutine();
    void previousRoutine();
    Routine getSelectedRoutine();

    void render_during_match();

}