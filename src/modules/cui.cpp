/*
 * ╭─────────────╮
 * │ DESCRIPTION │
 * ╰─────────────╯
 * 
 * This file contains methods that define Controller User Interface (CUI)
 * 
 */





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace std;





/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "modules/cui.hpp"

// namespace CUI {

//     namespace{
//         SCREEN currentScreen = COLOR_SELECTOR;
//         pros::Task *handleTouchTask = nullptr;
//     }

//     void initialize(){

//         startHandleTouch();
//         render();

//     }

//     void handleTouch(void* param){

//         // switch (currentScreen)
//         // {

//         // case SCREEN::COLOR_SELECTOR:
//         //     handle_touch_color_selector();
//         //     break;

//         // case SCREEN::AUTON_SELECTOR:
//         //     handle_touch_auton_selector();
//         //     break;

//         // default:
//         //     break;
        
//         // }

//         // pros::Task::delay(20);

//     }

//     void startHandleTouch(){

//         if(handleTouchTask != nullptr) return;

//         handleTouchTask = new pros::Task(handleTouch, nullptr, "handleTouch");

//     }

//     void endHandleTouch(){

//         if(handleTouchTask == nullptr) return;

//         handleTouchTask -> remove();
//         handleTouchTask = nullptr;

//     }
    
//     void set_screen(SCREEN newScreen){

//     }
    
//     void render(){

//         switch (currentScreen)
//         {

//         case SCREEN::COLOR_SELECTOR:
//             CUI::render_color_selector();
//             break;

//         case SCREEN::AUTON_SELECTOR:
//             render_auton_selector();
//             break;

//         case SCREEN::DURING_MATCH:
//             render_during_match();
//             break;
        
//         default:
//             controller.clear();
//             break;

//         }

//     }

//     void render_color_selector();
    
//     void handle_touch_color_selector();

//     void render_auton_selector();
    
//     void handle_touch_auton_selector();
    
//     void nextRoutine();
    
//     void previousRoutine();

//     void render_during_match();

// }