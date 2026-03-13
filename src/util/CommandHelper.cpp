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
#include <cstdio>
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
            printf("%sERROR, unknown type \"%s\". Please try again.\n", 
                    logPreamble.c_str(), filterType.c_str());
            return;
        }
    } else if (hasFilterSemester) {
        filterSemester = qHelper->translateSemester(filterSemester);
        bool validSemester = qHelper->isValidSemester(filterSemester);
        if (!validSemester) {
            printf("%sERROR, unknown semester \"%s\". Please try again.\n",
                    logPreamble.c_str(), filterSemester.c_str());
            return;
        }
    } else if (hasFilterTopic) {
        filterTopic = qHelper->translateTopic(filterTopic);
        bool validTopic = qHelper->isValidTopic(filterTopic);
        if (!validTopic) {
            printf("%sERROR, unknown topic \"%s\". Please try again.\n",
                    logPreamble.c_str(), filterTopic.c_str());
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
    if (namesSize > 0) {
        std::string output = "========================= Groups =========================\n";
        for (int i = 0; i < namesSize; i++) {
            output += "(" + std::to_string(i) + ") " + listTypes[i] 
                    + ": " + listNames[i] + "\n";
        }
        output += "==========================================================\n";
        printf("%s", output.c_str());
    }
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
            printf("%sERROR, the name \"%s\" has already been taken for a group \
                    already. Please try again.\n", logPreamble.c_str(), groupName.c_str());
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
    printf("%sSuccessfully added the group \"%s\".\n", 
            logPreamble.c_str(), groupName.c_str());
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
            printf("%sInvalid command, you can't have a specific name when trying \
                    to use the \"all\" flag.\n", logPreamble.c_str());
                return;
        }
        bool validName = manager->getGroupIdFromName(groupName) != -1;
        if (!validName) {
            printf("%sERROR, can't find a group with the name \"%s\". Please try again.\n", 
                    logPreamble.c_str(), groupName.c_str());
            return;
        }
    }

    if (remAll) filterCounter ++;
    if (hasFilterType) filterCounter ++;
    if (hasFilterSemester) filterCounter ++;
    if (hasFilterTopic) filterCounter ++;
    if (filterCounter > 1) {
        printf("%sInvalid command, you can't use multiple filters at \
                the same time.\n", logPreamble.c_str());
        return;
    } else if (filterCounter == 0 && !hasName) {
        printf("%sInvalid command, you need to set a flag.\n", logPreamble.c_str());
        return;
    }


    if (remAll) {
        bool response = qHelper->queryRemAllGroups();
        if (response) {
            manager->clearAllGroups();
            printf("%sSuccessfully removed all groups.\n", logPreamble.c_str());
        }
        return;
    } else if (hasFilterType) {
        filterType = qHelper->translateGroupType(filterType);
        bool validType = qHelper->isValidGroupType(filterType);
        if (!validType) {
            printf("%sERROR, unknown type \"%s\". Please try again.\n", 
                    logPreamble.c_str(), filterType.c_str());
            return;
        }
    } else if (hasFilterSemester) {
        filterSemester = qHelper->translateSemester(filterSemester);
        bool validSemester = qHelper->isValidSemester(filterSemester);
        if (!validSemester) {
            printf("%sERROR, unknown semester \"%s\". Please try again.",
                    logPreamble.c_str(), filterSemester.c_str());
            return;
        }
    } else if (hasFilterTopic) {
        filterTopic = qHelper->translateTopic(filterTopic);
        bool validTopic = qHelper->isValidTopic(filterTopic);
        if (!validTopic) {
            printf("%sERROR, unknown topic \"%s\". Please try again.\n",
                    logPreamble.c_str(), filterTopic.c_str());
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
        printf("%sSuccessfully removed the group \"%s\".\n", 
                logPreamble.c_str(), remNames[i].c_str());
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
void CommandHelper::listTasksCommand(std::string groupName, 
        std::string filterType, bool allFlag, bool gradeFlag, 
        bool dateFlag, bool date0Flag, bool date1Flag, 
        bool date2Flag, bool date3Flag) {

    struct TaskDisplay {
        std::string type;
        std::string name;
        std::string date;
        int grade;
    };
    int groupId = manager->getGroupIdFromName(groupName);
    bool hasGroupName = !groupName.empty();
    bool hasFilterType = !filterType.empty();
    int dateFilterCounter = 0;
    if (dateFlag) dateFilterCounter++;
    if (date0Flag) dateFilterCounter++;
    if (date1Flag) dateFilterCounter++;
    if (date2Flag) dateFilterCounter++;
    if (date3Flag) dateFilterCounter++;

    if (allFlag && hasGroupName) {
        printf("%sInvalid command, you can't speicfy a group name and use \
                the \"all\" flag at the same time.\n", logPreamble.c_str());
        return;
    }
    if (!allFlag && !hasGroupName) {
        printf("%sInvalid command, you must specify the tasks to list.\n", 
                logPreamble.c_str());
        return;
    }
    if (hasGroupName && groupId == -1) {
        printf("%sERROR, can't find a group with the name \"%s\".\n", 
                logPreamble.c_str(), groupName.c_str());
        return;
    }
    if (dateFilterCounter > 1) {
        printf("%sInvalid command, you can't use multiple date filters at \
                the same.\n", logPreamble.c_str());
        return;
    }
    if (hasFilterType) {
        filterType = qHelper->translateTaskType(filterType);

        if (!qHelper->isValidTaskType(filterType)) {
            printf("%sERROR, unknown task type \"%s\".\n", 
                    logPreamble.c_str(), filterType.c_str());
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
            int grade = -1;
            if (type != "Chore") {
                GradedTask* gradedTask = static_cast<GradedTask*>(task);
                grade = gradedTask->getGrade();
            }
            if (hasFilterType && filterType != type)
                continue;
            if (date0Flag && !qHelper->isValidTaskDate0(date)) continue;
            if (date1Flag && !qHelper->isValidTaskDate1(date)) continue;
            if (date2Flag && !qHelper->isValidTaskDate2(date)) continue;
            if (date3Flag && !qHelper->isValidTaskDate3(date)) continue;
            if (dateFilterCounter == 0) date.clear();
            results.push_back({type, name, date, grade});
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

    std::string output;
    std::string headerName = allFlag ? "All Groups" : groupName;
    if (!results.empty()) {
        output = "====================== Tasks {" 
                + headerName + "} ======================\n";
        constexpr int GRADE_COL = 40;
        constexpr int DATE_COL = 48;
        for (int i = 0; i < results.size(); i++) {
            std::string line = "(" + std::to_string(i) + ") " + results[i].type 
                    + ": " + results[i].name;

            if (!results[i].date.empty()) {
                if (results[i].grade != -1) {
                    std::string gradeStr = std::to_string(results[i].grade);
                    int gradeSize = static_cast<int>(gradeStr.size());
                    int diff = DATE_COL - GRADE_COL - (gradeSize + 4);
                    int padding = std::max(0, GRADE_COL - static_cast<int>(line.size()));
                    line += std::string(padding + diff, ' ');
                    line += " {" + gradeStr + "} ";
                }
                int padding = std::max(0, DATE_COL - static_cast<int>(line.size()));
                line += std::string(padding, ' ');
                line += "Due: " + results[i].date;
            } else {
                if (results[i].grade != -1) {
                    int padding = std::max(0, GRADE_COL - static_cast<int>(line.size()));
                    line += std::string(padding, ' ');
                    line += " {" + std::to_string(results[i].grade) + "} ";
                }
            }
            output += line + "\n";
        }
        if (!results.empty()) {
            output += "================================";
            int padding = std::max(0, static_cast<int>(headerName.size()));
            output += std::string(padding, '=');
            output += "======================\n";
        }
        
        printf("%s", output.c_str());
    }
}
        

/**
 * @brief Handles the logic for the assTask command.
 * @param groupName The group name option input.
 */
void CommandHelper::addTaskCommand(std::string groupName) {
    int groupId = manager->getGroupIdFromName(groupName);
    if (groupId == -1) {
        printf("%sERROR, can't find a group with the name \"%s\". Please try again.\n",
                logPreamble.c_str(), groupName.c_str());
        return;
    }

    std::string taskName;
    bool validName = false;
    while (!validName) {
        taskName = qHelper->queryTaskName();
        validName = manager->getTaskIdFromName(groupId, taskName) == -1;
        if (!validName) {
            printf("%sERROR, the name \"%s\" has already been taken by a task in \
                    the group {%s}. Please try again.\n", logPreamble.c_str(), 
                    taskName.c_str(), groupName.c_str());
        }
    }
        
    int taskCounter = static_cast<int>(manager->loadTaskFile(groupId).size());
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
    printf("%sSuccessfully added the task \"%s\" to the group {%s}.\n", 
            logPreamble.c_str(), taskName.c_str(), groupName.c_str());
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
        printf("%sERROR, could not find a group with the name \"%s\". Please try again.\n", 
                logPreamble.c_str(), groupName.c_str());
        return;
    }

    bool hasName = !taskName.empty();
    bool hasFilterType = !filterType.empty();

    if (!hasName && !hasFilterType && !allFlag && !statusFlag) {
        printf("%sInvalid command, you must specify the tasks to be removed.\n", 
                logPreamble.c_str());
        return;
    }

    if (hasName) {
        if (hasFilterType || allFlag || statusFlag) {
            printf("%sInvalid command, you can't specify a name when trying to \
                    use generic flags.\n", logPreamble.c_str());
            return;
        }
        int taskId = manager->getTaskIdFromName(groupId, taskName);
        if (taskId == -1) {
            printf("%sERROR, could not find a task with the name \"%s\" in the \
                    group {%s}. Please try again.\n", logPreamble.c_str(), 
                    taskName.c_str(), groupName.c_str());
            return;
        } else {
            toRemove.push_back(taskId);
            remNames.push_back(taskName);
        }
    } else if (allFlag) {
        if (hasFilterType || statusFlag) {
            printf("%sInvalid command, you can't use the \"all\" flag with \
                    generic flags.\n", logPreamble.c_str());
            return;
        }

        if (qHelper->queryRemAllTasks()) {
            manager->clearAllTasks(groupId);
            printf("%sSuccessfully removed all the tasks in the group {%s}.\n", 
                    logPreamble.c_str(), groupName.c_str()); 
        }
        return;
    }
    
    const std::vector<std::unique_ptr<Group>>& groups = manager->loadGroupData();
    if (hasFilterType) {
        filterType = qHelper->translateTaskType(filterType);
        bool validType = qHelper->isValidTaskType(filterType);
        if (!validType) {
            printf("%sERROR, could not find task type of \"%s\". Please \
                    try again.", logPreamble.c_str(), filterType.c_str());
            return;
        }
    }

    const std::vector<std::unique_ptr<Task>>& tasks = manager->loadTaskFile(groupId);
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

    for (int i = 0; i < static_cast<int>(toRemove.size()); i++) {
        manager->removeTask(groupId, toRemove.at(i));
        printf("%sSuccessfully removed the task \"%s\" from the group {%s}.\n", 
                logPreamble.c_str(), remNames[i].c_str(), groupName.c_str());
    }
}


/**
 * @brief Handles the logic for the setGrade command.
 * @param taskName The task name option input.
 */
void CommandHelper::setGradeCommand(std::string groupName, 
        std::string taskName, int value) {
   
    bool hasGroupName = !groupName.empty();
    bool hasTaskName = !taskName.empty();
    bool hasValue = value > -1;
    
    if (!hasGroupName) {
        printf("%sInvalid command, you must specify a group that the \
                task belongs to.\n", logPreamble.c_str());
        return;
    }
    if (!hasTaskName) {
        printf("%sInvalid command, you must specify a task name.\n", 
                logPreamble.c_str());
        return;
    }
    if (!hasValue) {
        printf("%sInvalid command, you must specify a grade value.\n", 
                logPreamble.c_str());
        return;
    }

    bool validGroup;
    int groupId = manager->getGroupIdFromName(groupName);
    if (groupId == -1) {
        printf("%sERROR, can't find a group with the name \"%s\". Please \
                try again.\n", logPreamble.c_str(), groupName.c_str());
        return;
    }
    bool validName;
    int taskId = manager->getTaskIdFromName(groupId, taskName);
    if (taskId == -1) {
        printf("%sERROR, can't find a task with the name \"%s\". Please \
                try again.\n", logPreamble.c_str(), taskName.c_str());
        return;
    }

    bool feedback = manager->setTaskGrade(groupId, taskId, value);
    if (!feedback) {
        printf("%sInvalid command, the task you set the grade of must be a \
                gradeable task.\n", logPreamble.c_str());
        return;
    }
    printf("%sSuccessfully set the grade of \"%s\" in the group {%s} to %d.\n",
            logPreamble.c_str(), taskName.c_str(), groupName.c_str(), value);
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
void CommandHelper::countTasksCommand(std::string groupName, 
        std::string filterType, bool allFlag, bool statusFlag, 
        bool date1Flag, bool date2Flag, bool date3Flag) {

    int dateFilterCounter = 0;
    if (date1Flag) dateFilterCounter++;
    if (date2Flag) dateFilterCounter++;
    if (date3Flag) dateFilterCounter++;
    if (dateFilterCounter > 1) {
        printf("%sInvalid command, you can't set more than one date flag \
                at a time.\n", logPreamble.c_str());
        return;
    }

    int taskCounter = 0;
    bool hasGroupName = !groupName.empty();
    bool hasFilterType = !filterType.empty();

    if (hasFilterType) {
        std::string filterType = qHelper->translateTaskType(filterType);
        bool validType = qHelper->isValidTaskType(filterType);
        if (!validType) {
            printf("%sERROR, unknown type \"%s\". Please try again.\n",
                    logPreamble.c_str(), filterType.c_str());
            return;
        }
    }

    if (hasGroupName) {
        int groupId = manager->getGroupIdFromName(groupName);
        if (allFlag) {
            printf("%sInvalid command, you can't use the \"all\" and \"group\" flags \
                    at the same time.\n", logPreamble.c_str());
            return;
        }
        if (groupId = -1) {
            printf("%sERROR, could not find a group with the name \"%s\". Please \
                    try again.\n", logPreamble.c_str(), groupName.c_str());
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
        printf("%sInvalid command, you must specify the tasks to \
                be counted.\n", logPreamble.c_str());
        return;
    }
   
    printf("%sTasks counted: %d\n", logPreamble.c_str(), std::to_string(taskCounter).c_str());
}
