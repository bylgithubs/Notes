//
//  MethodSignature.h
//  Notes
//
//  Created by Civet on 2020/11/2.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef MethodSignature_h
#define MethodSignature_h


#endif /* MethodSignature_h */

TestClass.m
- (void)sendMessage:(id)str para1:(id)str1 para2:(id)str2 para3:(id)str3 para4:(id)str4{  //v40@0:8@16@24@32
    NSLog(@"TestClass==============%@",[NSThread currentThread]);
}


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    NSLog(@"1----------------%@",[NSThread currentThread]);

    [self performSelector:@selector(sendMessage:para1:para2:para3:para4:) withObject:nil];

    NSLog(@"运行成功……");
    NSLog(@"6----------------%@",[NSThread currentThread]);
}

+ (BOOL)resolveInstanceMethod:(SEL)sel{
    NSLog(@"2----------------%@",[NSThread currentThread]);
    return NO;
}

- (id)forwardingTargetForSelector:(SEL)aSelector{
    NSLog(@"3----------------%@",[NSThread currentThread]);
    return [super forwardingTargetForSelector:aSelector];
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector{
    NSLog(@"4----------------%@",[NSThread currentThread]);
//    NSMethodSignature *signature = [TestClass instanceMethodSignatureForSelector:@selector(sendMessage:para1:para2:)];
    //第一个字符 v 表明返回值是void类型，第二个字符 @：表明该方法接收一个id和一个SEL，每个Object-C方法都把id和SEL作为头两个参数，
    //@16@24@32@40@48:表示第3、4、5、6、7个参数。
    return [NSMethodSignature signatureWithObjCTypes:"v56@0:8@16@24@32@40@48"]; //设置方法签名，确定参数数量，7个参数
    //return signature;
}

- (void)forwardInvocation:(NSInvocation *)anInvocation{
    NSLog(@"5----------------%@",[NSThread currentThread]);
//    SEL sel1 = @selector(sendMessage:para1:para2:);
//    Method signM = class_getInstanceMethod([TestClass class], sel1);
//    const char *s = method_getTypeEncoding(signM);
    SEL sel = anInvocation.selector;
    TestClass *test = [[TestClass alloc] init];
    if ([test respondsToSelector:sel]) {
        //两个以上自定义参数必须手动设置参数值，并且需要和方法签名中的参数数量一致，否则会报错。
        NSString *str1 = [NSString stringWithFormat:@"1"];
        NSString *str2 = @"bb";
        NSString *str3 = @"cc";
        NSString *str4 = @"dd";
        NSString *str5 = @"ee";
        [anInvocation setArgument:&str1 atIndex:2];
        [anInvocation setArgument:&str2 atIndex:3];
        [anInvocation setArgument:&str3 atIndex:4];
        [anInvocation setArgument:&str4 atIndex:5];
        [anInvocation setArgument:&str5 atIndex:6];
        [anInvocation invokeWithTarget:test];
    }
    //[self doesNotRecognizeSelector:anInvocation.selector];
}
