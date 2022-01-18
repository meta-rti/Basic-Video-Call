//
//  MetaConstants.h
//  MetaRtcEngineKit
//
//  Copyright (c) 2018 Meta. All rights reserved.
//
#import <Foundation/Foundation.h>
#if defined (TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#elif defined (TARGET_OS_MAC) && TARGET_OS_MAC
#import <AppKit/AppKit.h>
#endif

/** The standard bitrate set in [setVideoEncoderConfiguration]([MetaRtcEngineKit setVideoEncoderConfiguration:]).

(Recommended) The standard bitrate mode. In this mode, the bitrate under the live broadcast and communication profiles differs:

    - Communication profile: The video bitrate is the same as the base bitrate.
    - Live broadcast profile: The video bitrate is twice the base bitrate.
 */
__attribute__ ((visibility("default"))) extern NSInteger const MetaVideoBitrateStandard;

/** The compatible bitrate set in [setVideoEncoderConfiguration]([MetaRtcEngineKit setVideoEncoderConfiguration:]).

The compatible bitrate mode. In this mode, the bitrate stays the same regardless of the channel profile. In a live broadcast channel, if you choose this mode, the video frame rate may be lower than the set value.
 */
__attribute__ ((visibility("default")))  extern NSInteger const MetaVideoBitrateCompatible;

/** Use the default minimum bitrate.
 */
__attribute__ ((visibility("default"))) extern NSInteger const MetaVideoBitrateDefaultMin;

/** 120 * 120
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension120x120;
/** 160 * 120
 */
__attribute__ ((visibility("default")))  extern CGSize const MetaVideoDimension160x120;
/** 180 * 180
 */
__attribute__ ((visibility("default")))  extern CGSize const MetaVideoDimension180x180;
/** 240 * 180
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension240x180;
/** 320 * 180
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension320x180;
/** 240 * 240
 */
__attribute__ ((visibility("default")))  extern CGSize const MetaVideoDimension240x240;
/** 320 * 240
 */
__attribute__ ((visibility("default")))  extern CGSize const MetaVideoDimension320x240;
/** 424 * 240
 */
__attribute__ ((visibility("default")))  extern CGSize const MetaVideoDimension424x240;
/** 360 * 360
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension360x360;
/** 480 * 360
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension480x360;
/** 640 * 360
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension640x360;
/** 480 * 480
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension480x480;
/** 640 * 480
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension640x480;
/** 840 * 480
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension840x480;
/** 960 * 720 (Hardware dependent)
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension960x720;
/** 1280 * 720 (Hardware dependent)
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension1280x720;
#if TARGET_OS_MAC && !TARGET_OS_IPHONE
/** 1920 * 1080 (Hardware dependent, macOS only)
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension1920x1080;
/** 25400 * 1440 (Hardware dependent, macOS only)
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension2540x1440;
/** 3840 * 2160 (Hardware dependent, macOS only)
 */
__attribute__ ((visibility("default"))) extern CGSize const MetaVideoDimension3840x2160;
#endif
