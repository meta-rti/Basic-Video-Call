//
//  VideoView.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MediaInfo.h"

@interface VideoView : UIView
@property (assign, nonatomic) BOOL isVideoMuted;
@property (strong, nonatomic) UIView *videoView;
- (void)updateInfo:(MediaInfo *)info;
@end
