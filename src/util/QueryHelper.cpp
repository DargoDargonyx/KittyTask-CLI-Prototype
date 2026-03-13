// Utility header files
#include "util/QueryHelper.hpp"

// Built in libraries
#include <string>
#include <tuple>
#include <chrono>
#include <format>
#include <cstdio>
#include <iostream>



/**
 * @brief A one argument constructor for the class.
 * @param outputPreamble The preamble for any text outputs.
 */
QueryHelper::QueryHelper(const std::string& logPreamble) 
    : logPreamble(logPreamble) {}

/**
 * @brief Handles the logic for querying the user for a group type.
 * @return A string representation of the group type in question.
 */
std::string QueryHelper::queryGroupType() {
    std::string groupType;
    bool validType = false;
    while (!validType) {
        printf("%sEnter a group type: ", logPreamble.c_str());
        std::getline(std::cin, groupType);
        groupType = translateGroupType(groupType);
        validType = isValidGroupType(groupType);
        if (!validType) {
            printf("%sInvalid type, please try again. If you need to, please see \
                    the help menu for possible group types.\n", logPreamble.c_str());
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
        printf("%sEnter a group name: ", logPreamble.c_str());
        std::getline(std::cin, groupName);
        validName = isValidGroupName(groupName);
        if (!validName) {
            printf("%sInvalid name, please try again. A name must be a non zero string \
                    that isn't already taken as a group name.\n", logPreamble.c_str());
        }
    }
    return groupName;
}

/**
 * @brief Handles the logic for querying the user for a group year.
 * @return A 16 bit unsigned integer representation of the group 
 * year in question.
 */
int QueryHelper::queryGroupYear() {
    int groupYear;
    std::string yearStr;
    bool validYear = false;
    while (!validYear) {
        printf("%sEnter a year for the group: ", logPreamble.c_str());
        std::getline(std::cin, yearStr);
        try {
            groupYear = std::stoi(yearStr);
        } catch (...) {
            printf("%sERROR, couldn't convert the given year into an integer.\n", 
                    logPreamble.c_str());
            groupYear = 0;
        }
        validYear = isValidGroupYear(groupYear);
        if (!validYear) {
            printf("%sInvalid year, please try again. A year must be a proper integer \
                    representation of a year within 10 years of the current year.\n",
                    logPreamble.c_str());
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
        printf("%sEnter a semester type: ", logPreamble.c_str());
        std::getline(std::cin, semesterStr);
        semesterStr = translateSemester(semesterStr);
        validSemester = isValidSemester(semesterStr);
        if (!validSemester) {
            printf("%sInvalid semester, please try again. If you need to, please the help \
                    menu for possible semester options.\n", logPreamble.c_str());
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
        printf("%sEnter a topic type: ", logPreamble.c_str());
        std::getline(std::cin, topicStr);
        topicStr = translateTopic(topicStr);
        validTopic = isValidTopic(topicStr);
        if (!validTopic) {
            printf("%sInvalid topic, please try again. If you need to, please see the help \
                    menu for possible topic options.\n", logPreamble.c_str());
        }
    }
    return topicStr;
}

/**
 * @brief Handles the logic for querying the user on whether or not
 * they actually want to remove all groups.
 * @return A boolean representation of the users response where true
 * means yes and false means no.
 */
bool QueryHelper::queryRemAllGroups() {
    std::string response;
    while (true) {
        printf("%sAre you sure that you want to remove all groups? (y/n): ", 
                logPreamble.c_str());
        std::getline(std::cin, response);
        response = translateYesNo(response);
        if (response == "y") return true;
        else if (response == "n") return false;
        printf("%sInvalid response, please try again.\n", logPreamble.c_str());
    }
}

/**
 * @brief Handles the logic for querying the user on whether or not
 * they actually want to remove all tasks in a group.
 * @return A boolean representation of the users response where true
 * means yes and false means no.
 */
bool QueryHelper::queryRemAllTasks() {
    std::string response;
    while (true) {
        printf("%sAre you sure that you want to remove all tasks? (y/n): ", 
                logPreamble.c_str());
        std::getline(std::cin, response);
        response = translateYesNo(response);
        if (response == "y") return true;
        else if (response == "n") return false;
        printf("%sInvalid response, please try again.\n", logPreamble.c_str());
    }
}

/**
 * @brief Handles the logic for querying the user for a task type.
 * @return A string representation of the task type in question.
 */
std::string QueryHelper::queryTaskType() {
    std::string taskType;
    bool validType = false;
    while (!validType) {
        printf("%sEnter a task type: ", logPreamble.c_str());
        std::getline(std::cin, taskType);
        taskType = translateTaskType(taskType);
        validType = isValidTaskType(taskType);
        if (!validType) {
            printf("%sInvalid type, please try again. If you need to, please see the \
                    help menu for possible task types.\n", logPreamble.c_str());
        }
    }
    return taskType;
}

/**
 * @brief Handles the logic for querying the user for a task name.
 * @return A string representation of the task name in question.
 */
std::string QueryHelper::queryTaskName() {
    std::string taskName;
    bool validName = false;
    while (!validName) {
        printf("%sEnter a task name: ", logPreamble.c_str());
        std::getline(std::cin, taskName);
        validName = isValidTaskName(taskName);
        if (!validName) {
            printf("%sInvalid name, please try again. A name must be a non zero string \
                    that isn't already taken as a task name in the group.\n",
                    logPreamble.c_str());
        }
    }
    return taskName;
}

/**
 * @brief Handles the logic for querying the user for a task date.
 * @return A string representation of the task date in question.
 */
std::string QueryHelper::queryTaskDate() {
    std::string taskDate;
    bool validDate = false;
    while (!validDate) {
        printf("%sEnter a task date (MM/DD/YYYY): ", logPreamble.c_str());
        std::getline(std::cin, taskDate);
        validDate = isValidDate(taskDate);
        if (!validDate) {
            printf("%sInvalid date, please try again. A date must be formatted as (MM/DD/YYYY).\n",
                    logPreamble.c_str());
        }
    }
    return taskDate;
}

/**
 * @brief Checks whether or not a given group type is valid.
 * @param groupType A string representation of the group
 * type in question.
 * @return A boolean representation of whether or not the group
 * type in question is valid.
 */
bool QueryHelper::isValidGroupType(const std::string& groupType) {
    return groupType == "Class" || groupType == "DevWork" ||
        groupType == "Research" || groupType == "SelfStudy";
}

/**
 * @brief Checks whether or not a given group name is valid.
 * @param groupName A string representation of the group
 * name in question.
 * @return A boolean representation of whether or not the group
 * name in question is valid.
 */
bool QueryHelper::isValidGroupName(const std::string& groupName) {
    return groupName.length() > 0;
}

/**
 * @brief Checks whether or not a given group year is valid.
 * @param groupYear An 8 bit unsigned integer representation of
 * the group year in question.
 * @return A boolean representation of whether or not the group
 * year in question is valid.
 */
bool QueryHelper::isValidGroupYear(int groupYear) {
    std::string today = getTodaysDateStr();
    int currentYear = std::stoi(today.substr(6, 4));
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
    return semester == "Spring" || semester == "Fall" ||
        semester == "Summer";
}

/**
 * @brief Checks whether or not a given group Topic is valid.
 * @param topic A string representation of the group Topic
 * in question.
 * @return A boolean representation of whether or not the group
 * Topic in question is valid.
 */
bool QueryHelper::isValidTopic(const std::string& topic) {
    return topic == "Math" || topic == "CS" ||
        topic == "Physics" || topic == "Chemistry" ||
        topic == "Biology";
}

/**
 * @brief Checks whether or not a given task type is valid.
 * @param taskType A string representation of the task
 * type in question.
 * @return A boolean representation of whether or not the task
 * type in question is valid.
 */
bool QueryHelper::isValidTaskType(const std::string& taskType) {
    return taskType == "Chore" || taskType == "Exam" ||
        taskType == "Homework" || taskType == "Lab" ||
        taskType == "LabAssignment" || taskType == "Notes" ||
        taskType == "Presentation" || taskType == "Programming" ||
        taskType == "Project" || taskType == "Quiz" ||
        taskType == "Reading";
}

/**
 * @brief Checks whether or not a given task name is valid.
 * @param taskName A string representation of the task
 * name in question.
 * @return A boolean representation of whether or not the task
 * name in question is valid.
 */
bool QueryHelper::isValidTaskName(const std::string& taskName) {
    return taskName.length() > 0;
}

/**
 * @brief Checks whether or not a given date is valid
 * with regards to an American format.
 * @param date The given date in question.
 * @return A boolean representation of whether or not the
 * date in question is valid.
 */
bool QueryHelper::isValidDate(const std::string& date) {
    try {
        // Must be in MM/DD/YYYY format
        if (date.length() != 10 || date[2] != '/' || date[5] != '/')
            return false;
        
        int d = std::stoi(date.substr(3, 2));
        int m = std::stoi(date.substr(0, 2));
        int y = std::stoi(date.substr(6, 4));
        int dayThreshold;
        
        // Months with 31 days
        if (m == 1 || m == 3 || m == 5 || 
                m == 7 || m == 8 || m == 10 || m == 12) {
            dayThreshold = 31;
        // Months with 30 days
        } else if (m == 4 || m == 6 || m == 9 || m == 11) {
            dayThreshold = 30;
        // Februrary
        } else if (m == 2) {
            if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) dayThreshold = 29;
            else dayThreshold = 28;
        } else {
            return false;
        }

        return d <= dayThreshold && d > 0 && y > 0;
    } catch (...) {
        return false;
    }
}

/**
 * @brief Checks whether or not a given task date is valid
 * in relation to the date0 flag.
 * @param date The given task date in question.
 * @return A boolean representation of whether or not the
 * task date in question is valid.
 */
bool QueryHelper::isValidTaskDate0(const std::string& date) {
    int d = std::stoi(date.substr(3, 2));
    int m = std::stoi(date.substr(0, 2));
    int y = std::stoi(date.substr(6, 4));
    std::string today = getTodaysDateStr();
    int tD = std::stoi(today.substr(3, 2));
    int tM = std::stoi(today.substr(0, 2));
    int tY = std::stoi(today.substr(6, 4));

    std::tuple<int, int, int> dateTup  = std::make_tuple(y, m, d);
    std::tuple<int, int, int> todayTup = std::make_tuple(tY, tM, tD);

    return dateTup >= todayTup;
}

/**
 * @brief Checks whether or not a given task date is valid
 * in relation to the date1 flag.
 * @param date The given task date in question.
 * @return A boolean representation of whether or not the
 * task date in question is valid.
 */
bool QueryHelper::isValidTaskDate1(const std::string& date) {
    if (!isValidDate(date)) return false;
    std::string today = getTodaysDateStr();
    std::string expectedDay = addDaysToDate(today, 10);
    return isDateInRange(date, today, expectedDay);
}

/**
 * @brief Checks whether or not a given task date is valid
 * in relation to the date2 flag.
 * @param date The given task date in question.
 * @return A boolean representation of whether or not the
 * task date in question is valid.
 */
bool QueryHelper::isValidTaskDate2(const std::string& date) {
    if (!isValidDate(date)) return false;
    std::string today = getTodaysDateStr();
    std::string expectedDay = addDaysToDate(today, 30);
    return isDateInRange(date, today, expectedDay);
}

/**
 * @brief Checks whether or not a given task date is valid
 * in relation to the date3 flag.
 * @param date The given task date in question.
 * @return A boolean representation of whether or not the
 * task date in question is valid.
 */
bool QueryHelper::isValidTaskDate3(const std::string& date) {
    if (!isValidDate(date)) return false;
    std::string today = getTodaysDateStr();
    std::string expectedDay = addDaysToDate(today, 90);
    return isDateInRange(date, today, expectedDay);
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

    if (lowerStr == "spring") return "Spring";
    else if (lowerStr == "fall") return "Fall";
    else if (lowerStr == "summer") return "Summer";
    else return semester;
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
 * @brief Translates a string into a proper yes or no if available.
 * @param str The string in question.
 * @return A proper yes or no if available, if not the original
 * input string is returned.
 */
std::string QueryHelper::translateYesNo(const std::string& str) {
    std::string lowerStr = strToLower(str);
    if (lowerStr == "y" || lowerStr == "yes") return "y";
    else if (lowerStr == "n" || lowerStr == "no") return "n";
    else return str;
}

/**
 * @brief Adds a number of days to given date string to help
 * with date validty checker functions.
 * @param date
 */
std::string QueryHelper::addDaysToDate(const std::string& date, int days) {
    // MM/DD/YYYY
    int d = std::stoi(date.substr(3, 2));
    int m = std::stoi(date.substr(0, 2));
    int y = std::stoi(date.substr(6, 4));
    d += days;

    while (true) {
        bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        int daysInMonth;
        if (m == 2) daysInMonth = leap ? 29 : 28;
        else if (m == 4 || m == 6 || m == 9 || m == 11) daysInMonth = 30;
        else daysInMonth = 31;

        if (d <= daysInMonth) break;
        d -= daysInMonth;
        m++;

        if (m > 12) {
            m = 1;
            y++;
        }
    }

    return buildDateStr(d, m, y);
}

/**
 * @brief Transforms a set of integers into a date string in order
 * to reduce on repeated code in the class. This string is currently
 * built in an American format (may change later).
 * @param day The day integer.
 * @param month The month integer.
 * @param year The year integer.
 * @return The date string in American format.
 */
std::string QueryHelper::buildDateStr(int day, int month, int year) {
    return std::format("{:02}/{:02}/{:04}", month, day, year);
}

/**
 * @brief Gets the current date in a nice formatted string,
 * using the American time format.
 * @return The date in question as a string.
 */
std::string QueryHelper::getTodaysDateStr() {
    using namespace std::chrono;
    auto today = floor<days>(system_clock::now());
    year_month_day ymd = year_month_day{today};
    return std::format("{:02}/{:02}/{:04}", unsigned(ymd.month()),
            unsigned(ymd.day()), int(ymd.year()));
}

/**
 * @brief Checks whether or not a given date is a range between
 * two other given dates inclusively (expects the dates to be valid).
 * @param date The date in question.
 * @param lower The lower bound as a date for the range.
 * @param upper The upper bound as a date for the range.
 * @return A boolean representation of whether or not the date
 * in question is in between the range of dates given.
 */
bool QueryHelper::isDateInRange(const std::string& date, 
        const std::string& lower, const std::string& upper) {

    int d = std::stoi(date.substr(3, 2));
    int m = std::stoi(date.substr(0, 2));
    int y = std::stoi(date.substr(6, 4));
    int lD = std::stoi(lower.substr(3, 2));
    int lM = std::stoi(lower.substr(0, 2));
    int lY = std::stoi(lower.substr(6, 4));
    int uD = std::stoi(upper.substr(3, 2));
    int uM = std::stoi(upper.substr(0, 2));
    int uY = std::stoi(upper.substr(6, 4));

    // Apparently tuples compare from left to right
    // which tells us if the date is in the range
    std::tuple<int, int, int> dateTup  = std::make_tuple(y, m, d);
    std::tuple<int, int, int> lowerTup = std::make_tuple(lY, lM, lD);
    std::tuple<int, int, int> upperTup = std::make_tuple(uY, uM, uD);

    return dateTup >= lowerTup && dateTup <= upperTup;
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
