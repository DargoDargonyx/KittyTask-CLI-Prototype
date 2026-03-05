#ifndef TASK_H
#define TASK_H

// Built in library
#include <string>


class Task {
    private:
        const std::string TYPE = "Task";
    protected:
        // Fields
        int idNum;
        std::string name;
        std::string date;
        bool status;
        std::string type;
    public:
        // Constructor & Deconstructor
        Task(int idNum, const std::string& name, 
                const std::string& date, bool status);
        virtual ~Task() = default;
        // Accessors
        virtual int getIdNum();
        virtual std::string getName();
        virtual std::string getDate();
        virtual bool getStatus();
        virtual std::string getType(); 
        // Mutators
        virtual void setIdNum(int idNum);
        virtual void setName(const std::string& name);
        virtual void setDate(const std::string& date);
        virtual void setStatus(bool status);
};

#endif //TASK_H
