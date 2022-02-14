//
//  CircleCollectionView.h
//  Notes
//
//  Created by BaoYu Liao on 2021/7/12.
//  Copyright © 2021 PersonalONBYL. All rights reserved.
//

#ifndef CircleCollectionView_h
#define CircleCollectionView_h

#import "CircleCollectionViewController.h"
#import <iCarousel/iCarousel.h>

#define SCREEN_HEIGHT_V0 [UIScreen mainScreen].bounds.size.width

@interface CircleCollectionViewController () <iCarouselDataSource, iCarouselDelegate>

@property (nonatomic, strong) iCarousel *iCarousel;

@property (nonatomic, assign) NSInteger currentOffsetZeroIndex;
@property (nonatomic, assign) NSInteger itemCount;

@end

@implementation CircleCollectionViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    self.iCarousel = [[iCarousel alloc] initWithFrame:self.view.bounds];
    self.iCarousel.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    self.iCarousel.type = iCarouselTypeCustom;
    self.itemCount = 5;
    self.iCarousel.vertical = YES;
    self.iCarousel.scrollSpeed = 0.5;
    self.iCarousel.delegate = self;
    self.iCarousel.dataSource = self;
    [self.view addSubview:self.iCarousel];
}

- (NSInteger)numberOfItemsInCarousel:(iCarousel *)carousel {
    return self.itemCount;
}
- (UIView *)carousel:(iCarousel *)carousel viewForItemAtIndex:(NSInteger)index reusingView:(nullable UIView *)view {
    UIView *view1 = [UIView new];
    UILabel *label = [UILabel new];
    label.frame = CGRectMake(0, 0, 50, 50);
    label.textAlignment = NSTextAlignmentCenter;
    label.text = [NSString stringWithFormat:@"%ld",self.itemCount--];
    label.textColor = [UIColor redColor];
    view1.backgroundColor = [UIColor grayColor];
    view1.frame = CGRectMake(0, 0, 50, 50);
    [view1 addSubview:label];
    //view = view1;
    return view1;
}

- (CATransform3D)carousel:(iCarousel *)carousel itemTransformForOffset:(CGFloat)offset baseTransform:(CATransform3D)transform
{
    //[self updateItemViewsAlphaWithCarousel:carousel];
    if (offset == 0) {
        self.currentOffsetZeroIndex = carousel.currentItemIndex;
    }
//    transform = CATransform3DTranslate(transform, fabsf(offset) * 50, offset * carousel.itemWidth + 40, 0.0);
//    return transform;
//    //implement 'flip3D' style carousel
//    transform = CATransform3DRotate(transform, M_PI / 8.0f, 0.0f, 1.0f, 0.0f);
//    return CATransform3DTranslate(transform, 0.0f, 0.0f, offset * carousel.itemWidth);
    
    CGFloat count = 5;//[self circularCarouselItemCount];
//    CGFloat spacing = [self valueForOption:iCarouselOptionSpacing withDefault:1.0];
    CGFloat arc = M_PI * 0.6;//[self valueForOption:iCarouselOptionArc withDefault:M_PI * 1.0];
    CGFloat radius = (SCREEN_HEIGHT_V0 - 50) * 0.6;
    CGFloat angle = [self carousel:carousel valueForOption:iCarouselOptionAngle withDefault:arc / count];
    
//    if (carousel.type == iCarouselTypeInvertedWheel)
//    {
    radius = -radius;
    angle = -angle;
//    }
    
//    MSLogD(@"itemTransformForOffset - %.2f - %.2f", carousel.scrollOffset, offset);

    transform = CATransform3DTranslate(transform, radius * cos(angle * offset), radius * sin(angle * offset), 0.0);
    transform = CATransform3DTranslate(transform, -radius, 0, offset * 0.01);
    return transform;
}

- (CGFloat)carousel:(iCarousel *)carousel valueForOption:(iCarouselOption)option withDefault:(CGFloat)value
{
    //customize carousel display
    switch (option)
    {
        case iCarouselOptionWrap:
        {
            //normally you would hard-code this to YES or NO
            return YES;
        }
        case iCarouselOptionArc:
        {
            return 2 * M_PI * 0.5;
        }
        case iCarouselOptionSpacing:
        {
            //add a bit of spacing between the item views
            return value * 1.5 ;
        }
//        case iCarouselOptionRadius:
//        {
//            //add a bit of spacing between the item views
//            return value;
//        }
        case iCarouselOptionCount:
        {
            //add a bit of spacing between the item views
            return 1;
        }
//        case iCarouselOptionFadeMax:
//        {
//            if (carousel.type == iCarouselTypeCustom)
//            {
//                //set opacity based on distance from camera
//                return 0.0f;
//            }
//            return value;
//        }
        default:
        {
            return value;
        }
    }
}

#pragma mark ---

- (void)updateItemViewsAlphaWithCarousel:(iCarousel *)carousel {
    CGFloat currentOffset = [carousel offsetForItemAtIndex:carousel.currentItemIndex];
    YDHomeCardView *view = (YDHomeCardView *)[carousel itemViewAtIndex:carousel.currentItemIndex];
    //修改alpha
//    CGFloat bgAlpha = 1.f;
//    CGFloat littleAlpha = 0.f;
//    if (fabs(currentOffset) > 0) {
//        bgAlpha = 0.5 - fabs(currentOffset);
//        littleAlpha = 0.5 + fabs(currentOffset);
//    }
//    view.bgView.alpha = bgAlpha * 2.0;
//    view.littleView.alpha = littleAlpha;
//    //修改alpha
    
    //修改 transform
    CGFloat scaleDistance = 0.8f;
    CGFloat scale = 1.f + scaleDistance;
    if (fabs(currentOffset) > 0) {//0.5是切换index 的offset -0.5 ---- +0.5  顺时针+ 逆时针-
        scale = scale - fabs(currentOffset) * scaleDistance / 0.5;  //缩小cell尺寸
        if (!self.isgetRemoteData) {
            view.littleView.image = [UIImage imageNamed:@"home_card_small_placeholder"];
        }
    } else {
        if (!self.isgetRemoteData) {
            view.littleView.image = [UIImage imageNamed:@"home_card_big_placeholder"];
        }
    }
    NSLog(@"scale================%f----:%f",scale,currentOffset);
    view.littleView.transform = CGAffineTransformMakeScale(scale, scale);
}

@end

//自定义UICollectionViewCell尺寸delegate
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    return CGSizeMake(DWF(80), DWF(60));
}


#endif /* CircleCollectionView_h */
