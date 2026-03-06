#ifndef DATAMANAGER_H
#define DATAMANAGER_H

// Group & Task header files
#include "groups/Group.hpp"
#include "tasks/Task.hpp"

// Utility header file
#include "external/json.hpp"

// Built in libraries
#include <string>
#include <vector>
#include <memory>

using json = nlohmann::json;


class DataManager {
    private:
        // Fields
        std::string filepath;
        std::string groupDataPath;
        std::string logPreamble;
        json groupData;
        std::vector<json> taskFiles;
        // Helper functions
        std::string getTaskFilePath(int groupId);
        std::unique_ptr<Group> buildGroup(int groupId);
        std::unique_ptr<Task> buildTask(int groupId, int taskId);
        void saveGroupData();
        void saveTaskFile(int groupId);
    public:
        // Constructor
        DataManager(
            const std::string& filepath, 
            const std::string& logPreamble
        );
        void checkDataDirectory();
        std::vector<std::unique_ptr<Group>> loadGroupData();
        std::vector<std::unique_ptr<Task>> loadTaskFile(int groupId);
        int getGroupIdFromName(const std::string& groupName);
        void addGroup(std::unique_ptr<Group> newGroup);
        void removeGroup(int groupId);
        void clearAllGroups();
        int getTaskIdFromName(int groupId, const std::string& taskName);
        void addTask(int groupId, std::unique_ptr<Task> newTask);
        void removeTask(int groupId, int taskId);
        void clearAllTasks(int groupId);
};

#endif //DATAMANAGER_H
