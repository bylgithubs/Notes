//
//  CreateArrray.h
//  Notes
//
//  Created by Civet on 2020/8/13.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef CreateArrray_h
#define CreateArrray_h


#endif /* CreateArrray_h */

/*
- (void)immutableArray{
    NSArray *arr0 = @[@"a",@"b",@"c",@"d",@"e",@"f",@"g"];
    //创建空数组
    NSArray *arr = [[NSArray alloc] init];
    //对象方法创建数组，以nil结束
    NSArray *arr1 = [[NSArray alloc] initWithObjects:@"obj1",@"obj2",@"obj3", nil];
    //用类方法创建空数组，并通过已有数组对新创建的数组进行初始化
    //    NSArray *arr2 = [[NSArray array] initWithArray:arr1];
    //    NSArray *arr2 = [NSArray array];
    //    arr2 = [arr2 initWithObjects:@"obj1",@"obj2",@"obj3",nil];
    //arr2 = [arr2 initWithArray:arr0];
    //通过类方法创建数组
    NSArray *arr3 = [NSArray arrayWithArray:arr];
    //通过类方法创建空数组
    NSArray *arr4 = [NSArray array];
    
    NSArray *arr5 = @[@"a",@"b",@"c",@"d",@"e",@"f",@"g"];
    NSString *str = [arr5 objectAtIndex:3];
    //取出数组第一个元素
    NSString *firstObj = [arr5 firstObject];
    //取出数组最后一个元素
    NSString *lastObj = [arr5 lastObject];
    //通过下标直接取出数组元素
    NSString *str1 = arr5[arr5.count -1];
    
    //取多个
    //NSIndexSet:是一个索引集合，原理上与数组类似，只不过这是一个无序的
    NSIndexSet *set = [[NSIndexSet alloc] initWithIndexesInRange:NSMakeRange(1, 2)];
    NSArray *arr6 = [arr5 objectsAtIndexes:set];
    
    //简单方法截取多个元素
    NSArray *arr7 = [arr5 subarrayWithRange:NSMakeRange(2, 3)];
    NSLog(@"arr7=======%@",arr7);
}

- (void)mutableArray{
    //创建空数组
    NSMutableArray *arr = [NSMutableArray array];
    //capacity:容量、能力
    NSMutableArray *arr1 = [NSMutableArray arrayWithCapacity:20];
    NSMutableArray *arr2 = [[NSMutableArray alloc] initWithCapacity:20];
    //如下不可变数组不能调用addObject方法
    NSArray *arr3 = @[@"a",@"b",@"c",@"d",@"e",@"f",@"g"];
    NSMutableArray *arr4 = [[NSMutableArray alloc] initWithArray:arr3];
    //通过类方法创建
    NSMutableArray *arr5 = [NSMutableArray arrayWithObjects:@"a",@"b",@"c", nil];
    
    //增
    [arr addObject:@"a"];
    [arr addObjectsFromArray:@[@"b",@"c",@"d"]];
    
    //删
    NSMutableArray *arr6 = [NSMutableArray arrayWithObjects:@"a",@"a",@"b",@"b",@"b",@"c",@"d",@"e",@"f",@"g",@"h",@"j", nil];
    //按元素删除，如果数组中有多个相同的元素，那么会全部删除
    [arr6 removeObject:@"b"];
    //按下标删除
    [arr6 removeObjectAtIndex:2];
    //删除最后一个
    [arr6 removeLastObject];
    
    //删除多个，在range范围内删除从第一个参数开始的后第二个参数个数的数据
    NSIndexSet *set = [[NSIndexSet alloc] initWithIndexesInRange:NSMakeRange(1, 2)];
    [arr6 removeObjectsAtIndexes:set];
    
    //删除全部
    [arr6 removeAllObjects];
}

- (void)separatedOfCharacterString{
    NSString *str = @"sdjfkjdsjf#*sjkd#*skdud#*skudjhfksd#*";
    NSArray *arr = [str componentsSeparatedByString:@"#"];
    
    //字符集合中的字符切割
    NSString *str1 = @"skjdfsl!skljdfkds* smjdfjs*JHhndnf.sdfs";
    NSCharacterSet *set = [NSCharacterSet characterSetWithCharactersInString:@"!*,."];
    NSArray *arr1 = [str1 componentsSeparatedByCharactersInSet:set];
    
    //组合
    //将数组中的字符串元素按照某种规则组合成一个新的字符串
    NSArray *arr2 = @[@"aa",@"bb",@"cc",@"dd",@"ee",@"ff"];
    NSString *str2 = [arr2 componentsJoinedByString:@"!!"];
    NSLog(@"============%@",str2);
}

- (void)packagingSingleDataType{
    //NSNumber:专门用于封装简单数据类型的类
    //因为在OC中，数组、字典等存储工具里面只能存储对象，需要将简单数据类型转化为对象才能进行存储
    int a = 3;
    int b = 9;
    NSNumber *aNum = [[NSNumber alloc] initWithInt:a];
    NSNumber *bNum = [[NSNumber alloc] initWithInt:b];
    //存入数组
    NSArray *arr = @[aNum,bNum];
    
    //比较大小
    NSComparisonResult result = [aNum compare:bNum];
    NSLog(@"========%ld",result);
    
    //NSNumberl类型转换为int类型
    int c = [aNum intValue];
    NSInteger d = [bNum integerValue];
}

- (void)arraySort{
    [self arraySortOne];
}

- (void)arraySortOne{
    NSArray *arr = [NSArray arrayWithObjects:@"2",@"3",@"1",@"5",@"6",@"9",@"1",@"45",@"3",@"20",@"23",@"22",nil,nil];
    // 返回一个排好序的数组，原来数组的元素顺序不会改变
    // 指定元素的比较方法：compare:方法只能比较位数相同的数据的大小
    NSArray *arr1 = [arr sortedArrayUsingSelector:@selector(compare:)];
    NSLog(@"arr1==============%@",arr1);
    
}

- (void)arraySortTwo:(NSArray *)arr{
    //第一个排序条件
    NSSortDescriptor *firstCondition = [NSSortDescriptor sortDescriptorWithKey:@"firestProperty" ascending:YES];
    //第二个排序条件
    NSSortDescriptor *secondCondition = [NSSortDescriptor sortDescriptorWithKey:@"secondProperty" ascending:YES];
    //第三个排序条件
    NSSortDescriptor *thirdCondition = [NSSortDescriptor sortDescriptorWithKey:@"thirdProperty" ascending:YES];
    NSArray *sortConditionArr = [NSArray arrayWithObjects:firstCondition,secondCondition,thirdCondition, nil];
    //将所有排序条件加入待排序数组进行排序
    NSArray *arr1 = [arr sortedArrayUsingDescriptors:sortConditionArr];
    NSLog(@"已排好序数组：%@",arr1);
    
}
 
 */
