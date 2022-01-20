//
//  EncryptionType.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "Encryption.h"
#import <MetaRTCFramework/MetaRTCFramework.h>

@implementation Encryption
- (NSString *)modeString {
    switch (_type) {
        case EncryptionTypeXTS128: return @"aes-128-xts"; break;
        case EncryptionTypeXTS256: return @"aes-256-xts"; break;
        case EncryptionTypeNone:   return nil;
    }
}

- (MetaEncryptionMode)modeValue {
    switch (_type) {
        case EncryptionTypeXTS128:
            return MetaEncryptionModeAES128XTS;
            break;
        case EncryptionTypeXTS256:
            return MetaEncryptionModeAES256XTS;
        default:
            return MetaEncryptionModeAES128XTS;
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
