#include "groups/SelfStudy.hpp"

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

void SelfStudy::setSemester(const Semester& semester) {
    this->semester = semester;
}

Topic SelfStudy::getTopic() const {
    return topic;
}

void SelfStudy::setTopic(const Topic& topic) {
    this->topic = topic;
}
