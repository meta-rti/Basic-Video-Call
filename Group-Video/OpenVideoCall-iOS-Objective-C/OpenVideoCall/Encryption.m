//
//  EncryptionType.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2017 Wuji. All rights reserved.
//

#import "Encryption.h"
#import <WujiRTCFramework_Debug/WujiRTCFramework_Debug.h>

@implementation Encryption
- (NSString *)modeString {
    switch (_type) {
        case EncryptionTypeXTS128: return @"aes-128-xts"; break;
        case EncryptionTypeXTS256: return @"aes-256-xts"; break;
        case EncryptionTypeNone:   return nil;
    }
}

- (WujiEncryptionMode)modeValue {
    switch (_type) {
        case EncryptionTypeXTS128:
            return WujiEncryptionModeAES128XTS;
            break;
        case EncryptionTypeXTS256:
            return WujiEncryptionModeAES256XTS;
        default:
            return WujiEncryptionModeAES128XTS;
    }
}


- (NSString *)description {
    switch (_type) {
        case EncryptionTypeXTS128: return @"AES 128"; break;
        case EncryptionTypeXTS256: return @"AES 256"; break;
        case EncryptionTypeNone:   return nil;
    }
}

+ (NSString *)modeStringWithType:(EncryptionType)type {
    switch (type) {
        case EncryptionTypeXTS128: return @"aes-128-xts"; break;
        case EncryptionTypeXTS256: return @"aes-256-xts"; break;
        case EncryptionTypeNone:   return nil;
    }
}

+ (NSString *)descriptionWithType:(EncryptionType)type {
    switch (type) {
        case EncryptionTypeXTS128: return @"AES 128"; break;
        case EncryptionTypeXTS256: return @"AES 256"; break;
        case EncryptionTypeNone:   return nil;
    }
}

+ (NSArray *)allTypesArray {
    return @[@(EncryptionTypeXTS128), @(EncryptionTypeXTS256)];
}
@end
