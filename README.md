# 测试结果

可以看见：

- 切换到纤程时，纤程发起syscall，主程序阻塞，等待纤程返回时才继续执行；
- 切换到协程时，协程的syscall没有阻塞主程序的继续执行。

![image](https://github.com/natsunoshion/ULT-test/assets/100564236/a0fa1232-105a-4092-90a3-22369fb827b0)
