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



