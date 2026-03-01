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
        bool isValidGroupSemester(const std::string& semester);
        bool isValidGroupTopic(const std::string& topic);
        std::string translateSemester(const std::string& semester);
        std::string translateTopic(const std::string& topic);
        std::string translateTaskType(const std::string& taskType);
        std::string strToLower(const std::string& str);
    public:
        QueryHelper(const std::string& outputPreamble);
        std::string queryGroupType();
        std::string queryGroupName();
        uint16_t queryGroupYear();
        std::string queryGroupSemester();
        std::string queryGroupTopic();
        bool isValidGroupType(const std::string& groupType);
        std::string translateGroupType(const std::string& groupType);
        Semester strToSemester(const std::string& semester);
        Topic strToTopic(const std::string& topic);
};

#endif //QUERYHELPER_H
