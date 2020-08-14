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

/*
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
*/
