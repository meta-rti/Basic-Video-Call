//
//  MsgCell.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "MessageCell.h"
#import "CommonExtension.h"

@interface MessageCell ()
@property (weak, nonatomic) IBOutlet UIView *colorView;
@property (weak, nonatomic) IBOutlet UILabel *messageLabel;
@end

@implementation MessageCell
- (void)setMessage:(Message *)message {
    self.colorView.backgroundColor = (message.type == MessageTypeInfo ? UIColor.WJMessageInfoColor : UIColor.WJMessageErrorColor);
    self.messageLabel.text = message.text;
}
@end
