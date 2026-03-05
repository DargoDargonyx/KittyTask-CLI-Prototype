// Task header file
#include "tasks/GradedTask.hpp"


/**
 * @brief A constructor for the class.
 * @param idNum The identification number for the task.
 * @param name The name of the task.
 * @param date The date the task needs to be completed
 * by in MM/DD/YYYY format.
 * @param status Whether or not the task has been completed.
 * @param grade The grade associated with the task
 * if applicable.
 */
GradedTask::GradedTask(int idNum, const std::string& name, 
    const std::string& date, bool status, uint16_t grade)
    : Task(idNum, name, date, status), grade(grade) {
}

/**
 * @brief An accessor for the type field.
 * @return The type field as a string.
 */
std::string GradedTask::getType() {
    return TYPE;
}

/**
 * @brief An accessor for the grade field.
 * @return The grade field as an integer.
 */
uint16_t GradedTask::getGrade() {
    return grade;
}

/**
 * @brief A mutator for the grade field.
 * @param grade The new grade integer to be set.
 */
void GradedTask::setGrade(uint16_t grade) {
    this->grade = grade;
}
