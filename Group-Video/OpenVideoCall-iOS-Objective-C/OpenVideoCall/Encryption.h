//
//  EncryptionType.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2017 Wuji. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WujiRTCFramework/WujiRTCFramework.h>

typedef NS_ENUM(int, EncryptionType) {
    EncryptionTypeXTS128,
    EncryptionTypeXTS256,
    EncryptionTypeNone,
};

@interface Encryption : NSObject
@property (nonatomic, copy, readonly) NSString *modeString;
@property (nonatomic, readonly) WujiEncryptionMode modeValue;
@property (nonatomic, copy, readonly) NSString *description;
@property (nonatomic, assign) EncryptionType type;
@property (nonatomic, copy) NSString *secret;

+ (NSString *)modeStringWithType:(EncryptionType)type;
+ (NSString *)descriptionWithType:(EncryptionType)type;
+ (NSArray *)allTypesArray;
@end
