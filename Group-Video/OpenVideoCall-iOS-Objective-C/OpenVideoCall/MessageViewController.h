//
//  MessageViewController.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Message.h"

@interface MessageViewController : UIViewController
- (void)appendInfo:(NSString *)text;
- (void)appendError:(NSString *)text;
@end
