//
//  VariableAndPointer.h
//  Notes
//
//  Created by Civet on 2020/10/14.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef VariableAndPointer_h
#define VariableAndPointer_h


#endif /* VariableAndPointer_h */

1、局部变量存储在栈中
2、全局变量、静态变量（全局和局部静态变量）存储在静态存储区
3、new申请的内存是在堆中
4、字符串常量也是存储在静态存储区

- (void)pointerTest{
    int a = 100;
    int b = 100;
    int *p = &a;
    //    NSString *a = @"100000000000";
    //    int p = &a;
    NSLog(@"\n a--p--%p,\n &a--p--%p,\n p--p--%p,\n *p--p--%p,\n *p--d--%d,\n &p--p--%p \n a--d--%d\n",a,&a,p,*p,*p,&p,a);
    NSLog(@"\n b--p--%p,\n &b--p--%p, \n",b,&b);
    //    NSLog(@"\n a--p--%p,\n &a--p--%p,\n p--p--%p,\n *p--p--%p,\n *p--d--%d,\n a--d--%@\n",a,&a,p,p,p,a);
}

2020-10-14 15:16:44.477787+0800 test3[9652:239199]
a--p--0x64,
&a--p--0x7ffee0ded8dc,
p--p--0x7ffee0ded8dc,
*p--p--0x64,
*p--d--100,
&p--p--0x7ffee0ded8d0
a--d--100
2020-10-14 15:16:44.477993+0800 test3[9652:239199]
b--p--0x64,
&b--p--0x7ffee0ded8d8,
(lldb) p &*p
(int *) $0 = 0x00007ffee0ded8dc
(lldb) p &*p
(int *) $0 = 0x00007ffee0ded8dc
(lldb) p *&p
(int *) $1 = 0x00007ffee0ded8dc

个人总结：a、b为局部变量，位于栈区，p为指针变量名字，也在栈中，&为取地址符号，&a表示a变量的地址，&p表示p指针的地址，&*p表示a变量的地址，
*&p表示p所在内存中存储的内容，值为a的地址;以%p打印p为p指针所指内容的地址，值为a变量的首内存地址，打印&p为p指针所在的内存地址

int a = 1;
//int *p =a; //不对
//或者
//int *p = 100; //不对
//上面两个指针变量p的赋值都是不对的，指针变量是用来存储`变量地址`的
int *p = &a;//正确
*p = 2;
NSLog(@"%d",a);// 结果是2

如果在OC中，NSString *str = @"hello"; 其实str也是 @"hello"所在常量区的地址，那为什么我们平常打印str的时候，直接就是@“hello”这个值，而不是通过 *str来获取呢？
原因：NSString本身是一个对象，它不止是char *这些基本类型这么简单。本质上OC的对象是一个结构体。NSLog遇到%@格式和接收对象作为参数时直接调用对象的description方法。
与基本数据类型的处理是有区别的。

