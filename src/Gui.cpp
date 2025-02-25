//
// Created by Devs_leo on 24/02/2025.
//

#include "Gui.h"
#include <limits>


// Display of the menu for the choose operation
int Gui::menuDisplay() {
    int num;
    cout << "\n---- Menu Todo List ----";
    cout << "\n1. Mostra lista\n2. Aggiungi compito\n3. Compito comletato\n4. Rimuovi compito\n5. Uscita dal programma";
    cout << "\nScegliere l'operazione:";
    cin >> num;
    // Check if the num is correct if not call again the function
    if (num < 1 || num > 5 || cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "L'inserimento non e' andato a buon fine, ritenta.\n";
        num = menuDisplay();
    }
    return num;
}

// Display of the all task to do
void Gui::tasksDisplay(TodoList &list) {
    // Initialise the local variable
    const vector <Task>& tasks = list.getList();
    int num = 1;

    // Display in the terminal
    cout << "\n----- Compiti da fare -----\n";
    if (tasks.empty()){
        cout << "La lista e' vuota.\n";
        return;
    }
    for(const auto &task: tasks){
        cout << num << " |";
        if (task.getIsCompleted()) { //Check if the task is completed or not
            cout << "  Fatto  | ";
        }else{
            cout << " Da fare | ";
        }
        cout << task.getDescription() << "\n";
        num++;  // Update the index
    }
}


// Display for add a new task on the list
void Gui::addTaskDisplay(TodoList &list) {
    // Initialise the local variable
    string word;
    string descriptionTask;

    // Display for the user
    cout << "\n----- Aggiunta compito da fare -----\n";
    cout << "Inserisci il compito da aggiungere: ";
    cin >> std::ws; // Ignore the first blank space.
    // Is it possible to use the get line for take the test but for some reason the google test do not like it.
    // For this reason I use a custom insert for take the description for the new task.
    while (cin >> word) {   // Creation of the description string
        if (!descriptionTask.empty()) {
            descriptionTask += " ";
        }
        descriptionTask += word;
        if (cin.peek() == '\n') {
            break;
        }
    }
    if (!descriptionTask.empty()) { // Check if the descriptionTAsk is empty and add to the list
        list.addTask(descriptionTask);
    } else {    // Error on the insert
        cout << "Inserimento non e' andato a buon fine.\nRitorno al menu principale";
    }
}

// Display for remove the task from the list
void Gui::removeTaskDisplay(TodoList &list) {
    // Initialise the local variable
    int index;
    string check;
    // Display for select the task to remove
    cout << "\n----- Rimozione di un compito -----\n";
    cout << "Inserisci il numero del compito da voler rimuovere: ";
    cin >> index;
    index--;   //The value taken from user start with 1, the list start with 0
    try {   //Try that index value is correct to remove the task
        Task task = list.getTask(index);
        cout << "\nStai eliminando il compito: \"" <<task.getDescription();
        cout << "\"\n[Y|N]->";
        cin >> check;   // Confirm the remove the task
        if( check == "Y"|| check == "y"){
            list.removeTask(index);
            cout << "\n--Il compito e' stato eliminato con successo!\n";
        } else{
            cout << "\n--Il compito non e' stato eliminato.\n";
        }
    } catch (const std::out_of_range& e) {  // Error lunch if the value is not well define.
        cout << "\nIl numero inserito non e' nella lista!\n";
    }
}

void Gui::completeTaskDisplay(TodoList &list) {
    // Initialise the local variable
    int index;
    string check;
    bool status;
    //Display for set the task is completed
    cout << "\n----- Compito completato -----\n";
    cout << "Inserisci il numero del compito da segnare come completato/da fare: ";
    cin >> index;
    index--;

    try {   // Try if the index value is valid to operate
        Task task = list.getTask(index);
        // Display witch task is to complete or for completing
        cout << "\nIl compito " << task.getDescription();
        if ((status = task.getIsCompleted())){
            cout << " lo stai impostando da completare. ";
        }else{
            cout << " lo hai completato.";
        }
        // Display the confirm of the operation
        cout << "\nConfermi l'operazione\n[Y|N] -> ";
        cin >> check;
        if( check == "Y"|| check == "y"){
            cout << "\n--Il compito e' ";
            if (status){
                status = false;
                cout << "da completare.\n";
            }else{
                status = true;
                cout << "completato.\n";
            }
            list.setCompleteTask(index, status);
        } else{
            cout << "\n--Il compito non e' stato modificato.\n";
        }
    } catch (const std::out_of_range& e) {  // Error lunch if the value is not well define.
        cout << "\nIl numero inserito non e' nella lista!\n";
    }
}

void Gui::exitProgram(TodoList &list, string &path) {
    cout << "\nSalvataggio delle task sul file: " << path;
    try{
        list.saveTasks(path);
        cout << "\nSalvataggio effettuato. Chiusura del programma, arrivederci.";
    } catch (const out_of_range &e){
        cout << "\nERROR on save: the filepath is null or not defined.\nThe program is closing anyway.";
    }

}

