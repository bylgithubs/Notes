//
//  KVCAndKVO.h
//  Notes
//
//  Created by Civet on 2020/12/23.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef KVCAndKVO_h
#define KVCAndKVO_h


#endif /* KVCAndKVO_h */

KVC:
//dictionaryWithValuesForKeys:是指输入一组key，返回这组key对应的属性，再组成一个字典。
- (NSDictionary<NSString *, id> *)dictionaryWithValuesForKeys:(NSArray<NSString *> *)keys;
//setValuesForKeysWithDictionary:是用来修改Model中对应key的属性。
- (void)setValuesForKeysWithDictionary:(NSDictionary<NSString *, id> *)keyedValues;

NSDictionary *dic = @{@"name":@"name",@"content":@"content",@"subTitle":@"subTitle"};
KVCModel *model = [[KVCModel alloc] init];
//setValuesForKeysWithDictionary方法字典和model属性一一必须对应，model可以拥有多于字典的属性，
//但model中必须存在和字典对应的属性，必要条件
[model setValuesForKeysWithDictionary:dic];
NSLog(@"model.name:%@\nmodel.content:%@\nmodel.subTitle:%@",model.name,model.content,model.subTitle);

KVCModel * model0 = [[KVCModel alloc] init];
model0.age = 12;
KVCModel * model1 = [[KVCModel alloc] init];
model1.age = 13;
KVCModel * model2 = [[KVCModel alloc] init];
model2.age = 14;
KVCModel * model3 = [[KVCModel alloc] init];
model3.age = 15;
KVCModel * model4 = [[KVCModel alloc] init];
model4.age = 16;
NSArray * arr = @[model,model1,model2,model3,model4];
NSNumber* sum = [arr valueForKeyPath:@"@sum.age"];
NSLog(@"sum:%f",sum.floatValue);
NSNumber* avg = [arr valueForKeyPath:@"@avg.age"];
NSLog(@"avg:%f",avg.floatValue);
NSNumber* count = [arr valueForKeyPath:@"@count"];
NSLog(@"count:%f",count.floatValue);
NSNumber* min = [arr valueForKeyPath:@"@min.age"];
NSLog(@"min:%f",min.floatValue);
NSNumber* max = [arr valueForKeyPath:@"@max.age"];
NSLog(@"max:%f",max.floatValue);

2020-12-23 15:19:52.372663+0800 Test4[2258:107471] sum:58.000000
2020-12-23 15:19:52.372858+0800 Test4[2258:107471] avg:11.600000
2020-12-23 15:19:52.372984+0800 Test4[2258:107471] count:5.000000
2020-12-23 15:19:52.373116+0800 Test4[2258:107471] min:0.000000
2020-12-23 15:19:52.373228+0800 Test4[2258:107471] max:16.000000

@max用来查找集合中right keyPath指定的属性的最大值。
@sum用来计算集合中right keyPath指定的属性的总和。
@min用来查找集合中right keyPath指定的属性的最小值。
@count用来计算集合的总数。
@avg用来计算集合中right keyPath指定的属性的平均值。
注意：@count操作符比较特殊，它不需要写right keyPath，即使写了也会被忽略。
@max和@min在进行判断时，都是通过调用compare:方法进行判断，所以可以通过重写该方法对判断过程进行控制。


NSArray * unionOfArray = [array valueForKeyPath:@"@unionOfArrays.age"];
NSLog(@"%@",unionOfArray);
NSArray * distinctUnionOfArray = [array valueForKeyPath:@"@distinctUnionOfArrays.age"];
NSLog(@"%@",distinctUnionOfArray);

@unionOfArrays是用来操作集合内部的集合对象，将所有right keyPath对应的对象放在一个数组中返回。
@distinctUnionOfArrays是用来操作集合内部的集合对象，将所有right keyPath对应的对象放在一个数组中，并进行排重。

总结： KVC使用
 1、动态地取值和设值
 利用KVC动态的取值和设值。
 
 2、用KVC来访问和修改私有变量
 对于类里的私有属性，Objective-C是无法直接访问的，但是KVC是可以的。  KVC本质上是操作方法列表以及在内存中查找实例变量。我们可以利用这个特性访问类的私有变量，例如下面在.m中定义的私有成员变量和属性，都可以通过KVC的方式访问。
 这个操作对readonly的属性，@protected的成员变量，都可以正常访问。如果不想让外界访问类的成员变量，则可以将accessInstanceVariablesDirectly属性赋值为NO。

3、 Model和字典转换
 这是KVC强大作用的又一次体现，KVC和Objc的runtime组合可以很容易的实现Model和字典的转换。
 
4、 修改一些控件的内部属性
 这也是iOS开发中必不可少的小技巧。众所周知很多UI控件都由很多内部UI控件组合而成的，但是Apple度没有提供这访问这些控件的API，这样我们就无法正常地访问和修改这些控件的样式。
 而KVC在大多数情况可下可以解决这个问题。最常用的就是个性化UITextField中的placeHolderText了。


Apple对KVC的valueForKey:方法作了一些特殊的实现，比如说NSArray和NSSet这样的容器类就实现了这些方法。所以可以用KVC很方便地操作集合。

注意：KVC是支持基础数据类型和结构体的，可以在setter和getter的时候，通过NSValue和NSNumber来转换为OC对象。Swift中不存在这样的需求，因为Swift中所有变量都是对象。
需要注意的是，无论什么时候都不应该给setter中传入nil，会导致Crash并引起NSInvalidArgumentException异常。
尽管valueForKey：会自动将值类型封装成对象，但是setValue：forKey：却不行。你必须手动将值类型转换成NSNumber或者NSValue类型，才能传递过去。 因为传递进去和取出来的都是id类型，所以需要开发者自己担保类型的正确性，运行时Objective-C在发送消息的会检查类型，如果错误会直接抛出异常。
KVC存在一个问题在于，因为传入的key或keyPath是一个字符串，这样很容易写错或者属性自身修改后字符串忘记修改，这样会导致Crash。
可以利用iOS的反射机制来规避这个问题，通过@selector()获取到方法的SEL，然后通过NSStringFromSelector()将SEL反射为字符串。这样在@selector()中传入方法名的过程中，编译器会有合法性检查，如果方法不存在或未实现会报黄色警告。
[self valueForKey:NSStringFromSelector(@selector(object))];

--------------------------------------------------------------------------------------------------------------------------------
KVO:Key-Value Observing
使用kvo监听A对象的时候，监听的本质不是这个A对象，而是系统创建的一个中间对象NSKVONotifying_A并继承A对象，并且A对象的isa指针指向的也不是A的类，
而是这个NSKVONotifying_A对象
1.添加监听，注册观察者
[self.model addObserver:self forKeyPath:@"age" options:NSKeyValueObservingOptionNew context:nil];

2.触发监听方法
//收到通知
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context {
 if (self.model == object && [keyPath isEqualToString:@"age"]) {
     ageLable.text = [NSString stringWithFormat:@"%@", [change valueForKey:@"new"]];
 }
}
3.移除观察者：removeObserver: forKeyPath、removeObserver: forKeyPath: context:(对象销毁，必须移除观察者)


1.系统就会在运行期动态地创建该类的一个派生类（继承自原本的类），在这个派生类中重写基类中任何被观察属性的 setter 方法。派生类在被重写的 setter 方法实现真正的通知机制，就如前面手动实现键值观察那样。这么做是基于设置属性会调用 setter 方法，而通过重写就获得了 KVO 需要的通知机制。
2.同时派生类还重写了 class 方法以“欺骗”外部调用者它就是起初的那个类。然后系统将这个对象的 isa 指针指向这个新诞生的派生类，因此这个对象就成为该派生类的对象了，因而在该对象上对 setter 的调用就会调用重写的 setter，从而激活键值通知机制。此外，派生类还重写了 dealloc 方法来释放资源。
在你添加观察的时候呢，系统就创建一个派生类，然后派生类重写setter，class等方法，然后把指向原本的类指针指向派生类。由于重写了class类，这样你就以为是原来的类了。重写seeter方法呢，就是为了实现观察对象的改变

