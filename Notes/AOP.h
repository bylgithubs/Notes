//
//  AOP.h
//  Notes
//
//  Created by Civet on 2020/10/9.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef AOP_h
#define AOP_h


#endif /* AOP_h */

typedef void(^proxyBlock)(id target,SEL selector);

NS_ASSUME_NONNULL_BEGIN

@interface AOPProxy : NSProxy
+(instancetype)proxyWithTarget:(id)target;
-(void)inspectSelector:(SEL)selector preSelTask:(proxyBlock)preTask endSelTask:(proxyBlock)endTask;
@end

@implementation AOPProxy

-(void)inspect{
    NSMutableArray *targtArray = [AOPProxy proxyWithTarget:[NSMutableArray arrayWithCapacity:1]];
    [(AOPProxy *)targtArray inspectSelector:@selector(addObject:) preSelTask:^(id target, SEL selector) {
        [target addObject:@"-------"];
        NSLog(@"%@我加进来之前",target);
    } endSelTask:^(id target, SEL selector) {
        [target addObject:@"-------"];
        NSLog(@"%@我加进来之后",target);
    }];
    [targtArray addObject:@"我是一个元素"];
}

2018-12-28 11:57:05.590 NSProxyStudy[23812:4840464] (
                                                     "-------"
                                                     )我加进来之前
2018-12-28 11:57:05.591 NSProxyStudy[23812:4840464] (
                                                     "-------",
                                                     "\U6211\U662f\U4e00\U4e2a\U5143\U7d20",
                                                     "-------"
                                                     )我加进来之后

@end
