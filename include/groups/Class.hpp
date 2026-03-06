#ifndef CLASS_H
#define CLASS_H

// Group header file
#include "groups/Group.hpp"

// Built in libraries
#include <string>


class Class : public Group {
    private:
        // Fields
        const std::string TYPE = "Class";
        int year;
        std::string semester;
        std::string topic;
        int grade;
    public:
        // Constructor
        Class(
            int idNum, 
            const std::string& name, 
            uint16_t year, 
            const std::string& semester, 
            const std::string& topic,
            int grade
        );
        // Accessors
        int getYear();
        std::string getSemester();
        std::string getTopic();
        int getGrade();
        std::string getType();
        // Mutators
        void setYear(int year);
        void setSemester(const std::string& semester);
        void setTopic(const std::string& topic);
        void setGrade(int grade);
};

#endif // CLASS_H
