//
//  Message.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2017 Wuji. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(int, MessageType) {
    MessageTypeInfo = 0,
    MessageTypeError = 1
};

@interface Message: NSObject
@property (assign, nonatomic) MessageType type;
@property (copy, nonatomic) NSString *text;

+ (instancetype)messageWithText:(NSString *)text type:(MessageType)type;
@end
