//
//  StringAndCopy.h
//  Notes
//
//  Created by Civet on 2020/8/4.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef StringAndCopy_h
#define StringAndCopy_h


#endif /* StringAndCopy_h */
/*
 @property (nonatomic,strong) NSString *strCopy;
 
 NSMutableString *str = [NSMutableString stringWithFormat: @"bbbbb"];
 NSLog(@"str==========%p",str);
 self.strCopy = @"aaaa";
 NSLog(@"self.strCopy=============%p",self.strCopy);
 self.strCopy = str;
 NSLog(@"self.strCopy=============%p",self.strCopy);
 [str appendString:@"ccc"];
 NSLog(@"str==========%@",str);
 NSLog(@"str==========%p",str);
 NSLog(@"self.strCopy=============%@",self.strCopy);
 NSLog(@"self.strCopy=============%p",self.strCopy);
 
 2020-08-04 14:45:46.227111+0800 test5[6663:182976] str==========0x60000363fc30
 2020-08-04 14:45:46.227257+0800 test5[6663:182976] self.strCopy=============0x1070ee0a0
 2020-08-04 14:45:46.227341+0800 test5[6663:182976] self.strCopy=============0x60000363fc30
 2020-08-04 14:45:46.227423+0800 test5[6663:182976] str==========bbbbbccc
 2020-08-04 14:45:46.227507+0800 test5[6663:182976] str==========0x60000363fc30
 2020-08-04 14:45:46.227577+0800 test5[6663:182976] self.strCopy=============bbbbbccc
 2020-08-04 14:45:46.227647+0800 test5[6663:182976] self.strCopy=============0x60000363fc30
 
 
 
 @property (nonatomic,copy) NSString *strCopy;
 
 NSMutableString *str = [NSMutableString stringWithFormat: @"bbbbb"];
 NSLog(@"str==========%p",str);
 self.strCopy = @"aaaa";
 NSLog(@"self.strCopy=============%p",self.strCopy);
 self.strCopy = str;
 NSLog(@"self.strCopy=============%p",self.strCopy);
 [str appendString:@"ccc"];
 NSLog(@"str==========%@",str);
 NSLog(@"str==========%p",str);
 NSLog(@"self.strCopy=============%@",self.strCopy);
 NSLog(@"self.strCopy=============%p",self.strCopy);
 
 2020-08-04 14:53:36.473356+0800 test5[6815:187085] str==========0x6000024309c0
 2020-08-04 14:53:36.473561+0800 test5[6815:187085] self.strCopy=============0x1018270b0
 2020-08-04 14:53:36.473647+0800 test5[6815:187085] self.strCopy=============0xcaf5c958f5093422
 2020-08-04 14:53:36.473728+0800 test5[6815:187085] str==========bbbbbccc
 2020-08-04 14:53:36.473813+0800 test5[6815:187085] str==========0x6000024309c0
 2020-08-04 14:53:36.473895+0800 test5[6815:187085] self.strCopy=============bbbbb
 2020-08-04 14:53:36.473964+0800 test5[6815:187085] self.strCopy=============0xcaf5c958f5093422
 
 个人总结：
 1.当属性被strong或copy修饰，给属性赋值为不可变的变量，如：NSString、NSArray等，strong和copy效果相同，该属性指向不可变变量的内存地址；
 2.当属性被strong修饰，给属性赋值为可变变量，如NSMutableString,NSMutableArray等，当可变变量的值改变时，属性的值也会跟着改变，属于浅拷贝；
 3.当属性被copy修饰，给属性赋值为可变变量，如NSMutableString,NSMutableArray等，当可变变量的值改变时，属性的值不会改变，因为在给属性赋值的过程中，
对可变变量的值进行了拷贝，开辟了新的内存，然后属性的指针指向拷贝的变量内存，当原可变变量的值改变时，不会影响拷贝变量的值，属于深拷贝。
 
 
 @property （nonatomic,copy)NSMutableArray *mutArray;
 
 NSMutableArray *testArray = [NSMutableArray arrayWithObject:@"milan"];
 
 self.mutArray = [testArray copy];
 
 对于以上的操作在一般使用上是没有问题的,但是当你的mutArray想要插入或删除内容的时候会报错,因为[testArray copy]赋值给mutArray以后，其实它持有的是一个“不可变”的副本，即使你本身定义为一个可变对象。
 
 个人总结：
 不可变变量经过[xxx copy]操作后生成的副本为不可变的，所有不能对不可变变量使用插入或删除，执行copy操作生成的是不可变对象,执行mutableCopy操作生成的内容用可变类型接收就是可变的,
 不可变类型接收就是不可变的.
 
 
 
 @property (nonatomic,copy) NSMutableString *stringCopy;
 
 
 self.stringCopy = [NSMutableString stringWithString:@"aaaa"];
 NSLog(@"self.stringCopy===========%@,=====%p",self.stringCopy,self.stringCopy);
 [self.stringCopy appendString:@"bbbb"]; //报错，程序终止-----------------------------
 NSLog(@"self.stringCopy===========%@,=====%p",self.stringCopy,self.stringCopy);
 个人推测：对copy修饰的可变变量进行二次赋值，相当于先进行[self.stringCopy copy]操作，变为了不可变变量，所有修改不可变变量的值会报错。
 纠正：可变变量改为strong修饰即可修改可变变量的值
 
 
 
 自定义对象的copy/mutableCopy
 1.如果需要对自定义的对象进行copy或者mutableCopy操作的话首先需要遵守他们的协议NSCopying和NSMutableCopy
 2.重写方法
 
 
 - (id)copyWithZone:(NSZone *)zone{
 LineDayModel * model = [[LineDayModel allocWithZone:zone]init];
 model.arrData = [self.arrData copy];
 model.date = [self.date copy];
 model.highest = [self.highest copy];
 model.lowest = [self.lowest copy];
 return model;
 }
 - (id)mutableCopyWithZone:(nullable NSZone *)zone{
 LineDayModel * dayModel = [[LineDayModel allocWithZone:zone]init];
 dayModel.arrData = [self.arrData mutableCopy];
 dayModel.date = [self.date mutableCopy];
 dayModel.highest = [self.highest mutableCopy];
 dayModel.lowest = [self.lowest mutableCopy];
 return dayModel;
 }
 
 
 Block是将函数及其执行上下文封装起来的对象。所以Block理论上是可以retain/release的。但是Block在创建的时候它的内存是默认是分配在栈(stack)上, 而不是堆(heap)上的. 所以它的作用域仅限创建时候的当前上下文(函数, 方法...), 当你在该作用域外调用该block时, 程序就会崩溃.
 
 其实block使用copy是MRC时代留下来的传统。 在MRC下, 在方法中的block创建在栈区, 使用copy就能把它放到堆区, 这样在作用域外调用该block程序就不会崩溃.但在ARC下, 使用copy与strong其实都一样,因为block的retain就是用copy来实现的。之所以大家都习惯用copy就是MRC时代留下的习惯。
 
 */
