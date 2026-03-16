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
        void moveTaskFile(int origGroupId, int newGroupId);
    public:
        // Constructor
        DataManager(
            const std::string& filepath, 
            const std::string& logPreamble
        );
        void checkDataDirectory();
        // Groups
        std::vector<std::unique_ptr<Group>> loadGroupData();
        int getGroupIdFromName(const std::string& groupName);
        void sortGroupsByDate();
        void sortGroupsBySemester();
        void sortGroupsByTopic();
        void addGroup(std::unique_ptr<Group> newGroup);
        void removeGroup(int groupId);
        void clearAllGroups();
        bool setGroupGrade(int groupId, int value);
        // Tasks
        std::vector<std::unique_ptr<Task>> loadTaskFile(int groupId);
        int getTaskIdFromName(int groupId, const std::string& taskName);
        void sortTasks(int groupId);
        void addTask(int groupId, std::unique_ptr<Task> newTask);
        void removeTask(int groupId, int taskId);
        void clearAllTasks(int groupId);
        bool setTaskGrade(int groupId, int taskId, int value);
};

#endif //DATAMANAGER_H
