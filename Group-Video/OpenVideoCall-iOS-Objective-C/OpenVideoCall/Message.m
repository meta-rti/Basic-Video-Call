//
//  Message.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2017 Wuji. All rights reserved.
//

#import "Message.h"

@implementation Message
+ (instancetype)messageWithText:(NSString *)text type:(MessageType)type {
    Message *message = [[Message alloc] init];
    message.text = text;
    message.type = type;
    return message;
}
@end
