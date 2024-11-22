#pragma once

#include "lemlib/api.hpp"

extern lemlib::Chassis chassis;

extern pros::Controller controller;

extern pros::Motor intake;

extern pros::ADIDigitalOut mogo;
extern pros::ADIDigitalOut doinker;

extern pros::controller_digital_e_t INTAKE_IN;
extern pros::controller_digital_e_t INTAKE_OUT;
extern pros::controller_digital_e_t MOGO_IN;
extern pros::controller_digital_e_t MOGO_OUT;