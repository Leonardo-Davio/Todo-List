//
// Created by Devs_leo on 19/02/2025.
//

#ifndef TODO_LIST_TASK_H
#define TODO_LIST_TASK_H

#include <iostream>
using namespace std;

class Task {
private:
    string _description;    //Description of the task
    bool _isCompleted;      //Need for check if the task is completed, but to not eliminate the task

public:
    //Builder
    explicit Task(string description, bool completed = false):
            _description(move(description)), _isCompleted(completed) {};

    //Getter & setter of _description
    const string &getDescription() const {
        return _description;
    };
    void setDescription(const string &description) {
        _description = description;
    }

    //Getter & setter of _isCompleted
    bool getIsCompleted() const {
        return _isCompleted;
    }
    void setIsCompleted(bool isCompleted) {
        _isCompleted = isCompleted;
    }
};


#endif //TODO_LIST_TASK_H
