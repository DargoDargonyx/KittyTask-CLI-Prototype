// Task Header file
#include "tasks/Exam.hpp"


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
Exam::Exam(int idNum, const std::string& name, 
        const std::string& date, bool status, int grade) 
    : GradedTask(idNum, name, date, status, grade) {}

/**
 * @brief An accessor for the type field.
 * @return The type field as a string.
 */
std::string Exam::getType() {
    return TYPE;
}
