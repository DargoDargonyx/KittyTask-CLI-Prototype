#ifndef CHORE_H
#define CHORE_H

// Task header file
#include "tasks/Task.hpp"

// Built in library
#include <string>


class Chore : public Task {
    public:
        Chore(
            int idNum, 
            const std::string& name, 
            const std::string& date, 
            bool status
        );
};

#endif //CHORE_H
