//
//  Settings.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2019 Wuji. All rights reserved.
//

#import "Settings.h"

@implementation Settings
- (instancetype)init {
    if (self = [super init]) {
        self.encryption = [[Encryption alloc] init];
    }
    return self;
}
@end
