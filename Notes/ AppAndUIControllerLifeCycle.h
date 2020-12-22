//
//   AppAndUIControllerLifeCycle.h
//  Notes
//
//  Created by Civet on 2020/12/12.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef _AppAndUIControllerLifeCycle_h
#define _AppAndUIControllerLifeCycle_h


#endif /* _AppAndUIControllerLifeCycle_h */

ios app有5种状态，分别是：

1、Not running未运行：app没启动或被迫终止。

2、Inactive未激活：当前应用正在前台运行，但是并不接收事件（当前或许正在执行其它代码）。一般每当应用要从一个状态切换到另一个不同的状态时，中途过渡会短暂停留在此状态。唯一在此状态停留时间比较长的情况是：当用户锁屏时，或者系统提示用户去响应某些（诸如电话来电、有未读短信等）事件的时候。

3、Active激活：当前应用正在前台运行，并且接收事件。这是应用正在前台运行时所处的正常状态。

4、Backgroud后台：程序在后台而且能执行代码，大多数程序进入这个状态后会在在这个状态上停留一会。时间到之后会进入挂起状态(Suspended)。经过特殊的请求后可以长期处于Backgroud状态。

5、Suspended挂起：程序在后台不能执行代码。系统会自动把程序变成这个状态而且不会发出通知。当挂起时，程序还是停留在内存中的，当系统内存低时，系统就把挂起的程序清除掉，为前台程序提供更多的内存。

注意的一点是：对于从Not running状态直接进入到background状态的应用，在启动进入到background状态时，如果应用有界面，系统仍然会加载用户界面文件，
只是不会显示在应用的window上面。为了在程序中确定你的程序是进入到了foreground还是background，你可以在
application:didFinishLaunchingWithOptions: 方法中检测UIApplication类对象的applicationState属性，如果应用进入到了foreground，
则属性值为UIApplicationStateActive，如果进入到了background，则为UIApplicationStateBackground。

检测示例代码：
UIApplicationState state = [UIApplication sharedApplication].applicationState;
    return (state==UIApplicationStateActive || state==UIApplicationStateInactive );
 Not running    --------------------
    |                               |
 Inactive   ------  Background      |
    |                   |           |
 Active(foreground) Suspended   -----





- (BOOL)application:(UIApplication *)application willFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey,id> *)launchOptions{
    return YES;
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

---------------------------------------------------------------------------------------------------------------------------------------------

UIViewController生命周期：

@property(nonatomic,strong) UIView *customView;

//initWithCoder: 只要对象是从文件(xib或storyboard)解析来的，就会调用awakeFromNib 从xib或者storyboard加载完毕就会调用
- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self) {
        self.customView = [[UIView alloc] init];
        [self.view addSubview:self.customView];
        UILabel *label = [[UILabel alloc] init];
        [self.customView addSubview:label]; //在initWithCoder中往子视图中添加子视图无效
    }
    //NSLog(@"initWithCoder output self.view:%@",self.view);
    return self;
}

//
- (void)awakeFromNib{
    [super awakeFromNib];
    UILabel *label = [[UILabel alloc] init];
    [self.customView addSubview:label]; //有效
    //NSLog(@"awakeFromNib output self.view:%@",self.view);
}

//loadView中必须对sel.view进行实例化或将self.view指向一个实例化的视图，否则当self.view = nil时（初始为nil）,没有实例化，对该视图进行操作会造成死循环，
//使用self.view调用方法会崩溃
- (void)loadView{
    //[super loadView]; //方式一
    //self.view = [[UIView alloc] init];    //方式二
    self.view = [[UIView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];  //方式三 推荐
    self.view.backgroundColor = [UIColor grayColor]; //如果没有以上三种都没有使用，此次会导致死循环
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    UIView *view = [[UIView alloc] initWithFrame:self.view.frame];
    [self.view addSubview:view];    //重写了loadView方法，没有使用以上三种方式，此时self.view = nil，程序崩溃。
}

- (void)viewWillAppear:(BOOL)animated{
    
}

- (void)updateViewConstraints{
    
}

- (void)viewWillLayoutSubviews{
    
}

- (void)viewDidLayoutSubviews{
    
}

- (void)viewDidAppear:(BOOL)animated{
    
}

- (void)viewWillDisappear:(BOOL)animated{
    
}

- (void)viewDidDisappear:(BOOL)animated{
    
}

---------------------------------------------------------------------------------------------------------------------------------------------

//storyboard跳转到xib
TestViewController *TestVC = [[TestViewController alloc] initWithNibName:@"TestView2" bundle:nil];
[self presentViewController:TestVC animated:YES completion:^{
    
}];
//xib跳转到storyboard
UIStoryboard *story = [UIStoryboard storyboardWithName:@"TestViewController" bundle:nil];
TestViewController *testVC = [story instantiateViewControllerWithIdentifier:@"TestViewController"];
[self presentViewController:testVC animated:YES completion:^{
    testVC.view.backgroundColor = [UIColor grayColor];
}];
