#ifndef PROJECT_H
#define PROJECT_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in library
#include <string>
#include <cstdint>


class Project : public GradedTask {
    public:
        // Constructor
        Project(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
};

#endif //PROJECT_H
