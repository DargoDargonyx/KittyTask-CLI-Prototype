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

// Utility header file
#include "util/DataManager.hpp"

// Built in libraries
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <iostream>
#include <fstream>

using json = nlohmann::json;
namespace fs = std::filesystem;



/**
 * @brief A constructor for the class.
 * @param filepath The filepath to the data directory.
 * @param logPreamble A text preamble for the printing output
 */
DataManager::DataManager(const std::string& filepath, const std::string& logPreamble) 
        : filepath(filepath), logPreamble(logPreamble) {

    this->groupDataPath = filepath + "groupData.json";
    checkDataDirectory();
}

/**
 * @brief A helper function that gets the string representation
 * of the file path to a specific json that holds the task data
 * for a group
 * @param groupId The idNum of the group associated with the file.
 * @return The string representation of the file path in question.
 */
std::string DataManager::getTaskFilePath(int groupId) {
    std::string idStr = std::to_string(groupId);
    return filepath + "tasks/group" + idStr + "_tasks.json";
}

/**
 * @brief Ensures that the data directory exists and that it
 * contains a subdirectory for the task json files.
 */
void DataManager::checkDataDirectory() {
    try {
        bool dataCreated = fs::create_directories(filepath);
        if (dataCreated) {
            std::cout << logPreamble << "Directory created: " 
                      << filepath << std::endl;
        } else {
            std::ifstream file(groupDataPath);
            if (file.is_open()) groupData = json::parse(file);
            file.close();
        }
    } catch (const fs::filesystem_error& error) {
        std::cerr << logPreamble << "ERROR when creating directory \"" 
                  << filepath << "\": " << error.what() << std::endl;
    }

    try {
        bool tasksCreated = fs::create_directories(filepath + "tasks/");
        if (tasksCreated) {
            std::cout << logPreamble << "Directory created: " 
                      << filepath << "tasks/" << std::endl;
        } else {
            for (int groupId = 0; groupId < static_cast<int>(groupData.size()); groupId++) {
                std::string filename = getTaskFilePath(groupId);
                if (fs::exists(filename)) {
                    std::ifstream file(filename);
                    if (file.is_open()) 
                        taskFiles.push_back(json::parse(file));
                    file.close();
                }
                else {
                    std::ofstream file(filename);
                    if (file.is_open()) {
                        json temp;
                        file << std::setw(4) << temp << std::endl;
                    } else {
                        std::cerr << logPreamble << "ERROR when trying to write "
                                  << "to create task file." << std::endl;
                    }
                    file.close();
                }
            }
        }
    } catch (const fs::filesystem_error& error) {
        std::cerr << logPreamble << "ERROR when creating directory \""
                  << filepath << "/tasks\": " << error.what() << std::endl;
    }
}

/**
 * @brief Loads the data from the json file in the data directory
 * and returns a vector of created Group objects.
 * @return The vector of Group objects in question.
 */
std::vector<std::unique_ptr<Group>> DataManager::loadGroupData() {
    std::vector<std::unique_ptr<Group>> groups;
    for (int groupId = 0; groupId < static_cast<int>(groupData.size()); groupId++) {
        groups.push_back(buildGroup(groupId));
    }
    return groups;
}

/**
 * @brief Loads the data from the json files in the data/tasks 
 * directory and returns a vector of created Task objects.
 * @param groupId The idNum of the group associated with the
 * tasks and json task file.
 * @return The vector of Task objects in question.
 */
std::vector<std::unique_ptr<Task>> DataManager::loadTaskFile(int groupId) {
    std::vector<std::unique_ptr<Task>> tasks;
    for (int taskId = 0; taskId < static_cast<int>(taskFiles[groupId].size()); taskId++) {
        tasks.push_back(buildTask(groupId, taskId));
    }
    return tasks;
}

/**
 * @brief Saves the given group data to the json file in the data directory.
 * @param groups A vector of Group objects to be stored in the json file.
 */
void DataManager::saveGroupData() {
    std::ofstream file(groupDataPath);
    if (file.is_open()) {
        file << std::setw(4) << groupData << std::endl;
    } else {
        std::cerr << logPreamble << "ERROR when trying to write "
                  << "to groupData.json file." << std::endl;
    }
    file.close();
}

/**
 * @brief Saves the given task data to a json associated with the group
 * that tasks belong to.
 * @param groupId The idNum of the group the tasks in question belong to.
 * @param groups A vector of Task objects to be stored in the json file.
 */
void DataManager::saveTaskFile(int groupId) {
    std::string filename = getTaskFilePath(groupId);
    std::ofstream file(filename);
    if (file.is_open()) {
        file << std::setw(4) << taskFiles[groupId] << std::endl;
    } else {
        std::cerr << logPreamble << "ERROR when trying to "
                  << "write to group task file" << std::endl;
    }
    file.close();
}

/**
 * @brief Builds a group from json values.
 * @param groupId The idNum of the group in question.
 * @return A pointer to the newly built group.
 */
std::unique_ptr<Group> DataManager::buildGroup(int groupId) {
    std::string name = groupData[groupId]["name"];
    std::string type = groupData[groupId]["type"];

    if (type == "Class") {
        return std::make_unique<Class>(
                    groupId, 
                    name,
                    groupData[groupId]["year"],
                    groupData[groupId]["semester"], 
                    groupData[groupId]["topic"],
                    groupData[groupId]["grade"]
                );
    } else if (type == "DevWork") {
        return std::make_unique<DevWork>(
                    groupId, 
                    name,
                    groupData[groupId]["year"],
                    groupData[groupId]["topic"]
                );
    } else if (type == "Research") {
        return std::make_unique<Research>(
                    groupId, 
                    name,
                    groupData[groupId]["year"],
                    groupData[groupId]["semester"], 
                    groupData[groupId]["topic"]
                );
    } else if (type == "SelfStudy") {
        return std::make_unique<SelfStudy>(
                    groupId, 
                    name,
                    groupData[groupId]["year"],
                    groupData[groupId]["semester"], 
                    groupData[groupId]["topic"]
                );
    } else {
        std::cout << logPreamble << "No known group of type \""
                  << groupData[groupId]["type"] << "\", using a default "
                  << "type instead..." << std::endl;
        
        return std::make_unique<Group>(groupId, name);
    }
}

/**
 * @brief Builds a task from json values.
 * @param groupId The idNum of the group that the task in 
 * question belongs to.
 * @param taskId The idNum of the task in question.
 * @return A pointer to the newly built task.
 */
std::unique_ptr<Task> DataManager::buildTask(int groupId, int taskId) {
    std::string type = taskFiles[groupId][taskId]["type"];
    std::string name = taskFiles[groupId][taskId]["name"];
    std::string date = taskFiles[groupId][taskId]["date"];
    bool status = taskFiles[groupId][taskId]["status"];

    if (type == "Chore") {
        return std::make_unique<Chore>(
                    taskId, 
                    name, 
                    date, 
                    status
                );
    } else if (type == "Exam") {
        return std::make_unique<Exam>(
                    taskId, 
                    name, 
                    date, 
                    status,
                    taskFiles[groupId][taskId]["grade"]
                );
    } else if (type == "Homework") {
        return std::make_unique<Homework>(
                    taskId, 
                    name, 
                    date, 
                    status, 
                    taskFiles[groupId][taskId]["grade"]
                );
    } else if (type == "Lab") {
        return std::make_unique<Lab>(
                    taskId, 
                    name, 
                    date, 
                    status, 
                    taskFiles[groupId][taskId]["grade"]
                );
    } else if (type == "LabAssignment") {
        return std::make_unique<LabAssignment>(
                    taskId, 
                    name, 
                    date, 
                    status, 
                    taskFiles[groupId][taskId]["grade"]
                );
    } else if (type == "Notes") {
        return std::make_unique<Notes>(
                    taskId, 
                    name, 
                    date, 
                    status, 
                    taskFiles[groupId][taskId]["grade"]
                );
    } else if (type == "Presentation") {
        return std::make_unique<Presentation>(
                    taskId, 
                    name, 
                    date, 
                    status, 
                    taskFiles[groupId][taskId]["grade"]
                );
    } else if (type == "Programming") {
        return std::make_unique<Programming>(
                    taskId, 
                    name, 
                    date, 
                    status,
                    taskFiles[groupId][taskId]["grade"]
                );
    } else if (type == "Project") {
        return std::make_unique<Project>(
                    taskId, 
                    name, 
                    date, 
                    status,
                    taskFiles[groupId][taskId]["grade"]
                );
    } else if (type == "Quiz") {
        return std::make_unique<Quiz>(
                    taskId, 
                    name, 
                    date, 
                    status,
                    taskFiles[groupId][taskId]["grade"]
                );
    } else if (type == "Reading") {
        return std::make_unique<Reading>(
                    taskId, 
                    name, 
                    date, 
                    status, 
                    taskFiles[groupId][taskId]["grade"]
                );
    } else {
        std::cout << logPreamble << "Unknown task type of \"" << type 
                  << "\", using a default type instead..." << std::endl;
        return std::make_unique<Task>(taskId, name, date, status);
    }
}

/**
 * @brief Returns the id number of a group when given the
 * name of the group.
 * @param groupName The name of the group in question.
 * @return The idNum of the group in question.
 */
int DataManager::getGroupIdFromName(const std::string& groupName) {
    for (int groupId = 0; groupId < static_cast<int>(groupData.size()); groupId++) {
        if (groupData[groupId]["name"] == groupName) return groupId;
    }
    return -1;
}

/**
 * @brief Adds a new group to the groupData json file.
 * @param newGroup The new group to be added.
 */
void DataManager::addGroup(std::unique_ptr<Group> newGroup) {
    int groupId = static_cast<int>(groupData.size());

    std::string groupType = newGroup->getType();
    groupData[groupId]["name"] = newGroup->getName();
    groupData[groupId]["type"] = groupType;

    if (groupType == "Class") {
        Class* cGroup = static_cast<Class*>(newGroup.get());
        groupData[groupId]["year"] = cGroup->getYear();
        groupData[groupId]["semester"] = cGroup->getSemester();
        groupData[groupId]["topic"] = cGroup->getTopic();
        groupData[groupId]["grade"] = cGroup->getGrade();
    } else if (groupType == "DevWork") {
        DevWork* dGroup = static_cast<DevWork*>(newGroup.get());
        groupData[groupId]["year"] = dGroup->getYear();
        groupData[groupId]["topic"] = dGroup->getTopic();
    } else if (groupType == "Research") {
        Research* rGroup = static_cast<Research*>(newGroup.get());
        groupData[groupId]["year"] = rGroup->getYear();
        groupData[groupId]["semester"] = rGroup->getSemester();
        groupData[groupId]["topic"] = rGroup->getTopic();
    } else if (groupType == "SelfStudy") {
        SelfStudy* sGroup = static_cast<SelfStudy*>(newGroup.get());
        groupData[groupId]["year"] = sGroup->getYear();
        groupData[groupId]["semester"] = sGroup->getSemester();
        groupData[groupId]["topic"] = sGroup->getTopic();
    }

    saveGroupData();
}

/**
 * @brief Handles the logic for removing a group from the 
 * groupData json file.
 * @param groupId The idNum of the group to be removed.
 */
void DataManager::removeGroup(int groupId) {
    groupData.erase(groupData.begin() + groupId);
    int lastGroupId = static_cast<int>(taskFiles.size()) - 1;
    fs::remove(getTaskFilePath(lastGroupId));
    saveGroupData();
}

/**
 * @brief Removes all groups from the groupData json file.
 */
void DataManager::clearAllGroups() {
    groupData.clear();
    saveGroupData();
}

/**
 * @brief Handles the logic for changing the grade for a
 * specific group.
 * @param groupId The idNum of the group in question.
 * @param value The grade value to be set.
 * @return Whether or not the group value was successfully set.
 */
bool DataManager::setGroupGrade(int groupId, int value) {
    std::string groupType = groupData[groupId]["type"];
    if (groupType != "Class") return false;
    groupData[groupId]["grade"] = value;
    return true;
}

/**
 * @brief Handles the logic for checking whether or not a given
 * group contains a specific task.
 * @param groupId The idNum of the group that the task in
 * question belongs to.
 * @param taskName The name of the task in question.
 * @return A boolean representation of whether or not the task
 * was in the given group.
 */
int DataManager::getTaskIdFromName(int groupId, const std::string& taskName) {
    for (int taskId = 0; taskId < static_cast<int>(taskFiles[groupId].size()); taskId++) {
        if (taskFiles[groupId][taskId]["name"] == taskName) return taskId;
    }
    return -1;
}

/**
 * @brief Handles the logic for adding a new task to a given group.
 * @param groupId The idNum of the group in question.
 * @param newTask A pointer to the task in question.
 */
void DataManager::addTask(int groupId, std::unique_ptr<Task> newTask) {
    int taskId = static_cast<int>(taskFiles[groupId].size());
    std::string taskType = newTask->getType();
    taskFiles[groupId][taskId]["type"] = taskType;
    taskFiles[groupId][taskId]["name"] = newTask->getName();
    taskFiles[groupId][taskId]["date"] = newTask->getDate();
    taskFiles[groupId][taskId]["status"] = newTask->getStatus();
    if (taskType != "Chore") {
        GradedTask* gradedTask = static_cast<GradedTask*>(newTask.get());
        taskFiles[groupId][taskId]["grade"] = gradedTask->getGrade();
    }

    saveTaskFile(groupId);
}

/**
 * @brief Handles the logic for removing a task in a given group.
 * @param groupId The idNum of the group that the task in
 * question belongs to.
 * @param taskId The idNum of the task in question.
 */
void DataManager::removeTask(int groupId, int taskId) {
    taskFiles[groupId].erase(taskFiles[groupId].begin() + taskId);
    saveTaskFile(groupId);
}

/**
 * @brief Handles the logic for clearing the json task file 
 * for a given group.
 * @param groupId The idNum of the group in question.
 */
void DataManager::clearAllTasks(int groupId) {
    json empty;
    taskFiles[groupId] = empty;
    saveTaskFile(groupId);
}

/**
 * @brief Handles the logic for changing the grade of a 
 * specific task.
 * @param groupId The idNum of the group the task in question
 * belongs to.
 * @param taskId The idNum of the task in question.
 * @param value The grade value to be set.
 * @return Whether or not the task grade was successfully set.
 */
bool DataManager::setTaskGrade(int groupId, int taskId, int value) {
    std::string taskType = taskFiles[groupId][taskId]["type"];
    if (taskType == "Chore") return false;
    taskFiles[groupId][taskId]["grade"] = value;
    saveTaskFile(groupId);
    return true;
}
