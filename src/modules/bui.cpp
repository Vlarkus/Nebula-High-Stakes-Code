/*
 * ╭─────────────╮
 * │ DESCRIPTION │
 * ╰─────────────╯
 * 
 * This file contains methods that define Brain User Interface (BUI)
 * 
 */



/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "modules/bui.hpp"



/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace pros::screen;
using namespace lemlib;
using namespace pros;
using namespace std;



/*
 * ╭───────────────╮
 * │ NAMESPACE BUI │
 * ╰───────────────╯
 */

namespace BUI {



    /*
    * ╭─────────╮
    * │ SCREENS │
    * ╰─────────╯
    */

    namespace {
        SCREEN currentScreen = LOGO_ONLY;
    }



    /*
    * ╭─────────╮
    * │ GENERAL │
    * ╰─────────╯
    */

    void initialize() {

        touch_callback(handleTouch, E_TOUCH_PRESSED);
        render();

    }

    void handleTouch() {

        switch (currentScreen) {

        case SCREEN::COLOR_SELECTOR:
            handle_touch_color_selector();
            break;

        case SCREEN::AUTON_SELECTOR:
            handle_touch_auton_selector();
            break;

        default:
            break;

        }

    }

    void set_screen(SCREEN newScreen) {

        if (newScreen != currentScreen) {
            currentScreen = newScreen;
            render();
        }

    }

    void render() {

        switch (currentScreen) {

        case SCREEN::COLOR_SELECTOR:
            render_color_selector();
            break;

        case SCREEN::AUTON_SELECTOR:
            render_auton_selector();
            break;

        case SCREEN::LOGO_ONLY:
            render_logo_only();
            break;

        default:
            render_default();
            break;

        }

    }

    void render_default() {
        set_eraser(Color::red);
        erase();
        set_eraser(Color::black);
    }



    /*
    * ╭────────────────╮
    * │ COLOR SELECTOR │
    * ╰────────────────╯
    */

    void render_color_selector() {

        set_pen(Color::red);
        fill_rect(0, 0, 240, 240);
        set_pen(Color::blue);
        fill_rect(240, 0, 480, 240);
        set_pen(Color::white);

    }

    void handle_touch_color_selector() {

        auto status = touch_status();

        if (status.touch_status == E_TOUCH_PRESSED) {

            COLORSORT::set_is_eliminate_red(status.x > 240);

            set_screen(SCREEN::AUTON_SELECTOR);

        }

    }



    /*
    * ╭────────────────╮
    * │ AUTON SELECTOR │
    * ╰────────────────╯
    */

    void render_auton_selector() {

        set_eraser(Color::black);
        erase();
        set_pen(Color::yellow);
        print(E_TEXT_LARGE_CENTER, 1, getSelectedRoutine().getName().c_str());
        set_pen(Color::white);
        print(E_TEXT_MEDIUM, 3, getSelectedRoutine().getDescription().c_str());

    }

    void nextRoutine() {

        increaseSelectedRoutineIndex();
        render_auton_selector();

    }

    void previousRoutine() {

        decreaseSelectedRoutineIndex();
        render_auton_selector();

    }

    void handle_touch_auton_selector() {

        auto status = touch_status();

        if (status.touch_status == E_TOUCH_PRESSED) {

            if (status.x < 240) {
                previousRoutine();
            } else {
                nextRoutine();
            }

        }

    }



    /*
    * ╭──────────────╮
    * │ DURING MATCH │
    * ╰──────────────╯
    */

    void render_logo_only() {

        set_pen(Color::green);
        erase();
        draw_screen("Nebula Logo");

    }

    void draw_screen(std::string name) {

        if (screenImages.find(name) == screenImages.end()) {
            return;
        }

        for (const auto& tuple : *screenImages[name]) {
            int x = std::get<0>(tuple);
            int y = std::get<1>(tuple);
            int color = std::get<2>(tuple);

            set_pen(color);
            draw_pixel(x, y);
        }

    }



    map<std::string, const std::vector<std::tuple<int, int, int>>*> screenImages = {

        {"Nebula Logo", &IMAGES::NEBULA_LOGO}

    };




}
