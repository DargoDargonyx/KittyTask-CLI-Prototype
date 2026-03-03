// Utility & External header files
#include "util/CommandHelper.hpp"
#include "external/CLI11.hpp"

// Built in libraries
#include <iostream>
#include <string>
#include <memory>

const std::string OUTPUT_PREAMBLE = "{KittyTask} ";
const std::string STORAGE_FILEPATH = "data/";

/**
 * @brief The main function of the entire project.
 */
int main(int argc, char **argv) {
    std::unique_ptr<CommandHelper> cmdHelper = 
        std::make_unique<CommandHelper>(STORAGE_FILEPATH, OUTPUT_PREAMBLE);
    CLI::App app{"KittyTracker-CLI"};


    CLI::App* listGroups = app.add_subcommand("listGroups", "Lists all the known groups");
    std::string filterListGroupType;
    listGroups->add_option(
        "-t,--type", 
        filterListGroupType, 
        "Only list groups of this type"
    );
    std::string filterListGroupSemester;
    listGroups->add_option(
        "-S,--semester", 
        filterListGroupSemester, 
        "Only list groups of this semester"
    );
    std::string filterListGroupTopic;
    listGroups->add_option(
        "-T,--topic", 
        filterListGroupTopic,
        "Only list groups of this topic"
    );

    listGroups->callback([&]() { 
        cmdHelper->listGroupsCommand(
            filterListGroupType,
            filterListGroupSemester,
            filterListGroupTopic
        ); 
    });


    CLI::App* addGroup = app.add_subcommand("addGroup", "Add a new group");
    
    addGroup->callback([&]() {
        cmdHelper->addGroupCommand();
    });



    CLI::App* remGroup = app.add_subcommand(
            "remGroup",
            "Remove a group from the current groups"
    );

    std::string remGroupName;
    remGroup->add_option(
        "-n, --name",
        remGroupName,
        "Remove a group by name"
    );
    bool filterRemGroupAll = false;
    remGroup->add_flag(
        "--all", 
        filterRemGroupAll, 
        "Remove all groups from the current groups"
    );
    std::string filterRemGroupType;
    remGroup->add_option(
        "-t, --type",
        filterRemGroupType,
        "Remove all groups of the given type"
    );
    std::string filterRemGroupSemester;
    remGroup->add_option(
        "-S, --semester",
        filterRemGroupSemester,
        "Remove all groups of the given semester"
    );
    std::string filterRemGroupTopic;
    remGroup->add_option(
        "-T, --topic",
        filterRemGroupTopic,
        "Remove all groups of the given topic"
    );

    remGroup->callback([&]() {
        cmdHelper->removeGroupCommand(
            remGroupName,
            filterRemGroupAll,
            filterRemGroupType,
            filterRemGroupSemester,
            filterRemGroupTopic
        );
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
        filterListTaskType, 
        "Only list tasks of this type"
    );
    bool hasFilterListTaskDate = false;
    listTasks->add_flag(
        "-d,--date",
        hasFilterListTaskDate,
        "Only list tasks due the current day and/or in the future"
    );
    bool hasFilterListTaskDate1 = false;
    listTasks->add_flag(
        "--d1, --date1",
        hasFilterListTaskDate1,
        "Only list tasks due within the next 10 days"
    );
    bool hasFilterListTaskDate2 = false;
    listTasks->add_flag(
        "--d2, --date2",
        hasFilterListTaskDate2,
        "Only list tasks due within the next 30 days"
    );
    bool hasFilterListTaskDate3 = false;
    listTasks->add_flag(
        "--d3, --date3",
        hasFilterListTaskDate3,
        "Only list tasks due within the next 90 days"
    );

    listTasks->callback([&]() {
        cmdHelper->listTasksCommand(
            listTaskGroupName,
            filterListTaskType,
            hasFilterListTaskDate,
            hasFilterListTaskDate1,
            hasFilterListTaskDate2,
            hasFilterListTaskDate3
        );
    });



    CLI::App* addTask = app.add_subcommand("addTask", "Add a new task to a group");
    std::string addTaskGroupName;
    addTask->add_option(
        "-G, --group",
        addTaskGroupName,
        "A specific group that the task gets added to"
    )->required();
    
    addTask->callback([&]() {
        cmdHelper->addTaskCommand(addTaskGroupName); 
    });



    CLI11_PARSE(app, argc, argv);
    return 0;
}
