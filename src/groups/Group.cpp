// Group header file
#include "groups/Group.hpp"

// Built in libraries
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>


/**
 * @brief A constructor for the class.
 * @param idNum The identification number of the group.
 * @param name The name of the group.
 */
Group::Group(int idNum, const std::string& name) 
    : idNum(idNum), name(name) {}

/**
 * @brief An accessor for the idNum field.
 * @return The idNum field as an integer.
 */
int Group::getIdNum() {
    return idNum;
}

/**
 * @brief An accesor for the name field.
 * @return The name field as a string.
 */
std::string Group::getName() {
    return name;
}

/**
 * @brief An accessor for the tasks field.
 * @return A reference to the tasks field vector.
 */
const std::vector<std::unique_ptr<Task>>& Group::getTasks() {
    return tasks;
}

/**
 * @brief An accessor for the type field.
 * @return The type field as a string.
 */
std::string Group::getType() {
    return TYPE;
}

/**
 * @brief Checks whether or not the tasks field contains
 * a specfic task.
 * @param taskName The name of the task in question.
 * @return A boolean representation of whether or not the
 * task in question was in the tasks field.
 */
bool Group::containsTask(const std::string& taskName) {
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        if (tasks.at(i).get()->getName() == taskName) return true;
    }
    return false;
}

/**
 * @brief Gets a pointer to a task in the tasks field when
 * given a task idNum.
 * @param taskId The idNum for the task in question.
 * @return A pointer to the task in question.
 */
Task* Group::getTaskFromId(int taskId) {
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        if (tasks.at(i).get()->getIdNum() == taskId) {
            return tasks.at(i).get();
        }   
    }
    throw std::invalid_argument("ERROR, trying to find a task by an id that doesn't exist");
}

/**
 * @brief Gets a pointer to a task in the task field when
 * given a task name.
 * @param taskName The name of the task in question.
 * @return A pointer to the task in question.
 */
Task* Group::getTaskFromName(const std::string& taskName) {
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        if (tasks.at(i).get()->getName() == taskName) {
            return tasks.at(i).get();
        }
    }
    throw std::invalid_argument("Error, trying to find a task by a name that doesn't exist");
}

/**
 * @brief A mutator for the idNum field.
 * @param idNum The new idNum to be set.
 */
void Group::setIdNum(int idNum) {
    this->idNum = idNum;
}

/**
 * @brief A mutator for the name field.
 * @param name The new name to be set.
 */
void Group::setName(const std::string& name) {
    this->name = name;
}

/**
 * @brief A mutator for the tasks field.
 * @param The new vector of Task pointers to be set.
 */
void Group::setTasks(std::vector<std::unique_ptr<Task>>&& newTasks) {
    tasks = std::move(newTasks);
}

/**
 * @brief Adds a Task pointer to the tasks field.
 * @param newTask The Task pointer in question.
 */
void Group::addTask(std::unique_ptr<Task> newTask) {
    if (newTask->getIdNum() != static_cast<int>(tasks.size())) {
        newTask->setIdNum(static_cast<int>(tasks.size()));
    }
    tasks.push_back(std::move(newTask));
    refreshTasks();
}

/**
 * @brief Removes a Task pointer from the tasks field.
 * @param taskId The idNum of the Task pointer in question.
 */
void Group::removeTask(int taskId) {
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        if (tasks.at(i)->getIdNum() == taskId) {
            tasks.erase(tasks.begin() + i);
            break;
        }
    }
    refreshTasks();
}

/**
 * @brief Removes all Task pointers from the tasks field.
 */
void Group::clearAllTasks() {
    tasks.clear();
}

/**
 * @brief Refreshes all Task idNums from the Task pointers in
 * the tasks field in order to ensure that there are no gaps.
 */
void Group::refreshTasks() {
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        tasks.at(i)->setIdNum(i);
    }
}
