#ifndef GROUP_H
#define GROUP_H

// Task header file
#include "tasks/Task.hpp"

// Built in libraries
#include <string>
#include <vector>
#include <memory>


class Group {
    protected:
        // Fields
        int idNum;
        std::string name;
        std::vector<std::unique_ptr<Task>> tasks;
        std::string type;
    public:
        // Constructor & Deconstructor
        Group(
            int idNum, 
            const std::string& name
        );
        virtual ~Group() = default;
        // Accessors
        virtual int getIdNum() const;
        virtual std::string getName() const;
        virtual std::vector<std::unique_ptr<Task>>& getTasks();
        virtual std::string getType() const;
        virtual bool containsTask(const std::string& taskName);
        virtual Task* getTaskFromId(const int taskId);
        virtual Task* getTaskFromName(const std::string& taskName);
        // Mutators
        virtual void setIdNum(int idNum);
        virtual void setName(const std::string& name);
        virtual void setTasks(std::vector<std::unique_ptr<Task>>&& newTasks);
        virtual void addTask(std::unique_ptr<Task> newTask);
        virtual void removeTask(const int taskId);
        virtual void clearAllTasks();
        // Other
        virtual void refreshTasks();
};

#endif // GROUP_H
