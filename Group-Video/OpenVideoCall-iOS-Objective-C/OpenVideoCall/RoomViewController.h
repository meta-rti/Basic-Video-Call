//
//  RoomViewController.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2020年 Wuji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WujiRTCFramework/WujiRTCFramework.h>
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
