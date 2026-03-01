#include "groups/Class.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"
#include <stdexcept>

Class::Class(int idNum, const std::string& name, 
        uint16_t year, const Semester& semester, 
        const Topic& topic, uint8_t grade) : Group(idNum, name) {

    this->type = "Class";
    this->year = year;
    this->semester = semester;
    this->topic = topic;
    this->grade = grade;
}

uint16_t Class::getYear() const {
    return year;
}

void Class::setYear(uint16_t year) {
    this->year = year;
}

Semester Class::getSemester() const {
    return semester;
}

std::string Class::getSemesterStr() const {
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

void Class::setSemester(const Semester& semester) {
    this->semester = semester;
}

Topic Class::getTopic() const {
    return topic;
}

std::string Class::getTopicStr() const {
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

void Class::setTopic(const Topic& topic) {
    this->topic = topic;
}

uint8_t Class::getGrade() const {
    return grade;
}

void Class::setGrade(uint8_t grade) {
    this->grade = grade;
}
