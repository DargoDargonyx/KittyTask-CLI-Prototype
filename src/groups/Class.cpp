#include "groups/Class.hpp"

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

void Class::setSemester(const Semester& semester) {
    this->semester = semester;
}

Topic Class::getTopic() const {
    return topic;
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
