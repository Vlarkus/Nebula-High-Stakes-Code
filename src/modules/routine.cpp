/*
 * ╭─────────╮
 * │ INCLUDE │
 * ╰─────────╯
 */

#include "modules/routine.hpp"





/*
 * ╭───────────╮
 * │ NAMESPACE │
 * ╰───────────╯
 */

using namespace std;





/*
 * ╭─────────────╮
 * │ CONSTRUCTOR │
 * ╰─────────────╯
 */

Routine::Routine(const string &name, const string &path, const string &description) 
    : name(name), path(path), desciption(description) {}





/*
 * ╭─────────╮
 * │ GETTERS │
 * ╰─────────╯
 */

string Routine::getName() const {
    return name;
}

string Routine::getPath() const {
    return path;
}

string Routine::getDescription() const {
    return desciption;
}
