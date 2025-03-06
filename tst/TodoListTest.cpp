//
// Created by Devs_leo on 22/02/2025.
//
#include <gtest/gtest.h>
#include "Task.h" // Ensure that the Task.h file is correctly included
#include "TodoList.h"

// Test for addTask function
TEST(TodoListTest, AddTask) {
    TodoList todoList("");
    Task task("Task 1", false);
    todoList.addTask(task);
    ASSERT_EQ(todoList.taskCount(), 1);
}

// Get and delete by index
// Test for getTask function
TEST(TodoListTest, GetTask) {
    TodoList todoList("");
    Task task("Task 1", false);
    todoList.addTask(task);
    Task& retrievedTask = todoList.getTask(0);
    ASSERT_EQ(retrievedTask.getDescription(), "Task 1");
}

// Test for exception in getTask function
TEST(TodoListTest, GetTaskException) {
    TodoList todoList("");
    EXPECT_THROW(todoList.getTask(0), std::out_of_range);
}

// Test for removeTask function
TEST(TodoListTest, RemoveTask) {
    TodoList todoList("");
    Task task("Task 1", false);
    todoList.addTask(task);
    bool removed = todoList.removeTask(0);
    ASSERT_TRUE(removed);
    ASSERT_EQ(todoList.taskCount(), 0);
}

// Test for removeTask function with invalid index
TEST(TodoListTest, RemoveTaskInvalidIndex) {
    TodoList todoList("");
    Task task("Task 1", false);
    todoList.addTask(task);
    bool removed = todoList.removeTask(1);
    ASSERT_FALSE(removed);
}

// Task using description for get, delete and search with partial desc
// Test for getTaskByDescription function
TEST(TodoListTest, GetTaskByDescription) {
    TodoList todoList("");
    Task task("Task 1", false);
    todoList.addTask(task);
    Task& retrievedTask = todoList.getTaskByDescription("Task 1");
    ASSERT_EQ(retrievedTask.getDescription(), "Task 1");
}

// Test for exception in getTaskByDescription function
TEST(TodoListTest, GetTaskByDescriptionException) {
    TodoList todoList("");
    EXPECT_THROW(todoList.getTaskByDescription("Task 1"), std::out_of_range);
}

// Test for removeTaskByDescription function
TEST(TodoListTest, RemoveTaskByDescription) {
    TodoList todoList("");
    Task task("Task 1", false);
    todoList.addTask(task);
    bool removed = todoList.removeTaskByDescription("Task 1");
    ASSERT_TRUE(removed);
    ASSERT_EQ(todoList.taskCount(), 0);
}

// Test for removeTaskByDescription function with invalid description
TEST(TodoListTest, RemoveTaskByDescriptionInvalid) {
    TodoList todoList("");
    Task task("Task 1", false);
    todoList.addTask(task);
    bool removed = todoList.removeTaskByDescription("Task 2");
    ASSERT_FALSE(removed);
}

// Test for findTasksWithDescription function
TEST(TodoListTest, FindTasksWithDescription) {
    TodoList todoList("");
    Task task1("Completa il report", false);
    Task task2("Riguarda il budget", true);
    Task task3("Finire la presentazione", false);
    Task task4("Organizza l'incontro", true);
    Task task5("Aggiorna il sitoweb", false);

    todoList.addTask(task1);
    todoList.addTask(task2);
    todoList.addTask(task3);
    todoList.addTask(task4);
    todoList.addTask(task5);

    std::string desc = "il";
    std::vector<std::string> result = todoList.searchTaskByPartialDescription(desc);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "Completa il report");
    EXPECT_EQ(result[1], "Riguarda il budget");
    EXPECT_EQ(result[2], "Aggiorna il sitoweb");
}


// Test for setListName and getListName functions
TEST(TodoListTest, SetAndGetListName) {
    TodoList todoList("");
    todoList.setListName("MyTasks");
    ASSERT_EQ(todoList.getListName(), "MyTasks");
}

// Counting functions
// Test for taskCount function
TEST(TodoListTest, TaskCount) {
    TodoList todoList("");
    Task task1("Task 1", false);
    Task task2("Task 2", false);
    todoList.addTask(task1);
    todoList.addTask(task2);
    ASSERT_EQ(todoList.taskCount(), 2);
}

// Test for taskDoneCount function
TEST(TodoListTest, TaskDoneCount) {
    TodoList todoList("");
    Task task1("Task 1", true);
    Task task2("Task 2", false);
    todoList.addTask(task1);
    todoList.addTask(task2);
    ASSERT_EQ(todoList.taskDoneCount(), 1);
}

// methods for lad and save tasks on disk
// Test for insertTaskOnList function
TEST(TodoListTest, InsertTaskOnList) {
    TodoList todoList("");
    todoList.setListName("MyTasks");
    EXPECT_THROW(todoList.insertTaskOnList(), std::out_of_range);
}

// Test for saveListOnDisk function
TEST(TodoListTest, SaveListOnDisk) {
    TodoList todoList("");
    Task task("Task 1", false);
    todoList.addTask(task);
    todoList.setListName("MyTasks");
    EXPECT_NO_THROW(todoList.saveListOnDisk());

    // Check if the file is created and contains the correct data
    std::ifstream file(todoList.getPathFolder() + "MyTasks.txt");
    ASSERT_TRUE(file.is_open());

    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "Task 1;0");
    file.close();
}

// Test for delListOnDisk function
TEST(TodoListTest, DelListOnDisk) {
    TodoList todoList("");
    todoList.setListName("MyTasks");
    todoList.saveListOnDisk(); // Ensure the file is created

    // Check if the file is deleted successfully
    EXPECT_TRUE(todoList.delListOnDisk());

    // Verify the file no longer exists
    std::ifstream file(todoList.getPathFolder() + "MyTasks.txt");
    ASSERT_FALSE(file.is_open());
}


// Test for getPathFolder function
TEST(TodoListTest, GetPathFolder) {
    TodoList todoList("");
    ASSERT_EQ(todoList.getPathFolder(), "../../src/tasksFolder/");
}