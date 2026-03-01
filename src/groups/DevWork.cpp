#include "groups/DevWork.hpp"

DevWork::DevWork(int idNum, const std::string& name, uint16_t year, 
        const Topic& topic) : Group(idNum, name) {

    this->type = "DevWork";
    this->year = year;
    this->topic = topic;
}

uint16_t DevWork::getYear() const {
    return year;
}

void DevWork::setYear(uint16_t year) {
    this->year = year;
}

Topic DevWork::getTopic() const {
    return topic;
}

void DevWork::setTopic(const Topic& topic) {
    this->topic = topic;
}
