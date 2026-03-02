#ifndef PRESENTATION_H
#define PRESENTATION_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Presentation : public GradedTask {
    public:
        // Constructor
        Presentation(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
};

#endif //PRESENTATION_H
