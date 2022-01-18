//
//  MetaLivePublisher.h
//  MetaLiveKit
//
//  Created by Sting Feng on 2015-8-11.
//  Copyright (c) 2015 Meta. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MetaObjects.h"

/** The base class for managing a live broadcast.  MetaLiveKit manages the channel and all actions apart from publishing and subscribing.
 */
@class MetaLiveKit;

/** A class for managing the actions related to live publishing.
 */
@class MetaLivePublisher;

/** Protocol providing the MetaLivePublisher class with callbacks.
 */
@protocol MetaLivePublisherDelegate <NSObject>
@optional

/**
 A stream was published.

 @param publisher MetaRtcEngineKit object.
 @param url Address to which the publisher publishes the stream.
 @param error MetaErrorCode
 */
-(void)publisher:(MetaLivePublisher *_Nonnull)publisher streamPublishedWithUrl:(NSString *_Nonnull)url error:(MetaErrorCode)error;

/**
 A stream was unpublished.

 @param publisher MetaRtcEngineKit object.
 @param url Address to which the publisher unpublishes the stream.
 */
-(void)publisher:(MetaLivePublisher *_Nonnull)publisher streamUnpublishedWithUrl:(NSString *_Nonnull)url;

/**
 The publisher transcoding was updated.

 @param publisher MetaRtcEngineKit object
 */
-(void)publisherTranscodingUpdated: (MetaLivePublisher *_Nonnull)publisher;

/**
 The state of the imported external video stream.

 @param publisher MetaRtcEngineKit object.
 @param url URL address of the imported external video stream added to the live broadcast.
 @param uid User ID.
 @param status State of the externally injected video stream: MetaInjectStreamStatus.
 */
-(void)publisher:(MetaLivePublisher *_Nonnull)publisher streamInjectedStatusOfUrl:(NSString *_Nonnull)url uid:(NSUInteger)uid status:(MetaInjectStreamStatus)status;
@end


/**
 The MetaLivePublisher class manages all actions related to live broadcast publishing.

 */
__attribute__((visibility("default"))) @interface MetaLivePublisher: NSObject

/**
 Sets the delegate.

 @param delegate MetaLivePublisherDelegate
 */
-(void)setDelegate:(_Nullable id<MetaLivePublisherDelegate>)delegate;

/**
 Initializes the publisher.

 @param kit MetaLiveKit
 @return MetaLivePublisher object
 */
-(instancetype _Nonnull)initWithLiveKit:(MetaLiveKit *_Nonnull)kit;

/**  Sets the video encoding profile manually.

 @param resolution Resolution of the video. The highest value is 1280 * 720.
 @param frameRate Frame rate of the video. The highest value is 30. You can set it to 5, 10, 15, 24, 30, and so on.
 @param bitrate Bitrate of the video. You need to manually work out the frame rate according to the width, height, and frame rate. With the same width and height, the bitrate varies with the change of the frame rate:

* If the frame rate is 5 fps, divide the recommended bitrate by 2.
* If the frame rate is 15 fps, use the recommended bitrate.
* If the frame rate is 30 fps, multiply the recommended bitrate by 1.5.
* Calculate your bitrate with the ratio if you choose other frame rates.

 If you set a bitrate beyond the proper range, the SDK will automatically adjust it to a value within the range.
 */
- (void)setVideoResolution:(CGSize)resolution andFrameRate:(NSInteger)frameRate bitrate:(NSInteger)bitrate;

/**
Sets live transcoding.

 This method is used for CDN live. It sets the video layout and audio for CDN live.

 @param transcoding MetaLiveTranscoding object.
 */
-(void)setLiveTranscoding:(MetaLiveTranscoding *_Nullable)transcoding;


/**
 Adds a watermark to the local video stream.

 This method adds a watermark in the PNG file format onto the local video stream for the recording device and the audience in the channel and CDN live to see or capture it.
 To add the PNG file onto a CDN live publishing stream only, see [setLiveTranscoding](setLiveTranscoding:).


 @param watermark MetaImage
 @return Name of the watermark image.
 */
-(int)addVideoWatermark:(MetaImage * _Nonnull)watermark  NS_SWIFT_NAME(addVideoWatermark(_:));

/**
Removes the watermark from the video stream.
 */
-(void)clearVideoWatermarks;

/** Sets the media type.

 @param mediaType MetaMediaType
 */
-(void)setMediaType:(MetaMediaType)mediaType;

/** Adds a stream URL.

 This method is used for CDN live. It adds the URL to which the host publishes the stream.
 Note: This method only adds one URL each time it is called.

 @param url URL to which the host publishes the stream.
 @param transcodingEnabled * YES: Enable transcoding.
 * NO: Disable transcoding.

 */
-(void)addStreamUrl:(NSString *_Nullable)url transcodingEnabled:(BOOL)transcodingEnabled;

/** Removes a stream URL.

 This method is used for CDN live. It removes the URL to which the host publishes the stream.
 Note: This method only removes one URL each time it is called.

 @param url URL to which the host publishes the stream.
 */
-(void)removeStreamUrl:(NSString *_Nullable)url;

/** Publishes a stream.
 */
-(void)publish;

/** Stops stream publishing.
 */
-(void)unpublish;

#if defined (TARGET_OS_IPHONE) && TARGET_OS_IPHONE
/**
 Switches between front and rear cameras.
 */
-(void)switchCamera;
#endif

/**
Adds a URL address of the added stream into the live broadcast channel.

 @param url URL address to add to the ongoing live broadcast. Valid protocols are RTMP, HLS, and FLV live streaming protocols and the MP3/MP4 streams.
 @param config MetaLiveInjectStreamConfig
 */
- (void)addInjectStreamUrl:(NSString *_Nonnull)url config:(MetaLiveInjectStreamConfig * _Nonnull)config;

/**
 Removes the URL from the live broadcast.

 @param url URL address of the added stream to remove.
 */
- (void)removeInjectStreamUrl:(NSString *_Nonnull)url;

@end
