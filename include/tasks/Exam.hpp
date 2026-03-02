#ifndef EXAM_H
#define EXAM_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Exam : public GradedTask {
    public:
        // Constructor
        Exam(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
};

#endif //EXAM_H
