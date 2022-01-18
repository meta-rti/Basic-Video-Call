//
//  MetaRtmKit.h
//  MetaRtmKit
//
//  Copyright (c) 2020 Meta.io. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MetaRtmKit;
@class MetaRtmCallKit;

/**
<b>RETURNED TO THE CALLER.</b> States of an outgoing call invitation.
 */
typedef NS_ENUM(NSInteger, MetaRtmLocalInvitationState) {

  /**
0: <b>RETURNED TO THE CALLER.</b> The initial state of a call invitation (idle).
   */
  MetaRtmLocalInvitationStateIdle = 0,

  /**
1: FOR INTERNAL USE ONLY.
   */
  MetaRtmLocalInvitationStateSentToRemote = 1,

  /**
2: <b>RETURNED TO THE CALLER.</b> The call invitation is received by the callee.
   */
  MetaRtmLocalInvitationStateReceivedByRemote = 2,

  /**
3: <b>RETURNED TO THE CALLER.</b> The call invitation is accepted by the callee.
   */
  MetaRtmLocalInvitationStateAcceptedByRemote = 3,

  /**
4: <b>RETURNED TO THE CALLER.</b> The call invitation is declined by the callee.
   */
  MetaRtmLocalInvitationStateRefusedByRemote = 4,

  /**
5: <b>RETURNED TO THE CALLER.</b> You have canceled the call invitation.
   */
  MetaRtmLocalInvitationStateCanceled = 5,

  /**
6: <b>RETURNED TO THE CALLER.</b> The life cycle of the outgoing call invitation ends in failure.
   */
  MetaRtmLocalInvitationStateFailure = 6,
};

/**
<b>RETURNED TO THE CALLEE.</b> States of an incoming call invitation.
 */
typedef NS_ENUM(NSInteger, MetaRtmRemoteInvitationState) {

  /**
0: <b>RETURNED TO THE CALLEE.</b> The initial state of a call invitation (idle).
   */
  MetaRtmRemoteInvitationStateIdle = 0,

  /**
1: <b>RETURNED TO THE CALLEE.</b> A call invitation from a remote caller is received.
   */
  MetaRtmRemoteInvitationStateInvitationReceived = 1,

  /**
2: FOR INTERNAL USE ONLY.
   */
  MetaRtmRemoteInvitationStateAcceptSentToLocal = 2,

  /**
3: <b>RETURNED TO THE CALLEE.</b> You have declined the call invitation.
   */
  MetaRtmRemoteInvitationStateRefused = 3,

  /**
4: <b>RETURNED TO THE CALLEE.</b> You have accepted the call invitation.
   */
  MetaRtmRemoteInvitationStateAccepted = 4,

  /**
5: <b>RETURNED TO THE CALLEE.</b> The call invitation is canceled by the remote caller.
   */
  MetaRtmRemoteInvitationStateCanceled = 5,

  /**
6: <b>RETURNED TO THE CALLEE.</b> The life cycle of the incoming call invitation ends in failure.
   */
  MetaRtmRemoteInvitationStateFailure = 6,
};

/**
<b>RETURNED TO THE CALLER.</b> Error codes of an outgoing call invitation.
 */
typedef NS_ENUM(NSInteger, MetaRtmLocalInvitationErrorCode) {

  /**
0: <b>RETURNED TO THE CALLER.</b> The outgoing call invitation succeeds.
   */
  MetaRtmLocalInvitationErrorOk = 0,

  /**
1: <b>RETURNED TO THE CALLER.</b> The callee is offline. <p> The SDK: <ul><li>Keeps resending the
call invitation to the callee, if he or she is offline.</li><li>Returns this error code, if he or
she is still offline 30 seconds since the call invitation is sent.</li></ul>
   */
  MetaRtmLocalInvitationErrorRemoteOffline = 1,

  /**
2: <b>RETURNED TO THE CALLER.</b> The callee is online but has not ACKed to the call invitation 30
seconds since it is sent.
   */
  MetaRtmLocalInvitationErrorRemoteNoResponse = 2,

  /**
3: <b>RETURNED TO THE CALLER. SAVED FOR FUTURE USE.</b> The call invitation expires 60 seconds since
it is sent, if the callee ACKs to the call invitation but neither the caller or callee takes any
further action (cancel, accpet, or decline it).
   */
  MetaRtmLocalInvitationErrorExpire = 3,

  /**
4: <b>RETURNED TO THE CALLER.</b> The caller is not logged in.
   */
  MetaRtmLocalInvitationErrorNotLoggedIn = 4,
};

/**
<b>RETURNED TO THE CALLEE.</b> Error codes of an incoming call invitation.
 */
typedef NS_ENUM(NSInteger, MetaRtmRemoteInvitationErrorCode) {

  /**
0: <b>RETURNED TO THE CALLEE.</b> The incoming call invitation succeeds.
   */
  MetaRtmRemoteInvitationErrorOk = 0,

  /**
1: <b>RETURNED TO THE CALLEE.</b> The call invitation received by the callee fails: the callee is
not online.
   */
  MetaRtmRemoteInvitationErrorLocalOffline = 1,

  /**
2: <b>RETURNED TO THE CALLEE.</b> The call invitation received by callee fails: The callee does not
ACK within a set time after the callee accepts the call invitation. This is usually a result of a
network interruption.
   */
  MetaRtmRemoteInvitationErrorAcceptFailure = 2,

  /**
3: <b>RETURNED TO THE CALLEE.</b> The call invitation received by the callee fails: the call
invitation expires 60 seconds since it is sent, if the callee ACKs to the call invitation but
neither the caller or callee takes any further action (cancel, accpet, or decline it).
   */
  MetaRtmRemoteInvitationErrorExpire = 3,
};

/**
Error codes for the call invitation methods.
 */
typedef NS_ENUM(NSInteger, MetaRtmInvitationApiCallErrorCode) {

  /**
0: The method call succeeds.
   */
  MetaRtmInvitationApiCallErrorOk = 0,

  /**
1: The method call fails. Invalid argument, for example, the value of the content parameter exceeds
8K bytes.
   */
  MetaRtmInvitationApiCallErrorInvalidAugment = 1,

  /**
2: The method call fails. The call invitation has not started.
   */
  MetaRtmInvitationApiCallErrorNotStarted = 2,

  /**
3: The method call fails. The call invitation has ended.
   */
  MetaRtmInvitationApiCallErrorAlreadyEnd = 3,

  /**
4: The method call fails. The call invitation is already accepted.
   */
  MetaRtmInvitationApiCallErrorAlreadyAccept = 4,

  /**
5: The method call fails. The call invitation is already sent.
   */
  MetaRtmInvitationApiCallErrorAlreadySent = 5,
};

/**
 Returns the result of the [sendLocalInvitation]([MetaRtmCallKit sendLocalInvitation:completion:])
 method call. See MetaRtmInvitationApiCallErrorCode for the error codes.
 */
typedef void (^MetaRtmLocalInvitationSendBlock)(MetaRtmInvitationApiCallErrorCode errorCode);

/**
 Returns the result of the [acceptRemoteInvitation]([MetaRtmCallKit
 acceptRemoteInvitation:completion:]) method call. See MetaRtmInvitationApiCallErrorCode for the
 error codes.
 */
typedef void (^MetaRtmRemoteInvitationAcceptBlock)(MetaRtmInvitationApiCallErrorCode errorCode);

/**
 Returns the result of the [refuseRemoteInvitation]([MetaRtmCallKit
 refuseRemoteInvitation:completion:]) method call. See MetaRtmInvitationApiCallErrorCode for the
 error codes.
 */
typedef void (^MetaRtmRemoteInvitationRefuseBlock)(MetaRtmInvitationApiCallErrorCode errorCode);

/**
 Returns the result of the [cancelLocalInvitation]([MetaRtmCallKit
 cancelLocalInvitation:completion:]) method call. See MetaRtmInvitationApiCallErrorCode for the
 error codes.
 */
typedef void (^MetaRtmLocalInvitationCancelBlock)(MetaRtmInvitationApiCallErrorCode errorCode);

/**
 The caller's call invitation object.
 */
__attribute__((visibility("default"))) @interface MetaRtmLocalInvitation : NSObject

/**
 User ID of the callee.
 */
@property(nonatomic, copy, nonnull, readonly) NSString *calleeId;

/**
 The call invitation content set by the caller.
 */
@property(nonatomic, copy, nullable) NSString *content;

/**
 The callee's response to the incoming call invitation.
 */
@property(nonatomic, copy, nullable, readonly) NSString *response;

/**
 The channel ID.

 **NOTE**

 To intercommunicate with the legacy Meta Signaling SDK, you MUST set the channel ID. However, even
 if the callee successfully accepts the call invitation, the Meta RTM SDK does not join the channel
 of the specified channel ID.
 */
@property(nonatomic, copy, nullable) NSString *channelId;

/**
 The state of the outgoing call invitation. See MetaRtmLocalInvitationState.
 */
@property(nonatomic, assign, readonly) MetaRtmLocalInvitationState state;

/**
 Creates an MetaRtmLocalInvitation instance.

 @param calleeId uid of the callee.
 @return An MetaRtmLocalInvitation instance.
 */
- (instancetype _Nonnull)initWithCalleeId:(NSString *_Nonnull)calleeId;
@end

/** The callee's call invitation object. */
__attribute__((visibility("default"))) @interface MetaRtmRemoteInvitation : NSObject

/** User ID of the caller. */
@property(nonatomic, copy, nonnull, readonly) NSString *callerId;

/** The call invitation content set by the caller. */
@property(nonatomic, copy, nullable, readonly) NSString *content;

/** The callee's reponse to the call invitation. */
@property(nonatomic, copy, nullable) NSString *response;

/**The channel ID. */
@property(nonatomic, copy, nullable, readonly) NSString *channelId;

/** The state of the incoming call invitation. See MetaRtmRemoteInvitationState. */
@property(nonatomic, assign, readonly) MetaRtmRemoteInvitationState state;
@end

/**
 The MetaRtmCallDelegate protocol enables Meta RTM call callback event notifications to your app.
 */
@protocol MetaRtmCallDelegate <NSObject>
@optional

/**
 Callback to the caller: occurs when the callee receives the call invitation.

 @param callKit An RtmCallKit object.
 @param localInvitation An MetaRtmLocalInvitation object.
 */
- (void)rtmCallKit:(MetaRtmCallKit *_Nonnull)callKit
    localInvitationReceivedByPeer:(MetaRtmLocalInvitation *_Nonnull)localInvitation;

/**
 Callback to the caller: occurs when the callee accepts the call invitation.

 @param callKit An RtmCallKit object.
 @param localInvitation An MetaRtmLocalInvitation object.
 @param response The response set by the callee.
 */
- (void)rtmCallKit:(MetaRtmCallKit *_Nonnull)callKit
    localInvitationAccepted:(MetaRtmLocalInvitation *_Nonnull)localInvitation
               withResponse:(NSString *_Nullable)response;

/**
 Callback to the caller: occurs when the callee declines the call invitation.

 @param callKit An RtmCallKit object.
 @param localInvitation An MetaRtmLocalInvitation object.
 @param response The response set by the callee.
 */
- (void)rtmCallKit:(MetaRtmCallKit *_Nonnull)callKit
    localInvitationRefused:(MetaRtmLocalInvitation *_Nonnull)localInvitation
              withResponse:(NSString *_Nullable)response;

/**
 Callback to the caller: occurs when the caller cancels a call invitation.

 @param callKit An RtmCallKit object.
 @param localInvitation An MetaRtmLocalInvitation object.
 */
- (void)rtmCallKit:(MetaRtmCallKit *_Nonnull)callKit
    localInvitationCanceled:(MetaRtmLocalInvitation *_Nonnull)localInvitation;

/**
 Callback to the caller: occurs when the life cycle of the outgoing call invitation ends in failure.

 @param callKit An RtmCallKit object.
 @param localInvitation An MetaRtmLocalInvitation object.
 @param errorCode See MetaRtmLocalInvitationErrorCode for the error codes.
 */
- (void)rtmCallKit:(MetaRtmCallKit *_Nonnull)callKit
    localInvitationFailure:(MetaRtmLocalInvitation *_Nonnull)localInvitation
                 errorCode:(MetaRtmLocalInvitationErrorCode)errorCode;

/**
 Callback to the callee: occurs when the callee receives a call invitation.

 @param callKit An RtmCallKit object.
 @param remoteInvitation An MetaRtmRemoteInvitation object.
 */
- (void)rtmCallKit:(MetaRtmCallKit *_Nonnull)callKit
    remoteInvitationReceived:(MetaRtmRemoteInvitation *_Nonnull)remoteInvitation;

/**
 Callback to the callee: occurs when the callee declines a call invitation.

 @param callKit An RtmCallKit object.
 @param remoteInvitation An MetaRtmRemoteInvitation object.
 */
- (void)rtmCallKit:(MetaRtmCallKit *_Nonnull)callKit
    remoteInvitationRefused:(MetaRtmRemoteInvitation *_Nonnull)remoteInvitation;

/**
 Callback to the callee: occurs when the callee accepts a call invitation.

 @param callKit An RtmCallKit object.
 @param remoteInvitation An MetaRtmRemoteInvitation object.
 */
- (void)rtmCallKit:(MetaRtmCallKit *_Nonnull)callKit
    remoteInvitationAccepted:(MetaRtmRemoteInvitation *_Nonnull)remoteInvitation;

/**
 Callback to the callee: occurs when the caller cancels the call invitation.

 @param callKit An RtmCallKit object.
 @param remoteInvitation An MetaRtmRemoteInvitation object.
 */
- (void)rtmCallKit:(MetaRtmCallKit *_Nonnull)callKit
    remoteInvitationCanceled:(MetaRtmRemoteInvitation *_Nonnull)remoteInvitation;

/**
 Callback to the callee: occurs when the life cycle of the incoming call invitation ends in failure.

 @param callKit An RtmCallKit object.
 @param remoteInvitation An MetaRtmRemoteInvitation object.
 @param errorCode See MetaRtmRemoteInvitationErrorCode for the error codes.
 */
- (void)rtmCallKit:(MetaRtmCallKit *_Nonnull)callKit
    remoteInvitationFailure:(MetaRtmRemoteInvitation *_Nonnull)remoteInvitation
                  errorCode:(MetaRtmRemoteInvitationErrorCode)errorCode;
@end

__attribute__((visibility("default"))) @interface MetaRtmCallKit : NSObject
/** An MetaRtmKit instance. */
@property(atomic, readonly, weak, nullable) MetaRtmKit *rtmKit;
/** MetaRtmCallDelegate enables Meta RTM call callback event notifications to your app. */
@property(nonatomic, weak, nullable) id<MetaRtmCallDelegate> callDelegate;  // nonatomic

/**
 Allows the caller to send a call invitation to the callee.

 @param localInvitation An MetaRtmLocalInvitation object.
 @param completion An MetaRtmLocalInvitationSendBlock object, which indicates the result of sending
 a call invitation to a callee. See MetaRtmInvitationApiCallErrorCode for the error codes.

  - Success:
    - The caller receives the MetaRtmLocalInvitationSendBlock object with the
 `MetaRtmInvitationApiCallErrorOk` state and the
 [localInvitationReceivedByPeer]([MetaRtmCallDelegate rtmCallKit:localInvitationReceivedByPeer:])
 callback.
    - The callee receives the [remoteInvitationReceived]([MetaRtmCallDelegate
 rtmCallKit:remoteInvitationReceived:]) callback.
 - Failure: The caller receives the MetaRtmLocalInvitationSendBlock object with an error code. See
 MetaRtmInvitationApiCallErrorCode for the error codes.
 */
- (void)sendLocalInvitation:(MetaRtmLocalInvitation *_Nonnull)localInvitation
                 completion:(MetaRtmLocalInvitationSendBlock _Nullable)completion;

/**
 Allows the caller to cancel a call invitation.

 @param localInvitation An MetaRtmLocalInvitation object.
 @param completion An MetaRtmLocalInvitationCancelBlock object.

 - Success:
    - The caller receives the MetaRtmLocalInvitationCancelBlock object with the
 `MetaRtmInvitationApiCallErrorOk` state and the [localInvitationCanceled]([MetaRtmCallDelegate
 rtmCallKit:localInvitationCanceled:]) callback.
    - The callee receives the [remoteInvitationCanceled]([MetaRtmCallDelegate
 rtmCallKit:remoteInvitationCanceled:]) callback.
 - Failure: The caller receives the MetaRtmLocalInvitationCancelBlock object with an error code. See
 MetaRtmInvitationApiCallErrorCode for the error codes.

 */
- (void)cancelLocalInvitation:(MetaRtmLocalInvitation *_Nonnull)localInvitation
                   completion:(MetaRtmLocalInvitationCancelBlock _Nullable)completion;

/**
 Allows the callee to accept a call invitation.

 @param remoteInvitation An MetaRtmRemoteInvitation object.
 @param completion An MetaRtmRemoteInvitationAcceptBlock object.

 - Success:
    - The caller receives the MetaRtmRemoteInvitationAcceptBlock object with the
 `MetaRtmInvitationApiCallErrorOk` state and the [localInvitationAccepted]([MetaRtmCallDelegate
 rtmCallKit:localInvitationAccepted:withResponse:]) callback.
    - The callee receives the [remoteInvitationAccepted]([MetaRtmCallDelegate
 rtmCallKit:remoteInvitationAccepted:]) callback.
 - Failure: The caller receives the MetaRtmRemoteInvitationAcceptBlock object with an error code.
 See MetaRtmInvitationApiCallErrorCode for the error codes.

 */
- (void)acceptRemoteInvitation:(MetaRtmRemoteInvitation *_Nonnull)remoteInvitation
                    completion:(MetaRtmRemoteInvitationAcceptBlock _Nullable)completion;

/**
 Allows the callee to decline a call invitation.

 @param remoteInvitation An MetaRtmRemoteInvitation object.
 @param completion An MetaRtmRemoteInvitationRefuseBlock object.

 - Success:
    - The caller receives the MetaRtmRemoteInvitationRefuseBlock object with the
 `MetaRtmInvitationApiCallErrorOk` state and the [localInvitationRefused]([MetaRtmCallDelegate
 rtmCallKit:localInvitationRefused:withResponse:]) callback.
    - The callee receives the [remoteInvitationRefused]([MetaRtmCallDelegate
 rtmCallKit:remoteInvitationRefused:]) callback.
 - Failure: The caller receives the MetaRtmRemoteInvitationRefuseBlock object with an error code.
 See MetaRtmInvitationApiCallErrorCode for the error codes.
 */
- (void)refuseRemoteInvitation:(MetaRtmRemoteInvitation *_Nonnull)remoteInvitation
                    completion:(MetaRtmRemoteInvitationRefuseBlock _Nullable)completion;
@end
