// Group header file
#include "groups/Group.hpp"



/**
 * @brief A constructor for the class.
 * @param idNum The identification number of the group.
 * @param name The name of the group.
 */
Group::Group(int idNum, const std::string& name) 
    : idNum(idNum), name(name) {}

/**
 * @brief An accessor for the idNum field.
 * @return The idNum field as an integer.
 */
int Group::getIdNum() {
    return idNum;
}

/**
 * @brief An accesor for the name field.
 * @return The name field as a string.
 */
std::string Group::getName() {
    return name;
}

/**
 * @brief An accessor for the type field.
 * @return The type field as a string.
 */
std::string Group::getType() {
    return TYPE;
}

/**
 * @brief A mutator for the idNum field.
 * @param idNum The new idNum to be set.
 */
void Group::setIdNum(int idNum) {
    this->idNum = idNum;
}

/**
 * @brief A mutator for the name field.
 * @param name The new name to be set.
 */
void Group::setName(const std::string& name) {
    this->name = name;
}
