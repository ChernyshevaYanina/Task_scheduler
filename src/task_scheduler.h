#ifndef TASK_SCHEDULER_SRC_TASK_SCHEDULER_H_
#define TASK_SCHEDULER_SRC_TASK_SCHEDULER_H_

#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

class TaskScheduler {
 private:
  std::mutex mtx;
  std::vector<std::thread> threads;

 public:
  ~TaskScheduler();

  void Add(std::function<void()> task, std::time_t timestamp);
};

#endif  // TASK_SCHEDULER_SRC_TASK_SCHEDULER_H_