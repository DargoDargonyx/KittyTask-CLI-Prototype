#ifndef DEVWORK_H
#define DEVWORK_H

// Group header file
#include "groups/Group.hpp"

// Built in libraries
#include <string>


class DevWork : public Group {
    private:
        // Fields
        const std::string TYPE = "DevWork";
        int year;
        std::string topic;
    public:
        // Constructor
        DevWork(
            int idNum, 
            const std::string& name, 
            int year, 
            const std::string& topic
        );
        // Accessors
        int getYear();
        std::string getTopic();
        std::string getType();
        // Mutators
        void setYear(int year);
        void setTopic(const std::string& topic);
};

#endif //DEVWORK_H
