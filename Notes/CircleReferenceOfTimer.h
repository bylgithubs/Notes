//
//  CircleReferenceOfTimer.h
//  Notes
//
//  Created by Civet on 2020/8/14.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef CircleReferenceOfTimer_h
#define CircleReferenceOfTimer_h


#endif /* CircleReferenceOfTimer_h */

//在MRC下，当target为self时，self.timer和target中的self会造成循环引用，可以使用代理方式创建虚假对象，
//在通过forwardingTargetForSelector:方法重定向sel，进行事件触发
self.timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:[MJProxy proxyWithTarget:self] selector:@selector(timerTest) userInfo:nil repeats:YES];

- (void) timerTest{
    NSLog(@"%s",__func__);
}

@interface MJProxy()
@property (weak, nonatomic) id target;
@end
@implementation MJProxy

+ (instancetype)proxyWithTarget: (id)target{
    MJProxy *proxy = [[MJProxy alloc] init];
    proxy.target = target;
    return proxy;
}
//消息重定向，当前类的实例对象未实现@selector中的方法时，触发下列方法，转发到self.target中查找是否实现@selector中的方法
-(id)forwardingTargetForSelector:(SEL)aSelector{
    return self.target;
}
