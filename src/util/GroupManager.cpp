// Group header files
#include "groups/Group.hpp"
#include "groups/Class.hpp"
#include "groups/DevWork.hpp"
#include "groups/Research.hpp"
#include "groups/SelfStudy.hpp"

// Task header files
#include "tasks/Task.hpp"
#include "tasks/Chore.hpp"
#include "tasks/Exam.hpp"
#include "tasks/Homework.hpp"
#include "tasks/Lab.hpp"
#include "tasks/LabAssignment.hpp"
#include "tasks/Notes.hpp"
#include "tasks/Presentation.hpp"
#include "tasks/Programming.hpp"
#include "tasks/Project.hpp"
#include "tasks/Quiz.hpp"
#include "tasks/Reading.hpp"

// Utility & External header files
#include "util/GroupManager.hpp"
#include "external/json.hpp"

// Built in libraries
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>

using json = nlohmann::json;
namespace fs = std::filesystem;



/**
 * @brief Two argument constructor for the class.
 *
 * @param filepath The baseline file path for the data directory.
 * @param outputPreamble The preamble for any text outputs.
 */
GroupManager::GroupManager(
        const std::string& filepath, 
        const std::string& outputPreamble) {

    this->filepath = filepath;
    this->outputPreamble = outputPreamble;
    checkDataDirectory();
    loadGroupData();
}



/**
 * @brief Ensures that the data directory exists and that it
 * contains a subdirectory for the task json files.
 */
void GroupManager::checkDataDirectory() {
    try {
        bool dataCreated = fs::create_directories(filepath);
        if (dataCreated) {
            std::cout << outputPreamble << "Directory created: " 
                      << filepath << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << outputPreamble << "ERROR when creating directory \"" 
                  << filepath << "\": " << e.what() << std::endl;
    }

    try {
        bool tasksCreated = fs::create_directories(filepath + "tasks/");
        if (tasksCreated) {
            std::cout << outputPreamble << "Directory created: " 
                      << filepath << "tasks/" << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << outputPreamble << "ERROR when creating directory \""
                  << filepath << "/tasks\": " << e.what() << std::endl;
    }
}

/**
 * @brief Loads the data from the json files in the data directory.
 */
void GroupManager::loadGroupData() {
    std::ifstream file(filepath + "groupData.json");
    if (file.is_open()) {
        this->data = json::parse(file);
    } else {
        return;
    }
    file.close();
    
    for (int i = 0; i < static_cast<int>(data.size()); i++) {
        std::unique_ptr<Group> group = buildGroup(i);
        std::string idStr = std::to_string(group->getIdNum());
        std::string filename = filepath + "tasks/group"
                                + idStr + "_tasks.json";
        
        std::ifstream taskInFile(filename);
        json taskfile;
        if (taskInFile.is_open()) {
            taskfile = json::parse(taskInFile);
        }
        taskInFile.close();
        
        for (int j = 0; j < static_cast<int>(taskfile.size()); j++) {
            group->addTask(buildTask(taskfile, j));
        }
        groups.push_back(std::move(group));
    }
}

/**
 * @brief Saves the current data in the json files in the data directory.
 */
void GroupManager::saveGroupData() {
    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        Group* group = groups.at(i).get();
        std::string groupType = group->getType();
        data[i]["name"] = group->getName();
        data[i]["type"] = groupType;

        if (groupType == "Class") {
            Class* cGroup = static_cast<Class*>(group);
            data[i]["year"] = cGroup->getYear();
            data[i]["semester"] = cGroup->getSemester();
            data[i]["topic"] = cGroup->getTopic();
            data[i]["grade"] = cGroup->getGrade();
        } else if (groupType == "DevWork") {
            DevWork* dGroup = static_cast<DevWork*>(group);
            data[i]["year"] = dGroup->getYear();
            data[i]["topic"] = dGroup->getTopic();
        } else if (groupType == "Research") {
            Research* rGroup = static_cast<Research*>(group);
            data[i]["year"] = rGroup->getYear();
            data[i]["semester"] = rGroup->getSemester();
            data[i]["topic"] = rGroup->getTopic();
        } else if (groupType == "SelfStudy") {
            SelfStudy* sGroup = static_cast<SelfStudy*>(group);
            data[i]["year"] = sGroup->getYear();
            data[i]["semester"] = sGroup->getSemester();
            data[i]["topic"] = sGroup->getTopic();
        }

        std::string idStr = std::to_string(i);
        std::string filename = filepath + "tasks/group"
                                + idStr + "_tasks.json";
        std::ifstream taskInFile(filename);
        json taskfile;
        if (taskInFile.is_open()) {
            taskfile = json::parse(taskInFile);
        }
        taskInFile.close(); 

        const std::vector<std::unique_ptr<Task>>& tasks = group->getTasks();
        for (int j = 0; j < static_cast<int>(tasks.size()); j++) {
            Task* task = tasks.at(j).get();

            std::string taskType = task->getType();
            taskfile[j]["type"] = taskType;
            taskfile[j]["name"] = task->getName();
            taskfile[j]["date"] = task->getDate();
            taskfile[j]["status"] = task->getStatus();

            // Singular case for the time being
            if (taskType != "Chore") {
                GradedTask* gradedTask = static_cast<GradedTask*>(task);
                taskfile[j]["grade"] = gradedTask->getGrade();
            }
        }

        std::ofstream taskOutFile(filename);
        if (taskOutFile.is_open()) {
            taskOutFile << std::setw(4) << taskfile << std::endl;
        } else {
            std::cerr << outputPreamble
                      << "ERROR when trying to write to group task file"
                      << std::endl;
        }
        taskOutFile.close();
    }

    std::ofstream groupOutFile(filepath + "groupData.json");
    if (groupOutFile.is_open()) {
        groupOutFile << std::setw(4) << data << std::endl;
    } else {
        std::cerr << outputPreamble << "ERROR when trying to write "
                  << "to groupData.json file." << std::endl;
    }
    groupOutFile.close();
}

/**
 * @brief Builds a group from json values.
 * @param groupId The idNum of the group in question.
 * @return A pointer to the newly built group.
 */
std::unique_ptr<Group> GroupManager::buildGroup(int groupId) {
    std::string name = data[groupId]["name"];
    std::string type = data[groupId]["type"];

    if (type == "Class") {
        return std::make_unique<Class>(groupId, name,
                    static_cast<uint16_t>(data[groupId]["year"]),
                    data[groupId]["semester"], data[groupId]["topic"],
                    static_cast<uint16_t>(data[groupId]["grade"]));
    } else if (type == "DevWork") {
        return std::make_unique<DevWork>(groupId, name,
                    static_cast<uint16_t>(data[groupId]["year"]),
                    data[groupId]["topic"]);
    } else if (type == "Research") {
        return std::make_unique<Research>(groupId, name,
                    static_cast<uint16_t>(data[groupId]["year"]),
                    data[groupId]["semester"], data[groupId]["topic"]);
    } else if (type == "SelfStudy") {
        return std::make_unique<SelfStudy>(groupId, name,
                    static_cast<uint16_t>(data[groupId]["year"]),
                    data[groupId]["semester"], data[groupId]["topic"]);
    } else {
        std::cout << outputPreamble << "No known group of type \""
                  << data[groupId]["type"] << "\", using a default type instead..."
                  << std::endl;
        
        return std::make_unique<Group>(groupId, name);
    }
}

/**
 * @brief Builds a task from json values.
 * @param taskfile A reference to a josn object containing the task.
 * @param taskId The idNum of the task in question.
 * @return A pointer to the newly built task.
 */
std::unique_ptr<Task> GroupManager::buildTask(const json& taskfile, 
        int taskId) {
    
    std::string type = taskfile[taskId]["type"];
    std::string name = taskfile[taskId]["name"];
    std::string date = taskfile[taskId]["date"];
    bool status = taskfile[taskId]["status"];
    uint16_t grade;

    if (type == "Chore") {
        return std::make_unique<Chore>(taskId, name, 
                    date, status);
    } else if (type == "Exam") {
        grade = static_cast<uint16_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Exam>(taskId, name, 
                    date, status, grade);
    } else if (type == "Homework") {
        grade = static_cast<uint16_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Homework>(taskId, name, 
                    date, status, grade);
    } else if (type == "Lab") {
        grade = static_cast<uint16_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Lab>(taskId, name, 
                    date, status, grade);
    } else if (type == "LabAssignment") {
        grade = static_cast<uint16_t>(taskfile[taskId]["grade"]);
        return std::make_unique<LabAssignment>(taskId, name, 
                    date, status, grade);
    } else if (type == "Notes") {
        grade = static_cast<uint16_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Notes>(taskId, name, 
                    date, status, grade);
    } else if (type == "Presentation") {
        grade = static_cast<uint16_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Presentation>(taskId, name, 
                    date, status, grade);
    } else if (type == "Programming") {
        grade = static_cast<uint16_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Programming>(taskId, name, 
                    date, status,grade);
    } else if (type == "Project") {
        grade = static_cast<uint16_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Project>(taskId, name, 
                    date, status,grade);
    } else if (type == "Quiz") {
        grade = static_cast<uint16_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Quiz>(taskId, name, 
                    date, status,grade);
    } else if (type == "Reading") {
        grade = static_cast<uint16_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Reading>(taskId, name, 
                    date, status, grade);
    } else {
        std::cout << outputPreamble << "Unknown task type of \"" << type 
                  << "\", using a default type instead..." << std::endl;
        return std::make_unique<Task>(taskId, name, date, status);
    }
}

/**
 * @brief Refreshes the idNum of all groups in the groups field.
 */
void GroupManager::refreshGroups() {
    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        groups.at(i)->setIdNum(i);
    }
    saveGroupData();
}

/**
 * @brief An accessor for the groups field.
 * @return A reference to the groups field.
 */
const std::vector<std::unique_ptr<Group>>& GroupManager::getGroups() {
    return groups;
}

/**
 * @brief Returns a list of Task pointers for the given group.
 * @param groupName The name of the group in question.
 * @return The list of Task pointers in question.
 */
const std::vector<std::unique_ptr<Task>>& GroupManager::getTasks(
        const std::string& groupName) {
    
    Group* group = getGroupFromName(groupName);
    return group->getTasks();
}

/**
 * @brief Checks whether or not the groups field contains a specific group.
 * @param groupName The name of the group in question.
 * @return A boolean based in whether or not the groups field contains 
 * the group in question.
 */
bool GroupManager::containsGroup(const std::string& groupName) {
    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        if (groups.at(i).get()->getName() == groupName) return true;
    }
    return false;
}

/**
 * @brief Returns a pointer to a group when given the idNum of it.
 * @param groupId The idNum of the group in question.
 * @return A pointer to the group in question.
 */
Group* GroupManager::getGroupFromId(int groupId) {
    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        if (groups.at(i).get()->getIdNum() == groupId) {
            return groups.at(i).get();
        }   
    }
    throw std::invalid_argument("ERROR when trying to find a group by id that doesn't exist");
}

/**
 * @brief Returns a pointer to a group when given the name of it.
 * @param groupName The name of the group in question.
 * @return A pointer to the group in question.
 */
Group* GroupManager::getGroupFromName(
        const std::string& groupName) {
    
    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        if (groups.at(i).get()->getName() == groupName) {
            return groups.at(i).get();
        }
    }
    throw std::invalid_argument("Error when trying to find a group by name that doesn't exist");
}

/**
 * @brief Returns a pointer to a task when given the idNum of
 * the task and the name of the group it's in.
 * @param groupName The name of the group the task in question
 * is associated with.
 * @param taskId The idNum of the task in question.
 * @return A pointer to the task in question.
 */
Task* GroupManager::getTaskFromId(
        const std::string& groupName, int taskId) {

    Group* group = getGroupFromName(groupName);
    return group->getTaskFromId(taskId);
}

/**
 * @brief Handles the logic for checking whether or not a given
 * group contains a specific task.
 * @param groupName The name of the group in question.
 * @param taskName The name of the task in question.
 * @return A boolean representation of whether or not the task
 * was in the given group.
 */
bool GroupManager::containsTask(const std::string& groupName, 
        const std::string& taskName) {

    Group* group = getGroupFromName(groupName);
    return group->containsTask(taskName);
}

/**
 * @brief A mutator for the groups field.
 * @param newGroups The new vector of groups.
 */
void GroupManager::setGroups(
        std::vector<std::unique_ptr<Group>>&& newGroups) {
    
    groups = std::move(newGroups);
}

/**
 * @brief Adds a new groups to the groups field.
 * @param newGroup The new group to be added.
 */
void GroupManager::addGroup(std::unique_ptr<Group> newGroup) {
    groups.push_back(std::move(newGroup));
    refreshGroups();
    saveGroupData();
}

/**
 * @brief Removes a group from the groups field.
 * @param groupId The idNum of the group to be removed.
 */
void GroupManager::removeGroup(const int groupId) {
    groups.erase(groups.begin() + groupId);
    data.erase(data.begin() + groupId);
    int lastGroupId = static_cast<int>(groups.size()) - 1;
    fs::remove(filepath + "/tasks/group" 
            + std::to_string(lastGroupId) + "_tasks.json");
    refreshGroups();
    saveGroupData();
}

/**
 * @brief Removes all groups from the groups field.
 */
void GroupManager::clearAllGroups() {
    groups.clear();
    data.clear();
    saveGroupData();
}

/**
 * @brief Handles the logic for adding a task to a given group.
 * @param groupName The name of the group in question.
 * @param newTask A pointer to the task in question.
 */
void GroupManager::addTask(const std::string& groupName, 
        std::unique_ptr<Task> newTask) {

    Group* group = getGroupFromName(groupName);
    group->addTask(std::move(newTask));
    saveGroupData();
}

/**
 * @brief Handles the logic for removing a task in a given group.
 * @param groupName The name of the group in question.
 * @param taskId The idNum of the task in question.
 */
void GroupManager::removeTask(const std::string& groupName, 
        const int taskId) {

    Group* group = getGroupFromName(groupName);
    group->removeTask(taskId);

    int groupId = group->getIdNum();
    std::string idStr = std::to_string(groupId);
    std::string filename = filepath + "tasks/group"
                            + idStr + "_tasks.json";
    std::ifstream taskInFile(filename);
    json taskfile;
    if (taskInFile.is_open()) {
        taskfile = json::parse(taskInFile);
    }
    taskInFile.close();

    taskfile.erase(taskfile.begin() + taskId);
    
    std::ofstream taskOutFile(filename);
    if (taskOutFile.is_open()) {
        taskOutFile << std::setw(4) << taskfile << std::endl;
    } else {
        std::cerr << outputPreamble
                  << "ERROR when trying to write to " << filename
                  << std::endl;
    }
    taskOutFile.close();
}

/**
 * @brief Handles the logic for clearing all tasks in a given group.
 * @param groupName The name of the group in question.
 */
void GroupManager::clearAllTasks(const std::string& groupName) {
    Group* group = getGroupFromName(groupName);
    group->clearAllTasks();
   
    int groupId = group->getIdNum();
    std::string idStr = std::to_string(groupId);
    std::string filename = filepath + "tasks/group"
                            + idStr + "_tasks.json";
    json taskfile;
    std::ofstream taskOutFile(filename);
    if (taskOutFile.is_open()) {
        taskOutFile << std::setw(4) << taskfile << std::endl;
    } else {
        std::cerr << outputPreamble
                  << "ERROR when trying to write to " << filename
                  << std::endl;
    }
    taskOutFile.close();
}
