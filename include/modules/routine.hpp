#pragma once

#include <string>
#include <functional>

class Routine {
public:

    Routine(const std::string &name, const std::string &description, const std::function<void()> routeFunc);

    std::string getName() const;
    std::string getDescription() const;
    void run();

private:

    const std::string name;
    const std::string description;
    const std::function<void()> routeFunc;

};
