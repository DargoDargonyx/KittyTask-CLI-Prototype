#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include "external/json.hpp"
#include "groups/Group.hpp"
#include "tasks/Task.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"

#include <string>
#include <vector>
#include <memory>

using json = nlohmann::json;

class GroupManager {
    private:
        std::string filepath;
        std::string outputPreamble;
        json data;
        std::vector<std::unique_ptr<Group>> groups;
        void checkDataDirectory();
        void loadGroupData();
        void saveGroupData();
        std::unique_ptr<Group> buildGroup(const int groupId);
        std::unique_ptr<Task> buildTask(const json& taskfile, const int taskId);
        Semester jsonStrToSemester(const int groupId);
        Topic jsonStrToTopic(const int groupId);
        void refreshGroups();
    public:
        GroupManager(
            const std::string& filepath, 
            const std::string& outputPreamble
        );
        const std::vector<std::unique_ptr<Group>>& getGroups() const;
        void setGroups(std::vector<std::unique_ptr<Group>>&& newGroups);
        void addGroup(std::unique_ptr<Group> newGroup);
        void removeGroup(const int groupId);
        void clearAllGroups();
        bool containsGroup(const std::string& groupName);
        Group* getGroupFromId(const int groupId);
        Group* getGroupFromName(const std::string& groupName);
};

#endif //GROUPMANAGER_H
