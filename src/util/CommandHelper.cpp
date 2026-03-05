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
CommandHelper::CommandHelper(const std::string& filepath, 
        const std::string& outputPreamble) : filepath(filepath), 
        outputPreamble(outputPreamble) {

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

    const std::vector<std::unique_ptr<Group>>& groups = manager->getGroups();
    if (hasFilterType) {
        filterType = qHelper->translateGroupType(filterType);
        bool validType = qHelper->isValidGroupType(filterType);
        if (!validType) {
            std::cerr << outputPreamble << "ERROR, unknown type \""
                      << filterType << "\". Please try again." << std::endl;
            return;
        }
    } else if (hasFilterSemester) {
        filterSemester = qHelper->translateSemester(filterSemester);
        bool validSemester = qHelper->isValidSemester(filterSemester);
        if (!validSemester) {
            std::cerr << outputPreamble << "ERROR, unknown semester \""
                      << filterSemester << "\". Please try again." << std::endl;
            return;
        }
    } else if (hasFilterTopic) {
        filterTopic = qHelper->translateTopic(filterTopic);
        bool validTopic = qHelper->isValidTopic(filterTopic);
        if (!validTopic) {
            std::cerr << outputPreamble << "ERROR, unknown topic \""
                      << filterTopic << "\". Please try again." << std::endl;
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
                if (filterSemester != cGroup->getSemester()) continue;
            } else if (Research* rGroup = dynamic_cast<Research*>(group.get())) {
                if (filterSemester != rGroup->getSemester()) continue;
            } else if (SelfStudy* sGroup = dynamic_cast<SelfStudy*>(group.get())) {
                if (filterSemester != sGroup->getSemester()) continue;
            }
        } else if (hasFilterTopic) {
            if (Class* cGroup = dynamic_cast<Class*>(group.get())) {
                if (filterTopic != cGroup->getTopic()) continue;
            } else if (DevWork* dGroup = dynamic_cast<DevWork*>(group.get())) {
                if (filterTopic != dGroup->getTopic()) continue;
            } else if (Research* rGroup = dynamic_cast<Research*>(group.get())) {
                if (filterTopic != rGroup->getTopic()) continue;
            } else if (SelfStudy* sGroup = dynamic_cast<SelfStudy*>(group.get())) {
                if (filterTopic != sGroup->getTopic()) continue;
            }
        }

        listTypes.push_back(groupType);
        listNames.push_back(group->getName());
    }

    int namesSize = static_cast<int>(listNames.size());
    if (namesSize > 0) std::cout << "==================== Groups "
                                 << "====================" 
                                 << std::endl;
    for (int i = 0; i < namesSize; i++) {
        std::cout << "(" << i << ") " << listTypes.at(i) 
                  << ": " << listNames.at(i) << std::endl;
    }
    if (namesSize > 0) std::cout << "============================"
                                 << "====================" 
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
            std::cerr << outputPreamble << "ERROR, the name " << groupName
                      << "has already been taken for a group. "
                      << "Please try again." << std::endl;
        }
    }
    std::string groupType = qHelper->queryGroupType();

    std::unique_ptr<Group> newGroup;
    if (groupType == "Class") {
        uint16_t groupYear = qHelper->queryGroupYear();
        std::string semester = qHelper->queryGroupSemester();
        std::string topic = qHelper->queryGroupTopic();
        newGroup = std::make_unique<Class>(groupCounter, groupName, 
                groupYear, semester, topic, 255);
    } else if (groupType == "DevWork") {
        uint16_t groupYear = qHelper->queryGroupYear();
        std::string topic = qHelper->queryGroupTopic();
        newGroup = std::make_unique<DevWork>(groupCounter, groupName,
                groupYear, topic);
    } else if (groupType == "Research") {
        uint16_t groupYear = qHelper->queryGroupYear();
        std::string semester = qHelper->queryGroupSemester();
        std::string topic = qHelper->queryGroupTopic();
        newGroup = std::make_unique<Research>(groupCounter, groupName, 
                groupYear, semester, topic);
    } else if (groupType == "SelfStudy") {
        uint16_t groupYear = qHelper->queryGroupYear();
        std::string semester = qHelper->queryGroupSemester();
        std::string topic = qHelper->queryGroupTopic();
        newGroup = std::make_unique<SelfStudy>(groupCounter, groupName,
                groupYear, semester, topic);
    }
        
    manager->addGroup(std::move(newGroup));
    std::cout << outputPreamble << "Successfully added the group \"" 
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
        if (remAll) {
            std::cerr << outputPreamble
                      << "Invalid command, you can't have a specific name when "
                      << "trying to use the \"all\" flag." << std::endl;
                return;
        }
        if (!manager->containsGroup(groupName)) {
            std::cerr << outputPreamble << "ERROR, can't find a group with the name \""
                      << groupName << "\". Please try again." << std::endl;
            return;
        }
    }

    if (remAll) filterCounter ++;
    if (hasFilterType) filterCounter ++;
    if (hasFilterSemester) filterCounter ++;
    if (hasFilterTopic) filterCounter ++;
    if (filterCounter > 1) {
        std::cerr << outputPreamble << "Invalid command, you can't use "
                  << "multiple filters at the same time." << std::endl;
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
            std::cout << outputPreamble << "Successfully removed all groups." 
                      << std::endl;
        }
        return;
    } else if (hasFilterType) {
        filterType = qHelper->translateGroupType(filterType);
        bool validType = qHelper->isValidGroupType(filterType);
        if (!validType) {
            std::cerr << outputPreamble << "ERROR, unknown type \""
                      << filterType << "\". Please try again." << std::endl;
            return;
        }
    } else if (hasFilterSemester) {
        filterSemester = qHelper->translateSemester(filterSemester);
        bool validSemester = qHelper->isValidSemester(filterSemester);
        if (!validSemester) {
            std::cerr << outputPreamble << "ERROR, unknown semester \""
                      << filterSemester << "\". Please try again." << std::endl;
            return;
        }
    } else if (hasFilterTopic) {
        filterTopic = qHelper->translateTopic(filterTopic);
        bool validTopic = qHelper->isValidTopic(filterTopic);
        if (!validTopic) {
            std::cerr << outputPreamble << "ERROR, unknown topic \""
                      << filterTopic << "\". Please try again." << std::endl;
            return;
        }
    }

    
    std::vector<std::string> remNames;
    std::vector<int> toRemove;
    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        Group* group = groups.at(i).get();
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
                } else if (Class* cGroup = dynamic_cast<Class*>(group)) {
                    if (filterSemester == cGroup->getSemester()) {
                        toRemove.push_back(cGroup->getIdNum());
                        remNames.push_back(cGroup->getName());
                        continue;
                    } 
                } else if (Research* rGroup = dynamic_cast<Research*>(group)) {
                    if (filterSemester == rGroup->getSemester()) {
                        toRemove.push_back(rGroup->getIdNum());
                        remNames.push_back(rGroup->getName());
                        continue;
                    } 
                } else if (SelfStudy* sGroup = dynamic_cast<SelfStudy*>(group)) {
                    if (filterSemester == sGroup->getSemester()) {
                        toRemove.push_back(sGroup->getIdNum());
                        remNames.push_back(sGroup->getName());
                        continue;
                    } 
                }
            } else if (hasFilterTopic) {
                if (Class* cGroup = dynamic_cast<Class*>(group)) {
                    if (filterTopic == cGroup->getTopic()) {
                        toRemove.push_back(cGroup->getIdNum());
                        remNames.push_back(cGroup->getName());
                        continue;
                    }
                } else if (DevWork* dGroup = dynamic_cast<DevWork*>(group)) {
                    if (filterTopic == dGroup->getTopic()) {
                        toRemove.push_back(dGroup->getIdNum());
                        remNames.push_back(dGroup->getName());
                        continue;
                    }
                } else if (Research* rGroup = dynamic_cast<Research*>(group)) {
                    if (filterTopic == rGroup->getTopic()) {
                        toRemove.push_back(rGroup->getIdNum());
                        remNames.push_back(rGroup->getName());
                        continue;
                    } 
                } else if (SelfStudy* sGroup = dynamic_cast<SelfStudy*>(group)) {
                    if (filterTopic == sGroup->getTopic()) {
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
        std::cout << outputPreamble << "Successfully removed the group \"" 
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
        std::cerr << outputPreamble << "Invalid command, you can't "
                  << "use multiple filters at the same time."
                  << std::endl;
        return;
    }

    bool validName = manager->containsGroup(groupName);
    if (!validName) {
        std::cerr << outputPreamble
                  << "ERROR, can't find a group with the name \""
                  << groupName << "\". Please try again." << std::endl;
        return;
    }

    const std::vector<std::unique_ptr<Task>>& tasks = manager->getTasks(groupName);
    if (hasFilterType) {
        filterType = qHelper->translateTaskType(filterType);
        bool validType = qHelper->isValidTaskType(filterType);
        if (!validType) {
            std::cerr << outputPreamble << "ERROR, unknown task type of \""
                      << filterType << "\". Please try again." << std::endl;
        }
    }

    std::vector<std::string> listTypes;
    std::vector<std::string> listNames;
    std::vector<std::string> listDates;
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        Task* task = tasks.at(i).get();
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
            else date = task->getDate();
        } else if (date2Flag) {
            bool validDate = qHelper->isValidTaskDate2(task->getDate());
            if (!validDate) continue;
            else date = task->getDate();
        } else if (date3Flag) {
            bool validDate = qHelper->isValidTaskDate3(task->getDate());
            if (!validDate) continue;
            else date = task->getDate();
        }

        listDates.push_back(date);
        listTypes.push_back(taskType);
        listNames.push_back(task->getName());
    }

    const int dueDateSpacer = 40;
    int namesSize = static_cast<int>(listNames.size());
    if (namesSize > 0) {
        std::cout << "====================== Tasks {" << groupName 
                  << "} ======================" << std::endl;
    }

    for (int i = 0; i < namesSize; i++) {
        std::string index = std::to_string(i);
        if (dateFilterCounter != 0) {
            std::cout << "(" << index << ") " << listTypes.at(i) 
                      << ": " << listNames.at(i);
            int outStrSize = index.size() + listTypes.at(i).size() 
                        + listNames.at(i).size() + 5; // random spaces and punctuation
            
            for (int j = 0; j < dueDateSpacer - outStrSize; j++) {
                std::cout << " ";
            } 

            std::cout << "Due: " << listDates.at(i) << std::endl;
        } else {
            std::cout << "(" << i << ") " << listTypes.at(i) 
                      << ": " << listNames.at(i) << std::endl;
        }  
    }
    if (namesSize > 0) {
        std::cout << "================================";
        for (int i = 0; i < static_cast<int>(groupName.size()); i++) {
            std::cout << "=";
        }
        std::cout << "======================" << std::endl;
    }
}

/**
 *
 */
void CommandHelper::addTaskCommand(std::string groupName) {

    bool validGroupName = manager->containsGroup(groupName);
    if (!validGroupName) {
        std::cerr << outputPreamble
                  << "ERROR, can't find a group with the name \""
                  << groupName << "\". Please try again." << std::endl;
        return;
    }
    int taskCounter = static_cast<int>(manager->getTasks(groupName).size());

    std::string taskName;
    bool validTaskName = false;
    while (!validTaskName) {
        taskName = qHelper->queryTaskName();
        validTaskName = !(manager->containsTask(groupName, taskName));
        if (!validTaskName) {
            std::cerr << outputPreamble << "ERROR, the name \"" 
                      << taskName << "\" has already been "
                      << "taken by a task in the group {" 
                      << groupName << "}. Please try again." 
                      << std::endl;
        }
    }
        
    std::string taskType = qHelper->queryTaskType();
    std::string taskDate = qHelper->queryTaskDate();

    std::unique_ptr<Task> newTask;
    if (taskType == "Chore") {
        newTask = std::make_unique<Chore>(taskCounter,
            taskName, taskDate, false);
    } else if (taskType == "Exam") {
        newTask = std::make_unique<Exam>(taskCounter,
            taskName, taskDate, false, 255);
    } else if (taskType == "Homework") {
        newTask = std::make_unique<Homework>(taskCounter,
            taskName, taskDate, false, 255);
    } else if (taskType == "Lab") {
        newTask = std::make_unique<Lab>(taskCounter,
            taskName, taskDate, false, 255);       
    } else if (taskType == "LabAssignment") {
        newTask = std::make_unique<LabAssignment>(taskCounter,
            taskName, taskDate, false, 255);
    } else if (taskType == "Notes") {
        newTask = std::make_unique<Notes>(taskCounter,
            taskName, taskDate, false, 255);
    } else if (taskType == "Presentation") {
        newTask = std::make_unique<Presentation>(taskCounter,
            taskName, taskDate, false, 255);
    } else if (taskType == "Programming") {
        newTask = std::make_unique<Programming>(taskCounter,
            taskName, taskDate, false, 255);
    } else if (taskType == "Project") {
        newTask = std::make_unique<Project>(taskCounter,
            taskName, taskDate, false, 255);
    } else if (taskType == "Quiz") {
        newTask = std::make_unique<Quiz>(taskCounter, 
            taskName, taskDate, false, 255);
    } else if (taskType == "Reading") {
        newTask = std::make_unique<Reading>(taskCounter,
            taskName, taskDate, false, 255);
    }
        
    manager->addTask(groupName, std::move(newTask));
    std::cout << outputPreamble << "Successfully added the task \"" << taskName 
              << "\" to the group {" << groupName << "}." << std::endl;
}

/**
 *
 */
void CommandHelper::removeTaskCommand(std::string groupName, std::string taskName,
            std::string filterType, bool allFlag, bool statusFlag) {

    bool validGroupName = manager->containsGroup(groupName);
    if (!validGroupName) {
        std::cerr << outputPreamble
                  << "ERROR, could not find a group with the name \""
                  << groupName << "\". Please try again." << std::endl;
        return;
    }

    bool hasName = !taskName.empty();
    bool hasFilterType = !filterType.empty();

    if (hasName) {
        if (hasFilterType || allFlag || statusFlag) {
            std::cerr << outputPreamble 
                      << "Invalid command, you can't set a name when "
                      << "trying to use the \"all\" or \"status\" flags." 
                      << std::endl;
                return;
        }
        if (!manager->containsTask(groupName, taskName)) {
            std::cerr << outputPreamble << "ERROR, could not find a task with the name "
                      << "in the group {" << groupName << "}. Please try again."
                      << std::endl;
            return;
        }
    }

    int filterCounter = 0;
    if (hasFilterType) filterCounter ++;
    if (allFlag) filterCounter ++;
    if (statusFlag) filterCounter ++;
    if (filterCounter > 1) {
        std::cerr << outputPreamble << "Invalid command, you can't set more "
                  << "than one date flag at a time." << std::endl;
        return;
    } else if (filterCounter == 0 && !hasName) {
        std::cerr << outputPreamble << "Invalid command, you must set a flag to "
                  << "specify the tasks to be removed." << std::endl;
        return;
    }

    const std::vector<std::unique_ptr<Group>>& groups = manager->getGroups();
    if (hasFilterType) {
        filterType = qHelper->translateTaskType(filterType);
        bool validType = qHelper->isValidTaskType(filterType);
        if (!validType) {
            std::cerr << outputPreamble << "ERROR, could not find group a with the type \""
                      << filterType << "\". Please try again." << std::endl;
            return;
        }
    } else if (allFlag) {
        bool response = qHelper->queryRemAllTasks();
        if (response) {
            manager->clearAllTasks(groupName);
            std::cout << outputPreamble << "Succesfully removed all the tasks in the group {"
                      << groupName << "}." << std::endl;
        }
        return; 
    }

    std::vector<int> toRemove;
    std::vector<std::string> remNames;
    const std::vector<std::unique_ptr<Task>>& tasks = manager->getTasks(groupName);
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        Task* task = tasks.at(i).get();
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
        std::cout << outputPreamble << "Successfully removed the task \"" 
                  << remNames.at(i) << "\" from the group {" 
                  << groupName << "}." << std::endl;
    }
}

/**
 *
 */
void CommandHelper::countTasksCommand(std::string groupName, std::string filterType,
        bool allFlag, bool statusFlag, bool date1Flag, bool date2Flag, bool date3Flag) {

    int dateFilterCounter = 0;
    if (date1Flag) dateFilterCounter++;
    if (date2Flag) dateFilterCounter++;
    if (date3Flag) dateFilterCounter++;
    if (dateFilterCounter > 1) {
        std::cerr << outputPreamble << "Invalid command, you can't set "
                  << "more than one date flag at a time." << std::endl;
    }

    int taskCounter = 0;
    bool hasGroupName = !groupName.empty();
    bool hasFilterType = !filterType.empty();

    if (hasFilterType) {
        std::string filterType = qHelper->translateTaskType(filterType);
        bool validType = qHelper->isValidTaskType(filterType);
        if (!validType) {
            std::cerr << outputPreamble << "ERROR, unknown type \""
                      << filterType << "\". Please try again." << std::endl;
        }
    }

    if (hasGroupName) {
        if (allFlag) {
            std::cerr << outputPreamble << "Invalid command, you can't use the " 
                      << "\"all\" and \"group\" flag together." << std::endl;
            return;
        }
        bool validName = manager->containsGroup(groupName);
        if (!validName) {
            std::cerr << outputPreamble << "ERROR, could not find a "
                      << "group with the name \"" << groupName 
                      << "\". Please try again." << std::endl;
            return;
        }

        const std::vector<std::unique_ptr<Task>>& tasks = manager->getTasks(groupName);
        for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
            Task* task = tasks.at(i).get();
            std::string taskType = task->getType();
            if (hasFilterType && filterType != taskType) continue;
            if (statusFlag && task->getStatus()) continue;
            
            if (date1Flag) {
                bool validDate = qHelper->isValidTaskDate1(task->getDate());
                if (!validDate) continue;
            } else if (date2Flag) {
                bool validDate = qHelper->isValidTaskDate2(task->getDate());
                if (!validDate) continue;
            } else if (date3Flag) {
                bool validDate = qHelper->isValidTaskDate3(task->getDate());
                if (!validDate) continue;
            }

            taskCounter++;
        }
    } else if (allFlag) {
        const std::vector<std::unique_ptr<Group>>& groups = manager->getGroups();
        for (int i = 0; i < static_cast<int>(groups.size()); i++) {
            Group* group = groups.at(i).get();
            const std::vector<std::unique_ptr<Task>>& tasks = group->getTasks();
            for (int j = 0; j < static_cast<int>(tasks.size()); j++) {
                Task* task = tasks.at(i).get();
                if (hasFilterType && filterType != task->getType()) continue;
                if (statusFlag && task->getStatus()) continue;
            
                if (date1Flag) {
                    bool validDate = qHelper->isValidTaskDate1(task->getDate());
                    if (!validDate) continue;
                } else if (date2Flag) {
                    bool validDate = qHelper->isValidTaskDate2(task->getDate());
                    if (!validDate) continue;
                } else if (date3Flag) {
                    bool validDate = qHelper->isValidTaskDate3(task->getDate());
                    if (!validDate) continue;
                }

                taskCounter++;
            }
        }
    } else {
        std::cout << outputPreamble << "Invalid command, you must set either "
                  << "the \"group\" or \"all\" flag." << std::endl;
    }

    std::cout << outputPreamble << "Tasks counted: " 
              << std::to_string(taskCounter) << std::endl;
}
