//
//  WujiRtcChannel.h
//  WujiRtcChannel
//
//  Copyright (c) 2019 Wuji. All rights reserved.
//

#import "WujiRtcEngineKit.h"

@class WujiRtcChannelMediaOptions;
@protocol WujiRtcChannelDelegate;
@interface WujiRtcEngineKit ()

/** Creates and gets an WujiRtcChannel instance.

To join more than one channel, call this method multiple times to create as many WujiRtcChannel
objects as needed, and call the [joinChannelByToken]([WujiRtcChannel
joinChannelByToken:info:uid:options:]) method of each created WujiRtcChannel instance.

After joining multiple channels, you can simultaneously subscribe to streams of all the channels,
but publish a stream in only one channel at one time.

@param channelId The unique channel name for an Wuji RTC session. It must be in the string format
and not exceed 64 bytes in length. Supported character scopes are:

- All lowercase English letters: a to z.
- All uppercase English letters: A to Z.
- All numeric characters: 0 to 9.
- The space character.
- Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".

**Note**

- This parameter does not have a default value. You must set it.
- Do not set it as the empty string "". Otherwise, the SDK returns `WujiErrorCodeRefused`(-5).

@return - A pointer to the WujiRtcChannel instance, if the method call succeeds.
- An empty pointer `nil`, if the method call fails.
- `WujiErrorCodeRefused`(-5), if you set `channelId` as the empty string "".
 */
- (WujiRtcChannel *_Nullable)createRtcChannel:(NSString *_Nonnull)channelId;

@end

/** The WujiRtcChannel class.

 **Since** v3.0.0.
 */
__attribute__((visibility("default"))) @interface WujiRtcChannel : NSObject

/** Destroys the WujiRtcChannel instance.

 @return - 0: Success.
 - < 0: Failure.

   - `WujiErrorCodeNotInitialized`(-7): The WujiRtcChannel instance is not initialized before
 calling this method.
 */
- (int)destroy;
/** Sets the channel delegate.

 After setting the channel delegate, you can listen for channel events and receive the statistics of
 the corresponding WujiRtcChannel instance.

 @param channelDelegate The delegate of the WujiRtcChannel instance. For details, see
 WujiRtcChannelDelegate.
 */
- (void)setRtcChannelDelegate:(id<WujiRtcChannelDelegate> _Nullable)channelDelegate;

/** Gets the channel ID of the current WujiRtcChannel instance.

 @return - The channel ID of the current WujiRtcChannel instance, if the method call succeeds.
 - The empty string "", if the method call fails.
 */
- (NSString *_Nullable)getChannelId;

/** Gets the current call ID.

 @return - The current call ID, if the method call succeeds.
 - The empty string "", if the method call fails.
 */
- (NSString *_Nullable)getCallId;
/** Gets the connection state of the SDK.

 @return The connection state, see [WujiConnectionStateType](WujiConnectionStateType):

  - `WujiConnectionStateDisconnected`(1): The SDK is disconnected from Wuji's edge server.
  - `WujiConnectionStateConnecting`(2): The SDK is connecting to Wuji's edge server.
  - `WujiConnectionStateConnected`(3): The SDK joined a channel and is connected to Wuji's edge
 server. You can now publish or subscribe to a media stream in the channel.
  - `WujiConnectionStateReconnecting`(4): The SDK keeps rejoining the channel after being
 disconnected from a joined channel because of network issues.
  - `WujiConnectionStateFailed`(5): The SDK fails to join the channel.
 */
- (WujiConnectionStateType)getConnectionState;

/** Joins the channel with a user ID.

 This method differs from the [joinChannelByToken]([WujiRtcEngineKit
joinChannelByToken:channelId:info:uid:joinSuccess:]) method in the WujiRtcEngineKit class in the
following aspects:

| [WujiRtcChannel joinChannelByToken]([WujiRtcChannel joinChannelByToken:info:uid:options:]) |
[WujiRtcEngineKit joinChannelByToken]([WujiRtcEngineKit
joinChannelByToken:channelId:info:uid:joinSuccess:]) |
|------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------|
| Does not contain the `channelId` parameter, because `channelId` is specified when creating the
WujiRtcChannel instance.                                | Contains the `channelId` parameter, which
specifies the channel to join.                                       | | Contains the `options`
parameter, which decides whether to subscribe to all streams before joining the channel. | Does not
contain the `options` parameter. By default, users subscribe to all streams when joining the
channel. | | Users can join multiple channels simultaneously by creating multiple WujiRtcChannel
instances and calling the `joinChannelByToken` method of each instance. | Users can join only one
channel.                                                                             | | By default,
the SDK does not publish any stream after the user joins the channel. You need to call the
[publish]([WujiRtcChannel publish]) method to do that.              | By default, the SDK publishes
streams once the user joins the channel.                                       |

 **Note**

 - If you are already in a channel, you cannot rejoin it with the same `uid`.
 - We recommend using different `uid` for different channels.
 - If you want to join the same channel from different devices, ensure that the `uid` in all devices
are different.
 - Ensure that the app ID you use to generate the token is the same with the app ID used when
creating the WujiRtcEngineKit instance.

 @param token The token for authentication:

 - In situations not requiring high security: You can use the temporary token generated at Wuji
Console. For details, see [Get a temporary
token](https://docs.wuji.io/en/Wuji%20Platform/token?platform=All%20Platforms#get-a-temporary-token).
 - In situations requiring high security: Set it as the token generated at your server. For details,
see [Generate a
token](https://docs.wuji.io/en/Interactive%20Broadcast/token_server_cpp?platform=CPP).
 @param info Additional information about the channel. This parameter can be set as null. Other
users in the channel do not receive this information.
 @param uid The user ID. A 32-bit unsigned integer with a value ranging from 1 to
(2<sup>32</sup>-1). This parameter must be unique. If `uid` is not assigned (or set as 0), the SDK
assigns a `uid` and reports it in the [rtcChannelDidJoinChannel]([WujiRtcChannelDelegate
rtcChannelDidJoinChannel:withUid:elapsed:]) callback. The app must maintain this user ID.
 @param options The channel media options: WujiRtcChannelMediaOptions

 @return - 0: Success.
 - < 0: Failure.

   - `WujiErrorCodeInvalidArgument`(-2)
   - `WujiErrorCodeNotReady`(-3)
   - `WujiErrorCodeRefused`(-5)
 */
- (int)joinChannelByToken:(NSString *_Nullable)token
                     info:(NSString *_Nullable)info
                      uid:(NSUInteger)uid
                  options:(WujiRtcChannelMediaOptions *_Nonnull)options;

/** Joins a channel with the user account.

 This method differs from the [joinChannelByUserAccount]([WujiRtcEngineKit
joinChannelByUserAccount:token:channelId:joinSuccess:]) method in the WujiRtcEngineKit class in the
following aspects:

| [WujiRtcChannel joinChannelByUserAccount]([WujiRtcChannel
joinChannelByUserAccount:token:options:])                                                  |
[WujiRtcEngineKit joinChannelByUserAccount]([WujiRtcEngineKit
joinChannelByUserAccount:token:channelId:joinSuccess:]) |
|------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------|
| Does not contain the `channelId` parameter, because `channelId` is specified when creating the
WujiRtcChannel instance.                                | Contains the `channelId` parameter, which
specifies the channel to join.                                       | | Contains the `options`
parameter, which decides whether to subscribe to all streams before joining the channel. | Does not
contain the `options` parameter. By default, users subscribe to all streams when joining the
channel. | | Users can join multiple channels simultaneously by creating multiple WujiRtcChannel
instances and calling the `joinChannelByUserAccount` method of each instance. | Users can join only
one channel.                                                                             | | By
default, the SDK does not publish any stream after the user joins the channel. You need to call the
[publish]([WujiRtcChannel publish]) method to do that.              | By default, the SDK publishes
streams once the user joins the channel.                                       |

 **Note**

 - If you are already in a channel, you cannot rejoin it with the same `uid`.
 - We recommend using different `uid` for different channels.
 - If you want to join the same channel from different devices, ensure that the `uid` in all devices
are different.
 - Ensure that the app ID you use to generate the token is the same with the app ID used when
creating the WujiRtcEngineKit instance.

 @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that
you set this parameter and do not set it as null.

   - All lowercase English letters: a to z.
   - All uppercase English letters: A to Z.
   - All numeric characters: 0 to 9.
   - The space character.
   - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+",
"-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 @param token The token generated at your server:

 - In situations not requiring high security: You can use the temporary token generated at Console.
For details, see [Get a temporary
token](https://docs.wuji.io/en/Wuji%20Platform/token?platform=All%20Platforms#get-a-temporary-token).
 - In situations requiring high security: Set it as the token generated at your server. For details,
see [Get a
token](https://docs.wuji.io/en/Wuji%20Platform/token?platform=All%20Platforms&_ga=2.220734490.38407571.1574824837-569329450.1562664463#get-a-token).
 @param options The channel media options: WujiRtcChannelMediaOptions

 @return - 0: Success.
 - < 0: Failure.

   - `WujiErrorCodeInvalidArgument`(-2)
   - `WujiErrorCodeNotReady`(-3)
   - `WujiErrorCodeRefused`(-5)
 */
- (int)joinChannelByUserAccount:(NSString *_Nonnull)userAccount
                          token:(NSString *_Nullable)token
                        options:(WujiRtcChannelMediaOptions *_Nonnull)options;

/** Leaves the current channel.

 A successful `leaveChannel` method call triggers the following callbacks:

  - The local client: [rtcChannelDidLeaveChannel]([WujiRtcChannelDelegate
 rtcChannelDidLeaveChannel:withStats:]).
  - The remote client: [didOfflineOfUid]([WujiRtcChannelDelegate
 rtcChannel:didOfflineOfUid:reason:]), if the user leaving the channel is in a Communication
 channel, or is a broadcaster in a Live-Broadcast channel.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)leaveChannel;

/** Publishes the local stream to the channel.

 You must keep the following restrictions in mind when calling this method. Otherwise, the SDK
 returns the WujiErrorCodeRefused(-5)：

 - This method publishes one stream only to the channel corresponding to the current WujiRtcChannel
 instance.
 - In a Live-Broadcast channel, only a broadcaster can call this method. To switch the client role,
 call [setClientRole]([WujiRtcChannel setClientRole:]) of the current WujiRtcChannel instance.
 - You can publish a stream to only one channel at a time. For details, see the advanced guide *Join
 Multiple Channels*.

 @return - 0: Success.
 - < 0: Failure.

   - `WujiErrorCodeRefused`(-5): The method call is refused.
 */
- (int)publish;

/** Stops publishing a stream to the channel.

 If you call this method in a channel where you are not publishing streams, the SDK returns
 WujiErrorCodeRefused(-5).

 @return - 0: Success.
 - < 0: Failure.

   - `WujiErrorCodeRefused`(-5): The method call is refused.
 */
- (int)unpublish;

/** Sets the role of a user.

 This method sets the role of a user, such as a host or an audience. In a Live-Broadcast channel,
 only a broadcaster can call the [publish]([WujiRtcChannel publish]) method in the WujiRtcChannel
 class.

 A successful call of this method triggers the following callbacks:

 - The local client: [didClientRoleChanged]([WujiRtcChannelDelegate
 rtcChannel:didClientRoleChanged:newRole:]).
 - The remote client: [didJoinedOfUid]([WujiRtcChannelDelegate rtcChannel:didJoinedOfUid:elapsed:])
 or [didOfflineOfUid]([WujiRtcChannelDelegate
 rtcChannel:didOfflineOfUid:reason:])(WujiUserOfflineReasonBecomeAudience).

 @param role The role of the user:

 - `WujiClientRoleBroadcaster(1)`: Broadcaster. A broadcaster can both send and receive streams.
 - `WujiClientRoleAudience(2)`: Audience, the default role. An audience can only receive streams.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)setClientRole:(WujiClientRole)role;

/** Renews the token when the current token expires.

 In the following situations, the SDK decides that the current token has expired:

 - The SDK triggers the [tokenPrivilegeWillExpire]([WujiRtcChannelDelegate
 rtcChannel:tokenPrivilegeWillExpire:]) callback, or
 - The [connectionChangedToState]([WujiRtcChannelDelegate
 rtcChannel:connectionChangedToState:reason:]) callback reports the
 WujiConnectionChangedTokenExpired(9) error.

 You should get a new token from your server and call this method to renew it. Failure to do so
 results in the SDK disconnecting from the Wuji server.

 **Note**

 Wuji recommends using the [rtcChannelRequestToken]([WujiRtcChannelDelegate
 rtcChannelRequestToken:]) callback to report the WujiErrorCodeTokenExpired(-109) error, not using
 the [didOccurError]([WujiRtcChannelDelegate rtcChannel:didOccurError:]) callback.

 @param token The new token.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)renewToken:(NSString *_Nonnull)token;

/** Enables built-in encryption with an encryption password before joining a channel.

 All users in a channel must set the same encryption password. The encryption password is
 automatically cleared once a user leaves the channel.

 If the encryption password is not specified or set to empty, the encryption functionality is
 disabled.

 **Note**

 - Do not use this method for CDN live streaming.
 - For optimal transmission, ensure that the encrypted data size does not exceed the original data
 size + 16 bytes. 16 bytes is the maximum padding size for AES encryption.

 @param secret Encryption password.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)setEncryptionSecret:(NSString *_Nullable)secret;

/** Sets the built-in encryption mode.

 The SDK supports built-in encryption, which is set to the "aes-128-xts" mode by default. Call this
 method to use other encryption modes.

 All users in the same channel must use the same encryption mode and password.

 Refer to the information related to the AES encryption algorithm on the differences between the
 encryption modes.

 **Note**

 - Call the [setEncryptionSecret]([WujiRtcChannel setEncryptionSecret:]) method to enable the
 built-in encryption function before calling this method.
 - Do not use this method for CDN live streaming.

 @param encryptionMode Sets the encryption mode.

 - “aes-128-xts”: (default) 128-bit AES encryption, XTS mode.
 - “aes-256-xts”: 256-bit AES encryption, XTS mode.
 - “aes-128-ecb”: 128-bit AES encryption, ECB mode.
 - "": (Default) When encryptionMode is set as the empty string, the encryption is in “aes-128-xts”
 by default.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)setEncryptionMode:(NSString *_Nullable)encryptionMode;
/** Sets the priority of a remote user’s stream.

 Use this method with the [setRemoteSubscribeFallbackOption]([WujiRtcEngineKit
 setRemoteSubscribeFallbackOption:]) method. If the fallback function is enabled for a remote
 stream, the SDK ensures the high-priority user gets the best possible stream quality.

 **Note**

 The SDK supports setting userPriority as high for one user only.

 @param uid The ID of the remote user.
 @param userPriority The priority of the remote user, see WujiUserPriority.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)setRemoteUserPriority:(NSUInteger)uid type:(WujiUserPriority)userPriority;
/** Sets the sound position and gain of a remote user.

 When the local user calls this method to set the sound position of a remote user, the sound
 difference between the left and right channels allows the local user to track the real-time
 position of the remote user, creating a real sense of space. This method applies to massively
 multiplayer online games, such as Battle Royale games.

 **Note**

 - For this method to work, enable stereo panning for remote users by calling
 [enableSoundPositionIndication]([WujiRtcEngineKit enableSoundPositionIndication:]) before joining a
 channel. This method requires hardware support.
 - For the best effect, we recommend using the following audio output devices:

   - (iOS) A stereo headset.
   - (macOS) A stereo loudspeaker.

 @param uid The ID of the remote user.
 @param pan The sound position of the remote user. The value ranges from -1.0 to 1.0:

 - 0.0: (Default) The remote sound comes from the front.
 - -1.0: The remote sound comes from the left.
 - 1.0: The remote sound comes from the right.
 @param gain Gain of the remote user. The value ranges from 0.0 to 100.0. The default value is 100.0
 (the original gain of the remote user). The smaller the value, the less the gain.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)setRemoteVoicePosition:(NSUInteger)uid pan:(double)pan gain:(double)gain;
/** Updates the display mode of the video view of a remote user.

 After initializing the video view of a remote user, you can call this method to update its
 rendering and mirror modes. This method affects only the video view that the local user sees.

 **Note**

 - Ensure that you have called [setupRemoteVideo]([WujiRtcEngineKit setupRemoteVideo:]) to
 initialize the remote video view before calling this method.
 - During a call, you can call this method as many times as necessary to update the display mode of
 the video view of a remote user.

 @param uid The ID of the remote user.
 @param renderMode The rendering mode of the remote video view. See
 [WujiVideoRenderMode](WujiVideoRenderMode).
 @param mirrorMode The mirror mode of the remote video view. See
 [WujiVideoMirrorMode](WujiVideoMirrorMode).

 **Note**

 The SDK disables the mirror mode by default.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)setRemoteRenderMode:(NSUInteger)uid
                renderMode:(WujiVideoRenderMode)renderMode
                mirrorMode:(WujiVideoMirrorMode)mirrorMode;

/** Sets whether to receive all remote audio streams by default.

 You can call this method either before or after joining a channel. If you call
 `setDefaultMuteAllRemoteAudioStreams (YES)` after joining a channel, the remote audio streams of
 all subsequent users are not received.

 @note If you want to resume receiving the audio stream, call [muteRemoteAudioStream
 (NO)]([WujiRtcChannel muteRemoteAudioStream:mute:]), and specify the ID of the remote user whose
 audio stream you want to receive. To receive the audio streams of multiple remote users, call
 `muteRemoteAudioStream (NO)` as many times. Calling `setDefaultMuteAllRemoteAudioStreams (NO)`
 resumes receiving the audio streams of subsequent users only.

 @param mute Sets whether to receive/stop receiving all remote audio streams by default:

 - YES: Stop receiving all remote audio streams by default.
 - NO: (Default) Receive all remote audio streams by default.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)setDefaultMuteAllRemoteAudioStreams:(BOOL)mute;

/** Sets whether to receive all remote video streams by default.

 You can call this method either before or after joining a channel. If you call
 `setDefaultMuteAllRemoteVideoStreams (YES)` after joining a channel, the remote video streams of
 all subsequent users are not received.

 @note If you want to resume receiving the video stream, call [muteRemoteVideoStream
 (NO)]([WujiRtcEngineKit muteRemoteVideoStream:mute:]), and specify the ID of the remote user whose
 video stream you want to receive. To receive the video streams of multiple remote users, call
 `muteRemoteVideoStream (NO)` as many times. Calling `setDefaultMuteAllRemoteVideoStreams (NO)`
 resumes receiving the video streams of subsequent users only.

 @param mute Sets whether to receive/stop receiving all remote video streams by default.

 - YES: Stop receiving all remote video streams by default.
 - NO: (Default) Receive all remote video streams by default.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)setDefaultMuteAllRemoteVideoStreams:(BOOL)mute;

/** Receives/Stops receiving a specified remote user’s audio stream.

 **Note**

 If you call the [muteAllRemoteAudioStreams]([WujiRtcChannel muteAllRemoteAudioStreams:]) method and
 set `mute` as `YES` to mute all remote audio streams, call the `muteAllRemoteAudioStreams` method
 again and set `mute` as `NO` before calling this method. The `muteAllRemoteAudioStreams` method
 sets all remote streams, while the `muteRemoteAudioStream` method sets a specified stream.

 @param uid User ID of the specified remote user.
 @param mute Sets whether to receive/stop receiving a specified remote user’s audio stream:

 - YES: Stop receiving a specified remote user’s audio stream.
 - NO: (Default) Receive a specified remote user’s audio stream.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)muteRemoteAudioStream:(NSUInteger)uid mute:(BOOL)mute;
/** Adjust the playback volume of a specified remote user.

 You can call this method as many times as necessary to adjust the playback volume of different
 remote users, or to repeatedly adjust the playback volume of the same remote user.

 **Note**

 - Call this method after joining a channel.
 - The playback volume here refers to the mixed volume of a specified remote user.
 - This method can only adjust the playback volume of one specified remote user at a time. To adjust
 the playback volume of different remote users, call the method as many times, once for each remote
 user.

 @param uid The ID of the remote user.
 @param volume The playback volume of the specified remote user. The value ranges from 0 to 100:

 - 0: Mute.
 - 100: Original volume.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)adjustUserPlaybackSignalVolume:(NSUInteger)uid volume:(int)volume;

/** Receives/Stops receiving all remote audio streams.

 @param mute Sets whether to receive/stop receiving all remote audio streams:

 - YES: Stop receiving all remote audio streams.
 - NO: (Default) Receive all remote audio streams.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

/** Receives/Stops receiving a specified remote user’s video stream.

 **Note**

 If you call the [muteAllRemoteVideoStreams]([WujiRtcChannel muteAllRemoteVideoStreams:]) method and
 set `mute` as `YES` to stop receiving all remote video streams, call the
 `muteAllRemoteVideoStreams` method again and set `mute` as `NO` before calling this method.

 @param uid User ID of the specified remote user.
 @param mute Sets whether to receive/stop receiving a specified remote user’s video stream.

 - YES: Stops receiving a specified remote user’s video stream.
 - NO: (Default) Receives a specified remote user’s video stream.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)muteRemoteVideoStream:(NSUInteger)uid mute:(BOOL)mute;

/** Receives/Stops receiving all remote video streams.

 @param mute Sets whether to receive/stop receiving all remote video streams:

 - YES: Stops receiving all remote video streams.
 - NO: (Default) Receives all remote video streams.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)muteAllRemoteVideoStreams:(BOOL)mute;
/** Sets the stream type of the remote video.

 Under limited network conditions, if the publisher has not disabled the dual-stream mode using
[enableDualStreamMode(false)]([WujiRtcEngineKit enableDualStreamMode:])enableDualStreamMode(false),
the receiver can choose to receive either the high-quality video stream (the high resolution, and
high bitrate video stream) or the low-quality video stream (the low resolution, and low bitrate
video stream).

 By default, users receive the high-quality video stream. Call this method if you want to switch to
the low-quality video stream. This method allows the app to adjust the corresponding video stream
type based on the size of the video window to reduce the bandwidth and resources.

 The aspect ratio of the low-quality video stream is the same as the high-quality video stream. Once
the resolution of the high-quality video stream is set, the system automatically sets the
resolution, frame rate, and bitrate of the low-quality video stream.

 The SDK reports the result of calling this method in the [didApiCallExecute]([WujiRtcEngineDelegate
rtcEngine:didApiCallExecute:api:result:]) callback.

 @param uid ID of the remote user sending the video stream.
 @param streamType Sets the video-stream type. See WujiVideoStreamType.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)setRemoteVideoStream:(NSUInteger)uid type:(WujiVideoStreamType)streamType;
/** Sets the default video-stream type for the video received by the local user when the remote user
 sends dual streams.

 @param streamType Sets the default video-stream type. See WujiVideoStreamType.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)setRemoteDefaultVideoStreamType:(WujiVideoStreamType)streamType;
/** Adds a voice or video stream RTMP URL address to a live broadcast.

 If this method call is successful, the server pulls the voice or video stream and injects it into a
live channel. This is applicable to scenarios where all audience members in the channel can watch a
live show and interact with each other.

 The `addInjectStreamUrl` method call triggers the following callbacks:

 - The local client:

   - [streamInjectedStatusOfUrl]([WujiRtcChannelDelegate
rtcChannel:streamInjectedStatusOfUrl:uid:status:]), with the state of the injecting the online
stream.
   - [didJoinedOfUid]([WujiRtcChannelDelegate rtcChannel:didJoinedOfUid:elapsed:])(uid: 666), if the
method call is successful and the online media stream is injected into the channel.

 - The remote client:

   - [didJoinedOfUid]([WujiRtcChannelDelegate rtcChannel:didJoinedOfUid:elapsed:])(uid: 666), if the
method call is successful and the online media stream is injected into the channel.

 **Note:**

 - You can inject only one media stream into the channel at the same time.
 -
Ensure that you enable the RTMP Converter service before using this function. See [Prerequisites](https://docs.wuji.io/en/Interactive%20Broadcast/cdn_streaming_apple?platform=iOS#prerequisites).
 - This method applies to the Native SDK v2.4.1 and later.

 @param url    URL address to be added to the ongoing live broadcast. Valid protocols are RTMP, HLS,
and HTTP-FLV.

- Supported audio codec type: AAC.
- Supported video codec type: H264 (AVC).
 @param config WujiLiveInjectStreamConfig object which contains the configuration information for
the added voice or video stream.

@return * 0: Success.
* < 0: Failure.

    - `WujiErrorCodeInvalidArgument`(-2): The injected URL does not exist. Call this method again to
inject the stream and ensure that the URL is valid.
    - `WujiErrorCodeNotReady`(-3): The user is not in the channel.
    - `WujiErrorCodeNotSupported`(-4): The channel profile is not Live Broadcast.
    - `WujiErrorCodeNotInitialized`(-7): The SDK is not initialized. Ensure that the WujiRtcChannel
object is initialized before using this method.
 */
- (int)addInjectStreamUrl:(NSString *_Nonnull)url
                   config:(WujiLiveInjectStreamConfig *_Nonnull)config;
/** Removes the voice or video stream RTMP URL address from a live broadcast.

 This method removes the URL address (added by the [addInjectStreamUrl]([WujiRtcChannel
 addInjectStreamUrl:config:]) method) from a live broadcast.

 If this method call is successful, the SDK triggers the [didOfflineOfUid]([WujiRtcChannelDelegate
 rtcChannel:didOfflineOfUid:reason:]) callback and returns a stream uid of 666.

 @param url URL address of the added stream to be removed.

 @return * 0: Success.
 * < 0: Failure.
 */
- (int)removeInjectStreamUrl:(NSString *_Nonnull)url;
/** Publishes the local stream to the CDN.

 This method call triggers the [rtmpStreamingChangedToState]([WujiRtcChannelDelegate
 rtcChannel:rtmpStreamingChangedToState:state:errorCode:]) callback on the local client to report
 the state of adding a local stream to the CDN.

 **Note:**

 - This method applies to live-broadcast profile only.
 - Ensure that the user joins the channel before calling this method.
 - Ensure that you enable the RTMP Converter service before using this function. See
 [Prerequisites](https://docs.wuji.io/en/Interactive%20Broadcast/cdn_streaming_apple?platform=iOS#prerequisites).
 - This method adds only one stream URL each time it is called.

 @param url  The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024
 bytes. The RTMP URL address must not contain special characters, such as Chinese language
 characters.
 @param transcodingEnabled Sets whether transcoding is enabled/disabled:

 - YES: Enable transcoding. To
 [transcode](https://docs.wuji.io/en/Wuji%20Platform/terms?platform=All%20Platforms#transcoding) the
 audio or video streams when publishing them to CDN live, often used for combining the audio and
 video streams of multiple hosts in CDN live. If you set this parameter as `YES`, ensure that you
 call the [setLiveTranscoding]([WujiRtcChannel setLiveTranscoding:]) method before this method.
 - NO: Disable transcoding.

 @return * 0: Success.
 * < 0: Failure.

  - `WujiErrorCodeInvalidArgument`(-2): Invalid parameter. The URL is nil or the string length is 0.
  - `WujiErrorCodeNotInitialized`(-7): You have not initialized the RTC Engine when publishing the
 stream.
 */
- (int)addPublishStreamUrl:(NSString *_Nonnull)url transcodingEnabled:(BOOL)transcodingEnabled;
/** Removes an RTMP stream from the CDN.

This method removes the RTMP URL address added by the [addPublishStreamUrl]([WujiRtcChannel
addPublishStreamUrl:transcodingEnabled:]) method from a CDN live stream.

This method call triggers the [rtmpStreamingChangedToState]([WujiRtcChannelDelegate
rtcChannel:rtmpStreamingChangedToState:state:errorCode:]) callback on the local client to report the
state of removing an RTMP stream from the CDN.

 **Note:**

 * This method applies to live-broadcast profile only.
 * This method removes only one URL each time it is called.
 * The URL must not contain special characters, such as Chinese language characters.

 @param url The RTMP URL address to be removed. The maximum length of this parameter is 1024 bytes.

 @return * 0: Success.
 * < 0: Failure.
 */
- (int)removePublishStreamUrl:(NSString *_Nonnull)url;
/** Sets the video layout and audio settings for CDN live. (CDN live only.)

 The SDK triggers the [rtcEngineTranscodingUpdated]([WujiRtcEngineDelegate
 rtcEngineTranscodingUpdated:]) callback when you call the `setLiveTranscoding` method to update the
 transcoding setting.

 **Note**

 - This method applies to live-broadcast profile only.
 - Ensure that you enable the RTMP Converter service before using this function. See
 [Prerequisites](https://docs.wuji.io/en/Interactive%20Broadcast/cdn_streaming_apple?platform=iOS#prerequisites).
 - If you call the `setLiveTranscoding` method to update the transcoding setting for the first time,
 the SDK does not trigger the `rtcEngineTranscodingUpdated` callback.

 @param transcoding Sets the CDN live audio/video transcoding settings. See WujiLiveTranscoding.

 @return * 0: Success.
 * < 0: Failure.
 */
- (int)setLiveTranscoding:(WujiLiveTranscoding *_Nullable)transcoding;
/** Creates a data stream.

 Each user can create up to five data streams during the lifecycle of the
[WujiRtcChannel](WujiRtcChannel).

 **Note:**

 Set both the `reliable` and `ordered` parameters to `YES` or `NO`. Do not set one as `YES` and the
other as `NO`.

 @param streamId ID of the created data stream.
 @param reliable Sets whether or not the recipients are guaranteed to receive the data stream from
the sender within five seconds:

 * YES: The recipients receive the data stream from the sender within five seconds. If the recipient
does not receive the data stream within five seconds, an error is reported to the app.
 * NO: There is no guarantee that the recipients receive the data stream within five seconds and no
error message is reported for any delay or missing data stream.

 @param ordered  Sets whether or not the recipients receive the data stream in the sent order:

 * YES: The recipients receive the data stream in the sent order.
 * NO: The recipients do not receive the data stream in the sent order.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)createDataStream:(NSInteger *_Nonnull)streamId reliable:(BOOL)reliable ordered:(BOOL)ordered;
/** Sends data stream messages to all users in a channel.

The SDK has the following restrictions on this method:

* Up to 30 packets can be sent per second in a channel with each packet having a maximum size of 1
kB.
* Each client can send up to 6 kB of data per second.
* Each user can have up to five data streams simultaneously.

A successful `sendStreamMessage` method call triggers the
[receiveStreamMessageFromUid]([WujiRtcChannelDelegate
rtcChannel:receiveStreamMessageFromUid:streamId:data:]) callback on the remote client, from which
the remote user gets the stream message.

A failed `sendStreamMessage` method call triggers the
[didOccurStreamMessageErrorFromUid]([WujiRtcChannelDelegate
rtcChannel:didOccurStreamMessageErrorFromUid:streamId:error:missed:cached:]) callback on the remote
client.

 **Note**

 * This method applies only to the Communication profile or to the hosts in the Live-broadcast
profile. If an audience in the Live-broadcast profile calls this method, the audience role may be
changed to a host.
 * Ensure that you have created the data stream using
[createDataStream](createDataStream:reliable:ordered:) before calling this method.

 @param streamId ID of the sent data stream returned in the [createDataStream]([WujiRtcChannel
createDataStream:reliable:ordered:]) method.
 @param data Sent data.

 @return * 0: Success.
 * < 0: Failure.
 */
- (int)sendStreamMessage:(NSInteger)streamId data:(NSData *_Nonnull)data;
/** Starts to relay media streams across channels.

 After a successful method call, the SDK triggers the
 [channelMediaRelayStateDidChange]([WujiRtcChannelDelegate
 rtcChannel:channelMediaRelayStateDidChange:error:]) and
 [didReceiveChannelMediaRelayEvent]([WujiRtcChannelDelegate
 rtcChannel:didReceiveChannelMediaRelayEvent:]) callbacks, and these callbacks return the state and
 events of the media stream relay.

 - If the `channelMediaRelayStateDidChange` callback returns WujiChannelMediaRelayStateRunning(2)
 and WujiChannelMediaRelayStateIdle(0), and the `didReceiveChannelMediaRelayEvent` callback returns
 WujiChannelMediaRelayEventSentToDestinationChannel(4), the SDK starts relaying media streams
 between the original and the destination channel.
 - If the `channelMediaRelayStateDidChange` callback returns WujiChannelMediaRelayStateFailure(3),
 an exception occurs during the media stream relay.

 **Note**

 - Call this method after the [joinChannelByToken]([WujiRtcChannel
 joinChannelByToken:info:uid:options:]) method.
 - This method takes effect only when you are a broadcaster in a Live-broadcast channel.
 - After a successful method call, if you want to call this method again, ensure that you call the
 [stopChannelMediaRelay]([WujiRtcChannel stopChannelMediaRelay]) method to quit the current relay.
 - Contact sales-us@wuji.io before implementing this function.
 - We do not support string user accounts in this API.

 @param config The configuration of the media stream relay:
 [WujiChannelMediaRelayConfiguration](WujiChannelMediaRelayConfiguration).

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)startChannelMediaRelay:(WujiChannelMediaRelayConfiguration *_Nonnull)config;
/** Updates the channels for media stream relay.

 After the channel media relay starts, if you want to relay the media stream to more channels, or
 leave the current relay channel, you can call the `updateChannelMediaRelay` method.

 After a successful method call, the SDK triggers the
 [didReceiveChannelMediaRelayEvent]([WujiRtcChannelDelegate
 rtcChannel:didReceiveChannelMediaRelayEvent:]) callback with the
 WujiChannelMediaRelayEventUpdateDestinationChannel(7) state code.

 **Note**

 - Call this method after the [startChannelMediaRelay]([WujiRtcChannel startChannelMediaRelay:])
 method to update the destination channel.
 - This method supports adding at most four destination channels in the relay. If there are already
 four destination channels in the relay, remove the unnecessary ones with the
 `removeDestinationInfoForChannelName` method in channelMediaRelayConfiguration before calling this
 method.

 @param config The media stream relay configuration:
 [WujiChannelMediaRelayConfiguration](WujiChannelMediaRelayConfiguration).

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)updateChannelMediaRelay:(WujiChannelMediaRelayConfiguration *_Nonnull)config;
/** Stops the media stream relay.

 Once the relay stops, the broadcaster quits all the destination channels.

 After a successful method call, the SDK triggers the
 [channelMediaRelayStateDidChange]([WujiRtcChannelDelegate
 rtcChannel:channelMediaRelayStateDidChange:error:]) callback. If the callback returns
 WujiChannelMediaRelayStateIdle(0) and WujiChannelMediaRelayErrorNone(0), the broadcaster
 successfully stops the relay.

 @note If the method call fails, the SDK triggers the `channelMediaRelayStateDidChange` callback
 with the WujiChannelMediaRelayErrorServerNoResponse(2) or
 WujiChannelMediaRelayEventUpdateDestinationChannelRefused(8) state code. You can leave the channel
 by calling the [leaveChannel]([WujiRtcChannel leaveChannel]) method, and the media stream relay
 automatically stops.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)stopChannelMediaRelay;

#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
- (int)enableRemoteSuperResolution:(NSUInteger)uid enabled:(BOOL)enabled;
#endif

/** Customizes the remote video renderer for the WujiRtcChannel object.

 During real-time engagements, the Wuji SDK enables the default video sink to render the video. In
 the multi-channel scenario, if you want to customize the video renderer, you can create a
 customized video sink using WujiVideoSinkProtocol, and call `setRemoteVideoRenderer` to add the
 customized sink into the WujiRtcChannel object.

 @param videoRenderer The customized remote video renderer: WujiVideoSinkProtocol.
 @param userId The ID of the remote user.
 */
- (void)setRemoteVideoRenderer:(id<WujiVideoSinkProtocol> _Nullable)videoRenderer
                     forUserId:(NSUInteger)userId;

/** Gets the customized remote video renderer for the WujiRtcChannel object.

 @param userId The ID of the remote user.

 @return The customized remote video renderer: WujiVideoSourceProtocol.
*/
- (id<WujiVideoSinkProtocol> _Nullable)remoteVideoRendererOfUserId:(NSUInteger)userId;

/** Sets the data source of the metadata.

 You need to implement the [WujiMediaMetadataDataSource](WujiMediaMetadataDataSource) protocol and
 specify the type of metadata in this method.

 Use this method with the [setMediaMetadataDelegate]([WujiRtcChannel
 setMediaMetadataDelegate:withType:]) method to add synchronized metadata in the video stream. You
 can create more diversified live broadcast interactions, such as sending shopping links, digital
 coupons, and online quizzes.

 **Note**

 - Call this method before the [joinChannelByToken]([WujiRtcChannel
 joinChannelByToken:info:uid:options:]) method.
 - This method applies to the live broadcast channel profile only.

 @param metadataDataSource The WujiMediaMetadataDataSource protocol.
 @param type The metadata type. See [WujiMetadataType](WujiMetadataType). Currently, the SDK
 supports video metadata only.

 @return * YES: Success.
 * NO: Failure.
 */
- (BOOL)setMediaMetadataDataSource:(id<WujiMediaMetadataDataSource> _Nullable)metadataDataSource
                          withType:(WujiMetadataType)type;
/** Sets the delegate of the metadata.

 You need to implement the WujiMediaMetadataDelegate protocol and specify the type of metadata in
 this method.

 **Note**

 - Call this method before the [joinChannelByToken]([WujiRtcChannel
 joinChannelByToken:info:uid:options:]) method.
 - This method applies to the live broadcast channel profile only.

 @param metadataDelegate The WujiMediaMetadataDelegate protocol.
 @param type The metadata type. See [WujiMetadataType](WujiMetadataType). Currently, the SDK
 supports video metadata only.

 @return * YES: Success.
 * NO: Failure.
 */
- (BOOL)setMediaMetadataDelegate:(id<WujiMediaMetadataDelegate> _Nullable)metadataDelegate
                        withType:(WujiMetadataType)type;

@end
/** The WujiRtcChannelDelegate class.

 **Since** v3.0.0.
 */
@protocol WujiRtcChannelDelegate <NSObject>
@optional
/** Reports a warning during SDK runtime.

 In most cases, the app can ignore the warning reported by the SDK because the SDK can usually fix
 the issue and resume running.

 For instance, the SDK may report an WujiWarningCodeOpenChannelTimeout(106) warning upon
 disconnection from the server and attempts to reconnect.

 See [WujiWarningCode](WujiWarningCode).

 @param rtcChannel WujiRtcChannel
 @param warningCode Warning code: WujiWarningCode
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    didOccurWarning:(WujiWarningCode)warningCode;
/** Reports an error during SDK runtime.

In most cases, the SDK cannot fix the issue and resume running. The SDK requires the app to take
action or informs the user about the issue.

For example, the SDK reports an WujiErrorCodeStartCall = 1002 error when failing to initialize a
call. The app informs the user that the call initialization failed and invokes the
[leaveChannel]([WujiRtcChannel leaveChannel]) method to leave the channel.

See [WujiErrorCode](WujiErrorCode).

 @param rtcChannel WujiRtcChannel
 @param errorCode Error code: WujiErrorCode
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel didOccurError:(WujiErrorCode)errorCode;
/** Occurs when the local user joins a specified channel.

 @param rtcChannel WujiRtcChannel
 @param uid User ID. If the `uid` is specified in the [joinChannelByToken]([WujiRtcChannel
 joinChannelByToken:info:uid:options:]) method, the specified user ID is returned. If the user ID is
 not specified when the `joinChannelByToken` method is called, the server automatically assigns a
 `uid`.
 @param elapsed Time elapsed (ms) from the user calling the `joinChannelByToken` method until the
 SDK triggers this callback.
 */
- (void)rtcChannelDidJoinChannel:(WujiRtcChannel *_Nonnull)rtcChannel
                         withUid:(NSUInteger)uid
                         elapsed:(NSInteger)elapsed;
/** Occurs when the local user rejoins a channel.

 If the client loses connection with the server because of network problems, the SDK automatically
 attempts to reconnect and then triggers this callback upon reconnection, indicating that the user
 rejoins the channel with the assigned channel ID and user ID.

 @param rtcChannel WujiRtcChannel
 @param uid     User ID. If the `uid` is specified in the [joinChannelByToken]([WujiRtcChannel
 joinChannelByToken:info:uid:options:]) method, the specified user ID is returned. If the user ID is
 not specified when the `joinChannelByToken` method is called, the server automatically assigns a
 `uid`.
 @param elapsed Time elapsed (ms) from starting to reconnect to a successful reconnection.
 */
- (void)rtcChannelDidRejoinChannel:(WujiRtcChannel *_Nonnull)rtcChannel
                           withUid:(NSUInteger)uid
                           elapsed:(NSInteger)elapsed;
/** Occurs when the local user leaves a channel.

 When the app calls the [leaveChannel]([WujiRtcChannel leaveChannel]) method, this callback notifies
 the app that a user leaves a channel.

 With this callback, the app retrieves information, such as the call duration and the statistics.

 @param rtcChannel WujiRtcChannel
 @param stats  Statistics of the call: [WujiChannelStats](WujiChannelStats).
 */
- (void)rtcChannelDidLeaveChannel:(WujiRtcChannel *_Nonnull)rtcChannel
                        withStats:(WujiChannelStats *_Nonnull)stats;
/** Occurs when the local user role switches in a live broadcast.

The SDK triggers this callback when the local user switches the user role by calling the
[setClientRole]([WujiRtcChannel setClientRole:]) method after joining the channel.

 @param rtcChannel WujiRtcChannel
 @param oldRole Role that the user switches from: WujiClientRole.
 @param newRole Role that the user switches to: WujiClientRole.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    didClientRoleChanged:(WujiClientRole)oldRole
                 newRole:(WujiClientRole)newRole;
/** Occurs when a remote user or host joins a channel.

 - Communication profile: This callback notifies the app that another user joins the channel. If
 other users are already in the channel, the SDK also reports to the app on the existing users.
 - Live-broadcast profile: This callback notifies the app that a host joins the channel. If other
 hosts are already in the channel, the SDK also reports to the app on the existing hosts. Wuji
 recommends limiting the number of hosts to 17.

 The SDK triggers this callback under one of the following circumstances:
 - A remote user/host joins the channel by calling the [joinChannelByToken]([WujiRtcChannel
 joinChannelByToken:info:uid:options:]) method.
 - A remote user switches the user role to the host by calling the [setClientRole]([WujiRtcChannel
 setClientRole:]) method after joining the channel.
 - A remote user/host rejoins the channel after a network interruption.
 - A host injects an online media stream into the channel by calling the
 [addInjectStreamUrl]([WujiRtcChannel addInjectStreamUrl:config:]) method.

 **Note**

 Live-broadcast profile:

 * The host receives this callback when another host joins the channel.
 * The audience in the channel receives this callback when a new host joins the channel.
 * When a web application joins the channel, the SDK triggers this callback as long as the web
 application publishes streams.

 @param rtcChannel WujiRtcChannel
 @param uid     ID of the user or host who joins the channel. If the `uid` is specified in the
 `joinChannelByToken` method, the specified user ID is returned. If the `uid` is not specified in
 the `joinChannelByToken` method, the Wuji server automatically assigns a `uid`.
 @param elapsed Time elapsed (ms) from the local user calling the `joinChannelByToken` method until
 the SDK triggers this callback.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    didJoinedOfUid:(NSUInteger)uid
           elapsed:(NSInteger)elapsed;
/** Occurs when a remote user (Communication)/host (Live Broadcast) leaves a channel.

There are two reasons for users to be offline:

- Leave a channel: When the user/host leaves a channel, the user/host sends a goodbye message. When
the message is received, the SDK assumes that the user/host leaves a channel.
- Drop offline: When no data packet of the user or host is received for a certain period of time (20
seconds for the Communication profile, and more for the Live-broadcast profile), the SDK assumes
that the user/host drops offline. Unreliable network connections may lead to false detections, so
Wuji recommends using the [Wuji RTM
SDK](https://docs.wuji.io/en/Real-time-Messaging/product_rtm?platform=All%20Platforms) for more
reliable offline detection.

 @param rtcChannel WujiRtcChannel
 @param uid    ID of the user or host who leaves a channel or goes offline.
 @param reason Reason why the user goes offline, see WujiUserOfflineReason.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    didOfflineOfUid:(NSUInteger)uid
             reason:(WujiUserOfflineReason)reason;
/** Occurs when the network connection state changes.

The SDK triggers this callback to report on the current network connection state when it changes,
and the reason of the change.

@param rtcChannel WujiRtcChannel
@param state The current network connection state, see WujiConnectionStateType.
@param reason The reason of the connection state change, see WujiConnectionChangedReason.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    connectionChangedToState:(WujiConnectionStateType)state
                      reason:(WujiConnectionChangedReason)reason;
/** Occurs when the SDK cannot reconnect to Wuji's edge server 10 seconds after its connection to
the server is interrupted.

The SDK triggers this callback when it cannot connect to the server 10 seconds after calling the
[joinChannelByToken]([WujiRtcChannel joinChannelByToken:info:uid:options:]) method, regardless of
whether it is in the channel or not.

If the SDK fails to rejoin the channel 20 minutes after being disconnected from Wuji's edge server,
the SDK stops rejoining the channel.

@param rtcChannel WujiRtcChannel
 */
- (void)rtcChannelDidLost:(WujiRtcChannel *_Nonnull)rtcChannel;
/** Occurs when the token expires in 30 seconds.

 The user becomes offline if the `token` used in the [joinChannelByToken]([WujiRtcChannel
 joinChannelByToken:info:uid:options:]) method expires. The SDK triggers this callback 30 seconds
 before the `token` expires to remind the app to get a new `token`. Upon receiving this callback,
 generate a new `token` on the server and call the [renewToken]([WujiRtcChannel renewToken:]) method
 to pass the new `token` to the SDK.

 @param rtcChannel WujiRtcChannel
 @param token  The `token` that expires in 30 seconds.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    tokenPrivilegeWillExpire:(NSString *_Nonnull)token;
/** Occurs when the token expires.

 After a `token` is specified by calling the [joinChannelByToken]([WujiRtcChannel
 joinChannelByToken:info:uid:options:]) method, if the SDK losses connection to the Wuji server due
 to network issues, the `token` may expire after a certain period of time and a new `token` may be
 required to reconnect to the server.

 The SDK triggers this callback to notify the app to generate a new `token`. Call the
 [renewToken]([WujiRtcChannel renewToken:]) method to renew the `token`.

 @param rtcChannel WujiRtcChannel
 */
- (void)rtcChannelRequestToken:(WujiRtcChannel *_Nonnull)rtcChannel;
/** Reports which user is the loudest speaker over a period of time.

This callback reports the speaker with the highest accumulative volume during a certain period.
If the user enables the audio volume indication by calling the `enableAudioVolumeIndication` method,
this callback returns the user ID of the active speaker whose voice is detected by the audio volume
detection module of the SDK.

**Note:**

* To receive this callback, you need to call the `enableAudioVolumeIndication` method.
* This callback returns the user ID of the user with the highest voice volume during a period of
time, instead of at the moment.
 @param rtcChannel WujiRtcChannel
 @param speakerUid The user ID of the active speaker. A `speakerUid` of 0 represents the local user.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel activeSpeaker:(NSUInteger)speakerUid;
/** Occurs when the video size or rotation of a specific remote user changes.

 @param rtcChannel WujiRtcChannel
 @param uid      User ID of the remote user or local user (0) whose video size or rotation changes.
 @param size     New video size.
 @param rotation New rotation of the video. The value ranges between 0 and 360.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    videoSizeChangedOfUid:(NSUInteger)uid
                     size:(CGSize)size
                 rotation:(NSInteger)rotation;
/** Occurs when the remote video state changes.

 @param rtcChannel WujiRtcChannel
 @param uid ID of the remote user whose video state changes.
 @param state The state of the remote video. See [WujiVideoRemoteState](WujiVideoRemoteState).
 @param reason The reason of the remote video state change. See
 [WujiVideoRemoteStateReason](WujiVideoRemoteStateReason).
 @param elapsed The time elapsed (ms) from the local user calling the
 [joinChannelByToken]([WujiRtcChannel joinChannelByToken:info:uid:options:]) method until the SDK
 triggers this callback.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    remoteVideoStateChangedOfUid:(NSUInteger)uid
                           state:(WujiVideoRemoteState)state
                          reason:(WujiVideoRemoteStateReason)reason
                         elapsed:(NSInteger)elapsed;
;
/** Occurs when the local audio state changes.

 This callback indicates the state change of the local audio stream, including the state of the
 audio recording and encoding, and allows you to troubleshoot issues when exceptions occur.

 @param rtcChannel WujiRtcChannel
 @param uid ID of the remote user whose audio state changes.
 @param state  State of the remote audio. See [WujiAudioRemoteState](WujiAudioRemoteState).
 @param reason The reason of the remote audio state change. See
 [WujiAudioRemoteStateReason](WujiAudioRemoteStateReason).
 @param elapsed Time elapsed (ms) from the local user calling the
 [joinChannelByToken]([WujiRtcChannel joinChannelByToken:info:uid:options:]) method until the SDK
 triggers this callback.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    remoteAudioStateChangedOfUid:(NSUInteger)uid
                           state:(WujiAudioRemoteState)state
                          reason:(WujiAudioRemoteStateReason)reason
                         elapsed:(NSInteger)elapsed;
/** Occurs when the published video stream falls back to an audio-only stream due to unreliable
 network conditions or switches back to the video when the network conditions improve.

 If you call the [setLocalPublishFallbackOption]([WujiRtcEngineKit setLocalPublishFallbackOption:])
 method and set `option` as WujiStreamFallbackOptionAudioOnly, the SDK triggers this callback when
 the published stream falls back to audio-only mode due to unreliable uplink conditions, or when the
 audio stream switches back to the video when the uplink network condition improves.

 **Note**

 Once the published stream falls back to audio only, the remote app receives the
 [userMuteVideoBlock]([WujiRtcEngineKit userMuteVideoBlock:]) callback.

 @param rtcChannel WujiRtcChannel
 @param isFallbackOrRecover Whether the published stream falls back to audio-only or switches back
 to the video:

 * YES: The published stream falls back to audio-only due to unreliable network conditions.
 * NO: The published stream switches back to the video after the network conditions improve.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    didLocalPublishFallbackToAudioOnly:(BOOL)isFallbackOrRecover;
/** Occurs when the remote video stream falls back to an audio-only stream due to unreliable network
 conditions or switches back to the video after the network conditions improve.

 If you call [setRemoteSubscribeFallbackOption]([WujiRtcEngineKit
 setRemoteSubscribeFallbackOption:]) and set `option` as `WujiStreamFallbackOptionAudioOnly`, the
 SDK triggers this callback when the remote media stream falls back to audio only due to unreliable
 network conditions or switches back to the video after the network condition improves.

 **Note:**

 Once the remote media stream is switched to the low stream due to unreliable network conditions,
 you can monitor the stream switch between a high stream and low stream in the
 [remoteVideoStats]([WujiRtcChannelDelegate rtcChannel:remoteVideoStats:]) callback.

 @param rtcChannel WujiRtcChannel
 @param isFallbackOrRecover Whether the remote media stream falls back to audio-only or switches
 back to the video:

 * YES: The remote media stream falls back to audio-only due to unreliable network conditions.
 * NO: The remote media stream switches back to the video stream after the network conditions
 improve.
 @param uid ID of the remote user sending the stream.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    didRemoteSubscribeFallbackToAudioOnly:(BOOL)isFallbackOrRecover
                                    byUid:(NSUInteger)uid;
/** Reports the statistics of the current call. The SDK triggers this callback once every two
 seconds after the user joins the channel.

 @param rtcChannel WujiRtcChannel
 @param stats  Statistics of the WujiRtcEngineKit: [WujiChannelStats](WujiChannelStats).
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    reportRtcStats:(WujiChannelStats *_Nonnull)stats;
/** Reports the last mile network quality of each user in the channel once every two seconds.

 Last mile refers to the connection between the local device and Wuji's edge server. The SDK
 triggers this callback once every two seconds to report the last mile network conditions of each
 user in the channel. If a channel includes multiple users, the SDK triggers this callback as many
 times.

 @param rtcChannel WujiRtcChannel
 @param uid       User ID. The network quality of the user with this `uid` is reported. If `uid` is
 0, the local network quality is reported.
 @param txQuality Uplink transmission quality of the user in terms of the transmission bitrate,
 packet loss rate, average RTT (Round-Trip Time), and jitter of the uplink network. `txQuality` is a
 quality rating helping you understand how well the current uplink network conditions can support
 the selected WujiVideoEncoderConfiguration. For example, a 1000-Kbps uplink network may be adequate
 for video frames with a resolution of 640 * 480 and a frame rate of 15 fps in the Live-broadcast
 profile, but may be inadequate for resolutions higher than 1280 * 720. See  WujiNetworkQuality.
 @param rxQuality Downlink network quality rating of the user in terms of packet loss rate, average
 RTT, and jitter of the downlink network.  See WujiNetworkQuality.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    networkQuality:(NSUInteger)uid
         txQuality:(WujiNetworkQuality)txQuality
         rxQuality:(WujiNetworkQuality)rxQuality;
/** Reports the statistics of the video stream from each remote user/host.

 The SDK triggers this callback once every two seconds for each remote user/host. If a channel
includes multiple remote users, the SDK triggers this callback as many times.

 This callback reports the statistics more closely linked to the real-user experience of the video
transmission quality than the statistics that the [videoTransportStatsOfUid]([WujiRtcEngineDelegate
rtcEngine:videoTransportStatsOfUid:delay:lost:rxKBitRate:]) callback reports. This callback reports
more about media layer statistics such as the frame loss rate, while the `videoTransportStatsOfUid`
callback reports more about the transport layer statistics such as the packet loss rate.

Schemes such as FEC (Forward Error Correction) or retransmission counter the frame loss rate. Hence,
users may find the overall video quality acceptable even when the packet loss rate is high.

 @param rtcChannel WujiRtcChannel
 @param stats  Statistics of the received remote video streams. See
[WujiRtcRemoteVideoStats](WujiRtcRemoteVideoStats).
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    remoteVideoStats:(WujiRtcRemoteVideoStats *_Nonnull)stats;
/** Reports the statistics of the audio stream from each remote user/host.

 The SDK triggers this callback once every two seconds for each remote user/host. If a channel
includes multiple remote users, the SDK triggers this callback as many times.

 This callback reports the statistics more closely linked to the real-user experience of the audio
transmission quality than the statistics that the [audioTransportStatsOfUid]([WujiRtcEngineDelegate
rtcEngine:audioTransportStatsOfUid:delay:lost:rxKBitRate:]) callback reports. This callback reports
more about media layer statistics such as the frame loss rate, while the `audioTransportStatsOfUid`
callback reports more about the transport layer statistics such as the packet loss rate.

Schemes such as FEC (Forward Error Correction) or retransmission counter the frame loss rate. Hence,
users may find the overall audio quality acceptable even when the packet loss rate is high.

 @param rtcChannel WujiRtcChannel
 @param stats  Statistics of the received remote audio streams. See WujiRtcRemoteAudioStats.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    remoteAudioStats:(WujiRtcRemoteAudioStats *_Nonnull)stats;
/** Occurs when the state of the RTMP streaming changes.

The SDK triggers this callback to report the result of the local user calling the
[addPublishStreamUrl]([WujiRtcChannel addPublishStreamUrl:transcodingEnabled:]) or
[removePublishStreamUrl]([WujiRtcChannel removePublishStreamUrl:]) method.

This callback returns the URL and its current streaming state.

This callback indicates the state of the RTMP streaming. When exceptions occur, you can troubleshoot
issues by referring to the detailed error descriptions in the `errorCode` parameter.

@param rtcChannel WujiRtcChannel
@param url The RTMP URL address.
@param state The RTMP streaming state: WujiRtmpStreamingState. When the streaming state is
WujiRtmpStreamingStateFailure(4), see the `errorCode` parameter for details.
@param errorCode The detailed error information for streaming: WujiRtmpStreamingErrorCode.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    rtmpStreamingChangedToState:(NSString *_Nonnull)url
                          state:(WujiRtmpStreamingState)state
                      errorCode:(WujiRtmpStreamingErrorCode)errorCode;
/** Occurs when the CDN live streaming settings are updated.

 When the `LiveTranscoding` class in the [setLiveTranscoding]([WujiRtcChannel setLiveTranscoding:])
 method updates, the SDK triggers the `rtcChannelTranscodingUpdated` callback to report the update
 information to the local host.

 **Note:**

 If you call the `setLiveTranscoding` method to set the `LiveTranscoding` class for the first time,
 the SDK does not trigger the `rtcChannelTranscodingUpdated` callback.

 @param rtcChannel WujiRtcChannel
 */
- (void)rtcChannelTranscodingUpdated:(WujiRtcChannel *_Nonnull)rtcChannel;

#pragma mark Inject Stream URL Delegate Methods
/** Reports the status of injecting an online stream to a live broadcast.

@param rtcChannel WujiRtcChannel
@param url     URL address of the externally injected stream.
@param uid     User ID.
@param status  Status of the externally injected stream. See WujiInjectStreamStatus.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    streamInjectedStatusOfUrl:(NSString *_Nonnull)url
                          uid:(NSUInteger)uid
                       status:(WujiInjectStreamStatus)status;

#pragma mark Stream Message Delegate Methods

/** Occurs when the local user receives the data stream from a remote user within five seconds.

The SDK triggers this callback when the local user receives the stream message that the remote user
sends by calling the [sendStreamMessage]([WujiRtcChannel sendStreamMessage:data:]) method.

 @param rtcChannel WujiRtcChannel
 @param uid      User ID of the remote user sending the message.
 @param streamId Stream ID.
 @param data     Data received by the local user.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    receiveStreamMessageFromUid:(NSUInteger)uid
                       streamId:(NSInteger)streamId
                           data:(NSData *_Nonnull)data;
/** Occurs when the local user does not receive the data stream from the remote user within five
 seconds.

 The SDK triggers this callback when the local user fails to receive the stream message that the
 remote user sends by calling the [sendStreamMessage]([WujiRtcChannel sendStreamMessage:data:])
 method.

 @param rtcChannel WujiRtcChannel
 @param uid      User ID of the remote user sending the message.
 @param streamId Stream ID.
 @param error    Error code. See WujiErrorCode.
 @param missed Number of lost messages.
 @param cached Number of incoming cached messages when the data stream is interrupted.
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    didOccurStreamMessageErrorFromUid:(NSUInteger)uid
                             streamId:(NSInteger)streamId
                                error:(NSInteger)error
                               missed:(NSInteger)missed
                               cached:(NSInteger)cached;
/** Occurs when the state of the media stream relay changes.

 The SDK reports the state of the current media relay and possible error messages in this callback.

 @param rtcChannel WujiRtcChannel
 @param state The state code in [WujiChannelMediaRelayState](WujiChannelMediaRelayState).
 @param error The error code in [WujiChannelMediaRelayError](WujiChannelMediaRelayError).
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    channelMediaRelayStateDidChange:(WujiChannelMediaRelayState)state
                              error:(WujiChannelMediaRelayError)error;
/** Reports events during the media stream relay.

 @param rtcChannel WujiRtcChannel
 @param event The event code in [WujiChannelMediaRelayEvent](WujiChannelMediaRelayEvent).
 */
- (void)rtcChannel:(WujiRtcChannel *_Nonnull)rtcChannel
    didReceiveChannelMediaRelayEvent:(WujiChannelMediaRelayEvent)event;

@end
