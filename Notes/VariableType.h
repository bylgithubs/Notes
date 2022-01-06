//
//  VariableType.h
//  Notes
//
//  Created by BaoYu Liao on 2022/1/6.
//  Copyright © 2022 PersonalONBYL. All rights reserved.
//

#ifndef VariableType_h
#define VariableType_h

#include <stdio.h>

@interface MyViewController :UIViewControlle
{
UIButton *yourButton;
int count;
id data；
}
@property (nonatomic, strong) UIButton *myButton;
@end

　　在{   } 中所声明的变量都为成员变量。 所以yourButton、count、data都是成员变量。既然如此，实例变量又是什么意思呢？

　　实例变量本质上就是成员变量，只是实例是针对类而言，实例是指类的声明。{   }中的yourButton就是实例变量。id 是OC特有的类，本质上讲id等同于（void *）。所以id data属于实例变量。

　　成员变量用于类内部，无需与外界接触的变量。因为成员变量不会生成set、get方法，所以外界无法与成员变量接触。根据成员变量的私有性，为了方便访问，所以就有了属性变量。属性变量的好处就是允许让其他对象访问到该变量（因为属性创建过程中自动产生了set 和get方法）。当然，你可以设置只读或者可写等，设置方法也可自定义。所以，属性变量是用于与其他对象交互的变量。

　　综上所述可知：成员变量是定义在｛｝号中的变量，如果变量的数据类型是一个类则称这个变量为实例变量。因为实例变量是成员变量的一种特殊情况，所以实例变量也是类内部使用的，无需与外部接触的变量，这个也就是所谓的类私有变量。而属性变量是用于与其他对象交互的变量。

　　但是，现在大家似乎都不怎么喜欢用成员变量来定义类的变量，都喜欢用属性变量来定义类的变量。把需要与外部接触的变量定义在.h文件中，只在本类中使用的变量定义在.m文件中。

除去基本数据类型int float ....等，其他类型的变量都叫做实例变量。


#endif /* VariableType_h */
