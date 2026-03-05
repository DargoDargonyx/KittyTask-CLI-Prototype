#ifndef PROGRAMMING_H
#define PROGRAMMING_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Programming : public GradedTask {
    private:
        const std::string TYPE = "Programming";
    public:
        // Constructor
        Programming(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
        // Accessor
        std::string getType(); 
};

#endif //PROGRAMMING_H
