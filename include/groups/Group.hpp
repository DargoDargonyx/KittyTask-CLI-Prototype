#ifndef GROUP_H
#define GROUP_H

#include "tasks/Task.hpp"
#include <string>
#include <vector>
#include <memory>

class Group {
    protected:
        int idNum;
        std::string name;
        std::vector<std::unique_ptr<Task>> tasks;
        std::string type;
    public:
        Group(
            int idNum, 
            const std::string& name
        );
        virtual ~Group() = default;
        virtual int getIdNum() const;
        virtual void setIdNum(int idNum);
        virtual std::string getName() const;
        virtual void setName(const std::string& name);
        virtual std::vector<std::unique_ptr<Task>>& getTasks();
        virtual void setTasks(std::vector<std::unique_ptr<Task>>&& newTasks);
        virtual std::string getType() const;
        virtual void addTask(std::unique_ptr<Task> newTask);
        virtual void removeTask(const int taskId);
        virtual void clearAllTasks();
        virtual bool containsTask(const std::string& taskName);
        virtual Task* getTaskFromId(const int taskId);
        virtual Task* getTaskFromName(const std::string& taskName);
        virtual void refreshTasks();
};

#endif // GROUP_H
