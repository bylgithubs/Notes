//
//  StoryboardAndXib.h
//  Notes
//
//  Created by Civet on 2020/12/22.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef StoryboardAndXib_h
#define StoryboardAndXib_h


#endif /* StoryboardAndXib_h */

//TestView.xib
//storyboard跳转到xib
TestViewController *TestVC = [[TestViewController alloc] initWithNibName:@"TestView" bundle:nil];
[self presentViewController:TestVC animated:YES completion:^{
    
}];
//TestViewController.stoaryboard
//xib跳转到storyboard
UIStoryboard *story = [UIStoryboard storyboardWithName:@"TestViewController" bundle:nil];
TestViewController *testVC = [story instantiateViewControllerWithIdentifier:@"TestViewController"];
[self presentViewController:testVC animated:YES completion:^{
    testVC.view.backgroundColor = [UIColor grayColor];
}];

//app初始化视图
---------------- didFinishLaunchingWithOptions -----------------
if (@available(iOS 13.0, *)) {
    
} else {
    self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    self.window.rootViewController = [[UITabBarController alloc] init];
    [self.window makeKeyAndVisible];
}

---------------- willConnectToSession -----------------
if ([scene isKindOfClass:[UIWindowScene class]]) {
    UIWindowScene *windowScene = (UIWindowScene *)scene;
    self.window = [[UIWindow alloc] initWithWindowScene:windowScene];
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:[ViewController new]];
    self.window.rootViewController = nav;
    [self.window makeKeyAndVisible];
}


//删除storyboard启动图缓存
NSError *error;
[NSFileManager.defaultManager removeItemAtPath:[NSString stringWithFormat:@"%@/Library/SplashBoard",NSHomeDirectory()] error:&error];
if (error) {
    NSLog(@"Failed to delete launch screen cache: %@",error);
}
[NSThread sleepForTimeInterval:5.0];//设置启动页面时间
