//
//  WujiConstants.h
//  WujiRtcEngineKit
//
//  Copyright (c) 2018 Wuji. All rights reserved.
//
#import <Foundation/Foundation.h>
#if defined (TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#elif defined (TARGET_OS_MAC) && TARGET_OS_MAC
#import <AppKit/AppKit.h>
#endif

/** The standard bitrate set in [setVideoEncoderConfiguration]([WujiRtcEngineKit setVideoEncoderConfiguration:]).

(Recommended) The standard bitrate mode. In this mode, the bitrate under the live broadcast and communication profiles differs:

    - Communication profile: The video bitrate is the same as the base bitrate.
    - Live broadcast profile: The video bitrate is twice the base bitrate.
 */
__attribute__ ((visibility("default"))) extern NSInteger const WujiVideoBitrateStandard;

/** The compatible bitrate set in [setVideoEncoderConfiguration]([WujiRtcEngineKit setVideoEncoderConfiguration:]).

The compatible bitrate mode. In this mode, the bitrate stays the same regardless of the channel profile. In a live broadcast channel, if you choose this mode, the video frame rate may be lower than the set value.
 */
__attribute__ ((visibility("default")))  extern NSInteger const WujiVideoBitrateCompatible;

/** Use the default minimum bitrate.
 */
__attribute__ ((visibility("default"))) extern NSInteger const WujiVideoBitrateDefaultMin;

/** 120 * 120
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension120x120;
/** 160 * 120
 */
__attribute__ ((visibility("default")))  extern CGSize const WujiVideoDimension160x120;
/** 180 * 180
 */
__attribute__ ((visibility("default")))  extern CGSize const WujiVideoDimension180x180;
/** 240 * 180
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension240x180;
/** 320 * 180
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension320x180;
/** 240 * 240
 */
__attribute__ ((visibility("default")))  extern CGSize const WujiVideoDimension240x240;
/** 320 * 240
 */
__attribute__ ((visibility("default")))  extern CGSize const WujiVideoDimension320x240;
/** 424 * 240
 */
__attribute__ ((visibility("default")))  extern CGSize const WujiVideoDimension424x240;
/** 360 * 360
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension360x360;
/** 480 * 360
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension480x360;
/** 640 * 360
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension640x360;
/** 480 * 480
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension480x480;
/** 640 * 480
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension640x480;
/** 840 * 480
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension840x480;
/** 960 * 720 (Hardware dependent)
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension960x720;
/** 1280 * 720 (Hardware dependent)
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension1280x720;
//#if TARGET_OS_MAC && !TARGET_OS_IPHONE
/** 1920 * 1080 (Hardware dependent, macOS only)
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension1920x1080;
/** 25400 * 1440 (Hardware dependent, macOS only)
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension2540x1440;
/** 3840 * 2160 (Hardware dependent, macOS only)
 */
__attribute__ ((visibility("default"))) extern CGSize const WujiVideoDimension3840x2160;
//#endif
