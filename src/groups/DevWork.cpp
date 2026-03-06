// Group header file
#include "groups/DevWork.hpp"



/**
 * @brief A constructor for the class.
 * @param idNum The identification number for the group.
 * @param name The name of the group.
 * @param year The year for the group.
 * @param topic The topic of the group.
 * @param grade The grade associated with the group.
 */
DevWork::DevWork(int idNum, const std::string& name, int year, 
        const std::string& topic) : Group(idNum, name) {

    this->year = year;
    this->topic = topic;
}

/**
 * @brief An accessor for the year field.
 * @return The year field.
 */
int DevWork::getYear() {
    return year;
}

/**
 * @brief An accessor for the topic field.
 * @return The topic field as a string.
 */
std::string DevWork::getTopic() {
    return topic;
}

/**
 * @brief An accessor for the type field.
 * @return The type field as a string.
 */
std::string DevWork::getType() {
    return TYPE;
}

/**
 * @brief A mutator for the year field.
 * @param year The new year to integer be set.
 */
void DevWork::setYear(int year) {
    this->year = year;
}

/**
 * @brief A mutator for the topic field.
 * @param topic The new string to be set.
 */
void DevWork::setTopic(const std::string& topic) {
    this->topic = topic;
}
