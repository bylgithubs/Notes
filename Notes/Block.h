//
//  Block.h
//  Notes
//
//  Created by Civet on 2020/11/2.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef Block_h
#define Block_h


#endif /* Block_h */

Block：带有自动变量（局部变量）的匿名函数。它是C语言的扩充功能。之所以是拓展，是因为C语言不允许存在这样匿名函数。

1.写在方法里作为局部变量

returnType (^blockName)(parameterTypes) = ^returnType(parameters) {...};
returnType是返回值
blockName是block名称
parameterTypes是参数
2.作为类的属性

@property (nonatomic, copy) returnType (^blockName)(parameterTypes)
returnType是返回值
blockName是block名称
parameterTypes是参数
3.作为方法参数

- (void)someMethodThatTakesABlock:(returnType (^)(parameterTypes))blockName;
returnType是返回值
blockName是block名称
parameterTypes是参数
4.调用方法是传入的参数

[self someMethodThatTakesABlock:^returnType (parameters) {...}];
returnType是返回值
blockName是block名称
parameterTypes是参数
5.自定义Block类型

typedef returnType (^TypeName)(parameterTypes);
TypeName blockName = ^returnType(parameters) {...};
returnType是返回值
blockName是block名称
parameterTypes是参数
--------------------------------------------------------------------------------------------------------------------------
#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    void (^blk)(void) = ^{
        NSLog(@"hello");
    };
    blk();
    
    return 0;
}

clang -rewrite-objc -XXX.m
block C++代码：

struct __block_impl {
  void *isa;
  int Flags;
  int Reserved;
  void *FuncPtr;
};

//block结构体
struct __main_block_impl_0 {    //_0表示该函数内的第几个block，有_1
  struct __block_impl impl;
  struct __main_block_desc_0* Desc;
  __main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, int flags=0) {
    impl.isa = &_NSConcreteStackBlock;
    impl.Flags = flags;
    impl.FuncPtr = fp;
    Desc = desc;
  }
};

//block代码块中的实现
static void __main_block_func_0(struct __main_block_impl_0 *__cself) {

        NSLog((NSString *)&__NSConstantStringImpl__var_folders_7__3g67htjj4816xmx7ltbp2ntc0000gn_T_main_f871c6_mi_0);
    }

//block描述结构体
static struct __main_block_desc_0 {
  size_t reserved;
  size_t Block_size;
} __main_block_desc_0_DATA = { 0, sizeof(struct __main_block_impl_0)};

int main(int argc, const char * argv[]) {
//block实现
    void (*blk)(void) = ((void (*)())&__main_block_impl_0((void *)__main_block_func_0, &__main_block_desc_0_DATA));
//block调用
    ((void (*)(__block_impl *))((__block_impl *)blk)->FuncPtr)((__block_impl *)blk);

    return 0;
}
--------------------------------------------------------------------------------------------------------------------------
NSArray* (^TestBlock)(NSString*,NSString*,NSInteger) = ^NSArray*(NSString*str,NSString*str1,NSInteger i){
    NSArray *arr;
    return arr;
};
NSArray *arr1 = TestBlock(@"aa",@"bb",1);


__block int a = 0;
  int b = 1;
  NSLog(@"定义前外部：a：%p", &a);         //栈区
  NSLog(@"定义前外部：b：%p", &b);         //栈区
  void (^foo)(void) = ^{
      a = 1;
      //self->b = 2; //block内部可以修改全局变量
      NSLog(@"block内部：a：%p", &a);     //堆区
      NSLog(@"block内部：b：%p", &b);     //堆区
  };
  NSLog(@"定义后外部：a：%p", &a);         //堆区
  NSLog(@"定义后外部：b：%p", &b);         //栈区
  foo();
2020-11-02 15:38:27.314843+0800 test4[13002:244530] 定义前外部：a：0x7ffee699a0e8
2020-11-02 15:38:27.315022+0800 test4[13002:244530] 定义前外部：b：0x7ffee699a0cc
2020-11-02 15:38:27.315134+0800 test4[13002:244530] 定义后外部：a：0x6000026838d8
2020-11-02 15:38:27.315226+0800 test4[13002:244530] 定义后外部：b：0x7ffee699a0cc
2020-11-02 15:38:27.315327+0800 test4[13002:244530] block内部：a：0x6000026838d8
2020-11-02 15:38:27.315432+0800 test4[13002:244530] block内部：b：0x6000028fdf48

个人总结：block会将普通变量的指针复制一份到堆中使用，如果变量被__block修饰，栈上__block变量被复制到堆上后，
会将成员变量__forwarding指针从指向自己换成指向堆上的__block，而堆上__block的__forwarding才是指向自己,有点像把指针剪切到堆上。
_block不能修饰全局变量、静态变量


NSMutableString *a = [NSMutableString stringWithString:@"Tom"]; //1
void (^foo)(void) = ^{
    a.string = @"Jerry";    //2
    //a = [NSMutableString stringWithString:@"William"]; //编译报错 //3
};
foo();
NSLog(@"========%@",a);    //4

(lldb) p a  //1
(__NSCFString *) $0 = 0x0000600000d0b4e0 @"Tom"
(lldb) p &a
(NSMutableString **) $1 = 0x00007ffeee4c90e8
(lldb) p a  //2
(__NSCFString *) $2 = 0x0000600000d0b4e0 @"Tom"
(lldb) p &a
(NSMutableString **) $3 = 0x0000600000d0b9b0
(lldb) p a  //3
(__NSCFString *) $4 = 0x0000600000d0b4e0 @"Jerry"
(lldb) p &a
(NSMutableString **) $5 = 0x0000600000d0b9b0
(lldb) p a  //4
(__NSCFString *) $6 = 0x0000600000d0b4e0 @"Jerry"
(lldb) p &a
(NSMutableString **) $7 = 0x00007ffeee4c90e8

//效果同上
typedef void (^CYLBlock)(void);
NSMutableArray *array = [[NSMutableArray array] init];
CYLBlock block = ^{
    [array addObject: @"123"];
    //array = nil; //编译报错
};
block();
NSLog(@"===========%@",array);

个人推测：可变类型的变量，加载到block中，属于指针复制，将指针从栈中复制到堆中，浅复制，
在block中直接更改外部变量指针指向会编译报错，除非外部变量之前有__block关键字修饰，
a.string和[array addObject:@"aa"]方法直接对指针所指的内存区域的内容进行修改，所以不会报错。
-----------------------------------------------------------------------------------------------------------------------------
自动变量加入到block中是值复制，不能修改自动变量的值；
静态变量/__block变量加入到block中是指针复制，即地址传递，指针存储静态变量的地址，在block中对静态变量进行赋值，其实是修改静态变量内存地址所指的值，内存地址不变，值变；
-----------------------------------------------------------------------------------------------------------------------------
- (void)viewDidLoad{
__weak typeof(person) weakPerson = person;
[person configurePersonBlock:^ {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        NSLog(@"printf str:%@",weakPerson.name);
    });
}];
}

[person actionComplete];调用block之后，viewDidLoad方法作用域结束后，person对象被释放。由于dispatch_after的延迟执行，
在Block执行完成前，捕获的对象释放了，block捕获weakPerson变为nil

__weak typeof(person) weakPerson = person;
[person configurePersonBlock:^ {
    __strong typeof(weakPerson) strongPerson = weakPerson;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        NSLog(@"printf str:%@",strongPerson.name);
    });
}];
[person actionComplete];
-----------------------------------------------------------------------------------------------------------------------------
Person *person1 = [[Person alloc]init];
person1.name = @"commet";
person1.age = 18;

__block Person *blkPerson = person1;    //__block解决循环引用

[person1 configurePersonBlock:^{
    NSLog(@"%@",blkPerson.name);
    blkPerson = nil;
}];
person1.blk();  //必须执行一次才能解除循环引用
block在拷贝到堆上的时候，会retain其引用的外部变量，那么如果block中如果引用了他的宿主对象，比如self，那很有可能引起循环引用。
-----------------------------------------------------------------------------------------------------------------------------
void (^block)(void) = ^{
    NSLog(@"Hello");
};

NSLog(@"%@", [block class]);
NSLog(@"%@", [[block class] superclass]);
NSLog(@"%@", [[[block class] superclass] superclass]);
NSLog(@"%@", [[[[block class] superclass] superclass] superclass]);
NSLog(@"%@", [[[[[block class] superclass] superclass] superclass] superclass]);

2020-11-06 09:39:22.932173+0800 test4[1556:54724] __NSGlobalBlock__
2020-11-06 09:39:22.932386+0800 test4[1556:54724] __NSGlobalBlock
2020-11-06 09:39:22.932522+0800 test4[1556:54724] NSBlock
2020-11-06 09:39:22.932622+0800 test4[1556:54724] NSObject
2020-11-06 09:39:22.932710+0800 test4[1556:54724] (null)

block最终都是继承自NSBlock类型，而NSBlock继承于NSObjcet。那么block其中的isa指针其实是来自NSObject中的。这也更加印证了block的本质其实就是OC对象。

-----------------------------------------------------------------------------------------------------------------------------
// 1. 内部没有调用外部变量的block
 void (^block1)(void) = ^{
     NSLog(@"Hello");
 };
 // 2. 内部调用外部变量的block
 int a = 10;
 void (^block2)(void) = ^{
     NSLog(@"Hello - %d",a);
 };
// 3. 直接调用的block的class
 NSLog(@"%@ %@ %@", [block1 class], [block2 class], [^{
     NSLog(@"%d",a);
 } class]);

2020-11-06 09:43:25.123181+0800 test4[1584:56803] __NSGlobalBlock__ __NSMallocBlock__ __NSStackBlock__
-----------------------------------------------------------------------------------------------------------------------------
ARC下_NSConcreteStackBlock自动复制到堆中成为_NSConcreteMallocBlock情况：
1. block作为函数返回值时；
2. 将block赋值给__strong指针时；
3. block作为Cocoa API中方法名含有usingBlock的方法参数时；
NSArray *array = @[];
[array enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
}];
4. block作为GCD API的方法参数时;
GDC的一次性函数或延迟执行的函数，执行完block操作之后系统才会对block进行release操作
static dispatch_once_t onceToken;
dispatch_once(&onceToken, ^{
            
});
dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
});

栈上，__block结构体中的__forwarding指针指向自己，一旦复制到堆上，栈上的__block结构体中的__forwarding指针会指向堆上的__block结构体，
堆上__block结构体中的__forwarding还是指向自己。假设age是栈上的变量，age->__forwarding会拿到堆上的__block结构体，
age->__forwarding->age会把20赋值到堆上，不论是栈上还是堆上的__block结构体，都能保证20赋值到堆的结构体里
-----------------------------------------------------------------------------------------------------------------------------
传入按钮作为参赛的block
@property (nonatomic, copy) void (^btnClickedBlock)(UIButton *sender);

UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
self.btnClickedBlock = ^(UIButton *button){
    
};
self.btnClickedBlock(button);

匿名block
^{
    NSLog(@"匿名block自动调用");
}();
NSString *blockReturn = ^NSString*(NSString *str,NSInteger i){
    NSLog(@"带返回值和参赛的匿名block自动调用");
    return [NSString stringWithFormat:@"%@--%ld",str,i];
}(@"aa",1);
NSLog(@"block返回值为：%@",blockReturn);

2020-11-06 14:12:55.283689+0800 test4[2900:156311] 匿名block自动调用
2020-11-06 14:12:55.283851+0800 test4[2900:156311] 带返回值和参赛的匿名block自动调用
2020-11-06 14:12:55.283973+0800 test4[2900:156311] block返回值为：aa--1
-----------------------------------------------------------------------------------------------------------------------------
1.block之前定义对self的弱引用weakSelf,因为是弱引用，所以self被释放时weakSelf会变成nil
2.在block中引用该弱引用，考虑到多线程情况，通过强引用strongSelf来引用该弱引用，如果self不为nil，就会retain self，以防在block内部使用过程中self被释放
3.在block块中使用该强引用strongSelf，注意对strongSelf进行nil检测，因为多线程在弱引用weakSelf对强引用strongSelf赋值时，弱引用weakSelf可能已经为nil了
4.强引用strongSelf在block作用域结束之后，自动释放
weakSelf为什么需要strongSelf配合使用
1.在block块中先写一个strongSelf，是为了避免在block的执行过程中，突然出现self被释放的情况。
-----------------------------------------------------------------------------------------------------------------------------
CaculateMaker.m

- (CaculateMaker *(^)(CGFloat num))add{
    return ^CaculateMaker *(CGFloat num){
        self.result += num;
        return self;
    };
}

- (CaculateMaker *(^)(CGFloat num))minus{
    return ^CaculateMaker *(CGFloat num){
        self.result -= num;
        return self;
    };
}

- (CaculateMaker *(^)(CGFloat num))multiply{
    return ^CaculateMaker *(CGFloat num){
        self.result *=num;
        return self;
    };
}

- (CaculateMaker *(^)(CGFloat num))divide{
    return ^CaculateMaker *(CGFloat num){
        self.result /=num;
        return self;
    };
}

- (CGFloat)getResult{
    return self.result;
}
//调用方法
CaculateMaker *maker = [[CaculateMaker alloc] init];
//链式编程
CGFloat num = maker.add(20).minus(10).multiply(6).divide(5).getResult;
NSLog(@"------------%f",num);
个人总结： maker.add调用方法并返回block，maker.add()执行返回的block并返回self，self可以继续调用方法，以此类推，链式调用执行。
