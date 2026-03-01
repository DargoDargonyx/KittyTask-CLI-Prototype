#include "groups/Research.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"
#include <stdexcept>

Research::Research(int idNum, const std::string& name, uint16_t year, 
        const Semester& semester, const Topic& topic) : Group(idNum, name) {

    this->type = "Research";
    this->year = year;
    this->semester = semester;
    this->topic = topic;
}

uint16_t Research::getYear() const {
    return year;
}

void Research::setYear(uint16_t year) {
    this->year = year;
}

Semester Research::getSemester() const {
    return semester;
}

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

void Research::setSemester(const Semester& semester) {
    this->semester = semester;
}

Topic Research::getTopic() const {
    return topic;
}

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

void Research::setTopic(const Topic& topic) {
    this->topic = topic;
}
