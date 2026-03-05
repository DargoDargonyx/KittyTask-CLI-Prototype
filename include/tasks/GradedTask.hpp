#ifndef GRADEDTASK_H
#define GRADEDTASK_H

// Task header file
#include "tasks/Task.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class GradedTask : public Task {
    private:
        const std::string TYPE = "GradedTask";
    protected:
        // Field
        uint16_t grade;
    public:
        // Constructor & Deconstructor
        GradedTask(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            uint16_t grade
        );
        virtual ~GradedTask() = default;
        // Accessor & Mutator
        std::string getType();
        uint16_t getGrade();
        void setGrade(uint16_t grade);
};

#endif //GRADEDTASK_H 
