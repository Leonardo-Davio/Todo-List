//
// Created by Devs_leo on 24/02/2025.
//
#ifndef TODO_LIST_GUI_H
#define TODO_LIST_GUI_H
#include "TodoList.h"

// Display the menu for user to select the operation to do
int menuDisplay();

// Operation ->
    // Display all the task in the list
void tasksDisplay(TodoList &list);
    // Display for add a new task into the list
void addTaskDisplay(TodoList &list);
    // Display for remove the task from the list
void removeTaskDisplay(TodoList &list);
    // Display for completing the task + support
void completeTaskDisplay(TodoList &list);
void supportCompleteTaskDisplay(Task &task);
    // Delete list
bool deleteList(TodoList &list);
        // After deleting user can choose if exit from program or continue
bool contAfterDel();
    // Display and choose the list that there is in the folder
void listSelect(TodoList &list);
        // Support - take the name in the path folder and return a vector of the name of files
vector<string> listNameInFolder(TodoList &list);
    // Exit from the program
void exitProgram(TodoList &list);





#endif // TODO_LIST_GUI_H
