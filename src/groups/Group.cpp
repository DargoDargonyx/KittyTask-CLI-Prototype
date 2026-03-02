#include "groups/Group.hpp"
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>

Group::Group(int idNum, const std::string& name) 
    : idNum(idNum), name(name) {

    this->type = "Default";
}

int Group::getIdNum() const {
    return idNum;
}

void Group::setIdNum(int idNum) {
    this->idNum = idNum;
}

std::string Group::getName() const {
    return name;
}

void Group::setName(const std::string& name) {
    this->name = name;
}

std::vector<std::unique_ptr<Task>>& Group::getTasks() {
    return tasks;
}

void Group::setTasks(std::vector<std::unique_ptr<Task>>&& newTasks) {
    tasks = std::move(newTasks);
}

std::string Group::getType() const {
    return type;
}

void Group::addTask(std::unique_ptr<Task> newTask) {
    if (newTask->getIdNum() != static_cast<int>(tasks.size())) {
        newTask->setIdNum(static_cast<int>(tasks.size()));
    }
    tasks.push_back(std::move(newTask));
    refreshTasks();
}

void Group::removeTask(const int taskId) {
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        if (tasks.at(i)->getIdNum() == taskId) {
            tasks.erase(tasks.begin() + i);
            break;
        }
    }
    refreshTasks();
}

void Group::clearAllTasks() {
    tasks.clear();
}

bool Group::containsTask(const std::string& taskName) {
    bool containsTask = false;
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        if (tasks.at(i)->getName() == taskName) {
            containsTask = true;
            break;
        }
    }
    return containsTask;
}

Task* Group::getTaskFromId(const int taskId) {
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        if (tasks.at(i)->getIdNum() == taskId) {
            return tasks.at(i).get();
        }   
    }
    throw std::invalid_argument("ERROR when trying to find a task by id that doesn't exist");
}

Task* Group::getTaskFromName(const std::string& taskName) {
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        if (tasks.at(i)->getName() == taskName) {
            return tasks.at(i).get();
        }
    }
    throw std::invalid_argument("Error when trying to find a task by name that doesn't exist");
}

void Group::refreshTasks() {
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        tasks.at(i)->setIdNum(i);
    }
}
