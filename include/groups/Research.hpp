#ifndef RESEARCH_H
#define RESEARCH_H

// Group header file
#include "groups/Group.hpp"

// Built in libraries
#include <string>


class Research : public Group {
     private:
        // Fields
        const std::string TYPE = "Research";
        int year;
        std::string semester;
        std::string topic;
    public:
        // Constructor
        Research(
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

#endif //RESEARCH_H
