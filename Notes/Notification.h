//
//  Notification.h
//  Notes
//
//  Created by Civet on 2020/10/27.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef Notification_h
#define Notification_h


#endif /* Notification_h */

//注册通知，在iOS 9.0之后，通知不需要手动移除，当对象释放时，会自动先移除该对象的通知，再释放对象；iOS 9.0之前需要手动释放通知，
//当对象已经释放，而通知没有手动释放，给一个已经释放的对象发送注册的通知，会导致程序崩溃。
//方式一
//该方式注册和发送通知，接收通知的线程和发送通知的线程一致
[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(run) name:@"test" object:nil];

//方式二
/*该方式可以在注册通知时指定通知接收的线程，当queue的参数为[NSOperationQueue currentQueue]时，接收通知的线程和发送通知的线程一致，和方式一一样；
当queue的参数为[NSOperationQueue mainQueue]时，无论发送通知的是哪个线程，通知都是在主线程接收。
 */
dispatch_queue_t queue = dispatch_queue_create("test", DISPATCH_QUEUE_CONCURRENT);
dispatch_async(queue, ^{
    NSNotification *observer = [[NSNotificationCenter defaultCenter] addObserverForName:@"test" object:nil queue:[NSOperationQueue currentQueue] usingBlock:^(NSNotification * _Nonnull note) {
        NSLog(@"==========%@",[NSThread currentThread]);
    }];
});

//发送通知
dispatch_async(dispatch_get_global_queue(0, 0), ^{
    NSLog(@"sendThread==========%@",[NSThread currentThread]);
    [[NSNotificationCenter defaultCenter] postNotificationName:@"test" object:nil];
});
-----------------------------------------------------------------------------------------------------------------------------------

//注册通知
[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sendNotificationMessage) name:@"test" object:nil];

//接收通知后触发方法
- (void)sendNotificationMessage{
    NSLog(@"2============%@",[NSThread currentThread]);
}

//发送通知
//方式一
dispatch_async(dispatch_get_global_queue(0, 0), ^{
    NSLog(@"1========sendNotification========%@",[NSThread currentThread]);
    NSRunLoop *runloop = [NSRunLoop currentRunLoop];
    [runloop addPort:[NSPort port] forMode:NSDefaultRunLoopMode];
    NSNotification *notification = [NSNotification notificationWithName:@"test" object:nil];
    [[NSNotificationQueue defaultQueue] enqueueNotification:notification postingStyle:NSPostNow coalesceMask:NSNotificationNoCoalescing forModes:@[NSDefaultRunLoopMode]];
    NSLog(@"3========sendNotification========%@",[NSThread currentThread]);
    [runloop run];  //开启runloop循环，相当于do……while循环，下面的代码不会执行
    NSLog(@"4========sendNotification========%@",[NSThread currentThread]); //不会执行
});
2020-10-27 09:31:19.490559+0800 test3[1498:62486] 1========sendNotification========<NSThread: 0x600003021dc0>{number = 6, name = (null)}
2020-10-27 09:31:19.490970+0800 test3[1498:62486] 2============<NSThread: 0x600003021dc0>{number = 6, name = (null)}
2020-10-27 09:31:19.491099+0800 test3[1498:62486] 3========sendNotification========<NSThread: 0x600003021dc0>{number = 6, name = (null)}

//方式二
dispatch_async(dispatch_get_global_queue(0, 0), ^{
    NSLog(@"1========sendNotification========%@",[NSThread currentThread]);
    NSRunLoop *runloop = [NSRunLoop currentRunLoop];
    [runloop addPort:[NSPort port] forMode:NSDefaultRunLoopMode];
    NSNotification *notification = [NSNotification notificationWithName:@"test" object:nil];
    [[NSNotificationQueue defaultQueue] enqueueNotification:notification postingStyle:NSPostNow coalesceMask:NSNotificationNoCoalescing forModes:@[NSDefaultRunLoopMode]];
    NSLog(@"3========sendNotification========%@",[NSThread currentThread]);
    [runloop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:3]]; //3秒后结束runloop循环，执行下面的代码
    NSLog(@"4========sendNotification========%@",[NSThread currentThread]); //3秒后可以执行
});
2020-10-27 09:31:19.490559+0800 test3[1498:62486] 1========sendNotification========<NSThread: 0x600003021dc0>{number = 6, name = (null)}
2020-10-27 09:31:19.490970+0800 test3[1498:62486] 2============<NSThread: 0x600003021dc0>{number = 6, name = (null)}
2020-10-27 09:31:19.491099+0800 test3[1498:62486] 3========sendNotification========<NSThread: 0x600003021dc0>{number = 6, name = (null)}
2020-10-27 09:31:22.491857+0800 test3[1498:62486] 4========sendNotification========<NSThread: 0x600003021dc0>{number = 6, name = (null)}

postringStyle参数就是定义通知调用和runloop状态之间关系。
该参数的三个可选参数：
1，NSPostWhenIdle：runloop空闲的时候回调通知方法,通知回调方法是等待到当下线程runloop进入等待状态才会调用,即runloop将要进入休眠时调用。
2，NSPostASAP：runloop能够调用的时候就回调通知方法,通知回调方法是等待到当下线程runloop开始接收事件源的时候就会调用。
3，NSPostNow：runloop立即回调通知方法，和一般通知方法相同。
其他情况：
在主线程按方式二（没有添加runloop）发送通知，正常执行；在子线程按方式二发送通知，没有添加runloop，NSPostNow可以正常进行回调，和一般通知一样；
NSPostWhenIdle和NSPostASAP在子线程下无法进行方法回调，需要将通知加入子线程的runloop中，并手动启动runloop。

