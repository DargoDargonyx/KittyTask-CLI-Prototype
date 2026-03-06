#ifndef PRESENTATION_H
#define PRESENTATION_H

// Task header file
#include "tasks/GradedTask.hpp"

// Built in library
#include <string>


class Presentation : public GradedTask {
    private:
        const std::string TYPE = "Presentation";
    public:
        // Constructor
        Presentation(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            int grade
        );
        // Accessor
        std::string getType(); 
};

#endif //PRESENTATION_H
