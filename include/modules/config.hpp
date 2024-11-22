#pragma once

#include <string>
#include "lemlib/api.hpp"

extern lemlib::Chassis chassis;

extern pros::Controller controller;

extern pros::Motor intake;

extern pros::ADIMotor ledRed;
extern pros::ADIMotor ledGreen;
extern pros::ADIMotor ledBlue;

extern pros::adi::DigitalOut mogo;
extern pros::adi::DigitalOut doinker;

extern const pros::controller_digital_e_t INTAKE_IN;
extern const pros::controller_digital_e_t INTAKE_OUT;
extern const pros::controller_digital_e_t MOGO_IN;
extern const pros::controller_digital_e_t MOGO_OUT;

extern std::string find_disconnected_ports();