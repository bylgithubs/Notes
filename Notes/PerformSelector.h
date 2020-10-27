//
//  PerformSelector.h
//  Notes
//
//  Created by Civet on 2020/10/14.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef PerformSelector_h
#define PerformSelector_h


#endif /* PerformSelector_h */

- (void)performSelectorTest{
    dispatch_async(dispatch_queue_create("test", DISPATCH_QUEUE_SERIAL), ^{
        
        [self performSelector:@selector(run1) withObject:self afterDelay:1];
        [[NSRunLoop currentRunLoop] run];
        //[self performSelector:@selector(run1) withObject:nil];
        //[self performSelector:@selector(run1) withObject:nil withObject:nil];
    });
}

- (void)run1{
    NSLog(@"==============RUN====%@",[NSThread currentThread]);
}

个人总结：
1.perfomSelector:withObject:afterDelay:在子线程中，如果没有启动runloop将不会执行@selector中的方法，
因为perfomSelector:withObject:afterDelay其实是在内部创建了一个NSTimer，然后添加到当前的runloop中，
而子线程中runloop需要手动启动，并且需要保证runloop中有事件才能正常启动，所有需要先将NSTimer添加进runloop中，再执行run方法启动runloop;
2.performSelector:withObject:和performSelector:withObject:withObject:只是一个单纯的消息发送，和时间没有一点关系，
因此不需要添加到子线程的runloop中也能执行；

 [self performSelectorInBackground:@selector(test) withObject:nil]; //开启新的线程在后台执行test方法

[self performSelector:@selector(test) onThread:[NSThread currentThread] withObject:nil waitUntilDone:YES]; //thread参数是指定执行的线程
dispatch_async(dispatch_get_global_queue(0, 0), ^{
    [self performSelectorOnMainThread:@selector(test) withObject:nil waitUntilDone:NO]; //在子线程访问主线程
});

dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    [self performSelector:@selector(tests) onThread:[NSThread currentThread] withObject:nil waitUntilDone:NO];
    [[NSRunLoop currentRunLoop] run]; //source1事件，需要启动runloop
});
