//
//  MetaLiveKit.h
//  MetaLiveKit
//
//  Created by Junhao Wang
//  Copyright (c) 2017 Meta. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MetaLivePublisher.h"
#import "MetaLiveSubscriber.h"
#import "MetaRtcEngineKit.h"

/** A class for enabling or disabling the video.
 */
__attribute__((visibility("default"))) @interface MetaLiveChannelConfig: NSObject
@property (assign, nonatomic) BOOL videoEnabled;

+(MetaLiveChannelConfig *_Nonnull) defaultConfig;
@end

/** The base class for managing a live broadcast.

 MetaLiveKit manages the channel and all actions apart from publishing and subscribing.
 */
@class MetaLiveKit;

/** Protocol providing the MetaLiveKit class with callbacks.
 */
@protocol MetaLiveDelegate <NSObject>
@optional


/** A warning occurred during SDK runtime.

 The application can ignore the warning, and the SDK tries to resume automatically.

 @param kit         MetaLiveKit
 @param warningCode MetaWarningCode
 */
- (void)liveKit:(MetaLiveKit *_Nonnull)kit didOccurWarning:(MetaWarningCode)warningCode;

/** An error occurred during SDK runtime.

 The SDK cannot resume a normal state, and the application needs to handle it.

 @param kit       MetaLiveKit
 @param errorCode MetaErrorCode
 */
- (void)liveKit:(MetaLiveKit *_Nonnull)kit didOccurError:(MetaErrorCode)errorCode;

/** A user joined the channel.

 @param kit     MetaLiveKit
 @param channel Channel name
 @param uid     Local user ID
 @param elapsed Time elapsed (ms) from calling [joinChannelByToken]([MetaRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) until this callback is triggered.
  */
- (void)liveKit:(MetaLiveKit *_Nonnull)kit didJoinChannel:(NSString *_Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed;

/** The statistics of the call when leaving a channel

 @param kit    MetaLiveKit
 */
- (void)liveKitDidLeaveChannel:(MetaLiveKit *_Nonnull)kit;

/** A user rejoined the channel

 @param kit     MetaLiveKit
 @param channel Channel name.
 @param uid     User ID.
 @param elapsed Time elapsed (ms) from calling [joinChannelByToken]([MetaRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) until this callback is triggered.
 */
- (void)liveKit:(MetaLiveKit *_Nonnull)kit didRejoinChannel:(NSString *_Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed;

/** Generates a new Token.

 When the Token is enabled, and the specified Token is invalid or has expired, this function will be called.
 The app should generate a new Token and call renewToken to refresh the key.

 Note: MetaErrorCodeTokenExpired = -109 and MetaErrorCodeInvalidToken = -110 are also reported through the [didOccurError](liveKit:didOccurError:) callback. Move the renew token logic into this callback.

 @param kit MetaLiveKit
 */
- (void)liveKitRequestToken:(MetaLiveKit *_Nonnull)kit;

/**
 The Token will expire within 30 seconds.

 If the Token you specified when calling [joinChannelByToken]([MetaRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) expires, you will become offline. This callback is triggered 30 seconds before the Token expires to remind the app to renew the Token.

 Upon receiving this callback, the user needs to generate a new Token on your server and call renewToken to pass the new Token on to the SDK.


 @param kit MetaLiveKit
 @param token The Token that will expire in 30 seconds.
 */
- (void)liveKit:(MetaLiveKit * _Nonnull)kit tokenPrivilegeWillExpire:(NSString * _Nonnull)token;

// statistics

/** The statistics of the RTC MetaLiveKit status every two seconds.

 @param kit    MetaLiveKit
 @param stats  Statistics of the RTC status, including the duration, sent bytes, and received bytes
 */
- (void)liveKit:(MetaLiveKit *_Nonnull)kit reportLiveStats:(MetaChannelStats *_Nonnull)stats;
// network

/** The connection between the SDK and the server has been interrupted.

This callback is triggered when the SDK losses connection with the server.

Once the connection is lost, the SDK attempts to reconnect until the
   application calls [leaveChannel]([MetaLiveKit leaveChannel]).

 @param kit    MetaLiveKit
 */
- (void)liveKitConnectionDidInterrupted:(MetaLiveKit *_Nonnull)kit;

/** The connection to the server is lost.

 This event is reported after the connection to the server is interrupted and the reconnection time has exceeded (10 seconds by default).
 The SDK tries to automatically reconnect with the server until the app calls [leaveChannel]([MetaLiveKit leaveChannel]).

@param kit    MetaLiveKit
 */
- (void)liveKitConnectionDidLost:(MetaLiveKit *_Nonnull)kit;

/** The network quality of the local user.

 @param kit     MetaLiveKit
 @param uid     User ID
 @param txQuality Network transmission quality: MetaNetworkQuality
 @param rxQuality Network receiving quality: MetaNetworkQuality
 */
- (void)liveKit:(MetaLiveKit *_Nonnull)kit networkQuality:(NSUInteger)uid txQuality:(MetaNetworkQuality)txQuality rxQuality:(MetaNetworkQuality)rxQuality;
@end

/**
 MetaLiveKit is the base class for managing a live broadcast. MetaLiveKit manages the channel and all actions apart from publishing and subscribing.
 */
__attribute__((visibility("default"))) @interface MetaLiveKit : NSObject

/**
 Protocol providing the MetaLiveKit class with callbacks.
 */
@property (weak, nonatomic) _Nullable id<MetaLiveDelegate> delegate;

/** Returns the version of the Meta SDK.

@return string, SDK version
*/
+ (NSString *_Nonnull)getSdkVersion;

/** Returns the native handler of the SDK engine
 */
- (MetaRtcEngineKit *_Nonnull)getRtcEngineKit;

/** Initializes the MetaLiveKit object.

 @param appId The appId is issued to you by Meta.

 @return an object of MetaLiveKit class
 */
+ (instancetype _Nonnull)sharedLiveKitWithAppId:(NSString *_Nonnull)appId;


/**
 Destroys the engine instance.

 This method releases all the resources used by the Meta SDK.  This is useful for applications occasionally making voice calls, to free up resources for other operations when not making calls.

 Once the application has called destroy() to destroy the created RtcEngine instance,
 no other methods in the SDK can be used and no callbacks occur.

 To start communications again, initialize [sharedEngineWithappId](sharedEngineWithAppId:delegate:) to establish a new MetaRtcEngineKit instance.

 Note: This method is called synchronously. The result returns after the IRtcEngine
 object resources are released. The app should not call this interface in the
 callback generated by the SDK, otherwise the SDK must wait for the callback
 to return before it can reclaim the related object resources, causing a deadlock.

 */
+ (void)destroy;

/** Core Methods */

/**  Allows a user to join a channel.

 This method creates an open UDP socket to the MetaLiveKit cloud service to join a channel.
 Users in the same channel can talk to each other using the same App ID. This method is asynchronous.


 @param token A Token generated by the app through signature certification.
 @param channelId Channel ID.  Joining a channel with the same channel ID means that users are joining the same room.
 The channel ID supported scope: a-z, A-Z, 0-9, space, !#$%&()+-:;&le;.,>?@[]^_{|}~
 @param channelConfig MetaLiveChannelConfig
 @param uid Optional: ID of each user in the channel that is unique. If it is set as 0, the SDK automatically assigns an ID, which can be found in the [didJoinChannel]([MetaLiveDelegate liveKit:didJoinChannel:withUid:elapsed:]) delegate.

 @return * 0: Success. * <0: Failure.
 */
- (int)joinChannelByToken:(NSString *_Nullable)token
               channelId:(NSString *_Nonnull)channelId
            config:(MetaLiveChannelConfig *_Nonnull)channelConfig
               uid:(NSUInteger)uid;

/**
 Allows a user to leave a channel, such as hanging up or exiting a call.

 @return * 0: Success. * <0: Failure.
 */
- (int)leaveChannel;


/** Updates the Token.

 The key expires after a certain period of time once the Token scheme is enabled. When the [didOccurError]([MetaLiveDelegate liveKit:didOccurError:]) callback reports the error ERR_TOKEN_EXPIRED(109), the application should retrieve a new key and then call this method to renew it. Failure to do so will result in the SDK disconnecting from the server.

 @param token New Token.

 @return * 0: Success. * <0: Failure.
 */
- (int)renewToken:(NSString*_Nonnull)token;

/** Starts the local video preview.

 Before starting the preview, always call the setupLocalVideo:local: method to set up the preview window and configure its attributes and also call the enableVideo method to enable video. If before calling [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) to join the channel, you have called startPreview to start the local video preview, then the local preview will be still in the started state after you called [leaveChannel]([MetaLiveKit leaveChannel]) to exit the channel. You can call stopPreview to close the local preview.

 @param mode Video display mode: MetaVideoRenderMode
 @return * 0: Success. * <0: Failure.
 */
- (int)startPreview:(VIEW_CLASS *_Nonnull)view
         renderMode:(MetaVideoRenderMode)mode;

/** Stops the local video preview.

 @return * 0: Success. * <0: Failure.
 */
- (int)stopPreview;

@end
