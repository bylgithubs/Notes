//
//  OtherFiles.h
//  Notes
//
//  Created by Civet on 2020/12/9.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef OtherFiles_h
#define OtherFiles_h


#endif /* OtherFiles_h */

//条形码扫描
//ZBarSDK已停更，可以使用下方的LBXZarSDK代替
https://github.com/MxABC/LBXZBarSDK.git

UIApplicationMain(argc, argv, nil, appDelegateClassName);
argc: 整数,用来统计bai你运行程序时送给dumain函数zhi的命令行参数dao的个数 　　* argv: 字符串数组，用来存zhuan放指向shu你的字符串参数的指针数组，每一个元素指向一个参数 　　argv[0] 指向程序运行的全路径名 　　argv[1] 指向在DOS命令行中执行程序名后的第一个字符串 　　argv[2] 指向执行程序名后的第二个字符串

app生命周期：
1.Not running：未运行
2.Inactive：未激活
3.Active：已激活
4.Background：后台运行
5.Suspend：挂起


UIController生命周期
按照执行顺序排列：

1. initWithCoder：通过nib文件初始化时触发。

2. awakeFromNib：nib文件被加载的时候，会发生一个awakeFromNib的消息到nib文件中的每个对象。

3. loadView：开始加载视图控制器自带的view。

4. viewDidLoad：视图控制器的view被加载完成。

5. viewWillAppear：视图控制器的view将要显示在window上。

6. updateViewConstraints：视图控制器的view开始更新AutoLayout约束。

7. viewWillLayoutSubviews：视图控制器的view将要更新内容视图的位置。

8. viewDidLayoutSubviews：视图控制器的view已经更新视图的位置。

9. viewDidAppear：视图控制器的view已经展示到window上。

10. viewWillDisappear：视图控制器的view将要从window上消失。

11. viewDidDisappear：视图控制器的view已经从window上消失。

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    if (@available(iOS 13.0, *)) {
        
    } else {
        self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
        self.window.backgroundColor = [UIColor whiteColor];
        HomeViewController *homeVC = [[HomeViewController alloc] init];
        self.window.rootViewController = homeVC;
        [self.window makeKeyAndVisible];;
    }

    return YES;
}

- (void)scene:(UIScene *)scene willConnectToSession:(UISceneSession *)session options:(UISceneConnectionOptions *)connectionOptions {
    // Use this method to optionally configure and attach the UIWindow `window` to the provided UIWindowScene `scene`.
    // If using a storyboard, the `window` property will automatically be initialized and attached to the scene.
    // This delegate does not imply the connecting scene or session are new (see `application:configurationForConnectingSceneSession` instead).
    UIWindowScene *windowScene = (UIWindowScene *)scene;
    self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    self.window = [[UIWindow alloc] initWithWindowScene:windowScene];   //方式一
    [self.window setWindowScene:windowScene];   //方式二
    self.window.backgroundColor = [UIColor whiteColor];
    self.window.rootViewController = [[HomeViewController alloc] init];
    [self.window makeKeyAndVisible];
}
------------------------------------------------------------------------------------------------------------------------------------------

