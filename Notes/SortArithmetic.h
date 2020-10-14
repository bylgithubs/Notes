//
//  SortArithmetic.h
//  Notes
//
//  Created by Civet on 2020/8/11.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef SortArithmetic_h
#define SortArithmetic_h


#endif /* SortArithmetic_h */


//冒泡排序算法
-(void)bubbleSort{
    //未排序数组
    NSMutableArray *arr = [NSMutableArray arrayWithObjects:@"16",@"18",@"6",@"8",@"66", nil];
    //开始排序
    for (int i = 0; i < arr.count; i++) {
        for (int j = 0; j < arr.count - 1 - i; j++) {
            //比较数据大小,升序排序，从后往前有序
            if ([arr[j] intValue]> [arr[j+1] intValue]) {
                int temp = [arr[j] intValue];
                arr[j] = arr[j+1];
                arr[j+1] = [NSString stringWithFormat:@"%d",temp];
            }
        }
    }
    NSLog(@"冒泡排序结果:%@",arr);
}

//选择排序
-(void)selectionSort{
    NSMutableArray *arr = [NSMutableArray arrayWithObjects:@"16",@"18",@"6",@"8",@"66", nil];
    //开始排序
    for (int i = 0; i <arr.count; i++) {
        //升序排序，从前向后排，有序
        for (int j = i + 1; j < arr.count; j++) {
            if ([arr[i] intValue] > [arr[j] intValue]) {
                int temp = [arr[i] intValue];
                arr[i] = arr[j];
                arr[j] = [NSString stringWithFormat:@"%d",temp];
            }
        }
    }
    NSLog(@"选择排序结果:%@",arr);
}

//插入排序
- (void)insertionSort{
    NSMutableArray *arr = [NSMutableArray arrayWithObjects:@"16",@"18",@"6",@"8",@"66", nil];
    //开始排序
    for (int i = 1; i < arr.count; i++) {
        int j = i;
        int temp = [arr[i] intValue];
        //对之前有序序列进行比较，插入排序
        while (j > 0 && [arr[j-1] intValue] > temp) {
            arr[j] = arr[j-1];
            //效果同上，将arr[j-1]的值插入可变数组j的位置
            //[arr replaceObjectAtIndex:j withObject:[arr objectAtIndex:j-1]];
            j--;
        }
        arr[j] = [NSString stringWithFormat:@"%d",temp];
        //[arr replaceObjectAtIndex:j withObject:[NSNumber numberWithInt:temp]];
    }
    NSLog(@"插入排序结果:%@",arr);
}

//希尔排序
//折半插入排序，从中间往前依次排序，有序
- (void)shellSort{
    NSMutableArray *arr = [NSMutableArray arrayWithObjects:@"16",@"18",@"6",@"8",@"66", nil];
    int gap = arr.count/2.0;
    while (gap >=1) {
        for (int i = gap; i < arr.count; i++) {
            int j = i;
            int temp = [arr[j] intValue];
            while (j >= gap && temp < [arr[j-1] intValue]) {
                arr[j] = arr[j-1];
                j--;
            }
            arr[j] = [NSString stringWithFormat:@"%d",temp];
        }
        gap = gap/2.0;
    }
    NSLog(@"希尔排序结果：%@",arr);
}

- (void)binSearch{
    NSMutableArray *arr = [NSMutableArray arrayWithObjects:@"6",@"8",@"16",@"18",@"66", nil];
    NSInteger number = 8;
    //折半查找，递归方式
    NSInteger location = [self binSearch:number array:arr low:0 high:arr.count-1];
    NSLog(@"折半查找，递归方式=====%ld位于数组第%ld位",number,location);
    //折半查找，非递归
    NSInteger location1 = [self binSearch:number array:arr];
    NSLog(@"折半查找，非递归方式=====%ld位于数组第%ld位",number,location1);
}

//二分/折半查找，递归
- (NSInteger)binSearch:(NSInteger)key array:(NSMutableArray *)arr low:(NSInteger)low high:(NSInteger)high{
    if (arr == nil || arr.count <=0) {
        NSLog(@"查找数组为空");
        return -1;
    }
    if (key < [arr[0] integerValue] || key > [arr[arr.count-1] integerValue]) {
        NSLog(@"========超出数组元素值边界！");
        return -1;
    }
    //必须包含等于
    if (low <= high) {
        NSInteger mid =  (low + high)/2;
        if (key == [arr[mid] integerValue]) {
            return mid;
        }
        else if(key < [arr[mid] integerValue]){
            return [self binSearch:key array:arr low:low high:mid - 1]; //递归
        }
        else{
            return [self binSearch:key array:arr low:mid+1 high:high];  //递归
        }
    }else{
        NSLog(@"========该数组不存在该值，请重新输入");
        return -1;
    }
}

//二分/折半查找，非递归
- (NSInteger)binSearch:(NSInteger)key array:(NSMutableArray *)arr{
    if (arr == nil || arr.count <=0) {
        NSLog(@"查找数组为空");
        return -1;
    }
    if (key < [arr[0] integerValue] || key > [arr[arr.count-1] integerValue]) {
        NSLog(@"超出数组数值范围");
        return -1;
    }
    NSInteger i = 0;
    NSInteger j = arr.count -1;
    while (i <= j) {
        NSInteger mid = (i + j)/2;
        if (key == [arr[mid] integerValue]) {
            return mid;
        }
        if (key < [arr[mid] integerValue]) {
            j = mid - 1;
        } else {
            i = mid +1;
        }
    }
    return -1;
}

- (void)quickSort{
    NSMutableArray *arr = [NSMutableArray arrayWithObjects:@"16",@"18",@"6",@"8",@"66", nil];
    [self quickSort:arr leftIndex:0 rightIndex:arr.count-1];
}

//快速排序
- (void)quickSort:(NSMutableArray *)arr leftIndex:(NSInteger)leftIndex rightIndex:(NSInteger)rightIndex{
    if (leftIndex >= rightIndex) {
        NSLog(@"快速排序有序数组:%@",arr);
        return;
    }
    NSInteger i = leftIndex;
    NSInteger j = rightIndex;
    NSInteger key = [arr[i] integerValue];
    while (i < j) {
        //首先从右边j开始查找比基准数小的值
        while (i < j && key < [arr[j] integerValue]) {
            j--;
        }
        //如果比基准数小，则将查找到的小值调换到i的位置
        arr[i] = arr[j];
        //当在右边查找到一个比基准数小的值时，就从i开始往后找比基准数大的值
        while (i < j && key > [arr[i] integerValue]) {
            i++;
        }
        //如果比基准数大，则将查找到的大值调换到j的位置
        arr[j] = arr[i];
    }
    arr[i] = @(key);
    /// 递归排序
    //排序基准数左边的
    [self quickSort:arr leftIndex:leftIndex rightIndex:i-1];
    //排序基准数右边的
    [self quickSort:arr leftIndex:i+1 rightIndex:rightIndex];
}

//快速排序,优化
- (void)quickSort:(NSMutableArray *)arr leftIndex:(NSInteger)leftIndex rightIndex:(NSInteger)rightIndex{
    if (leftIndex >= rightIndex) {
        NSLog(@"key===%ld,快速排序有序数组:%@",leftIndex,arr);
        return;
    }
    NSInteger i = leftIndex;
    NSInteger j = rightIndex;
    NSInteger key = [arr[i] integerValue];
    while (i < j) {
        //首先从右边j开始查找比基准数小的值
        while (i < j && key < [arr[j] integerValue]) {
            j--;
        }
        //当在右边查找到一个比基准数小的值时，就从i开始往后找比基准数大的值
        while (i < j && key >= [arr[i] integerValue]) {
            i++;
        }
        //交换两个数在数组中的位置
        if(i<j){
            [arr exchangeObjectAtIndex:i withObjectAtIndex:j];
            //            NSInteger temp = [arr[i] integerValue];
            //            arr[i] = arr[j];
            //            arr[j] = @(temp);
        }
    }
    arr[leftIndex] = arr[i];
    arr[i] = @(key);
    /// 递归排序
    //排序基准数左边的
    [self quickSort:arr leftIndex:leftIndex rightIndex:i-1];
    //排序基准数右边的
    [self quickSort:arr leftIndex:i+1 rightIndex:rightIndex];
}




