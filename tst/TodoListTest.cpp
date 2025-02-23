//
// Created by Devs_leo on 22/02/2025.
//
#include <gtest/gtest.h>
#include "../src/TodoList.h"
#include <fstream>


// Test loading tasks from file
TEST(TodoListTest, LoadTasks) {
    // Setup: create a temporary file with tasks
    std::ofstream file("tasksTest.txt");
    file << "Task 1;1\nTask 2;0\n";
    file.close();

    // Initialize an empty TodoList
    std::vector<Task> initialTasks;
    std::string filepath = "tasksTest.txt";
    TodoList todoList(initialTasks, filepath);

    // Load tasks from the file
    todoList.loadTasks(filepath);

    // Check if the tasks from the file are loaded correctly
    ASSERT_EQ(todoList.getTask(0).getDescription(), "Task 1");
    ASSERT_TRUE(todoList.getTask(0).getIsCompleted());
    ASSERT_EQ(todoList.getTask(1).getDescription(), "Task 2");
    ASSERT_FALSE(todoList.getTask(1).getIsCompleted());
}

// Test saving tasks to file
TEST(TodoListTest, SaveTasks) {
    // Clear the file tasksTest.txt
    std::ofstream _file("tasksTest.txt");
    _file << "";
    _file.close();

    // Initialize a TodoList with some tasks
    std::vector<Task> initialTasks = {Task("Task 1", true), Task("Task 2", false)};
    std::string filepath = "tasksTest.txt";
    TodoList todoList(initialTasks, filepath);

    // Save tasks to the file
    todoList.saveTasks(filepath);

    // Verify the contents of the file
    std::ifstream file(filepath);
    std::string line;
    getline(file, line);
    ASSERT_EQ(line, "Task 1;1");
    getline(file, line);
    ASSERT_EQ(line, "Task 2;0");
    file.close();
}


// Test removing tasks
TEST(TodoListTest, RemoveTask) {
    // Clear the file tasksTest.txt
    std::ofstream file("tasksTest.txt");
    file << "";
    file.close();

    // Initialize a TodoList with some tasks
    std::vector<Task> initialTasks;
    std::string filepath = "tasksTest.txt";
    TodoList todoList(initialTasks, filepath);
    todoList.addTask("Task 1");
    todoList.addTask("Task 2");
    todoList.setCompleteTask(1,true);

    // Remove the first task
    todoList.removeTask(0);
    ASSERT_EQ(todoList.getTask(0).getDescription(), "Task 2");
    ASSERT_TRUE(todoList.getTask(0).getIsCompleted());

    // Check if the index is not in the list
    ASSERT_THROW(todoList.getTask(10), std::out_of_range);

    // Remove the second task (now the first task after the previous removal)
    todoList.removeTask(0);
    ASSERT_THROW(todoList.getTask(0), std::out_of_range);
}

// Test getting tasks
TEST(TodoListTest, GetTask) {
    // Clear the file tasksTest.txt
    std::ofstream file("tasksTest.txt");
    file << "";
    file.close();

    // Initialize a TodoList with some tasks
    std::vector<Task> initialTasks;
    std::string filepath = "tasksTest.txt";
    TodoList todoList(initialTasks, filepath);
    todoList.addTask("Task 1");
    todoList.addTask("Task 2");
    todoList.setCompleteTask(1, true);

    // Get the first task
    ASSERT_EQ(todoList.getTask(0).getDescription(), "Task 1");
    ASSERT_FALSE(todoList.getTask(0).getIsCompleted());

    // Get the second task
    ASSERT_EQ(todoList.getTask(1).getDescription(), "Task 2");
    ASSERT_TRUE(todoList.getTask(1).getIsCompleted());

    // Test out of range index
    ASSERT_THROW(todoList.getTask(2), std::out_of_range);
}

// Test adding tasks
TEST(TodoListTest, AddTask) {
    //Clear the file tasksTest.txt
    std::ofstream file("tasksTest.txt");
    file << "";
    file.close();

    // Initialize a TodoList with some tasks
    std::vector<Task> initialTasks;
    std::string filepath = "tasksTest.txt";
    TodoList todoList(initialTasks, filepath);

    // Add a new task
    todoList.addTask("New Task");
    ASSERT_EQ(todoList.getTask(0).getDescription(), "New Task");
    ASSERT_FALSE(todoList.getTask(0).getIsCompleted());
}

// Test setting task description
TEST(TodoListTest, SetTaskDescription) {
    std::vector<Task> initialTasks = { Task("Initial Task", false) };
    std::string filepath = "tasksTest.txt";
    TodoList todoList(initialTasks, filepath);

    // Set a new description for the existing task
    std::string newDescription = "Updated Task Description";
    todoList.setTaskDescription(0, newDescription);
    ASSERT_EQ(todoList.getTask(0).getDescription(), "Updated Task Description");
}

// Test setting task completion status
TEST(TodoListTest, SetCompleteTask) {
    std::vector<Task> initialTasks = { Task("Task to Complete", false) };
    std::string filepath = "tasksTest.txt";
    TodoList todoList(initialTasks, filepath);

    // Set the task as completed
    todoList.setCompleteTask(0, true);
    ASSERT_TRUE(todoList.getTask(0).getIsCompleted());

    // Set the task as not completed
    todoList.setCompleteTask(0, false);
    ASSERT_FALSE(todoList.getTask(0).getIsCompleted());
}

// Test constructor initialization
TEST(TodoListTest, ConstructorInitialization) {
    // Setup: create a temporary file with tasks
    std::ofstream file("tasksTest.txt");
    file << "Task 1;1\nTask 2;0\n";
    file.close();

    // Initialize TodoList with predefined tasks and file path
    std::vector<Task> initialTasks;
    std::string filepath = "tasksTest.txt";
    TodoList todoList(initialTasks, filepath);
    todoList.addTask("Initial Task 1");
    todoList.addTask("Initial Task 2");
    todoList.setCompleteTask(0, true);
    todoList.setCompleteTask(3, true);

    // Check if the tasks from the file are loaded correctly
    ASSERT_EQ(todoList.getTask(0).getDescription(), "Task 1");
    ASSERT_TRUE(todoList.getTask(0).getIsCompleted());
    ASSERT_EQ(todoList.getTask(1).getDescription(), "Task 2");
    ASSERT_FALSE(todoList.getTask(1).getIsCompleted());

    // Check if the initial tasks provided to the constructor are present in the list
    ASSERT_EQ(todoList.getTask(2).getDescription(), "Initial Task 1");
    ASSERT_FALSE(todoList.getTask(2).getIsCompleted());
    ASSERT_EQ(todoList.getTask(3).getDescription(), "Initial Task 2");
    ASSERT_TRUE(todoList.getTask(3).getIsCompleted());
}
