//
// Created by Devs_leo on 22/02/2025.
//
#include <gtest/gtest.h>
#include "task.h"

TEST(TaskTest, DescriptionGetterAndSetter) {
    Task task("Initial Description");
    ASSERT_EQ(task.getDescription(), "Initial Description");

    task.setDescription("Updated Description");
    ASSERT_EQ(task.getDescription(), "Updated Description");
}

TEST(TaskTest, IsCompletedGetterAndSetter) {
    Task task("Task Description");
    ASSERT_FALSE(task.getIsCompleted());

    task.setIsCompleted(true);
    ASSERT_TRUE(task.getIsCompleted());

    task.setIsCompleted(false);
    ASSERT_FALSE(task.getIsCompleted());
}

TEST(TaskTest, ConstructorInitialization) {
    Task task("New Task", true);
    ASSERT_EQ(task.getDescription(), "New Task");
    ASSERT_TRUE(task.getIsCompleted());

    Task task2("Another Task");
    ASSERT_EQ(task2.getDescription(), "Another Task");
    ASSERT_FALSE(task2.getIsCompleted());
}

