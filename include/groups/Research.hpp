#ifndef RESEARCH_H
#define RESEARCH_H

// Group header file
#include "groups/Group.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Research : public Group {
     private:
        // Fields
        const std::string TYPE = "Research";
        uint16_t year;
        std::string semester;
        std::string topic;
    public:
        // Constructor
        Research(
            int idNum, 
            const std::string& name, 
            uint16_t year, 
            const std::string& semester, 
            const std::string& topic
        );
        // Accessors
        uint16_t getYear();
        std::string getSemester();
        std::string getTopic();
        std::string getType();
        // Mutators
        void setYear(uint16_t year);
        void setSemester(const std::string& semester);
        void setTopic(const std::string& topic);
};

#endif //RESEARCH_H
