#include "external/CLI11.hpp"
#include "util/GroupManager.hpp"
#include "util/QueryHelper.hpp"
#include "util/Semester.hpp"
#include "util/Topic.hpp"

#include "groups/Group.hpp"
#include "groups/Class.hpp"
#include "groups/DevWork.hpp"
#include "groups/Research.hpp"
#include "groups/SelfStudy.hpp"

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

#include <iostream>
#include <string>
#include <vector>
#include <memory>



int main(int argc, char **argv) {
    const std::string outputPreamble = "{KittyTask} ";
    const std::string filepath = "data/";
    CLI::App app{"KittyTracker-CLI"};
    GroupManager manager(filepath, outputPreamble);
    QueryHelper helper(outputPreamble);
    int groupCounter = static_cast<int>(manager.getGroups().size());


    CLI::App* addGroup = app.add_subcommand("addGroup", "Add a new group");
    addGroup->callback([&]() {
        std::string groupType;
        groupType = helper.queryGroupType();
        std::string groupName = helper.queryGroupName();

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

    CLI11_PARSE(app, argc, argv);
    return 0;
}
