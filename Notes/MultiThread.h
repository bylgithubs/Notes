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
注意：主队列其实并不特殊。所有放在主队列中的任务，都会放到主线程中执行。 主队列的实质上就是一个普通的串行队列，只是因为默认情况下，当前代码是放在主队列中的，然后主队列中的代码，有都会放到主线程中去执行，所以才造成了主队列特殊的现象。
所以，主队列中有同步任务会锁死，异步任务不会创建子线程，仍然在主线程执行。
注意： 『主线程』 中调用 『主队列』+『同步执行』 会导致死锁问题。
     这是因为 主队列中追加的同步任务 和 主线程本身的任务 两者之间相互等待，阻塞了 『主队列』，最终造成了主队列所在的线程（主线程）死锁问题。
     而如果我们在 『其他线程』 调用 『主队列』+『同步执行』，则不会阻塞 『主队列』，自然也不会造成死锁问题。最终的结果是：不会开启新线程，串行执行任务。
     
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

