#include <chrono>
#include <coroutine>
#include <iostream>
#include <thread>
#include <unistd.h>

struct SleepAwaitable {
  unsigned int duration;

  bool await_ready() const noexcept { return duration == 0; }
  void await_suspend(std::coroutine_handle<>) const {
    std::thread([this] {
      std::cout << "协程sleep开始" << std::endl;
      sleep(duration);
      std::cout << "协程sleep结束" << std::endl;
    }).detach();
  }
  void await_resume() const noexcept {}
};

struct AsyncTask {
  struct promise_type {
    AsyncTask get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};

AsyncTask async_task() {
  std::cout << "协程任务开始" << std::endl;
  co_await SleepAwaitable{3}; // 等待3秒
  std::cout << "协程任务结束" << std::endl;
}

int main() {
  auto task = async_task();

  // 在主线程中执行其他操作
  for (int i = 0; i < 5; ++i) {
    std::cout << "主程序执行中，这是第" << i + 1 << "秒..." << std::endl;
    sleep(1);
  }
}
