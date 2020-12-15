//
//  LazyLoading.h
//  Notes
//
//  Created by Civet on 2020/7/20.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef LazyLoading_h
#define LazyLoading_h


#endif /* LazyLoading_h */

 这里列举了四种线程延时加载的方法,
 1.performSelector方法 此方法必须在主线程中执行,并不是阻塞当前的线程
 [self performSelector:@selector(delayMethod) withObject:nil afterDelay:1.0f];
 2.定时器:NSTimer,也必须在主线程中加载,是一种非阻塞的执行方式
 [NSTimer scheduledTimerWithTimeInterval:1.0f target:self selector:@selector(delayMethod) userInfo:nil repeats:NO];
 3.    sleep方式此方式在主线程和子线程中均可执行。 是一种阻塞的执行方式，建议放到子线程中，以免卡住界面
 [NSThread sleepForTimeInterval:1.0f]; [self delayMethod];
 4.GCD方式此方式在可以在参数中选择执行的线程。是一种非阻塞的执行方式
 //delayInSeconds 延迟的时间
 dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
 
 });

