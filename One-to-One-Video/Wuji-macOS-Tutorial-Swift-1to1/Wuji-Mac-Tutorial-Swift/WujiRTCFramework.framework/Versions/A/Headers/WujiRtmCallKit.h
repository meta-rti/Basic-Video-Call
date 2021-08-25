//
//  WujiRtmKit.h
//  WujiRtmKit
//
//  Copyright (c) 2020 Wuji.io. All rights reserved.
//

#import <Foundation/Foundation.h>

@class WujiRtmKit;
@class WujiRtmCallKit;

/**
<b>RETURNED TO THE CALLER.</b> States of an outgoing call invitation.
 */
typedef NS_ENUM(NSInteger, WujiRtmLocalInvitationState) {

  /**
0: <b>RETURNED TO THE CALLER.</b> The initial state of a call invitation (idle).
   */
  WujiRtmLocalInvitationStateIdle = 0,

  /**
1: FOR INTERNAL USE ONLY.
   */
  WujiRtmLocalInvitationStateSentToRemote = 1,

  /**
2: <b>RETURNED TO THE CALLER.</b> The call invitation is received by the callee.
   */
  WujiRtmLocalInvitationStateReceivedByRemote = 2,

  /**
3: <b>RETURNED TO THE CALLER.</b> The call invitation is accepted by the callee.
   */
  WujiRtmLocalInvitationStateAcceptedByRemote = 3,

  /**
4: <b>RETURNED TO THE CALLER.</b> The call invitation is declined by the callee.
   */
  WujiRtmLocalInvitationStateRefusedByRemote = 4,

  /**
5: <b>RETURNED TO THE CALLER.</b> You have canceled the call invitation.
   */
  WujiRtmLocalInvitationStateCanceled = 5,

  /**
6: <b>RETURNED TO THE CALLER.</b> The life cycle of the outgoing call invitation ends in failure.
   */
  WujiRtmLocalInvitationStateFailure = 6,
};

/**
<b>RETURNED TO THE CALLEE.</b> States of an incoming call invitation.
 */
typedef NS_ENUM(NSInteger, WujiRtmRemoteInvitationState) {

  /**
0: <b>RETURNED TO THE CALLEE.</b> The initial state of a call invitation (idle).
   */
  WujiRtmRemoteInvitationStateIdle = 0,

  /**
1: <b>RETURNED TO THE CALLEE.</b> A call invitation from a remote caller is received.
   */
  WujiRtmRemoteInvitationStateInvitationReceived = 1,

  /**
2: FOR INTERNAL USE ONLY.
   */
  WujiRtmRemoteInvitationStateAcceptSentToLocal = 2,

  /**
3: <b>RETURNED TO THE CALLEE.</b> You have declined the call invitation.
   */
  WujiRtmRemoteInvitationStateRefused = 3,

  /**
4: <b>RETURNED TO THE CALLEE.</b> You have accepted the call invitation.
   */
  WujiRtmRemoteInvitationStateAccepted = 4,

  /**
5: <b>RETURNED TO THE CALLEE.</b> The call invitation is canceled by the remote caller.
   */
  WujiRtmRemoteInvitationStateCanceled = 5,

  /**
6: <b>RETURNED TO THE CALLEE.</b> The life cycle of the incoming call invitation ends in failure.
   */
  WujiRtmRemoteInvitationStateFailure = 6,
};

/**
<b>RETURNED TO THE CALLER.</b> Error codes of an outgoing call invitation.
 */
typedef NS_ENUM(NSInteger, WujiRtmLocalInvitationErrorCode) {

  /**
0: <b>RETURNED TO THE CALLER.</b> The outgoing call invitation succeeds.
   */
  WujiRtmLocalInvitationErrorOk = 0,

  /**
1: <b>RETURNED TO THE CALLER.</b> The callee is offline. <p> The SDK: <ul><li>Keeps resending the
call invitation to the callee, if he or she is offline.</li><li>Returns this error code, if he or
she is still offline 30 seconds since the call invitation is sent.</li></ul>
   */
  WujiRtmLocalInvitationErrorRemoteOffline = 1,

  /**
2: <b>RETURNED TO THE CALLER.</b> The callee is online but has not ACKed to the call invitation 30
seconds since it is sent.
   */
  WujiRtmLocalInvitationErrorRemoteNoResponse = 2,

  /**
3: <b>RETURNED TO THE CALLER. SAVED FOR FUTURE USE.</b> The call invitation expires 60 seconds since
it is sent, if the callee ACKs to the call invitation but neither the caller or callee takes any
further action (cancel, accpet, or decline it).
   */
  WujiRtmLocalInvitationErrorExpire = 3,

  /**
4: <b>RETURNED TO THE CALLER.</b> The caller is not logged in.
   */
  WujiRtmLocalInvitationErrorNotLoggedIn = 4,
};

/**
<b>RETURNED TO THE CALLEE.</b> Error codes of an incoming call invitation.
 */
typedef NS_ENUM(NSInteger, WujiRtmRemoteInvitationErrorCode) {

  /**
0: <b>RETURNED TO THE CALLEE.</b> The incoming call invitation succeeds.
   */
  WujiRtmRemoteInvitationErrorOk = 0,

  /**
1: <b>RETURNED TO THE CALLEE.</b> The call invitation received by the callee fails: the callee is
not online.
   */
  WujiRtmRemoteInvitationErrorLocalOffline = 1,

  /**
2: <b>RETURNED TO THE CALLEE.</b> The call invitation received by callee fails: The callee does not
ACK within a set time after the callee accepts the call invitation. This is usually a result of a
network interruption.
   */
  WujiRtmRemoteInvitationErrorAcceptFailure = 2,

  /**
3: <b>RETURNED TO THE CALLEE.</b> The call invitation received by the callee fails: the call
invitation expires 60 seconds since it is sent, if the callee ACKs to the call invitation but
neither the caller or callee takes any further action (cancel, accpet, or decline it).
   */
  WujiRtmRemoteInvitationErrorExpire = 3,
};

/**
Error codes for the call invitation methods.
 */
typedef NS_ENUM(NSInteger, WujiRtmInvitationApiCallErrorCode) {

  /**
0: The method call succeeds.
   */
  WujiRtmInvitationApiCallErrorOk = 0,

  /**
1: The method call fails. Invalid argument, for example, the value of the content parameter exceeds
8K bytes.
   */
  WujiRtmInvitationApiCallErrorInvalidAugment = 1,

  /**
2: The method call fails. The call invitation has not started.
   */
  WujiRtmInvitationApiCallErrorNotStarted = 2,

  /**
3: The method call fails. The call invitation has ended.
   */
  WujiRtmInvitationApiCallErrorAlreadyEnd = 3,

  /**
4: The method call fails. The call invitation is already accepted.
   */
  WujiRtmInvitationApiCallErrorAlreadyAccept = 4,

  /**
5: The method call fails. The call invitation is already sent.
   */
  WujiRtmInvitationApiCallErrorAlreadySent = 5,
};

/**
 Returns the result of the [sendLocalInvitation]([WujiRtmCallKit sendLocalInvitation:completion:])
 method call. See WujiRtmInvitationApiCallErrorCode for the error codes.
 */
typedef void (^WujiRtmLocalInvitationSendBlock)(WujiRtmInvitationApiCallErrorCode errorCode);

/**
 Returns the result of the [acceptRemoteInvitation]([WujiRtmCallKit
 acceptRemoteInvitation:completion:]) method call. See WujiRtmInvitationApiCallErrorCode for the
 error codes.
 */
typedef void (^WujiRtmRemoteInvitationAcceptBlock)(WujiRtmInvitationApiCallErrorCode errorCode);

/**
 Returns the result of the [refuseRemoteInvitation]([WujiRtmCallKit
 refuseRemoteInvitation:completion:]) method call. See WujiRtmInvitationApiCallErrorCode for the
 error codes.
 */
typedef void (^WujiRtmRemoteInvitationRefuseBlock)(WujiRtmInvitationApiCallErrorCode errorCode);

/**
 Returns the result of the [cancelLocalInvitation]([WujiRtmCallKit
 cancelLocalInvitation:completion:]) method call. See WujiRtmInvitationApiCallErrorCode for the
 error codes.
 */
typedef void (^WujiRtmLocalInvitationCancelBlock)(WujiRtmInvitationApiCallErrorCode errorCode);

/**
 The caller's call invitation object.
 */
__attribute__((visibility("default"))) @interface WujiRtmLocalInvitation : NSObject

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

 To intercommunicate with the legacy Wuji Signaling SDK, you MUST set the channel ID. However, even
 if the callee successfully accepts the call invitation, the Wuji RTM SDK does not join the channel
 of the specified channel ID.
 */
@property(nonatomic, copy, nullable) NSString *channelId;

/**
 The state of the outgoing call invitation. See WujiRtmLocalInvitationState.
 */
@property(nonatomic, assign, readonly) WujiRtmLocalInvitationState state;

/**
 Creates an WujiRtmLocalInvitation instance.

 @param calleeId uid of the callee.
 @return An WujiRtmLocalInvitation instance.
 */
- (instancetype _Nonnull)initWithCalleeId:(NSString *_Nonnull)calleeId;
@end

/** The callee's call invitation object. */
__attribute__((visibility("default"))) @interface WujiRtmRemoteInvitation : NSObject

/** User ID of the caller. */
@property(nonatomic, copy, nonnull, readonly) NSString *callerId;

/** The call invitation content set by the caller. */
@property(nonatomic, copy, nullable, readonly) NSString *content;

/** The callee's reponse to the call invitation. */
@property(nonatomic, copy, nullable) NSString *response;

/**The channel ID. */
@property(nonatomic, copy, nullable, readonly) NSString *channelId;

/** The state of the incoming call invitation. See WujiRtmRemoteInvitationState. */
@property(nonatomic, assign, readonly) WujiRtmRemoteInvitationState state;
@end

/**
 The WujiRtmCallDelegate protocol enables Wuji RTM call callback event notifications to your app.
 */
@protocol WujiRtmCallDelegate <NSObject>
@optional

/**
 Callback to the caller: occurs when the callee receives the call invitation.

 @param callKit An RtmCallKit object.
 @param localInvitation An WujiRtmLocalInvitation object.
 */
- (void)rtmCallKit:(WujiRtmCallKit *_Nonnull)callKit
    localInvitationReceivedByPeer:(WujiRtmLocalInvitation *_Nonnull)localInvitation;

/**
 Callback to the caller: occurs when the callee accepts the call invitation.

 @param callKit An RtmCallKit object.
 @param localInvitation An WujiRtmLocalInvitation object.
 @param response The response set by the callee.
 */
- (void)rtmCallKit:(WujiRtmCallKit *_Nonnull)callKit
    localInvitationAccepted:(WujiRtmLocalInvitation *_Nonnull)localInvitation
               withResponse:(NSString *_Nullable)response;

/**
 Callback to the caller: occurs when the callee declines the call invitation.

 @param callKit An RtmCallKit object.
 @param localInvitation An WujiRtmLocalInvitation object.
 @param response The response set by the callee.
 */
- (void)rtmCallKit:(WujiRtmCallKit *_Nonnull)callKit
    localInvitationRefused:(WujiRtmLocalInvitation *_Nonnull)localInvitation
              withResponse:(NSString *_Nullable)response;

/**
 Callback to the caller: occurs when the caller cancels a call invitation.

 @param callKit An RtmCallKit object.
 @param localInvitation An WujiRtmLocalInvitation object.
 */
- (void)rtmCallKit:(WujiRtmCallKit *_Nonnull)callKit
    localInvitationCanceled:(WujiRtmLocalInvitation *_Nonnull)localInvitation;

/**
 Callback to the caller: occurs when the life cycle of the outgoing call invitation ends in failure.

 @param callKit An RtmCallKit object.
 @param localInvitation An WujiRtmLocalInvitation object.
 @param errorCode See WujiRtmLocalInvitationErrorCode for the error codes.
 */
- (void)rtmCallKit:(WujiRtmCallKit *_Nonnull)callKit
    localInvitationFailure:(WujiRtmLocalInvitation *_Nonnull)localInvitation
                 errorCode:(WujiRtmLocalInvitationErrorCode)errorCode;

/**
 Callback to the callee: occurs when the callee receives a call invitation.

 @param callKit An RtmCallKit object.
 @param remoteInvitation An WujiRtmRemoteInvitation object.
 */
- (void)rtmCallKit:(WujiRtmCallKit *_Nonnull)callKit
    remoteInvitationReceived:(WujiRtmRemoteInvitation *_Nonnull)remoteInvitation;

/**
 Callback to the callee: occurs when the callee declines a call invitation.

 @param callKit An RtmCallKit object.
 @param remoteInvitation An WujiRtmRemoteInvitation object.
 */
- (void)rtmCallKit:(WujiRtmCallKit *_Nonnull)callKit
    remoteInvitationRefused:(WujiRtmRemoteInvitation *_Nonnull)remoteInvitation;

/**
 Callback to the callee: occurs when the callee accepts a call invitation.

 @param callKit An RtmCallKit object.
 @param remoteInvitation An WujiRtmRemoteInvitation object.
 */
- (void)rtmCallKit:(WujiRtmCallKit *_Nonnull)callKit
    remoteInvitationAccepted:(WujiRtmRemoteInvitation *_Nonnull)remoteInvitation;

/**
 Callback to the callee: occurs when the caller cancels the call invitation.

 @param callKit An RtmCallKit object.
 @param remoteInvitation An WujiRtmRemoteInvitation object.
 */
- (void)rtmCallKit:(WujiRtmCallKit *_Nonnull)callKit
    remoteInvitationCanceled:(WujiRtmRemoteInvitation *_Nonnull)remoteInvitation;

/**
 Callback to the callee: occurs when the life cycle of the incoming call invitation ends in failure.

 @param callKit An RtmCallKit object.
 @param remoteInvitation An WujiRtmRemoteInvitation object.
 @param errorCode See WujiRtmRemoteInvitationErrorCode for the error codes.
 */
- (void)rtmCallKit:(WujiRtmCallKit *_Nonnull)callKit
    remoteInvitationFailure:(WujiRtmRemoteInvitation *_Nonnull)remoteInvitation
                  errorCode:(WujiRtmRemoteInvitationErrorCode)errorCode;
@end

__attribute__((visibility("default"))) @interface WujiRtmCallKit : NSObject
/** An WujiRtmKit instance. */
@property(atomic, readonly, weak, nullable) WujiRtmKit *rtmKit;
/** WujiRtmCallDelegate enables Wuji RTM call callback event notifications to your app. */
@property(nonatomic, weak, nullable) id<WujiRtmCallDelegate> callDelegate;  // nonatomic

/**
 Allows the caller to send a call invitation to the callee.

 @param localInvitation An WujiRtmLocalInvitation object.
 @param completion An WujiRtmLocalInvitationSendBlock object, which indicates the result of sending
 a call invitation to a callee. See WujiRtmInvitationApiCallErrorCode for the error codes.

  - Success:
    - The caller receives the WujiRtmLocalInvitationSendBlock object with the
 `WujiRtmInvitationApiCallErrorOk` state and the
 [localInvitationReceivedByPeer]([WujiRtmCallDelegate rtmCallKit:localInvitationReceivedByPeer:])
 callback.
    - The callee receives the [remoteInvitationReceived]([WujiRtmCallDelegate
 rtmCallKit:remoteInvitationReceived:]) callback.
 - Failure: The caller receives the WujiRtmLocalInvitationSendBlock object with an error code. See
 WujiRtmInvitationApiCallErrorCode for the error codes.
 */
- (void)sendLocalInvitation:(WujiRtmLocalInvitation *_Nonnull)localInvitation
                 completion:(WujiRtmLocalInvitationSendBlock _Nullable)completion;

/**
 Allows the caller to cancel a call invitation.

 @param localInvitation An WujiRtmLocalInvitation object.
 @param completion An WujiRtmLocalInvitationCancelBlock object.

 - Success:
    - The caller receives the WujiRtmLocalInvitationCancelBlock object with the
 `WujiRtmInvitationApiCallErrorOk` state and the [localInvitationCanceled]([WujiRtmCallDelegate
 rtmCallKit:localInvitationCanceled:]) callback.
    - The callee receives the [remoteInvitationCanceled]([WujiRtmCallDelegate
 rtmCallKit:remoteInvitationCanceled:]) callback.
 - Failure: The caller receives the WujiRtmLocalInvitationCancelBlock object with an error code. See
 WujiRtmInvitationApiCallErrorCode for the error codes.

 */
- (void)cancelLocalInvitation:(WujiRtmLocalInvitation *_Nonnull)localInvitation
                   completion:(WujiRtmLocalInvitationCancelBlock _Nullable)completion;

/**
 Allows the callee to accept a call invitation.

 @param remoteInvitation An WujiRtmRemoteInvitation object.
 @param completion An WujiRtmRemoteInvitationAcceptBlock object.

 - Success:
    - The caller receives the WujiRtmRemoteInvitationAcceptBlock object with the
 `WujiRtmInvitationApiCallErrorOk` state and the [localInvitationAccepted]([WujiRtmCallDelegate
 rtmCallKit:localInvitationAccepted:withResponse:]) callback.
    - The callee receives the [remoteInvitationAccepted]([WujiRtmCallDelegate
 rtmCallKit:remoteInvitationAccepted:]) callback.
 - Failure: The caller receives the WujiRtmRemoteInvitationAcceptBlock object with an error code.
 See WujiRtmInvitationApiCallErrorCode for the error codes.

 */
- (void)acceptRemoteInvitation:(WujiRtmRemoteInvitation *_Nonnull)remoteInvitation
                    completion:(WujiRtmRemoteInvitationAcceptBlock _Nullable)completion;

/**
 Allows the callee to decline a call invitation.

 @param remoteInvitation An WujiRtmRemoteInvitation object.
 @param completion An WujiRtmRemoteInvitationRefuseBlock object.

 - Success:
    - The caller receives the WujiRtmRemoteInvitationRefuseBlock object with the
 `WujiRtmInvitationApiCallErrorOk` state and the [localInvitationRefused]([WujiRtmCallDelegate
 rtmCallKit:localInvitationRefused:withResponse:]) callback.
    - The callee receives the [remoteInvitationRefused]([WujiRtmCallDelegate
 rtmCallKit:remoteInvitationRefused:]) callback.
 - Failure: The caller receives the WujiRtmRemoteInvitationRefuseBlock object with an error code.
 See WujiRtmInvitationApiCallErrorCode for the error codes.
 */
- (void)refuseRemoteInvitation:(WujiRtmRemoteInvitation *_Nonnull)remoteInvitation
                    completion:(WujiRtmRemoteInvitationRefuseBlock _Nullable)completion;
@end
