//
// Created by Devs_leo on 19/02/2025.
//
#include "Gui.h"

int main() {
    // Initialise the program
    string filepath = "../../src/tasks.txt";  //Change here for a different disc file folder src, not cmake folder
    vector<Task> tasks;
    TodoList list(tasks, filepath);
    int opMenu; // Variable that manage the value from the menuDisplay

    //Start the main program
    while(true){
        opMenu = Gui::menuDisplay();
        switch(opMenu){
            case 1:
                Gui::tasksDisplay(list);
                break;
            case 2:
                Gui::addTaskDisplay(list);
                break;
            case 3:
                Gui::completeTaskDisplay(list);
                break;
            case 4:
                Gui::removeTaskDisplay(list);
                break;
            case 5:
                Gui::exitProgram(list, filepath);
                return 0;

            default:
                cout << "\nERROR opMenu: value is not well define.";
                return 1;
        }
    }
}
