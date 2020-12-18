//
//  VideoChatViewController.m
//  Wuji iOS Tutorial Objective-C
//
//  Created by 3 on 20/12/17.
//  Copyright © 2020 Wuji. All rights reserved.
//

#import "VideoChatViewController.h"

@interface VideoChatViewController ()

@property (strong, nonatomic) WujiRtcEngineKit *wujiKit;
@property (weak, nonatomic) IBOutlet UIView *localVideo;
@property (weak, nonatomic) IBOutlet UIView *remoteVideo;
@property (weak, nonatomic) IBOutlet UIView *controlButtons;
@property (weak, nonatomic) IBOutlet UIImageView *remoteVideoMutedIndicator;
@property (weak, nonatomic) IBOutlet UIImageView *localVideoMutedBg;
@property (weak, nonatomic) IBOutlet UIImageView *localVideoMutedIndicator;

@end

@implementation VideoChatViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setupButtons];
    [self hideVideoMuted];
    [self initializeWujiEngine];
    [self setupVideo];
    [self setupLocalVideo];
    [self joinChannel];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)initializeWujiEngine {
    self.wujiKit = [WujiRtcEngineKit sharedEngineWithAppId:appID delegate:self];
}

- (void)setupVideo {
    [self.wujiKit enableVideo];
    // Default mode is disableVideo
    
    // Set up the configuration such as dimension, frame rate, bit rate and orientation
    WujiVideoEncoderConfiguration *encoderConfiguration =
    [[WujiVideoEncoderConfiguration alloc] initWithSize:WujiVideoDimension640x360
                                               frameRate:WujiVideoFrameRateFps15
                                                 bitrate:WujiVideoBitrateStandard
                                         orientationMode:WujiVideoOutputOrientationModeAdaptative];
    [self.wujiKit setVideoEncoderConfiguration:encoderConfiguration];
}

- (void)setupLocalVideo {
    WujiRtcVideoCanvas *videoCanvas = [[WujiRtcVideoCanvas alloc] init];
    videoCanvas.uid = 0;
    // UID = 0 means we let Wuji pick a UID for us
    
    videoCanvas.view = self.localVideo;
    videoCanvas.renderMode = WujiVideoRenderModeHidden;
    [self.wujiKit setupLocalVideo:videoCanvas];
    // Bind local video stream to view
}

- (void)joinChannel {
    [self.wujiKit joinChannelByToken:token channelId:@"demoChannel1" info:nil uid:0 joinSuccess:^(NSString *channel, NSUInteger uid, NSInteger elapsed) {
        // Join channel "demoChannel1"
    }];
    // The UID database is maintained by your app to track which users joined which channels. If not assigned (or set to 0), the SDK will allocate one and returns it in joinSuccessBlock callback. The App needs to record and maintain the returned value as the SDK does not maintain it.
    
    [self.wujiKit setEnableSpeakerphone:YES];
    [UIApplication sharedApplication].idleTimerDisabled = YES;
}


/// Callback to handle the event such when the first frame of a remote video stream is decoded on the device.
/// @param engine - RTC engine instance
/// @param uid - user id
/// @param size - the height and width of the video frame
/// @param elapsed - lapsed Time elapsed (ms) from the local user calling JoinChannel method until the SDK triggers this callback.
- (void)rtcEngine:(WujiRtcEngineKit *)engine firstRemoteVideoDecodedOfUid:(NSUInteger)uid size: (CGSize)size elapsed:(NSInteger)elapsed {
    if (self.remoteVideo.hidden) {
        self.remoteVideo.hidden = NO;
    }
    
    WujiRtcVideoCanvas *videoCanvas = [[WujiRtcVideoCanvas alloc] init];
    videoCanvas.uid = uid;
    // Since we are making a simple 1:1 video chat app, for simplicity sake, we are not storing the UIDs. You could use a mechanism such as an array to store the UIDs in a channel.
    
    videoCanvas.view = self.remoteVideo;
    videoCanvas.renderMode = WujiVideoRenderModeHidden;
    [self.wujiKit setupRemoteVideo:videoCanvas];
    // Bind remote video stream to view
    [self.wujiKit startPreview];
}

- (void)rtcEngine:(WujiRtcEngineKit *)engine remoteVideoStateChangedOfUid:(NSUInteger)uid state:(WujiVideoRemoteState)state reason:(WujiVideoRemoteStateReason)reason elapsed:(NSInteger)elapsed
{
    NSLog(@"remoteVideoStateChangedOfUid %@ %@ %@", @(uid), @(state), @(reason));
}

- (IBAction)hangUpButton:(UIButton *)sender {
    [self leaveChannel];
}



///  Leave the channel and handle UI change when it is done.
- (void)leaveChannel {
    [self.wujiKit leaveChannel:^(WujiChannelStats *stat) {
        [self hideControlButtons];
        [UIApplication sharedApplication].idleTimerDisabled = NO;
        [self.remoteVideo removeFromSuperview];
        [self.localVideo removeFromSuperview];
    }];
}


/// Callback to handle an user offline event.
/// @param engine - RTC engine instance
/// @param uid - user id
/// @param reason - why is the user offline
- (void)rtcEngine:(WujiRtcEngineKit *)engine didOfflineOfUid:(NSUInteger)uid reason:(WujiUserOfflineReason)reason {
    self.remoteVideo.hidden = true;
}

- (void)setupButtons {
    [self performSelector:@selector(hideControlButtons) withObject:nil afterDelay:3];
    UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(remoteVideoTapped:)];
    [self.view addGestureRecognizer:tapGestureRecognizer];
    self.view.userInteractionEnabled = true;
}

- (void)hideControlButtons {
    self.controlButtons.hidden = true;
}

- (void)remoteVideoTapped:(UITapGestureRecognizer *)recognizer {
    if (self.controlButtons.hidden) {
        self.controlButtons.hidden = false;
        [self performSelector:@selector(hideControlButtons) withObject:nil afterDelay:3];
    }
}

- (void)resetHideButtonsTimer {
    [VideoChatViewController cancelPreviousPerformRequestsWithTarget:self];
    [self performSelector:@selector(hideControlButtons) withObject:nil afterDelay:3];
}

- (IBAction)didClickMuteButton:(UIButton *)sender {
    sender.selected = !sender.selected;
    [self.wujiKit muteLocalAudioStream:sender.selected];
    [self resetHideButtonsTimer];
}

- (IBAction)didClickVideoMuteButton:(UIButton *)sender {
    sender.selected = !sender.selected;
    [self.wujiKit muteLocalVideoStream:sender.selected];
    self.localVideo.hidden = sender.selected;
    self.localVideoMutedBg.hidden = !sender.selected;
    self.localVideoMutedIndicator.hidden = !sender.selected;
    [self resetHideButtonsTimer];
}


/// A callback to handle muting of the audio
/// @param engine  - RTC engine instance
/// @param muted  - YES if muted; NO otherwise
/// @param uid  - user id
- (void)rtcEngine:(WujiRtcEngineKit *)engine didVideoMuted:(BOOL)muted byUid:(NSUInteger)uid {
    self.remoteVideo.hidden = muted;
    self.remoteVideoMutedIndicator.hidden = !muted;
}

- (void) hideVideoMuted {
    self.remoteVideoMutedIndicator.hidden = true;
    self.localVideoMutedBg.hidden = true;
    self.localVideoMutedIndicator.hidden = true;
}

- (IBAction)didClickSwitchCameraButton:(UIButton *)sender {
    sender.selected = !sender.selected;
    [self.wujiKit switchCamera];
    [self resetHideButtonsTimer];
}
@end
