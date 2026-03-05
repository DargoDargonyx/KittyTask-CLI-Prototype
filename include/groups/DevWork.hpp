#ifndef DEVWORK_H
#define DEVWORK_H

// Group header file
#include "groups/Group.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class DevWork : public Group {
    private:
        // Fields
        const std::string TYPE = "DevWork";
        uint16_t year;
        std::string topic;
    public:
        // Constructor
        DevWork(
            int idNum, 
            const std::string& name, 
            uint16_t year, 
            const std::string& topic
        );
        // Accessors
        uint16_t getYear();
        std::string getTopic();
        std::string getType();
        // Mutators
        void setYear(uint16_t year);
        void setTopic(const std::string& topic);
};

#endif //DEVWORK_H
