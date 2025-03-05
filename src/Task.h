//
// Created by Devs_leo on 19/02/2025.
//

#ifndef TODO_LIST_TASK_H
#define TODO_LIST_TASK_H

#include <iostream>
using namespace std;

class Task {
private:
    string description;    //Description of the task
    bool isCompleted;      //Need for check if the task is completed, but to not eliminate the task

public:
    //Builder
    explicit Task(string description, bool completed = false):
            description(move(description)), isCompleted(completed) {};

    //Getter & setter of description
    const string &getDescription() const {
        return description;
    };
    void setDescription(const string &desc) {
        description = desc;
    }

    //Getter & setter of isCompleted
    bool getIsCompleted() const {
        return isCompleted;
    }
    void setIsCompleted(bool isComplete) {
        isCompleted = isComplete;
    }
};


#endif //TODO_LIST_TASK_H
