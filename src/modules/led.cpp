/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "led.hpp"





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace pros;

namespace {



    bool isTaskRunning = false;

    Task* led_task = nullptr;



    void set(uint8_t r, uint8_t g, uint8_t b) {

        ledRed.set_value(r / 2);
        ledGreen.set_value(g / 2);
        ledBlue.set_value(b / 2);

    }



    void rainbow(void* param) {

        int time_delay = 25;

        while (true) {

            for (int i = 0; i < 255; i++) {
                set(255, i, 0);
                Task::delay(time_delay);
            }

            for (int i = 255; i > 0; i--) {
                set(i, 255, 0);
                Task::delay(time_delay);
            }

            for (int i = 0; i < 255; i++) {
                set(0, 255, i);
                Task::delay(time_delay);
            }

            for (int i = 255; i > 0; i--) {
                set(0, i, 255);
                Task::delay(time_delay);
            }

            for (int i = 0; i < 255; i++) {
                set(i, 0, 255);
                Task::delay(time_delay);
            }
            
            for (int i = 255; i > 0; i--) {
                set(255, 0, i);
                Task::delay(time_delay);
            }
        
        }


    }



}





/*
 * ╭─────────╮
 * │ METHODS │
 * ╰─────────╯
 */

void set_color(uint8_t r, uint8_t g, uint8_t b) {

    stop();
    set(r, b, g);
    
}



void red() {

    stop();
    set(255, 0, 0);

}



void blue() {

    stop();
    set(255, 0, 255);

}



void purple() {

    stop();
    set(255, 0, 255);

}



void white() {

    stop();
    set(255, 255, 255);

}



void rainbow() {

    if(isTaskRunning) return;
    led_task =  new Task(rainbow, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "led_task");
    isTaskRunning = true;
    
}



void stop() {

    if(led_task) {

        led_task -> suspend();
        delete led_task;
        led_task = nullptr;

    }
    
    isTaskRunning = false;

}