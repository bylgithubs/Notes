//
//  CopyAndMutableCopy.h
//  Notes
//
//  Created by Civet on 2020/8/14.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef CopyAndMutableCopy_h
#define CopyAndMutableCopy_h


#endif /* CopyAndMutableCopy_h */

NSArray *arr = @[@"a",@"b",@"c"];
NSArray *arr0 = @[@"a"];
NSMutableArray *arr1 = [NSMutableArray arrayWithObject:@"d"];
NSMutableArray *arr2 = [NSMutableArray arrayWithObjects:@"d",@"e",@"f"];
NSMutableArray *arr3 = [NSMutableArray arrayWithObjects:arr,arr0,arr1,arr2,[arr mutableCopy],@"bbbb",@"ccc",nil];


//__NSSingleObjectArrayI:存了一个元素的不可变数组
//__NSArrayI:不可变数组
//__NSArrayM:可变数组
Printing description of arr3:
<__NSArrayM 0x6000000c0720>(    //arr3
                            <__NSArrayI 0x6000000c09c0>(  //arr
                                                        a,
                                                        b,
                                                        c
                                                        )
                            ,
                            <__NSSingleObjectArrayI 0x600000c9c460>(    //arr0
                                                                    a
                                                                    )
                            ,
                            <__NSArrayM 0x6000000c07e0>(    //arr1
                                                        d
                                                        )
                            ,
                            <__NSArrayM 0x6000000c0840>(    //arr2
                                                        d,
                                                        e,
                                                        f
                                                        )
                            ,
                            <__NSArrayM 0x6000000c0780>(    //[arr mutableCopy]
                                                        a,
                                                        b,
                                                        c
                                                        )
                            ,
                            bbbb,
                            ccc
                            )
个人总结：不可变数组经过mutableCopy后变为可变数组，NSArray和NSMutableArray声明的指针都可以指向[NSArray mutableCopy]后的数组

@property (nonatomic,strong) NSString *name;

dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
    for (int i = 0; i <1000; i++) {
        dispatch_async(queue, ^{
            self.name = [NSString stringWithFormat:@"asdfghjklz1"];
        });
    }

个人总结：当name的字符数不大于9个时，该name为tagged pointer,推测name位于栈区，当name的字符数大于9个时，
name是对象，位于堆区，MRC下在异步全局队列中进行for循环赋值会崩溃，由于是异步线程原来的name通过release释放，又有一个线程来释放name，但是现在name的引用计数为0，不能再次释放，所以会崩溃，tagged pointer，就不会发生这样的问题。
-(void)setName:(NSString *)name {
    if(_name != name){
        [_name release];
        _name = [name retrain];
    }
}

NSString *str = @"aaaaaaaaa";
NSString *str1 = @"aaaaaaaaab";
NSString *str2 = @"aaaaaaaaabc";
NSLog(@"str===============%p",str); //0x10352b070
NSLog(@"str1=================%p",str1); //0x10352b090
NSLog(@"str2=================%p",str2); //0x10352b0b0

NSString *str3 = [NSString stringWithFormat: @"aaaaaaaaa"];
NSString *str4 = [NSString stringWithFormat: @"aaaaaaaaab"];
NSString *str5 = [NSString stringWithFormat: @"aaaaaaaaabc"];
NSLog(@"str3===============%p",str3);   //0xc8b8ba4d10cf200a
NSLog(@"str4=================%p",str4); //0x60000253cec0
NSLog(@"str5=================%p",str5); //0x60000253dcc0

 栈区 0x7
 堆区 0x6
/*
@"",initWithString和stringWithString创建的NSString对象，不管字符串的内容和长度怎么变化，该字符串对象始终是存储在常量区的，
 引用计数为-1；从用%lu打印来看initWithString和stringWithString创建的字符串retainCount是无符号长整型的最大值。所以可以说他们没有引用计数这个概念.
而由initWithFormat和stringWithFormat创建的对象，如果字符串内容是非汉字的，那么当字符串长度小于10个时，该字符串存储区域在五大区域之外，且随着字符串长度的变化，
 存储地址会有很大变化。当字符串长度超过10个以后，该字符串在堆中，与正常的OC对象一样。这里为什么要说非汉字呢，因为如果字符串内容是汉字，不管字符串的内容和长度怎么变化，
 该字符串都是在堆中，与正常OC对象一样。
 */

NSString *str = @"aaaa";
NSString *str1 = [str copy];
NSString *str2 = [str mutableCopy];
NSLog(@"\n str=========%p,\n str1=========%p,\n str2==========%p",str,str1,str2);

2020-10-15 14:08:03.211932+0800 test3[6891:189295]
str=========0x10e5b1180,
str1=========0x10e5b1180,
str2==========0x60000051c060

NSArray *arr1 = [NSArray arrayWithObjects:[NSMutableString stringWithString:@"a"],@"b",@"c",nil];
NSArray *arr2 = [arr1 copy];
NSMutableArray *arr3 = [arr1 mutableCopy];
NSMutableArray *arr4 = [[NSMutableArray alloc] initWithArray:arr1 copyItems:YES];
NSLog(@"\arr1=========%p,\n arr2========%p,\n arr3========%p,\n arr3========%p",arr1,arr2,arr3,arr4);
NSMutableString *testString = [arr1 objectAtIndex:0];
[testString appendString:@" tail"];//这样以上三个数组的首元素都被改变了

2020-10-15 13:50:31.108562+0800 test3[6697:178914] rr1=========0x6000017bdec0,
arr2========0x6000017bdec0,
arr3========0x6000017bdda0,
arr3========0x6000017bdd10
(lldb) p &*arr1[0]
(__NSCFString *) $0 = 0x00006000017bdb60 @"a"
(lldb) p &*arr2[0]
(__NSCFString *) $1 = 0x00006000017bdb60 @"a"
(lldb) p &*arr3[0]
(__NSCFString *) $2 = 0x00006000017bdb60 @"a"
(lldb) p &*arr4[0]
(NSTaggedPointerString *) $3 = 0x91d096d0625e81b3 @"a"
(lldb) p &*arr1[1]
(__NSCFConstantString *) $4 = 0x000000010f4ca1a0 @"b"
(lldb) p &*arr3[1]
(__NSCFConstantString *) $5 = 0x000000010f4ca1a0 @"b"
(lldb) p &*arr4[1]
(__NSCFConstantString *) $6 = 0x000000010f4ca1a0 @"b"
(lldb) p &*arr1[0]
(__NSCFString *) $7 = 0x00006000017bdb60 @"a tail"
(lldb) p &*arr3[0]
(__NSCFString *) $8 = 0x00006000017bdb60 @"a tail"
(lldb) p &*arr4[0]
(NSTaggedPointerString *) $9 = 0x91d096d0625e81b3 @"a"

个人总结：
1.对非容器类（NSString,NSNumber……)进行拷贝操作，不可变对象，使用copy，浅拷贝，拷贝后的指针和原指针指向同一个对象，对象引用计数加一；
不可变对象，使用mutableCopy，深拷贝，重新分配一块内存，拷贝后的指针指向新的内存，引用计数为1，原指针指向地址不变，引用计数不变；
可变对象，使用copy，深拷贝，拷贝后的对象变为不可变对象；可变对象，使用mutableCopy，深拷贝，拷贝后的对象可以赋值给可变和不可变的指针引用；
2.对容器类(NSArray,NSDictionary……)进行拷贝操作，最外层容器的拷贝情况和非容器类一样；如果容器的元素还是容器，使用mutableCopy对容器进行拷贝，
虽然也是深拷贝，但是容器中的容器元素仅仅只拷贝了指针，对于容器元素来说属于浅拷贝，可以使用[[NSMutableArray alloc] initWithArray:arr1 copyItems:YES]函数，
将copyItems的参数设为YES进行容器元素的深拷贝。
3.容器中，经实际测试发现，对不可变对象进行mutableCopy操作，虽然是深拷贝，但是不可变元素所在的内存地址并没有改变，
因为如果容器的某一元素是不可变的，那你复制完后该对象仍旧是不能改变的，因此只需要指针复制即可。除非你对容器内的元素重新赋值，否则指针复制已经足够。

NSArray *array = [NSArray arrayWithObjects:[NSMutableString stringWithString:@"first"],[NSMutableString stringWithString:@"b"],@"c",nil];
NSArray *deepCopyArray=[[NSArray alloc] initWithArray: array copyItems: YES];
NSArray* trueDeepCopyArray = [NSKeyedUnarchiver unarchiveObjectWithData:
                              [NSKeyedArchiver archivedDataWithRootObject: array]];
NSLog(@"\n array===========%p,\n deepCopyArray==========%p,\n trueDeepCopyArray==========%p\n",array,deepCopyArray,trueDeepCopyArray);
2020-10-15 14:52:58.020933+0800 test3[7378:211677]
array===========0x600000934930,
deepCopyArray==========0x600000934a50,
trueDeepCopyArray==========0x600000934bd0
(lldb) p &*array[2]
(__NSCFConstantString *) $0 = 0x000000010da391c0 @"c"
(lldb) p &*deepCopyArray[2]
(__NSCFConstantString *) $1 = 0x000000010da391c0 @"c"
(lldb) p &*trueDeepCopyArray[2]
(NSTaggedPointerString *) $2 = 0xa07054d98e804493 @"c"
个人总结：使用归档和解档方法可以对容器中的不可变对象进行拷贝操作。

