#ifndef GROUP_H
#define GROUP_H

// Task header file
#include "tasks/Task.hpp"

// Built in libraries
#include <string>
#include <memory>


class Group {
    private:
        const std::string TYPE = "Default";
    protected:
        // Fields
        int idNum;
        std::string name;
    public:
        // Constructor & Deconstructor
        Group(
            int idNum, 
            const std::string& name
        );
        virtual ~Group() = default;
        // Accessors
        virtual int getIdNum();
        virtual std::string getName();
        virtual std::string getType();
        // Mutators
        virtual void setIdNum(int idNum);
        virtual void setName(const std::string& name);
};

#endif // GROUP_H
