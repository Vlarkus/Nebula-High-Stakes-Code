#pragma once

#include <string>
#include <cmath>
#include "lemlib/api.hpp"
#include "pros/optical.hpp"

extern lemlib::Chassis chassis;

extern pros::Controller controller;

extern pros::Motor intake;

extern pros::adi::AnalogOut ledRed;
extern pros::adi::AnalogOut ledGreen;
extern pros::adi::AnalogOut ledBlue;
extern pros::adi::AnalogOut ledBrightness;

extern pros::adi::DigitalOut mogo;
extern pros::adi::DigitalOut doinker;

extern pros::Optical optical;

extern const pros::controller_digital_e_t INTAKE_IN;
extern const pros::controller_digital_e_t INTAKE_OUT;
extern const pros::controller_digital_e_t MOGO_IN;
extern const pros::controller_digital_e_t MOGO_OUT;
extern const pros::controller_digital_e_t TURN_180;

extern std::string find_disconnected_ports();