/*
 * ╭─────────────╮
 * │ DESCRIPTION │
 * ╰─────────────╯
 * 
 * This file contains methods that control RGB LED lights connected through ADIMotors defined in config.cpp.
 * 
 */





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





/*
 * ╭─────╮
 * │ LED │
 * ╰─────╯
 */

namespace LED{



    /*
    * ╭─────────╮
    * │ PRIVATE │
    * ╰─────────╯
    */

    namespace {



        bool isTaskRunning = false;

        Task* led_task = nullptr;



        void set(uint8_t r, uint8_t g, uint8_t b) {

            // ledRed.set_value(static_cast<uint16_t>(255 - r));
            // ledGreen.set_value(static_cast<uint16_t>(255 - g));
            // ledBlue.set_value(static_cast<uint16_t>(255 - b));
            
        }




        void rainbow(void* param) {
            int time_delay = 10;

            while (true) {
                for (int i = 0; i <= 255; i++) {
                    set(255, i, 0);
                    Task::delay(time_delay);
                }

                for (int i = 255; i >= 0; i--) {
                    set(i, 255, 0);
                    Task::delay(time_delay);
                }

                for (int i = 0; i <= 255; i++) {
                    set(0, 255, i);
                    Task::delay(time_delay);
                }

                for (int i = 255; i >= 0; i--) {
                    set(0, i, 255);
                    Task::delay(time_delay);
                }

                for (int i = 0; i <= 255; i++) {
                    set(i, 0, 255);
                    Task::delay(time_delay);
                }

                for (int i = 255; i >= 0; i--) {
                    set(255, 0, i);
                    Task::delay(time_delay);
                }
            }
        }








    }





    /*
    * ╭────────╮
    * │ PUBLIC │
    * ╰────────╯
    */

    void set_color(uint8_t r, uint8_t g, uint8_t b) {

        stop();
        set(r, b, g);
        
    }

    void set_brightness(uint8_t b) {

        ledBrightness.set_value(static_cast<uint16_t>(static_cast<float>(16 - b) / 16.0 * 4095.0));

    }



    void red() {

        stop();
        set(255, 0, 0);

    }



    void yellow() {

        stop();
        set(255, 255, 0);

    }



    void green() {

        stop();
        set(0, 255, 0);

    }



    void blue() {

        stop();
        set(0, 0, 255);

    }



    void purple() {

        stop();
        set(255, 0, 255);

    }



    void white() {

        stop();
        set(255, 255, 255);

    }



    void off() {

        stop();
        set(0, 0, 0);

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



}