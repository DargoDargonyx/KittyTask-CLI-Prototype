#ifndef QUIZ_H
#define QUIZ_H

// Task header file
#include "tasks/GradedTask.hpp"
#include <string>
#include <cstdint>


class Quiz : public GradedTask {
    public:
        // Constructor
        Quiz(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
};

#endif //QUIZ_H
