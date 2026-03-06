// Utility header file
#include "util/DataManager.hpp"
#include "util/QueryHelper.hpp"

// Built in libraries
#include <string>
#include <vector>
#include <memory>


class CommandHelper {
    private:
        std::string filepath;
        std::string logPreamble;
        std::unique_ptr<DataManager> manager;
        std::unique_ptr<QueryHelper> qHelper;
    public:
        CommandHelper(
            const std::string& filepath, 
            const std::string& outputPreamble
        );
        // Commands for groups
        void listGroupsCommand(
            std::string filterType, 
            std::string filterSemester, 
            std::string filterTopic
        );
        void addGroupCommand();
        void removeGroupCommand(
            std::string groupName, 
            bool remAll, 
            std::string filterType, 
            std::string filterSemester, 
            std::string filterTopic
        );       
        // Commands for tasks
        void listTasksCommand(
            std::string groupName, 
            std::string filterType, 
            bool dateFlag,
            bool date1Flag,
            bool date2Flag, 
            bool date3Flag
        );
        void addTaskCommand(std::string groupName);
        void removeTaskCommand(
            std::string groupName,
            std::string taskName,
            std::string filterType,
            bool allFlag,
            bool statusFlag
        );
        void countTasksCommand(
            std::string groupName,
            std::string filterType,
            bool allFlag,
            bool statusFlag,
            bool date1Flag,
            bool date2Flag,
            bool date3Flag
        );
};
