//
//  GradientView.h
//  Notes
//
//  Created by BaoYu Liao on 2021/10/20.
//  Copyright © 2021 PersonalONBYL. All rights reserved.
//

#ifndef GradientView_h
#define GradientView_h

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface GradientView : UIView

@property (nonatomic, strong, readonly) CAGradientLayer *gradientLayer;

@end

NS_ASSUME_NONNULL_END



#import "GradientView.h"

@implementation GradientView

+ (Class)layerClass {
    return [CAGradientLayer class];
}

- (CAGradientLayer *)gradientLayer {
    return (CAGradientLayer *)self.layer;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end


#endif /* GradientView_h */
