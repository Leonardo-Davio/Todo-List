//
// Created by Devs_leo on 19/02/2025.
//

#include "TodoList.h"
#include <fstream>  //Lib for work with the external file
#include <sstream>

TodoList::TodoList(const vector<Task> &list, string &filepath): _list(list) {
    loadTasks(filepath);
}

//Methods for interacting with Task objects inside the _list vector.
void TodoList::addTask(const string &description) {
    Task task(description);
    _list.push_back(task);
}

void TodoList::setTaskDescription(int index, string &description) {
    if (index < 0 || index >= _list.size()) {
        throw out_of_range("Index out of range on setTaskDescription");
    }
    _list[index].setDescription(description);
}

void TodoList::setCompleteTask(int index, bool complete) {
    if (index < 0 || index >= _list.size()) {
        throw out_of_range("Index out of range on setCompleteTask");
    }
    _list[index].setIsCompleted(complete);
}

//Methods for interacting with the _list vector
void TodoList::removeTask(int index) {
    if (index < 0 || index >= _list.size()) {
        throw out_of_range("Index out of range on removeTask()");
    }
    _list.erase(_list.begin() + index);
}

Task TodoList::getTask(int index) {
    if (index < 0 || index >= _list.size()) {
        throw out_of_range("Index out of range on getTask()");
    }
    return _list[index];
}

//Methods to save Tasks to disk or unload them from disk to the _list vector
void TodoList::loadTasks(const string &filepath) {
    ifstream file(filepath);
    if (!file.is_open()){
        throw out_of_range("Impossible to open the file on loadTask()");
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string description, completeStr;
        if (getline(iss, description, ';')&&getline(iss, completeStr)) {
            bool completed = (completeStr == "1");
            _list.emplace_back(description, completed);
        }
    }
    file.close();
}

void TodoList::saveTasks(const string &filepath) const {
    ofstream file(filepath);
    if (!file.is_open()){
        throw out_of_range("Impossible to open the file on loadTask()");
    }
    for (const auto &task: _list) {
        file << task.getDescription() << ";" << task.getIsCompleted();
    }
    file.close();
}
