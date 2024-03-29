//
//  RoomViewController.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MetaRTCFramework/MetaRTCFramework.h>
#import "Encryption.h"
#import "Settings.h"

@class RoomViewController;
@protocol RoomVCDataSource <NSObject>
- (MetaRtcEngineKit *)roomVCNeedMetaKit;
- (Settings *)roomVCNeedSettings;
@end

@interface RoomViewController : UIViewController
@property (weak, nonatomic) id<RoomVCDataSource> dataSource;
@end
