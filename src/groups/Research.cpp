// Group header file
#include "groups/Research.hpp"

// Utility header files
#include "util/Semester.hpp"
#include "util/Topic.hpp"

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
Research::Research(int idNum, const std::string& name, uint16_t year, 
        const Semester& semester, const Topic& topic) : Group(idNum, name) {

    this->type = "Research";
    this->year = year;
    this->semester = semester;
    this->topic = topic;
}

/**
 * @brief An accessor for the year field.
 * @return The year field as an integer.
 */
uint16_t Research::getYear() const {
    return year;
}

/**
 * @brief An accessor for the semester field.
 * @return The semester field as a Semester object.
 */
Semester Research::getSemester() const {
    return semester;
}

/**
 * @brief An accessor for the semester field.
 * @return The semester field as a string.
 */
std::string Research::getSemesterStr() const {
    if (semester == Semester::SPRING) {
        return "Spring";
    } else if (semester == Semester::FALL) {
        return "Fall";
    } else if (semester == Semester::SUMMER) {
        return "Summer";
    } else {
        throw std::invalid_argument("Unknown semester");
    }
}

/**
 * @brief An accessor for the topic field.
 * @return The topic field as a Topic object.
 */
Topic Research::getTopic() const {
    return topic;
}

/**
 * @brief An accessor for the topic field.
 * @return The topic field as a string.
 */
std::string Research::getTopicStr() const {
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
void Research::setYear(uint16_t year) {
    this->year = year;
}

/**
 * @brief A mutator for the semester field.
 * @param semester The new Semester object to be set.
 */
void Research::setSemester(const Semester& semester) {
    this->semester = semester;
}

/**
 * @brief A mutator for the topic field.
 * @param topic The new Topic object to be set.
 */
void Research::setTopic(const Topic& topic) {
    this->topic = topic;
}
