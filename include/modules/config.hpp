#pragma once

#include "pros/distance.hpp"
#include "pros/optical.hpp"
#include "lemlib/api.hpp"
#include "modules/led.hpp"
#include <string>
#include <cmath>

extern stormlib::aRGB_manager led;

extern lemlib::Chassis chassis;

extern pros::Controller controller;

extern pros::MotorGroup intake;

extern pros::adi::DigitalOut mogoPiston;
extern pros::adi::DigitalOut doinkerPiston;
extern pros::adi::DigitalOut ladybrownPiston;
extern pros::adi::DigitalOut colorsortPiston;
extern pros::adi::DigitalOut hangPiston;

extern pros::Optical opticalSensor;
extern pros::v5::Distance distanceSensor;

extern pros::v5::Rotation lbEncoderSensor;
extern pros::Motor ladyBrown;

extern const pros::controller_digital_e_t LADYBROWN_LOADSCORETOGGLE_BTN;
extern const pros::controller_digital_e_t LADYBROWN_STORE_BTN;
extern const pros::controller_digital_e_t INTAKE_IN_BTN;
extern const pros::controller_digital_e_t INTAKE_OUT_BTN;
extern const pros::controller_digital_e_t SELECTIVE_INTAKE_TOGGLE_ACTIVE_BTN;
extern const pros::controller_digital_e_t SELECTIVE_INTAKE_TOGGLE_COLOR_BTN;
extern const pros::controller_digital_e_t SELECTIVE_INTAKE_BTN;
extern const pros::controller_digital_e_t MOGO_IN_BTN;
extern const pros::controller_digital_e_t MOGO_OUT_BTN;
extern const pros::controller_digital_e_t HANG_ACTIVATE_BTN;
extern const pros::controller_digital_e_t DOINKER_ACTIVATE_BTN;
extern const pros::controller_digital_e_t DOINKER_DEACTIVATE_BTN;
extern const pros::controller_digital_e_t TURN_180_BTN;
extern const pros::controller_digital_e_t CTRL_BTN;

extern std::string find_disconnected_ports();