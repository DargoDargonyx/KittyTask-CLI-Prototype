#ifndef READING_H
#define READING_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in library
#include <string>


class Reading : public GradedTask {
    private:
        const std::string TYPE = "Reading";
    public:
        // Constructor
        Reading(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            int grade
        );
        // Accessor
        std::string getType(); 
};

#endif //READING_H
