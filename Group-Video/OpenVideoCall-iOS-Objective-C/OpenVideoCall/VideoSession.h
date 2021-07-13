//
//  VideoSession.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WujiRTCFramework/WujiRTCFramework.h>

@interface VideoSession : NSObject
@property (assign, nonatomic) NSUInteger uid;
@property (strong, nonatomic) UIView *hostingView;
@property (strong, nonatomic) WujiRtcVideoCanvas *canvas;
@property (assign, nonatomic) CGSize size;
@property (assign, nonatomic) BOOL isVideoMuted;

+ (instancetype)localSession;
- (instancetype)initWithUid:(NSUInteger)uid;
- (void)updateMediaInfo:(CGSize)resolution fps:(NSInteger)fps;
@end
