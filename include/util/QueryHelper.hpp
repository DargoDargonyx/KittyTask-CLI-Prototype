#ifndef QUERYHELPER_H
#define QUERYHELPER_H

// Built in libraries
#include <string>


class QueryHelper {
    private:
        // Fields
        std::string logPreamble;
        // Utility
        bool isValidGroupName(const std::string& groupName);
        bool isValidGroupYear(int groupYear);
        bool isValidTaskName(const std::string& taskName);
        bool isValidDate(const std::string& date);
        std::string strToLower(const std::string& str);
        std::string translateYesNo(const std::string& str);
        std::string addDaysToDate(const std::string& date, int days);
        std::string buildDateStr(int day, int month, int year);
        std::string getTodaysDateStr();
        bool isDateInRange(const std::string& date, 
                const std::string& lower, const std::string& upper);
    public:
        // Constructor
        QueryHelper(const std::string& logPreamble);
        // Queries
        std::string queryGroupType();
        std::string queryGroupName();
        int queryGroupYear();
        std::string queryGroupSemester();
        std::string queryGroupTopic();
        bool queryRemAllGroups();
        std::string queryTaskType();
        std::string queryTaskName();
        std::string queryTaskDate();
        bool queryRemAllTasks();
        // Utility
        bool isValidGroupType(const std::string& groupType);
        bool isValidSemester(const std::string& semester);
        bool isValidTopic(const std::string& topic);
        bool isValidTaskType(const std::string& taskType);
        bool isValidTaskDate0(const std::string& date);
        bool isValidTaskDate1(const std::string& date);
        bool isValidTaskDate2(const std::string& date);
        bool isValidTaskDate3(const std::string& date);
        std::string translateGroupType(const std::string& groupType);
        std::string translateSemester(const std::string& semester);
        std::string translateTopic(const std::string& topic);
        std::string translateTaskType(const std::string& taskType);
};

#endif //QUERYHELPER_H
