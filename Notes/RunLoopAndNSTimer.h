//
//  RunLoopAndNSTimer.h
//  Notes
//
//  Created by Civet on 2020/10/8.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef RunLoopAndNSTimer_h
#define RunLoopAndNSTimer_h


#endif /* RunLoopAndNSTimer_h */

//主线程下，NSTimer可以自动加入runloop下运行
[NSTimer scheduledTimerWithTimeInterval:2.0 target:self selector:@selector(run) userInfo:nil repeats:YES];
//等同于
NSTimer *timer = [NSTimer timerWithTimeInterval:2.0 target:self selector:@selector(run) userInfo:nil repeats:YES];
[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];

//子线程下，NSTimer需要手动添加到runloop下，并手动启动runloop，NSTimer才能运行，添加和启动顺序不能错
dispatch_async(dispatch_get_global_queue(0, 0), ^{
    //同上
    NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval:2.0 target:self selector:@selector(run) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop] run];
});

- (void)run{
    NSLog(@"timer is runing");
}


//GCD创建定时器
dispatch_queue_t queue = dispatch_get_main_queue();
dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
dispatch_source_set_timer(timer, DISPATCH_TIME_NOW, 1.0 * NSEC_PER_SEC, 0 * NSEC_PER_SEC);
dispatch_source_set_event_handler(timer, ^{
    NSLog(@"==========%@",[NSThread currentThread]);
});
dispatch_resume(timer);
