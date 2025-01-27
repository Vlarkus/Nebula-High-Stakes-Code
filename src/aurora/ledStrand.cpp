// #include "aurora/ledStrand.hpp"

// ledStrand::ledStrand(char port, int length) 
//     : adiPort(charToPort(port)), length(length), ledDriver(adiPort) {
//   buffer.resize(length, 0x000000); // Default all LEDs to off (black).
// }

// int ledStrand::charToPort(char port) {
//   if (std::isalpha(port)) {
//     port = std::toupper(port);      // Convert to uppercase for uniformity.
//     return port - 'A' + 1;          // 'A' becomes 1, 'B' becomes 2, etc.
//   } else if (std::isdigit(port)) {
//     return port - '0';              // If already a number, return as-is.
//   } else {
//     throw std::invalid_argument("Invalid ADI port: must be 'A'-'H', 'a'-'h', or 1-8.");
//   }
// }

// void ledStrand::initialize() {
//   buffer.assign(length, 0xFFFFFF); // Default to white during initialization.
//   update();
// }

// void ledStrand::update() {
//   for (int i = 0; i < length; ++i) {
//     ledDriver.set_pixel(buffer[i], i); // Set each LED color from the buffer.
//   }
//   ledDriver.update(); // Apply the changes to the physical LED strand.
// }

// void ledStrand::off() {
//   buffer.assign(length, 0x000000); // Set all LEDs to off (black).
//   update();
// }

// void ledStrand::setColor(uint32_t color) {
//   buffer.assign(length, color); // Set all LEDs to the specified color.
//   update();
// }

// void ledStrand::setDiode(int index, uint32_t color) {
//   if (index >= 0 && index < length) {
//     buffer[index] = color; // Set the specific LED to the given color.
//     update();
//   }
// }
