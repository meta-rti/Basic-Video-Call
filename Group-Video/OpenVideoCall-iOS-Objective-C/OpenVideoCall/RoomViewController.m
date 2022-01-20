//
//  RoomViewController.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "RoomOptionsViewController.h"
#import "MessageViewController.h"
#import "RoomViewController.h"
#import "VideoViewLayouter.h"
#import "VideoSession.h"
#import "AppDelegate.h"
#import "FileCenter.h"
#import "KeyCenter.h"

@interface RoomViewController () <MetaRtcEngineDelegate, RoomOptionsVCDelegate, RoomOptionsVCDataSource>
@property (weak, nonatomic) IBOutlet UIView *containerView;
@property (weak, nonatomic) IBOutlet UIView *messageTableContainerView;

@property (weak, nonatomic) IBOutlet UIButton *cameraButton;
@property (weak, nonatomic) IBOutlet UIButton *audioMixingButton;
@property (weak, nonatomic) IBOutlet UIButton *speakerPhoneButton;
@property (weak, nonatomic) IBOutlet UIButton *beautyButton;
@property (weak, nonatomic) IBOutlet UIButton *muteVideoButton;
@property (weak, nonatomic) IBOutlet UIButton *muteAudioButton;

@property (weak, nonatomic) IBOutlet UITapGestureRecognizer *backgroundDoubleTap;

@property (weak, nonatomic) MetaRtcEngineKit *metaKit;

@property (assign, nonatomic) BOOL isSwitchCamera;
@property (assign, nonatomic) BOOL isAudioMixing;
@property (assign, nonatomic) BOOL isBeauty;
@property (assign, nonatomic) BOOL isEarPhone;
@property (assign, nonatomic) BOOL isVideoMuted;
@property (assign, nonatomic) BOOL isAudioMuted;
@property (assign, nonatomic) BOOL isDebugMode;

@property (strong, nonatomic) NSMutableArray<VideoSession *> *videoSessions;
@property (strong, nonatomic) VideoSession *doubleClickFullSession;
@property (strong, nonatomic) VideoViewLayouter *videoViewLayouter;

@property (strong, nonatomic) RoomOptions *options;

@property (weak, nonatomic) MessageViewController *messageVC;
@property (weak, nonatomic) RoomOptionsViewController *optionsVC;
@property (weak, nonatomic) Settings *settings;
@end

@implementation RoomViewController
#pragma mark - Setter, Getter
- (void)setIsSwitchCamera:(BOOL)isSwitchCamera {
    [self.metaKit switchCamera];
}

- (void)setIsAudioMixing:(BOOL)isAudioMixing {
    if (_isAudioMixing == isAudioMixing) {
        return;
    }
    
    _isAudioMixing = isAudioMixing;
    self.audioMixingButton.selected = _isAudioMixing;
    if (_isAudioMixing) {
        // play music file
        [self.metaKit startAudioMixing:[FileCenter audioFilePath]
                               loopback:false
                                replace:false
                                  cycle:1];
    } else {
        // stop play
        [self.metaKit stopAudioMixing];
    }
}

- (void)setIsBeauty:(BOOL)isBeauty {
    if (_isBeauty == isBeauty) {
        return;
    }
    
    _isBeauty = isBeauty;
    self.beautyButton.selected = _isBeauty;
    MetaBeautyOptions *options = nil;
    if (_isBeauty) {
        options = [[MetaBeautyOptions alloc] init];
        options.lighteningContrastLevel = MetaLighteningContrastNormal;
        options.lighteningLevel = 0.7;
        options.smoothnessLevel = 0.5;
        options.rednessLevel = 0.1;
    }
    // improve local render view
    [self.metaKit setBeautyEffectOptions:_isBeauty options:options];
}

- (void)setIsEarPhone:(BOOL)isEarPhone {
    if (_isEarPhone == isEarPhone) {
        return;
    }
    
    _isEarPhone = isEarPhone;
    self.speakerPhoneButton.selected = _isEarPhone;
    // switch playout audio route
    [self.metaKit setEnableSpeakerphone:_isEarPhone];
}

- (void)setIsVideoMuted:(BOOL)isVideoMuted {
    if (_isVideoMuted == isVideoMuted) {
        return;
    }
    
    _isVideoMuted = isVideoMuted;
    self.muteVideoButton.selected = _isVideoMuted;
    [self setVideoMuted:_isVideoMuted forUid:0];
    [self updateSelfViewVisiable];
    // mute local video
    [self.metaKit muteLocalVideoStream:_isVideoMuted];
}

- (void)setIsAudioMuted:(BOOL)isAudioMuted {
    if (_isAudioMuted == isAudioMuted) {
        return;
    }
    
    _isAudioMuted = isAudioMuted;
    self.muteAudioButton.selected = _isAudioMuted;
    // mute local audio
    [self.metaKit muteLocalAudioStream:_isAudioMuted];
}

- (void)setIsDebugMode:(BOOL)isDebugMode {
    if (_isDebugMode == isDebugMode) {
        return;
    }
    
    _isDebugMode = isDebugMode;
    _options.isDebugMode = _isDebugMode;
    self.messageTableContainerView.hidden = !_isDebugMode;
}

- (void)setDoubleClickFullSession:(VideoSession *)doubleClickFullSession {
    _doubleClickFullSession = doubleClickFullSession;
    if (self.videoSessions.count >= 3) {
        [self updateInterfaceWithSessions:self.videoSessions targetSize:self.containerView.frame.size animation:YES];
    }
}

- (MetaRtcEngineKit *)metaKit {
    return [self.dataSource roomVCNeedMetaKit];
}

// videoViewLayouter and videoSessions manage all render views
- (VideoViewLayouter *)videoViewLayouter {
    if (!_videoViewLayouter) {
        _videoViewLayouter = [[VideoViewLayouter alloc] init];
    }
    return _videoViewLayouter;
}

- (NSMutableArray<VideoSession *> *)videoSessions {
    if (!_videoSessions) {
        _videoSessions = [[NSMutableArray alloc] init];
    }
    return _videoSessions;
}

- (Settings *)settings {
    return [self.dataSource roomVCNeedSettings];
}

- (RoomOptions *)options {
    if (!_options) {
        _options = [[RoomOptions alloc] init];
        _options.isDebugMode = false;
    }
    return _options;
}

#pragma mark - VC Life
- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = self.settings.roomName;
    [self loadmetaKit];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    NSString *segueId = segue.identifier;
    if (!segueId.length) {
        return;
    }
    
    if ([segueId isEqualToString:@"roomEmbedMessage"]) {
        self.messageVC = segue.destinationViewController;
    } else if ([segueId isEqualToString:@"roomToOptions"]) {
        RoomOptionsViewController *optionsVC = segue.destinationViewController;
        optionsVC.delegate = self;
        optionsVC.dataSource = self;
        self.optionsVC = optionsVC;
    }
}

- (void)dealloc {
    [self leaveChannel];
}

#pragma mark - UI Actions
- (IBAction)doCameraPressed:(UIButton *)sender {
    self.isSwitchCamera = !self.isSwitchCamera;
}

- (IBAction)doBeautyPressed:(UIButton *)sender {
    self.isBeauty = !self.isBeauty;
}

- (IBAction)doAudioMixingPressed:(UIButton *)sender {
    self.isAudioMixing = !self.isAudioMixing;
}

- (IBAction)doSpeakerPhonePressed:(UIButton *)sender {
    self.isEarPhone = !self.isEarPhone;
}

- (IBAction)doMuteVideoPressed:(UIButton *)sender {
    self.isVideoMuted = !self.isVideoMuted;
}

- (IBAction)doMuteAudioPressed:(UIButton *)sender {
    self.isAudioMuted = !self.isAudioMuted;
}

- (IBAction)doBackDoubleTapped:(UITapGestureRecognizer *)sender {
    if (!self.doubleClickFullSession) {
        // full screen display after be double clicked
        NSInteger tappedIndex = [self.videoViewLayouter responseIndexOfLocation:[sender locationInView:self.containerView]];
        if (tappedIndex >= 0 && tappedIndex < self.videoSessions.count) {
            self.doubleClickFullSession = self.videoSessions[tappedIndex];
        }
    } else {
        self.doubleClickFullSession = nil;
    }
}

#pragma mark - MetaRtcEngineKit
- (void)loadmetaKit {
    // Step 1, set delegate
    self.metaKit.delegate = self;
    // Step 2, set communication mode
    [self.metaKit setChannelProfile:MetaChannelProfileCommunication];
    
    // Step 3, enable the video module
    [self.metaKit enableVideo];
    // set video configuration
    MetaVideoEncoderConfiguration *configuration = [[MetaVideoEncoderConfiguration alloc] initWithSize:self.settings.dimension
                                                                                               frameRate:self.settings.frameRate
                                                                                                 bitrate:MetaVideoBitrateStandard
                                                                                         orientationMode:MetaVideoOutputOrientationModeAdaptative];
    [self.metaKit setVideoEncoderConfiguration:configuration];
    // add local render view and start preview
    [self addLocalSession];
    [self.metaKit startPreview];
    
    // Step 4, enable encryption mode
    //暂未开通
    if (self.settings.encryption.type != EncryptionTypeNone && self.settings.encryption.secret.length) {
//        MetaEncryptionConfig* config = [MetaEncryptionConfig new];
//        config.encryptionMode = self.settings.encryption.modeValue;
//        config.encryptionKey = self.settings.encryption.secret;
//        [self.metaKit enableEncryption:true encryptionConfig:config];
    }
    
    // Step 5, join channel and start group chat
    // If join  channel success, metaKit triggers it's delegate function
    // 'rtcEngine:(MetaRtcEngineKit *)engine didJoinChannel:(NSString *)channel withUid:(NSUInteger)uid elapsed:(NSInteger)elapsed'
    [self.metaKit joinChannelByToken:nil channelId:self.settings.roomName info:nil uid:0 joinSuccess:nil];
    [self setIdleTimerActive:NO];
}

- (void)addLocalSession {
    VideoSession *localSession = [VideoSession localSession];
    [localSession updateMediaInfo:self.settings.dimension fps:self.settings.frameRate];
    [self.videoSessions addObject:localSession];
    [self.metaKit setupLocalVideo:localSession.canvas];
    [self updateInterfaceWithSessions:self.videoSessions targetSize:self.containerView.frame.size animation:YES];
    [self.metaKit startPreview];
}

- (void)leaveChannel {
    // Step 1, release local MetaRtcVideoCanvas instance
    [self.metaKit setupLocalVideo:nil];
    // Step 2, leave channel and end group chat
    [self.metaKit leaveChannel:nil];
    // Step 3, please attention, stop preview after leave channel
    [self.metaKit stopPreview];
    
    // Step 4, remove all render views
    for (VideoSession *session in self.videoSessions) {
        [session.hostingView removeFromSuperview];
    }
    [self.videoSessions removeAllObjects];
    
    [self setIdleTimerActive:YES];
}

#pragma mark - <MetaRtcEngineDelegate>

///  Occurs when the local user joins a specified channel.
/// @param engine - RTC engine instance
/// @param channel  - Channel name
/// @param uid - User ID of the remote user sending the video stream.
/// @param elapsed - Time elapsed (ms) from the local user calling the joinChannelByToken method until the SDK triggers this callback.
- (void)rtcEngine:(MetaRtcEngineKit *)engine didJoinChannel:(NSString *)channel withUid:(NSUInteger)uid elapsed:(NSInteger)elapsed {
    [self info:[NSString stringWithFormat:@"Join channel: %@", channel]];
}


/// Occurs when the connection between the SDK and the server is interrupted.
/// The SDK triggers this callback when it loses connection with the server for more than four seconds after a connection is established.
/// After triggering this callback, the SDK tries reconnecting to the server. You can use this callback to implement pop-up reminders.
/// @param engine - RTC engine instance
- (void)rtcEngineConnectionDidInterrupted:(MetaRtcEngineKit *)engine {
    [self alert:@"Connection Interrupted"];
}

/// Occurs when the SDK cannot reconnect to Meta’s edge server 10 seconds after its connection to the server is interrupted.
/// @param engine - RTC engine instance
- (void)rtcEngineConnectionDidLost:(MetaRtcEngineKit *)engine {
    [self alert:@"Connection Lost"];
}


/// Reports an error during SDK runtime.
/// @param engine - RTC engine instance
/// @param errorCode - see complete list on this page
- (void)rtcEngine:(MetaRtcEngineKit *)engine didOccurError:(MetaErrorCode)errorCode {
    [self alert:[NSString stringWithFormat:@"Occur error: %ld", errorCode]];
}

/// First remote video frame,Occurs when the first remote video frame is received and decoded.
/// This callback is triggered in either of the following scenarios:
///   * The remote user joins the channel and sends the video stream.
///   * The remote user stops sending the video stream and re-sends it after 15 seconds. Possible reasons include:
///   * The remote user leaves channel.
///   * The remote user drops offline.
///   * The remote user calls muteLocalVideoStream.
///   * The remote user calls disableVideo.
///
/// @param engine - RTC engine instance
/// @param uid - User ID of the remote user sending the video stream.
/// @param size - Size of the first local video frame (width and height).
/// @param elapsed - Time elapsed (ms) from the local user calling the joinChannelByToken method until the SDK triggers this callback.
- (void)rtcEngine:(MetaRtcEngineKit *)engine firstRemoteVideoDecodedOfUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed {
    VideoSession *userSession = [self videoSessionOfUid:uid];
    userSession.size = size;
    [self.metaKit setupRemoteVideo:userSession.canvas];
}

/// First local video frame - occurs when the first local video frame is displayed/rendered on the local video view.
/// @param engine - RTC engine instance
/// @param size - Size of the first local video frame (width and height).
/// @param elapsed - Time elapsed (ms) from the local user calling the joinChannelByToken method until the SDK calls this callback.
///             If the startPreview method is called before the joinChannelByToken method, then elapsed is the time elapsed from
///             calling the startPreview method until the SDK triggers this callback.
- (void)rtcEngine:(MetaRtcEngineKit *)engine firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed {
    if (self.videoSessions.count) {
        VideoSession *selfSession = self.videoSessions.firstObject;
        selfSession.size = size;
        [self updateInterfaceWithSessions:self.videoSessions targetSize:self.containerView.frame.size animation:NO];
        [self info:[NSString stringWithFormat:@"local video dimension: %f x %f", size.width, size.height]];
    }
}

/// Occurs when a remote user (Communication)/host (Live Broadcast) leaves a channel.
/// @param engine - RTC engine instance
/// @param uid - User ID of the remote user sending the video stream.
/// @param reason - reason why user went offline, see complete list of the reasons:
- (void)rtcEngine:(MetaRtcEngineKit *)engine didOfflineOfUid:(NSUInteger)uid reason:(MetaUserOfflineReason)reason {
    VideoSession *deleteSession;
    for (VideoSession *session in self.videoSessions) {
        if (session.uid == uid) {
            deleteSession = session;
            break;
        }
    }
    
    if (deleteSession) {
        [self.videoSessions removeObject:deleteSession];
        [deleteSession.hostingView removeFromSuperview];
        [self updateInterfaceWithSessions:self.videoSessions targetSize:self.containerView.frame.size animation:YES];
        
        if (deleteSession == self.doubleClickFullSession) {
            self.doubleClickFullSession = nil;
        }
        
        // release canvas's view
        deleteSession.canvas.view = nil;
        
        [self.metaKit setupRemoteVideo:deleteSession.canvas];
    }
}

/// Occurs when a remote user’s video stream playback pauses/resumes.
/// @param engine - RTC engine instance
/// @param muted - true if muted; false otherwise
/// @param uid - User ID of the remote user sending the video stream.
- (void)rtcEngine:(MetaRtcEngineKit *)engine didVideoMuted:(BOOL)muted byUid:(NSUInteger)uid {
    [self setVideoMuted:muted forUid:uid];
}

/// Reports the statistics of the video stream from each remote user/host.
/// @param engine - RTC engine instance
/// @param stats - Statistics of the received remote video streams. See complete listing at
- (void)rtcEngine:(MetaRtcEngineKit *)engine remoteVideoStats:(MetaRtcRemoteVideoStats *)stats {
    VideoSession *session = [self fetchSessionOfUid:stats.uid];
    [session updateMediaInfo:CGSizeMake(stats.width, stats.height) fps:stats.rendererOutputFrameRate];
}

/// Occurs when the audio mixing file playback finishes.
/// @param engine - RTC engine instance
- (void)rtcEngineLocalAudioMixingDidFinish:(MetaRtcEngineKit *)engine {
    self.isAudioMixing = NO;
}

#pragma mark - RoomOptionsVCDelegate, RoomOptionsVCDataSource
- (void)roomOptions:(RoomOptionsViewController *)vc debugModeDidEnable:(BOOL)enable {
    self.isDebugMode = enable;
}

- (RoomOptions *)roomOptionsVCNeedOptions {
    return self.options;
}

#pragma mark - Private
- (void)updateInterfaceWithSessions:(NSArray *)sessions targetSize:(CGSize)targetSize animation:(BOOL)animation {
    if (animation) {
        [UIView animateWithDuration:0.3 animations:^{
            [self updateInterfaceWithSessions:sessions targetSize:targetSize];
            [self.view layoutIfNeeded];
        }];
    } else {
        [self updateInterfaceWithSessions:sessions targetSize:targetSize];
    }
}

- (void)updateInterfaceWithSessions:(NSArray *)sessions targetSize:(CGSize)targetSize {
    if (!sessions.count) {
        return;
    }
    
    VideoSession *selfSession = sessions.firstObject;
    self.videoViewLayouter.selfView = selfSession.hostingView;
    self.videoViewLayouter.selfSize = selfSession.size;
    self.videoViewLayouter.targetSize = targetSize;
    
    NSMutableArray *peerVideoViews = [[NSMutableArray alloc] init];
    for (NSInteger i = 1; i < sessions.count; ++i) {
        VideoSession *session = sessions[i];
        [peerVideoViews addObject:session.hostingView];
    }
    self.videoViewLayouter.videoViews = peerVideoViews;
    self.videoViewLayouter.fullView = self.doubleClickFullSession.hostingView;
    self.videoViewLayouter.containerView = self.containerView;
    
    [self.videoViewLayouter layoutVideoViews];
    [self updateSelfViewVisiable];
    
    // Only three people or more can switch the layout
    if (sessions.count >= 3) {
        self.backgroundDoubleTap.enabled = YES;
    } else {
        self.backgroundDoubleTap.enabled = NO;
        self.doubleClickFullSession = nil;
    }
}

- (void)setIdleTimerActive:(BOOL)active {
    [UIApplication sharedApplication].idleTimerDisabled = !active;
}

- (VideoSession *)fetchSessionOfUid:(NSUInteger)uid {
    for (VideoSession *session in self.videoSessions) {
        if (session.uid == uid) {
            return session;
        }
    }
    return nil;
}

- (VideoSession *)videoSessionOfUid:(NSUInteger)uid {
    VideoSession *fetchedSession = [self fetchSessionOfUid:uid];
    if (fetchedSession) {
        return fetchedSession;
    } else {
        VideoSession *newSession = [[VideoSession alloc] initWithUid:uid];
        [self.videoSessions addObject:newSession];
        [self updateInterfaceWithSessions:self.videoSessions targetSize:self.containerView.frame.size animation:YES];
        return newSession;
    }
}

- (void)setVideoMuted:(BOOL)muted forUid:(NSUInteger)uid {
    VideoSession *fetchedSession = [self fetchSessionOfUid:uid];
    fetchedSession.isVideoMuted = muted;
}

- (void)updateSelfViewVisiable {
    UIView *selfView = self.videoSessions.firstObject.hostingView;
    if (self.videoSessions.count == 2) {
        selfView.hidden = self.isVideoMuted;
    } else {
        selfView.hidden = false;
    }
}

// Log
- (void)info:(NSString *)text {
    if (!text.length) {
        return;
    }
    
    [self.messageVC appendInfo:text];
}

- (void)alert:(NSString *)text {
    if (!text.length) {
        return;
    }
    
    [self.messageVC appendError:text];
}

#pragma mark - Others
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    AppDelegate *appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    appDelegate.orientation = UIInterfaceOrientationMaskAll;
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    AppDelegate *appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    appDelegate.orientation = UIInterfaceOrientationMaskPortrait;
}
@end
