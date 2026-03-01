#include "groups/Group.hpp"
#include "groups/Class.hpp"
#include "groups/DevWork.hpp"
#include "groups/Research.hpp"
#include "groups/SelfStudy.hpp"

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

#include "util/GroupManager.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"
#include "external/json.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;
namespace fs = std::filesystem;


GroupManager::GroupManager(
        const std::string& filepath, 
        const std::string& outputPreamble) {

    this->filepath = filepath;
    this->outputPreamble = outputPreamble;
    checkDataDirectory();
    loadGroupData();
}


const std::vector<std::unique_ptr<Group>>& GroupManager::getGroups() const {
    return groups;
}

void GroupManager::setGroups(std::vector<std::unique_ptr<Group>>&& newGroups) {
    groups = std::move(newGroups);
}

void GroupManager::addGroup(std::unique_ptr<Group> newGroup) {

    if (newGroup->getIdNum() != static_cast<int>(groups.size())) {
        newGroup->setIdNum(static_cast<int>(groups.size()));
    }

    int idNum = newGroup->getIdNum();
    std::string type = newGroup->getType();
    data[idNum]["name"] = newGroup->getName();
    data[idNum]["type"] = type;

    if (type == "Class") {
        Class* cGroup = static_cast<Class*>(newGroup.get());
        data[idNum]["year"] = cGroup->getYear();
        data[idNum]["semester"] = semesterToJsonStr(cGroup->getSemester());
        data[idNum]["topic"] = topicToJsonStr(cGroup->getTopic());
        data[idNum]["grade"] = cGroup->getGrade();
    } else if (type == "DevWork") {
        DevWork* dGroup = static_cast<DevWork*>(newGroup.get());
        data[idNum]["year"] = dGroup->getYear();
        data[idNum]["topic"] = topicToJsonStr(dGroup->getTopic());
    } else if (type == "Research") {
        Research* rGroup = static_cast<Research*>(newGroup.get());
        data[idNum]["year"] = rGroup->getYear();
        data[idNum]["semester"] = semesterToJsonStr(rGroup->getSemester());
        data[idNum]["topic"] = topicToJsonStr(rGroup->getTopic());
    } else if (type == "SelfStudy") {
        SelfStudy* sGroup = static_cast<SelfStudy*>(newGroup.get());
        data[idNum]["year"] = sGroup->getYear();
        data[idNum]["semester"] = semesterToJsonStr(sGroup->getSemester());
        data[idNum]["topic"] = topicToJsonStr(sGroup->getTopic());
    }
    groups.push_back(std::move(newGroup));
    saveGroupData();
}

void GroupManager::removeGroup(int groupId) {}



void GroupManager::checkDataDirectory() {
    try {
        bool dataCreated = fs::create_directories(filepath);
        if (dataCreated) {
            std::cout << outputPreamble
                      << "Directory created: " 
                      << filepath 
                      << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << outputPreamble
                  << "ERROR when creating directory \"" 
                  << filepath 
                  << "\": " << e.what() 
                  << std::endl;
    }

    try {
        bool tasksCreated = fs::create_directories(filepath + "tasks/");
        if (tasksCreated) {
            std::cout << outputPreamble
                      << "Directory created: " 
                      << filepath 
                      << "tasks/" 
                      << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << outputPreamble
                  << "ERROR when creating directory \""
                  << filepath
                  << "/tasks\": " << e.what()
                  << std::endl;
    }
}

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
        std::string filename = filepath
                + "tasks/group"
                + idStr
                + "_tasks.json";
        
        std::ifstream taskfileStream(filename);
        json taskfile;
        if (taskfileStream.is_open()) {
            taskfile = json::parse(taskfileStream);
        }
        taskfileStream.close();       
        
        for (int j = 0; j < static_cast<int>(taskfile.size()); j++) {
            group->addTask(buildTask(taskfile, j));
        }
        group->refreshTaskIdList();
        groups.push_back(std::move(group));
    }
}

void GroupManager::saveGroupData() {

    std::ofstream file(filepath + "groupData.json");
    if (file.is_open()) {
        file << std::setw(4) << data << std::endl;
    } else {
        std::cerr << outputPreamble
                  << "ERROR when trying to write to groupData.json file"
                  << std::endl;
    }
    file.close();
}



std::unique_ptr<Group> GroupManager::buildGroup(const int groupId) {
    std::string name = data[groupId]["name"];
    std::string type = data[groupId]["type"];

    if (type == "Class") {
        std::unique_ptr<Class> cGroup = std::make_unique<Class>(
            groupId, 
            name,
            static_cast<uint8_t>(data[groupId]["year"]),
            jsonStrToSemester(groupId),
            jsonStrToTopic(groupId),
            static_cast<uint8_t>(data[groupId]["grade"])
        );
        return cGroup;
    } else if (type == "DevWork") {
        return std::make_unique<DevWork>(
            groupId,
            name,
            static_cast<uint8_t>(data[groupId]["year"]),
            jsonStrToTopic(groupId)
        );
    } else if (type == "Research") {
        return std::make_unique<Research>(
            groupId, 
            name,
            static_cast<uint8_t>(data[groupId]["year"]),
            jsonStrToSemester(groupId),
            jsonStrToTopic(groupId)
        );
    } else if (type == "SelfStudy") {
        return std::make_unique<SelfStudy>(
            groupId, 
            name,
            static_cast<uint8_t>(data[groupId]["year"]),
            jsonStrToSemester(groupId),
            jsonStrToTopic(groupId)
        );
    } else {
        std::cout << outputPreamble
                  << "No known group of type \""
                  << data[groupId]["type"]
                  << "\", using a default type instead..."
                  << std::endl;
        
        return std::make_unique<Group>(groupId, name);
    }
}

std::unique_ptr<Task> GroupManager::buildTask(const json& taskfile, const int taskId) {
    std::string name = taskfile[taskId]["name"];
    std::string date = taskfile[taskId]["date"];
    bool status = taskfile[taskId]["status"];
    uint8_t grade;
    std::string type = taskfile[taskId]["type"];

    if (type == "Chore") {
        return std::make_unique<Chore>(
                taskId, 
                name, 
                date, 
                status
            );
    } else if (type == "Exam") {
        grade = static_cast<uint8_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Exam>(
                taskId, 
                name, 
                date, 
                status,
                grade
            );
    } else if (type == "Homework") {
        grade = static_cast<uint8_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Homework>(
                taskId, 
                name, 
                date, 
                status, 
                grade
            );
    } else if (type == "Lab") {
        grade = static_cast<uint8_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Lab>(
                taskId, 
                name, 
                date, 
                status,
                grade
            );
    } else if (type == "LabAssignment") {
        grade = static_cast<uint8_t>(taskfile[taskId]["grade"]);
        return std::make_unique<LabAssignment>(
                taskId, 
                name, 
                date, 
                status,
                grade
            );
    } else if (type == "Notes") {
        grade = static_cast<uint8_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Notes>(
                taskId, 
                name, 
                date, 
                status,
                grade
            );
    } else if (type == "Presentation") {
        grade = static_cast<uint8_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Presentation>(
                taskId, 
                name, 
                date, 
                status,
                grade
            );
    } else if (type == "Programming") {
        grade = static_cast<uint8_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Programming>(
                taskId, 
                name, 
                date, 
                status,
                grade
            );
    } else if (type == "Project") {
        grade = static_cast<uint8_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Project>(
                taskId, 
                name, 
                date, 
                status,
                grade
            );
    } else if (type == "Quiz") {
        grade = static_cast<uint8_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Quiz>(
                taskId, 
                name, 
                date, 
                status,
                grade
            );
    } else if (type == "Reading") {
        grade = static_cast<uint8_t>(taskfile[taskId]["grade"]);
        return std::make_unique<Reading>(
                taskId, 
                name, 
                date, 
                status, 
                grade
            );
    } else {
        std::cout << outputPreamble
                  << "Unknown task type of \""
                  << type
                  << "\", using a default type instead..."
                  << std::endl;
        return std::make_unique<Task>(
                taskId, 
                name, 
                date, 
                status
            );
    }
}



Semester GroupManager::jsonStrToSemester(const int groupId) {
    std::string semesterStr = data[groupId]["semester"];
    if (semesterStr == "Spring") {
        return Semester::SPRING;
    } else if (semesterStr == "Fall") {
        return Semester::FALL;
    } else if (semesterStr == "Summer") {
        return Semester::SUMMER;
    } else {
        std::cerr << outputPreamble
                  << "ERROR when reading from group data JSON, unknown semester \"" 
                  << semesterStr
                  << "\" from the group " 
                  << data[groupId]["name"] 
                  << std::endl;
        throw std::invalid_argument("Unknown semester value in JSON");
    }
}

Topic GroupManager::jsonStrToTopic(const int groupId) {
    std::string topicStr = data[groupId]["topic"];
    if (topicStr == "Math") {
        return Topic::MATH;
    } else if (topicStr == "CS") {
        return Topic::CS;
    } else if (topicStr == "Physics") {
        return Topic::PHYSICS;
    } else if (topicStr == "Chemistry") {
        return Topic::CHEM;
    } else if (topicStr == "Biology") {
        return Topic::BIO;
    } else {
        std::cerr << outputPreamble
                  << "ERROR when reading from group data JSON, unknown topic \"" 
                  << topicStr
                  << "\" from the group " 
                  << data[groupId]["name"] 
                  << std::endl;
        throw std::invalid_argument("Unknown topic value in JSON");
    }
}

std::string GroupManager::semesterToJsonStr(const Semester& semester) {
    switch(semester) {
        case Semester::SPRING: return "Spring";
        case Semester::FALL: return "Fall";
        case Semester::SUMMER: return "Summer";
        default:
            std::cerr << outputPreamble
                      << "ERROR when trying to translate into a string for saving into a JSON"
                      << std::endl;
            throw std::invalid_argument("Unknown semester value");
    }
}

std::string GroupManager::topicToJsonStr(const Topic& topic) {
    switch(topic) {
        case Topic::MATH: return "Math";
        case Topic::CS: return "CS";
        case Topic::PHYSICS: return "Physics";
        case Topic::CHEM: return "Chemistry";
        case Topic::BIO: return "Biology";
        default:
            std::cerr << outputPreamble
                      << "ERROR when trying to translate into a string for saving into a JSON"
                      << std::endl;
            throw std::invalid_argument("Unknown topic value");
    }
}
