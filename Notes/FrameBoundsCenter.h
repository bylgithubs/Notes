//
//  FrameBoundsCenter.h
//  Notes
//
//  Created by Civet on 2020/7/20.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef FrameBoundsCenter_h
#define FrameBoundsCenter_h


#endif /* FrameBoundsCenter_h */
/*
 frame: 该view在父view坐标系统中的位置和大小。（参照点是，父亲的坐标系统）
 
 bounds：该view在本地坐标系统中的位置和大小。（参照点是，本地坐标系统，就相当于ViewB自己的坐标系统，以0,0点为起点）
 testView.bounds = CGRectMak(25,25,40,40);
 这句code 的意思也就是说把testView的左上角的那个原点坐标设置为(25, 25),
 (25, 25)这个坐标是针对testView内部空间的, 这个时候你在testView上面继续添加subView的话, 这个subView的位置就是参照这个(25, 25)了.
 
 center：该view的中心点在父view坐标系统中的位置和大小。（参照点是，父亲的坐标系统）

 */
