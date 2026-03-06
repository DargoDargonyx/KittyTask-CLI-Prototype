#ifndef LAB_H
#define LAB_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in library
#include <string>


class Lab : public GradedTask {
    private:
        const std::string TYPE = "Lab";
    public:
        // Constructor
        Lab(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            int grade
        );
        // Accessor
        std::string getType(); 
};

#endif //LAB_H
