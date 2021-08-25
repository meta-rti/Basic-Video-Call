//
//  WujiMediaIO.h
//  WujiRtcEngineKit
//
//  Copyright (c) 2018 Wuji. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "WujiEnumerates.h"
#import "WujiObjects.h"


/** Video pixel format.

 This enumeration defines the pixel format of the video frame. Wuji supports three pixel formats on iOS: I420, BGRA, and NV12. For information on the YVU format, see:

   * [FourCC YUV Pixel Formats](http://www.fourcc.org/yuv.php)
   * [Recommended 8-Bit YUV Formats for Video Rendering](https://docs.microsoft.com/zh-cn/windows/desktop/medfound/recommended-8-bit-yuv-formats-for-video-rendering)
 */
typedef NS_ENUM(NSUInteger, WujiVideoPixelFormat) {
    /** I420 */
    WujiVideoPixelFormatI420   = 1,
    /** BGRA */
    WujiVideoPixelFormatBGRA   = 2,
    /** NV12 */
    WujiVideoPixelFormatNV12   = 8,
};

/** Video rotation.

 This enumeration defines the rotating angle of the video. Wuji supports rotating clockwise by 0, 90, 180, and 270 degrees.
 */
typedef NS_ENUM(NSInteger, WujiVideoRotation) {
    /** No rotation */
    WujiVideoRotationNone      = 0,
    /** 90 degrees */
    WujiVideoRotation90        = 1,
    /** 180 degrees */
    WujiVideoRotation180       = 2,
    /** 270 degrees */
    WujiVideoRotation270       = 3,
};

/** Video buffer type */
typedef NS_ENUM(NSInteger, WujiVideoBufferType) {
   /** Use a pixel buffer to transmit the video data. */
    WujiVideoBufferTypePixelBuffer = 1,
    /** Use raw data to transmit the video data. */
    WujiVideoBufferTypeRawData     = 2,
};

/** An object supporting video data in two formats; pixel buffer and raw data.

 When the video source is initialized, the media engine passes this object to you and you need to reserve it, and then pass the video frame to the media engine through this object once the video source is initialized.
 Call [bufferType]([WujiVideoSinkProtocol bufferType]) to specify a buffer type. The video data can only be transmitted in the corresponding type.
 */
@protocol WujiVideoFrameConsumer <NSObject>

/** Uses the video information in the pixel buffer.

 @param pixelBuffer Buffer type
 @param timestamp   Timestamp (ms) of the video frame. For each video frame, you need to set a timestamp.
 @param rotation    WujiVideoRotation
 */
- (void)consumePixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
             withTimestamp:(CMTime)timestamp
                  rotation:(WujiVideoRotation)rotation;

/** Uses the video information in the raw data.

 @param rawData   Raw data of the video frame.
 @param timestamp Timestamp (ms) of the video frame.
 @param format    WujiVideoPixelFormat
 @param size      Size of the raw video data.
 @param rotation  WujiVideoRotation
 */
- (void)consumeRawData:(void * _Nonnull)rawData
         withTimestamp:(CMTime)timestamp
                format:(WujiVideoPixelFormat)format
                  size:(CGSize)size
              rotation:(WujiVideoRotation)rotation;
@end

/** Defines a set of protocols to implement the custom video source and pass it to the underlying media engine to replace the default video source.

 `WujiVideoSourceProtocol` allows you to take the ownership of the video source and manipulate it.
 By default, when enabling real-time communications, the Wuji SDK enables the default video input device (built-in camera) to start video streaming.
 By calling [setVideoSource]([WujiRtcEngineKit setVideoSource:]), you can change the default video input device, control it, and send the video source from the specified input device to the Wuji Media Engine to handle the remaining video processes; such as video filtering and publishing the video to the RTC connection.
 Once you have implemented this interface, the Wuji Media Engine automatically releases the ownership of the current video input device and passes the ownership to you, so that you can use the same video input device to capture the video stream.
 `WujiVideoSourceProtocol` consists of the following methods:

 * Initializes the Video Source ([shouldInitialize](shouldInitialize))
 * Enables the Video Source ([shouldStart](shouldStart))
 * Disables the Video Source ([shouldStop](shouldStop))
 * Releases the Video Source ([shouldDispose](shouldDispose))
 * Retrieves the Buffer Type ([bufferType](bufferType))

 Note:

 * All methods in `WujiVideoSourceProtocol` are callbacks. The media engine maintains a finite state machine and uses these methods at the right time. Do not use these methods directly in the app.
 * These methods are synchronized.
 * If the media engine restarts during the process, these methods can be repeated for a couple of times.
 * These methods are not in the primary thread.

 When using the `WujiVideoSourceProtocol`, call WujiVideoBufferType, WujiVideoPixelFormat, and WujiVideoRotation to set the buffer type, pixel format, and rotation angle of the transmitted video.
 */
@protocol WujiVideoSourceProtocol <NSObject>
@required
/** See WujiVideoFrameConsumer */
@property (strong) id<WujiVideoFrameConsumer> _Nullable consumer;
/** Initializes the video source.

 The media engine calls this method to initialize the video source. You can also initialize the video source before this method is called and return YES to the media engine in this method. You need to pass YES or NO in this method to tell the media engine if the video source is initialized.
 When the video source is initialized, the media engine initializes the WujiVideoFrameConsumer pointer in WujiVideoSourceProtocol, then the video source sends the video frame to the media engine through the WujiVideoFrameConsumer method.

 @return * YES: If the external video source is initialized.
 * NO: If the external video source is not ready or fails to initialize, the media engine stops and reports the error.
 */
- (BOOL)shouldInitialize;

/** Enables the video source.

 Call this method when the media engine is ready to start video streaming. You should start the video source to capture the video frame. Once the frame is ready, use WujiVideoFrameConsumer to consume the video frame.
 Pass one of the following return values to the media engine:

 * YES: If the external video source is enabled and WujiVideoFrameConsumer is called to receive video frames.
 * NO: If the external video source is not ready or fails to enable, the media engine stops and reports the error.

 After YES is returned, video frames can be passed to the media engine through the preset WujiVideoFrameConsumer interface method.
 */
- (void)shouldStart;

/** Disables the video source.

 Call this method when the media engine stops streaming. You should then stop capturing the video frame and consuming it. After this method is called, the video frames are discarded by the media engine.
 */
- (void)shouldStop;

/** Releases the video source.

Call this method when WujiVideoFrameConsumer is released by the media engine. You can now release the video source as well as WujiVideoFrameConsumer.
 */
- (void)shouldDispose;

/** Retrieves the buffer type.

 Passes the buffer type previously set in `WujiVideoBufferType` to the media engine. This buffer type is used to set up the correct media engine environment.

 @return return WujiVideoBufferType
 */
- (WujiVideoBufferType)bufferType;
@end

/** Defines a set of protocols to implement the custom video sink and pass it to the underlying media engine to replace the default video sink.

 WujiVideoSinkProtocol allows you to implement the custom video source.
 By default, when you try to enable real-time communications, the Wuji SDK enables the default video sink to start video rendering. By calling [setLocalVideoRenderer]([WujiRtcEngineKit setLocalVideoRenderer:]) and [setRemoteVideoRenderer]([WujiRtcEngineKit setRemoteVideoRenderer:forUserId:]), you can change the default video sink.
 Once you implement this interface, you receive callbacks from the media engine to indicate the state of the custom video sink, the underlying media engine, and enable their synchronization. Follow each callback to handle the resource allocation, and to release and receive the video frame from the media engine.
 WujiVideoSinkProtocol defines a set of protocols to create a customized video sink. The WujiVideoFrameConsumer interface passes the video frames to the media engine, which then passes them to the renderer.
 After a customized video sink is created, the app passes it to the media engine, see [setLocalVideoRenderer]([WujiRtcEngineKit setLocalVideoRenderer:]) and [setRemoteVideoRenderer]([WujiRtcEngineKit setRemoteVideoRenderer:forUserId:]).
 WujiVideoSinkProtocol consists of the following methods:

 * Initializes the Video Sink ([shouldInitialize](shouldInitialize))
 * Enables the Video Sink ([shouldStart](shouldStart))
 * Disables the Video Sink ([shouldStop](shouldStop))
 * Releases the Video Sink ([shouldDispose](shouldDispose))
 * Retrieves the Buffer Type ([bufferType](bufferType))
 * Retrieves the Pixel Format ([pixelFormat](pixelFormat))
 * (Optional) Outputs the Video in the Pixel Buffer ([renderPixelBuffer](renderPixelBuffer:rotation:))
 * (Optional) Outputs the Video in the Raw Data ([renderRawData](renderRawData:size:rotation:))

 Note: All methods defined in WujiVideoSinkProtocol are callbacks. The media engine uses these methods to inform the customized renderer of its internal changes.
 An example is shown in the following steps to customize the video sink:

 1. Call bufferType and WujiVideoPixelFormat to set the buffer type and pixel format of the video frame.
 2. Implement [shouldInitialize](shouldInitialize), [shouldStart](shouldStart), [shouldStop](shouldStop), and [shouldDispose](shouldDispose) to manage the customized video sink.
 3. Implement the buffer type and pixel format as specified in WujiVideoFrameConsumer.
 4. Create the customized video sink object.
 5. Call the [setLocalVideoRenderer]([WujiRtcEngineKit setLocalVideoRenderer:]) and [setRemoteVideoRenderer]([WujiRtcEngineKit setRemoteVideoRenderer:forUserId:]) methods to set the local and remote renderers.
 6. The media engine calls functions in WujiVideoSinkProtocol according to its internal state.
 */
@protocol WujiVideoSinkProtocol <NSObject>
@required
/** Initializes the video  sink.

 You can also initialize the video sink before this method is called and return YES in this method.

 @return * YES: If the video sink is initialized.
 * NO: If the video sink is not ready or fails to initialize, the media engine stops and reports the error.
 */
- (BOOL)shouldInitialize;

/** Enables the video sink.

 Call this method when the media engine starts streaming.

 * YES: If the video sink is ready. The media engine provides the video frame to the custom video sink by calling the WujiVideoFrameConsumer interface.
 * NO: If the video sink is not ready.
 */
- (void)shouldStart;

/** Disables the video sink.

 Call this method when the media engine stops video streaming. You should then stop the video sink.
 */
- (void)shouldStop;

/** Releases the video sink.

 Call this method when the media engine wants to release the video sink resources.
 */
- (void)shouldDispose;

/** Retrieves the buffer type and passes the buffer type specified in `WujiVideoBufferType` to the media engine.

 @return bufferType WujiVideoBufferType
 */
- (WujiVideoBufferType)bufferType;

/** Retrieves the pixel format and passes it to the media engine.

 @return pixelFormat WujiVideoPixelFormat
 */
- (WujiVideoPixelFormat)pixelFormat;

@optional
/** (Optional) Outputs the video in the pixel buffer.

 @param pixelBuffer Video in the pixel buffer.
 @param rotation    Clockwise rotating angle of the video frame. See WujiVideoRotation.
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(WujiVideoRotation)rotation;

/** (Optional) Outputs the video in the raw data.

 @param rawData  Raw video data.
 @param size     Size of the raw video.
 @param rotation Clockwise rotating angle of the video frame. See WujiVideoRotation.
 */
- (void)renderRawData:(void * _Nonnull)rawData
                 size:(CGSize)size
             rotation:(WujiVideoRotation)rotation;
@end


#pragma mark - Wuji Default Media IO
/** Default camera position */
typedef NS_ENUM(NSInteger, WujiRtcDefaultCameraPosition) {
    /** Front camera */
    WujiRtcDefaultCameraPositionFront = 0,
    /** Rear camera */
    WujiRtcDefaultCameraPositionBack = 1,
};

__attribute__((visibility("default"))) @interface WujiRtcDefaultCamera: NSObject<WujiVideoSourceProtocol>
#if defined (TARGET_OS_IPHONE) && TARGET_OS_IPHONE
@property (nonatomic, assign) WujiRtcDefaultCameraPosition position;
- (instancetype _Nonnull)initWithPosition:(WujiRtcDefaultCameraPosition)position;
#endif
@end

#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))
__attribute__((visibility("default"))) @interface WujiRtcScreenCapture: NSObject<WujiVideoSourceProtocol>
@property (nonatomic, assign, readonly) BOOL ifWindowShare;
@property (nonatomic, assign, readonly) NSUInteger displayId;
@property (nonatomic, assign, readonly) NSUInteger windowId;
@property (nonatomic, assign, readonly) CGRect rect;
@property (nonatomic, assign, readonly) CGSize dimensions;
@property (nonatomic, assign, readonly) NSInteger frameRate;
@property (nonatomic, assign, readonly) NSInteger bitrate;
@property (nonatomic, assign, readonly) BOOL captureMouseCursor;

+ (instancetype _Nonnull)screenCaptureWithId:(NSUInteger)displayId
                                        rect:(CGRect)rect
                                  dimensions:(CGSize)dimensions
                                   frameRate:(NSInteger)frameRate
                                     bitrate:(NSInteger)bitrate
                          captureMouseCursor:(BOOL)captureMouseCursor;
+ (instancetype _Nonnull)windowCaptureWithId:(NSUInteger)windowId
                                        rect:(CGRect)rect
                                  dimensions:(CGSize)dimensions
                                   frameRate:(NSInteger)frameRate
                                     bitrate:(NSInteger)bitrate
                          captureMouseCursor:(BOOL)captureMouseCursor;
@end
#endif

__attribute__((visibility("default"))) @interface WujiRtcDefaultRenderer: NSObject<WujiVideoSinkProtocol>
@property (nonatomic, strong, readonly) VIEW_CLASS * _Nonnull view;
@property (nonatomic, assign) WujiVideoRenderMode mode;
- (instancetype _Nonnull)initWithView:(VIEW_CLASS * _Nonnull)view
                           renderMode:(WujiVideoRenderMode)mode;
@end
