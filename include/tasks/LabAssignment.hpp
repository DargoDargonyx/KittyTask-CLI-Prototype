#ifndef LABASSIGNMENT_H
#define LABASSIGNMENT_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class LabAssignment : public GradedTask {
    private:
        const std::string TYPE = "LabAssignment";
    public:
        // Constructor
        LabAssignment(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
        // Accessor
        std::string getType(); 
};

#endif //LABASSIGNMENT_H
