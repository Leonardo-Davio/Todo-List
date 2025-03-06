//
// Created by Devs_leo on 19/02/2025.
//

#ifndef TODO_LIST_TODOLIST_H
#define TODO_LIST_TODOLIST_H

#include "Task.h"
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

class TodoList{
private:
    vector<Task> list;
    string listName;
    const string pathFolder = "../../src/tasksFolder/";   //Default value

public:
    // Builder
    explicit TodoList(string name) : listName(move(name)) {}

    // Add a task in the vector of list
    void addTask(Task &task);

    // Clear the list
    void clearList();

    // Get and remove task by index
    Task &getTask(size_t index);
    bool removeTask(int index);

    // Get and remove task by description
    Task &getTaskByDescription(const string &desc);
    bool removeTaskByDescription(const string &desc);
    // Return task description with a partial description
    vector<string> searchTaskByPartialDescription(const string &desc) const;

    // Set and get the listName string
    void setListName(const string &name);
    const string &getListName() const;

    // Methods for counting the quantity of vector and tasks completed
    size_t taskCount();
    int taskDoneCount();

    // Methods for load and save the tasks on the disk
    void insertTaskOnList();
    void saveListOnDisk();
    bool delListOnDisk();

    // Get pathFolder
    const string &getPathFolder() const;

    /*Comments
     * addTask()override [DONE]
     * void removeTask() return bool [Done]
     * searchTask by description [Done] but need all description not a part of descrition
     * searchTask by part of description [done]
     * taskCount(), taskDoneCount() [Done]
     * loadtask(), savetask attribute [Done]
    */
};


#endif //TODO_LIST_TODOLIST_H
