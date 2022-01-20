//
//  SettingsViewController.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MetaRTCFramework/MetaRTCFramework.h>
#import "Settings.h"

@class SettingsViewController;
@protocol SettingsVCDelegate <NSObject>
- (void)settingsVC:(SettingsViewController *)settingsVC didSelectDimension:(CGSize)dimension;
- (void)settingsVC:(SettingsViewController *)settingsVC didSelectFrameRate:(MetaVideoFrameRate)frameRate;
@end

@protocol SettingsVCDataSource <NSObject>
- (Settings *)settingsVCNeedSettings;
@end

@interface SettingsViewController : UITableViewController
@property (weak, nonatomic) id<SettingsVCDelegate> delegate;
@property (weak, nonatomic) id<SettingsVCDataSource> dataSource;
@end
