//
//  VideoViewLayouter.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2020年 Wuji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "VideoSession.h"

@interface VideoViewLayouter : NSObject
@property (strong, nonatomic) UIView *selfView;
@property (assign, nonatomic) CGSize selfSize;
@property (assign, nonatomic) CGSize targetSize;

@property (strong, nonatomic) NSArray<UIView *> *videoViews;
@property (strong, nonatomic) UIView *fullView;
@property (strong, nonatomic) UIView *containerView;

- (void)layoutVideoViews;
- (NSInteger)responseIndexOfLocation:(CGPoint)location;
@end
