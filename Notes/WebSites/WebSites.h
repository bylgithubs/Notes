//
//  WebSites.h
//  Notes
//
//  Created by Civet on 2020/12/15.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef WebSites_h
#define WebSites_h


#endif /* WebSites_h */

NFC相关：
NFC部分介绍：
ISO18092 system codes for NFC Tag Reader Session
ISO7816 application identifiers for NFC Tag Reader Session
iOS NFC功能集成及详解:https://www.jianshu.com/p/c1b7e9062fee
iOS之NFC使用 https://www.jianshu.com/p/09e4d40f10fe
https://www.jianshu.com/p/7822103337ae/
https://blog.csdn.net/liwei16611/article/details/89081817
https://developer.apple.com/documentation/corenfc/nfctagreadersession?language=objc
https://github.com/janlionly/NFCReaderWriter/blob/master/NFCReaderWriterDemo/Info.plist
https://blog.csdn.net/longxiying/article/details/110879055
https://developer.android.com/guide/topics/connectivity/nfc/advanced-nfc
https://github.com/treastrain/TRETJapanNFCReader
https://www.ansi.org/about/roles/registration-program/rid
https://blog.csdn.net/lion456/article/details/40298521
https://wiki.nfc.im/
http://m.wdfxw.net/doc99847332.htm
https://jia.je/hardware/2020/05/10/mifare-classic-ndef/
http://icivetapps.efoxconn.com/wiki/index.php/NFC%E6%B5%81%E7%A8%8B

NFC注意事项：
NFC最低支持硬件iPhone7或者iPhone7Plus，最低支持系统为iOS11
需要开启一个session，与其他session类似，同时只能开启一个，系统会强制推出一个NFC的识别界面
需要App完全在前台模式，iPhoneX之后机型，支持后台读取
每个session最多扫描60s，超时需再次开启新session
配置读取单个或多个Tag，配置为单个时，会在读取到第一个Tag时自动结束session

NFC是一个大的规范，目前有协议文档中有规范支援14443A/B，15693 和Felica这三个协议，身份证属于14443B类型的卡片，所以从链路层上来说，是支援身份证读取的。但是有一个问题，身份证是一个智能卡，上层通信要基于7816协议。7816协议中有对访问权限进行限制。想要访问身份证中的内容涉及到一系列的鉴权过程，如果没有相应的秘钥是无法访问其中的内容的。

