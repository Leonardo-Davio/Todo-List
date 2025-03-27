//
// Created by Devs_leo on 24/02/2025.
//

#include "Gui.h"
#include <limits>
#include <dirent.h>
#include <sstream>

int menuDisplay() {
    int num;
    cout << "\n---- Menu Todo List ----";
    cout << "\n1. Mostra lista"
            "\n2. Aggiungi compito"
            "\n3. Rimuovi compito"
            "\n4. Imposta compito completato"
            "\n5. Eliminazione della lista"
            "\n6. Cambia lista"
            "\n7. Uscita dal programma"
            "\nScegliere l'operazione:";
    cin >> num;
    // Check if the num is correct if not call again the function
    if (num < 1 || num > 8 || cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "L'inserimento non e' andato a buon fine, ritenta.\n";
        num = menuDisplay();
    }
    return num;
}

void tasksDisplay(TodoList &list) {

    cout << "\n----- Compiti da fare -----\n";

    if(list.taskCount() == 0){
        cout << "La lista " << list.getListName() << " non contiene nessun compito.\n";
        return;
    }

    cout << "-- " << list.getListName() << endl;
    for(size_t i = 0; i < list.taskCount(); i++){
        Task task = list.getTask(i);
        cout << i+1 << " | " << task.getDescription();
        if(task.getIsCompleted()){
            cout << " [Completato]\n";
        }else{
            cout << " [Da completare]\n";
        }
    }

    cout << "\nHa da completare " << list.taskCount() - list.taskDoneCount()
         << " attivita' su " << list.taskCount() << ".\n";
}

void addTaskDisplay(TodoList &list) {
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
        Task task(descriptionTask);
        list.addTask(task);
    } else {    // Error on the insert
        cout << "Inserimento non e' andato a buon fine.\nRitorno al menu principale";
    }
}

void removeTaskDisplay(TodoList &list) {
    // Initialise the local variable
    int index, op;
    string check, word, descriptionTask;
    // Display for select the task to remove
    cout << "\n----- Rimozione di un compito -----\n";
    cout << "Inserisca il numero dell'operazione da svoglere.\n"
            "1. Rimozione attivita' in base all'indice.\n"
            "2. Rimozione attivita' in base alla descrizione.\n"
            "3. Annullamento dell'opreazione.\n"
            "Operazione scelta: ";
    cin >> op;
    // Check if the num is correct if not call again the function
    switch (op) {
        case 3:
            return;

        case 1:
            cout << "\nE' stato scelto la rimozione con l'indice.\n"
                    "Inserisca l'indice: ";
            cin >> index;
            index--;
            try {
                Task task = list.getTask(index);
                cout << "--Sai elimando l'attivita': " << task.getDescription() << endl;
                cout << "Conferma? [Y|N]->";
                cin >> check;
                if (check == "Y" || check == "y") {
                    list.removeTask(index);
                    cout << "\n--Il compito e' stato eliminato con successo!\n";
                } else {
                    cout << "\n--Il compito non e' stato eliminato.\n";
                }
            }
            catch (out_of_range &e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << e.what() << endl;
            }
            cout << "Ritorno al menu principale.\n";
            return;

        case 2: {
            cout << "\nE' stato scleto la rimozione con descrizione.\n"
                    "Inserisca la descrizione completa dell'attivita' da eliminare:\n";
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
            vector<string> matchDesc = list.searchTaskByPartialDescription(descriptionTask);
            if (matchDesc.empty()) {
                cout << "\nNon esiste nessuna attivita' con la descrizione " << descriptionTask << endl;
            } else {
                if (matchDesc.size() != 1) {
                    cout << "\nEsistono piu' attivita' con la descrizione immessa."
                            "\nIndicare con un numero l'indice dell'attivta' da eliminare.";
                    int i = 1;
                    for (const auto &desc: matchDesc) {
                        cout << endl << i << ". " << desc;
                        i++;
                    }
                    cout << "\nIndice scelto: ";
                    cin >> index;
                    index--;
                    if (index < 0 && index > matchDesc.size()) {
                        cout << "\nIl valore inserito e' errato. Ritorno al memnu principale.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        return;
                    }
                } else {
                    index = 0;
                }
                try {
                    Task task = list.getTask(matchDesc[index]);
                    cout << "--Sai elimando l'attivita': " << task.getDescription() << endl;
                    cout << "Conferma? [Y|N]->";
                    cin >> check;
                    if (check == "Y" || check == "y") {
                        list.removeTask(descriptionTask);
                        cout << "\n--Il compito e' stato eliminato con successo!\n";
                    } else {
                        cout << "\n--Il compito non e' stato eliminato.\n";
                    }
                }
                catch (out_of_range &e) {
                    cout << endl << e.what() << endl;
                }
            }
            cout << "Ritorno al menu principale.\n";
            return;
        }

        default:
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "L'inserimento non e' andato a buon fine, ritenta.\n";
            removeTaskDisplay(list);
            return;
    }
}

void completeTaskDisplay(TodoList &list) {
    // Initialise the local variable
    int index, op;
    string check, word, descriptionTask;
    //Display for set the task is completed
    cout << "\n----- Compito completato -----\n"
            "Inserisca il numero dell'operazione da svolgere.\n"
            "1. Completa l'attivita' attraverso l'indice.\n"
            "2. Completa l'attivita' attraverso la descrizione.\n"
            "3. Annullamento dell'opreazione.\n"
            "Operazione scelta: ";
    cin >> op;
    switch (op) {
        case 3:
            return;

        case 1:
            cout << "\nE' stato la scelto l'opreazione completa attivita' in base all'indice.\n"
                    "Inserisca ora l'indice dell'attivita' da completare: ";
            cin >> index;
            try {
                index--;
                Task &task = list.getTask(index);
                supportCompleteTaskDisplay(task);
                return;
            }
            catch (out_of_range &e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << e.what() << endl;
            }

        case 2:{
            cout << "\nE' stato la scelto l'opreazione completa attivita' in base alla descrizione.\n"
                    "Inserisca la descrizione completa dell'attivita' da completare:\n ";
            cin >> ws;
            while (cin >> word) {
                if (!descriptionTask.empty()) {
                    descriptionTask += " ";
                }
                descriptionTask += word;
                if (cin.peek() == '\n') {
                    break;
                }
            }
            vector<string> matchDesc = list.searchTaskByPartialDescription(descriptionTask);
            if (matchDesc.empty()) {
                cout << "\nNon esiste nessuna attivita' con la descrizione " << descriptionTask << endl;
            } else {
                if (matchDesc.size() != 1) {
                    cout << "\nEsistono piu' attivita' con la descrizione immessa."
                            "\nIndicare con un numero l'indice dell'attivta' da eliminare.";
                    int i = 1;
                    for (const auto &desc: matchDesc) {
                        cout << endl << i << ". " << desc;
                        i++;
                    }
                    cout << "\nIndice scelto: ";
                    cin >> index;
                    index--;
                    if (index < 0 && index > matchDesc.size()) {
                        cout << "\nIl valore inserito e' errato. Ritorno al memnu principale.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        return;
                    }
                } else {
                    index = 0;
                }
                try {
                    Task &task = list.getTask(matchDesc[index]);
                    supportCompleteTaskDisplay(task);
                    return;
                }
                catch (out_of_range &e) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << endl << e.what() << endl;
                    return;
                }
            }
        }

        default:
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "L'inserimento non e' andato a buon fine, ritenta.\n";
            completeTaskDisplay(list);
            return;
    }
}
void supportCompleteTaskDisplay(Task &task){
    string check;
    cout << "\nStai completando l'atttivita': " << task.getDescription()<< endl;
    if (task.getIsCompleted()){
        cout << "L'attivita' scelta e' completata. "
                "Stai quindi impostando l'attivita': Da completare.\n"
                "Confermi la scelta [Y|N] ->";
        cin >> check;
        if (check == "y" || check == "Y"){
            cout << "\nL'attivita' e' stata impostatata: Da completare.\n";
            task.setIsCompleted(false);
        }else{
            cout << "\nOperazione annullata!\n";
        }
    }else{
        cout << "L'attivita' scelta e' da completare. "
                "Stai quindi impostando l'attivita': Completata.\n"
                "Confermi la scelta [Y|N] ->";
        cin >> check;
        if (check == "y" || check == "Y"){
            cout << "\nL'attivita' e' stata impostatata: Completata.\n";
            task.setIsCompleted(true);
        }else{
            cout << "\nOperazione annullata!\n";
        }
    }
    cout << "Ritorno al menu principale.\n";
}

void exitProgram(TodoList &list) {
    cout << "\nSalvataggio delle task sul file: " << list.getListName() <<".txt";
    try{
        list.saveTask();
        cout << "\nSalvataggio effettuato. Chiusura del programma, arrivederci.";
    } catch (const out_of_range &e){
        cout << "\nERROR on save: the filepath is null or not defined.\nThe program is closing anyway.";
    }

}

void listSelect(TodoList &list){
    string text;
    bool found = false;
    cout << "Liste attivita' salvate: \n";
    vector<string> listName = listNameInFolder(list);
    for (const auto &itr : listName ){
        cout << "- " <<itr << endl;
    }
    cout << "Digiti il nome della lista da usare. Scriva new per creare una nuova lista\n"
            "Lista: ";
    cin >> text;
    if(text == "new"){
        cout << "\nInserica il nome della lista che vorrebbe inserire: ";
        cin.clear();
        cin >> text;
        list.setListName(text);
        return;
    }
    for(const auto &itr : listName) {
        if( itr == text){
            found = true;
            list.setListName(text);
            break;
        }
    }
    if(!found){
        cout << "Il nome della lista inserito non e' valido. Ritenta o crea una nuova.\n";
        listSelect(list);
        return;
    }
    try{
        list.loadTask();
    }
    catch (const out_of_range &e){
        cout << "Attenzione: " << e.what() << list.getListName() <<".\n";
    }
}

vector<string> listNameInFolder(TodoList &list){
    vector<string> fileName;
    DIR *dir = opendir(list.getPathFolder().c_str());
    if (dir) {
        dirent *entry;
        while ((entry = readdir(dir)) != nullptr) {
            string name = entry->d_name;
            if (name.size() > 4 && name.substr(name.size() - 4) == ".txt") {
                name.erase(name.length()-4);
                fileName.push_back(name);
            }
        }
        closedir(dir);
    } else {
        throw out_of_range("La cartella non contiene nessun file.");
    }
    return fileName;
}

bool deleteList(TodoList &list){
    string check;
    cout << "\n---- Eliminazione della lista ----\n"
            "Stai eliminando la lista di nome: " << list.getListName() <<
            "\nConferma la scelta, non sara' possibile ripristinare dopo la conferma\n"
            "Conferma [Y|N]->";
    cin >> check;
    if (check == "y" || check == "Y"){
        if(list.delListOnDisk()){
            cout << "\nLa lista " << list.getListName() << " e' stata eliminata con successo!";
            list.clearList();
            return true;
        }else{
            cout << "\nLa lista " << list.getListName() << " non e' stata eliminata.\n"
                     "Ritorno al menu principale.\n";
            return false;
        }
    }else{
        cout << "\nL'operazione e' stata annullata.\nRitorno al menu principale.\n";
        return false;
    }
}
bool contAfterDel(){
    string check;
    cout << "\nChiudere il programma?\n[Y|N] ->";
    cin >> check;
    if(check == "y" || check == "N"){
        return false;
    }
    return true;
}