//
// Created by Devs_leo on 24/02/2025.
//
#include <gtest/gtest.h>
#include <fstream>
#include "Gui.h"

// Test the Operation select menu
TEST(GuiTest, MenuDisplayTest) {
    std::stringstream input("3");
    std::cin.rdbuf(input.rdbuf());

    int result = Gui::menuDisplay();
    EXPECT_EQ(result, 3);
}

// Test the result of display all the task on the list
TEST(GuiTest, TasksDisplayTest) {
    // Set the file and initialise the list
    std::ofstream file("tasksTest.txt");
    file << "Task 1;1 \nTask 2;0 \n";
    file.close();
    std::vector<Task> initialTasks;
    std::string filepath = "tasksTest.txt";
    TodoList list(initialTasks, filepath);

    // Take the output
    std::stringstream output;
    std::cout.rdbuf(output.rdbuf());
    // Check teh output
    Gui::tasksDisplay(list);
    std::string expectedOutput = "\n----- Compiti da fare -----\n1 | 9675 | Task 1\n2 | 9675 | Task 2\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

// Test if the result of the display of adding a new task
TEST(GuiTest, AddTaskDisplayTest) {
    // Set the file and initialise the list
    std::ofstream file("tasksTest.txt");
    file << "Task 1;1 \nTask 2;0 \n";
    file.close();
    std::vector<Task> initialTasks;
    std::string filepath = "tasksTest.txt";
    TodoList list(initialTasks, filepath);

    // Set the input for adding the new task
    std::stringstream input("New Task");
    std::cin.rdbuf(input.rdbuf());
    // Check if corrected output
    Gui::addTaskDisplay(list);
    EXPECT_EQ(list.getList().size(), 3);
    EXPECT_EQ(list.getList().back().getDescription(), "New Task");
}

// Test if the remove of the task is corrected
TEST(GuiTest, RemoveTaskDisplayTest) {
    // Set the file and initialise the list
    std::ofstream file("tasksTest.txt");
    file << "Task 1;1 \nTask 2;0 \n";
    file.close();
    std::vector<Task> initialTasks;
    std::string filepath = "tasksTest.txt";
    TodoList list(initialTasks, filepath);

    // Set the input to operate
    std::stringstream input("1\nY");
    std::cin.rdbuf(input.rdbuf());
    // Check if the output is corrected
    Gui::removeTaskDisplay(list);
    EXPECT_EQ(list.getList().size(), 1);
    EXPECT_EQ(list.getList().front().getDescription(), "Task 2");
}

// Test is the switch of completing task is correct
TEST(GuiTest, CompleteTaskDisplayTest) {
    // Set the file and initialise the list
    std::ofstream file("tasksTest.txt");
    file << "Task 1;1 \nTask 2;0 \n";
    file.close();
    std::vector<Task> initialTasks;
    std::string filepath = "tasksTest.txt";
    TodoList list(initialTasks, filepath);

    // Set the input
    std::stringstream input("1\nY");
    std::cin.rdbuf(input.rdbuf());
    // Check the output
    Gui::completeTaskDisplay(list);
    EXPECT_TRUE(list.getList().front().getIsCompleted());
}