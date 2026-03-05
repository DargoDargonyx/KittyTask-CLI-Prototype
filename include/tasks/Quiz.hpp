#ifndef QUIZ_H
#define QUIZ_H

// Task header file
#include "tasks/GradedTask.hpp"
#include <string>
#include <cstdint>


class Quiz : public GradedTask {
    private:
        const std::string TYPE = "Quiz";
    public:
        // Constructor
        Quiz(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
        // Accessor
        std::string getType(); 
};

#endif //QUIZ_H
