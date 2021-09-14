//
//  RoundCorner.h
//  Notes
//
//  Created by BaoYu Liao on 2021/9/14.
//  Copyright © 2021 PersonalONBYL. All rights reserved.
//

#ifndef RoundCorner_h
#define RoundCorner_h

typedef NS_OPTIONS(NSUInteger, UIRectCorner) {
    UIRectCornerTopLeft     = 1 << 0,
    UIRectCornerTopRight    = 1 << 1,
    UIRectCornerBottomLeft  = 1 << 2,
    UIRectCornerBottomRight = 1 << 3,
    UIRectCornerAllCorners  = ~0UL
};

//贝塞尔曲线画圆角
[self.view setupRoundedCornersWithcutCorners:UIRectCornerTopLeft | UIRectCornerTopRight cornerRadii:CGSizeMake(DWF(20), DWF(20)) borderColor:[UIColor clearColor] borderWidth:0];

- (void)setupRoundedCornersWithcutCorners:(UIRectCorner)rectCorner cornerRadii:(CGSize)cornerRadii borderColor:(UIColor *)borderColor borderWidth:(CGFloat)borderWidth {

    CAShapeLayer *mask=[CAShapeLayer layer];
    UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:self.bounds byRoundingCorners:rectCorner cornerRadii:cornerRadii];
    mask.path = path.CGPath;
    mask.frame = self.bounds;


    CAShapeLayer *borderLayer = [CAShapeLayer layer];
    borderLayer.path=path.CGPath;
    borderLayer.fillColor = [UIColor clearColor].CGColor;
    borderLayer.strokeColor = borderColor.CGColor;
    borderLayer.lineWidth = borderWidth;
    borderLayer.frame = self.bounds;
    self.layer.mask = mask;
    [self.layer addSublayer:borderLayer];
}


#endif /* RoundCorner_h */
