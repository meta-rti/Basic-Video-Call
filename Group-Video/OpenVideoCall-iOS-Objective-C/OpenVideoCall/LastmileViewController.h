//
//  LastmileViewController.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MetaRTCFramework/MetaRTCFramework.h>

@class LastmileViewController;
@protocol LastmileVCDataSource <NSObject>
- (MetaRtcEngineKit *)lastmileVCNeedMetaKit;

@end

@interface LastmileViewController : UITableViewController
@property (weak, nonatomic) id<LastmileVCDataSource> dataSource;
@end
