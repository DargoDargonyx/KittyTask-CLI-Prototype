#ifndef LAB_H
#define LAB_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Lab : public GradedTask {
    public:
        // Constructor
        Lab(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
};

#endif //LAB_H
