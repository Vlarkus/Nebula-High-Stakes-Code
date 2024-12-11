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
using namespace std;





/*
 * ╭───────────────╮
 * │ NAMESPACE BUI │
 * ╰───────────────╯
 */

namespace BUI{



    /*
    * ╭─────────╮
    * │ SCREENS │
    * ╰─────────╯
    */

    namespace{
        SCREEN currentScreen = COLOR_SELECTOR;
    }




    /*
    * ╭─────────╮
    * │ GENERAL │
    * ╰─────────╯
    */

    void initialize(){

        touch_callback(handleTouch, pros::E_TOUCH_PRESSED);
        render();

    }

    void handleTouch() {

        switch (currentScreen)
        {

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

    void set_screen(SCREEN newScreen){

        currentScreen = newScreen;
        render();

    }

    void render(){

        switch (currentScreen)
        {

        case SCREEN::COLOR_SELECTOR:
            render_color_selector();
            break;

        case SCREEN::AUTON_SELECTOR:
            render_auton_selector();
            break;

        case SCREEN::DURING_MATCH:
            render_during_match();
            break;
        
        default:

            set_eraser(pros::Color::red);
            erase();
            set_eraser(pros::Color::black);

            break;

        }

    }





    /*
    * ╭────────────────╮
    * │ COLOR SELECTOR │
    * ╰────────────────╯
    */

    void render_color_selector(){

        set_pen(pros::Color::red);
        fill_rect(0, 0, 240, 240);
        set_pen(pros::Color::blue);
        fill_rect(240, 0, 480, 240);

    }

    void handle_touch_color_selector(){

        auto status = touch_status();

        if (status.touch_status == pros::E_TOUCH_PRESSED) {

            set_selective_intake_is_eliminate_red(status.x > 240);

            set_screen(SCREEN::AUTON_SELECTOR);
            
        }

    }





    /*
    * ╭────────────────╮
    * │ AUTON SELECTOR │
    * ╰────────────────╯
    */

    void render_auton_selector(){

        erase();
        print(pros::E_TEXT_LARGE_CENTER, 1, getSelectedRoutine().getName().c_str());
        print(pros::E_TEXT_MEDIUM, 3, getSelectedRoutine().getDescription().c_str());

    }

    void nextRoutine(){

        increaseSelectedRoutineIndex();
        render_auton_selector();
        // update cui

    }

    void previousRoutine(){

        decreaseSelectedRoutineIndex();
        render_auton_selector();
        // update cui

    }

    void handle_touch_auton_selector(){

        auto status = touch_status();

        if (status.touch_status == pros::E_TOUCH_PRESSED) {

            if (status.x < 240) {
                previousRoutine();
            } else {
                nextRoutine();
            }

            render_auton_selector();
            
        }

    }





    /*
    * ╭──────────────╮
    * │ DURING MATCH │
    * ╰──────────────╯
    */

    void render_during_match(){
        erase();
    }



}