#ifndef HOMEWORK_H
#define HOMEWORK_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Homework : public GradedTask {
    private:
        const std::string TYPE = "Homework";
    public:
        // Constructor
        Homework(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
        // Accessor
        std::string getType(); 
};

#endif //HOMEWORK_H
