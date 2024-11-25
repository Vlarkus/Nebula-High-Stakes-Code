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

Routine::Routine(const std::string &name, const std::string &description, const std::function<void()> routeFunc)
    : name(name), description(description), routeFunc(routeFunc) {}





/*
 * ╭─────────╮
 * │ METHODS │
 * ╰─────────╯
 */

string Routine::getName() const {
    return name;
}

string Routine::getDescription() const {
    return description;
}

void Routine::run() {
    routeFunc();
}
