#ifndef RESEARCH_H
#define RESEARCH_H

// Group header file
#include "groups/Group.hpp"

// Utility header files
#include "util/Semester.hpp"
#include "util/Topic.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Research : public Group {
     private:
        // Fields
        uint16_t year;
        Semester semester;
        Topic topic;
    public:
        // Constructor
        Research(
            int idNum, 
            const std::string& name, 
            uint16_t year, 
            const Semester& semester, 
            const Topic& topic
        );
        // Accessors
        uint16_t getYear() const;
        Semester getSemester() const;
        std::string getSemesterStr() const;
        Topic getTopic() const;
        std::string getTopicStr() const;
        // Mutators
        void setYear(uint16_t year);
        void setSemester(const Semester& semester);
        void setTopic(const Topic& topic);
};

#endif //RESEARCH_H
