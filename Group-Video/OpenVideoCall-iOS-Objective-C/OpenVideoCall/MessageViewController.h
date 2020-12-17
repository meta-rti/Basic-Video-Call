//
//  MessageViewController.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2019 Wuji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Message.h"

@interface MessageViewController : UIViewController
- (void)appendInfo:(NSString *)text;
- (void)appendError:(NSString *)text;
@end
