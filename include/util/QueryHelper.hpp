#ifndef QUERYHELPER_H
#define QUERYHELPER_H

#include "util/Semester.hpp"
#include "util/Topic.hpp"
#include <string>
#include <cstdint>

class QueryHelper {
    private:
        std::string outputPreamble;
        bool isValidGroupName(const std::string& groupName);
        bool isValidGroupYear(uint16_t groupType);
        std::string strToLower(const std::string& str);
    public:
        QueryHelper(const std::string& outputPreamble);
        std::string queryGroupType();
        std::string queryGroupName();
        uint16_t queryGroupYear();
        std::string queryGroupSemester();
        std::string queryGroupTopic();
        bool isValidGroupType(const std::string& groupType);
        bool isValidSemester(const std::string& semester);
        bool isValidTopic(const std::string& topic);
        std::string translateGroupType(const std::string& groupType);
        std::string translateSemester(const std::string& semester);
        std::string translateTopic(const std::string& topic);
        std::string translateTaskType(const std::string& taskType);
        Semester strToSemester(const std::string& semester);
        Topic strToTopic(const std::string& topic);
};

#endif //QUERYHELPER_H
