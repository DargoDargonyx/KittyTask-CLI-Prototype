#ifndef CLASS_H
#define CLASS_H

// Group header file
#include "groups/Group.hpp"

// Utility header files
#include "util/Semester.hpp"
#include "util/Topic.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Class : public Group {
    private:
        // Fields
        uint16_t year;
        Semester semester;
        Topic topic;
        uint16_t grade;
    public:
        // Constructor
        Class(
            int idNum, 
            const std::string& name, 
            uint16_t year, 
            const Semester& semester, 
            const Topic& topic,
            uint16_t grade
        );
        // Accessors
        uint16_t getYear() const;
        Semester getSemester() const;
        std::string getSemesterStr() const;
        Topic getTopic() const;
        std::string getTopicStr() const;
        uint16_t getGrade() const;
        // Mutators
        void setYear(uint16_t year);
        void setSemester(const Semester& semester);
        void setTopic(const Topic& topic);
        void setGrade(uint16_t grade);
};

#endif // CLASS_H
