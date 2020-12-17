//
//  LastmileViewController.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2019 Wuji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WujiRTCFramework/WujiRTCFramework.h>

@class LastmileViewController;
@protocol LastmileVCDataSource <NSObject>
- (WujiRtcEngineKit *)lastmileVCNeedWujiKit;

@end

@interface LastmileViewController : UITableViewController
@property (weak, nonatomic) id<LastmileVCDataSource> dataSource;
@end
