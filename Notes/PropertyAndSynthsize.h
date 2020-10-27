//
//  PropertyAndSynthsize.h
//  Notes
//
//  Created by Civet on 2020/7/20.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef PropertyAndSynthsize_h
#define PropertyAndSynthsize_h


#endif /* PropertyAndSynthsize_h */

 @property @synthesize
1.类中的属性只存在@property修饰，系统会自动生成该属性的get和set方法和带_XX的实例变量；
2.变量被@property修饰，不能同时重写get和set方法，否则Xcode 会认为我们写的这 get set 方法的属性和@propery 声明的属性不是同一个属性,所以会报错;
3.@property和@synthesize生成的变量_X和X赋值时不会增加引用计数，使用self.X赋值时可能会增加引用计数，取决于@property中的定义：copy，strong，assign；
4.直接使用_X不会增加引用计数，使用self.X获取变量引用计数会+1；
5.成员变量是定义在｛｝号中的变量，如果变量的数据类型是一个类则称这个变量为实例变量。因为实例变量是成员变量的一种特殊情况，所以实例变量也是类内部使用的，
无需与外部接触的变量，这个也就是所谓的类私有变量。而属性变量是用于与其他对象交互的变量。
6.@synthesize还有一个作用，可以指定与属性对应的实例变量，例如@synthesize myButton = xxx；那么self.myButton其实是操作的实例变量xxx，而不是_myButton了。
 
 属性是与其他对象交互的变量，会生成默认的setter和getter方法。苹果早期的编译器是GCC，后来发展到LLVM，LLVM在没有匹配实例变量的属性时会自动创建一个带下划线的成员变量。注意：分类中添加的属性是不会自动生成setter和getter方法的，必须要手动添加。如果已经手动实现了get和set方法的话Xcode不会再自动生成带有下划线的私有成员变量了，因为xCode自动生成成员变量的目的就是为了根据成员变量而生成get/set方法的，但是如果get和set方法缺一个的话都会生成带下划线的变量。


nonatomic 非原子属性,同一时间可以有很多线程读和写
atomic 原子属性(线程安全)，保证同一时间只有一个线程能够写入(但是同一个时间多个线程都可以取值)，atomic 本身就有一把锁(自旋锁)

atomic：线程安全，需要消耗大量的资源
nonatomic：非线程安全，不过效率更高，一般使用nonatomic
 


