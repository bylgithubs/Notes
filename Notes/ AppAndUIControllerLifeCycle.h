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


application:didFinishLauchingWithOptions:
