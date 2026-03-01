#include "util/QueryHelper.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"

#include <string>
#include <cstdint>
#include <iostream>
#include <chrono>


QueryHelper::QueryHelper(const std::string& outputPreamble) {
    this->outputPreamble = outputPreamble;
}


std::string QueryHelper::queryGroupType() {
    std::string groupType;
    bool validType = false;
    while (!validType) {
        std::cout << outputPreamble 
                  << "Enter a group type: ";
        std::getline(std::cin, groupType);
        groupType = translateGroupType(groupType);
        validType = isValidGroupType(groupType);
        if (!validType) {
            std::cout << outputPreamble 
                      << "Not a valid type, try again." 
                      << std::endl;
        }
    }
    return groupType;
}

std::string QueryHelper::queryGroupName() {
    std::string groupName;
    bool validName = false;
    while (!validName) {
        std::cout << outputPreamble 
                  << "Enter a group name: ";
        std::getline(std::cin, groupName);
        validName = isValidGroupName(groupName);
        if (!validName) {
            std::cout << outputPreamble
                      << "Not a valid name, try again." 
                      << std::endl;
        }
    }
    return groupName;
}

uint16_t QueryHelper::queryGroupYear() {
    uint16_t groupYear;
    std::string yearStr;
    bool validYear = false;
    while (!validYear) {
        std::cout << outputPreamble
                  << "Enter a year for the group: ";
        std::getline(std::cin, yearStr);
        try {
            groupYear = static_cast<uint16_t>(std::stoi(yearStr));
        } catch (...) { 
            std::cerr << outputPreamble
                      << "Conversion to int failed" 
                      << std::endl;
            groupYear = 0;
        }
        validYear = isValidGroupYear(groupYear);
        if (!validYear) {
            std::cout << outputPreamble
                      << "Not a valid year, must be a proper integer" 
                      << " representation of a year within 10 years" 
                      << " of the current year." 
                      << std::endl;
        }
    }
    return groupYear;
}

std::string QueryHelper::queryGroupSemester() {
    std::string semesterStr;
    bool validSemester = false;
    while (!validSemester) {
        std::cout << outputPreamble
                  << "Enter a semester type (Spring, Fall, Summer): ";
        std::getline(std::cin, semesterStr);
        semesterStr = translateSemester(semesterStr);
        validSemester = isValidGroupSemester(semesterStr);
        if (!validSemester) {
            std::cout << outputPreamble
                      << "Not a valid semester, try again." 
                      << std::endl;
        }
    }
    return semesterStr;
}

std::string QueryHelper::queryGroupTopic() {
    std::string topicStr;
    bool validTopic = false;
    while (!validTopic) {
        std::cout << outputPreamble
                  << "Enter a topic type: ";
        std::getline(std::cin, topicStr);
        topicStr = translateTopic(topicStr);
        validTopic = isValidGroupTopic(topicStr);
        if (!validTopic) {
            std::cout << outputPreamble
                      << "Not a valid topic, try again." 
                      << std::endl;
        }
    }
    return topicStr;
}



bool QueryHelper::isValidGroupType(const std::string& groupType) {
    return groupType == "Class" ||
            groupType == "DevWork" ||
            groupType == "Research" ||
            groupType == "SelfStudy";
}

bool QueryHelper::isValidGroupName(const std::string& groupName) {
    return groupName.length() > 0;
}

bool QueryHelper::isValidGroupYear(uint16_t groupYear) {
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

bool QueryHelper::isValidGroupSemester(const std::string& semester) {
    return semester == "Spring" ||
        semester == "Fall" ||
        semester == "Summer";
}

bool QueryHelper::isValidGroupTopic(const std::string& topic) {
    return topic == "Math" ||
        topic == "CS" ||
        topic == "Physics" ||
        topic == "Chemistry" ||
        topic == "Biology";
}



std::string QueryHelper::translateGroupType(const std::string& groupType) {
    std::string lowerStr = strToLower(groupType);

    if (lowerStr == "class" ||
            lowerStr == "clas") {
        return "Class";
    } else if (lowerStr == "devwork" ||
            lowerStr == "dvwork" ||
            lowerStr == "devwrk") {
        return "DevWork";
    } else if (lowerStr == "research" ||
            lowerStr == "rsearch" ||
            lowerStr == "reserch") {
        return "Research";
    } else if (lowerStr == "selfstudy" ||
            lowerStr == "slfstudy" ||
            lowerStr == "selfstdy") {
        return "SelfStudy";
    } else {
        return groupType;
    }
}

std::string QueryHelper::translateSemester(const std::string& semester) {
    std::string lowerStr = strToLower(semester);

    if (lowerStr == "spring") {
        return "Spring";
    } else if (lowerStr == "fall") {
        return "Fall";
    } else if (lowerStr == "summer") {
        return "Summer";
    } else {
        return semester;
    }
}

std::string QueryHelper::translateTopic(const std::string& topic) {
    std::string lowerStr = strToLower(topic);

    if (lowerStr == "cs" || 
            lowerStr == "comp sci" ||
            lowerStr == "computer science") {
        return "CS"; 
    } else if (lowerStr == "math" || 
            lowerStr == "mat" ||
            lowerStr == "mathematics") {
        return "Math";
    } else if (lowerStr == "physics" || 
            lowerStr == "physic" || 
            lowerStr == "phy") { 
        return "Physics";
    } else if (topic == "chemistry" || 
            lowerStr == "chem") {
        return "Chemistry";
    } else if (topic == "biology" || 
            lowerStr == "bio") {
        return "Biology";
    } else {
        return topic;
    }
}

Semester QueryHelper::strToSemester(const std::string& semester) {
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

Topic QueryHelper::strToTopic(const std::string& topic) {
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



std::string QueryHelper::translateTaskType(const std::string& taskType) {
    std::string lowerStr = strToLower(taskType);

    if (lowerStr == "chore" ||
            lowerStr == "chre") {
        return "Chore";
    } else if (lowerStr == "exam" ||
            lowerStr == "exm") {
        return "Exam";
    } else if (lowerStr == "homework" ||
            lowerStr == "hw" ||
            lowerStr == "homwork" ||
            lowerStr == "homweork" ||
            lowerStr == "homewrk") {
        return "Homework";
    } else if (lowerStr == "labassignment" ||
            lowerStr == "labasignment" ||
            lowerStr == "labassignmnt" ||
            lowerStr == "labasignmnt") {
        return "LabAssignment";
    } else if (lowerStr == "notes" ||
            lowerStr == "note") {
        return "Notes";
    } else if (lowerStr == "presentation" ||
            lowerStr == "presntation" ||
            lowerStr == "prsentation" ||
            lowerStr == "prsntation") {
        return "Presentation";
    } else if (lowerStr == "programming" ||
            lowerStr == "progaming" ||
            lowerStr == "prgramming" ||
            lowerStr == "prgraming") {
        return "Programming";
    } else if (lowerStr == "project" ||
            lowerStr == "prject" ||
            lowerStr == "projct") {
        return "Project";
    } else if (lowerStr == "quiz" ||
            lowerStr == "quz") {
        return "Quiz";
    } else if (lowerStr == "reading" ||
            lowerStr == "readng" ||
            lowerStr == "reding") {
        return "Reading";
    } else {
        return taskType;
    }
}



std::string QueryHelper::strToLower(const std::string& str) {
    std::string copy = str;
    for (char& c : copy) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return copy;
}
