//
// Created by Devs_leo on 24/02/2025.
//
#include <gtest/gtest.h>
#include <fstream>
#include "Gui.h"

// Test function for menuDisplay
TEST(MenuDisplayTest, ValidInput) {
    // This test verifies that valid inputs are correctly accepted
    std::istringstream input("1\n");
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(menuDisplay(), 1);
}

TEST(MenuDisplayTest, InvalidInputRetry) {
    // This test verifies that invalid inputs are handled correctly and retried
    std::istringstream input("0\n2\n");
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(menuDisplay(), 2);
}

TEST(MenuDisplayTest, NonIntegerInput) {
    // This test verifies that non-integer inputs are handled correctly and retried
    std::istringstream input("abc\n3\n");
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(menuDisplay(), 3);
}


// Test function for tasksDisplay
TEST(TasksDisplayTest, DisplayEmptyList) {
    // This test verifies that an empty task list is handled correctly
    TodoList emptyList("");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    tasksDisplay(emptyList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_TRUE(output.str().find("non contiene nessun compito") != std::string::npos);
}

TEST(TasksDisplayTest, DisplayNonEmptyList) {
    // This test verifies that a non-empty task list is displayed correctly
    TodoList list("");
    Task task1("Task 1", false);
    Task task2("Task 2", true);
    list.addTask(task1);
    list.addTask(task2);

    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    tasksDisplay(list);

    std::cout.rdbuf(oldCoutBuf);
    std::string result = output.str();
    EXPECT_TRUE(result.find("Task 1 [Da completare]") != std::string::npos);
    EXPECT_TRUE(result.find("Task 2 [Completato]") != std::string::npos);
    EXPECT_TRUE(result.find("Ha da completare 1 attivita' su 2") != std::string::npos);
}

TEST(TasksDisplayTest, DisplayAllCompletedTasks) {
    // This test verifies that all completed tasks are displayed correctly
    TodoList list("");
    Task task1("Task 1", true);
    Task task2("Task 2", true);
    list.addTask(task1);
    list.addTask(task2);

    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    tasksDisplay(list);

    std::cout.rdbuf(oldCoutBuf);
    std::string result = output.str();
    EXPECT_TRUE(result.find("Task 1 [Completato]") != std::string::npos);
    EXPECT_TRUE(result.find("Task 2 [Completato]") != std::string::npos);
    EXPECT_TRUE(result.find("Ha da completare 0 attivita' su 2") != std::string::npos);
}


// Test function for addTaskDisplay
TEST(AddTaskDisplayTest, AddValidTask) {
    // This test verifies that a valid task is added correctly
    TodoList list("");
    std::istringstream input("Test task\n");
    std::cin.rdbuf(input.rdbuf());

    addTaskDisplay(list);

    ASSERT_EQ(list.taskCount(), 1);
    EXPECT_EQ(list.getTask(0).getDescription(), "Test task");
}

TEST(AddTaskDisplayTest, AddEmptyTask) {
    // This test verifies that an empty task is not added and an error message is displayed
    TodoList list("");
    std::istringstream input("\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    addTaskDisplay(list);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_EQ(list.taskCount(), 0);
    EXPECT_TRUE(output.str().find("Inserimento non e' andato a buon fine") != std::string::npos);
}

TEST(AddTaskDisplayTest, AddMultipleWordsTask) {
    // This test verifies that a task with multiple words in its description is added correctly
    TodoList list("");
    std::istringstream input("Test task with multiple words\n");
    std::cin.rdbuf(input.rdbuf());

    addTaskDisplay(list);

    ASSERT_EQ(list.taskCount(), 1);
    EXPECT_EQ(list.getTask(0).getDescription(), "Test task with multiple words");
}


// Test function for removeTaskDisplay
TEST(RemoveTaskDisplayTest, RemoveTaskByIndex) {
    // This test verifies that a task is removed correctly by index
    TodoList todoList("");
    Task task1("Task 1", false);
    Task task2("Task 2", true);
    todoList.addTask(task1);
    todoList.addTask(task2);

    std::istringstream input("1\n1\nY\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    removeTaskDisplay(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_EQ(todoList.taskCount(), 1);
    EXPECT_TRUE(output.str().find("--Il compito e' stato eliminato con successo!") != std::string::npos);
}

TEST(RemoveTaskDisplayTest, RemoveTaskByDescription) {
    // This test verifies that a task is removed correctly by description
    TodoList todoList("");
    Task task1("Task 1", false);
    Task task2("Task 2", true);
    todoList.addTask(task1);
    todoList.addTask(task2);

    std::istringstream input("2\nTask 2\nY\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    removeTaskDisplay(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_EQ(todoList.taskCount(), 1);
    EXPECT_TRUE(output.str().find("--Il compito e' stato eliminato con successo!") != std::string::npos);
}

TEST(RemoveTaskDisplayTest, RemoveNonExistentTask) {
    // This test verifies that attempting to remove a non-existent task is handled correctly
    TodoList todoList("");
    Task task1("Task 1", false);
    todoList.addTask(task1);

    std::istringstream input("1\n2\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    removeTaskDisplay(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_EQ(todoList.taskCount(), 1);
    EXPECT_TRUE(output.str().find("Task at index 1 not found.") != std::string::npos);
}

TEST(RemoveTaskDisplayTest, CancelOperation) {
    // This test verifies that canceling the remove task operation is handled correctly
    TodoList todoList("");
    Task task1("Task 1", false);
    todoList.addTask(task1);

    std::istringstream input("3\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    removeTaskDisplay(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_EQ(todoList.taskCount(), 1);
    EXPECT_FALSE(output.str().find("Ritorno al menu principale.") != std::string::npos);
}


// Test function for completeTaskDisplay and supportCompleteTaskDisplay
TEST(CompleteTaskDisplayTest, CompleteTaskByIndex) {
    // This test verifies that a task is marked as completed correctly by index
    TodoList todoList("");
    Task task1("Task 1", false);
    todoList.addTask(task1);

    std::istringstream input("1\n1\nY\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    completeTaskDisplay(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_TRUE(todoList.getTask(0).getIsCompleted());
    EXPECT_TRUE(output.str().find("L'attivita' e' stata impostatata: Completata.") != std::string::npos);
}

TEST(CompleteTaskDisplayTest, CompleteTaskByDescription) {
    // This test verifies that a task is marked as completed correctly by partial description
    TodoList todoList("");
    Task task1("Task 1", false);
    todoList.addTask(task1);

    std::istringstream input("2\nTask\nY\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    completeTaskDisplay(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_TRUE(todoList.getTask(0).getIsCompleted());
    EXPECT_TRUE(output.str().find("L'attivita' e' stata impostatata: Completata.") != std::string::npos);
}

TEST(CompleteTaskDisplayTest, CompleteNonExistentTaskByIndex) {
    // This test verifies that attempting to complete a non-existent task by index is handled correctly
    TodoList todoList("");
    Task task1("Task 1", false);
    todoList.addTask(task1);

    std::istringstream input("1\n2\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    completeTaskDisplay(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_FALSE(todoList.getTask(0).getIsCompleted());
    EXPECT_TRUE(output.str().find("Task at index 1 not found.") != std::string::npos);
}

// Test function for completeTaskDisplay and supportCompleteTaskDisplay
TEST(CompleteTaskDisplayTest, CompleteNonExistentTaskByDescription) {
    // This test verifies that attempting to complete a non-existent task by partial description is handled correctly
    TodoList todoList("");
    Task task1("Task 1", false);
    todoList.addTask(task1);

    std::istringstream input("2\nNon existent task\n3\n"); // Added '3\n' to exit the loop
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    completeTaskDisplay(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_FALSE(todoList.getTask(0).getIsCompleted());
    EXPECT_TRUE(output.str().find("Non esiste nessuna attivita' con la descrizione Non existent task") != std::string::npos);
}

TEST(CompleteTaskDisplayTest, CancelOperation) {
    // This test verifies that canceling the complete task operation is handled correctly
    TodoList todoList("");
    Task task1("Task 1", false);
    todoList.addTask(task1);

    std::istringstream input("3\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    completeTaskDisplay(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_FALSE(todoList.getTask(0).getIsCompleted());
}


// Test function for exitProgram
TEST(ExitProgramTest, SuccessfulSave) {
    // This test verifies that the list is saved successfully and the program exits
    TodoList todoList("TEST");
    Task task1("Task 1", false);
    todoList.addTask(task1);

    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    exitProgram(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_TRUE(output.str().find("Salvataggio effettuato. Chiusura del programma, arrivederci.") != std::string::npos);
}

TEST(ExitProgramTest, SaveException) {
    // This test verifies that an exception during saving is handled correctly
    TodoList todoList("");
    todoList.setListName(""); // Setting list name to empty to trigger the exception

    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    exitProgram(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_TRUE(output.str().find("ERROR on save: the filepath is null or not defined.\nThe program is closing anyway.") != std::string::npos);
}


// Test function for listSelect
TEST(ListSelectTest, ValidListSelection) {
    // This test verifies that a valid list name is selected correctly
    TodoList todoList("");
    std::ofstream("TEST.txt");  // Create a test file

    std::istringstream input("TEST\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    listSelect(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_EQ(todoList.getListName(), "TEST");
    EXPECT_TRUE(output.str().find("Liste attivita' salvate:") != std::string::npos);

    std::remove("TEST.txt");  // Clean up
}

TEST(ListSelectTest, ValidEmptyListSelection) {
    // This test verifies that a valid list name, but in the file there isn't any Task
    TodoList todoList("");
    std::ofstream("./tasksFolder/TEST.txt");

    std::istringstream input("TEST\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    listSelect(todoList);

    std::cout.rdbuf(oldCoutBuf);
    std::cin.rdbuf(nullptr);

    EXPECT_TRUE(output.str().find("Attenzione: Non ci sono compiti salvati sul file") != std::string::npos);

    std::remove("TEST.txt");
}

TEST(ListSelectTest, CreateNewList) {
    // This test verifies that a new list is created correctly
    TodoList todoList("");

    std::istringstream input("new\nNewList\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    listSelect(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_EQ(todoList.getListName(), "NewList");
    EXPECT_TRUE(output.str().find("Inserica il nome della lista che vorrebbe inserire") != std::string::npos);
}

TEST(ListSelectTest, InvalidListSelectionRetry) {
    // This test verifies that an invalid list name prompts the user to retry
    TodoList todoList("");
    std::ofstream("TEST.txt");  // Create a test file

    std::istringstream input("InvalidList\nTEST\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    listSelect(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_EQ(todoList.getListName(), "TEST");
    EXPECT_TRUE(output.str().find("Il nome della lista inserito non e' valido. Ritenta o crea una nuova.") != std::string::npos);

    std::remove("TEST.txt");  // Clean up
}


// Test function for listNameInFolder
TEST(ListNameInFolderTest, RetrieveFileNames) {
    // This test verifies that the function retrieves the correct list names from the folder
    TodoList todoList("");
    std::ofstream("./tasksFolder/TEST1.txt");
    std::ofstream("./tasksFolder/TEST2.txt");

    std::vector<std::string> fileNames = listNameInFolder(todoList);
    bool foundTest1 = false;
    bool foundTest2 = false;

    for (const auto& name : fileNames) {
        if (name == "TEST1") {
            foundTest1 = true;
        } else if (name == "TEST2") {
            foundTest2 = true;
        }
    }

    EXPECT_TRUE(foundTest1);
    EXPECT_TRUE(foundTest2);

    std::remove("./tasksFolder/TEST1.txt");
    std::remove("./tasksFolder/TEST2.txt");
}


// Test function for deleteList
TEST(DeleteListTest, ConfirmDelete) {
    // This test verifies that the list is deleted when the user confirms
    TodoList todoList("");
    todoList.setListName("TEST");
    std::ofstream("./tasksFolder/TEST.txt");

    std::istringstream input("Y\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    bool result = deleteList(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_TRUE(result);
    EXPECT_TRUE(output.str().find("La lista TEST e' stata eliminata con successo!") != std::string::npos);
    EXPECT_FALSE(std::ifstream("./tasksFolder/TEST.txt")); // Verify that the file no longer exists
}

TEST(DeleteListTest, CancelDelete) {
    // This test verifies that the list is not deleted when the user cancels
    TodoList todoList("./tasksFolder");
    todoList.setListName("TEST");
    std::ofstream("./tasksFolder/TEST.txt"); // Create a test file

    std::istringstream input("N\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    bool result = deleteList(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_FALSE(result);
    EXPECT_TRUE(output.str().find("L'operazione e' stata annullata.\nRitorno al menu principale.") != std::string::npos);
    EXPECT_TRUE(std::ifstream("./tasksFolder/TEST.txt")); // Verify that the file still exists
    std::remove("./tasksFolder/TEST.txt");
}

TEST(DeleteListTest, DeleteFailure) {
    // This test verifies that the appropriate message is displayed when the list deletion fails
    TodoList todoList("");
    todoList.setListName("TEST");

    std::istringstream input("Y\n");
    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());

    bool result = deleteList(todoList);

    std::cout.rdbuf(oldCoutBuf);
    EXPECT_FALSE(result);
    EXPECT_TRUE(output.str().find("La lista TEST non e' stata eliminata.") != std::string::npos);
}


// Test function for contAferDel [Continue After Delete the list]
TEST(ContAfterDelTest, HandlesYesInput) {
    std::istringstream input("y\n");
    std::cin.rdbuf(input.rdbuf());

    bool result = contAfterDel();
    EXPECT_FALSE(result);
}

TEST(ContAfterDelTest, HandlesNoInput) {
    std::istringstream input("N\n");
    std::cin.rdbuf(input.rdbuf());

    bool result = contAfterDel();
    EXPECT_FALSE(result);
}

TEST(ContAfterDelTest, HandlesInvalidInput) {
    std::istringstream input("invalid\n");
    std::cin.rdbuf(input.rdbuf());

    bool result = contAfterDel();
    EXPECT_TRUE(result);
}
