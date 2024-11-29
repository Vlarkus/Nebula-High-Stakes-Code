#pragma once

#include "modules/config.hpp"
#include <cstdint>
#include <algorithm>

namespace LED{

    void set_color(uint8_t r, uint8_t g, uint8_t b);
    void set_brightness(uint8_t b);
    void red();
    void yellow();
    void green();
    void blue();
    void purple();
    void white();
    void off();
    void rainbow();
    void stop();

}