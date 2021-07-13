//
//  Message.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
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
