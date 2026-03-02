#ifndef LABASSIGNMENT_H
#define LABASSIGNMENT_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class LabAssignment : public GradedTask {
    public:
        // Constructor
        LabAssignment(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
};

#endif //LABASSIGNMENT_H
