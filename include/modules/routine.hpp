#pragma once

#include <string>

class Routine {
public:

    Routine(const std::string &name, const std::string &path, const std::string &description);

    std::string getName() const;
    std::string getPath() const;
    std::string getDescription() const;

private:

    std::string name;
    std::string path;
    std::string desciption;

};
