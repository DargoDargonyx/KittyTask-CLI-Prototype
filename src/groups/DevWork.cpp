#include "groups/DevWork.hpp"
#include "util/Topic.hpp"
#include <stdexcept>

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

void DevWork::setTopic(const Topic& topic) {
    this->topic = topic;
}
