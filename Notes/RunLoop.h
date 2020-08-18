//
//  RunLoop.h
//  Notes
//
//  Created by Civet on 2020/8/18.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef RunLoop_h
#define RunLoop_h


#endif /* RunLoop_h */

@property (nonatomic, strong) NSThread *thread;

/*
//设置常驻线程
//创建线程，并调用run1方法执行任务
self.thread = [[NSThread alloc] initWithTarget:self selector:@selector(run1) object:nil];
//开启线程
[self.thread start];

- (void)run1{
    //开启RunLoop，之后self.thread变成常驻线程，可随时添加任务，并交于RunLoop处理
    [[NSRunLoop currentRunLoop] addPort:[NSPort port] forModel:NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop] run];
    
    // 测试是否开启了RunLoop，如果开启RunLoop，则来不了这里，因为RunLoop开启了循环。
    NSLog(@"未开启RunLoop");
}

- (void)run1{
    NSLog(@"----run2------");
}

//往常驻线程添加任务
- (void)touchesBegan:(NSSet<uitouch *> *)touches withEvent:(UIEvent *)event{
    //利用performSelector,在self.thread的线程中调用run2方法执行任务
    [self performSelector:@selector(run2) onThread:self.thread withObject:nil waitUntilDone:NO];
}

- (void)run2{
    NSLog(@"----run2------");
}
 
 */
