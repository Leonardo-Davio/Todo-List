//
// Created by Devs_leo on 19/02/2025.
//

#ifndef TODO_LIST_TODOLIST_H
#define TODO_LIST_TODOLIST_H

#include "Task.h"
#include <vector>

class TodoList {
private:
    vector<Task> _list;

public:
    //builder & destroyer
    explicit TodoList(const vector<Task> &list, string &filepath);
    virtual ~TodoList() = default;

    //Methods for interacting with Task objects inside the _list vector.
    void addTask(const string &description);
    void setTaskDescription(int index, string &description);
    void setCompleteTask(int index, bool complete);

    //Methods for interacting with the _list vector
    void removeTask(int index);     //Index value is from the user input
    Task getTask(int index);

    //Method for take all the Task for display
    const vector<Task> &getList();

    //Methods to save Tasks to disk or unload them from disk to the _list vector
    void loadTasks(const string &filepath);
    void saveTasks(const string &filepath) const;
};


#endif //TODO_LIST_TODOLIST_H
