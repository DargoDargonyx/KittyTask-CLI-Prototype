// Group header file
#include "groups/SelfStudy.hpp"



/**
 * @brief A constructor for the class.
 * @param idNum The identification number for the group.
 * @param name The name of the group.
 * @param year The year for the group.
 * @param semester The semester for the group.
 * @param topic The topic of the group.
 * @param grade The grade associated with the group.
 */
SelfStudy::SelfStudy(int idNum, const std::string& name, int year, 
        const std::string& semester, const std::string& topic) 
        : Group(idNum, name) {

    this->year = year;
    this->semester = semester;
    this->topic = topic;
}

/**
 * @brief An accessor for the year field.
 * @return The year field as an integer.
 */
int SelfStudy::getYear() {
    return year;
}

/**
 * @brief An accessor for the semester field.
 * @return The semester field as a string.
 */
std::string SelfStudy::getSemester() {
    return semester;
}

/**
 * @brief An accessor for the topic field.
 * @return The topic field as a string.
 */
std::string SelfStudy::getTopic() {
    return topic;
}

/**
 * @brief An accessor for the type field.
 * @return The type field as a string.
 */
std::string SelfStudy::getType() {
    return TYPE;
}

/**
 * @brief A mutator for the year field.
 * @param year The new year to integer be set.
 */
void SelfStudy::setYear(int year) {
    this->year = year;
}

/**
 * @brief A mutator for the semester field.
 * @param semester The new string to be set.
 */
void SelfStudy::setSemester(const std::string& semester) {
    this->semester = semester;
}

/**
 * @brief A mutator for the topic field.
 * @param topic The new string to be set.
 */
void SelfStudy::setTopic(const std::string& topic) {
    this->topic = topic;
}
