//
//  ClearNavigationBgcShadowBtn.h
//  Notes
//
//  Created by BaoYu Liao on 2021/5/10.
//  Copyright © 2021 PersonalONBYL. All rights reserved.
//

#ifndef ClearNavigationBgcShadowBtn_h
#define ClearNavigationBgcShadowBtn_h

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self clearNavigationBackground:[UIColor clearColor]];
    self.navigationController.navigationBar.shadowImage = [[UIImage alloc] init];
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    UIBarButtonItem *backBtn = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.leftBarButtonItem = backBtn;
}

static char overlayKey;

- (UIView *)overlay
{
    return objc_getAssociatedObject(self, &overlayKey);
}

- (void)setOverlay:(UIView *)overlay
{
    objc_setAssociatedObject(self, &overlayKey, overlay, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)clearNavigationBackground:(UIColor *)backgroundColor {
    if (!self.overlay) {
        [self.navigationController.navigationBar setBackgroundImage:[UIImage new] forBarMetrics:UIBarMetricsDefault];
        self.overlay = [[UIView alloc] initWithFrame:CGRectMake(0, 0, CGRectGetWidth(self.navigationController.navigationBar.bounds), CGRectGetHeight(self.navigationController.navigationBar.bounds))];
        self.overlay.userInteractionEnabled = NO;
        [self.navigationController.navigationBar.subviews.firstObject insertSubview:self.overlay atIndex:0];
        self.overlay.bounds = self.navigationController.navigationBar.subviews.firstObject.bounds;
    }
    self.overlay.backgroundColor = backgroundColor;
}

#endif /* ClearNavigationBgcShadowBtn_h */
