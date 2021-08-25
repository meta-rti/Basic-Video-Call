//
//  WujiObjects.h
//  WujiRtcEngineKit
//
//  Copyright (c) 2018 Wuji. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import "WujiEnumerates.h"

#if defined (TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIView VIEW_CLASS;
typedef UIColor COLOR_CLASS;
#elif defined (TARGET_OS_MAC) && TARGET_OS_MAC
#import <AppKit/AppKit.h>
typedef NSView VIEW_CLASS;
typedef NSColor COLOR_CLASS;
#endif

/** Properties of the video canvas object.
 */
__attribute__((visibility("default"))) @interface WujiRtcVideoCanvas : NSObject
/** The video display view.

 VIEW_CLASS is a general name for this property. See the following definitions for iOS and macOS:

 - iOS: UIView
 - MacOS: NSView
 */
@property (strong, nonatomic) VIEW_CLASS* _Nullable view;
/** The rendering mode of the video view. See [WujiVideoRenderMode](WujiVideoRenderMode).
 */
@property (assign, nonatomic) WujiVideoRenderMode renderMode;
/** The unique channel name for the WujiRTC session in the string format. The string length must be less than 64 bytes. Supported character scopes are:
 
 - All lowercase English letters: a to z. 
 - All uppercase English letters: A to Z. 
 - All numeric characters: 0 to 9. 
 - The space character. 
 - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ",".
 <p>**Note**</p>

 - The default value is the empty string "". Use the default value if the user joins the channel using the [joinChannelByToken]([WujiRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method in the [WujiRtcEngineKit](WujiRtcEngineKit) class. The `WujiRtcVideoCanvas` struct defines the video canvas of the user in the channel.
 - If the user joins the channel using the [joinChannelByToken]([WujiRtcChannel joinChannelByToken:info:uid:options:]) method in the [WujiRtcChannel](WujiRtcChannel) class, set this parameter as the `channelID` of the `WujiRtcChannel` object. The `WujiRtcVideoCanvas` struct defines the video canvas of the user in the channel with the specified channel ID.
 */
@property (copy, nonatomic) NSString* _Nullable channelId;
/** User ID of the view.
 */
@property (assign, nonatomic) NSUInteger uid;
/** The mirror mode of the video view. See [WujiVideoMirrorMode](WujiVideoMirrorMode).
 
 **Note**
 
 - For the mirror mode of the local video view: If you use a front camera, the SDK enables the mirror mode by default; if you use a rear camera, the SDK disables the mirror mode by default.
 - For the mirror mode of the remote video view: The SDK disables the mirror mode by default.
 */
@property (assign, nonatomic) WujiVideoMirrorMode mirrorMode;
@end

/** The configurations of the last-mile network probe test. */
__attribute__((visibility("default"))) @interface WujiLastmileProbeConfig : NSObject
/** Sets whether or not to test the uplink network. Some users, for example, the audience in a Live-broadcast channel, do not need such a test.

- NO: disables the test.
- YES: enables the test.
*/
@property (assign, nonatomic) BOOL probeUplink;
/** Sets whether or not to test the downlink network.

- NO: disables the test.
- YES: enables the test.
*/
@property (assign, nonatomic) BOOL probeDownlink;
/** The expected maximum sending bitrate (bps) of the local user.

The value ranges between 100000 and 5000000. We recommend setting this parameter according to the bitrate value set by [setVideoEncoderConfiguration]([WujiRtcEngineKit setVideoEncoderConfiguration:]). */
@property (assign, nonatomic) NSUInteger expectedUplinkBitrate;
/** The expected maximum receiving bitrate (bps) of the local user.

The value ranges between 100000 and 5000000.
*/
@property (assign, nonatomic) NSUInteger expectedDownlinkBitrate;
@end

/** The last-mile network probe test result in one direction (uplink or downlink). */
__attribute__((visibility("default"))) @interface WujiLastmileProbeOneWayResult : NSObject
/** The packet loss rate (%). */
@property (assign, nonatomic) NSUInteger packetLossRate;
/** The network jitter (ms). */
@property (assign, nonatomic) NSUInteger jitter;
/** The estimated available bandwidth (Kbps). */
@property (assign, nonatomic) NSUInteger availableBandwidth;
@end

/** The uplink and downlink last-mile network probe test result. */
__attribute__((visibility("default"))) @interface WujiLastmileProbeResult : NSObject
/* The state of the probe test.

See [WujiLastmileProbeResultState](WujiLastmileProbeResultState).
*/
@property (assign, nonatomic) WujiLastmileProbeResultState state;
/** The round-trip delay time (ms). */
@property (assign, nonatomic) NSUInteger rtt;
/** The uplink last-mile network report

See [WujiLastmileProbeOneWayResult](WujiLastmileProbeOneWayResult).
*/
@property (strong, nonatomic) WujiLastmileProbeOneWayResult *_Nonnull uplinkReport;
/** The downlink last-mile network report

See [WujiLastmileProbeOneWayResult](WujiLastmileProbeOneWayResult).
*/
@property (strong, nonatomic) WujiLastmileProbeOneWayResult *_Nonnull downlinkReport;
@end

/** Statistics of the local video stream.
 */
__attribute__((visibility("default"))) @interface WujiRtcLocalVideoStats : NSObject
/** Bitrate (Kbps) sent in the reported interval, which does not include the bitrate of the retransmission video after packet loss. */
@property (assign, nonatomic) NSUInteger sentBitrate;
/** Frame rate (fps) sent in the reported interval, which does not include the frame rate of the retransmission video after packet loss. */
@property (assign, nonatomic) NSUInteger sentFrameRate;
/** The encoder output frame rate (fps) of the local video. */
@property (assign, nonatomic) NSUInteger encoderOutputFrameRate;
/** The renderer output frame rate (fps) of the local video. */
@property (assign, nonatomic) NSUInteger rendererOutputFrameRate;
/** The target bitrate (Kbps) of the current encoder. This value is estimated by the SDK based on the current network conditions. */
@property (assign, nonatomic) NSUInteger sentTargetBitrate;
/** The target frame rate (fps) of the current encoder. */
@property (assign, nonatomic) NSUInteger sentTargetFrameRate;
/** Quality change of the local video in terms of target frame rate and target bit rate in this reported interval, see [WujiVideoQualityAdaptIndication](WujiVideoQualityAdaptIndication). */
@property (assign, nonatomic) WujiVideoQualityAdaptIndication qualityAdaptIndication;
/** The encoding bitrate (Kbps), which does not include the bitrate of the re-transmission video after packet loss.
 */
@property (assign, nonatomic) NSUInteger encodedBitrate;
/** The width of the encoding frame (px).
 */
@property (assign, nonatomic) NSUInteger encodedFrameWidth;
/** The height of the encoding frame (px).
 */
@property (assign, nonatomic) NSUInteger encodedFrameHeight;
/** The value of the sent frames, represented by an aggregate value.
 */
@property (assign, nonatomic) NSUInteger encodedFrameCount;
/** The codec type of the local video：

 - WujiVideoCodecTypeVP8 = 1: VP8.
 - WujiVideoCodecTypeH264 = 2: (Default) H.264.
 */
@property (assign, nonatomic) WujiVideoCodecType codecType;
@end

/** Statistics of the remote video stream.
 */
__attribute__((visibility("default"))) @interface WujiRtcRemoteVideoStats : NSObject
/** User ID of the user sending the video streams.
 */
@property (assign, nonatomic) NSUInteger uid;
/** Time delay (ms). **DEPRECATED** In scenarios where audio and video is synchronized, you can use the value of `networkTransportDelay` and `jitterBufferDelay` in WujiRtcRemoteAudioStats to know the delay statistics of the remote video.
 */
@property (assign, nonatomic) NSUInteger __deprecated delay;
/** Width (pixels) of the video stream.
 */
@property (assign, nonatomic) NSUInteger width;
/** Height (pixels) of the video stream.
 */
@property (assign, nonatomic) NSUInteger height;
/** The average bitrate (Kbps) of the received video stream.
 */
@property (assign, nonatomic) NSUInteger receivedBitrate;
/** The decoder output frame rate (fps) of the remote video.
 */
@property (assign, nonatomic) NSUInteger decoderOutputFrameRate;
/** The renderer output frame rate (fps) of the remote video.
 */
@property (assign, nonatomic) NSUInteger rendererOutputFrameRate;
/** Packet loss rate (%) of the remote video stream after using the anti-packet-loss method.
 */
@property (assign, nonatomic) NSUInteger packetLossRate;
/** Video stream type (high-stream or low-stream).
 */
@property (assign, nonatomic) WujiVideoStreamType rxStreamType;
/** The total freeze time (ms) of the remote video stream after the remote user joins the channel. In a video session where the frame rate is set to no less than 5 fps, video freeze occurs when the time interval between two adjacent renderable video frames is more than 500 ms.
 */
@property (assign, nonatomic) NSUInteger totalFrozenTime;
/** The total video freeze time as a percentage (%) of the total time when the video is available.
 */
@property (assign, nonatomic) NSUInteger frozenRate;
/** The total time (ms) when the remote user in the Communication profile or the remote broadcaster in the Live-broadcast profile neither stops sending the video stream nor disables the video module after joining the channel.
 */
@property (assign, nonatomic) NSUInteger totalActiveTime;
@end

/** The statistics of the local audio stream.
 */
__attribute__((visibility("default"))) @interface WujiRtcLocalAudioStats : NSObject
/** The number of channels.
 */
@property (assign, nonatomic) NSUInteger numChannels;
/** The sample rate (Hz).
 */
@property (assign, nonatomic) NSUInteger sentSampleRate;
/** The average sending bitrate (Kbps).
 */
@property (assign, nonatomic) NSUInteger sentBitrate;
@end

/** The statistics of the remote audio stream.
 */
__attribute__((visibility("default"))) @interface WujiRtcRemoteAudioStats : NSObject
/** User ID of the user sending the audio stream.
 */
@property (assign, nonatomic) NSUInteger uid;
/** Audio quality received by the user.
 */
@property (assign, nonatomic) NSUInteger quality;
/** Network delay (ms) from the sender to the receiver.
 */
@property (assign, nonatomic) NSUInteger networkTransportDelay;
/** Network delay (ms) from the receiver to the jitter buffer.
 */
@property (assign, nonatomic) NSUInteger jitterBufferDelay;
/** The audio frame loss rate in the reported interval.
 */
@property (assign, nonatomic) NSUInteger audioLossRate;
/** The number of channels.
 */
@property (assign, nonatomic) NSUInteger numChannels;
/** The sample rate (Hz) of the received audio stream in the reported interval.
 */
@property (assign, nonatomic) NSUInteger receivedSampleRate;
/** The average bitrate (Kbps) of the received audio stream in the reported interval.
 */
@property (assign, nonatomic) NSUInteger receivedBitrate;
/** The total freeze time (ms) of the remote audio stream after the remote user joins the channel.
 */
@property (assign, nonatomic) NSUInteger totalFrozenTime;
/** The total audio freeze time as a percentage (%) of the total time when the audio is available.
 */
@property (assign, nonatomic) NSUInteger frozenRate;
/** The total time (ms) when the remote user in the Communication profile or the remote broadcaster in the Live-broadcast profile neither stops sending the audio stream nor disables the audio module after joining the channel.
 */
@property (assign, nonatomic) NSUInteger totalActiveTime;
@end

/** Properties of the audio volume information.
 */
__attribute__((visibility("default"))) @interface WujiRtcAudioVolumeInfo : NSObject
/** User ID of the speaker. The `uid` of the local user is 0.
 */
@property (assign, nonatomic) NSUInteger uid;
/** The sum of the voice volume and audio-mixing volume of the speaker. The value ranges between 0 (lowest volume) and 255 (highest volume).
 */
@property (assign, nonatomic) NSUInteger volume;
/** Voice activity status of the local user.

 - 0: The local user is not speaking.
 - 1: The local user is speaking.

 **Note**

 - The `vad` parameter cannot report the voice activity status of the remote users. In the remote users' callback, `vad` = 0.
 - Ensure that you set `report_vad(YES)` in the `enableAudioVolumeIndication` method to enable the voice activity detection of the local user.
 */
@property (assign, nonatomic) NSUInteger vad;
/** The channel ID, which indicates which channel the speaker is in.
 */
@property (copy, nonatomic) NSString * _Nonnull channelId;
@end

/** Statistics of the channel
 */
__attribute__((visibility("default"))) @interface WujiChannelStats: NSObject
/** Call duration (s), represented by an aggregate value.
 */
@property (assign, nonatomic) NSInteger duration;
/** Total number of bytes transmitted, represented by an aggregate value.
 */
@property (assign, nonatomic) NSInteger txBytes;
/** Total number of bytes received, represented by an aggregate value.
 */
@property (assign, nonatomic) NSInteger rxBytes;
/** Total number of audio bytes sent (bytes), represented by an aggregate value.
 */
@property (assign, nonatomic) NSInteger txAudioBytes;
/** Total number of video bytes sent (bytes), represented by an aggregate value.
 */
@property (assign, nonatomic) NSInteger txVideoBytes;
/** Total number of audio bytes received (bytes), represented by an aggregate value.
 */
@property (assign, nonatomic) NSInteger rxAudioBytes;
/** Total number of video bytes received (bytes), represented by an aggregate value.
 */
@property (assign, nonatomic) NSInteger rxVideoBytes;
/** Total packet transmission bitrate (Kbps), represented by an instantaneous value.
 */
@property (assign, nonatomic) NSInteger txKBitrate;
/** Total receive bitrate (Kbps), represented by an instantaneous value.
 */
@property (assign, nonatomic) NSInteger rxKBitrate;
/** Audio packet transmission bitrate (Kbps), represented by an instantaneous value.
 */
@property (assign, nonatomic) NSInteger txAudioKBitrate;
/** Audio receive bitrate (Kbps), represented by an instantaneous value.
 */
@property (assign, nonatomic) NSInteger rxAudioKBitrate;
/** Video transmission bitrate (Kbps), represented by an instantaneous value.
 */
@property (assign, nonatomic) NSInteger txVideoKBitrate;
/** Video receive bitrate (Kbps), represented by an instantaneous value.
 */
@property (assign, nonatomic) NSInteger rxVideoKBitrate;
/** Client-server latency (ms)
 */
@property (assign, nonatomic) NSInteger lastmileDelay;
/** The packet loss rate (%) from the local client to Wuji's edge server, before using the anti-packet-loss method.
 */
@property (assign, nonatomic) NSInteger txPacketLossRate;
/** The packet loss rate (%) from Wuji's edge server to the local client, before using the anti-packet-loss method.
 */
@property (assign, nonatomic) NSInteger rxPacketLossRate;
/** Number of users in the channel.

- Communication profile: The number of users in the channel.
- Live broadcast profile:

  - If the local user is an audience: The number of users in the channel = The number of hosts in the channel + 1.
  - If the user is a host: The number of users in the channel = The number of hosts in the channel.
 */
@property (assign, nonatomic) NSInteger userCount;
/** Application CPU usage (%).
 */
@property (assign, nonatomic) double cpuAppUsage;
/** System CPU usage (%).
 */
@property (assign, nonatomic) double cpuTotalUsage;
/** The round-trip time delay from the client to the local router.
 */
@property (assign, nonatomic) NSInteger gatewayRtt;
/** The memory usage ratio of the app (%).
 **Note** This value is for reference only. Due to system limitations, you may not get the value of this member.
 */
@property (assign, nonatomic) double memoryAppUsageRatio;
/** The memory usage ratio of the system (%). 
 **Note** This value is for reference only. Due to system limitations, you may not get the value of this member.
 */
@property (assign, nonatomic) double memoryTotalUsageRatio;
/** The memory usage of the app (KB). 
 **Note** This value is for reference only. Due to system limitations, you may not get the value of this member.
 */
@property (assign, nonatomic) NSInteger memoryAppUsageInKbytes;
@end

/** Properties of the video encoder configuration.
 */
__attribute__((visibility("default"))) @interface WujiVideoEncoderConfiguration: NSObject
/** The video frame dimension (px) used to specify the video quality in the total number of pixels along a frame's width and height. The default value is 640 * 360.

You can customize the dimension, or select from the following list:

 - WujiVideoDimension120x120
 - WujiVideoDimension160x120
 - WujiVideoDimension180x180
 - WujiVideoDimension240x180
 - WujiVideoDimension320x180
 - WujiVideoDimension240x240
 - WujiVideoDimension320x240
 - WujiVideoDimension424x240
 - WujiVideoDimension360x360
 - WujiVideoDimension480x360
 - WujiVideoDimension640x360
 - WujiVideoDimension480x480
 - WujiVideoDimension640x480
 - WujiVideoDimension840x480
 - WujiVideoDimension960x720
 - WujiVideoDimension1280x720
 - WujiVideoDimension1920x1080 (macOS only)
 - WujiVideoDimension2540x1440 (macOS only)
 - WujiVideoDimension3840x2160 (macOS only)

 Note:

 - The dimension does not specify the orientation mode of the output ratio. For how to set the video orientation, see [WujiVideoOutputOrientationMode](WujiVideoOutputOrientationMode).
 - Whether 720p can be supported depends on the device. If the device cannot support 720p, the frame rate will be lower than the one listed in the table. Wuji optimizes the video in lower-end devices.
 - iPhones do not support video frame dimensions above 720p.
 */
@property (assign, nonatomic) CGSize dimensions;

/** The frame rate of the video (fps). 

 You can either set the frame rate manually or choose from the following options. The default value is 15. We do not recommend setting this to a value greater than 30.

  *  WujiVideoFrameRateFps1(1): 1 fps
  *  WujiVideoFrameRateFps7(7): 7 fps
  *  WujiVideoFrameRateFps10(10): 10 fps
  *  WujiVideoFrameRateFps15(15): 15 fps
  *  WujiVideoFrameRateFps24(24): 24 fps
  *  WujiVideoFrameRateFps30(30): 30 fps
  *  WujiVideoFrameRateFps60(30): 60 fps (macOS only)
 */
@property (assign, nonatomic) NSInteger frameRate;

/** The minimum video encoder frame rate (fps).

The default value is DEFAULT_MIN_BITRATE(-1) (the SDK uses the lowest encoder frame rate). For information on scenarios and considerations, see *Set the Video Profile*.
*/
@property (assign, nonatomic) NSInteger minFrameRate;

/** The bitrate of the video.

 Sets the video bitrate (Kbps). Refer to the table below and set your bitrate. If you set a bitrate beyond the proper range, the SDK automatically adjusts it to a value within the range. You can also choose from the following options:

 - WujiVideoBitrateStandard: (recommended) the standard bitrate mode. In this mode, the bitrates differ between the Live-broadcast and Communication profiles:

     - Communication profile: the video bitrate is the same as the base bitrate.
     - Live-broadcast profile: the video bitrate is twice the base bitrate.

 - WujiVideoBitrateCompatible: the compatible bitrate mode. In this mode, the bitrate stays the same regardless of the profile. In the Live-broadcast profile, if you choose this mode, the video frame rate may be lower than the set value.

Wuji uses different video codecs for different profiles to optimize the user experience. For example, the Communication profile prioritizes the smoothness while the Live-broadcast profile prioritizes the video quality (a higher bitrate). Therefore, Wuji recommends setting this parameter as WujiVideoBitrateStandard.

**Video Bitrate Table**

| Resolution        	| Frame Rate (fps) 	| Base Bitrate (Kbps, for Communication) 	| Live Bitrate (Kbps, for Live Broadcast) 	|
|-------------------	|------------------	|----------------------------------------	|-----------------------------------------	|
| 160 * 120   	| 15               	| 65                                     	| 130                                     	|
| 120 * 120   	| 15               	| 50                                     	| 100                                     	|
| 320 * 180   	| 15               	| 140                                    	| 280                                     	|
| 180 * 180   	| 15               	| 100                                    	| 200                                     	|
| 240 * 180   	| 15               	| 120                                    	| 240                                     	|
| 320 * 240   	| 15               	| 200                                    	| 400                                     	|
| 240 * 240   	| 15               	| 140                                    	| 280                                     	|
| 424 * 240   	| 15               	| 220                                    	| 440                                     	|
| 640 * 360   	| 15               	| 400                                    	| 800                                     	|
| 360 * 360   	| 15               	| 260                                    	| 520                                     	|
| 640 * 360   	| 30               	| 600                                    	| 1200                                    	|
| 360 * 360   	| 30               	| 400                                    	| 800                                     	|
| 480 * 360   	| 15               	| 320                                    	| 640                                     	|
| 480 * 360   	| 30               	| 490                                    	| 980                                     	|
| 640 * 480   	| 15               	| 500                                    	| 1000                                    	|
| 480 * 480   	| 15               	| 400                                    	| 800                                     	|
| 640 * 480   	| 30               	| 750                                    	| 1500                                    	|
| 480 * 480   	| 30               	| 600                                    	| 1200                                    	|
| 848 * 480   	| 15               	| 610                                    	| 1220                                    	|
| 848 * 480   	| 30               	| 930                                    	| 1860                                    	|
| 640 * 480   	| 10               	| 400                                    	| 800                                     	|
| 1280 * 720  	| 15               	| 1130                                   	| 2260                                    	|
| 1280 * 720  	| 30               	| 1710                                   	| 3420                                    	|
| 960 * 720   	| 15               	| 910                                    	| 1820                                    	|
| 960 * 720   	| 30               	| 1380                                   	| 2760                                    	|
| 1920 * 1080 	| 15               	| 2080                                   	| 4160                                    	|
| 1920 * 1080 	| 30               	| 3150                                   	| 6300                                    	|
| 1920 * 1080 	| 60               	| 4780                                   	| 6500                                    	|
| 2560 * 1440 	| 30               	| 4850                                   	| 6500                                    	|
| 2560 * 1440 	| 60               	| 6500                                   	| 6500                                    	|
| 3840 * 2160 	| 30               	| 6500                                   	| 6500                                    	|
| 3840 * 2160 	| 60               	| 6500                                   	| 6500                                    	|


**Note:**

The base bitrate in this table applies to the Communication profile. The Live-broadcast profile generally requires a higher bitrate for better video quality. Wuji recommends setting the bitrate mode as WujiVideoBitrateStandard. You can also set the bitrate as twice the base bitrate.


*/
@property (assign, nonatomic) NSInteger bitrate;

/** The minimum encoding bitrate.

Sets the minimum encoding bitrate (Kbps).

The Wuji SDK automatically adjusts the encoding bitrate to adapt to network conditions. Using a value greater than the default value forces the video encoder to output high-quality images but may cause more packet loss and hence sacrifice the smoothness of the video transmission. Unless you have special requirements for image quality, Wuji does not recommend changing this value.

**Note:**

This parameter applies only to the Live-broadcast profile.*/
@property (assign, nonatomic) NSInteger minBitrate;

/** The video orientation mode of the video: WujiVideoOutputOrientationMode.

 * WujiVideoOutputOrientationModeAdaptative(0): (Default) The output video always follows the orientation of the captured video, because the receiver takes the rotational information passed on from the video encoder.
   - If the captured video is in landscape mode, the output video is in landscape mode.
   - If the captured video is in portrait mode, the output video is in portrait mode.
 * WujiVideoOutputOrientationModeFixedLandscape(1): The output video is always in landscape mode. If the captured video is in portrait mode, the video encoder crops it to fit the output. This applies to situations where the receiver cannot process the rotational information. For example, CDN live streaming.
 * WujiVideoOutputOrientationModeFixedPortrait(2): The output video is always in portrait mode. If the captured video is in landscape mode, the video encoder crops it to fit the output. This applies to situations where the receiver cannot process the rotational information. For example, CDN live streaming.

For scenarios with video rotation, Wuji provides *Rotate the Video* to guide users on how to set this parameter to get the preferred video orientation.

 */
@property (assign, nonatomic) WujiVideoOutputOrientationMode orientationMode;

/** The video encoding degradation preference under limited bandwidth.

WujiDegradationPreference:

* WujiDegradationMaintainQuality(0): (Default) Degrades the frame rate to guarantee the video quality.
* WujiDegradationMaintainFramerate(1): Degrades the video quality to guarantee the frame rate.
*/
@property (assign, nonatomic) WujiDegradationPreference degradationPreference;

/** Sets the mirror mode of the published local video stream. It only affects the video that the remote user sees. See [WujiVideoMirrorMode](WujiVideoMirrorMode).
 <p>**Note**</p>
 <p>The SDK disables the mirror mode by default.</p>
 */
@property (assign, nonatomic) WujiVideoMirrorMode mirrorMode;


/** Initializes and returns a newly allocated WujiVideoEncoderConfiguration object with the specified video resolution.

 @param size Video resolution.
 @param frameRate Video frame rate.
 @param bitrate Video bitrate.
 @param orientationMode WujiVideoOutputOrientationMode.
 @return An initialized WujiVideoEncoderConfiguration object.
 */
- (instancetype _Nonnull)initWithSize:(CGSize)size
                            frameRate:(WujiVideoFrameRate)frameRate
                              bitrate:(NSInteger)bitrate
                      orientationMode:(WujiVideoOutputOrientationMode)orientationMode;

/** Initializes and returns a newly allocated WujiVideoEncoderConfiguration object with the specified video width and height.

 @param width Width of the video.
 @param height Height of the video.
 @param frameRate Video frame rate.
 @param bitrate Video bitrate.
 @param orientationMode WujiVideoOutputOrientationMode.
 @return An initialized WujiVideoEncoderConfiguration object.
 */
- (instancetype _Nonnull)initWithWidth:(NSInteger)width
                                height:(NSInteger)height
                             frameRate:(WujiVideoFrameRate)frameRate
                               bitrate:(NSInteger)bitrate
                       orientationMode:(WujiVideoOutputOrientationMode)orientationMode;
@end

/** Properties of the screen sharing encoding parameters.
 */
__attribute__((visibility("default"))) @interface WujiScreenCaptureParameters: NSObject
/**  The maximum encoding dimensions for screen sharing.

The default value is 1920 * 1080 pixels, that is, 2073600 pixels. Wuji uses the value of this parameter to calculate the charges.

If the aspect ratio is different between the encoding dimensions and screen dimensions, Wuji applies the following algorithms for encoding. Suppose the encoding dimensions are 1920 * 1080:

- If the value of the screen dimensions is lower than that of the encoding dimensions, for example, 1000 * 1000, the SDK uses 1000 * 1000 for encoding.
- If the value of the screen dimensions is higher than that of the encoding dimensions, for example, 2000 * 1500, the SDK uses the maximum value under 1920 * 1080 with the aspect ratio of the screen dimension (4:3) for encoding, that is, 1440 * 1080.

In either case, Wuji uses the value of this parameter to calculate the charges.
 */
@property (assign, nonatomic) CGSize dimensions;

/** The frame rate (fps) of the shared region. The default value is 5. We do not recommend setting this to a value greater than 15.
 */
@property (assign, nonatomic) NSInteger frameRate;

/** The bitrate (Kbps) of the shared region. The default value is 0 (the SDK works out a bitrate according to the dimensions of the current screen).
 */
@property (assign, nonatomic) NSInteger bitrate;

/** Sets whether or not to capture the mouse for screen sharing.

- YES: (Default) Capture the mouse.
- NO: Do not capture the mouse.
 */
@property (assign, nonatomic) BOOL captureMouseCursor;

@end

/** A class for providing user-specific CDN live audio/video transcoding settings.
 */
__attribute__((visibility("default"))) @interface WujiLiveTranscodingUser: NSObject
/** User ID of the CDN live host.
 */
@property (assign, nonatomic) NSUInteger uid;
/** Size and the position of the video frame relative to the top left corner.
 */
@property (assign, nonatomic) CGRect rect;
/**  The layer index of the video frame.

 From v2.3.0, the Wuji SDK supports setting zOrder as 0.

 An integer. The value range is [0,100].

 - 0: (Default) Bottom layer.
 - 100: Top layer.

 Note: If the value is set lower than 0 or higher than 100, the `WujiErrorCodeInvalidArgument` error occurs.
 */
@property (assign, nonatomic) NSInteger zOrder;
/** The transparency level of the user's video.

 The value ranges between 0.0 and 1.0:

 * 0.0: Completely transparent.
 * 1.0: (Default) Opaque.
 */
@property (assign, nonatomic) double alpha;
/** The audio channel of the sound.

 The default value is 0:

    - 0: (Default) Supports dual channels. Depends on the upstream of the broadcaster.
    - 1: The audio stream of the broadcaster uses the FL audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels will be mixed into mono first.
    - 2: The audio stream of the broadcaster uses the FC audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels will be mixed into mono first.
    - 3: The audio stream of the broadcaster uses the FR audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels will be mixed into mono first.
    - 4: The audio stream of the broadcaster uses the BL audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels will be mixed into mono first.
    - 5: The audio stream of the broadcaster uses the BR audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels will be mixed into mono first.

Note: If your setting is not 0, you may need a specialized player.
 */
@property (assign, nonatomic) NSInteger audioChannel;
@end

/** Image properties.

 A class for setting the properties of the watermark and background images in live broadcasting.
 */
__attribute__((visibility("default"))) @interface WujiImage: NSObject
/** URL address of the image on the broadcasting video.

The maximum length of this parameter is 1024 bytes.
 */
@property (strong, nonatomic) NSURL *_Nonnull url;
/** Position and size of the image on the broadcasting video in CGRect.
 */
@property (assign, nonatomic) CGRect rect;
@end

/** The options of the watermark image to be added.
 */
__attribute__((visibility("default"))) @interface WatermarkOptions: NSObject
/** Sets whether or not the watermark image is visible in the local video preview: 
 
 - YES: (Default) The watermark image is visible in preview.
 - NO: The watermark image is not visible in preview. 
 */
@property (assign, nonatomic) BOOL visibleInPreview;
/** The watermark position in landscape mode of *Rotate the Video*. This parameter contains the following members:
  
  - `x`: The horizontal offset of the watermark from the top-left corner. 
  - `y`: The vertical offset of the watermark from the top-left corner. 
  - `width`: The width (pixel) of the watermark region. 
  - `height`: The height (pixel) of the watermark region. 
 */
@property (assign, nonatomic) CGRect positionInLandscapeMode;
/** The watermark position in portrait mode of *Rotate the Video*. This parameter contains the following members:
  
  - `x`: The horizontal offset of the watermark from the top-left corner. 
  - `y`: The vertical offset of the watermark from the top-left corner. 
  - `width`: The width (pixel) of the watermark region. 
  - `height`: The height (pixel) of the watermark region. 
 */
@property (assign, nonatomic) CGRect positionInPortraitMode;
@end


/** A class for managing user-specific CDN live audio/video transcoding settings.
 */
__attribute__((visibility("default"))) @interface WujiLiveTranscoding: NSObject
/** The size of the video (width and height in pixels).
 
- When pushing video streams to the CDN, ensure that both the width and height are at least 64; otherwise, the Wuji server adjusts the value to 64.
- When pushing audio streams to the CDN, set the width and height as 0.
 */
@property (assign, nonatomic) CGSize size;
/** Bitrate of the CDN live output video stream.

The default value is 400 Kbps.

Set this parameter according to the Video Bitrate Table. If you set a bitrate beyond the proper range, the SDK automatically adapts it to a value within the range.
 */
@property (assign, nonatomic) NSInteger videoBitrate;
/** Frame rate of the CDN live output video stream.

The default value is 15 fps, and the value range is (0,30]. 

@note The Wuji server adjusts any value over 30 to 30.
 */
@property (assign, nonatomic) NSInteger videoFramerate;
/** Latency mode. **DEPRECATED** from v2.8.0

 * YES: Low latency with unassured quality.
 * NO:（Default）High latency with assured quality.
 */
@property (assign, nonatomic) BOOL lowLatency;
/** Video GOP in frames. The default value is 30 fps. */
@property (assign, nonatomic) NSInteger videoGop;
/** Video codec profile type

Set it as 66, 77, or 100 (default), see [WujiVideoCodecProfileType](WujiVideoCodecProfileType).

If you set this parameter to other values, Wuji adjusts it to the default value of 100.
 */
@property (assign, nonatomic) WujiVideoCodecProfileType videoCodecProfile;

/** An WujiLiveTranscodingUser object managing the user layout configuration in the CDN live stream. Wuji supports a maximum of 17 transcoding users in a CDN live stream channel. See WujiLiveTranscodingUser.
 */
@property (copy, nonatomic) NSArray<WujiLiveTranscodingUser *> *_Nullable transcodingUsers;
/** Reserved property. Extra user-defined information to send SEI for the H.264/H.265 video stream to the CDN live client. Maximum length: 4096 bytes. For more information on SEI, see [SEI-related questions](https://docs.wuji.io/en/faq/sei).
 */
@property (copy, nonatomic) NSString *_Nullable transcodingExtraInfo;
/** The watermark image added to the CDN live publishing stream.

The audience of the CDN live publishing stream can see the watermark. Ensure that the format of the image is PNG.

See WujiImage for the definition of the watermark.
 */
@property (strong, nonatomic) WujiImage *_Nullable watermark;
/** The background image added to the CDN live publishing stream.

The audience of the CDN live publishing stream can see the background image. See WujiImage for the definition of the background image.
 */
@property (strong, nonatomic) WujiImage *_Nullable backgroundImage;
/** The background color in RGB hex.

Value only. Do not include a preceding #. For example, 0xFFB6C1 (light pink). The default value is 0x000000 (black).

COLOR_CLASS is a general name for the type:

* iOS: UIColor
* macOS: NSColor
 */
@property (strong, nonatomic) COLOR_CLASS *_Nullable backgroundColor;

/** Self-defined audio sample rate: WujiAudioSampleRateType.
 */
@property (assign, nonatomic) WujiAudioSampleRateType audioSampleRate;
/** Bitrate (Kbps) of the CDN live audio output stream. The default value is 48, and the highest value is 128.
 */
@property (assign, nonatomic) NSInteger audioBitrate;
/** The number of audio channels for the CDN live stream.
 
 Wuji recommends choosing 1 (mono), or 2 (stereo) audio channels. Special players are required if you choose 3, 4, or 5.

 * 1: (Default) Mono
 * 2: Stereo
 * 3: Three audio channels
 * 4: Four audio channels
 * 5: Five audio channels
 */
@property (assign, nonatomic) NSInteger audioChannels;
/**
 Audio codec profile. See WujiAudioCodecProfileType.

 The default value is WujiAudioCodecProfileLCAAC(0).
 */
@property (assign, nonatomic) WujiAudioCodecProfileType audioCodecProfile;

/** Creates a default transcoding object.

 @return Default WujiLiveTranscoding object.
 */
+(WujiLiveTranscoding *_Nonnull) defaultTranscoding;

-(int)addUser:(WujiLiveTranscodingUser * _Nonnull)user;

-(int)removeUser:(NSUInteger)uid;
@end

/** Configuration of the imported live broadcast voice or video stream.
 */
__attribute__((visibility("default"))) @interface WujiLiveInjectStreamConfig: NSObject
/** Size of the added stream to the broadcast.

The default value is 0; same size as the original stream.
 */
@property (assign, nonatomic) CGSize size;
/** Video GOP of the added stream to the broadcast.

The default value is 30 fps.
 */
@property (assign, nonatomic) NSInteger videoGop;
/** Video frame rate of the added stream to the broadcast.

The default value is 15 fps.
 */
@property (assign, nonatomic) NSInteger videoFramerate;
/** Video bitrate of the added stream to the broadcast.

The default value is 400 Kbps.

The setting of the video bitrate is closely linked to the resolution. If the video bitrate you set is beyond a reasonable range, the SDK will set it within a reasonable range instead.
 */
@property (assign, nonatomic) NSInteger videoBitrate;

/** Audio sample rate of the added stream to the broadcast.

The default value is 48000 Hz. See WujiAudioSampleRateType for details.

**Note:**

Wuji recommends using the default value.
 */
@property (assign, nonatomic) WujiAudioSampleRateType audioSampleRate;
/** Audio bitrate of the added stream to the broadcast.

The default value is 48 Kbps.

**Note:**

Wuji recommends using the default value.
 */
@property (assign, nonatomic) NSInteger audioBitrate;
/** Number of audio channels to add to the broadcast. The values are 1 and 2.

The default value is 1.

**Note:**

Wuji recommends using the default value.
 */
@property (assign, nonatomic) NSInteger audioChannels;

/** Creates a default stream configuration object.

 @return Default stream configuration object.
 */
+(WujiLiveInjectStreamConfig *_Nonnull) defaultConfig;
@end

/** the configuration of camera capturer.
 */
__attribute__((visibility("default"))) @interface WujiCameraCapturerConfiguration: NSObject
/** This preference will balance the performance and preview quality by adjusting camera output frame size.
 */
@property (assign, nonatomic) WujiCameraCaptureOutputPreference preference;
#if defined (TARGET_OS_IOS) && TARGET_OS_IOS
/** The camera direction. See WujiCameraDirection:

 - WujiCameraDirectionRear: The rear camera.
 - WujiCameraDirectionFront: The front camera.
 */ 
@property (assign, nonatomic) WujiCameraDirection cameraDirection;
#endif
@end

#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))

/** WujiRtcDeviceInfo array.
 */
__attribute__((visibility("default"))) @interface WujiRtcDeviceInfo : NSObject
@property (assign, nonatomic) int __deprecated index;

/** Device type: WujiMediaDeviceType.
 */
@property (assign, nonatomic) WujiMediaDeviceType type;

/** Device ID.
 */
@property (copy, nonatomic) NSString * _Nullable deviceId;

/** Device name.
 */
@property (copy, nonatomic) NSString * _Nullable deviceName;
@end
#endif

/** Video frame containing the Wuji SDK's encoded video data.
 */
__attribute__((visibility("default"))) @interface WujiVideoFrame : NSObject
/** Video format:

 * 1: I420
 * 2: BGRA
 * 3: NV21
 * 4: RGBA
 * 5: IMC2
 * 7: ARGB
 * 8: NV12
 * 12: iOS texture (CVPixelBufferRef)
 * 16: I422
 */
@property (assign, nonatomic) NSInteger format;

/** Timestamp of the incoming video frame (ms).

An incorrect timestamp results in frame loss or unsynchronized audio and video.

 */
@property (assign, nonatomic) CMTime time; // Time for this frame.

@property (assign, nonatomic) int stride DEPRECATED_MSG_ATTRIBUTE("use strideInPixels instead");

/** Line spacing of the incoming video frame, which must be in pixels instead of bytes. For textures, it is the width of the texture.
 */
@property (assign, nonatomic) int strideInPixels; // Number of pixels between two consecutive rows. Note: in pixel, not byte. Not used for iOS textures.

/** Height of the incoming video frame
 */
@property (assign, nonatomic) int height; // Number of rows of pixels. Not used for iOS textures.

/** CVPixelBuffer
 */
@property (assign, nonatomic) CVPixelBufferRef _Nullable textureBuf;

/** Raw data buffer
 */
@property (strong, nonatomic) NSData * _Nullable dataBuf;  // Raw data buffer. Not used for iOS textures.

/** (Optional) The number of pixels trimmed from the left. The default value is 0.
 */
@property (assign, nonatomic) int cropLeft;   // Number of pixels to crop on the left boundary.
/** (Optional) The number of pixels trimmed from the top. The default value is 0.
 */
@property (assign, nonatomic) int cropTop;    // Number of pixels to crop on the top boundary.
/** (Optional) The number of pixels trimmed from the right. The default value is 0.
 */
@property (assign, nonatomic) int cropRight;  // Number of pixels to crop on the right boundary.
/** (Optional) The number of pixels trimmed from the bottom. The default value is 0.
 */
@property (assign, nonatomic) int cropBottom; // Number of pixels to crop on the bottom boundary.
/** (Optional) The clockwise rotation of the incoming video frame.

Optional values: 0, 90, 180, or 270. The default value is 0.
 */
@property (assign, nonatomic) int rotation;   // 0, 90, 180, 270. See document for rotation calculation.
/* Note
 * 1. strideInPixels
 *    Stride is in pixels, not bytes.
 * 2. About the frame width and height.
 *    No field is defined for the width. However, it can be deduced by:
 *       croppedWidth = (strideInPixels - cropLeft - cropRight)
 *    And
 *       croppedHeight = (height - cropTop - cropBottom)
 * 3. About crop.
 *    _________________________________________________________________.....
 *    |                        ^                                      |  ^
 *    |                        |                                      |  |
 *    |                     cropTop                                   |  |
 *    |                        |                                      |  |
 *    |                        v                                      |  |
 *    |                ________________________________               |  |
 *    |                |                              |               |  |
 *    |                |                              |               |  |
 *    |<-- cropLeft -->|          valid region        |<- cropRight ->|
 *    |                |                              |               | height
 *    |                |                              |               |
 *    |                |_____________________________ |               |  |
 *    |                        ^                                      |  |
 *    |                        |                                      |  |
 *    |                     cropBottom                                |  |
 *    |                        |                                      |  |
 *    |                        v                                      |  v
 *    _________________________________________________________________......
 *    |                                                               |
 *    |<---------------- strideInPixels ----------------------------->|
 *
 *    If your buffer contains garbage data, you can crop them. For example, if the frame size is
 *    360 * 640, often the buffer stride is 368, that is, the extra 8 pixels on the
 *    right are for padding, and should be removed. In this case, you can set:
 *    strideInPixels = 368;
 *    height = 640;
 *    cropRight = 8;
 *    // cropLeft, cropTop, cropBottom are set to a default of 0
 */
@end

/** The definition of WujiChannelMediaRelayInfo.
 */
__attribute__((visibility("default"))) @interface WujiChannelMediaRelayInfo: NSObject
/** The token that enables the user to join the channel.
 */
@property (copy, nonatomic) NSString * _Nullable token;
/** The channel name.
 */
@property (copy, nonatomic) NSString * _Nullable channelName;
/** The user ID.
 */
@property (assign, nonatomic) NSUInteger uid;
/** Initializes the WujiChannelMediaRelayInfo object
 
 @param token The token that enables the user to join the channel.
 */ 
- (instancetype _Nonnull)initWithToken:(NSString *_Nullable)token;
@end

/** The definition of WujiChannelMediaRelayConfiguration.

 */
__attribute__((visibility("default"))) @interface WujiChannelMediaRelayConfiguration: NSObject
/** The information of the destination channel: WujiChannelMediaRelayInfo. It contains the following members:

 - `channelName`: The name of the destination channel.
 - `uid`: ID of the broadcaster in the destination channel. The value ranges from 0 to (2<sup>32</sup>-1). To avoid UID conflicts, this `uid` must be different from any other UIDs in the destination channel. The default value is 0, which means the SDK generates a random UID.
 - `token`: The token for joining the destination channel. It is generated with the `channelName` and `uid` you set in `destinationInfos`.

   - If you have not enabled the App Certificate, set this parameter as the default value `nil`, which means the SDK applies the App ID.
   - If you have enabled the App Certificate, you must use the `token` generated with the `channelName` and `uid`.
 */
@property (strong, nonatomic, readonly) NSDictionary<NSString *, WujiChannelMediaRelayInfo *> *_Nullable destinationInfos;
/** The information of the source channel: WujiChannelMediaRelayInfo. It contains the following members:

 - `channelName`: The name of the source channel. The default value is `nil`, which means the SDK applies the name of the current channel.
 - `uid`: ID of the broadcaster whose media stream you want to relay. The default value is 0, which means the SDK generates a random UID. You must set it as 0.
 - `token`: The token for joining the source channel. It is generated with the `channelName` and `uid` you set in `sourceInfo`.

   - If you have not enabled the App Certificate, set this parameter as the default value `nil`, which means the SDK applies the App ID.
   - If you have enabled the App Certificate, you must use the `token` generated with the `channelName` and `uid`, and the `uid` must be set as 0.
 */
@property (strong, nonatomic) WujiChannelMediaRelayInfo *_Nonnull sourceInfo;
/** Sets the information of the destination channel.

 If you want to relay the media stream to multiple channels, call this method as many times (at most four).

 @param destinationInfo The information of the destination channel: WujiChannelMediaRelayInfo. It contains the following members:

 - `channelName`: The name of the destination channel.
 - `uid`: ID of the broadcaster in the destination channel. The value ranges from 0 to (2<sup>32</sup>-1). To avoid UID conflicts, this `uid` must be different from any other UIDs in the destination channel. The default value is 0, which means the SDK generates a random UID.
 - `token`: The token for joining the destination channel. It is generated with the `channelName` and `uid` you set in `destinationInfo`.

   - If you have not enabled the App Certificate, set this parameter as the default value `nil`, which means the SDK applies the App ID.
   - If you have enabled the App Certificate, you must use the `token` generated with the `channelName` and `uid`.

 @param channelName The name of the destination channel. Ensure that the value of this parameter is the same as that of the `channelName` member in `destinationInfo`.

 @return - YES: Success.
 - NO: Failure.
 */
- (BOOL)setDestinationInfo:(WujiChannelMediaRelayInfo *_Nonnull)destinationInfo forChannelName:(NSString *_Nonnull)channelName;
/** Removes the destination channel.

 @param channelName The name of the destination channel.

 @return - YES: Success.
 - NO: Failure.
 */
- (BOOL)removeDestinationInfoForChannelName:(NSString *_Nonnull)channelName;
@end


/** The image enhancement options in [setBeautyEffectOptions]([WujiRtcEngineKit setBeautyEffectOptions:options:]). */
__attribute__((visibility("default"))) @interface WujiBeautyOptions : NSObject

/** The lightening contrast level

[WujiLighteningContrastLevel](WujiLighteningContrastLevel), used with the lighteningLevel property:

- 0: Low contrast level.
- 1: (Default) Normal contrast level.
- 2: High contrast level.
*/
@property (nonatomic, assign) WujiLighteningContrastLevel lighteningContrastLevel;

/** The brightness level.

The default value is 0.7. The value ranges from 0.0 (original) to 1.0.
 */
@property (nonatomic, assign) float lighteningLevel;

/** The sharpness level.

The default value is 0.5. The value ranges from 0.0 (original) to 1.0. This parameter is usually used to remove blemishes.
 */
@property (nonatomic, assign) float smoothnessLevel;

/** The redness level.

The default value is 0.1. The value ranges from 0.0 (original) to 1.0. This parameter adjusts the red saturation level.
*/
@property (nonatomic, assign) float rednessLevel;

@end

/** The user information, including the user ID and user account. */
__attribute__((visibility("default"))) @interface WujiUserInfo : NSObject
/** The user ID of a user.
 */
@property (nonatomic, assign) NSUInteger uid;
/** The user account of a user.
 */
@property (copy, nonatomic) NSString * _Nullable userAccount;
@end

/** The channel media options.
 */ 
__attribute__((visibility("default"))) @interface WujiRtcChannelMediaOptions : NSObject
/** Determines whether to subscribe to audio streams when the user joins the channel:

 - true: (Default) Subscribe.
 - false: Do not subscribe.
 
 This member serves a similar function to the [muteAllRemoteAudioStreams]([WujiRtcChannel muteAllRemoteAudioStreams:]) method. After joining the channel, you can call the `muteAllRemoteAudioStreams` method to set whether to subscribe to audio streams in the channel.
 */ 
@property (nonatomic, assign) BOOL autoSubscribeAudio;
/** Determines whether to subscribe to video streams when the user joins the channel:

 - true: (Default) Subscribe.
 - false: Do not subscribe.

 This member serves a similar function to the [muteAllRemoteVideoStreams]([WujiRtcChannel muteAllRemoteVideoStreams:]) method. After joining the channel, you can call the `muteAllRemoteVideoStreams` method to set whether to subscribe to audio streams in the channel.
 */ 
@property (nonatomic, assign) BOOL autoSubscribeVideo;
@end

/** WujiFacePositionInfo array.
 */
__attribute__((visibility("default"))) @interface WujiFacePositionInfo : NSObject

/** The x coordinate (px) of the human face in the local video. Taking the top left corner of the captured video as the origin, the x coordinate represents the relative lateral displacement of the top left corner of the human face to the origin.
 */
@property (assign, nonatomic) NSInteger x;

/** The y coordinate (px) of the human face in the local video. Taking the top left corner of the captured video as the origin, the y coordinate represents the relative longitudinal displacement of the top left corner of the human face to the origin.
 */
@property (assign, nonatomic) NSInteger y;

/** The width (px) of the human face in the captured video.
 */
@property (assign, nonatomic) NSInteger width;

/** The height (px) of the human face in the captured video.
 */
@property (assign, nonatomic) NSInteger height;

/** The distance (cm) between the human face and the screen.
 */
@property (assign, nonatomic) NSInteger distance;
@end

//__attribute__((visibility("default"))) @interface WujiRtcChannelInfo : NSObject
//
//@property (nonatomic, copy) NSString * _Nonnull channelId;
//
//@end
/** Configurations for the WujiRtcEngineKit instance.
 */ 
__attribute__((visibility("default"))) @interface WujiRtcEngineConfig: NSObject
 /** The App ID issued to you by Wuji. See [How to get the App ID](https://docs.wuji.io/en/Wuji%20Platform/token#get-an-app-id). Only users in apps with the same App ID can join the same channel and communicate with each other. Use an App ID to create only one WujiRtcEngineKit instance. To change your App ID, call [destroy]([WujiRtcEngineKit destroy]) to destroy the current WujiRtcEngineKit instance and then call create to create an WujiRtcEngineKit instance with the new App ID.
  */ 
 @property (copy, nonatomic) NSString * _Nullable appId;
 /** The area for connection. This advanced feature applies to scenarios that have regional restrictions. <p>You can use the bitwise OR operator (`|`) to specify multiple areas. For details, see WujiIpAreaCode.<p>After specifying the area of connection:<li>When the app that integrates the Wuji SDK is used within the specified area, it connects to the Wuji servers within the specified area under normal circumstances.<li>When the app that integrates the Wuji SDK is used out of the specified area, it connects to the Wuji servers either in the specified area or in the area where the app is located.</li></p>
  */ 
 @property (nonatomic, assign) int areaCode;
 @end
