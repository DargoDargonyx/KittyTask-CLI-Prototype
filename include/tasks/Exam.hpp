#ifndef EXAM_H
#define EXAM_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Exam : public GradedTask {
    private:
        const std::string TYPE = "Exam";
    public:
        // Constructor
        Exam(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
        // Accessor
        std::string getType(); 
};

#endif //EXAM_H
