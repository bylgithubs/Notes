//
//  DealWithImageArithmetic.h
//  Notes
//
//  Created by Civet on 2020/7/20.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef DealWithImageArithmetic_h
#define DealWithImageArithmetic_h


#endif /* DealWithImageArithmetic_h */
/*
 
 //通用图片处理方法，防止图片压缩变形，mult为:图片宽高/imagView宽高的比例，用于判断是否为长图,返回UIImageView.
 + (UIImageView *)imageViewPictureProcessing:(UIImageView *)imageView image:(UIImage *)image multiple:(CGFloat)mult imageViewMaxWidth:(NSInteger)maxWidth imageViewMinWidth:(NSInteger)minWidth imageViewMaxHeight:(NSInteger)maxHeight imageViewMinHeight:(NSInteger)minHeight
 {
 if (mult < 1) {
 mult = 3;       //判断长图倍率，小于mult正常显示，大于mult算长图截取显示
 }
 CGSize oldImageSize = image.size;
 CGSize newImageSize = oldImageSize;
 CGFloat scaleMin = MIN(oldImageSize.width/minWidth, oldImageSize.height/minHeight);
 CGFloat scaleMax = MAX(oldImageSize.width/maxWidth, oldImageSize.height/maxHeight);
 CGFloat imageViewMult = maxWidth/maxHeight;
 CGFloat picMult = oldImageSize.width/oldImageSize.height;
 if(oldImageSize.width > 0 || oldImageSize.height > 0)
 {
 CGFloat actualMult;     //图片倍率，图片宽高与imageView宽高的比值
 //计算图片倍率
 if (picMult > 1) {
 actualMult = picMult/imageViewMult;
 } else {
 actualMult = imageViewMult/picMult;
 }
 NSData *data = nil;
 //正常显示图片尺寸，等比例放缩
 if (actualMult <= mult) {
 newImageSize.width = oldImageSize.width/scaleMax;
 newImageSize.height = oldImageSize.height/scaleMax;
 //放缩图片以适应imagView的大小
 data = [CommonMethods createThumbImage:image size:newImageSize percent:1];
 }
 else {
 //长图显示尺寸，太宽，则高度放缩到minHeight,宽高比例不变；太高，则宽度放缩到minWidth，宽高比例不变。
 newImageSize.width = oldImageSize.width/scaleMin;
 newImageSize.height = oldImageSize.height/scaleMin;
 data = [CommonMethods createThumbImage:image size:newImageSize percent:1];
 //截取部分长图显示
 if (newImageSize.width > maxWidth) {
 newImageSize.width = maxWidth;
 imageView.contentMode = UIViewContentModeLeft;
 }
 else{
 newImageSize.height = maxHeight;
 imageView.contentMode = UIViewContentModeTop;
 }
 imageView.layer.masksToBounds = YES;
 }
 image = [UIImage imageWithData:data];
 image = [ImageManager imageByCroppingWithImage:image interceptSize:newImageSize];
 imageView.image = image;
 imageView.frame = CGRectMake(imageView.frame.origin.x, imageView.frame.origin.y, newImageSize.width, newImageSize.height);
 }
 return imageView;
 }
 
 //通用图片处理方法，防止图片压缩变形，mult为:图片宽高/imagView宽高的比例，用于判断是否为长图,返回UImage.
 + (UIImage *)imageViewPictureProcessing:(UIImage *)image multiple:(CGFloat)mult imageMaxWidth:(NSInteger)maxWidth imageMinWidth:(NSInteger)minWidth imageMaxHeight:(NSInteger)maxHeight imageMinHeight:(NSInteger)minHeight
 {
 if (mult < 1) {
 mult = 3;       //判断长图倍率，小于mult正常显示，大于mult算长图截取显示
 }
 CGSize oldImageSize = image.size;
 CGSize newImageSize = oldImageSize;
 CGFloat scaleMin = MIN(oldImageSize.width/minWidth, oldImageSize.height/minHeight);
 CGFloat scaleMax = MAX(oldImageSize.width/maxWidth, oldImageSize.height/maxHeight);
 CGFloat imageViewMult = maxWidth/maxHeight;
 CGFloat picMult = oldImageSize.width/oldImageSize.height;
 if(oldImageSize.width > 0 || oldImageSize.height > 0)
 {
 CGFloat actualMult;     //图片倍率，图片宽高与imageView宽高的比值
 //计算图片倍率
 if (picMult > 1) {
 actualMult = picMult/imageViewMult;
 } else {
 actualMult = imageViewMult/picMult;
 }
 NSData *data = nil;
 //正常显示图片尺寸，等比例放缩
 if (actualMult <= mult) {
 newImageSize.width = oldImageSize.width/scaleMax;
 newImageSize.height = oldImageSize.height/scaleMax;
 //放缩图片以适应imagView的大小
 data = [CommonMethods createThumbImage:image size:newImageSize percent:1];
 }
 else {
 //长图显示尺寸，太宽，则高度放缩到minHeight,宽高比例不变；太高，则宽度放缩到minWidth，宽高比例不变。
 newImageSize.width = oldImageSize.width/scaleMin;
 newImageSize.height = oldImageSize.height/scaleMin;
 data = [CommonMethods createThumbImage:image size:newImageSize percent:1];
 //截取部分长图显示
 if (newImageSize.width > maxWidth) {
 newImageSize.width = maxWidth;
 }
 else{
 newImageSize.height = maxHeight;
 }
 }
 image = [UIImage imageWithData:data];
 image = [ImageManager imageByCroppingWithImage:image interceptSize:newImageSize];
 }
 return image;
 }
 
 
 //传入的参数：1、生成图片的大小 2、压缩比
 +(NSData *)createThumbImage:(UIImage *)image size:(CGSize )thumbSize percent:(float)percent
 {
 CGPoint thumbPoint = CGPointMake(0.0,0.0);
 UIGraphicsBeginImageContext(thumbSize);
 CGRect thumbRect = CGRectZero;
 thumbRect.origin = thumbPoint;
 thumbRect.size  = thumbSize;
 //    thumbRect.size.height = scaledHeight;
 [image drawInRect:thumbRect];
 
 UIImage *thumbImage = UIGraphicsGetImageFromCurrentImageContext();
 UIGraphicsEndImageContext();
 NSData *thumbImageData = UIImageJPEGRepresentation(thumbImage, percent);
 return thumbImageData;
 }
 
 //剪裁图片
 +(UIImage*)imageByCroppingWithImage:(UIImage*)myImage interceptSize:(CGSize)size
 {
 CGRect rect = CGRectMake(0,0,size.width,size.height);
 
 CGImageRef imageRef = myImage.CGImage;
 CGImageRef imagePartRef=CGImageCreateWithImageInRect(imageRef,rect);
 UIImage * cropImage=[UIImage imageWithCGImage:imagePartRef];
 CGImageRelease(imagePartRef);
 
 return cropImage;
 }
 
 */
