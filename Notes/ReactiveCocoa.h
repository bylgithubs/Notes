//
//  ReactiveCocoa.h
//  Notes
//
//  Created by Civet on 2020/11/28.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef ReactiveCocoa_h
#define ReactiveCocoa_h


#endif /* ReactiveCocoa_h */
导入ReactiveCocoa
source 'https://github.com/CocoaPods/Specs.git'
pod 'ReactiveCocoa', '~> 2.5'   //方案一
pod 'ReactiveObjC', '~> 3.1.1'  //方案二 推荐


#import <RACEXTScope.h> //方案一
#import <ReactiveObjC/ReactiveObjC.h> //方案二 推荐
@weakify(self1,self2,……)最大20个参数
@strongify(self1,self2,……)同上

{
    int _result;
}
BOOL isResult = [[self caculator:^int(int result) {
    result += 2;
    result *= 10;
    return result;
}] equal:^BOOL(int result) {
    return result == 10;
}];
NSLog(@"%d",isResult);

- (ViewController *)caculator:(int(^)(int result))caculator{
    _result = caculator(0);
    return self;
}

- (BOOL)equal:(BOOL(^)(int result))operation{

    return operation(_result);
}

---------------------------------------------------------------------------------------------------------------
信号 => 订阅 响应式编程思想，只要信号已发生改变，就会通知订阅
RACSignal:信号，ReactiveCocoa最基本类
RACDisposable:处理数据,清空数据
- (void)RACSignalTest{
    //创建信号 1
    RACSignal *signal = [RACSignal createSignal:^RACDisposable *(id<RACSubscriber> subscriber) {
        //发送信号  3
        [subscriber sendNext:@"text"];
        // 如果不在发送数据，最好发送信号完成，内部会自动调用[RACDisposable disposable]取消订阅信号。
        [subscriber sendCompleted];
        //销毁信号 5
        return [RACDisposable disposableWithBlock:^{
            // 当订阅者被销毁的时候就会执行
            // 订阅发送完成或者error,也会执行Block
            // 清空数据
            //6
            NSLog(@"默认信号发送完毕");
        }];
    }];

    //订阅信号 2
    [signal subscribeNext:^(id  _Nullable x) {
        //接收内容 4
        NSLog(@"%@",x);
    } error:^(NSError * _Nullable error) {
        NSLog(@"%@",error);
    } completed:^{
        NSLog(@"订阅完成");
    }];
    
}
---------------------------------------------------------------------------------------------------------------
//多个订阅者
- (void)RACSubjectTest{
    // 先订阅 在发送信号
    // 创建信号
    RACSubject *subject = [RACSubject subject];
    // 订阅
    // 内部创建RACSubscriber，并且保存起来
    // RACSubscriber保存nextBlock
    [subject subscribeNext:^(id  _Nullable x) {
        NSLog(@"第一个订阅者:%@", x);
    }];
    [subject subscribeNext:^(id  _Nullable x) {
        NSLog(@"第二个订阅者:%@", x);
    }];
    
    //发送信号，便利所有的订阅者
    [subject sendNext:@5];
    [subject sendNext:@8];
}

2020-11-30 16:23:43.467731+0800 Test[8053:239834] 第一个订阅者:5
2020-11-30 16:23:59.436063+0800 Test[8053:239834] 第二个订阅者:5
2020-11-30 16:24:01.146817+0800 Test[8053:239834] 第一个订阅者:8
2020-11-30 16:24:10.235987+0800 Test[8053:239834] 第二个订阅者:8
---------------------------------------------------------------------------------------------------------------
//先发信号，在订阅
- (void)RACReplaySubjectTest{
    RACReplaySubject *replaySubject = [RACReplaySubject subject];
    // 发送信息
    // 先保存信息
    // 在执行nextBlock
    [replaySubject sendNext:@"hello"];
    [replaySubject sendNext:@"Come"];
    
    // 订阅信号
    // 遍历值，让一个订阅者去发送多个值
    // 只要订阅一次，之前所有发送的值都能获取到.
    [replaySubject subscribeNext:^(id  _Nullable x) {
        NSLog(@"%@", x);
    }];
    // 多个值一个类可以拿到
    // 一个类想拿多个值，采用RACReplaySubject
    // RACReplaySubject价值 ：先发送，在订阅
}

2020-11-30 16:33:29.668813+0800 Test[8118:244186] hello
2020-11-30 16:33:31.301500+0800 Test[8118:244186] Come
---------------------------------------------------------------------------------------------------------------
//字典转模型
- (void)dictToModel
{
//    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"Info" ofType:@"plist"];
//    NSDictionary *dic = [NSDictionary dictionaryWithContentsOfFile:filePath];
    NSDictionary *dic = @{@"1":@"one",@"2":@"two"};
    // 字典转模型
    NSMutableArray *mutArr = [NSMutableArray array];
    
    //1. 简单便利
    [dic.rac_sequence.signal subscribeNext:^(id  _Nullable x)
     {
        NSLog(@"%@", [NSThread currentThread]);
        
        NSLog(@"%@", x);
    }];
    
    //2. 更新UI，执行完成之后操作
    [dic.rac_sequence.signal subscribeNext:^(id  _Nullable x)
     {
//        Item *item = [Item itemWithDict:x];
//        [mutArr addObject:item];
        NSLog(@"%@", x);
        
    } completed:^
     {   // 不管使用谁的框架,一定要记得确认线程,UI界面不显示,可能线程问题
        NSLog(@"%@", [NSThread currentThread]);
    }];
    
    // 字典转模型
    //3.  map:映射
    // mapBlock: value参数:集合  返回值:需要映射成那个值
    //映射完成生成新的模型数组
    NSArray *flags = [[dic.rac_sequence map:^id(id value) {
     
        return self;
        
    }] array];
}
---------------------------------------------------------------------------------------------------------------
//遍历字典
- (void)dicTest{
    NSDictionary *dic = @{
        @"name":@"老王",
        @"age":@"18",
        @"height":@"198.0"
    };
    [dic.rac_sequence.signal subscribeNext:^(id  _Nullable x) {
        //RAC有个宏可以 把快速元组解析出来
        //x的第0个元素是key，1个是代表值
        RACTupleUnpack(NSString *key,id value) = x;
        NSLog(@"key = %@ ,v = %@",key, value);
        NSLog(@"%@", x[1]);
    }];
}
---------------------------------------------------------------------------------------------------------------
// 需求:
// 1.给当前控制器添加一个按钮，modal到另一个控制器界面
// 2.另一个控制器view中有个按钮，点击按钮，通知当前控制器
    
步骤一：在第二个控制器.h，添加一个RACSubject代替代理。
@interface TwoViewController : UIViewController

@property (nonatomic, strong) RACSubject *delegateSignal;

@end

步骤二：监听第二个控制器按钮点击
@implementation TwoViewController
- (IBAction)notice:(id)sender {
    // 通知第一个控制器，告诉它，按钮被点了
    
     // 通知代理
     // 判断代理信号是否有值
    if (self.delegateSignal) {
        // 有值，才需要通知
        [self.delegateSignal sendNext:nil];
    }
}
@end

步骤三：在第一个控制器中，监听跳转按钮，给第二个控制器的代理信号赋值，并且监听.
@implementation OneViewController
- (IBAction)btnClick:(id)sender {
    
    // 创建第二个控制器
    TwoViewController *twoVc = [[TwoViewController alloc] init];
    
    // 设置代理信号
    twoVc.delegateSignal = [RACSubject subject];
    
    // 订阅代理信号
    [twoVc.delegateSignal subscribeNext:^(id x) {
       
        NSLog(@"点击了通知按钮");
    }];
    
    // 跳转到第二个控制器
    [self presentViewController:twoVc animated:YES completion:nil];
    
}
@end
---------------------------------------------------------------------------------------------------------------
// 1.遍历数组
NSArray *numbers = @[@1,@2,@3,@4];

// 这里其实是三步
// 第一步: 把数组转换成集合RACSequence numbers.rac_sequence
// 第二步: 把集合RACSequence转换RACSignal信号类,numbers.rac_sequence.signal
// 第三步: 订阅信号，激活信号，会自动把集合中的所有值，遍历出来。
[numbers.rac_sequence.signal subscribeNext:^(id x) {
    
    NSLog(@"%@",x);
}];


// 2.遍历字典,遍历出来的键值对会包装成RACTuple(元组对象)
NSDictionary *dict = @{@"name":@"xmg",@"age":@18};
[dict.rac_sequence.signal subscribeNext:^(RACTuple *x) {
    
    // 解包元组，会把元组的值，按顺序给参数里面的变量赋值
    RACTupleUnpack(NSString *key,NSString *value) = x;
    
    // 相当于以下写法
    //        NSString *key = x[0];
    //        NSString *value = x[1];
    
    NSLog(@"%@ %@",key,value);
    
}];


// 3.字典转模型
// 3.1 OC写法
NSString *filePath = [[NSBundle mainBundle] pathForResource:@"flags.plist" ofType:nil];

NSArray *dictArr = [NSArray arrayWithContentsOfFile:filePath];

NSMutableArray *items = [NSMutableArray array];

for (NSDictionary *dict in dictArr) {
    FlagItem *item = [FlagItem flagWithDict:dict];
    [items addObject:item];
}

// 3.2 RAC写法
NSString *filePath = [[NSBundle mainBundle] pathForResource:@"flags.plist" ofType:nil];

NSArray *dictArr = [NSArray arrayWithContentsOfFile:filePath];

NSMutableArray *flags = [NSMutableArray array];

_flags = flags;

// rac_sequence注意点：调用subscribeNext，并不会马上执行nextBlock，而是会等一会。
[dictArr.rac_sequence.signal subscribeNext:^(id x) {
    // 运用RAC遍历字典，x：字典
    
    FlagItem *item = [FlagItem flagWithDict:x];
    
    [flags addObject:item];
    
}];

NSLog(@"%@",  NSStringFromCGRect([UIScreen mainScreen].bounds));


// 3.3 RAC高级写法:
NSString *filePath = [[NSBundle mainBundle] pathForResource:@"flags.plist" ofType:nil];

NSArray *dictArr = [NSArray arrayWithContentsOfFile:filePath];
// map:映射的意思，目的：把原始值value映射成一个新值
// array: 把集合转换成数组
// 底层实现：当信号被订阅，会遍历集合中的原始值，映射成新值，并且保存到新的数组里。
NSArray *flags = [[dictArr.rac_sequence map:^id(id value) {
    
    return [FlagItem flagWithDict:value];
    
}] array];
---------------------------------------------------------------------------------------------------------------
- (void)RACCommandTest{
    
    // 一、RACCommand使用步骤:
    // 1.创建命令 initWithSignalBlock:(RACSignal * (^)(id input))signalBlock
    // 2.在signalBlock中，创建RACSignal，并且作为signalBlock的返回值
    // 3.执行命令 - (RACSignal *)execute:(id)input
    
    // 二、RACCommand使用注意:
    // 1.signalBlock必须要返回一个信号，不能传nil.
    // 2.如果不想要传递信号，直接创建空的信号[RACSignal empty];
    // 3.RACCommand中信号如果数据传递完，必须调用[subscriber sendCompleted]，这时命令才会执行完毕，否则永远处于执行中。
    // 4.RACCommand需要被强引用，否则接收不到RACCommand中的信号，因此RACCommand中的信号是延迟发送的。
    
    // 三、RACCommand设计思想：内部signalBlock为什么要返回一个信号，这个信号有什么用。
    // 1.在RAC开发中，通常会把网络请求封装到RACCommand，直接执行某个RACCommand就能发送请求。
    // 2.当RACCommand内部请求到数据的时候，需要把请求的数据传递给外界，这时候就需要通过signalBlock返回的信号传递了。
    
    // 四、如何拿到RACCommand中返回信号发出的数据。
    // 1.RACCommand有个执行信号源executionSignals，这个是signal of signals(信号的信号),意思是信号发出的数据是信号，不是普通的类型。
    // 2.订阅executionSignals就能拿到RACCommand中返回的信号，然后订阅signalBlock返回的信号，就能获取发出的值。
    
    // 五、监听当前命令是否正在执行executing
    
    // 六、使用场景,监听按钮点击，网络请求
    
    
    // 1.创建命令
    RACCommand *command = [[RACCommand alloc] initWithSignalBlock:^RACSignal *(id input) {
        
        NSLog(@"执行命令");
        
        // 创建空信号,必须返回信号
        //        return [RACSignal empty];
        
        // 2.创建信号,用来传递数据
        return [RACSignal createSignal:^RACDisposable *(id<RACSubscriber> subscriber) {
            
            [subscriber sendNext:@"请求数据"];
            
            // 注意：数据传递完，最好调用sendCompleted，这时命令才执行完毕。
            [subscriber sendCompleted];
            
            return nil;
        }];
        
    }];
    
    // 强引用命令，不要被销毁，否则接收不到数据
    _command = command;
    
    
    
    // 3.订阅RACCommand中的信号
    [command.executionSignals subscribeNext:^(id x) {
        
        [x subscribeNext:^(id x) {
            
            NSLog(@"%@",x);
        }];
        
    }];
    
    // RAC高级用法
    // switchToLatest:用于signal of signals，获取signal of signals发出的最新信号,也就是可以直接拿到RACCommand中的信号
    [command.executionSignals.switchToLatest subscribeNext:^(id x) {
        
        NSLog(@"%@",x);
    }];
    
    // 4.监听命令是否执行完毕,默认会来一次，可以直接跳过，skip表示跳过第一次信号。
    [[command.executing skip:1] subscribeNext:^(id x) {
        
        if ([x boolValue] == YES) {
            // 正在执行
            NSLog(@"正在执行");
            
        }else{
            // 执行完成
            NSLog(@"执行完成");
        }
        
    }];
    // 5.执行命令
    [self.command execute:@1];
}
---------------------------------------------------------------------------------------------------------------
- (void)RACMulticastConnection{
    // RACMulticastConnection使用步骤:
    // 1.创建信号 + (RACSignal *)createSignal:(RACDisposable * (^)(id<RACSubscriber> subscriber))didSubscribe
    // 2.创建连接 RACMulticastConnection *connect = [signal publish];
    // 3.订阅信号,注意：订阅的不在是之前的信号，而是连接的信号。 [connect.signal subscribeNext:nextBlock]
    // 4.连接 [connect connect]
    
    // RACMulticastConnection底层原理:
    // 1.创建connect，connect.sourceSignal -> RACSignal(原始信号)  connect.signal -> RACSubject
    // 2.订阅connect.signal，会调用RACSubject的subscribeNext，创建订阅者，而且把订阅者保存起来，不会执行block。
    // 3.[connect connect]内部会订阅RACSignal(原始信号)，并且订阅者是RACSubject
    // 3.1.订阅原始信号，就会调用原始信号中的didSubscribe
    // 3.2 didSubscribe，拿到订阅者调用sendNext，其实是调用RACSubject的sendNext
    // 4.RACSubject的sendNext,会遍历RACSubject所有订阅者发送信号。
    // 4.1 因为刚刚第二步，都是在订阅RACSubject，因此会拿到第二步所有的订阅者，调用他们的nextBlock
    
    
    // 需求：假设在一个信号中发送请求，每次订阅一次都会发送请求，这样就会导致多次请求。
    // 解决：使用RACMulticastConnection就能解决.
    
    // 1.创建请求信号
    RACSignal *signal = [RACSignal createSignal:^RACDisposable *(id<RACSubscriber> subscriber) {
        NSLog(@"发送请求");
        return nil;
    }];
    // 2.订阅信号
    [signal subscribeNext:^(id x) {
        
        NSLog(@"接收数据");
        
    }];
    // 2.订阅信号
    [signal subscribeNext:^(id x) {
        
        NSLog(@"接收数据");
        
    }];
    
    // 3.运行结果，会执行两遍发送请求，也就是每次订阅都会发送一次请求
    
    // RACMulticastConnection:解决重复请求问题
    // 1.创建信号
    RACSignal *signal1 = [RACSignal createSignal:^RACDisposable *(id<RACSubscriber> subscriber) {
        
        
        NSLog(@"发送请求");
        [subscriber sendNext:@1];
        
        return nil;
    }];
    
    // 2.创建连接
    RACMulticastConnection *connect = [signal1 publish];
    
    // 3.订阅信号，
    // 注意：订阅信号，也不能激活信号，只是保存订阅者到数组，必须通过连接,当调用连接，就会一次性调用所有订阅者的sendNext:
    [connect.signal subscribeNext:^(id x) {
        
        NSLog(@"订阅者一信号");
        
    }];
    
    [connect.signal subscribeNext:^(id x) {
        
        NSLog(@"订阅者二信号");
        
    }];
    
    // 4.连接,激活信号
    [connect connect];
    
}
---------------------------------------------------------------------------------------------------------------
1.rac_signalForSelector：用于替代代理。
2.rac_valuesAndChangesForKeyPath：用于监听某个对象的属性改变。
3.rac_signalForControlEvents：用于监听某个事件。
4.rac_addObserverForName:用于监听某个通知。
5.rac_textSignal:只要文本框发出改变就会发出这个信号。
6.rac_liftSelector:withSignalsFromArray:Signals:当传入的Signals(信号数组)，每一个signal都至少sendNext过一次，就会去触发第一个selector参数的方法。
使用注意：几个信号，参数一的方法就几个参数，每个参数对应信号发出的数据。

- (void)RACBaseMethod{
    UIView *redV = [[UIView alloc] initWithFrame:self.view.frame];
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
    UITextField *textField = [[UITextField alloc] initWithFrame:CGRectMake(100, 100, 100, 30)];
    // 1.代替代理
     // 需求：自定义redView,监听红色view中按钮点击
     // 之前都是需要通过代理监听，给红色View添加一个代理属性，点击按钮的时候，通知代理做事情
     // rac_signalForSelector:把调用某个对象的方法的信息转换成信号，就要调用这个方法，就会发送信号。
     // 这里表示只要redV调用btnClick:,就会发出信号，订阅就好了。
     [[redV rac_signalForSelector:@selector(btnClick:)] subscribeNext:^(id x) {
         NSLog(@"点击红色按钮");
     }];

     // 2.KVO
     // 把监听redV的center属性改变转换成信号，只要值改变就会发送信号
     // observer:可以传入nil
     [[redV rac_valuesAndChangesForKeyPath:@"center" options:NSKeyValueObservingOptionNew observer:nil] subscribeNext:^(id x) {

         NSLog(@"%@",x);

     }];

     // 3.监听事件
     // 把按钮点击事件转换为信号，点击按钮，就会发送信号
     [[btn rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(id x) {

         NSLog(@"按钮被点击了");
     }];

     // 4.代替通知
     // 把监听到的通知转换信号
     [[[NSNotificationCenter defaultCenter] rac_addObserverForName:UIKeyboardWillShowNotification object:nil] subscribeNext:^(id x) {
         NSLog(@"键盘弹出");
     }];

     // 5.监听文本框的文字改变
    [textField.rac_textSignal subscribeNext:^(id x) {

        NSLog(@"文字改变了%@",x);
    }];
    
    // 6.处理多个请求，都返回结果的时候，统一做处理.
     RACSignal *request1 = [RACSignal createSignal:^RACDisposable *(id<RACSubscriber> subscriber) {
         
         // 发送请求1
         [subscriber sendNext:@"发送请求1"];
         return nil;
     }];
     
     RACSignal *request2 = [RACSignal createSignal:^RACDisposable *(id<RACSubscriber> subscriber) {
         // 发送请求2
         [subscriber sendNext:@"发送请求2"];
         return nil;
     }];
     
     // 使用注意：几个信号，参数一的方法就几个参数，每个参数对应信号发出的数据。
     [self rac_liftSelector:@selector(updateUIWithR1:r2:) withSignalsFromArray:@[request1,request2]];

}

// 更新UI
- (void)updateUIWithR1:(id)data r2:(id)data1
{
    NSLog(@"更新UI%@  %@",data,data1);
}
---------------------------------------------------------------------------------------------------------------
ReactiveCocoa常见宏:

1.RAC(TARGET, [KEYPATH, [NIL_VALUE]]):用于给某个对象的某个属性绑定。

// 只要文本框文字改变，就会修改label的文字
RAC(self.labelView,text) = _textField.rac_textSignal;

2.RACObserve(self, name):监听某个对象的某个属性,返回的是信号。

[RACObserve(self.view, center) subscribeNext:^(id x) {
    
    NSLog(@"%@",x);
}];

3.@weakify(Obj)和@strongify(Obj),一般两个都是配套使用,在主头文件(ReactiveCocoa.h)中并没有导入，需要自己手动导入，RACEXTScope.h才可以使用。但是每次导入都非常麻烦，只需要在主头文件自己导入就好了。

4 RACTuplePack：把数据包装成RACTuple（元组类）

// 把参数中的数据包装成元组
RACTuple *tuple = RACTuplePack(@10,@20);
5 RACTupleUnpack：把RACTuple（元组类）解包成对应的数据。


// 把参数中的数据包装成元组
RACTuple *tuple = RACTuplePack(@"xmg",@20);

// 解包元组，会把元组的值，按顺序给参数里面的变量赋值
// name = @"xmg" age = @20
RACTupleUnpack(NSString *name,NSNumber *age) = tuple;
---------------------------------------------------------------------------------------------------------------

