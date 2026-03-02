#ifndef NOTES_H
#define NOTES_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Notes : public GradedTask {
    public:
        // Constructor
        Notes(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
};

#endif //NOTES_H
