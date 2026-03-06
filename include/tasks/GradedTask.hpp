#ifndef GRADEDTASK_H
#define GRADEDTASK_H

// Task header file
#include "tasks/Task.hpp"

// Built in library
#include <string>


class GradedTask : public Task {
    private:
        const std::string TYPE = "GradedTask";
    protected:
        // Field
        int grade;
    public:
        // Constructor & Deconstructor
        GradedTask(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status,
            int grade
        );
        virtual ~GradedTask() = default;
        // Accessor & Mutator
        std::string getType();
        int getGrade();
        void setGrade(int grade);
};

#endif //GRADEDTASK_H 
