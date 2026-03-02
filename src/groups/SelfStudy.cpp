// Group header file
#include "groups/SelfStudy.hpp"

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
SelfStudy::SelfStudy(int idNum, const std::string& name, uint16_t year, 
        const Semester& semester, const Topic& topic) : Group(idNum, name) {

    this->type = "SelfStudy";
    this->year = year;
    this->semester = semester;
    this->topic = topic;
}

/**
 * @brief An accessor for the year field.
 * @return The year field as an integer.
 */
uint16_t SelfStudy::getYear() const {
    return year;
}

/**
 * @brief An accessor for the semester field.
 * @return The semester field as a Semester object.
 */
Semester SelfStudy::getSemester() const {
    return semester;
}

/**
 * @brief An accessor for the semester field.
 * @return The semester field as a string.
 */
std::string SelfStudy::getSemesterStr() const {
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
Topic SelfStudy::getTopic() const {
    return topic;
}

/**
 * @brief An accessor for the topic field.
 * @return The topic field as a string.
 */
std::string SelfStudy::getTopicStr() const {
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
void SelfStudy::setYear(uint16_t year) {
    this->year = year;
}

/**
 * @brief A mutator for the semester field.
 * @param semester The new Semester object to be set.
 */
void SelfStudy::setSemester(const Semester& semester) {
    this->semester = semester;
}

/**
 * @brief A mutator for the topic field.
 * @param topic The new Topic object to be set.
 */
void SelfStudy::setTopic(const Topic& topic) {
    this->topic = topic;
}
