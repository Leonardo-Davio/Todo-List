//
// Created by Devs_leo on 19/02/2025.
//
#include "Gui.h"

int main() {
    // Initialise the program
    TodoList list("");
    cout << "------ Benvenuto nel programma Todo List ------\n";
    listSelect(list);

    int opMenu; // Variable that manage the value from the menuDisplay

    //Start the main program
    while(true){
        opMenu = menuDisplay();
        switch(opMenu){
            case 1:
                tasksDisplay(list);
                break;
            case 2:
                addTaskDisplay(list);
                break;
            case 3:
                removeTaskDisplay(list);
                break;
            case 4:
                completeTaskDisplay(list);
                break;

            case 5:
                if( deleteList(list)){
                    if(contAfterDel()){
                        cout << "\n---- Cambio della lista ----\n";
                        listSelect(list);
                        break;
                    }else{
                        return 0;
                    }
                }
                break;

            case 6:
                list.saveListOnDisk();
                cout << "\n---- Cambio della lista ----\n";
                listSelect(list);
                break;

            case 7:
                exitProgram(list);
                return 0;

            default:
                cerr << "\nERROR opMenu: value is not well define.";
                return 1;
        }
    }
}
