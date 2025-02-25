//
// Created by Devs_leo on 24/02/2025.
//

#ifndef TODO_LIST_GUI_H
#define TODO_LIST_GUI_H
#include <iostream>
using namespace std;
#include "TodoList.h"

class Gui {
public:
    Gui() = default;

    static int menuDisplay();
    static void tasksDisplay(TodoList &list);
    static void addTaskDisplay(TodoList &list);
    static void removeTaskDisplay(TodoList &list);
    static void completeTaskDisplay(TodoList &list);

    static void exitProgram(TodoList &list, string &path);
};


#endif //TODO_LIST_GUI_H
