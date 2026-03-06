#ifndef SELFSTUDY_H
#define SELFSTUDY_H

// Group header file
#include "groups/Group.hpp"

// Built in libraries
#include <string>


class SelfStudy : public Group {
    private:
        // Fields
        const std::string TYPE = "SelfStudy";
        int year;
        std::string semester;
        std::string topic;
    public:
        // Constructor
        SelfStudy(
            int idNum, 
            const std::string& name,
            int year, 
            const std::string& semester, 
            const std::string& topic
        );
        // Accessors
        int getYear();
        std::string getSemester();
        std::string getTopic();
        std::string getType();
        // Mutators
        void setYear(int year);
        void setSemester(const std::string& semester);
        void setTopic(const std::string& topic);
};

#endif //SELFSTUDY_H
