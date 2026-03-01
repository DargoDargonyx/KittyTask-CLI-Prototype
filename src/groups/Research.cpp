#include "groups/Research.hpp"

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

void Research::setSemester(const Semester& semester) {
    this->semester = semester;
}

Topic Research::getTopic() const {
    return topic;
}

void Research::setTopic(const Topic& topic) {
    this->topic = topic;
}
