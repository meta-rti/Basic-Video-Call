//
//  VideoChatViewController.m
//  Meta Mac Tutorial Objective-C
//
//  Created by 3 on 2020/12/17.
//  Portions Copyright (c) 2020 Meta-co. All rights reserved.
//

#import "VideoChatViewController.h"
#include "meta_video_call.h"
#include "engine_event_handler.h"

@interface VideoChatViewController ()<RTCEngineEventDelegate>{
    std::unique_ptr<meta::rtc::MetaVideoCall> video_call_;
    meta::rtc::RTCEngineEventHandler handler_observer_;
}
@property (weak) IBOutlet NSView *localVideo;
@property (weak) IBOutlet NSView *remoteVideo;
@property (weak) IBOutlet NSView *controlButtons;
@property (weak) IBOutlet NSImageView *remoteVideoMutedIndicator;
@property (weak) IBOutlet NSImageView *localVideoMutedBg;
@property (weak) IBOutlet NSImageView *localVideoMutedIndicator;

@property (nonatomic) BOOL muteAudio;
@property (nonatomic) BOOL muteVideo;
@property (nonatomic) BOOL screenShare;

@property (nonatomic,assign)NSUInteger remoteUid;


@end

@implementation VideoChatViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    video_call_ = std::make_unique<meta::rtc::MetaVideoCall>();
    
    self.view.wantsLayer = YES;
    self.remoteVideo.wantsLayer = YES;
    self.localVideo.wantsLayer = YES;
    
    [self setupButtons];
    [self hideVideoMuted];
    [self initializeMetaEngine];
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

- (void)initializeMetaEngine {
    handler_observer_._delegate = self;
    video_call_->SetEngineEventHandler(&handler_observer_);
    video_call_->InitializeEngine();
}

- (void)setupVideo {
    
    video_call_->EnableVideo();
    
    meta::rtc::VideoEncoderConfiguration config{};
    config.dimensions = meta::rtc::VideoDimensions{640,480};
    config.frameRate = meta::rtc::FRAME_RATE_FPS_15;
    config.bitrate = meta::rtc::STANDARD_BITRATE;
    config.orientationMode = meta::rtc::ORIENTATION_MODE_ADAPTIVE;
    config.minFrameRate = -1;
    config.minBitrate = meta::rtc::DEFAULT_MIN_BITRATE;
    config.minBitrate = meta::rtc::VIDEO_MIRROR_MODE_AUTO;
    video_call_->SetVideoEncoderConfig(config);
}

- (void)setupLocalVideo {

    meta::rtc::VideoCanvas canvas{};
    canvas.uid = 0;
    canvas.view = (meta::rtc::view_t)CFBridgingRetain(self.localVideo);
    canvas.renderMode = meta::rtc::RENDER_MODE_HIDDEN;
    video_call_->SetupLocalCanvas(canvas);
    video_call_->StartPreview();
}

- (void)joinChannel {
    std::string channelName = "default_channel";
    video_call_->JoinChannel(channelName, 0);
}

- (IBAction)didClickHangUpButton:(NSButton *)sender {
    [self leaveChannel];
}

- (void)leaveChannel {
    video_call_->LeaveChannel();
    meta::rtc::VideoCanvas canvas{};
    video_call_->SetupLocalCanvas(canvas);
    [self.remoteVideo removeFromSuperview];
    [self.localVideo removeFromSuperview];
    [self.view.window close];
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
    video_call_->MuteLocalAudioStream(self.muteAudio);
    if (self.muteAudio) {
        [sender setImage:[NSImage imageNamed:@"muteButtonSelected"]];
    } else {
        [sender setImage:[NSImage imageNamed:@"muteButton"]];
    }
}

- (IBAction)didClickVideoMuteButton:(NSButton *)sender {
    self.muteVideo = !self.muteVideo;
    video_call_->MuteLocalVideoStream(self.muteVideo);
    
    if (self.muteVideo) {
        [sender setImage:[NSImage imageNamed:@"videoMuteButtonSelected"]];
    } else {
        [sender setImage:[NSImage imageNamed:@"videoMuteButton"]];
    }
    self.localVideo.hidden = self.muteVideo;
    self.localVideoMutedBg.hidden = !(self.muteVideo);
    self.localVideoMutedIndicator.hidden = !(self.muteVideo);
}



- (void)hideVideoMuted {
    self.remoteVideoMutedIndicator.hidden = true;
    self.localVideoMutedBg.hidden = true;
    self.localVideoMutedIndicator.hidden = true;
}

- (IBAction)didClickScreenShareButton:(NSButton *)sender {
    self.screenShare = !self.screenShare;
    if (self.screenShare) {
        [sender setImage:[NSImage imageNamed:@"screenShareButtonSelected"]];
        meta::rtc::Rectangle rect{0,0,0,0};
        meta::rtc::VideoDimensions dimes{640,480};
        meta::rtc::ScreenCaptureParameters params{dimes,5,meta::rtc::STANDARD_BITRATE,true};
        video_call_->startScreenCaptureByDisplayId(CGMainDisplayID(), rect, params);
    } else {
        [sender setImage:[NSImage imageNamed:@"screenShareButton"]];
        video_call_->StopScreenCapture();
    }
}

#pragma mark - RTCEngineEventDelegate

- (void)joinChannel:(NSString *)channel uid:(NSUInteger)uid elapsed:(int)elapsed {
    
}
- (void)userDidOffline:(NSUInteger)uid reason:(meta::rtc::USER_OFFLINE_REASON_TYPE)reason {
    if (self.remoteUid != uid) {
        return;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        self.remoteVideo.hidden = true;
    });
}
- (void)user:(NSUInteger)uid muteVideo:(BOOL)mute {
    dispatch_async(dispatch_get_main_queue(), ^{
        self.remoteVideo.hidden = mute;
        self.remoteVideoMutedIndicator.hidden = !mute;
    });
}
- (void)userJoined:(NSUInteger) uid elapsed:(int)elapsed {
    dispatch_async(dispatch_get_main_queue(), ^{
        if (self.remoteVideo.hidden)
            self.remoteVideo.hidden = false;
        self.remoteUid = uid;
        meta::rtc::VideoCanvas canvas{};
        canvas.uid = uid;
        canvas.view = (meta::rtc::view_t)CFBridgingRetain(self.remoteVideo);
        canvas.renderMode = meta::rtc::RENDER_MODE_HIDDEN;
        self->video_call_->SetRemoteVideoCanvas(canvas);
        
    });
}

- (void)deviceOnChanged:(const char *)deviceID type:(meta::rtc::MEDIA_DEVICE_TYPE)type state:(int)state {
}


@end
