#ifndef CLASS_H
#define CLASS_H

#include "groups/Group.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"
#include <string>
#include <cstdint>

class Class : public Group {
    private:
        uint16_t year;
        Semester semester;
        Topic topic;
        uint8_t grade;
    public:
        Class(
            int idNum, 
            const std::string& name, 
            uint16_t year, 
            const Semester& semester, 
            const Topic& topic,
            uint8_t grade
        );
        uint16_t getYear() const;
        void setYear(uint16_t year);
        Semester getSemester() const;
        void setSemester(const Semester& semester);
        Topic getTopic() const;
        void setTopic(const Topic& topic);
        uint8_t getGrade() const;
        void setGrade(uint8_t grade);
};

#endif // CLASS_H
