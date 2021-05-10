//
//  SceneDelegateAdaption.h
//  Notes
//
//  Created by BaoYu Liao on 2021/5/10.
//  Copyright © 2021 PersonalONBYL. All rights reserved.
//

#ifndef SceneDelegateAdaption_h
#define SceneDelegateAdaption_h

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    if (@available(iOS 13.0, *)) {
        
    } else {
        self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
        self.window.rootViewController = [[UITabBarController alloc] init];
        [self.window makeKeyAndVisible];
    }
    return YES;
}

- (void)scene:(UIScene *)scene willConnectToSession:(UISceneSession *)session options:(UISceneConnectionOptions *)connectionOptions {
    if ([scene isKindOfClass:[UIWindowScene class]]) {
        UIWindowScene *windowScene = (UIWindowScene *)scene;
        self.window = [[UIWindow alloc] initWithWindowScene:windowScene];
        UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:[ViewController new]];
        self.window.rootViewController = nav;
        [self.window makeKeyAndVisible];
    }
    // Use this method to optionally configure and attach the UIWindow `window` to the provided UIWindowScene `scene`.
    // If using a storyboard, the `window` property will automatically be initialized and attached to the scene.
    // This delegate does not imply the connecting scene or session are new (see `application:configurationForConnectingSceneSession` instead).
}

#endif /* SceneDelegateAdaption_h */
