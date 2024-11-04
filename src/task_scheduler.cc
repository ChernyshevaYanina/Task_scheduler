#include "task_scheduler.h"

TaskScheduler::~TaskScheduler() {
  for (auto &thread : threads) {
    if (thread.joinable()) thread.join();
  }
}

void TaskScheduler::Add(std::function<void()> task, std::time_t timestamp) {
  std::lock_guard<std::mutex> lock(mtx);

  threads.emplace_back([task, timestamp]() {
    std::this_thread::sleep_until(

        std::chrono::system_clock::from_time_t(timestamp));

    task();
  });
}