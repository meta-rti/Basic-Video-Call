//
//  KeyCenter.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2020年 Wuji. All rights reserved.
//

#import "KeyCenter.h"

@implementation KeyCenter
+ (NSString *)AppId {
    return @"123";
}

// assign token to nil if you have not enabled app certificate
+ (NSString *)Token {
    return @"";
}
@end
