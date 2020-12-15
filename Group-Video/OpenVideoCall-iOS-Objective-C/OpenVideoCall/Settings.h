//
//  Settings.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2019 Wuji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WujiRTCFramework_Debug/WujiRTCFramework_Debug.h>
#import "Encryption.h"

@interface Settings : NSObject
@property (nonatomic, strong) Encryption *encryption;
@property (nonatomic, assign) WujiVideoFrameRate frameRate;
@property (nonatomic, assign) CGSize dimension;
@property (nonatomic, copy) NSString *roomName;
@end
