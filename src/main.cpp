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

// Utility & External header files
#include "util/GroupManager.hpp"
#include "util/QueryHelper.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"
#include "external/CLI11.hpp"

// Built in libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>


/**
 * @brief The main function of the entire project.
 */
int main(int argc, char **argv) {
    const std::string outputPreamble = "{KittyTask} ";
    const std::string filepath = "data/";
    CLI::App app{"KittyTracker-CLI"};
    GroupManager manager(filepath, outputPreamble);
    QueryHelper helper(outputPreamble);
    
    CLI::App* listGroups = app.add_subcommand("listGroups", "Lists all the known groups");
    std::string filterListType;
    listGroups->add_option(
        "-t,--type", 
        filterListType, 
        "Only list groups of this type"
    );
    std::string filterListSemester;
    listGroups->add_option(
        "-S,--semester", 
        filterListSemester, 
        "Only list groups of this semester"
    );
    std::string filterListTopic;
    listGroups->add_option(
        "-T,--topic", 
        filterListTopic,
        "Only list groups of this topic"
    );
    listGroups->callback([&]() {
        int filterCounter = 0;
        bool hasFilterListType = !filterListType.empty();
        bool hasFilterListSemester = !filterListSemester.empty();
        bool hasFilterListTopic = !filterListTopic.empty();

        if (hasFilterListType) filterCounter ++;
        if (hasFilterListSemester) filterCounter ++;
        if (hasFilterListTopic) filterCounter ++;
        if (filterCounter > 1) {
            std::cerr << outputPreamble
                      << "Invalid command, can't use multiple filters at the same time"
                      << std::endl;
            return;
        }

        const std::vector<std::unique_ptr<Group>>& groups = manager.getGroups();
        if (hasFilterListType) {
            filterListType = helper.translateGroupType(filterListType);
            bool validType = helper.isValidGroupType(filterListType);
            if (!validType) {
                std::cerr << outputPreamble << "ERROR when trying to find type \""
                          << filterListType << "\", please try again."
                          << std::endl;
                return;
            }
        } else if (hasFilterListSemester) {
            filterListSemester = helper.translateSemester(filterListSemester);
            bool validSemester = helper.isValidSemester(filterListSemester);
            if (!validSemester) {
                std::cerr << outputPreamble << "ERROR when trying to find semester \""
                          << filterListSemester << "\", please try again."
                          << std::endl;
                return;
            }
        } else if (hasFilterListTopic) {
            filterListTopic = helper.translateTopic(filterListTopic);
            bool validTopic = helper.isValidTopic(filterListTopic);
            if (!validTopic) {
                std::cerr << outputPreamble << "ERROR when trying to find topic \""
                          << filterListTopic << "\", please try again."
                          << std::endl;
                return;
            }
        }

        int counter = 0;
        for (int i = 0; i < groups.size(); i++) {
            const std::unique_ptr<Group>& group = groups.at(i);
            std::string groupType = group->getType();
            if (hasFilterListType && filterListType != groupType) {
                continue;
            } else if (hasFilterListSemester) {
                if (groupType != "Class" 
                        && groupType != "Research" 
                        && groupType != "SelfStudy") {
                    continue;
                } else if (Class* cGroup = 
                        dynamic_cast<Class*>(group.get())) {
                    if (filterListSemester != cGroup->getSemesterStr()) {
                        continue;
                    } 
                } else if (Research* rGroup = 
                        dynamic_cast<Research*>(group.get())) {
                    if (filterListSemester != rGroup->getSemesterStr()) {
                        continue;
                    } 
                } else if (SelfStudy* sGroup = 
                        dynamic_cast<SelfStudy*>(group.get())) {
                    if (filterListSemester != sGroup->getSemesterStr()) {
                        continue;
                    } 
                }
            } else if (hasFilterListTopic) {
                if (groupType != "Class" 
                        && groupType != "DevWork" 
                        && groupType != "Research" 
                        && groupType != "SelfStudy") {
                    continue;
                } else if (Class* cGroup = 
                        dynamic_cast<Class*>(group.get())) {
                    if (filterListTopic != cGroup->getTopicStr()) {
                        continue;
                    }
                } else if (DevWork* dGroup = 
                        dynamic_cast<DevWork*>(group.get())) {
                    if (filterListTopic != dGroup->getTopicStr()) {
                        continue;
                    }
                } else if (Research* rGroup = 
                        dynamic_cast<Research*>(group.get())) {
                    if (filterListTopic != rGroup->getTopicStr()) {
                        continue;
                    } 
                } else if (SelfStudy* sGroup = 
                        dynamic_cast<SelfStudy*>(group.get())) {
                    if (filterListTopic != sGroup->getTopicStr()) {
                        continue;
                    } 
                }
            }

            std::cout << "(" << std::to_string(counter) << ") "
                      << groupType << ": " << group->getName() 
                      << std::endl;
            counter++;
        }
    });

    CLI::App* addGroup = app.add_subcommand("addGroup", "Add a new group");
    addGroup->callback([&]() {
        int groupCounter = static_cast<int>(manager.getGroups().size());
        std::string groupName;
        bool validName = false;
        while (!validName) {
            groupName = helper.queryGroupName();
            validName = !manager.containsGroup(groupName);
            if (!validName) {
                std::cerr << outputPreamble
                          << "Can't add a group with a name that's already taken, please try again."
                          << std::endl;
            }
        }
        std::string groupType = helper.queryGroupType();

        std::unique_ptr<Group> newGroup;
        if (groupType == "Class") {
            uint16_t groupYear = helper.queryGroupYear();
            std::string semesterStr = helper.queryGroupSemester();
            std::string topicStr = helper.queryGroupTopic();
            newGroup = std::make_unique<Class>(
                groupCounter,
                groupName,
                groupYear,
                helper.strToSemester(semesterStr),
                helper.strToTopic(topicStr),
                -1
            );
        } else if (groupType == "DevWork") {
            uint16_t groupYear = helper.queryGroupYear();
            std::string topicStr = helper.queryGroupTopic();
            newGroup = std::make_unique<DevWork>(
                groupCounter,
                groupName,
                groupYear,
                helper.strToTopic(topicStr)
            );
        } else if (groupType == "Research") {
            uint16_t groupYear = helper.queryGroupYear();
            std::string semesterStr = helper.queryGroupSemester();
            std::string topicStr = helper.queryGroupTopic();
            newGroup = std::make_unique<Research>(
                groupCounter,
                groupName,
                groupYear,
                helper.strToSemester(semesterStr),
                helper.strToTopic(topicStr)
            );
        } else if (groupType == "SelfStudy") {
            uint16_t groupYear = helper.queryGroupYear();
            std::string semesterStr = helper.queryGroupSemester();
            std::string topicStr = helper.queryGroupTopic();
            newGroup = std::make_unique<SelfStudy>(
                groupCounter,
                groupName,
                groupYear,
                helper.strToSemester(semesterStr),
                helper.strToTopic(topicStr)
            );
        }
        
        manager.addGroup(std::move(newGroup));
        std::cout << outputPreamble << "Added group \"" 
                  << groupName << "\"" 
                  << std::endl;
    });



    CLI::App* remGroup = app.add_subcommand(
            "remGroup",
            "Remove a group from the current groups"
    );
    bool filterRemAll = false;
    remGroup->add_flag(
        "--all", 
        filterRemAll, 
        "Remove all groups from the current groups"
    );
    std::string remGroupName;
    remGroup->add_option(
        "-n, --name",
        remGroupName,
        "Remove a group by name"
    );
    std::string filterRemType;
    remGroup->add_option(
        "-t, --type",
        filterRemType,
        "Remove all groups of the given type"
    );
    std::string filterRemSemester;
    remGroup->add_option(
        "-S, --semester",
        filterRemSemester,
        "Remove all groups of the given semester"
    );
    std::string filterRemTopic;
    remGroup->add_option(
        "-T, --topic",
        filterRemTopic,
        "Remove all groups of the given topic"
    );

    remGroup->callback([&]() {
        int filterCounter = 0;
        bool hasRemName = !remGroupName.empty();
        bool hasFilterRemType = !filterRemType.empty();
        bool hasFilterRemSemester = !filterRemSemester.empty();
        bool hasFilterRemTopic = !filterRemTopic.empty();

        if (hasRemName) {
            if (filterRemAll || hasFilterRemType || 
                    hasFilterRemSemester || hasFilterRemTopic) {
                std::cerr << outputPreamble
                          << "Invalid command, can't have a specific name when trying to use a filter flag" 
                          << std::endl;
                return;
            }
            if (!manager.containsGroup(remGroupName)) {
                std::cerr << outputPreamble << "Invalid command, no group of that name"
                          << std::endl;
                return;
            }
        }
        if (filterRemAll) filterCounter ++;
        if (hasFilterRemType) filterCounter ++;
        if (hasFilterRemSemester) filterCounter ++;
        if (hasFilterRemTopic) filterCounter ++;
        if (filterCounter > 1) {
            std::cerr << outputPreamble
                      << "Invalid command, can't use multiple filters at the same time"
                      << std::endl;
            return;
        } else if (filterCounter == 0 && !hasRemName) {
            std::cerr << outputPreamble << "Invalid command, you need to set a flag"
                      << std::endl;
            return;
        }


        const std::vector<std::unique_ptr<Group>>& groups = manager.getGroups();
        if (filterRemAll) {
            std::string response;
            response = helper.queryRemAllGroups();
            if (response == "y") {
                manager.clearAllGroups();
                std::cout << outputPreamble << "Removed all groups"
                          << std::endl;
            }
            return;
        } else if (hasFilterRemType) {
            filterRemType = helper.translateGroupType(filterRemType);
            bool validType = helper.isValidGroupType(filterRemType);
            if (!validType) {
                std::cerr << outputPreamble << "ERROR when trying to find type \""
                          << filterRemType << "\", please try again."
                          << std::endl;
                return;
            }
        } else if (hasFilterRemSemester) {
            filterRemSemester = helper.translateSemester(filterRemSemester);
            bool validSemester = helper.isValidSemester(filterRemSemester);
            if (!validSemester) {
                std::cerr << outputPreamble << "ERROR when trying to find semester \""
                          << filterRemSemester << "\", please try again."
                          << std::endl;
                return;
            }
        } else if (hasFilterRemTopic) {
            filterRemTopic = helper.translateTopic(filterRemTopic);
            bool validTopic = helper.isValidTopic(filterRemTopic);
            if (!validTopic) {
                std::cerr << outputPreamble << "ERROR when trying to find topic \""
                          << filterRemTopic << "\", please try again."
                          << std::endl;
                return;
            }
        }


        std::vector<int> toRemove;
        for (int i = 0; i < static_cast<int>(groups.size()); i++) {
            const std::unique_ptr<Group>& group = groups.at(i);
            std::string groupType = group->getType();
            if (hasRemName) {
                if (group->getName() == remGroupName) {
                    toRemove.push_back(group->getIdNum());
                    break;
                } else { continue; }
            } else {
                if (hasFilterRemType && filterRemType != groupType) {
                    continue;
                } else if (hasFilterRemSemester) {
                    if (groupType != "Class" 
                            && groupType != "Research" 
                            && groupType != "SelfStudy") {
                        continue;
                    } else if (Class* cGroup = 
                            dynamic_cast<Class*>(group.get())) {
                        if (filterRemSemester == cGroup->getSemesterStr()) {
                            toRemove.push_back(group->getIdNum());
                            continue;
                        } 
                    } else if (Research* rGroup = 
                            dynamic_cast<Research*>(group.get())) {
                        if (filterRemSemester == rGroup->getSemesterStr()) {
                            toRemove.push_back(group->getIdNum());
                            continue;
                        } 
                    } else if (SelfStudy* sGroup = 
                            dynamic_cast<SelfStudy*>(group.get())) {
                        if (filterRemSemester == sGroup->getSemesterStr()) {
                            toRemove.push_back(group->getIdNum());
                            continue;
                        } 
                    }
                } else if (hasFilterRemTopic) {
                    if (groupType != "Class" 
                            && groupType != "DevWork" 
                            && groupType != "Research" 
                            && groupType != "SelfStudy") {
                        continue;
                    } else if (Class* cGroup = 
                            dynamic_cast<Class*>(group.get())) {
                        if (filterRemTopic == cGroup->getTopicStr()) {
                            toRemove.push_back(group->getIdNum());
                            continue;
                        }
                    } else if (DevWork* dGroup = 
                            dynamic_cast<DevWork*>(group.get())) {
                        if (filterRemTopic == dGroup->getTopicStr()) {
                            toRemove.push_back(group->getIdNum());
                            continue;
                        }
                    } else if (Research* rGroup = 
                            dynamic_cast<Research*>(group.get())) {
                        if (filterRemTopic == rGroup->getTopicStr()) {
                            toRemove.push_back(group->getIdNum());
                            continue;
                        } 
                    } else if (SelfStudy* sGroup = 
                            dynamic_cast<SelfStudy*>(group.get())) {
                        if (filterRemTopic == sGroup->getTopicStr()) {
                            toRemove.push_back(group->getIdNum());
                            continue;
                        } 
                    }
                }
            }
        }
            
        for (int i = static_cast<int>(toRemove.size()) - 1; i >= 0; i--) {
            int groupId = toRemove.at(i);
            std::string groupName = manager.getGroupFromId(groupId)->getName();
            manager.removeGroup(groupId);
            std::cout << outputPreamble << "Removed group \"" 
                      << groupName << "\""
                      << std::endl;
        }
    });
  


    CLI::App* listTasks = app.add_subcommand(
        "listTasks", 
        "Lists all the known taks in a given group"
    );
    std::string listTaskGroupName;
    listTasks->add_option(
        "-G, --group",
        listTaskGroupName,
        "A specific group to list the tasks for"
    )->required();
    std::string filterListTaskType;
    listTasks->add_option(
        "-t,--type", 
        filterListType, 
        "Only list tasks of this type"
    );
    bool hasFilterDate = false;
    listTasks->add_flag(
        "-d,--date",
        hasFilterDate,
        "Only list tasks due the current day and/or in the future"
    );
    bool hasFilterDate1 = false;
    listTasks->add_flag(
        "--d1, --date1",
        hasFilterDate1,
        "Only list tasks due within the next 10 days"
    );
    bool hasFilterDate2 = false;
    listTasks->add_flag(
        "--d2, --date2",
        hasFilterDate2,
        "Only list tasks due within the next 30 days"
    );
    bool hasFilterDate3 = false;
    listTasks->add_flag(
        "--d3, --date3",
        hasFilterDate3,
        "Only list tasks due within the next 90 days"
    );

    listTasks->callback([&]() {
        int dateFlagCounter = 0;
        bool hasFilterTaskType = !filterListType.empty();

        if (hasFilterDate) dateFlagCounter ++;
        if (hasFilterDate1) dateFlagCounter ++;
        if (hasFilterDate2) dateFlagCounter ++;
        if (hasFilterDate3) dateFlagCounter ++;
        if (dateFlagCounter > 1) {
            std::cerr << outputPreamble
                      << "Invalid command, can't use multiple filters at the same time"
                      << std::endl;
            return;
        }

        bool validName = manager.containsGroup(listTaskGroupName);
        if (!validName) {
            std::cerr << outputPreamble
                      << "ERROR when trying to find group with name of \""
                      << listTaskGroupName << "\", please try again."
                      << std::endl;
            return;
        }

        const std::vector<std::unique_ptr<Task>>& tasks = manager.getTasks(listTaskGroupName);
        if (hasFilterTaskType) {
            filterListTaskType = helper.translateTaskType(filterListTaskType);
            bool validTaskType = helper.isValidSemester(filterListTaskType);
            if (!validTaskType) {
                std::cerr << outputPreamble
                      << "ERROR when trying to find task with type of \""
                      << filterListTaskType << "\", please try again."
                      << std::endl;            
            }
        }

        int counter = 0;
        for (int i = 0; i < tasks.size(); i++) {
            const std::unique_ptr<Task>& task = tasks.at(i);
            std::string taskType = task->getType();
            if (hasFilterTaskType && filterListTaskType != taskType) {
                continue;
            }

            std::string date;
            if (hasFilterDate) {
                date = task->getDate();
            } else if (hasFilterDate1) {
                bool validDate = helper.isValidTaskDate1(task->getDate());
                if (!validDate) continue;
            } else if (hasFilterDate2) {
                bool validDate = helper.isValidTaskDate2(task->getDate());
                if (!validDate) continue;
            } else if (hasFilterDate3) {
                bool validDate = helper.isValidTaskDate3(task->getDate());
                if (!validDate) continue;
            }

            if (dateFlagCounter != 0) {
                std::cout << "(" << std::to_string(counter) << ") "
                          << taskType << ": " << task->getName()
                          << "        Due " << date
                          << std::endl;
            }

            std::cout << "(" << std::to_string(counter) << ") "
                      << taskType << ": " << task->getName() 
                      << std::endl;
            counter++;   
        }
    });

    CLI::App* addTask = app.add_subcommand("addTask", "Add a new task to a group");
    std::string addTaskGroupName;
    addTask->add_option(
        "-G, --group",
        addTaskGroupName,
        "A specific group that the task gets added to"
    )->required();
    addTask->callback([&]() {
        bool validGroupName = manager.containsGroup(addTaskGroupName);
        if (!validGroupName) {
            std::cerr << outputPreamble
                      << "ERROR when trying to find group with name of \""
                      << addTaskGroupName << "\", please try again."
                      << std::endl;
            return;
        }
        int taskCounter = static_cast<int>(manager.getTasks(addTaskGroupName).size());

        std::string taskName;
        bool validTaskName = false;
        while (!validTaskName) {
            taskName = helper.queryTaskName();
            validTaskName = !manager.containsTask(addTaskGroupName, taskName);
            if (!validTaskName) {
                std::cerr << outputPreamble
                          << "Can't add a task with a name that's already taken, please try again."
                          << std::endl;
            }
        }
        
        std::string taskType = helper.queryTaskType();
        std::string taskDate = helper.queryTaskDate();

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
                255
            );
        } else if (taskType == "Lab") {
             newTask = std::make_unique<Lab>(
                taskCounter,
                taskName,
                taskDate,
                false,
                255
            );       
        } else if (taskType == "LabAssignment") {
             newTask = std::make_unique<LabAssignment>(
                taskCounter,
                taskName,
                taskDate,
                false,
                255
            );       
        } else if (taskType == "Notes") {
             newTask = std::make_unique<Notes>(
                taskCounter,
                taskName,
                taskDate,
                false,
                255
            );       
        } else if (taskType == "Presentation") {
             newTask = std::make_unique<Presentation>(
                taskCounter,
                taskName,
                taskDate,
                false,
                255
            );       
        } else if (taskType == "Programming") {
             newTask = std::make_unique<Programming>(
                taskCounter,
                taskName,
                taskDate,
                false,
                255
            );       
        } else if (taskType == "Project") {
             newTask = std::make_unique<Project>(
                taskCounter,
                taskName,
                taskDate,
                false,
                255
            );       
        } else if (taskType == "Quiz") {
             newTask = std::make_unique<Quiz>(
                taskCounter,
                taskName,
                taskDate,
                false,
                255
            );       
        } else if (taskType == "Reading") {
              newTask = std::make_unique<Reading>(
                taskCounter,
                taskName,
                taskDate,
                false,
                255
            );      
        }
        
        manager.addTask(addTaskGroupName, std::move(newTask));
        std::cout << outputPreamble << "Added task \"" 
                  << taskName << "\"" 
                  << std::endl;
    });


    CLI11_PARSE(app, argc, argv);
    return 0;
}
