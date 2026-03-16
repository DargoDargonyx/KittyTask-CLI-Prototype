// Utility & External header files
#include "util/CommandHelper.hpp"
#include "external/CLI11.hpp"

// Built in libraries
#include <iostream>
#include <string>
#include <memory>


const std::string LOG_PREAMBLE = "{KittyTask} ";
const std::string STORAGE_FILEPATH = "data/";


/**
 * @brief The main function of the entire project.
 */
int main(int argc, char **argv) {
    std::unique_ptr<CommandHelper> cmdHelper = 
        std::make_unique<CommandHelper>(STORAGE_FILEPATH, LOG_PREAMBLE);
    CLI::App app{"KittyTracker-CLI"};



    CLI::App* listGroups = app.add_subcommand("listGroups", 
        "Lists all the known groups");
    
    std::string filterListGroupType;
    listGroups->add_option("-t,--type", filterListGroupType, 
        "Only list groups of this type");
    std::string filterListGroupSemester;
    listGroups->add_option("-S,--semester", filterListGroupSemester, 
        "Only list groups of this semester");
    std::string filterListGroupTopic;
    listGroups->add_option("-T,--topic", filterListGroupTopic,
        "Only list groups of this topic");

    listGroups->callback([&]() { 
        cmdHelper->listGroupsCommand(
            filterListGroupType,
            filterListGroupSemester,
            filterListGroupTopic
        ); 
    });



    CLI::App* sortGroups = app.add_subcommand("sortGroups", 
        "Sort the known groups");
    
    bool sortGroupsDate = false;
    sortGroups->add_flag("-d, --date", sortGroupsDate,
        "Sort by date");
    bool sortGroupsSemester = false;
    sortGroups->add_flag("-S, --semester", sortGroupsSemester,
        "Sort by semester chronologically");
    bool sortGroupsTopic = false;
    sortGroups->add_flag("-T, --topic", sortGroupsTopic,
        "Sort by topic alphabetically");

    sortGroups->callback([&]() {
        cmdHelper->sortGroupsCommand(
            sortGroupsDate,
            sortGroupsSemester,
            sortGroupsTopic
        );
    });



    CLI::App* addGroup = app.add_subcommand("addGroup", "Add a new group");
    
    addGroup->callback([&]() {
        cmdHelper->addGroupCommand();
    });



    CLI::App* remGroup = app.add_subcommand("removeGroup",
        "Remove a group from the current groups");
    
    std::string remGroupName;
    remGroup->add_option("-n, --name", remGroupName,
        "Remove a group by name");
    bool filterRemGroupAll = false;
    remGroup->add_flag("-a, --all", filterRemGroupAll, 
        "Remove all groups from the current groups");
    std::string filterRemGroupType;
    remGroup->add_option("-t, --type", filterRemGroupType,
        "Remove all groups of the given type");
    std::string filterRemGroupSemester;
    remGroup->add_option("-S, --semester", filterRemGroupSemester,
        "Remove all groups of the given semester");
    std::string filterRemGroupTopic;
    remGroup->add_option("-T, --topic", filterRemGroupTopic,
        "Remove all groups of the given topic");

    remGroup->callback([&]() {
        cmdHelper->removeGroupCommand(
            remGroupName,
            filterRemGroupAll,
            filterRemGroupType,
            filterRemGroupSemester,
            filterRemGroupTopic
        );
    });
  


    CLI::App* listTasks = app.add_subcommand("listTasks", 
        "Lists all the known taks in a given group");
    
    std::string listTaskGroupName;
    listTasks->add_option("-G, --group", listTaskGroupName,
        "A specific group to list the tasks for");
    std::string filterListTaskType;
    listTasks->add_option("-t,--type", filterListTaskType, 
        "Only list tasks of this type");
    bool hasFilterListAll = false;
    listTasks->add_flag("-a, --all", hasFilterListAll, 
        "Lists all tasks in every group");
    bool hasFilterListTaskGrade = false;
    listTasks->add_flag("-g, --grade", hasFilterListTaskGrade,
        "Displays the grade information when applicable");
    bool hasFilterListTaskDate = false;
    listTasks->add_flag("-d, --date", hasFilterListTaskDate,
        "Displays the date information");
    bool hasFilterListTaskDate0 = false;
    listTasks->add_flag("--date0", hasFilterListTaskDate0,
        "Only list tasks due the current day and/or in the future (Displays the date)");
    bool hasFilterListTaskDate1 = false;
    listTasks->add_flag("--date1", hasFilterListTaskDate1,
        "Only list tasks due within the next 10 days (Displays the date)");
    bool hasFilterListTaskDate2 = false;
    listTasks->add_flag("--date2", hasFilterListTaskDate2,
        "Only list tasks due within the next 30 days (Displays the date)");
    bool hasFilterListTaskDate3 = false;
    listTasks->add_flag("--date3", hasFilterListTaskDate3,
        "Only list tasks due within the next 90 days (Displays the date)");

    listTasks->callback([&]() {
        cmdHelper->listTasksCommand(
            listTaskGroupName,
            filterListTaskType,
            hasFilterListAll,
            hasFilterListTaskGrade,
            hasFilterListTaskDate,
            hasFilterListTaskDate0,
            hasFilterListTaskDate1,
            hasFilterListTaskDate2,
            hasFilterListTaskDate3
        );
    });


    
    CLI::App* sortTasks = app.add_subcommand("sortTasks",
        "Sort the known tasks in a given group");
    
    std::string sortTasksGroupName;
    sortTasks->add_option("-G, --group", sortTasksGroupName,
        "A specific group that the tasks to be sorted belong to \
        (Currently only by date)")->required();

    sortTasks->callback([&]() {
        cmdHelper->sortTasksCommand(sortTasksGroupName);
    });



    CLI::App* addTask = app.add_subcommand("addTask", "Add a new task to a group");
    
    std::string addTaskGroupName;
    addTask->add_option("-G, --group", addTaskGroupName,
        "A specific group that the task gets added to")->required();
    
    addTask->callback([&]() {
        cmdHelper->addTaskCommand(addTaskGroupName); 
    });



    CLI::App* removeTask = app.add_subcommand("removeTask", 
        "Remove a task from a group");

    std::string removeTaskGroupName;
    removeTask->add_option("-G, --group", removeTaskGroupName,
        "A specific group that the task gets removed from")->required();
    std::string filterRemoveTaskTaskName;
    removeTask->add_option("-n, --name", filterRemoveTaskTaskName,
        "Remove a task by name in the given group");
    std::string filterRemoveTaskType;
    removeTask->add_option("-t, --type", filterRemoveTaskType,
        "Remove a task by task type in the given group");
    bool filterRemoveTaskAll = false;
    removeTask->add_flag("-a, --all", filterRemoveTaskAll,
        "Remove all tasks in the given group");
    bool filterRemoveTaskStatus = false;
    removeTask->add_flag("-s, --status", filterRemoveTaskStatus,
        "Remove all tasks that are marked complete");

    removeTask->callback([&]() {
        cmdHelper->removeTaskCommand(
            removeTaskGroupName,
            filterRemoveTaskTaskName,
            filterRemoveTaskType,
            filterRemoveTaskAll,
            filterRemoveTaskStatus
        );
    });



    CLI::App* setGrade = app.add_subcommand("setGrade", 
        "Set the grade for a task if applicable");
   
    std::string setGradeGroupName;
    setGrade->add_option("-G, --group", setGradeGroupName,
        "The name of the group the task belongs to")->required();
    std::string setGradeTaskName;
    setGrade->add_option("-n, --name", setGradeTaskName,
        "The name of the task")->required();
    int setGradeValue = -1;
    setGrade->add_option("-v, --value", setGradeValue,
        "The numerical value of the grade to be set")->required();

    setGrade->callback([&]() {
        cmdHelper->setGradeCommand(
            setGradeGroupName,
            setGradeTaskName,
            setGradeValue
        );
    });



    CLI::App* countTasks = app.add_subcommand("countTasks", 
        "Get a count of how many tasks are in a group");
    
    std::string countTasksGroupName;
    countTasks->add_option("-G, --group", countTasksGroupName,
        "A specific group to count the tasks in");
    std::string countTasksFilterType;
    countTasks->add_option("-t, --type", countTasksFilterType,
        "Count all tasks of a specific Type");
    bool countTasksAllFlag = false;
    countTasks->add_flag("-a, --all", countTasksAllFlag,
        "Count every task in every group");
    bool countTasksStatusFlag = false;
    countTasks->add_flag("-s, --status", countTasksStatusFlag,
        "Count all tasks that are marked incomplete");
    bool countTasksDate1Flag = false;
    countTasks->add_flag("--d1, --date1", countTasksDate1Flag,
        "Count all tasks that are due within the next 10 days");
    bool countTasksDate2Flag = false;
    countTasks->add_flag("--d2, --date2", countTasksDate2Flag,
        "Count all tasks that are due within the next 30 days");
    bool countTasksDate3Flag = false;
    countTasks->add_flag("--d3, --date3", countTasksDate3Flag,
        "Count all tasks that are due within the next 90 days");

    countTasks->callback([&]() {
        cmdHelper->countTasksCommand(
            countTasksGroupName,
            countTasksFilterType,
            countTasksAllFlag,
            countTasksStatusFlag,
            countTasksDate1Flag,
            countTasksDate2Flag,
            countTasksDate3Flag
        );
    });



    CLI11_PARSE(app, argc, argv);
    return 0;
}
