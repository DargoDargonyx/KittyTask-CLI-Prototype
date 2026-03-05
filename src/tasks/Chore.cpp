// Task header file
#include "tasks/Chore.hpp"


/**
 * @brief A constructor for the class.
 * @param idNum The identification number for the task.
 * @param name The name of the task.
 * @param date The date the task needs to be completed
 * by in MM/DD/YYYY format.
 * @param status Whether or not the task has been completed.
 */
Chore::Chore(int idNum, const std::string& name, 
        const std::string& date, bool status) 
    : Task(idNum, name, date, status) {

    this->type = "Chore";
}

/**
 * @brief An accessor for the type field.
 * @return The type field as a string.
 */
std::string Chore::getType() {
    return TYPE;
}
