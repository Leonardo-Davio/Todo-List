//
// Created by Devs_leo on 19/02/2025.
//

#include "TodoList.h"
#include <dirent.h>
#include <sstream>
#include <cstdio>

void TodoList::addTask(Task &task) {
    list.push_back(task);
}

Task &TodoList::getTask(size_t index) {
    if (index < list.size()) {
        return list[index];
    }
    throw out_of_range("Task at index " + to_string(index) + " not found.");
}

bool TodoList::removeTask(int index) {
    if (index < list.size() || index < 0) {
        list.erase(list.begin() + index);
        return true;
    }
    return false;
}

Task& TodoList::getTaskByDescription(const string &desc) {
    for (auto& task : list) {
        if (task.getDescription() == desc) {
            return task;
        }
    }
    throw out_of_range("Attivita' con descrizione " + desc + " non e' stata trovata.");
}

bool TodoList::removeTaskByDescription(const string &desc) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->getDescription() == desc) {
            list.erase(it);
            return true;
        }
    }
    return false;
}

void TodoList::setListName(const string &name) {
    listName = name;
}

const string &TodoList::getListName() const {
    return listName;
}

size_t TodoList::taskCount() {
    return list.size();
}

int TodoList::taskDoneCount() {
    int count = 0 ;
    for ( const auto& task: list ){
        if (task.getIsCompleted()){
            count++;
        }
    }
    return count;
}

void TodoList::insertTaskOnList() {
    string listNameFile = pathFolder+listName+".txt";
    ifstream file(listNameFile);
    // Check if the file exist
    if (!file) {
        throw out_of_range("Errore: impossibile aprire il file "+listName);
    }
    // Check if the file is empty
    file.seekg(0, ios::end);
    if (file.tellg() == 0) {
        file.close();
        throw out_of_range("Non ci sono compiti salvati sul file");
    }
    // Return the pointer to the origin and upload the task saved.
    file.seekg(0, ios::beg);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string description, completeStr;
        if (getline(iss, description, ';')&&getline(iss, completeStr)) {
            bool completed = (completeStr == "1");
            Task task(description,completed);
            addTask(task);
        }
    }
    file.close();
}

void TodoList::saveListOnDisk() {
    string listNameFile = pathFolder+listName+".txt";
    if (listName.empty()){
        throw out_of_range("Impossible to open the file for saving the list");
    }
    ofstream file(listNameFile);
    if(!file.is_open()){
        throw out_of_range("Impossible to open the file for saving the list");
    }
    file << "";
    for(auto & itr : list){
        file << itr.getDescription() << ";" << itr.getIsCompleted() << endl;
    }
    file.close();
}

bool TodoList::delListOnDisk() {
    string listNameFile = pathFolder+listName+".txt";
    if (remove(listNameFile.c_str()) == 0){
        return true;
    }
    return false;
}

const string &TodoList::getPathFolder() const {
    return pathFolder;
}

vector<string> TodoList::searchTaskByPartialDescription(const string &desc) const{
    vector<string> matchDesc;
    for (const auto &task : list){
        if (task.getDescription().find(desc) != string::npos){
            matchDesc.push_back(task.getDescription());
        }
    }
    return matchDesc;
}
