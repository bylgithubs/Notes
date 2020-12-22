//
//  StoryboardAndXib.h
//  Notes
//
//  Created by Civet on 2020/12/22.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef StoryboardAndXib_h
#define StoryboardAndXib_h


#endif /* StoryboardAndXib_h */

//TestView.xib
//storyboard跳转到xib
TestViewController *TestVC = [[TestViewController alloc] initWithNibName:@"TestView" bundle:nil];
[self presentViewController:TestVC animated:YES completion:^{
    
}];
//TestViewController.stoaryboard
//xib跳转到storyboard
UIStoryboard *story = [UIStoryboard storyboardWithName:@"TestViewController" bundle:nil];
TestViewController *testVC = [story instantiateViewControllerWithIdentifier:@"TestViewController"];
[self presentViewController:testVC animated:YES completion:^{
    testVC.view.backgroundColor = [UIColor grayColor];
}];
