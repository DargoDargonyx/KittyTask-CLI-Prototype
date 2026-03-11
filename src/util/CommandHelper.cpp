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
#include "util/DataManager.hpp"
#include "util/QueryHelper.hpp"

// Built in libraries
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>



/**
 * @brief A constructor for the class.
 * @param filepath The filepath to the data directory.
 * @param logPreamble A text preamble for the printing output
 */
CommandHelper::CommandHelper(const std::string& filepath, 
        const std::string& logPreamble) : filepath(filepath), 
        logPreamble(logPreamble) {

    manager = std::make_unique<DataManager>(filepath, logPreamble);
    qHelper = std::make_unique<QueryHelper>(logPreamble);
}

/**
 * @brief Handles the logic for the listGroups command.
 * @param filterType The filter type option input.
 * @param filterSemester The filter semester option input.
 * @param filterTopic The filter topic option input.
 */
void CommandHelper::listGroupsCommand(std::string filterType, 
        std::string filterSemester, std::string filterTopic) {
    
    int filterCounter = 0;
    bool hasFilterType = !filterType.empty();
    bool hasFilterSemester = !filterSemester.empty();
    bool hasFilterTopic = !filterTopic.empty();

    const std::vector<std::unique_ptr<Group>>& groups = manager->loadGroupData();
    if (hasFilterType) {
        filterType = qHelper->translateGroupType(filterType);
        bool validType = qHelper->isValidGroupType(filterType);
        if (!validType) {
            std::cerr << logPreamble << "ERROR, unknown type \""
                      << filterType << "\". Please try again." << std::endl;
            return;
        }
    } else if (hasFilterSemester) {
        filterSemester = qHelper->translateSemester(filterSemester);
        bool validSemester = qHelper->isValidSemester(filterSemester);
        if (!validSemester) {
            std::cerr << logPreamble << "ERROR, unknown semester \""
                      << filterSemester << "\". Please try again." << std::endl;
            return;
        }
    } else if (hasFilterTopic) {
        filterTopic = qHelper->translateTopic(filterTopic);
        bool validTopic = qHelper->isValidTopic(filterTopic);
        if (!validTopic) {
            std::cerr << logPreamble << "ERROR, unknown topic \""
                      << filterTopic << "\". Please try again." << std::endl;
            return;
        }
    }

    std::vector<std::string> listTypes;
    std::vector<std::string> listNames;
    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        const std::unique_ptr<Group>& group = groups[i];
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
        std::cout << "(" << i << ") " << listTypes[i] 
                  << ": " << listNames[i] << std::endl;
    }
    if (namesSize > 0) std::cout << "============================"
                                 << "====================" 
                                 << std::endl;
}

/**
 * @brief Handles the logic for the addGroupCommand.
 */
void CommandHelper::addGroupCommand() {
    int groupCounter = static_cast<int>(manager->loadGroupData().size());
    std::string groupName;
    bool validName = false;
    while (!validName) {
        groupName = qHelper->queryGroupName();
        validName = manager->getGroupIdFromName(groupName) == -1;
        if (!validName) {
            std::cerr << logPreamble << "ERROR, the name " << groupName
                      << "has already been taken for a group. "
                      << "Please try again." << std::endl;
        }
    }
    std::string groupType = qHelper->queryGroupType();

    std::unique_ptr<Group> newGroup;
    if (groupType == "Class") {
        int groupYear = qHelper->queryGroupYear();
        std::string semester = qHelper->queryGroupSemester();
        std::string topic = qHelper->queryGroupTopic();
        newGroup = std::make_unique<Class>(groupCounter, groupName, 
                groupYear, semester, topic, -1);
    } else if (groupType == "DevWork") {
        int groupYear = qHelper->queryGroupYear();
        std::string topic = qHelper->queryGroupTopic();
        newGroup = std::make_unique<DevWork>(groupCounter, groupName,
                groupYear, topic);
    } else if (groupType == "Research") {
        int groupYear = qHelper->queryGroupYear();
        std::string semester = qHelper->queryGroupSemester();
        std::string topic = qHelper->queryGroupTopic();
        newGroup = std::make_unique<Research>(groupCounter, groupName, 
                groupYear, semester, topic);
    } else if (groupType == "SelfStudy") {
        int groupYear = qHelper->queryGroupYear();
        std::string semester = qHelper->queryGroupSemester();
        std::string topic = qHelper->queryGroupTopic();
        newGroup = std::make_unique<SelfStudy>(groupCounter, groupName,
                groupYear, semester, topic);
    }
        
    manager->addGroup(std::move(newGroup));
    std::cout << logPreamble << "Successfully added the group \"" 
              << groupName << "\"." << std::endl;
}

/**
 * @brief Handles the logic for the removeGroup command.
 * @param groupName The group name option input.
 * @param remAll The remove all flag.
 * @param filterType The group type option input.
 * @param filterSemester The group semester option input.
 * @param filterTopic The group topic option input.
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
            std::cerr << logPreamble << "Invalid command, you can't have "
                      << "a specific name when trying to use the \"all\" "
                      << "flag." << std::endl;
                return;
        }
        bool validName = manager->getGroupIdFromName(groupName) != -1;
        if (!validName) {
            std::cerr << logPreamble << "ERROR, can't find a group with the name \""
                      << groupName << "\". Please try again." << std::endl;
            return;
        }
    }

    if (remAll) filterCounter ++;
    if (hasFilterType) filterCounter ++;
    if (hasFilterSemester) filterCounter ++;
    if (hasFilterTopic) filterCounter ++;
    if (filterCounter > 1) {
        std::cerr << logPreamble << "Invalid command, you can't use "
                  << "multiple filters at the same time." << std::endl;
        return;
    } else if (filterCounter == 0 && !hasName) {
        std::cerr << logPreamble << "Invalid command, you need to set a flag."
                  << std::endl;
        return;
    }


    if (remAll) {
        bool response = qHelper->queryRemAllGroups();
        if (response) {
            manager->clearAllGroups();
            std::cout << logPreamble << "Successfully removed all groups." 
                      << std::endl;
        }
        return;
    } else if (hasFilterType) {
        filterType = qHelper->translateGroupType(filterType);
        bool validType = qHelper->isValidGroupType(filterType);
        if (!validType) {
            std::cerr << logPreamble << "ERROR, unknown type \""
                      << filterType << "\". Please try again." 
                      << std::endl;
            return;
        }
    } else if (hasFilterSemester) {
        filterSemester = qHelper->translateSemester(filterSemester);
        bool validSemester = qHelper->isValidSemester(filterSemester);
        if (!validSemester) {
            std::cerr << logPreamble << "ERROR, unknown semester \""
                      << filterSemester << "\". Please try again." 
                      << std::endl;
            return;
        }
    } else if (hasFilterTopic) {
        filterTopic = qHelper->translateTopic(filterTopic);
        bool validTopic = qHelper->isValidTopic(filterTopic);
        if (!validTopic) {
            std::cerr << logPreamble << "ERROR, unknown topic \""
                      << filterTopic << "\". Please try again." 
                      << std::endl;
            return;
        }
    }


    const std::vector<std::unique_ptr<Group>>& groups = manager->loadGroupData();
    std::vector<std::string> remNames;
    std::vector<int> toRemove;
    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        Group* group = groups[i].get();
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
        manager->removeGroup(toRemove[i]);
        std::cout << logPreamble << "Successfully removed the group \"" 
                  << remNames[i] << "\"." << std::endl;
    }
}

/**
 * @brief Handles the logic for the list tasks command.
 * @param groupName The group name option input.
 * @param filterType The task type option input.
 * @param allFlag The flag that indicates every task to be listed.
 * @param dateFlag The task date flag.
 * @param date1Flag The task date1 flag.
 * @param date2Flag The task date2 flag.
 * @param date3Flag The task date3 flag.
 */
struct TaskDisplay {
    std::string type;
    std::string name;
    std::string date;
};

void CommandHelper::listTasksCommand(std::string groupName, 
        std::string filterType, bool allFlag, bool dateFlag, 
        bool date1Flag, bool date2Flag, bool date3Flag) {

    int groupId = manager->getGroupIdFromName(groupName);
    bool hasGroupName = !groupName.empty();
    bool hasFilterType = !filterType.empty();
    int dateFilterCounter = dateFlag + date1Flag + date2Flag + date3Flag;

    if (allFlag && hasGroupName) {
        std::cerr << logPreamble
                  << "Invalid command, you can't specify a group and "
                  << "use the \"all\" flag at the same time.\n";
        return;
    }
    if (!allFlag && !hasGroupName) {
        std::cerr << logPreamble
                  << "Invalid command, you must specify the tasks to list.\n";
        return;
    }
    if (hasGroupName && groupId == -1) {
        std::cerr << logPreamble
                  << "ERROR, can't find a group with the name \""
                  << groupName << "\".\n";
        return;
    }
    if (dateFilterCounter > 1) {
        std::cerr << logPreamble
                  << "Invalid command, you can't use multiple date filters.\n";
        return;
    }
    if (hasFilterType) {
        filterType = qHelper->translateTaskType(filterType);

        if (!qHelper->isValidTaskType(filterType)) {
            std::cerr << logPreamble
                      << "ERROR, unknown task type \"" << filterType << "\".\n";
            return;
        }
    }

    std::vector<TaskDisplay> results;
    auto processTasks = [&](const std::vector<std::unique_ptr<Task>>& tasks) {
        for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
            Task* task = tasks[i].get();
            std::string type = task->getType();
            std::string name = task->getName();
            std::string date = task->getDate();
            if (hasFilterType && filterType != type)
                continue;
            if (date1Flag && !qHelper->isValidTaskDate1(date)) continue;
            if (date2Flag && !qHelper->isValidTaskDate2(date)) continue;
            if (date3Flag && !qHelper->isValidTaskDate3(date)) continue;
            if (!dateFlag && dateFilterCounter == 0) date.clear();
            results.push_back({type, name, date});
        }
    };

    if (allFlag) {
        const std::vector<std::unique_ptr<Group>>& groups = 
                manager->loadGroupData();
        for (int i = 0; i < static_cast<int>(groups.size()); i++) {
            const std::vector<std::unique_ptr<Task>>& tasks = manager->loadTaskFile(i);
            processTasks(tasks);
        }
    }
    else {
        const std::vector<std::unique_ptr<Task>>& tasks = 
                manager->loadTaskFile(groupId);
        processTasks(tasks);
    }

    std::string headerName = allFlag ? "All Groups" : groupName;
    if (!results.empty()) {
        std::cout << "====================== Tasks {" << headerName
                  << "} ======================\n";
    }

    constexpr int DUE_DATE_COLUMN = 40;
    for (size_t i = 0; i < results.size(); ++i) {
        std::string line = "(" + std::to_string(i) + ") "
                           + results[i].type + ": "
                           + results[i].name;

        if (!results[i].date.empty()) {
            int padding = std::max(0,
                DUE_DATE_COLUMN - static_cast<int>(line.size()));
            line += std::string(padding, ' ');
            line += "Due: " + results[i].date;
        }
        std::cout << line << "\n";
    }

    if (!results.empty()) {
        std::cout << "================================";
        for (size_t i = 0; i < headerName.size(); i++)
            std::cout << "=";
        std::cout << "======================\n";
    }
}
        

/**
 * @brief Handles the logic for the assTask command.
 * @param groupName The group name option input.
 */
void CommandHelper::addTaskCommand(std::string groupName) {

    int groupId = manager->getGroupIdFromName(groupName);
    if (groupId == -1) {
        std::cerr << logPreamble << "ERROR, can't find a group "
                  << "with the name \"" << groupName << "\". Please "
                  << "try again." << std::endl;
        return;
    }

    int taskCounter = static_cast<int>(manager->loadTaskFile(groupId).size());

    std::string taskName;
    bool validName = false;
    while (!validName) {
        taskName = qHelper->queryTaskName();
        validName = manager->getTaskIdFromName(groupId, taskName) == -1;
        if (!validName) {
            std::cerr << logPreamble << "ERROR, the name \"" 
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
            taskName, taskDate, false, -1);
    } else if (taskType == "Homework") {
        newTask = std::make_unique<Homework>(taskCounter,
            taskName, taskDate, false, -1);
    } else if (taskType == "Lab") {
        newTask = std::make_unique<Lab>(taskCounter,
            taskName, taskDate, false, -1);       
    } else if (taskType == "LabAssignment") {
        newTask = std::make_unique<LabAssignment>(taskCounter,
            taskName, taskDate, false, -1);
    } else if (taskType == "Notes") {
        newTask = std::make_unique<Notes>(taskCounter,
            taskName, taskDate, false, -1);
    } else if (taskType == "Presentation") {
        newTask = std::make_unique<Presentation>(taskCounter,
            taskName, taskDate, false, -1);
    } else if (taskType == "Programming") {
        newTask = std::make_unique<Programming>(taskCounter,
            taskName, taskDate, false, -1);
    } else if (taskType == "Project") {
        newTask = std::make_unique<Project>(taskCounter,
            taskName, taskDate, false, -1);
    } else if (taskType == "Quiz") {
        newTask = std::make_unique<Quiz>(taskCounter, 
            taskName, taskDate, false, -1);
    } else if (taskType == "Reading") {
        newTask = std::make_unique<Reading>(taskCounter,
            taskName, taskDate, false, -1);
    }
        
    manager->addTask(groupId, std::move(newTask));
    std::cout << logPreamble << "Successfully added the task \"" 
              << taskName << "\" to the group {" << groupName 
              << "}." << std::endl;
}

/**
 * @brief Handles the logic for the removeTask command.
 * @param groupName The group name option input.
 * @param taskName The task name option input.
 * @param filterType The task type option input.
 * @param allFlag The remove all tasks flag.
 * @param statusFlag The remove all completed tasks flag.
 */
void CommandHelper::removeTaskCommand(std::string groupName, std::string taskName,
            std::string filterType, bool allFlag, bool statusFlag) {

    std::vector<int> toRemove;
    std::vector<std::string> remNames;

    int groupId = manager->getGroupIdFromName(groupName);
    if (groupId == -1) {
        std::cerr << logPreamble << "ERROR, could not find a group with "
                  << "the name \"" << groupName << "\". Please try again." 
                  << std::endl;
        return;
    }

    bool hasName = !taskName.empty();
    bool hasFilterType = !filterType.empty();

    if (hasName) {
        if (hasFilterType || allFlag || statusFlag) {
            std::cerr << logPreamble << "Invalid command, you can't set "
                      << "a name when trying to use the \"all\" or \"status\" "
                      << "flags." << std::endl;
                return;
        }
        int taskId = manager->getTaskIdFromName(groupId, taskName);
        if (taskId == -1) {
            std::cerr << logPreamble << "ERROR, could not find a task with the name "
                      << "in the group {" << groupName << "}. Please try again."
                      << std::endl;
            return;
        } else {
            toRemove.push_back(taskId);
            remNames.push_back(taskName);
        }
    }

    int filterCounter = 0;
    if (hasFilterType) filterCounter ++;
    if (allFlag) filterCounter ++;
    if (statusFlag) filterCounter ++;
    if (filterCounter > 1) {
        std::cerr << logPreamble << "Invalid command, you can't set more "
                  << "than one date flag at a time." << std::endl;
        return;
    } else if (filterCounter == 0 && !hasName) {
        std::cerr << logPreamble << "Invalid command, you must set a flag to "
                  << "specify the tasks to be removed." << std::endl;
        return;
    }

    const std::vector<std::unique_ptr<Group>>& groups = manager->loadGroupData();
    if (allFlag) {
        bool response = qHelper->queryRemAllTasks();
        if (response) {
            manager->clearAllTasks(groupId);
            std::cout << logPreamble << "Succesfully removed all the tasks "
                      << "in the group {" << groupName << "}." << std::endl;
        }
        return; 
    } else if (hasFilterType) {
        filterType = qHelper->translateTaskType(filterType);
        bool validType = qHelper->isValidTaskType(filterType);
        if (!validType) {
            std::cerr << logPreamble << "ERROR, could not find group a "
                      << "with the type \"" << filterType << "\". Please "
                      << "try again." << std::endl;
            return;
        }
    }

    const std::vector<std::unique_ptr<Task>>& tasks = manager->loadTaskFile(groupId);
    if (!hasName) {
        for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
            Task* task = tasks[i].get();
            std::string taskType = task->getType();
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
        manager->removeTask(groupId, toRemove.at(i));
        std::cout << logPreamble << "Successfully removed the task \"" 
                  << remNames[i] << "\" from the group {" 
                  << groupName << "}." << std::endl;
    }
}

/**
 * @brief Handles the logic for the countTasks command.
 * @param groupName The group name option input.
 * @param filterType The task type option input.
 * @param allFlag The all tasks option input.
 * @param statusFlag The task completion flag.
 * @param date1Flag The date1 flag.
 * @param date2Flag The date2 flag.
 * @param date3Flag The date3 flag.
 */
void CommandHelper::countTasksCommand(std::string groupName, std::string filterType,
        bool allFlag, bool statusFlag, bool date1Flag, bool date2Flag, bool date3Flag) {

    int dateFilterCounter = 0;
    if (date1Flag) dateFilterCounter++;
    if (date2Flag) dateFilterCounter++;
    if (date3Flag) dateFilterCounter++;
    if (dateFilterCounter > 1) {
        std::cerr << logPreamble << "Invalid command, you can't set "
                  << "more than one date flag at a time." << std::endl;
    }

    int taskCounter = 0;
    bool hasGroupName = !groupName.empty();
    bool hasFilterType = !filterType.empty();

    if (hasFilterType) {
        std::string filterType = qHelper->translateTaskType(filterType);
        bool validType = qHelper->isValidTaskType(filterType);
        if (!validType) {
            std::cerr << logPreamble << "ERROR, unknown type \""
                      << filterType << "\". Please try again." << std::endl;
        }
    }

    if (hasGroupName) {
        int groupId = manager->getGroupIdFromName(groupName);
        if (allFlag) {
            std::cerr << logPreamble << "Invalid command, you can't use the " 
                      << "\"all\" and \"group\" flag together." << std::endl;
            return;
        }
        if (groupId = -1) {
            std::cerr << logPreamble << "ERROR, could not find a "
                      << "group with the name \"" << groupName 
                      << "\". Please try again." << std::endl;
            return;
        }

        const std::vector<std::unique_ptr<Task>>& tasks = manager->loadTaskFile(groupId);
        for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
            Task* task = tasks[i].get();
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
        const std::vector<std::unique_ptr<Group>>& groups = manager->loadGroupData();
        for (int i = 0; i < static_cast<int>(groups.size()); i++) {
            Group* group = groups[i].get();
            const std::vector<std::unique_ptr<Task>>& tasks = manager->loadTaskFile(i);
            for (int j = 0; j < static_cast<int>(tasks.size()); j++) {
                Task* task = tasks[i].get();
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
        std::cout << logPreamble << "Invalid command, you must set either "
                  << "the \"group\" or \"all\" flag." << std::endl;
    }

    std::cout << logPreamble << "Tasks counted: " 
              << std::to_string(taskCounter) << std::endl;
}
