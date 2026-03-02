#ifndef READING_H
#define READING_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Reading : public GradedTask {
    public:
        // Constructor
        Reading(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
};

#endif //READING_H
