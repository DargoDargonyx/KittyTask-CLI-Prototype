#ifndef CLASS_H
#define CLASS_H

// Group header file
#include "groups/Group.hpp"

// Built in libraries
#include <string>
#include <cstdint>


class Class : public Group {
    private:
        // Fields
        const std::string TYPE = "Class";
        uint16_t year;
        std::string semester;
        std::string topic;
        uint16_t grade;
    public:
        // Constructor
        Class(
            int idNum, 
            const std::string& name, 
            uint16_t year, 
            const std::string& semester, 
            const std::string& topic,
            uint16_t grade
        );
        // Accessors
        uint16_t getYear();
        std::string getSemester();
        std::string getTopic();
        uint16_t getGrade();
        std::string getType();
        // Mutators
        void setYear(uint16_t year);
        void setSemester(const std::string& semester);
        void setTopic(const std::string& topic);
        void setGrade(uint16_t grade);
};

#endif // CLASS_H
