#pragma once

#include "pros/distance.hpp"
#include "pros/optical.hpp"
#include "lemlib/api.hpp"
#include <string>
#include <cmath>

extern lemlib::Chassis chassis;

extern pros::Controller controller;

extern pros::MotorGroup intake;

extern pros::adi::AnalogOut ledRed;
extern pros::adi::AnalogOut ledGreen;
extern pros::adi::AnalogOut ledBlue;
extern pros::adi::AnalogOut ledBrightness;

extern pros::adi::DigitalOut mogoPiston;
extern pros::adi::DigitalOut doinkerPiston;
extern pros::adi::DigitalOut ladybrownPiston;
extern pros::adi::DigitalOut colorsortPiston;

extern pros::Rotation ladybrownRotation;
// extern pros::Motor ladybrownMotor;

extern pros::Optical opticalSensor;
extern pros::v5::Distance distanceSensor;

extern const pros::controller_digital_e_t INTAKE_IN_BTN;
extern const pros::controller_digital_e_t INTAKE_OUT_BTN;
extern const pros::controller_digital_e_t SELECTIVE_INTAKE_TOGGLE_ACTIVE_BTN;
extern const pros::controller_digital_e_t SELECTIVE_INTAKE_TOGGLE_COLOR_BTN;
extern const pros::controller_digital_e_t SELECTIVE_INTAKE_BTN;
extern const pros::controller_digital_e_t MOGO_IN_BTN;
extern const pros::controller_digital_e_t MOGO_OUT_BTN;
extern const pros::controller_digital_e_t LADYBROWN_RETRACT_BTN;
extern const pros::controller_digital_e_t LADYBROWN_INTAKE_BTN;
extern const pros::controller_digital_e_t LADYBROWN_EXTEND_BTN;
extern const pros::controller_digital_e_t LIFT_UP_BTN;
extern const pros::controller_digital_e_t LIFT_DOWN_BTN;
extern const pros::controller_digital_e_t TURN_180_BTN;
extern const pros::controller_digital_e_t CTRL_BTN;

extern std::string find_disconnected_ports();