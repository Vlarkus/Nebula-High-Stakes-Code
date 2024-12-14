#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <map>

#include "modules/config.hpp"
#include "modules/images.hpp"
#include "modules/led.hpp"
#include "controls.hpp"
#include "autons.hpp"
#include "api.h"

namespace BUI{

    enum SCREEN{

        COLOR_SELECTOR = 0,
        AUTON_SELECTOR,
        LOGO_ONLY

    };

    extern void initialize();
    void handleTouch();
    void endHandleTouch();
    void set_screen(SCREEN newScreen);
    void render();

    void render_color_selector();
    void handle_touch_color_selector();

    void render_auton_selector();
    void handle_touch_auton_selector();
    void nextRoutine();
    void previousRoutine();

    void render_logo_only();

    void draw_screen(std::string name);


    extern std::map<std::string, const std::vector<std::tuple<int, int, int>>*> screenImages;

}