#include "groups/SelfStudy.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"
#include <stdexcept>

SelfStudy::SelfStudy(int idNum, const std::string& name, uint16_t year, 
        const Semester& semester, const Topic& topic) : Group(idNum, name) {

    this->type = "SelfStudy";
    this->year = year;
    this->semester = semester;
    this->topic = topic;
}

uint16_t SelfStudy::getYear() const {
    return year;
}

void SelfStudy::setYear(uint16_t year) {
    this->year = year;
}

Semester SelfStudy::getSemester() const {
    return semester;
}

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

void SelfStudy::setSemester(const Semester& semester) {
    this->semester = semester;
}

Topic SelfStudy::getTopic() const {
    return topic;
}

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

void SelfStudy::setTopic(const Topic& topic) {
    this->topic = topic;
}
