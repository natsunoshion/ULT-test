#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

#define STACK_SIZE 1024 * 64

ucontext_t main_context, fiber_context;
char fiber_stack[STACK_SIZE];

// 模拟纤程的函数
void fiber_function() {
  printf("纤程开始执行，即将 sleep 2 秒...\n");
  sleep(2); // 在纤程中 sleep
  printf("纤程完完成 sleep。\n");

  // 切换回主上下文
  setcontext(&main_context);
}

int main() {
  // 初始化纤程上下文
  getcontext(&fiber_context);
  fiber_context.uc_link = 0;
  fiber_context.uc_stack.ss_sp = fiber_stack;
  fiber_context.uc_stack.ss_size = sizeof(fiber_stack);
  makecontext(&fiber_context, fiber_function, 0);

  // 保存当前上下文（主上下文），并切换到纤程
  printf("主线程即将切换到协程...\n");
  swapcontext(&main_context, &fiber_context);

  // 在主线程中执行 sleep
  printf("回到主线程，开始执行 sleep 1 秒...\n");
  sleep(1);
  printf("主线程完成 sleep。\n");

  return 0;
}
