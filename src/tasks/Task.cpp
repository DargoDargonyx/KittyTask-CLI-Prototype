// Task header file
#include "tasks/Task.hpp"


/**
 * @brief A constructor for the class.
 * @param idNum The identification number for the task.
 * @param name The name of the task.
 * @param date The date the task needs to be completed
 * by in MM/DD/YYYY format.
 * @param status Whether or not the task has been completed.
 */
Task::Task(int idNum, const std::string& name, 
        const std::string& date, bool status) 
    : idNum(idNum), name(name), date(date), status(status) {}

/**
 * @brief An accessor for the idNum field.
 * @return The idNum field as an integer.
 */
int Task::getIdNum() {
    return idNum;
}

/**
 * @brief An accessor for the name field.
 * @return The name field as a string.
 */
std::string Task::getName() {
    return name;
}

/**
 * @brief An accessor for the date field.
 * @return The date field as a string in
 * the format of MM/DD/YYYY.
 */
std::string Task::getDate() {
    return date;
}

/**
 * @brief An accessor for the status field.
 * @return The status field as a boolean.
 */
bool Task::getStatus() {
    return status;
}

/**
 * @brief An accessor for the type field.
 * @return The type field as a string.
 */
std::string Task::getType() {
    return TYPE;
}

/**
 * @brief A mutator for the idNum field.
 * @param idNum The new idNum integer to be set.
 */
void Task::setIdNum(int idNum) {
    this->idNum = idNum;
}

/**
 * @brief A mutator for the name field.
 * @param name The new name string to be set.
 */
void Task::setName(const std::string& name) {
    this->name = name;
}

/**
 * @brief A mutator for the date field.
 * @param date The new date string to be set
 * in the format of MM/DD/YYYY.
 */
void Task::setDate(const std::string& date) {
    this->date = date;
}

/**
 * @brief A mutator for the status field.
 * @param status The new status boolean
 * to be set.
 */
void Task::setStatus(bool status) {
    this->status = status;
}
