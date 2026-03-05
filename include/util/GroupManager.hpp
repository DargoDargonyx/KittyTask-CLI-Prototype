#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

// Group & Task header files
#include "groups/Group.hpp"
#include "tasks/Task.hpp"

// Utility & External header files
#include "external/json.hpp"

// Built in libraries
#include <string>
#include <vector>
#include <memory>

using json = nlohmann::json;


class GroupManager {
    private:
        // Fields
        std::string filepath;
        std::string outputPreamble;
        json data;
        std::vector<std::unique_ptr<Group>> groups;
        // IO handling
        void checkDataDirectory();
        void loadGroupData();
        void saveGroupData();
        // Translating JSON to objects
        std::unique_ptr<Group> buildGroup(int groupId);
        std::unique_ptr<Task> buildTask(const json& taskfile, int taskId);
        void refreshGroups();
    public:
        // Constructor
        GroupManager(
            const std::string& filepath, 
            const std::string& outputPreamble
        );
        // Accessors
        const std::vector<std::unique_ptr<Group>>& getGroups();
        const std::vector<std::unique_ptr<Task>>& getTasks(const std::string& groupName);
        Group* getGroupFromId(int groupId);
        Group* getGroupFromName(const std::string& groupName);
        Task* getTaskFromId(const std::string& groupName, int taskId);
        bool containsGroup(const std::string& groupName);
        bool containsTask(const std::string& groupName, const std::string& taskName);
        // Mutators
        void setGroups(std::vector<std::unique_ptr<Group>>&& newGroups);
        void addGroup(std::unique_ptr<Group> newGroup);
        void removeGroup( int groupId);
        void clearAllGroups();
        void addTask(const std::string& groupName, std::unique_ptr<Task> newTask);
        void removeTask(const std::string& groupName, int taskId);
        void clearAllTasks(const std::string& groupName);
};

#endif //GROUPMANAGER_H
