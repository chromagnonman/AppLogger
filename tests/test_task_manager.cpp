#include <gtest/gtest.h>

#include "TaskManager.h"

using namespace Rightware::core;

TEST (TaskManager, ThreadInvocations)
{
    const auto task_handler = TaskManager::getInstance();
    ASSERT_NE(task_handler, nullptr);

    testing::internal::CaptureStdout();

    // Invoke a single thread
    task_handler->execute(std::thread([]{std::cout << "This is a thread!";}));

    std::string console = testing::internal::GetCapturedStdout();
    EXPECT_EQ("This is a thread!", console);

    // Execute multiple threads
    for (uint32_t i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        testing::internal::CaptureStdout();

        std::string output{"thread id: "};
        output += std::to_string(i);
        
        task_handler->execute(std::thread([=]{ std::cout << "thread id: " << i;}));

        std::string actual = testing::internal::GetCapturedStdout();
        EXPECT_EQ(actual, output);
    }
}