//
//  RoomViewController.h
//  OpenVideoCall
//
//  Created by GongYuhua on 2016/9/12.
//  Copyright © 2020年 Wuji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WujiRTCFramework_Debug/WujiRTCFramework_Debug.h>
#import "Encryption.h"
#import "Settings.h"

@class RoomViewController;
@protocol RoomVCDataSource <NSObject>
- (WujiRtcEngineKit *)roomVCNeedWujiKit;
- (Settings *)roomVCNeedSettings;
@end

@interface RoomViewController : UIViewController
@property (weak, nonatomic) id<RoomVCDataSource> dataSource;
@end
