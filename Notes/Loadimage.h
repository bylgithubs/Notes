//
//  Loadimage.h
//  Notes
//
//  Created by Civet on 2020/7/20.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef Loadimage_h
#define Loadimage_h


#endif /* Loadimage_h */
/*
 1:使用imageNamed:
 第一次读取的时候,会先把这个图片放到缓存当中,下次在使用到这个同名的图片时,直接从缓存中读取.
 优点:
 方便快捷,只有第一次使用的时候稍慢,接下来在使用就会快些.
 缺点:
 如果在当前工程中大量会大量的浪费内存空间
 UIImage *image = [UIImage imageNamed:@"v_red_heart_selected@3x"];
 //这种初始化方法可以直接不给出图片的具体名字,它会自动匹配
 2:使用initWithContentsOfFile:
 初始化图片时,每次都会根据路径去读取,不会占用内存,如果图片在当前工程中只使用一次,应该选择这个方法.
 */
