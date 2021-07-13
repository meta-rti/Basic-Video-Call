//
//  RoomOptionsViewController.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RoomOptions : NSObject
@property (assign, nonatomic) BOOL isDebugMode;
@end

@class RoomOptionsViewController;
@protocol RoomOptionsVCDelegate <NSObject>
- (void)roomOptions:(RoomOptionsViewController *)vc debugModeDidEnable:(BOOL)enable;
@end

@protocol RoomOptionsVCDataSource <NSObject>
- (RoomOptions *)roomOptionsVCNeedOptions;
@end

@interface RoomOptionsViewController : UITableViewController
@property (weak, nonatomic) id<RoomOptionsVCDataSource> dataSource;
@property (weak, nonatomic) id<RoomOptionsVCDelegate> delegate;
@end

