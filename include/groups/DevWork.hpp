#ifndef DEVWORK_H
#define DEVWORK_H

// Group header file
#include "groups/Group.hpp"

// Utility header file
#include "util/Topic.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class DevWork : public Group {
    private:
        // Fields
        uint16_t year;
        Topic topic;
    public:
        // Constructor
        DevWork(
            int idNum, 
            const std::string& name, 
            uint16_t year, 
            const Topic& topic
        );
        // Accessors
        uint16_t getYear() const;
        Topic getTopic() const;
        std::string getTopicStr() const;
        // Mutators
        void setYear(uint16_t year);
        void setTopic(const Topic& topic);
};

#endif //DEVWORK_H
