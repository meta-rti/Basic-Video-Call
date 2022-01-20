//
//  Settings.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MetaRTCFramework/MetaRTCFramework.h>
#import "Encryption.h"

@interface Settings : NSObject
@property (nonatomic, strong) Encryption *encryption;
@property (nonatomic, assign) MetaVideoFrameRate frameRate;
@property (nonatomic, assign) CGSize dimension;
@property (nonatomic, copy) NSString *roomName;
@end
