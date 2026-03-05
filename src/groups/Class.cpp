// Group header file
#include "groups/Class.hpp"

// Built in library
#include <stdexcept>


/**
 * @brief A constructor for the class.
 * @param idNum The identification number for the group.
 * @param name The name of the group.
 * @param year The year for the group.
 * @param semester The semester for the group.
 * @param topic The topic of the group.
 * @param grade The grade associated with the group.
 */
Class::Class(int idNum, const std::string& name, 
        uint16_t year, const std::string& semester, 
        const std::string& topic, uint16_t grade) : Group(idNum, name) {

    this->year = year;
    this->semester = semester;
    this->topic = topic;
    this->grade = grade;
}

/**
 * @brief An accessor for the year field.
 * @return The year field as an integer.
 */
uint16_t Class::getYear() {
    return year;
}

/**
 * @brief An accessor for the semester field.
 * @return The semester field as a Semester object.
 */
std::string Class::getSemester() {
    return semester;
}

/**
 * @brief An accessor for the topic field.
 * @return The topic field as a Topic object.
 */
std::string Class::getTopic() {
    return topic;
}

/**
 * @brief An accessor for the grade field.
 * @return The grade field as an integer.
 */
uint16_t Class::getGrade() {
    return grade;
}

/**
 * @brief An accessor for the type field.
 * @return The type field as a string.
 */
std::string Class::getType() {
    return TYPE;
}

/**
 * @brief A mutator for the year field.
 * @param year The new year to integer be set.
 */
void Class::setYear(uint16_t year) {
    this->year = year;
}

/**
 * @brief A mutator for the semester field.
 * @param semester The new string to be set.
 */
void Class::setSemester(const std::string& semester) {
    this->semester = semester;
}

/**
 * @brief A mutator for the topic field.
 * @param topic The new string to be set.
 */
void Class::setTopic(const std::string& topic) {
    this->topic = topic;
}

/**
 * @brief A mutator for the grade field.
 * @param grade The new grade integer to be set.
 */
void Class::setGrade(uint16_t grade) {
    this->grade = grade;
}
