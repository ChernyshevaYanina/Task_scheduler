#include "test.h"

class TaskSchedulerTest : public ::testing::Test {
 protected:
  TaskScheduler scheduler;

  void SetUp() override {}
};

TEST_F(TaskSchedulerTest, AddAndRunSingleTask) {
  bool taskExecuted = false;
  auto timestamp = std::time(nullptr) + 1;

  scheduler.Add([&taskExecuted]() { taskExecuted = true; }, timestamp);

  std::this_thread::sleep_for(std::chrono::seconds(2));

  EXPECT_TRUE(taskExecuted);
}

TEST_F(TaskSchedulerTest, ExecuteMultipleTasks) {
  std::vector<bool> tasksExecuted(3, false);
  auto now = std::time(nullptr);

  for (int i = 0; i < 3; ++i) {
    scheduler.Add([i, &tasksExecuted]() { tasksExecuted[i] = true; },
                  now + i + 1);
  }

  std::this_thread::sleep_for(std::chrono::seconds(4));
  for (bool executed : tasksExecuted) {
    EXPECT_TRUE(executed);
  }
}

TEST_F(TaskSchedulerTest, ExecuteTaskInPast) {
  bool taskExecuted = false;
  auto pastTimestamp = std::time(nullptr) - 1;

  scheduler.Add([&taskExecuted]() { taskExecuted = true; }, pastTimestamp);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  EXPECT_TRUE(taskExecuted);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
