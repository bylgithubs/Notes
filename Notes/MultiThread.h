//
//  MultiThread.h
//  Notes
//
//  Created by Civet on 2020/8/10.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef MultiThread_h
#define MultiThread_h


#endif /* MultiThread_h */

同步执行（sync）：
同步添加任务到指定的队列中，在添加的任务执行结束之前，会一直等待，直到队列里面的任务完成之后再继续执行。
只能在当前线程中执行任务，不具备开启新线程的能力。
异步执行（async）：
异步添加任务到指定的队列中，它不会做任何等待，可以继续执行任务。
可以在新的线程中执行任务，具备开启新线程的能力。

串行队列（Serial Dispatch Queue）：
每次只有一个任务被执行。让任务一个接着一个地执行。（只开启一个线程，一个任务执行完毕后，再执行下一个任务）
并发队列（Concurrent Dispatch Queue）：
可以让多个任务并发（同时）执行。（可以开启多个线程，并且同时执行任务）
注意：并发队列 的并发功能只有在异步（dispatch_async）方法下才有效。

-----------------------------------------------------------------------------------------------------------------------------
 dispatch_queue_t queue = dispatch_queue_create("test", DISPATCH_QUEUE_CONCURRENT);
 
 for (int i = 0; i < 10; i++) {
 dispatch_async(queue, ^{
 NSLog(@"======================1------%@------",[NSThread currentThread]);
 
 });
 dispatch_async(queue, ^{
 NSLog(@"======================2------%@-----",[NSThread currentThread]);
 });
 dispatch_sync(queue, ^{
 NSLog(@"======================3==%@",[NSThread currentThread]);
 });
 dispatch_sync(queue, ^{
 NSLog(@"======================4==%@",[NSThread currentThread]);
 });
 dispatch_sync(queue, ^{
 NSLog(@"======================5==%@",[NSThread currentThread]);
 });
 dispatch_async(queue, ^{
 NSLog(@"======================6-----%@------",[NSThread currentThread]);
 });
 dispatch_sync(queue, ^{
 NSLog(@"======================7==%@",[NSThread currentThread]);
 });
 dispatch_sync(queue, ^{
 NSLog(@"======================8==%@",[NSThread currentThread]);
 });
 dispatch_sync(queue, ^{
 NSLog(@"======================9==%@",[NSThread currentThread]);
 });
 //        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0 *NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
 //            NSLog(@"==============================================");
 //        });
 NSLog(@"=========================================================================");
 
 2020-08-10 15:30:24.945720+0800 test6[10127:217838] ======================1------<NSThread: 0x600003b78e80>{number = 3, name = (null)}------
 2020-08-10 15:30:24.945724+0800 test6[10127:217839] ======================2------<NSThread: 0x600003b58980>{number = 4, name = (null)}-----
 2020-08-10 15:30:24.945716+0800 test6[10127:217615] ======================3==<NSThread: 0x600003b3a940>{number = 1, name = main}
 2020-08-10 15:30:24.945887+0800 test6[10127:217615] ======================4==<NSThread: 0x600003b3a940>{number = 1, name = main}
 2020-08-10 15:30:24.945978+0800 test6[10127:217615] ======================5==<NSThread: 0x600003b3a940>{number = 1, name = main}
 2020-08-10 15:30:24.946084+0800 test6[10127:217615] ======================7==<NSThread: 0x600003b3a940>{number = 1, name = main}
 2020-08-10 15:30:24.946093+0800 test6[10127:217839] ======================6-----<NSThread: 0x600003b58980>{number = 4, name = (null)}------
 2020-08-10 15:30:24.946178+0800 test6[10127:217615] ======================8==<NSThread: 0x600003b3a940>{number = 1, name = main}
 2020-08-10 15:30:24.946314+0800 test6[10127:217615] ======================9==<NSThread: 0x600003b3a940>{number = 1, name = main}
 2020-08-10 15:30:24.946486+0800 test6[10127:217615] =========================================================================

 个人总结：当一个并行队列中含有同步和异步两种任务时，同步任务按照并行队列中的顺序执行，异步任务可以开辟子线程，执行顺序改变。
-----------------------------------------------------------------------------------------------------------------------------
     for (int i = 0; i < 100; i++) {
         dispatch_queue_t serialQueue = dispatch_queue_create("test2", DISPATCH_QUEUE_SERIAL);
         NSLog(@"0=======%d========%@",i,[NSThread currentThread]);
         dispatch_async(serialQueue, ^{
             [NSThread sleepForTimeInterval:5];
             NSLog(@"A0=======%d========%@",i,[NSThread currentThread]);
         });
         dispatch_async(serialQueue, ^{
             //[NSThread sleepForTimeInterval:5];
             NSLog(@"A00=======%d========%@",i,[NSThread currentThread]);
         });
         dispatch_sync(serialQueue, ^{
             //[NSThread sleepForTimeInterval:1];
             NSLog(@"A=======%d========%@",i,[NSThread currentThread]);
         });
         dispatch_async(serialQueue, ^{
             [NSThread sleepForTimeInterval:2];
             NSLog(@"A1=======%d========%@",i,[NSThread currentThread]);
         });
         dispatch_async(serialQueue, ^{
             //[NSThread sleepForTimeInterval:25];
             NSLog(@"B=======%d========%@",i,[NSThread currentThread]);
         });
         dispatch_async(serialQueue, ^{
             //[NSThread sleepForTimeInterval:1];
             NSLog(@"B1=======%d========%@",i,[NSThread currentThread]);
         });
         dispatch_async(serialQueue, ^{
             //[NSThread sleepForTimeInterval:1];
             NSLog(@"B2=======%d========%@",i,[NSThread currentThread]);
         });
         NSLog(@"C=======%d========%@",i,[NSThread currentThread]);
         [NSThread sleepForTimeInterval:5];
         NSLog(@"C1=======%d========%@",i,[NSThread currentThread]);
         dispatch_sync(serialQueue, ^{
             NSLog(@"D=======%d========%@",i,[NSThread currentThread]);
         });
         NSLog(@"E=======%d========%@",i,[NSThread currentThread]);
         [NSThread sleepForTimeInterval:3];
         NSLog(@"=====================%d=================================================================",i);
     }
     
     2020-10-16 10:34:43.367805+0800 test3[3535:96166] 0=======5========<NSThread: 0x60000284c980>{number = 1, name = main}
     2020-10-16 10:34:48.368278+0800 test3[3535:96299] A0=======5========<NSThread: 0x6000028079c0>{number = 3, name = (null)}
     2020-10-16 10:34:48.368458+0800 test3[3535:96299] A00=======5========<NSThread: 0x6000028079c0>{number = 3, name = (null)}
     2020-10-16 10:34:48.368568+0800 test3[3535:96166] A=======5========<NSThread: 0x60000284c980>{number = 1, name = main}
     2020-10-16 10:34:48.368684+0800 test3[3535:96166] C=======5========<NSThread: 0x60000284c980>{number = 1, name = main}
     2020-10-16 10:34:50.371096+0800 test3[3535:96299] A1=======5========<NSThread: 0x6000028079c0>{number = 3, name = (null)}
     2020-10-16 10:34:50.371308+0800 test3[3535:96299] B=======5========<NSThread: 0x6000028079c0>{number = 3, name = (null)}
     2020-10-16 10:34:50.371419+0800 test3[3535:96299] B1=======5========<NSThread: 0x6000028079c0>{number = 3, name = (null)}
     2020-10-16 10:34:50.371528+0800 test3[3535:96299] B2=======5========<NSThread: 0x6000028079c0>{number = 3, name = (null)}
     2020-10-16 10:34:53.370063+0800 test3[3535:96166] C1=======5========<NSThread: 0x60000284c980>{number = 1, name = main}
     2020-10-16 10:34:53.370292+0800 test3[3535:96166] D=======5========<NSThread: 0x60000284c980>{number = 1, name = main}
     2020-10-16 10:34:53.370373+0800 test3[3535:96166] E=======5========<NSThread: 0x60000284c980>{number = 1, name = main}
     2020-10-16 10:34:56.371690+0800 test3[3535:96166] =====================5=================================================================
     
个人总结：当一个串行队列中包含同步和异步两种任务时,同步任务在主线程执行，异步任务会开辟一个子线程，在新开辟的子线程中执行。
前提条件：串行队列
1.如果当前在执行dispatch_sync中的任务，会一直执行dispatch_sync类型的任务，直到遇到dispatch_async后，切换执行dispatch_async类型的任务；
2.如果当前在执行dispatch_async中的任务，会一直执行dispatch_async类型的任务，直到遇到dispatch_sync后，切换执行dispatch_async类型的任务;
3.如果当前在执行dispatch_sync中的任务，在遇到下个不连续dispatch_sync时，两个dispatch_sync之间的非CGD代码按顺序执行，不会受dispatch_async代码影响，
因为非GCD代码未加入到该串行队列中。
结论：同步任务会“阻塞”当前线程，执行完当前同步任务才会继续执行下面的代码，异步任务不会“阻塞”当前线程，可以继续执行之后的代码。
注意：主队列其实并不特殊。所有放在主队列中的任务，都会放到主线程中执行。主队列专门负责在主线程上调度任务，不会在子线程上调度任务，在主队列不允许开辟新线程。
     主队列的实质上就是一个普通的串行队列，只是因为默认情况下，当前代码是放在主队列中的，然后主队列中的代码，有都会放到主线程中去执行，所以才造成了主队列特殊的现象。
     所以，主队列中有同步任务会锁死，异步任务不会创建子线程，仍然在主线程执行。
注意： 『主线程』 中调用 『主队列』+『同步执行』 会导致死锁问题。
     这是因为 主队列中追加的同步任务 和 主线程本身的任务 两者之间相互等待，阻塞了 『主队列』，最终造成了主队列所在的线程（主线程）死锁问题。
     而如果我们在 『其他线程』 调用 『主队列』+『同步执行』，则不会阻塞 『主队列』，自然也不会造成死锁问题。最终的结果是：不会开启新线程，串行执行任务。
-----------------------------------------------------------------------------------------------------------------------------
     dispatch_queue_t serialQueue = dispatch_queue_create("test2", DISPATCH_QUEUE_SERIAL);
     dispatch_async(serialQueue, ^{
         [NSThread sleepForTimeInterval:5];
         NSLog(@"A=======%d========%@",i,[NSThread currentThread]);
     });
     dispatch_sync(serialQueue, ^{
         NSLog(@"B=======%d========%@",i,[NSThread currentThread]);
     });
     NSLog(@"C=====================%d================================%@\n\n\n\n\n\n",i,[NSThread currentThread]);
     
     2020-10-16 11:47:39.536694+0800 test3[4681:134724] A=======60========<NSThread: 0x6000014be900>{number = 5, name = (null)}
     2020-10-16 11:47:39.536898+0800 test3[4681:134654] B=======60========<NSThread: 0x6000014e6980>{number = 1, name = main}
     2020-10-16 11:47:39.537013+0800 test3[4681:134654] C=====================60================================<NSThread: 0x6000014e6980>{number = 1, name = main}     //顺序执行
-----------------------------------------------------------------------------------------------------------------------------
     dispatch_queue_t serialQueue = dispatch_queue_create("test2", DISPATCH_QUEUE_SERIAL);
     dispatch_sync(serialQueue, ^{
         NSLog(@"A=======%d========%@",i,[NSThread currentThread]);
     });
     dispatch_async(serialQueue, ^{
         //[NSThread sleepForTimeInterval:1];
         NSLog(@"B=======%d========%@",i,[NSThread currentThread]);
     });
     //[NSThread sleepForTimeInterval:1];
     NSLog(@"C=====================%d================================%@\n\n\n\n\n\n",i,[NSThread currentThread]);
     
     AC执行顺序固定，A在BC之前，BC顺序按任务时间确定
-----------------------------------------------------------------------------------------------------------------------------
实现线程异步：
     //创建线程
     NSThread *thread = [[NSThread alloc] initWithTarget:self selector:@selector(run2) object:nil];
     //启动线程
     [thread start];
     //以下两个方法创建并自动启动线程，在子线程中运行
     [NSThread detachNewThreadSelector:@selector(run1) toTarget:self withObject:nil];
     [NSThread detachNewThreadWithBlock:^{
         NSLog(@"run====================newThread---%@",[NSThread currentThread]);
     }];
-----------------------------------------------------------------------------------------------------------------------------
     
dispatch_barrier_sync 和 dispatch_barrier_async的区别
dispatch_barrier_sync: Submits a barrier block object for execution and waits until that block completes.(提交一个栅栏函数在执行中,它会等待栅栏函数执行完)
 
dispatch_barrier_async: Submits a barrier block for asynchronous execution and returns immediately.(提交一个栅栏函数在异步执行中,它会立马返回)
    dispatch_barrier_sync 需要等待栅栏执行完才会执行栅栏后面的任务,而dispatch_barrier_async 无需等待栅栏执行完,会继续往下走(保留在队列里)
    原因:在同步栅栏时栅栏函数在主线程中执行,而异步栅栏中开辟了子线程栅栏函数在子线程中执行
注意:不能使用全局并发队列(系统提供给我们的)否则会散失栅栏函数的意义
The queue you specify should be a concurrent queue that you create yourself using the dispatch_queue_create function. If the queue you pass to this function is a serial queue or one of the global concurrent queues, this function behaves like the dispatch_sync function.
 
官方说明大意:在使用栅栏函数时.使用自定义队列才有意义,如果用的是串行队列或者系统提供的全局并发队列,这个栅栏函数的作用等同于一个同步函数的作用
-----------------------------------------------------------------------------------------------------------------------------
 dispatch_after(dispatch_time(DISPATCH_TIME_NOW,(int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
     NSLog(@"========%@",[NSThread currentThread]);
 });
 注意：dispatch_after 方法并不是在指定时间之后才开始执行处理，而是在指定时间之后将任务追加到主队列中。严格来说，这个时间并不是绝对准确的，
 但想要大致延迟执行任务，dispatch_after 方法是很有效的。
---------------------------------------------------------------------------------------------------------------
 //执行一次，线程安全
static dispatch_once_t onceToken;
dispatch_once(&onceToken, ^{
    NSLog(@"execution with once, multiThread is security");
});
---------------------------------------------------------------------------------------------------------------
dispatch_apply
 dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
 NSLog(@"apply---begin");
 dispatch_apply(9, queue, ^(size_t index) {
     NSLog(@"%zd---%@",index, [NSThread currentThread]);
 });
 NSLog(@"apply---end");
 串行队列，和for循环一样，按顺序执行，并发队列，不会按顺序执行，当是apply---end一定会在循环之后，diapatch_apply会等待全部任务执行完毕。
 
 ---------------------------------------------------------------------------------------------------------------
dispatch_group_notify
 dispatch_group_t group = dispatch_group_create();
 dispatch_group_async(group, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0),^{
     NSLog(@"任务一");
 });
 dispatch_group_async(group, dispatch_get_global_queue(0, 0), ^{
     NSLog(@"任务二");
 });
 dispatch_group_notify(group, dispatch_get_main_queue(), ^{
     NSLog(@"任务完成");
 });
 ---------------------------------------------------------------------------------------------------------------
 dispatch_group_wait
 dispatch_group_t group = dispatch_group_create();
 dispatch_group_async(group, dispatch_get_global_queue(0, 0), ^{
     NSLog(@"任务一");
 });
 dispatch_group_async(group, dispatch_get_global_queue(0, 0), ^{
     NSLog(@"任务二");
 });
 dispatch_group_wait(group, DISPATCH_TIME_FOREVER); //阻塞当前线程
 NSLog(@"任务三");
     
 dispatch_barrier_async 不会阻塞当前线程，如果在 dispatch_barrier_async 之后有代码，还会接着执行。 dispatch_group_wait
     
---------------------------------------------------------------------------------------------------------------
 dispatch_group_t group = dispatch_group_create();
 dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
 dispatch_group_enter(group);    //追加任务，未执行完毕任务数 +1；
 dispatch_async(queue, ^{
     NSLog(@"追加任务1");
     dispatch_group_leave(group);    //未执行完毕任务数 -1;
 });
 dispatch_group_enter(group);    //追加任务，未执行完毕任务数 +1；
 dispatch_async(queue, ^{
     NSLog(@"追加任务2");
     dispatch_group_leave(group);    //未执行完毕任务数 -1;
 });
 dispatch_group_notify(group, dispatch_get_main_queue(), ^{
     NSLog(@"以上任务执行完毕，回到主线程");
 });
     
---------------------------------------------------------------------------------------------------------------
 dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
 dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
 dispatch_async(queue, ^{
     NSLog(@"执行任务……");
     dispatch_semaphore_signal(semaphore);   //发送信号，信号量+1
 });
 dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);  //信号量-1，信号量小于0，线程阻塞，等待信号量不小于0，唤醒线程。
 1.semaphore 初始创建时计数为 0。
 2.异步执行 将 任务 1 追加到队列之后，不做等待，接着执行 dispatch_semaphore_wait 方法，semaphore 减 1，此时 semaphore == -1，当前线程进入等待状态。
 3.然后，异步任务 1 开始执行。任务 1 执行到 dispatch_semaphore_signal 之后，总信号量加 1，此时 semaphore == 0，正在被阻塞的线程（主线程）恢复继续执行。
 4.最后打印 semaphore---end,number = 100。
 这样就实现了线程同步，将异步执行任务转换为同步执行任务。

---------------------------------------------------------------------------------------------------------------------------------
信号量加锁
 
 @property(nonatomic,strong) dispatch_semaphore_t semaphoreLock;
 @property(nonatomic,assign) int ticketSurplusCount;
 
 semaphoreLock = dispatch_semaphore_create(1);
 
 self.ticketSurplusCount = 50;
 // queue1 代表北京火车票售卖窗口
 dispatch_queue_t queue1 = dispatch_queue_create("queue1", DISPATCH_QUEUE_SERIAL);
 // queue2 代表上海火车票售卖窗口
 dispatch_queue_t queue2 = dispatch_queue_create("queue2", DISPATCH_QUEUE_SERIAL);
 
 __weak typeof(self) weakSelf = self;
 dispatch_async(queue1, ^{
     [weakSelf saleTicketSafe];
 });
 
 dispatch_async(queue2, ^{
     [weakSelf saleTicketSafe];
 });
 
 - (void)saleTicketSafe {
     while (1) {
         // 相当于加锁
         dispatch_semaphore_wait(semaphoreLock, DISPATCH_TIME_FOREVER);
         
         if (self.ticketSurplusCount > 0) {  // 如果还有票，继续售卖
             self.ticketSurplusCount--;
             NSLog(@"%@", [NSString stringWithFormat:@"剩余票数：%d 窗口：%@", self.ticketSurplusCount, [NSThread currentThread]]);
             [NSThread sleepForTimeInterval:0.2];
         } else { // 如果已卖完，关闭售票窗口
             NSLog(@"所有火车票均已售完");
             
             // 相当于解锁
             dispatch_semaphore_signal(semaphoreLock);
             break;
         }
         
         // 相当于解锁
         dispatch_semaphore_signal(semaphoreLock);
     }
 }
     
---------------------------------------------------------------------------------------------------------------------------------
 dispatch_queue_t queue1 = dispatch_queue_create("queue1", DISPATCH_QUEUE_SERIAL);
 dispatch_queue_t queue2 = dispatch_queue_create("queue1", DISPATCH_QUEUE_SERIAL);
 dispatch_queue_t queue3 = dispatch_queue_create("queue1", DISPATCH_QUEUE_CONCURRENT);
 dispatch_async(queue3, ^{
     NSLog(@"1===========%@",[NSThread currentThread]);
     dispatch_async(queue1, ^{
         NSLog(@"2===========%@",[NSThread currentThread]);
         dispatch_async(queue3, ^{
             NSLog(@"3===========%@",[NSThread currentThread]);
         });
     });
 });
 
 2020-10-20 17:09:26.101727+0800 test3[12346:282821] 1===========<NSThread: 0x600002741300>{number = 6, name = (null)}
 2020-10-20 17:09:26.101939+0800 test3[12346:282821] 2===========<NSThread: 0x600002741300>{number = 6, name = (null)}
 2020-10-20 17:09:26.102082+0800 test3[12346:282818] 3===========<NSThread: 0x600002741540>{number = 7, name = (null)}
 
 主队列其实并没什么特殊的，就是一个普通的串行队列。
 1、同步操作时，在同一个串行队列中对当前队列sync操作都会导致死锁，
 2、异步操作时，如果在当前队列async，并不会开启新线程；在其他队列当中再对该串行队列进行asyn操作会开启新线程
     
 ---------------------------------------------------------------------------------------------------------------------------------
NSOperationQueue *queue = [[NSOperationQueue alloc] init];
[queue setMaxConcurrentOperationCount:3];       //当最大并发数为1时，串行执行任务，为-1或其他大于1的情况直接并发执行任务。
NSInvocationOperation *operation1 = [[NSInvocationOperation alloc] initWithTarget:self selector:@selector(run) object:nil];
[operation1 setCompletionBlock:^{
    NSLog(@"=====completionBlock1");
}];
[queue addOperation:operation1];    //添加到队列为多线程异步操作，如果直接使用start启动NSInvocationOperation,则没有创建新的线程，在当前线程执行任务。
NSBlockOperation *operation2 = [NSBlockOperation blockOperationWithBlock:^{
    NSLog(@"======blockOpeartion2");;
}];
[operation2 setCompletionBlock:^{
 [NSThread sleepForTimeInterval:1];
    NSLog(@"=====completionBlock2");
}];
[queue addOperation:operation2];            //同NSInvocationOperation一样
[NSThread sleepForTimeInterval:3];

NSOperationQueue *operationQueue = [NSOperationQueue mainQueue];    //主队列
NSBlockOperation *blockOperation1 = [NSBlockOperation blockOperationWithBlock:^{
    NSLog(@"blockOperation1");
}];
NSInvocationOperation *invocationOperation1 = [[NSInvocationOperation alloc] initWithTarget:self selector:@selector(run) object:nil];
[invocationOperation1 addDependency:blockOperation1];    //添加依赖，先执行blockOperation1,在执行invocationOperation1
[operationQueue addOperation:blockOperation1];
[operationQueue addOperation:invocationOperation1];
 
[operationQueue cancelAllOperations];   //取消队列中的所有任务，不可恢复
[operationQueue setSuspended:YES];  //暂停队列中的所有任务
[operationQueue setSuspended:NO];   //恢复队列中的所有任务
 ---------------------------------------------------------------------------------------------------------------------------------
 NSBlockOperation *blockOperation = [NSBlockOperation blockOperationWithBlock:^{
     NSLog(@"1================%@",[NSThread currentThread]);
 }];
 [blockOperation addExecutionBlock:^{
     NSLog(@"2================%@",[NSThread currentThread]);
 }];
 [blockOperation addExecutionBlock:^{
     //sleep(3);
     NSLog(@"3================%@",[NSThread currentThread]);
 }];
 [blockOperation addExecutionBlock:^{
     NSLog(@"4================%@",[NSThread currentThread]);
 }];
 [blockOperation start];
 
 2020-10-23 08:48:36.087197+0800 test3[1193:35834] 4================<NSThread: 0x6000005d22c0>{number = 5, name = (null)}
 2020-10-23 08:48:36.087197+0800 test3[1193:35691] 1================<NSThread: 0x6000005dc400>{number = 1, name = main}
 2020-10-23 08:48:36.087197+0800 test3[1193:35833] 3================<NSThread: 0x600000587100>{number = 8, name = (null)}
 2020-10-23 08:48:36.087197+0800 test3[1193:35835] 2================<NSThread: 0x600000590ac0>{number = 4, name = (null)}
 
 个人总结：addExecutionBlock可以加入任务到子线程，blockOperationWithBlock仍然在主线程执行
 ---------------------------------------------------------------------------------------------------------------------------------
 NSOperationQueue *queue = [[NSOperationQueue alloc] init];
 [queue addOperationWithBlock:^{
     NSLog(@"在子线程执行任务");
 }];
 ---------------------------------------------------------------------------------------------------------------------------------
 //退出线程
 [NSThread exit];
 //判断当前线程是否为主线程
 [NSThread isMainThread];
 //判断当前线程是否是多线程
 [NSThread isMultiThreaded];
 //主线程的对象
 NSThread *mainThread = [NSThread mainThread];
 //线程是否在执行
 thread.isExecuting;
 //线程是否被取消
 thread.isCancelled;
 //线程是否完成
 thread.isFinished;
 //是否是主线程
 thread.isMainThread;
 //线程的优先级，取值范围0.0到1.0，默认优先级0.5，1.0表示最高优先级，优先级高，CPU调度的频率高
  thread.threadPriority;
 ---------------------------------------------------------------------------------------------------------------------------------

