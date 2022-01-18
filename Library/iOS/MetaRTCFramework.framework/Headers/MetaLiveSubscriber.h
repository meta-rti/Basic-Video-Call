//
//  MetaLiveSubscriber.h
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

/** A class for managing actions related to live subscribing.
 */
@class MetaLiveSubscriber;

/** Protocol providing the MetaLiveSubscriber class with callbacks.
 */
@protocol MetaLiveSubscriberDelegate <NSObject>
@optional

// Subscriber

/**
 A stream was published by a specified host.

 @param subscriber MetaLiveSubscriber
 @param uid User ID of the host
 @param type Stream type: MetaMediaType
 */
- (void)subscriber: (MetaLiveSubscriber *_Nonnull)subscriber publishedByHostUid:(NSUInteger)uid streamType:(MetaMediaType) type;

/**
 The stream type was changed by a specified host.

 @param subscriber MetaLiveSubscriber
 @param type MetaMediaType
 @param uid User ID of the host
 */
- (void)subscriber: (MetaLiveSubscriber *_Nonnull)subscriber streamTypeChangedTo:(MetaMediaType) type byHostUid:(NSUInteger)uid;

// Unmute, offline

/**
 A stream was unpublished by a specified host.

 @param subscriber MetaLiveSubscriber
 @param uid User ID of the host
 */
- (void)subscriber: (MetaLiveSubscriber *_Nonnull)subscriber unpublishedByHostUid:(NSUInteger)uid;

// Video
/** The first frame of the specified remote user was displayed successfully.
 *
 *  @param subscriber     Live subscriber.
 *  @param uid     Remote user id.
 *  @param size    Size of video stream.
 *  @param elapsed Time elapsed (ms) from the beginning of the session.
 */
- (void)subscriber:(MetaLiveSubscriber *_Nonnull)subscriber firstRemoteVideoDecodedOfHostUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  The video size and rotational change of the specified user.
 *
 *  @param subscriber     Live subscriber
 *  @param uid     User ID
 *  @param size    New video size
 *  @param rotation  New video rotation
 */
- (void)subscriber:(MetaLiveSubscriber *_Nonnull)subscriber videoSizeChangedOfHostUid:(NSUInteger)uid size:(CGSize)size rotation:(NSInteger)rotation;
@end


/**
 The MetaLiveSubscriber class manages all actions related to live broadcast subscribing.

 */
__attribute__((visibility("default"))) @interface MetaLiveSubscriber: NSObject // MetaLiveSubscriber

/**
 Initializes an MetaLiveSubscriber object.

 @param kit MetaLiveKit
 @return MetaLiveSubscriber object.
 */
-(instancetype _Nonnull)initWithLiveKit:(MetaLiveKit * _Nonnull)kit;


/**
 Sets the delegate.

 @param delegate MetaLiveSubscriberDelegate
 */
-(void)setDelegate:(_Nullable id<MetaLiveSubscriberDelegate>)delegate;

/**
 Subscribes to a host.

 @param uid User ID of the host
 @param mediaType Media type: MetaMediaType
 @param view View to render
 @param mode Video display mode: MetaVideoRenderMode
 @param videoType MetaVideoStreamType
 */
- (void)subscribeToHostUid:(NSUInteger)uid
             mediaType:(MetaMediaType)mediaType
                  view:(VIEW_CLASS *_Nullable)view
            renderMode:(MetaVideoRenderMode)mode
             videoType:(MetaVideoStreamType)videoType;

/**
 Unsubscribes from a host.

 @param uid User ID of the host
 */
-(void)unsubscribeToHostUid:(NSUInteger)uid;

@end
