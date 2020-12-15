//
//  VideoView.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2020年 Wuji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MediaInfo.h"

@interface VideoView : UIView
@property (assign, nonatomic) BOOL isVideoMuted;
@property (strong, nonatomic) UIView *videoView;
- (void)updateInfo:(MediaInfo *)info;
@end
