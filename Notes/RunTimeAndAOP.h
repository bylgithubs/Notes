//
//  RunTimeAndAOP.h
//  Notes
//
//  Created by Civet on 2020/8/25.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef RunTimeAndAOP_h
#define RunTimeAndAOP_h


#endif /* RunTimeAndAOP_h */

#import "ViewController.h"
#import "Person.h"
#import <Aspects/Aspects.h> //需导入第三方库 pod 'Aspects', '~> 1.4.1'
#import <objc/runtime.h>

typedef void (^AspectHandlerBlock)(id<AspectInfo> aspectInfo);

@interface ViewController ()


@property (strong, nonatomic) IBOutlet UIButton *button;
@property(nonatomic,strong) Person *person;
@property(nonatomic,strong) AspectHandlerBlock block;

@end

@implementation ViewController

+(void)load{
    [[self class] swizzleMethod:@selector(addObject:) withMethod:@selector(safeAddObject:)];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    //    SEL methodId = @selector(run2:param:);
    //    NSString *methodName = NSStringFromSelector(methodId);
    //    NSLog(@"==============");
    self.person = [[Person alloc] init];
    [self performSelector:@selector(foo)];
    self.block = ^(id<AspectInfo> aspectInfo) {
        NSLog(@"this is aspectInfo block, aspectInfo ======= %@",aspectInfo);
    };
    [self aspect_hookSelector:@selector(actionBtn:) withOptions:AspectPositionInstead usingBlock:^(id<AspectInfo> aspectInfo){
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            self.block(aspectInfo);
        });
    } error:nil];
    [self addObject:nil];
    [self getPropertyListData];
}

+ (BOOL)resolveInstanceMethod:(SEL)sel {
    //    if (sel == @selector(foo:)) {//如果是执行foo函数，就动态解析，指定新的IMP
    //        class_addMethod([self class], sel, (IMP)fooMethod, "v@:");
    //        return YES;
    //    }
    //    return [super resolveInstanceMethod:sel];
    return YES;//返回YES，进入下一步转发
}

- (id)forwardingTargetForSelector:(SEL)aSelector {
    //    if (aSelector == @selector(foo)) {
    //        return [Person new];//返回Person对象，让Person对象接收这个消息
    //    }
    //
    //    return [super forwardingTargetForSelector:aSelector];
    return nil;//返回nil，进入下一步转发
}

/*
NSStringFromSelector() 将SEL对象转为NSString对象
 SEL sel=@selector(compare:);
 NSString *functionName= NSStringFromSelector(sel);
 
 NSSelectorFromString() Cocoa提供NSSelectorFromString,利用OC动态特性是通过String来生成Selectors,NSSelectorFromString动态加载实例方法
 SEL anotherSel=NSSelectorFromString(functionName);
 */
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector {
    if ([NSStringFromSelector(aSelector) isEqualToString:@"foo"]) {
        //v表示返回值为void，@表示该方法接受一个 id 和一个 SEL 。其实每个 Objective-C 方法都把 id 和 SEL 作为头2个参数。最后一个字符 * 表示该方法的一个显式的参数是一个字符串（char *）
        return [NSMethodSignature signatureWithObjCTypes:"v@:*"];//签名，进入forwardInvocation
    }
    
    return [super methodSignatureForSelector:aSelector];
}

- (void)forwardInvocation:(NSInvocation *)anInvocation {
    SEL sel = anInvocation.selector;
    
    //Person *p = [Person new];
    if([self.person respondsToSelector:sel]) {
        [anInvocation invokeWithTarget:self.person];
    }
    else {
        [self doesNotRecognizeSelector:sel];
    }
    
}

- (IBAction)actionBtn:(id)sender {
    NSLog(@"this is action");
}

- (void)addObject:(id)anObject{
    [self addObject:anObject];
}

- (void)safeAddObject:(id)anObject{
    if (anObject) {
        [self safeAddObject:anObject];
    } else {
        NSLog(@"object is nil");
    }
}

//swizzling method方法实现交换
+ (void)swizzleMethod:(SEL)origSelector withMethod:(SEL)newSelector{
    Class class = [self class];
    Method orignalMethod = class_getInstanceMethod(class, origSelector);
    Method swizzleMethod = class_getInstanceMethod(class, newSelector);
    //判断是否插入新的方法实现成功
    BOOL isAddSuccess = class_addMethod(class, origSelector, method_getImplementation(swizzleMethod), method_getTypeEncoding(swizzleMethod));
    //成功则将原方法实现插入新的方法实现，失败则原方法和新方法相互插入对方的方法实现
    if (isAddSuccess) {
        class_replaceMethod(class, newSelector, method_getImplementation(orignalMethod), method_getTypeEncoding(orignalMethod));
    } else {
        method_exchangeImplementations(orignalMethod, swizzleMethod);
    }
}

//从plist文件中读取数据
- (void)getPropertyListData{
    NSString *path = [[NSBundle mainBundle] pathForResource:@"data" ofType:@"plist"];
    NSDictionary *dataDic = [[NSDictionary alloc] initWithContentsOfFile:path];
    NSLog(@"dataDic====%@",dataDic);
}

@end
