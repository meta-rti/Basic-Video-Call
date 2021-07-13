//
//  VideoChatViewController.m
//  Wuji Mac Tutorial Objective-C
//
//  Created by 3 on 2020/12/17.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

#import "VideoChatViewController.h"

@interface VideoChatViewController ()

@property (strong, nonatomic) WujiRtcEngineKit *wujiKit;
@property (weak) IBOutlet NSView *localVideo;
@property (weak) IBOutlet NSView *remoteVideo;
@property (weak) IBOutlet NSView *controlButtons;
@property (weak) IBOutlet NSImageView *remoteVideoMutedIndicator;
@property (weak) IBOutlet NSImageView *localVideoMutedBg;
@property (weak) IBOutlet NSImageView *localVideoMutedIndicator;

@property (nonatomic) BOOL muteAudio;
@property (nonatomic) BOOL muteVideo;
@property (nonatomic) BOOL screenShare;

@end

@implementation VideoChatViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.wantsLayer = YES;
    self.remoteVideo.wantsLayer = YES;
    self.localVideo.wantsLayer = YES;
    
    [self setupButtons];
    [self hideVideoMuted];
    [self initializeWujiEngine];
    [self setupVideo];
    [self setupLocalVideo];
    [self joinChannel];
}

- (void)viewWillAppear {
    [super viewWillAppear];
    
    self.view.layer.backgroundColor = [NSColor blackColor].CGColor;
    self.remoteVideo.layer.backgroundColor = [NSColor clearColor].CGColor;
    self.localVideo.layer.backgroundColor = [NSColor clearColor].CGColor;
}

- (void)initializeWujiEngine {
    self.wujiKit = [WujiRtcEngineKit sharedEngineWithAppId:AppID delegate:self];
}

- (void)setupVideo {
    [self.wujiKit enableVideo];
    
    WujiVideoEncoderConfiguration *configuration =
        [[WujiVideoEncoderConfiguration alloc] initWithSize:WujiVideoDimension960x720
                                                   frameRate:WujiVideoFrameRateFps15
                                                     bitrate:WujiVideoBitrateStandard
                                             orientationMode:WujiVideoOutputOrientationModeAdaptative];
    
    [self.wujiKit setVideoEncoderConfiguration:configuration];
}

- (void)setupLocalVideo {
    WujiRtcVideoCanvas *videoCanvas = [[WujiRtcVideoCanvas alloc] init];
    videoCanvas.uid = 0;
    // UID = 0 means we let Wuji pick a UID for us
    
    videoCanvas.view = self.localVideo;
    videoCanvas.renderMode = WujiVideoRenderModeHidden;
    [self.wujiKit setupLocalVideo:videoCanvas];
    // Bind local video stream to view
    [self.wujiKit startPreview];
}

- (void)joinChannel {
    [self.wujiKit joinChannelByToken:Token channelId:@"demoChannel1" info:nil uid:0 joinSuccess:^(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed) {
        // Did join channel "demoChannel1"
    }];
    // The UID database is maintained by your app to track which users joined which channels. If not assigned (or set to 0), the SDK will allocate one and returns it in joinSuccessBlock callback. The App needs to record and maintain the returned value as the SDK does not maintain it.
}

- (void)rtcEngine:(WujiRtcEngineKit *)engine firstRemoteVideoDecodedOfUid:(NSUInteger)uid size: (CGSize)size elapsed:(NSInteger)elapsed {
    if (self.remoteVideo.hidden)
        self.remoteVideo.hidden = false;
    WujiRtcVideoCanvas *videoCanvas = [[WujiRtcVideoCanvas alloc] init];
    videoCanvas.uid = uid;
    // Since we are making a simple 1:1 video chat app, for simplicity sake, we are not storing the UIDs. You could use a mechanism such as an array to store the UIDs in a channel.
    
    videoCanvas.view = self.remoteVideo;
    videoCanvas.renderMode = WujiVideoRenderModeHidden;
    [self.wujiKit setupRemoteVideo:videoCanvas];
    // Bind remote video stream to view
}

- (IBAction)didClickHangUpButton:(NSButton *)sender {
    [self leaveChannel];
}

- (void)leaveChannel {
    [self.wujiKit leaveChannel:nil];
    [self.wujiKit setupLocalVideo:nil];
    [self.remoteVideo removeFromSuperview];
    [self.localVideo removeFromSuperview];
    self.wujiKit = nil;
    [self.view.window close];
}

- (void)rtcEngine:(WujiRtcEngineKit *)engine didOfflineOfUid:(NSUInteger)uid reason:(WujiUserOfflineReason)reason {
    self.remoteVideo.hidden = true;
}

- (void)setupButtons {
    [self performSelector:@selector(hideControlButtons) withObject:nil afterDelay:3];
    
    [self.remoteVideo addTrackingArea:[[NSTrackingArea alloc] initWithRect:self.remoteVideo.bounds
                                                                            options:NSTrackingMouseMoved | NSTrackingActiveInActiveApp | NSTrackingInVisibleRect
                                                                              owner:self
                                                                           userInfo:nil]];
    
    [self.controlButtons addTrackingArea:[[NSTrackingArea alloc] initWithRect:self.controlButtons.bounds
                                                                    options:NSTrackingMouseEnteredAndExited | NSTrackingActiveInActiveApp | NSTrackingInVisibleRect
                                                                      owner:self
                                                                   userInfo:nil]];
}

- (void)hideControlButtons {
    self.controlButtons.hidden = YES;
}

- (void)mouseMoved:(NSEvent *)theEvent {
    if (self.controlButtons.hidden) {
        self.controlButtons.hidden = NO;
        [self performSelector:@selector(hideControlButtons) withObject:nil afterDelay:3];
    }
}

- (void)mouseEntered:(NSEvent *)theEvent {
    [VideoChatViewController cancelPreviousPerformRequestsWithTarget:self];
}

- (void)mouseExited:(NSEvent *)theEvent {
    [self performSelector:@selector(hideControlButtons) withObject:nil afterDelay:3];
}

- (IBAction)didClickMuteButton:(NSButton *)sender {
    self.muteAudio = !self.muteAudio;
    [self.wujiKit muteLocalAudioStream:self.muteAudio];
    
    if (self.muteAudio) {
        [sender setImage:[NSImage imageNamed:@"muteButtonSelected"]];
    } else {
        [sender setImage:[NSImage imageNamed:@"muteButton"]];
    }
}

- (IBAction)didClickVideoMuteButton:(NSButton *)sender {
    self.muteVideo = !self.muteVideo;
    [self.wujiKit muteLocalVideoStream:self.muteVideo];
    
    if (self.muteVideo) {
        [sender setImage:[NSImage imageNamed:@"videoMuteButtonSelected"]];
    } else {
        [sender setImage:[NSImage imageNamed:@"videoMuteButton"]];
    }
    self.localVideo.hidden = self.muteVideo;
    self.localVideoMutedBg.hidden = !(self.muteVideo);
    self.localVideoMutedIndicator.hidden = !(self.muteVideo);
}

- (void)rtcEngine:(WujiRtcEngineKit *)engine didVideoMuted:(BOOL)muted byUid:(NSUInteger)uid {
    self.remoteVideo.hidden = muted;
    self.remoteVideoMutedIndicator.hidden = !muted;
}

- (void)hideVideoMuted {
    self.remoteVideoMutedIndicator.hidden = true;
    self.localVideoMutedBg.hidden = true;
    self.localVideoMutedIndicator.hidden = true;
}

- (IBAction)didClickDeviceSelectionButton:(NSButton *)sender {
    DeviceSelectionViewController *deviceSelectionViewController = [self.storyboard instantiateControllerWithIdentifier:@"DeviceSelectionViewController"];
    deviceSelectionViewController.wujiKit = self.wujiKit;
    // Pass in WujiRtcEngineKit
    [self presentViewControllerAsSheet:deviceSelectionViewController];
    // Segue to sheet view controller DeviceSelectionViewController
}

- (IBAction)didClickScreenShareButton:(NSButton *)sender {
    self.screenShare = !self.screenShare;
    if (self.screenShare) {
        [sender setImage:[NSImage imageNamed:@"screenShareButtonSelected"]];
        [self.wujiKit startScreenCaptureByDisplayId:CGMainDisplayID()
                                           rectangle:CGRectZero
                                          parameters:[[WujiScreenCaptureParameters alloc] init]];
    } else {
        [sender setImage:[NSImage imageNamed:@"screenShareButton"]];
        [self.wujiKit stopScreenCapture];
    }
}

@end
