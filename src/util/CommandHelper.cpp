// Group header files
#include "groups/Group.hpp"
#include "groups/Class.hpp"
#include "groups/DevWork.hpp"
#include "groups/Research.hpp"
#include "groups/SelfStudy.hpp"

// Task header files
#include "tasks/Task.hpp"
#include "tasks/Chore.hpp"
#include "tasks/Exam.hpp"
#include "tasks/Homework.hpp"
#include "tasks/Lab.hpp"
#include "tasks/LabAssignment.hpp"
#include "tasks/Notes.hpp"
#include "tasks/Presentation.hpp"
#include "tasks/Programming.hpp"
#include "tasks/Project.hpp"
#include "tasks/Quiz.hpp"
#include "tasks/Reading.hpp"

// Utility header files
#include "util/CommandHelper.hpp"
#include "util/GroupManager.hpp"
#include "util/QueryHelper.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"

// Built in libraries
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>
#include <stdexcept>


/**
 *
 */
CommandHelper::CommandHelper(const std::string& filepath, const std::string& outputPreamble) 
        : filepath(filepath), outputPreamble(outputPreamble) {

    manager = std::make_unique<GroupManager>(filepath, outputPreamble);
    qHelper = std::make_unique<QueryHelper>(outputPreamble);
}

/**
 *
 */
void CommandHelper::listGroupsCommand(std::string filterType, 
        std::string filterSemester, std::string filterTopic) {
    
    int filterCounter = 0;
    bool hasFilterType = !filterType.empty();
    bool hasFilterSemester = !filterSemester.empty();
    bool hasFilterTopic = !filterTopic.empty();

    if (hasFilterType) filterCounter ++;
    if (hasFilterSemester) filterCounter ++;
    if (hasFilterTopic) filterCounter ++;
    if (filterCounter > 1) {
        std::cerr << outputPreamble
                  << "Invalid command, can't use multiple filters at the same time"
                  << std::endl;
        return;
    }

    const std::vector<std::unique_ptr<Group>>& groups = manager->getGroups();
    if (hasFilterType) {
        filterType = qHelper->translateGroupType(filterType);
        bool validType = qHelper->isValidGroupType(filterType);
        if (!validType) {
            std::cerr << outputPreamble << "ERROR when trying to find type \""
                      << filterType << "\", please try again." << std::endl;
            return;
        }
    } else if (hasFilterSemester) {
        filterSemester = qHelper->translateSemester(filterSemester);
        bool validSemester = qHelper->isValidSemester(filterSemester);
        if (!validSemester) {
            std::cerr << outputPreamble << "ERROR when trying to find semester \""
                      << filterSemester << "\", please try again." << std::endl;
            return;
        }
    } else if (hasFilterTopic) {
        filterTopic = qHelper->translateTopic(filterTopic);
        bool validTopic = qHelper->isValidTopic(filterTopic);
        if (!validTopic) {
            std::cerr << outputPreamble << "ERROR when trying to find topic \""
                      << filterTopic << "\", please try again." << std::endl;
            return;
        }
    }

    std::vector<std::string> listTypes;
    std::vector<std::string> listNames;
    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        const std::unique_ptr<Group>& group = groups.at(i);
        std::string groupType = group->getType();
        
        if (hasFilterType && filterType != groupType) {
            continue;
        } else if (hasFilterSemester) {
            if (groupType != "Class" && groupType != "Research" && 
                    groupType != "SelfStudy") {
                continue;
            } else if (Class* cGroup = dynamic_cast<Class*>(group.get())) {
                if (filterSemester != cGroup->getSemesterStr()) continue;
            } else if (Research* rGroup = dynamic_cast<Research*>(group.get())) {
                if (filterSemester != rGroup->getSemesterStr()) continue;
            } else if (SelfStudy* sGroup = dynamic_cast<SelfStudy*>(group.get())) {
                if (filterSemester != sGroup->getSemesterStr()) continue;
            }
        } else if (hasFilterTopic) {
            if (Class* cGroup = dynamic_cast<Class*>(group.get())) {
                if (filterTopic != cGroup->getTopicStr()) continue;
            } else if (DevWork* dGroup = dynamic_cast<DevWork*>(group.get())) {
                if (filterTopic != dGroup->getTopicStr()) continue;
            } else if (Research* rGroup = dynamic_cast<Research*>(group.get())) {
                if (filterTopic != rGroup->getTopicStr()) continue;
            } else if (SelfStudy* sGroup = dynamic_cast<SelfStudy*>(group.get())) {
                if (filterTopic != sGroup->getTopicStr()) continue;
            }
        }

        listTypes.push_back(groupType);
        listNames.push_back(group->getName());
    }

    int namesSize = static_cast<int>(listNames.size());
    if (namesSize > 0) std::cout << "==================== Groups ====================" 
                                 << std::endl;
    for (int i = 0; i < namesSize; i++) {
        std::cout << "(" << i << ") " << listTypes.at(i) 
                  << ": " << listNames.at(i) << std::endl;
    }
    if (namesSize > 0) std::cout << "================================================" 
                                 << std::endl;
}



/**
 *
 */
void CommandHelper::addGroupCommand() {
    int groupCounter = static_cast<int>(manager->getGroups().size());
    std::string groupName;
    bool validName = false;
    while (!validName) {
        groupName = qHelper->queryGroupName();
        validName = !manager->containsGroup(groupName);
        if (!validName) {
            std::cerr << outputPreamble
                      << "Can't add a group with a name that's already "
                      << "taken, please try again." << std::endl;
        }
    }
    std::string groupType = qHelper->queryGroupType();

    std::unique_ptr<Group> newGroup;
    if (groupType == "Class") {
        uint16_t groupYear = qHelper->queryGroupYear();
        std::string semesterStr = qHelper->queryGroupSemester();
        std::string topicStr = qHelper->queryGroupTopic();
        newGroup = std::make_unique<Class>(
            groupCounter,
            groupName,
            groupYear,
            qHelper->strToSemester(semesterStr),
            qHelper->strToTopic(topicStr),
            255
        );
    } else if (groupType == "DevWork") {
        uint16_t groupYear = qHelper->queryGroupYear();
        std::string topicStr = qHelper->queryGroupTopic();
        newGroup = std::make_unique<DevWork>(
            groupCounter,
            groupName,
            groupYear,
            qHelper->strToTopic(topicStr)
        );
    } else if (groupType == "Research") {
        uint16_t groupYear = qHelper->queryGroupYear();
        std::string semesterStr = qHelper->queryGroupSemester();
        std::string topicStr = qHelper->queryGroupTopic();
        newGroup = std::make_unique<Research>(
            groupCounter,
            groupName,
            groupYear,
            qHelper->strToSemester(semesterStr),
            qHelper->strToTopic(topicStr)
        );
    } else if (groupType == "SelfStudy") {
        uint16_t groupYear = qHelper->queryGroupYear();
        std::string semesterStr = qHelper->queryGroupSemester();
        std::string topicStr = qHelper->queryGroupTopic();
        newGroup = std::make_unique<SelfStudy>(
            groupCounter,
            groupName,
            groupYear,
            qHelper->strToSemester(semesterStr),
            qHelper->strToTopic(topicStr)
        );
    }
        
    manager->addGroup(std::move(newGroup));
    std::cout << outputPreamble << "Added group \"" 
              << groupName << "\"." << std::endl;
}



/**
 *
 */
void CommandHelper::removeGroupCommand(std::string groupName, bool remAll, 
        std::string filterType, std::string filterSemester, 
        std::string filterTopic) {

    int filterCounter = 0;
    bool hasName = !groupName.empty();
    bool hasFilterType = !filterType.empty();
    bool hasFilterSemester = !filterSemester.empty();
    bool hasFilterTopic = !filterTopic.empty();

    if (hasName) {
        if (remAll || hasFilterType || hasFilterSemester || hasFilterTopic) {
            std::cerr << outputPreamble
                      << "Invalid command, can't have a specific name when "
                      << "trying to use a filter flag." << std::endl;
                return;
        }
        if (!manager->containsGroup(groupName)) {
            std::cerr << outputPreamble << "Invalid command, no group of that name."
                      << std::endl;
            return;
        }
    }

    if (remAll) filterCounter ++;
    if (hasFilterType) filterCounter ++;
    if (hasFilterSemester) filterCounter ++;
    if (hasFilterTopic) filterCounter ++;
    if (filterCounter > 1) {
        std::cerr << outputPreamble
                  << "Invalid command, can't use multiple filters at the same time."
                  << std::endl;
        return;
    } else if (filterCounter == 0 && !hasName) {
        std::cerr << outputPreamble << "Invalid command, you need to set a flag."
                  << std::endl;
        return;
    }


    const std::vector<std::unique_ptr<Group>>& groups = manager->getGroups();
    if (remAll) {
        bool response = qHelper->queryRemAllGroups();
        if (response) {
            manager->clearAllGroups();
            std::cout << outputPreamble << "Removed all groups" << std::endl;
        }
        return;
    } else if (hasFilterType) {
        filterType = qHelper->translateGroupType(filterType);
        bool validType = qHelper->isValidGroupType(filterType);
        if (!validType) {
            std::cerr << outputPreamble << "ERROR when trying to find type \""
                      << filterType << "\", please try again." << std::endl;
            return;
        }
    } else if (hasFilterSemester) {
        filterSemester = qHelper->translateSemester(filterSemester);
        bool validSemester = qHelper->isValidSemester(filterSemester);
        if (!validSemester) {
            std::cerr << outputPreamble << "ERROR when trying to find semester \""
                      << filterSemester << "\", please try again." << std::endl;
            return;
        }
    } else if (hasFilterTopic) {
        filterTopic = qHelper->translateTopic(filterTopic);
        bool validTopic = qHelper->isValidTopic(filterTopic);
        if (!validTopic) {
            std::cerr << outputPreamble << "ERROR when trying to find topic \""
                      << filterTopic << "\", please try again." << std::endl;
            return;
        }
    }

    
    std::vector<std::string> remNames;
    std::vector<int> toRemove;
    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        const std::unique_ptr<Group>& group = groups.at(i);
        std::string groupType = group->getType();
        if (hasName) {
            if (group->getName() == groupName) {
                toRemove.push_back(group->getIdNum());
                remNames.push_back(groupName);
                break;
            } else { continue; }
        } else {
            if (hasFilterType && filterType == groupType) {
                toRemove.push_back(group->getIdNum());
                remNames.push_back(group->getName());
                continue;
            } else if (hasFilterSemester) {
                if (groupType != "Class" && groupType != "Research" && 
                        groupType != "SelfStudy") {
                    continue;
                    
                } else if (Class* cGroup = dynamic_cast<Class*>(group.get())) {
                    if (filterSemester == cGroup->getSemesterStr()) {
                        toRemove.push_back(cGroup->getIdNum());
                        remNames.push_back(cGroup->getName());
                        continue;
                    } 
                } else if (Research* rGroup = dynamic_cast<Research*>(group.get())) {
                    if (filterSemester == rGroup->getSemesterStr()) {
                        toRemove.push_back(rGroup->getIdNum());
                        remNames.push_back(rGroup->getName());
                        continue;
                    } 
                } else if (SelfStudy* sGroup = dynamic_cast<SelfStudy*>(group.get())) {
                    if (filterSemester == sGroup->getSemesterStr()) {
                        toRemove.push_back(sGroup->getIdNum());
                        remNames.push_back(sGroup->getName());
                        continue;
                    } 
                }
            } else if (hasFilterTopic) {
                if (Class* cGroup = dynamic_cast<Class*>(group.get())) {
                    if (filterTopic == cGroup->getTopicStr()) {
                        toRemove.push_back(cGroup->getIdNum());
                        remNames.push_back(cGroup->getName());
                        continue;
                    }
                } else if (DevWork* dGroup = dynamic_cast<DevWork*>(group.get())) {
                    if (filterTopic == dGroup->getTopicStr()) {
                        toRemove.push_back(dGroup->getIdNum());
                        remNames.push_back(dGroup->getName());
                        continue;
                    }
                } else if (Research* rGroup = dynamic_cast<Research*>(group.get())) {
                    if (filterTopic == rGroup->getTopicStr()) {
                        toRemove.push_back(rGroup->getIdNum());
                        remNames.push_back(rGroup->getName());
                        continue;
                    } 
                } else if (SelfStudy* sGroup = dynamic_cast<SelfStudy*>(group.get())) {
                    if (filterTopic == sGroup->getTopicStr()) {
                        toRemove.push_back(sGroup->getIdNum());
                        remNames.push_back(sGroup->getName());
                        continue;
                    }
                }
            }
        }
    }

    for (int i = 0; i < static_cast<int>(toRemove.size()); i++) {
        manager->removeGroup(toRemove.at(i));
        std::cout << outputPreamble << "Removed group \"" 
                  << remNames.at(i) << "\"." << std::endl;
    }
}



/**
 *
 */
void CommandHelper::listTasksCommand(std::string groupName, 
        std::string filterType, bool dateFlag, bool date1Flag,
        bool date2Flag, bool date3Flag) {

    int filterCounter = 0;
    int dateFilterCounter = 0;
    bool hasFilterType = !filterType.empty();
    if (dateFlag) filterCounter ++;
    if (date1Flag) filterCounter ++;
    if (date2Flag) filterCounter ++;
    if (date3Flag) filterCounter ++;
    dateFilterCounter = filterCounter; // In case future flags are added.
    if (filterCounter > 1) {
        std::cerr << outputPreamble
                  << "Invalid command, can't use multiple filters at the same time."
                  << std::endl;
        return;
    }

    bool validName = manager->containsGroup(groupName);
    if (!validName) {
        std::cerr << outputPreamble
                  << "ERROR when trying to find group with name of \""
                  << groupName << "\", please try again." << std::endl;
        return;
    }

    const std::vector<std::unique_ptr<Task>>& tasks = manager->getTasks(groupName);
    if (hasFilterType) {
        std::string filterType = qHelper->translateTaskType(filterType);
        bool validType = qHelper->isValidTaskType(filterType);
        if (!validType) {
            std::cerr << outputPreamble << "ERROR when trying to find task with type of \""
                      << filterType << "\", please try again." << std::endl;
        }
    }

    std::vector<std::string> listTypes;
    std::vector<std::string> listNames;
    std::vector<std::string> listDates;
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        const std::unique_ptr<Task>& task = tasks.at(i);
        std::string taskType = task->getType();
        if (hasFilterType && filterType != taskType) {
            continue;
        }

        std::string date;
        if (dateFlag) {
            date = task->getDate();
        } else if (date1Flag) {
            bool validDate = qHelper->isValidTaskDate1(task->getDate());
            if (!validDate) continue;
        } else if (date2Flag) {
            bool validDate = qHelper->isValidTaskDate2(task->getDate());
            if (!validDate) continue;
        } else if (date3Flag) {
            bool validDate = qHelper->isValidTaskDate3(task->getDate());
            if (!validDate) continue;
        }

        if (!date.empty()) listDates.push_back(date);
        listTypes.push_back(taskType);
        listNames.push_back(task->getName());
    }

    int namesSize = static_cast<int>(listNames.size());
    if (namesSize > 0) {
        std::cout << "==================== Tasks (" << groupName 
                  << ") ====================" << std::endl;
    }
    for (int i = 0; i < namesSize; i++) {
        if (dateFilterCounter != 0) {
            std::cout << "(" << i << ") " << listTypes.at(i) << ": " 
                      << listNames.at(i) << "        Due " << listDates.at(i)
                      << std::endl;
        } else {
            std::cout << "(" << i << ") " << listTypes.at(i) 
                      << ": " << listNames.at(i) << std::endl;
        }  
    }
    if (namesSize > 0) {
        std::cout << "==============================";
        for (int i = 0; i < static_cast<int>(groupName.size()); i++) {
            std::cout << "=";
        }
        std::cout << "====================" << std::endl;
    }
}



/**
 *
 */
void CommandHelper::addTaskCommand(std::string groupName) {

    bool validGroupName = manager->containsGroup(groupName);
    if (!validGroupName) {
        std::cerr << outputPreamble
                  << "ERROR when trying to find group with name of \""
                  << groupName << "\", please try again." << std::endl;
        return;
    }
    int taskCounter = static_cast<int>(manager->getTasks(groupName).size());

    std::string taskName;
    bool validTaskName = false;
    while (!validTaskName) {
        taskName = qHelper->queryTaskName();
        validTaskName = !manager->containsTask(groupName, taskName);
        if (!validTaskName) {
            std::cerr << outputPreamble 
                      << "Can't add a task with a name that's already "
                      << "taken, please try again." << std::endl;
        }
    }
        
    std::string taskType = qHelper->queryTaskType();
    std::string taskDate = qHelper->queryTaskDate();

    std::unique_ptr<Task> newTask;
    if (taskType == "Chore") {
        newTask = std::make_unique<Chore>(
            taskCounter,
            taskName,
            taskDate,
            false
        );
    } else if (taskType == "Exam") {
        newTask = std::make_unique<Exam>(
            taskCounter,
            taskName,
            taskDate,
            false,
            255 // Upper limit for 16 bit unsigned to indicate N/A
        );
    } else if (taskType == "Homework") {
        newTask = std::make_unique<Homework>(
            taskCounter,
            taskName,
            taskDate,
            false,
            255 // Upper limit for 16 bit unsigned to indicate N/A
        );
    } else if (taskType == "Lab") {
        newTask = std::make_unique<Lab>(
            taskCounter,
            taskName,
            taskDate,
            false,
            255 // Upper limit for 16 bit unsigned to indicate N/A
        );       
    } else if (taskType == "LabAssignment") {
        newTask = std::make_unique<LabAssignment>(
            taskCounter,
            taskName,
            taskDate,
            false,
            255 // Upper limit for 16 bit unsigned to indicate N/A
        );       
    } else if (taskType == "Notes") {
        newTask = std::make_unique<Notes>(
            taskCounter,
            taskName,
            taskDate,
            false,
            255 // Upper limit for 16 bit unsigned to indicate N/A
        );       
    } else if (taskType == "Presentation") {
        newTask = std::make_unique<Presentation>(
            taskCounter,
            taskName,
            taskDate,
            false,
            255 // Upper limit for 16 bit unsigned to indicate N/A
        );       
    } else if (taskType == "Programming") {
        newTask = std::make_unique<Programming>(
            taskCounter,
            taskName,
            taskDate,
            false,
            255 // Upper limit for 16 bit unsigned to indicate N/A
        );       
    } else if (taskType == "Project") {
        newTask = std::make_unique<Project>(
            taskCounter,
            taskName,
            taskDate,
            false,
            255 // Upper limit for 16 bit unsigned to indicate N/A
        );       
    } else if (taskType == "Quiz") {
        newTask = std::make_unique<Quiz>(
            taskCounter,
            taskName,
            taskDate,
            false,
            255 // Upper limit for 16 bit unsigned to indicate N/A
        );       
    } else if (taskType == "Reading") {
        newTask = std::make_unique<Reading>(
            taskCounter,
            taskName,
            taskDate,
            false,
            255 // Upper limit for 16 bit unsigned to indicate N/A
        );      
    }
        
    manager->addTask(groupName, std::move(newTask));
    std::cout << outputPreamble << "Added task \"" 
              << taskName << "\"." << std::endl;
}



void CommandHelper::removeTaskCommand(std::string groupName, std::string taskName,
            std::string filterType, bool allFlag, bool statusFlag) {

    bool validGroupName = manager->containsGroup(groupName);
    if (!validGroupName) {
        std::cerr << outputPreamble
                  << "ERROR when trying to find group with name of \""
                  << groupName << "\", please try again." << std::endl;
        return;
    }

    bool hasName = !taskName.empty();
    bool hasFilterType = !filterType.empty();

    if (hasName) {
        if (hasFilterType || allFlag || statusFlag) {
            std::cerr << outputPreamble 
                      << "Invalid command, can't have a specific name when "
                      << "trying to use a filter flag." << std::endl;
                return;
        }
        if (!manager->containsTask(groupName, taskName)) {
            std::cerr << outputPreamble << "Invalid command, no task of that name "
                      << "in the group " << groupName << "."
                      << std::endl;
            return;
        }
    }

    int filterCounter = 0;
    if (hasFilterType) filterCounter ++;
    if (allFlag) filterCounter ++;
    if (statusFlag) filterCounter ++;
    if (filterCounter > 1) {
        std::cerr << outputPreamble
                  << "Invalid command, can't use multiple filters at the same time."
                  << std::endl;
        return;
    } else if (filterCounter == 0 && !hasName) {
        std::cerr << outputPreamble << "Invalid command, you need to set a flag."
                  << std::endl;
        return;
    }

    const std::vector<std::unique_ptr<Group>>& groups = manager->getGroups();
    if (hasFilterType) {
        filterType = qHelper->translateTaskType(filterType);
        bool validType = qHelper->isValidTaskType(filterType);
        if (!validType) {
            std::cerr << outputPreamble << "ERROR when trying to find type \""
                      << filterType << "\", please try again." << std::endl;
            return;
        }
    } else if (allFlag) {
        bool response = qHelper->queryRemAllTasks();
        if (response) {
            manager->clearAllTasks(groupName);
            std::cout << outputPreamble << "Removed all tasks in "
                      << groupName << "." << std::endl;
        }
        return; 
    }

    std::vector<int> toRemove;
    std::vector<std::string> remNames;
    const std::vector<std::unique_ptr<Task>>& tasks = manager->getTasks(groupName);
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        const std::unique_ptr<Task>& task = tasks.at(i);
        std::string taskType = task->getType();
        if (hasName) {
            if (task->getName() == taskName) {
                toRemove.push_back(task->getIdNum());
                remNames.push_back(taskName);
                break;
            } else { continue; }
        } else {
            if (hasFilterType && filterType != taskType) {
                continue;
            } else if (statusFlag) {
                if (task->getStatus()) {
                    toRemove.push_back(task->getIdNum());
                    remNames.push_back(task->getName());
                }
            }
        }
    }

    for (int i = 0; i < static_cast<int>(toRemove.size()); i++) {
        manager->removeTask(groupName, toRemove.at(i));
        std::cout << outputPreamble << "Removed task \"" 
                  << remNames.at(i) << "\"." << std::endl;
    }
}
