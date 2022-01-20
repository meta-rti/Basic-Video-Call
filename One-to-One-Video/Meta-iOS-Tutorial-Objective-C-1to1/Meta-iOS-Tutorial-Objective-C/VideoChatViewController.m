//
//  VideoChatViewController.m
//  Meta iOS Tutorial Objective-C
//
//  Created by 3 on 20/12/17.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "VideoChatViewController.h"

@interface VideoChatViewController ()

@property (strong, nonatomic) MetaRtcEngineKit *metaKit;
@property (weak, nonatomic) IBOutlet UIView *localVideo;
@property (weak, nonatomic) IBOutlet UIView *remoteVideo;
@property (weak, nonatomic) IBOutlet UIView *controlButtons;
@property (weak, nonatomic) IBOutlet UIImageView *remoteVideoMutedIndicator;
@property (weak, nonatomic) IBOutlet UIImageView *localVideoMutedBg;
@property (weak, nonatomic) IBOutlet UIImageView *localVideoMutedIndicator;
@property (nonatomic,assign)NSUInteger remoteUid;

@end

@implementation VideoChatViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setupButtons];
    [self hideVideoMuted];
    [self initializeMetaEngine];
    [self setupVideo];
    [self setupLocalVideo];
    [self joinChannel];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)initializeMetaEngine {
    self.metaKit = [MetaRtcEngineKit sharedEngineWithAppId:appID delegate:self];
}

- (void)setupVideo {
    [self.metaKit enableVideo];
    // Default mode is disableVideo
    
    // Set up the configuration such as dimension, frame rate, bit rate and orientation
    MetaVideoEncoderConfiguration *encoderConfiguration =
    [[MetaVideoEncoderConfiguration alloc] initWithSize:CGSizeMake(1920, 1080)
                                               frameRate:MetaVideoFrameRateFps15
                                                 bitrate:MetaVideoBitrateStandard
                                         orientationMode:MetaVideoOutputOrientationModeAdaptative];
    [self.metaKit setVideoEncoderConfiguration:encoderConfiguration];
}

- (void)setupLocalVideo {
    MetaRtcVideoCanvas *videoCanvas = [[MetaRtcVideoCanvas alloc] init];
    videoCanvas.uid = 0;
    // UID = 0 means we let Meta pick a UID for us
    
    videoCanvas.view = self.localVideo;
    videoCanvas.renderMode = MetaVideoRenderModeHidden;
    [self.metaKit setupLocalVideo:videoCanvas];
    // Bind local video stream to view
}

- (void)joinChannel {
    [self.metaKit joinChannelByToken:token channelId:@"demoChannel1" info:nil uid:0 joinSuccess:^(NSString *channel, NSUInteger uid, NSInteger elapsed) {
        // Join channel "demoChannel1"
    }];
    // The UID database is maintained by your app to track which users joined which channels. If not assigned (or set to 0), the SDK will allocate one and returns it in joinSuccessBlock callback. The App needs to record and maintain the returned value as the SDK does not maintain it.
    
    [self.metaKit setEnableSpeakerphone:YES];
    [UIApplication sharedApplication].idleTimerDisabled = YES;
}


/// Callback to handle the event such when the first frame of a remote video stream is decoded on the device.
/// @param engine - RTC engine instance
/// @param uid - user id
/// @param size - the height and width of the video frame
/// @param elapsed - lapsed Time elapsed (ms) from the local user calling JoinChannel method until the SDK triggers this callback.
- (void)rtcEngine:(MetaRtcEngineKit *)engine firstRemoteVideoDecodedOfUid:(NSUInteger)uid size: (CGSize)size elapsed:(NSInteger)elapsed {
    if (self.remoteVideo.hidden) {
        self.remoteVideo.hidden = NO;
        NSArray * subViews = self.remoteVideo.subviews;
        for (UIView * subview in subViews) {
            [subview removeFromSuperview];
        }
    }
    
    self.remoteUid = uid;
    MetaRtcVideoCanvas *videoCanvas = [[MetaRtcVideoCanvas alloc] init];
    videoCanvas.uid = uid;
    // Since we are making a simple 1:1 video chat app, for simplicity sake, we are not storing the UIDs. You could use a mechanism such as an array to store the UIDs in a channel.
    
    videoCanvas.view = self.remoteVideo;
    videoCanvas.renderMode = MetaVideoRenderModeHidden;
    [self.metaKit setupRemoteVideo:videoCanvas];
    // Bind remote video stream to view
    [self.metaKit startPreview];
}

- (void)rtcEngine:(MetaRtcEngineKit *)engine remoteVideoStateChangedOfUid:(NSUInteger)uid state:(MetaVideoRemoteState)state reason:(MetaVideoRemoteStateReason)reason elapsed:(NSInteger)elapsed
{
    NSLog(@"remoteVideoStateChangedOfUid %@ %@ %@", @(uid), @(state), @(reason));
}

- (IBAction)hangUpButton:(UIButton *)sender {
    [self leaveChannel];
}



///  Leave the channel and handle UI change when it is done.
- (void)leaveChannel {
    [self.metaKit leaveChannel:^(MetaChannelStats *stat) {
        [self hideControlButtons];
        [UIApplication sharedApplication].idleTimerDisabled = NO;
        [self.remoteVideo removeFromSuperview];
        [self.localVideo removeFromSuperview];
    }];
    [MetaRtcEngineKit destroy];
}


/// Callback to handle an user offline event.
/// @param engine - RTC engine instance
/// @param uid - user id
/// @param reason - why is the user offline
- (void)rtcEngine:(MetaRtcEngineKit *)engine didOfflineOfUid:(NSUInteger)uid reason:(MetaUserOfflineReason)reason {
    if (self.remoteUid == uid) {
        self.remoteVideo.hidden = true;
    }
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
    [self.metaKit muteLocalAudioStream:sender.selected];
    [self resetHideButtonsTimer];
}

- (IBAction)didClickVideoMuteButton:(UIButton *)sender {
    sender.selected = !sender.selected;
    [self.metaKit muteLocalVideoStream:sender.selected];
    self.localVideo.hidden = sender.selected;
    self.localVideoMutedBg.hidden = !sender.selected;
    self.localVideoMutedIndicator.hidden = !sender.selected;
    [self resetHideButtonsTimer];
}


/// A callback to handle muting of the audio
/// @param engine  - RTC engine instance
/// @param muted  - YES if muted; NO otherwise
/// @param uid  - user id
- (void)rtcEngine:(MetaRtcEngineKit *)engine didVideoMuted:(BOOL)muted byUid:(NSUInteger)uid {
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
    [self.metaKit switchCamera];
    [self resetHideButtonsTimer];
}
@end
