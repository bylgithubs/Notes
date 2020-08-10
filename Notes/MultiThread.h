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
/*
 
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

 总结：当一个并行队列中含有同步和异步两种任务时，同步任务按照并行队列中的顺序执行，异步任务可以开辟子线程，执行顺序改变。
 
 */
