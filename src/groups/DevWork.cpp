// Group header file
#include "groups/DevWork.hpp"

// Utility header file
#include "util/Topic.hpp"

// Built in library
#include <stdexcept>


/**
 * @brief A constructor for the class.
 * @param idNum The identification number for the group.
 * @param name The name of the group.
 * @param year The year for the group.
 * @param topic The topic of the group.
 * @param grade The grade associated with the group.
 */
DevWork::DevWork(int idNum, const std::string& name, uint16_t year, 
        const Topic& topic) : Group(idNum, name) {

    this->type = "DevWork";
    this->year = year;
    this->topic = topic;
}

/**
 * @brief An accessor for the year field.
 * @return The year field.
 */
uint16_t DevWork::getYear() const {
    return year;
}

/**
 * @brief An accessor for the topic field.
 * @return The topic field as a Topic object.
 */
Topic DevWork::getTopic() const {
    return topic;
}

/**
 * @brief An accessor for the topic field.
 * @return The topic field as a string.
 */
std::string DevWork::getTopicStr() const {
    if (topic == Topic::MATH) {
        return "Math";
    } else if (topic == Topic::CS) {
        return "CS";
    } else if (topic == Topic::PHYSICS) {
        return "Physics";
    } else if (topic == Topic::CHEM) {
        return "Chemistry";
    } else if (topic == Topic::BIO) {
        return "Biology";
    } else {
        throw std::invalid_argument("Unknown topic");
    }
}

/**
 * @brief A mutator for the year field.
 * @param year The new year to integer be set.
 */
void DevWork::setYear(uint16_t year) {
    this->year = year;
}

/**
 * @brief A mutator for the topic field.
 * @param topic The new Topic object to be set.
 */
void DevWork::setTopic(const Topic& topic) {
    this->topic = topic;
}
