// Utility header files
#include "util/QueryHelper.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"

// Built in libraries
#include <string>
#include <cstdint>
#include <iostream>
#include <chrono>


//==================================
//========== Constructor ===========
//==================================

/**
 * @brief A one argument constructor for the class.
 * @param outputPreamble The preamble for any text outputs.
 */
QueryHelper::QueryHelper(const std::string& outputPreamble) {
    this->outputPreamble = outputPreamble;
}



//==============================
//========== Queries ===========
//==============================


/**
 * @brief Handles the logic for querying the user for a group type.
 * @return A string representation of the group type in question.
 */
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
                      << "Not a valid type, please try again." 
                      << std::endl;
        }
    }
    return groupType;
}

/**
 * @brief Handles the logic for querying the user for a group name.
 * @return A string representation of the group name in question.
 */
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
                      << "Not a valid name, please try again. A name must be a non zero string that isn't already taken as a group name" 
                      << std::endl;
        }
    }
    return groupName;
}

/**
 * @brief Handles the logic for querying the user for a group year.
 * @return A 16 bit unsigned integer representation of the group 
 * year in question.
 */
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

/**
 * @brief Handles the logic for querying the user for a group Semester.
 * @return A string representation of the group Semester in question.
 */
std::string QueryHelper::queryGroupSemester() {
    std::string semesterStr;
    bool validSemester = false;
    while (!validSemester) {
        std::cout << outputPreamble
                  << "Enter a semester type (Spring, Fall, Summer): ";
        std::getline(std::cin, semesterStr);
        semesterStr = translateSemester(semesterStr);
        validSemester = isValidSemester(semesterStr);
        if (!validSemester) {
            std::cout << outputPreamble
                      << "Not a valid semester, please try again." 
                      << std::endl;
        }
    }
    return semesterStr;
}

/**
 * @brief Handles the logic for querying the user for a group Topic.
 * @return A string representation of the group Topic in question.
 */
std::string QueryHelper::queryGroupTopic() {
    std::string topicStr;
    bool validTopic = false;
    while (!validTopic) {
        std::cout << outputPreamble
                  << "Enter a topic type: ";
        std::getline(std::cin, topicStr);
        topicStr = translateTopic(topicStr);
        validTopic = isValidTopic(topicStr);
        if (!validTopic) {
            std::cout << outputPreamble
                      << "Not a valid topic, please try again." 
                      << std::endl;
        }
    }
    return topicStr;
}

/**
 * @brief Handles the logic for querying the user on whether or not
 * they actually want to remove all groups.
 * @return A string representation of "y" for yes and "n" for no of
 * whether or not the user wants to remove all groups.
 */
std::string QueryHelper::queryRemAllGroups() {
    std::string response;
    bool validResponse = false;
    while (!validResponse) {
        std::cout << outputPreamble
                  << "Are you sure that you want to remove all groups? (y/n): ";
        std::getline(std::cin, response);
        response = translateYesNo(response);
        validResponse = isValidYesNo(response);
        if (!validResponse) {
            std::cout << outputPreamble
                      << "Not a valid response, please try again."
                      << std::endl;
        }
    }
    return response;
}



//==============================
//========== Utility ===========
//==============================


/**
 * @brief Checks whether or not a given group type is valid.
 * @param groupType A string representation of the group
 * type in question.
 * @return A boolean representation of whether or not the group
 * type in question is valid.
 */
bool QueryHelper::isValidGroupType(const std::string& groupType) {
    return groupType == "Class" ||
            groupType == "DevWork" ||
            groupType == "Research" ||
            groupType == "SelfStudy";
}

/**
 * @brief Checks whether or not a given group name is valid.
 * @param groupName A string representation of the group
 * name in question.
 * @return A boolean representation of whether or not the group
 * name in question is valid.
 */
bool QueryHelper::isValidGroupName(const std::string& groupName) {
    return groupName.length();
}

/**
 * @brief Checks whether or not a given group year is valid.
 * @param groupYear An 8 bit unsigned integer representation of
 * the group year in question.
 * @return A boolean representation of whether or not the group
 * year in question is valid.
 */
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

/**
 * @brief Checks whether or not a given group Semester is valid.
 * @param semester A string representation of the group
 * Semester in question.
 * @return A boolean representation of whether or not the group
 * Semester in question is valid.
 */
bool QueryHelper::isValidSemester(const std::string& semester) {
    return semester == "Spring" ||
        semester == "Fall" ||
        semester == "Summer";
}

/**
 * @brief Checks whether or not a given group Topic is valid.
 * @param topic A string representation of the group Topic
 * in question.
 * @ return A boolean representation of whether or not the group
 * Topic in question is valid.
 */
bool QueryHelper::isValidTopic(const std::string& topic) {
    return topic == "Math" ||
        topic == "CS" ||
        topic == "Physics" ||
        topic == "Chemistry" ||
        topic == "Biology";
}

/**
 * @brief Checks whether or not a given input is a valid yes or no.
 * @param str The given input in question.
 * @return A boolean representation of whether or not the given input
 * in question is valid.
 */
bool QueryHelper::isValidYesNo(const std::string& str) {
    return str == "y" || str == "n";
}

/**
 * @brief Translates the given input into a proper group type if one
 * is detected.
 * @param groupType The given input in question.
 * @return A string representation of the proper group type in question
 * if one is available, and if not the original input is returned.
 */
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

/**
 * @brief Translates the given input into a proper task type if one
 * is detected.
 * @param taskType The given input in question.
 * @return A string representation of the proper task type in question
 * if one is available, and if not the original input is returned.
 */
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

/**
 * @brief Translates the given input into a proper group Semester 
 * if one is detected.
 * @param semester The given input in question.
 * @return A string representation of the proper group Semester 
 * in question if one is available, and if not the original 
 * input is returned.
 */
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

/**
 * @brief Translates the given input into a proper group Topic 
 * if one is detected.
 * @param topic The given input in question.
 * @return A string representation of the proper group Topic 
 * in question if one is available, and if not the original 
 * input is returned.
 */
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

/**
 * @brief Translates a string into a Semester object.
 * @param semester The string in question.
 * @return The Semester object in question.
 */
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

/**
 * @brief Translates a string into a Topic object.
 * @param topic The string in question.
 * @return The Topic object in question.
 */
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

/**
 * @brief Translates a string into a proper yes or no if available.
 * @param str The string in question.
 * @return A proper yes or no if available, if not the original
 * input string is returned.
 */
std::string QueryHelper::translateYesNo(const std::string& str) {
    std::string lowerStr = strToLower(str);
    if (lowerStr == "y" || lowerStr == "yes") {
        return "y";
    } else if (lowerStr == "n" || lowerStr == "no") {
        return "n";
    } else {
        return str;
    }
}

/**
 * @brief Transforms a given string into all lowercase letters.
 * @param The given string in question.
 * @return The transformed string that is all lowercase.
 */
std::string QueryHelper::strToLower(const std::string& str) {
    std::string copy = str;
    for (char& c : copy) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return copy;
}
