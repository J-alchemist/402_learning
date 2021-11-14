test33: fcntl文件锁-->进程间同步
test32: 进程间互斥锁实现同步（修改线程锁的属性为进程可用）
test31: 信号量sem实现，生产者消费者模型
test30: 条件变量cond实现，生产者消费者模型（依赖于互斥锁）
test29: 读写锁rwlock
test28: 互斥锁mutex
test27: pthread_detach线程分离,pthread_cancel杀死线程，pthread_testcancel定义取消点配合杀死线程
test26: pthread_join获取线程pthread_exit退出状态值
test25: pthread_create创建线程，pthread_self获取线程id，pthread_exit退出线程
//-------------------------------------
test24: 创建守护进程
test23: 会话
test22: 进程组
test21: 信号父子进程通信，全局变量异步IO
test20: sigsuspend挂起当前进程（且为原子操作）
test19: pause挂起当前进程，时序竞态
test18: sigaction信号捕捉,比signal函数更优秀
test17: 信号集操作
test16: signal函数，注册信号触发函数，信号捕捉
test15: setitimer定时发送SIGLARM信号，终止程序
test14: alarm函数定时发送SIGLARM信号终止程序，time ./test14 > xfile
test13: kill给指定进程发送信号（不一定是杀死信号），raise发送信号，abort直接终止程序
test12：mmap匿名映射
test11：mmap哪些共享，哪些不共享
test10：ftruncate设置文件大小、mmap共享内存映射(lseek也可以做)
test9： pipe进程间通信-管道
test8： wait、waitpid删除多个子进程
test7： wait删除子进程，并反馈信息
test6： dup2文件描述符、execlp输出信息到文件
test5： execlp、execl子进程执行其他功能
test4： fork循环创建多个子进程
test3： fork创建一个子进程
//-------------------------------------
test2-1：stat获取文件信息
test2： lseek文件指针重定向
test1： open、read、write、close
