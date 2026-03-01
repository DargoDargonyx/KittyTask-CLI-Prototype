#include "external/CLI11.hpp"
#include "util/GroupManager.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"

#include "groups/Group.hpp"
#include "groups/Class.hpp"
#include "groups/DevWork.hpp"
#include "groups/Research.hpp"
#include "groups/SelfStudy.hpp"

#include "tasks/Task.hpp"
#include "tasks/Chore.hpp"
#include "tasks/Exam.hpp"
#include "tasks/Homework.hpp"
#include "tasks/Lab.hpp"
#include "tasks/LabAssignment.hpp"
#include "tasks/Notes.hpp"
#include "tasks/Presentation.hpp"
#include "tasks/Programming.hpp"
#include "tasks/Project.hpp"
#include "tasks/Quiz.hpp"
#include "tasks/Reading.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>

// forward declarations
std::string queryGroupType();
std::string queryGroupName();
uint16_t queryGroupYear();
std::string queryGroupSemester();
std::string queryGroupTopic();

bool isValidGroupType(std::string groupType);
bool isValidGroupName(std::string groupName);
bool isValidGroupYear(uint16_t groupYear);
bool isValidGroupSemester(std::string semester);
bool isValidGroupTopic(std::string topic);

std::string translateSemester(std::string semester);
std::string translateTopic(std::string topic);

Semester strToSemester(std::string semester);
Topic strToTopic(std::string topic);



int main(int argc, char **argv) {
    CLI::App app{"KittyTracker-CLI"};
    GroupManager manager("data/");
    int groupCounter = static_cast<int>(manager.getGroups().size());


    std::string groupType;
    CLI::App* addGroup = app.add_subcommand("addGroup", "Add a new group");
    
    addGroup->callback([&]() {
        groupType = queryGroupType();
        std::string groupName = queryGroupName();

        std::unique_ptr<Group> newGroup;
        if (groupType == "Class") {
            uint16_t groupYear = queryGroupYear();
            std::string semesterStr = queryGroupSemester();
            std::string topicStr = queryGroupTopic();
            newGroup = std::make_unique<Class>(
                groupCounter,
                groupName,
                groupYear,
                strToSemester(semesterStr),
                strToTopic(topicStr),
                -1
            );
        } else if (groupType == "DevWork") {
            uint16_t groupYear = queryGroupYear();
            std::string topicStr = queryGroupTopic();
            newGroup = std::make_unique<DevWork>(
                groupCounter,
                groupName,
                groupYear,
                strToTopic(topicStr)
            );
        } else if (groupType == "Research") {
            uint16_t groupYear = queryGroupYear();
            std::string semesterStr = queryGroupSemester();
            std::string topicStr = queryGroupTopic();
            newGroup = std::make_unique<Research>(
                groupCounter,
                groupName,
                groupYear,
                strToSemester(semesterStr),
                strToTopic(topicStr)
            );
        } else if (groupType == "SelfStudy") {
            uint16_t groupYear = queryGroupYear();
            std::string semesterStr = queryGroupSemester();
            std::string topicStr = queryGroupTopic();
            newGroup = std::make_unique<SelfStudy>(
                groupCounter,
                groupName,
                groupYear,
                strToSemester(semesterStr),
                strToTopic(topicStr)
            );
        }
        
        manager.addGroup(std::move(newGroup));
        std::cout << "Added group \"" << groupName << "\"" << std::endl;
    });

    CLI11_PARSE(app, argc, argv);
    return 0;
}



std::string queryGroupType() {
    std::string groupType;
    bool validType = false;
    while (!validType) {
        std::cout << "Enter a group type (Class, DevWork, Research, SelfStudy): ";
        std::getline(std::cin, groupType);
        validType = isValidGroupType(groupType);
        if (!validType) {
            std::cout << "Not a valid type, try again." << std::endl;
        }
    }
    return groupType;
}

std::string queryGroupName() {
    std::string groupName;
    bool validName = false;
    while (!validName) {
        std::cout << "Enter a group name: ";
        std::getline(std::cin, groupName);
        validName = isValidGroupName(groupName);
        if (!validName) {
            std::cout << "Not a valid name, try again." << std::endl;
        }
    }
    return groupName;
}

uint16_t queryGroupYear() {
    uint16_t groupYear;
    std::string yearStr;
    bool validYear = false;
    while (!validYear) {
        std::cout << "Enter a year for the group: ";
        std::getline(std::cin, yearStr);
        try {
            groupYear = static_cast<uint16_t>(std::stoi(yearStr));
        } catch (...) { 
            std::cerr << "Conversion to int failed" << std::endl;
            groupYear = 0;
        }
        validYear = isValidGroupYear(groupYear);
        if (!validYear) {
            std::cout << "Not a valid year must be a proper integer representation of a year within 10 years of the current year." << std::endl;
        }
    }
    return groupYear;
}

std::string queryGroupSemester() {
    std::string semesterStr;
    bool validSemester = false;
    while (!validSemester) {
        std::cout << "Enter a semester type (Spring, Fall, Summer): ";
        std::getline(std::cin, semesterStr);
        semesterStr = translateSemester(semesterStr);
        validSemester = isValidGroupSemester(semesterStr);
        if (!validSemester) {
            std::cout << "Not a valid semester, try again." << std::endl;
        }
    }
    return semesterStr;
}

std::string queryGroupTopic() {
    std::string topicStr;
    bool validTopic = false;
    while (!validTopic) {
        std::cout << "Enter a topic type (Math, CS, Physics, Chemistry, Biology): ";
        std::getline(std::cin, topicStr);
        topicStr = translateTopic(topicStr);
        validTopic = isValidGroupTopic(topicStr);
        if (!validTopic) {
            std::cout << "Not a valid topic, try again." << std::endl;
        }
    }
    return topicStr;
}

bool isValidGroupType(std::string groupType) {
    return groupType == "Class" ||
            groupType == "DevWork" ||
            groupType == "Research" ||
            groupType == "SelfStudy";
}

bool isValidGroupName(std::string groupName) {
    return groupName.length() > 0;
}

bool isValidGroupYear(uint16_t groupYear) {
    const std::chrono::time_point now{
        std::chrono::system_clock::now()
    };
    const std::chrono::year_month_day ymd{
        std::chrono::floor<std::chrono::days>(now)
    };
    uint16_t currentYear = static_cast<uint16_t>(
            static_cast<int>(ymd.year())
        );
    return groupYear >= currentYear - 10 && 
        groupYear <= currentYear + 10;
}

bool isValidGroupSemester(std::string semester) {
    return semester == "Spring" ||
        semester == "Fall" ||
        semester == "Summer";
}

bool isValidGroupTopic(std::string topic) {
    return topic == "Math" ||
        topic == "CS" ||
        topic == "Physics" ||
        topic == "Chemistry" ||
        topic == "Biology";
}

std::string translateSemester(std::string semester) {
    if (semester == "spring") {
        return "Spring";
    } else if (semester == "fall") {
        return "Fall";
    } else if (semester == "summer") {
        return "Summer";
    } else {
        return semester;
    }
}

std::string translateTopic(std::string topic) {
    if (topic == "Cs" || 
        topic == "cS" || 
        topic == "cs" ||
        topic == "Comp Sci" ||
        topic == "Comp sci" ||
        topic == "comp Sci" ||
        topic == "comp sci" ||
        topic == "Computer Science" ||
        topic == "Computer science" ||
        topic == "computer Science" ||
        topic == "computer science") {
       return "CS"; 
    } else if (topic == "math" || 
               topic == "Mat" || 
               topic == "mat" ||
               topic == "MAT" ||
               topic == "Mathematics" ||
               topic == "mathematics") {
        return "Math";
    } else if (topic == "physics" || 
               topic == "Physic" || 
               topic == "physic" || 
               topic == "Phy" || 
               topic == "phy" || 
               topic == "PHY") {
        return "Physics";
    } else if (topic == "chemistry" || 
               topic == "Chem" || 
               topic == "chem" || 
               topic == "CHEM") {
        return "Chemistry";
    } else if (topic == "biology" || 
               topic == "Bio" || 
               topic == "bio" || 
               topic == "BIO") {
        return "Biology";
    } else {
        return topic;
    }
}

Semester strToSemester(std::string semester) {
    if (semester == "Spring") {
        return Semester::SPRING;
    } else if (semester == "Fall") {
        return Semester::FALL;
    } else if (semester == "Summer") {
        return Semester::SUMMER;
    } else {
        throw std::invalid_argument("Unknown semester value");
    }
}

Topic strToTopic(std::string topic) {
    if (topic == "Math") {
        return Topic::MATH;
    } else if (topic == "CS") {
        return Topic::CS;
    } else if (topic == "Physics") {
        return Topic::PHYSICS;
    } else if (topic == "Chemistry") {
        return Topic::CHEM;
    } else if (topic == "Biology") {
        return Topic::BIO;
    } else {
        throw std::invalid_argument("Unknown topic value");
    }
}
