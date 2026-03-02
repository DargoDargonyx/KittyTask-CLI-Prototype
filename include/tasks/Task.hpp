#ifndef TASK_H
#define TASK_H

// Built in library
#include <string>


class Task {
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
        int getIdNum() const;
        std::string getName() const;
        std::string getDate() const;
        bool getStatus() const;
        std::string getType() const; 
        // Mutators
        void setIdNum(int idNum);
        void setName(const std::string& name);
        void setDate(const std::string& date);
        void setStatus(bool status);
};

#endif //TASK_H
