#ifndef DEVWORK_H
#define DEVWORK_H

#include "groups/Group.hpp"
#include "util/Topic.hpp"
#include <string>
#include <cstdint>

class DevWork : public Group {
    private:
        uint16_t year;
        Topic topic;
    public:
        DevWork(
            int idNum, 
            const std::string& name, 
            uint16_t year, 
            const Topic& topic
        );
        uint16_t getYear() const;
        void setYear(uint16_t year);
        Topic getTopic() const;
        std::string getTopicStr() const;
        void setTopic(const Topic& topic);
};

#endif //DEVWORK_H
