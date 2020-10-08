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

个人总结：当name的字符数不大于10个时，该name为tagged pointer,推测name位于栈区，当name的字符数大于10个时，
name是对象，位于堆区，MRC下在异步全局队列中进行for循环赋值会崩溃，由于是异步线程原来的name通过release释放，又有一个线程来释放name，但是现在name的引用计数为0，不能再次释放，所以会崩溃，tagged pointer，就不会发生这样的问题。
-(void)setName:(NSString *)name {
    if(_name != name){
        [_name release];
        _name = [name retrain];
    }
}

