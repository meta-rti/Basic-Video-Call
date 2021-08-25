//
//  WujiLiveSubscriber.h
//  WujiLiveKit
//
//  Created by Sting Feng on 2015-8-11.
//  Copyright (c) 2015 Wuji. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WujiObjects.h"

/** The base class for managing a live broadcast.  WujiLiveKit manages the channel and all actions apart from publishing and subscribing.
 */
@class WujiLiveKit;

/** A class for managing actions related to live subscribing.
 */
@class WujiLiveSubscriber;

/** Protocol providing the WujiLiveSubscriber class with callbacks.
 */
@protocol WujiLiveSubscriberDelegate <NSObject>
@optional

// Subscriber

/**
 A stream was published by a specified host.

 @param subscriber WujiLiveSubscriber
 @param uid User ID of the host
 @param type Stream type: WujiMediaType
 */
- (void)subscriber: (WujiLiveSubscriber *_Nonnull)subscriber publishedByHostUid:(NSUInteger)uid streamType:(WujiMediaType) type;

/**
 The stream type was changed by a specified host.

 @param subscriber WujiLiveSubscriber
 @param type WujiMediaType
 @param uid User ID of the host
 */
- (void)subscriber: (WujiLiveSubscriber *_Nonnull)subscriber streamTypeChangedTo:(WujiMediaType) type byHostUid:(NSUInteger)uid;

// Unmute, offline

/**
 A stream was unpublished by a specified host.

 @param subscriber WujiLiveSubscriber
 @param uid User ID of the host
 */
- (void)subscriber: (WujiLiveSubscriber *_Nonnull)subscriber unpublishedByHostUid:(NSUInteger)uid;

// Video
/** The first frame of the specified remote user was displayed successfully.
 *
 *  @param subscriber     Live subscriber.
 *  @param uid     Remote user id.
 *  @param size    Size of video stream.
 *  @param elapsed Time elapsed (ms) from the beginning of the session.
 */
- (void)subscriber:(WujiLiveSubscriber *_Nonnull)subscriber firstRemoteVideoDecodedOfHostUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  The video size and rotational change of the specified user.
 *
 *  @param subscriber     Live subscriber
 *  @param uid     User ID
 *  @param size    New video size
 *  @param rotation  New video rotation
 */
- (void)subscriber:(WujiLiveSubscriber *_Nonnull)subscriber videoSizeChangedOfHostUid:(NSUInteger)uid size:(CGSize)size rotation:(NSInteger)rotation;
@end


/**
 The WujiLiveSubscriber class manages all actions related to live broadcast subscribing.

 */
__attribute__((visibility("default"))) @interface WujiLiveSubscriber: NSObject // WujiLiveSubscriber

/**
 Initializes an WujiLiveSubscriber object.

 @param kit WujiLiveKit
 @return WujiLiveSubscriber object.
 */
-(instancetype _Nonnull)initWithLiveKit:(WujiLiveKit * _Nonnull)kit;


/**
 Sets the delegate.

 @param delegate WujiLiveSubscriberDelegate
 */
-(void)setDelegate:(_Nullable id<WujiLiveSubscriberDelegate>)delegate;

/**
 Subscribes to a host.

 @param uid User ID of the host
 @param mediaType Media type: WujiMediaType
 @param view View to render
 @param mode Video display mode: WujiVideoRenderMode
 @param videoType WujiVideoStreamType
 */
- (void)subscribeToHostUid:(NSUInteger)uid
             mediaType:(WujiMediaType)mediaType
                  view:(VIEW_CLASS *_Nullable)view
            renderMode:(WujiVideoRenderMode)mode
             videoType:(WujiVideoStreamType)videoType;

/**
 Unsubscribes from a host.

 @param uid User ID of the host
 */
-(void)unsubscribeToHostUid:(NSUInteger)uid;

@end
