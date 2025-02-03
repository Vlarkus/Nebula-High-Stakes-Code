#pragma once

#include "pros/rtos.hpp"
#include "pros/adi.hpp"
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <cctype>

/**
 * @brief LED Strand class for controlling a single LED strand.
 */
class ledStrand {
public:
  /**
   * @brief Construct a new ledStrand object.
   * 
   * @param adiPort ADI port (either a number or a character 'A'-'H' or 'a'-'h').
   * @param length Number of LEDs in the strand.
   */
  ledStrand(char adiPort, int length);

  /**
   * @brief Initialize the LED strand.
   */
  void initialize();

  /**
   * @brief Update the LED strand with the current buffer values.
   */
  void update();

  /**
   * @brief Turn off all LEDs on the strand.
   */
  void off();

  /**
   * @brief Set the entire strand to a single color.
   * 
   * @param color The color to set all LEDs to (0xRRGGBB format).
   */
  void setColor(uint32_t color);

  /**
   * @brief Set the color of a specific LED in the strand.
   * 
   * @param index The index of the LED to modify.
   * @param color The color to set the LED to (0xRRGGBB format).
   */
  void setDiode(int index, uint32_t color);

private:
  int adiPort;                      ///< ADI port of the LED strand (converted to integer).
  int length;                       ///< Number of LEDs in the strand.
  std::vector<uint32_t> buffer;     ///< Buffer storing current colors of the LEDs.
  pros::adi::Led ledDriver;         ///< PROS LED driver object.

  /**
   * @brief Convert a character port ('A'-'H', 'a'-'h') to an integer (1-8).
   * 
   * @param port Character representing the port.
   * @return int Integer port number (1-8).
   */
  int charToPort(char port);
};
