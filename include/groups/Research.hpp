#ifndef RESEARCH_H
#define RESEARCH_H

#include "groups/Group.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"
#include <string>
#include <cstdint>

class Research : public Group {
     private:
        uint16_t year;
        Semester semester;
        Topic topic;
    public:
        Research(
            int idNum, 
            const std::string& name, 
            uint16_t year, 
            const Semester& semester, 
            const Topic& topic
        );
        uint16_t getYear() const;
        void setYear(uint16_t year);
        Semester getSemester() const;
        std::string getSemesterStr() const;
        void setSemester(const Semester& semester);
        Topic getTopic() const;
        std::string getTopicStr() const;
        void setTopic(const Topic& topic);
};

#endif //RESEARCH_H
