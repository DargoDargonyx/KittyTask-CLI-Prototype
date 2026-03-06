#ifndef QUIZ_H
#define QUIZ_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in library
#include <string>


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
            int grade
        );
        // Accessor
        std::string getType(); 
};

#endif //QUIZ_H
