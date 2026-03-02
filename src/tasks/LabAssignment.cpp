// Task header file
#include "tasks/LabAssignment.hpp"


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
LabAssignment::LabAssignment(int idNum, const std::string& name, 
        const std::string& date, bool status, uint16_t grade) 
    : GradedTask(idNum, name, date, status, grade) {
   
    this->type = "LabAssignment";
}
