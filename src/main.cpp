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
                std::cerr << outputPreamble
                          << "ERROR when trying to find type \""
                          << filterListType 
                          << "\", please try again."
                          << std::endl;
                return;
            }
        } else if (hasFilterListSemester) {
            filterListSemester = helper.translateSemester(filterListSemester);
            bool validSemester = helper.isValidSemester(filterListSemester);
            if (!validSemester) {
                std::cerr << outputPreamble
                          << "ERROR when trying to find semester \""
                          << filterListSemester 
                          << "\", please try again."
                          << std::endl;
                return;
            }
        } else if (hasFilterListTopic) {
            filterListTopic = helper.translateTopic(filterListTopic);
            bool validTopic = helper.isValidTopic(filterListTopic);
            if (!validTopic) {
                std::cerr << outputPreamble
                          << "ERROR when trying to find topic \""
                          << filterListTopic 
                          << "\", please try again."
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
                      << groupType << ": "
                      << group->getName() 
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
        std::cout << outputPreamble
                  << "Added group \"" 
                  << groupName 
                  << "\"" 
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
                std::cerr << outputPreamble
                          << "Invalid command, no group of that name"
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
            std::cerr << outputPreamble
                      << "Invalid command, you need to set a flag"
                      << std::endl;
            return;
        }


        const std::vector<std::unique_ptr<Group>>& groups = manager.getGroups();
        if (filterRemAll) {
            std::string response;
            response = helper.queryRemAllGroups();
            if (response == "y") {
                manager.clearAllGroups();
                std::cout << outputPreamble
                          << "Removed all groups"
                          << std::endl;
            }
            return;
        } else if (hasFilterRemType) {
            filterRemType = helper.translateGroupType(filterRemType);
            bool validType = helper.isValidGroupType(filterRemType);
            if (!validType) {
                std::cerr << outputPreamble
                          << "ERROR when trying to find type \""
                          << filterRemType 
                          << "\", please try again."
                          << std::endl;
                return;
            }
        } else if (hasFilterRemSemester) {
            filterRemSemester = helper.translateSemester(filterRemSemester);
            bool validSemester = helper.isValidSemester(filterRemSemester);
            if (!validSemester) {
                std::cerr << outputPreamble
                          << "ERROR when trying to find semester \""
                          << filterRemSemester 
                          << "\", please try again."
                          << std::endl;
                return;
            }
        } else if (hasFilterRemTopic) {
            filterRemTopic = helper.translateTopic(filterRemTopic);
            bool validTopic = helper.isValidTopic(filterRemTopic);
            if (!validTopic) {
                std::cerr << outputPreamble
                          << "ERROR when trying to find topic \""
                          << filterRemTopic 
                          << "\", please try again."
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
            std::cout << outputPreamble
                      << "Removed group \""
                      << groupName
                      << "\""
                      << std::endl;
        }
    });
    

    CLI11_PARSE(app, argc, argv);
    return 0;
}
