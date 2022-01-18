//
//  MetaRtmKit.h
//  MetaRtmKit
//
//  Copyright (c) 2020 Meta.io. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MetaRtmCallKit.h"

/**
 The `MetaRtmKit` class is the entry point of the Meta RTM SDK.
 */
@class MetaRtmKit;
/**
 The MetaRtmMessage class provides Meta RTM message methods that can be invoked by your app.
 */
@class MetaRtmMessage;

@class MetaRtmFileMessage;

@class MetaRtmImageMessage;
/**
 The MetaRtmChannel class provides Meta RTM channel methods that can be invoked by your app.
 */
@class MetaRtmChannel;
/**
 The MetaRtmCallKit class provides Meta RTM call methods that can be invoked by your app.
 */
@class MetaRtmCallKit;

/**
 MetaRtmPeerOnlineStatus provides the online status of a specified user.
 */
@class MetaRtmPeerOnlineStatus;

/**
 The prefix for ending a call. You can use it with the [sendMessage]([MetaRtmKit
 sendMessage:toPeer:sendMessageOptions:completion:]) method to be compatible with the endCall method
 of the legacy Meta Signaling SDK.
 */
static NSString * _Nonnull  const MetaRtmEndcallPrefix = @"MetaRTMLegacyEndcallCompatibleMessagePrefix";

/**
Message types.
 */
typedef NS_ENUM(NSInteger, MetaRtmMessageType) {

  /**
0: Undefined message type.
   */
  MetaRtmMessageTypeUndefined = 0,

  /**
1: A text message.
   */
  MetaRtmMessageTypeText = 1,

  /**
2: A raw message.
   */
  MetaRtmMessageTypeRaw = 2,

  /**
3: A file message. The size of a file message must be less than 32 KB.
   */
  MetaRtmMessageTypeFile = 3,

  /**
4: An image message. The size of an image message must be less than 32 KB.
   */
  MetaRtmMessageTypeImage = 4,
};

/**
Error codes related to sending a peer-to-peer message.
 */
typedef NS_ENUM(NSInteger, MetaRtmSendPeerMessageErrorCode) {

  /**
0: The specified user receives the peer-to-peer message.
   */
  MetaRtmSendPeerMessageErrorOk = 0,

  /**
1: The user fails to send the peer-to-peer message.
   */
  MetaRtmSendPeerMessageErrorFailure = 1,

  /**
2: A timeout occurs when sending the peer-to-peer message. The current timeout is set as 10 seconds.
Possible reasons: The user is in the `MetaRtmConnectionStateAborted` or
`MetaRtmConnectionStateReconnecting` state.
   */
  MetaRtmSendPeerMessageErrorTimeout = 2,

  /**
3: The user is offline and has not received the peer-to-peer message.
   */
  MetaRtmSendPeerMessageErrorPeerUnreachable = 3,

  /**
4: The specified user is offline and does not receive the peer-to-peer message, but the server has
cached the message and will send the message to the specified user when he/she is back online.
   */
  MetaRtmSendPeerMessageErrorCachedByServer = 4,

  /**
5: The method call frequency exceeds the limit of 60 queries per second (channel and peer messages
taken together).
   */
  MetaRtmSendPeerMessageErrorTooOften = 5,

  /**
6: The user ID is invalid.
   */
  MetaRtmSendPeerMessageErrorInvalidUserId = 6,

  /**
7: The message is null or exceeds 32 KB in length.
   */
  MetaRtmSendPeerMessageErrorInvalidMessage = 7,
  /**
8: The message receiver‘s SDK is of an earlier version and hence cannot recognize this message.
   */
  MetaRtmSendPeerMessageErrorImcompatibleMessage = 8,

  /**
101: The SDK is not initialized.
   */
  MetaRtmSendPeerMessageErrorNotInitialized = 101,

  /**
102: The sender does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before sending the peer-to-peer message.
   */
  MetaRtmSendPeerMessageErrorNotLoggedIn = 102,
};

/**
Connection states between the SDK and the Meta RTM system.
 */
typedef NS_ENUM(NSInteger, MetaRtmConnectionState) {

  /**
  1: The initial state. The SDK is disconnected from the Meta RTM system.
  <p>When the user calls the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method, the
  SDK starts to log in the Meta RTM system, triggers the [connectionStateChanged]([MetaRtmDelegate
  rtmKit:connectionStateChanged:reason:]) callback, and switches to the
  `MetaRtmConnectionStateConnecting` state.
   */
  MetaRtmConnectionStateDisconnected = 1,

  /**
  2: The SDK is logging in the Meta RTM system.
  <p><li>Success: The SDK triggers the [connectionStateChanged]([MetaRtmDelegate
  rtmKit:connectionStateChanged:reason:]) callback and switches to the
  `MetaRtmConnectionStateConnected` state. <li>Failure: The SDK triggers the
  [connectionStateChanged]([MetaRtmDelegate rtmKit:connectionStateChanged:reason:]) callback and
  switches to the `MetaRtmConnectionStateDisConnected` state.
  */
  MetaRtmConnectionStateConnecting = 2,

  /**
  3: The SDK has logged in the Meta RTM system.
  <p><li>If the connection between the SDK and the Meta RTM system is interrupted because of network
  issues, the SDK triggers the [connectionStateChanged]([MetaRtmDelegate
  rtmKit:connectionStateChanged:reason:]) callback and switches to the
  `MetaRtmConnectionStateReconnecting` state. <li>If the login is banned by the server because, for
  example, another instance logs in the Meta RTM system with the same user ID, the SDK triggers the
  [connectionStateChanged]([MetaRtmDelegate rtmKit:connectionStateChanged:reason:]) callback and
  switches to the `MetaRtmConnectionStateAborted` state. <li>If the user calls the
  [logoutWithCompletion]([MetaRtmKit logoutWithCompletion:]) method to log out of the Meta RTM
  system and receives `MetaRtmLogoutErrorOk`, the SDK triggers the
  [connectionStateChanged]([MetaRtmDelegate rtmKit:connectionStateChanged:reason:]) callback and
  switches to the `MetaRtmConnectionStateDisconnected` state.
  */
  MetaRtmConnectionStateConnected = 3,

  /**
  4: The connection state between the SDK and the Meta RTM system is interrupted due to network
  issues, and the SDK keeps re-logging in the Meta RTM system. <p><li>If the SDK successfully
  re-logs in the Meta RTM system, it triggers the [connectionStateChanged]([MetaRtmDelegate
  rtmKit:connectionStateChanged:reason:]) callback and switches to the
  `MetaRtmConnectionStateConnected` state. The SDK automatically adds the user back to the
  channel(s) he or she was in when the connection was interrupted, and synchronizes the local user's
  attributes with the server. <li>If the SDK fails to re-log in the Meta RTM system, the SDK stays
  in the `MetaRtmConnectionStateReconnecting` state and keeps re-logging in the system.
  */
  MetaRtmConnectionStateReconnecting = 4,

  /**
  5: The SDK gives up logging in the Meta RTM system, mainly because another instance has logged in
  the Meta RTM system with the same user ID. <p>You must call the [logoutWithCompletion]([MetaRtmKit
  logoutWithCompletion:]) method before calling the [loginByToken]([MetaRtmKit
  loginByToken:user:completion:]) method to log in the Meta RTM system again.
  */
  MetaRtmConnectionStateAborted = 5,
};

/**
Reasons for a connection state change.
 */
typedef NS_ENUM(NSInteger, MetaRtmConnectionChangeReason) {

  /**
1: The SDK is logging in the Meta RTM system.
   */
  MetaRtmConnectionChangeReasonLogin = 1,

  /**
2: The SDK has logged in the Meta RTM system.
   */
  MetaRtmConnectionChangeReasonLoginSuccess = 2,

  /**
3: The SDK fails to log in the Meta RTM system.
   */
  MetaRtmConnectionChangeReasonLoginFailure = 3,

  /**
4: The login has timed out for 10 seconds, and the SDK stops logging in.
   */
  MetaRtmConnectionChangeReasonLoginTimeout = 4,

  /**
5: The connection between the SDK and the Meta RTM system is interrupted for more than four seconds.
   */
  MetaRtmConnectionChangeReasonInterrupted = 5,

  /**
6: The user has called the [logoutWithCompletion]([MetaRtmKit logoutWithCompletion:]) method to log
out of the Meta RTM system.
   */
  MetaRtmConnectionChangeReasonLogout = 6,

  /**
7: Login is banned by the Meta RTM server.
   */
  MetaRtmConnectionChangeReasonBannedByServer = 7,

  /**
8: Another instance has logged in the Meta RTM system with the same user ID.
   */
  MetaRtmConnectionChangeReasonRemoteLogin = 8,
};

/**
Error codes related to login.
 */
typedef NS_ENUM(NSInteger, MetaRtmLoginErrorCode) {

  /**
0: Login succeeds. No error occurs.
   */
  MetaRtmLoginErrorOk = 0,

  /**
1: Login fails for reasons unknown.
   */
  MetaRtmLoginErrorUnknown = 1,

  /**
2: Login is rejected by the server.
   */
  MetaRtmLoginErrorRejected = 2,

  /**
3: Invalid login arguments.
   */
  MetaRtmLoginErrorInvalidArgument = 3,

  /**
4: The App ID is invalid.
   */
  MetaRtmLoginErrorInvalidAppId = 4,

  /**
5: The token is invalid.
   */
  MetaRtmLoginErrorInvalidToken = 5,

  /**
6: The token has expired, and hence login is rejected.
   */
  MetaRtmLoginErrorTokenExpired = 6,

  /**
7: Unauthorized login.
   */
  MetaRtmLoginErrorNotAuthorized = 7,

  /**
8: The user has already logged in or is logging in the Meta RTM system, or the user has not called
the [logoutWithCompletion]([MetaRtmKit logoutWithCompletion:]) method to leave the
`MetaRtmConnectionStateAborted` state.
   */
  MetaRtmLoginErrorAlreadyLogin = 8,

  /**
9: The login times out. The current timeout is set as six seconds.
   */
  MetaRtmLoginErrorTimeout = 9,

  /**
10: The call frequency of the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method
exceeds the limit of two queries per second.
   */
  MetaRtmLoginErrorLoginTooOften = 10,

  /**
101: The SDK is not initialized.
   */
  MetaRtmLoginErrorLoginNotInitialized = 101,
};

/**
Error codes related to logout.
 */
typedef NS_ENUM(NSInteger, MetaRtmLogoutErrorCode) {

  /**
0: Logout succeeds. No error occurs.
   */
  MetaRtmLogoutErrorOk = 0,

  /**
1: **RESERVED FOR FUTURE USE**
   */
  MetaRtmLogoutErrorRejected = 1,

  /**
101: The SDK is not initialized.
   */
  MetaRtmLogoutErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before the user logs out of the Meta RTM system.
   */
  MetaRtmLogoutErrorNotLoggedIn = 102,
};

/**
Error codes related to querying the online status of the specified peer(s).
 */
typedef NS_ENUM(NSInteger, MetaRtmQueryPeersOnlineErrorCode) {

  /**
0: The method call succeeds.
   */
  MetaRtmQueryPeersOnlineErrorOk = 0,

  /**
1: The method call fails.
   */
  MetaRtmQueryPeersOnlineErrorFailure = 1,

  /**
2: The method call fails. The argument is invalid.
   */
  MetaRtmQueryPeersOnlineErrorInvalidArgument = 2,

  /**
3: **RESERVED FOR FUTURE USE**
   */
  MetaRtmQueryPeersOnlineErrorRejected = 3,

  /**
4: The SDK has not received a response from the server for 10 seconds. The current timeout is set as
10 seconds. Possible reasons: The user is in the `MetaRtmConnectionStateAborted` or
`MetaRtmConnectionStateReconnecting` state.
   */
  MetaRtmQueryPeersOnlineErrorTimeout = 4,

  /**
5: The method call frequency of this method exceeds the limit of 10 queries every five seconds.
   */
  MetaRtmQueryPeersOnlineErrorTooOften = 5,

  /**
101: The SDK is not initialized.
   */
  MetaRtmQueryPeersOnlineErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before querying the online status.
   */
  MetaRtmQueryPeersOnlineErrorNotLoggedIn = 102,
};

/**
Error codes related to attrubute operations.
 */
typedef NS_ENUM(NSInteger, MetaRtmProcessAttributeErrorCode) {

  /**
0: The attribute operation succeeds.
   */
  MetaRtmAttributeOperationErrorOk = 0,

  /**
1: **DEPRECATED**
   */
  MetaRtmAttributeOperationErrorNotReady = 1,

  /**
2: The attribute operation fails.
   */
  MetaRtmAttributeOperationErrorFailure = 2,

  /**
3: The argument you put for this attribute operation is invalid.
   */
  MetaRtmAttributeOperationErrorInvalidArgument = 3,

  /**
4: The attribute size exceeds the limit. <p><li> For user attribute operations: The user's overall
attribute size would exceed the limit of 16 KB, one of the user's attributes would exceeds 8 KB in
size, or the number of this user's attributes would exceed 32 after this attribute operation.<li>
For channel attribute operations: The channel's overall attribute size would exceed the limit of 32
KB, one of the channel attributes would exceed 8 KB in size, or the number of this channel's
attributes would exceed 32 after this attribute operation.
   */
  MetaRtmAttributeOperationErrorSizeOverflow = 4,

  /**
5: The method call frequency exceeds the limit.<p><li>For [setLocalUserAttributes]([MetaRtmKit
setLocalUserAttributes:completion:]), [addOrUpdateLocalUserAttributes]([MetaRtmKit
addOrUpdateLocalUserAttributes:completion:]), [deleteLocalUserAttributesByKeys]([MetaRtmKit
deleteLocalUserAttributesByKeys:completion:]) and [clearLocalUserAttributes]([MetaRtmKit
clearLocalUserAttributesWithCompletion:]) taken together: the limit is 10 queries every five
seconds.<li>For [getUserAttributes]([MetaRtmKit getUserAllAttributes:completion:]) and
[getUserAttributesByKeys]([MetaRtmKit getUserAttributes:ByKeys:completion:]) taken together, the
limit is 40 queries every five seconds.<li>For [setChannelAttributes]([MetaRtmKit
setChannel:Attributes:Options:completion:]), [addOrUpdateChannelAttributes]([MetaRtmKit
addOrUpdateChannel:Attributes:Options:completion:]), [deleteChannelAttributesByKeys]([MetaRtmKit
deleteChannel:AttributesByKeys:Options:completion:]) and [clearChannelAttributes]([MetaRtmKit
clearChannel:Options:AttributesWithCompletion:]) taken together: the limit is 10 queries every five
seconds.<li>For [getChannelAllAttributes]([MetaRtmKit getChannelAllAttributes:completion:]) and
[getChannelAttributesByKeys]([MetaRtmKit getChannelAttributes:ByKeys:completion:]) taken together,
the limit is 10 queries every five seconds.
   */
  MetaRtmAttributeOperationErrorTooOften = 5,

  /**
6: The specified user is not found, either because the user is offline or because the user does not
exist.
   */
  MetaRtmAttributeOperationErrorUserNotFound = 6,

  /**
7: A timeout occurs in the attribute-related operation. The current timeout is set as five seconds.
Possible reasons: The user is in the `MetaRtmConnectionStateAborted` or
`MetaRtmConnectionStateReconnecting` state.
   */
  MetaRtmAttributeOperationErrorTimeout = 7,

  /**
101: The SDK is not initialized.
   */
  MetaRtmAttributeOperationErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before the attribute operation.
   */
  MetaRtmAttributeOperationErrorNotLoggedIn = 102,
};

/**
Error codes related to renewing the token.
 */
typedef NS_ENUM(NSInteger, MetaRtmRenewTokenErrorCode) {

  /**
0: The token-renewing operation succeeds.
   */
  MetaRtmRenewTokenErrorOk = 0,

  /**
1: Common unknown failure.
   */
  MetaRtmRenewTokenErrorFailure = 1,

  /**
2: The method call fails. The argument is invalid.
   */
  MetaRtmRenewTokenErrorInvalidArgument = 2,

  /**
3: **RESERVED FOR FUTURE USE**
   */
  MetaRtmRenewTokenErrorRejected = 3,

  /**
4: The method call frequency of exceeds the limit of two queries per second.
   */
  MetaRtmRenewTokenErrorTooOften = 4,

  /**
5: The token has expired.
   */
  MetaRtmRenewTokenErrorTokenExpired = 5,

  /**
6: The token is invalid.
   */
  MetaRtmRenewTokenErrorInvalidToken = 6,

  /**
101: The SDK is not initialized.
   */
  MetaRtmRenewTokenErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before renewing the token.
   */
  MetaRtmRenewTokenErrorNotLoggedIn = 102,
};

/**
Error codes related to retrieving the channel member count of specified channel(s).
 */
typedef NS_ENUM(NSInteger, MetaRtmChannelMemberCountErrorCode) {

  /**
0: The operation succeeds.
   */
  MetaRtmChannelMemberCountErrorOk = 0,

  /**
1: Unknown common failure.
   */
  MetaRtmChannelMemberCountErrorFailure = 1,

  /**
2: One or several of your channel IDs is invalid.
   */
  MetaRtmChannelMemberCountErrorInvalidArgument = 2,

  /**
3: The method call frequency exceeds the limit of one query per second.
   */
  MetaRtmChannelMemberCountErrorTooOften = 3,

  /**
4: A timeout occurs during this operation. The current timeout is set as five seconds.
   */
  MetaRtmChannelMemberCountErrorTimeout = 4,

  /**
5: The number of the channels that you query is greater than 32.
   */
  MetaRtmChannelMemberCountErrorExceedLimit = 5,

  /**
101: The SDK is not initialized.
   */
  MetaRtmChannelMemberCountErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  MetaRtmChannelMemberCountErrorNotLoggedIn = 102,
};

/**
Error codes related to subscribing to or unsubscribing from the status of specified peer(s).
 */
typedef NS_ENUM(NSInteger, MetaRtmPeerSubscriptionStatusErrorCode) {

  /**
0: The method call succeeds, or the operation succeeds.
   */
  MetaRtmPeerSubscriptionStatusErrorOk = 0,

  /**
1: Common failure. The user fails to subscribe to or unsubscribe from the status of the specified
peer(s).
   */
  MetaRtmPeerSubscriptionStatusErrorFailure = 1,

  /**
2: The method call fails. The argument is invalid.
   */
  MetaRtmPeerSubscriptionStatusErrorInvalidArgument = 2,

  /**
3: **RESERVED FOR FUTURE USE**
   */
  MetaRtmPeerSubscriptionStatusErrorRejected = 3,

  /**
4: The SDK fails to receive a response from the server in 10 seconds. The current timeout is set as
10 seconds. Possible reasons: The user is in the \ref meta::rtm::CONNECTION_STATE_ABORTED
"CONNECTION_STATE_ABORTED" or \ref meta::rtm::CONNECTION_STATE_RECONNECTING
"CONNECTION_STATE_RECONNECTING" state.
   */
  MetaRtmPeerSubscriptionStatusErrorTimeout = 4,

  /**
5: The method call frequency exceeds the limit of 10 subscribes every five seconds.
   */
  MetaRtmPeerSubscriptionStatusErrorTooOften = 5,

  /**
6: The number of peers, to whom you subscribe, exceeds the limit of 512.
   */
  MetaRtmPeerSubscriptionStatusErrorOverflow = 6,

  /**
101: The SDK is not initialized.
   */
  MetaRtmPeerSubscriptionStatusErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  MetaRtmPeerSubscriptionStatusErrorNotLoggedIn = 102,
};

/**
Error codes related to getting a list of the peer(s) by suscription option type.
 */
typedef NS_ENUM(NSInteger, MetaRtmQueryPeersBySubscriptionOptionErrorCode) {

  /**
0: The method call succeeds, or the operation succeeds.
   */
  MetaRtmQueryPeersBySubscriptionOptionErrorOk = 0,

  /**
1: Common failure. The user fails to query peer(s) by subscription option type.
   */
  MetaRtmQueryPeersBySubscriptionOptionErrorFailure = 1,

  /**
2: The SDK fails to receive a response from the server in 5 seconds. The current timeout is set as 5
seconds. Possible reasons: The user is in the `MetaRtmConnectionStateAborted` or
`MetaRtmConnectionStateReconnecting` state.
   */
  MetaRtmQueryPeersBySubscriptionOptionErrorTimeout = 2,

  /**
3: The method call frequency exceeds the limit of 10 subscribes every five seconds.
   */
  MetaRtmQueryPeersBySubscriptionOptionErrorTooOften = 3,

  /**
101: The SDK is not initialized.
   */
  MetaRtmQueryPeersBySubscriptionOptionErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  MetaRtmQueryPeersBySubscriptionOptionErrorNotLoggedIn = 102,
};

/**
Error codes related to downloading a file or image.
 */
typedef NS_ENUM(NSInteger, MetaRtmDownloadMediaErrorCode) {

  /**
0: The method call succeeds, or the operation succeeds.
   */
  MetaRtmDownloadMediaErrorOk = 0,

  /**
1: Unknown common failure.
   */
  MetaRtmDownloadMediaErrorFailure = 1,

  /**
2: An argument you put is invalid. For example, `mediaId` is in the wrong format or `filePath` is
set as `null`.
   */
  MetaRtmDownloadMediaErrorInvalidArgument = 2,

  /**
3: A timeout occurs. The current timeout is set as 120 seconds. The SDK assumes that a timeout
occurs if it has not detected any file transmission between the SDK and the file server for 120
seconds.
   */
  MetaRtmDownloadMediaErrorTimeout = 3,
  /**
4: The file or image to download does not exist, either because the media ID you input is incorrect
or because the validity of the media ID has expired.
   */
  MetaRtmDownloadMediaErrorNotExist = 4,
  /**
5: You have exceeded the upper limit for file download. You can initiate a maximum of nine file
download or upload tasks at the same time (download and upload tasks count together).
   */
  MetaRtmDownloadMediaErrorConcurrencyLimitExceeded = 5,
  /**
6: The file or image download task is aborted for either of the following reasons:<p><li>The
receiver is in the `MetaRtmConnectionStateAborted` state.</li><li>The receiver has cancelled the
download task.</li></p>
   */
  MetaRtmDownloadMediaErrorInterrupted = 6,

  /**
101: The SDK is not initialized.
   */
  MetaRtmDownloadMediaErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  MetaRtmDownloadMediaErrorNotLoggedIn = 102,
};

/**
Error codes related to uploading a file or image.
 */
typedef NS_ENUM(NSInteger, MetaRtmUploadMediaErrorCode) {

  /**
0: The method call succeeds, or the operation succeeds.
   */
  MetaRtmUploadMediaErrorOk = 0,

  /**
1: Unknown common failure.
   */
  MetaRtmUploadMediaErrorFailure = 1,

  /**
2: The argument you put is invalid.
   */
  MetaRtmUploadMediaErrorInvalidArgument = 2,

  /**
3: A timeout occurs. The current timeout is set as 120 seconds. The SDK assumes that a timeout
occurs if it has not detected any file transmission between the SDK and the file server for 120
seconds.
   */
  MetaRtmUploadMediaErrorTimeout = 3,
  /**
4: The size of the file or image to upload exceeds 30 MB.
   */
  MetaRtmUploadMediaErrorSizeOverflow = 4,
  /**
5: You have exceeded the upper limit for file upload. You can initiate a maximum of nine file upload
or download tasks at the same time (upload and download tasks count together).
   */
  MetaRtmUploadMediaErrorConcurrencyLimitExceeded = 5,
  /**
6: The file or image upload task is aborted for either of the following reasons:<p><li>The user in
the `MetaRtmConnectionStateAborted` state. </li><li>The user has cancelled the upload task.</li></p>
   */
  MetaRtmUploadMediaErrorInterrupted = 6,

  /**
101: The SDK is not initialized.
   */
  MetaRtmUploadMediaErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  MetaRtmUploadMediaErrorNotLoggedIn = 102,
};

/**
Error codes related to cancelling a download task or cancelling an upload task.
 */
typedef NS_ENUM(NSInteger, MetaRtmCancelMediaErrorCode) {

  /**
0: The method call succeeds, or the operation succeeds.
   */
  MetaRtmCancelMediaErrorOk = 0,

  /**
1: Unknown common failure.
   */
  MetaRtmCancelMediaErrorFailure = 1,

  /**
2: The task to cancel does not exist. You can only cancel an ongoing download or upload task. If the
download or upload task completes, the corresponding `requestId` is no longer valid.
   */
  MetaRtmCancelMediaErrorNotExist = 2,

  /**
101: The SDK is not initialized.
   */
  MetaRtmCancelMediaErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  MetaRtmCancelMediaErrorNotLoggedIn = 102,
};

/**
The online states of a peer.
 */
typedef NS_ENUM(NSInteger, MetaRtmPeerOnlineState) {
  /**
0: The peer is online.
   */
  MetaRtmPeerOnlineStateOnline = 0,
  /**
1: The peer is temporarily unreachable (the server has not received a packet from the SDK for more
than six seconds).
   */
  MetaRtmPeerOnlineStateUnreachable = 1,
  /**
2: The peer is offline (the sdk has not logged in the Meta RTM system, or it has logged out of the
system, or the server has not received a packet from the SDK for more than 30 seconds).
   */
  MetaRtmPeerOnlineStateOffline = 2,
};

/**
Subscription types.
 */
typedef NS_ENUM(NSInteger, MetaRtmPeerSubscriptionOptions) {
  /**
0: Takes out a subscription to the online status of specified user(s).
   */
  MetaRtmPeerSubscriptionOnlineStatus = 0,
};

/**
 Returns the result of the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method call.
 <p><i>errorCode:</i> Login error code. See MetaRtmLoginErrorCode.
 */
typedef void (^MetaRtmLoginBlock)(MetaRtmLoginErrorCode errorCode);

/**
 Indicates the results of calling the [logoutWithCompletion]([MetaRtmKit logoutWithCompletion:])
 method call. <p><i>errorCode:</i> Logout error code. See MetaRtmLogoutErrorCode.
 */
typedef void (^MetaRtmLogoutBlock)(MetaRtmLogoutErrorCode errorCode);

/**
 Returns the result of the [sendMessage]([MetaRtmKit sendMessage:toPeer:completion:]) method call.
 <p><i>errorCode:</i> Error code of sending the peer-to-peer message. See
 MetaRtmSendPeerMessageErrorCode.
 */
typedef void (^MetaRtmSendPeerMessageBlock)(MetaRtmSendPeerMessageErrorCode errorCode);

/**
 Returns the result of the [queryPeersOnlineStatus]([MetaRtmKit queryPeersOnlineStatus:completion:])
 method call. <p><li><i>peerOnlineStatus:</i> A list of the specified users' online status. See
 MetaRtmPeerOnlineStatus. <li><i>errorCode:</i> See MetaRtmQueryPeersOnlineErrorCode.
 */
typedef void (^MetaRtmQueryPeersOnlineBlock)(NSArray<MetaRtmPeerOnlineStatus *> * _Nullable peerOnlineStatus,
                                             MetaRtmQueryPeersOnlineErrorCode errorCode);

/**
 Returns the result of the [renewToken]([MetaRtmKit renewToken:completion:]) method call.
 <p><li><i>token</i> Your new Token. <li><i>errorCode:</i> See MetaRtmRenewTokenErrorCode.
 */
typedef void (^MetaRtmRenewTokenBlock)(NSString * _Nullable token, MetaRtmRenewTokenErrorCode errorCode);

/**
 Returns the result of the [subscribePeersOnlineStatus]([MetaRtmKit
 subscribePeersOnlineStatus:completion:]) or [unsubscribePeersOnlineStatus]([MetaRtmKit
 unsubscribePeersOnlineStatus:completion:]) method call. <p><i>errorCode:</i> See
 MetaRtmPeerSubscriptionStatusErrorCode.
 */
typedef void (^MetaRtmSubscriptionRequestBlock)(MetaRtmPeerSubscriptionStatusErrorCode errorCode);

/**
 Returns the result of the [queryPeersBySubscriptionOption]([MetaRtmKit
 queryPeersBySubscriptionOption:completion:]) method call. <p><i>errorCode:</i> See
 MetaRtmQueryPeersBySubscriptionOptionErrorCode.
 */
typedef void (^MetaRtmQueryPeersBySubscriptionOptionBlock)(
                                                           NSArray<NSString *> * _Nullable peers, MetaRtmQueryPeersBySubscriptionOptionErrorCode errorCode);

/**
 Returns the result of the [downloadMediaToMemory]([MetaRtmKit
 downloadMediaToMemory:withRequest:completion:]) method call. <p><li><i>requestId:</i> The unique ID
 of the download request.<li><i>data:</i> The downloaded file or image.<li><i>errorCode:</i> See
 MetaRtmDownloadMediaErrorCode.
 */
typedef void (^MetaRtmDownloadMediaToMemoryBlock)(long long requestId,
                                                  NSData * _Nullable data,
                                                  MetaRtmDownloadMediaErrorCode errorCode);

/**
 Returns the result of the [downloadMediaToFile]([MetaRtmKit
 downloadMedia:toFile:withRequest:completion:]) method call. <p><li><i>requestId:</i> The unique ID
 of the download request.<li><i>errorCode:</i> See MetaRtmDownloadMediaErrorCode.
 */
typedef void (^MetaRtmDownloadMediaToFileBlock)(long long requestId,
                                                MetaRtmDownloadMediaErrorCode errorCode);

/**
 Returns the result of the [createFileMessageByUploading]([MetaRtmKit
 createFileMessageByUploading:withRequest:completion:]). <p><li><i>requestId:</i> The unique ID of
 the upload request.<li><i>fileMessage:</i> An MetaRtmFileMessage object. <i>errorCode:</i> See
 MetaRtmUploadMediaErrorCode.
 */
typedef void (^MetaRtmUploadFileMediaBlock)(long long requestId,
                                            MetaRtmFileMessage * _Nonnull fileMessage,
                                            MetaRtmUploadMediaErrorCode errorCode);
/**
 Returns the result of the [createImageMessageByUploading]([MetaRtmKit
 createImageMessageByUploading:withRequest:completion:]) method call. <p><li><i>requestId:</i> The
 unique ID of the upload request.<li><i>imageMessage:</i> An MetaRtmImageMessage object.
 <i>errorCode:</i> See MetaRtmUploadMediaErrorCode.
 */
typedef void (^MetaRtmUploadImageMediaBlock)(long long requestId,
                                             MetaRtmImageMessage * _Nonnull  imageMessage,
                                             MetaRtmUploadMediaErrorCode errorCode);

/**
 Returns the result of the [cancelMediaDownload]([MetaRtmKit cancelMediaDownload:completion:]) or
 [cancelMediaUpload]([MetaRtmKit cancelMediaUpload:completion:]) method call.
 <p><li><i>requestId:</i> The unique ID of the cancel request.<i>errorCode:</i> See
 MetaRtmCancelMediaErrorCode.
 */
typedef void (^MetaRtmCancelMediaBlock)(long long requestId, MetaRtmCancelMediaErrorCode errorCode);

/**
Attributes of a peer-to-peer or channel text message.
 */
__attribute__((visibility("default"))) @interface MetaRtmMessage : NSObject

/**
 Meta RTM message type. See MetaRtmMessageType. Text messages only.
 */
@property(nonatomic, assign, readonly) MetaRtmMessageType type;

/**
 Meta RTM message content. Must not exceed 32 KB in length.
 */
@property(nonatomic, copy, nonnull) NSString *text;

/**
 The timestamp (ms) of when the messaging server receives this message.

 **NOTE**

 - You can infer from the returned timestamp the *approximate* time as to when this message was
 sent.
 - The returned timestamp is on a millisecond time-scale. It is for demonstration purposes only, not
 for strict ordering of messages.
 */
@property(nonatomic, assign, readonly) long long serverReceivedTs;

/**
 Whether this message has been cached on the server (Applies to peer-to-peer message only).

 - YES: This message has been cached on the server (the server caches this message and resends it to
 the receiver when he/she is back online).
 - NO: (Default) This message has not been cached on the server.

 **NOTE**

 <li> This method returns NO if a message is not cached by the server. Only if the sender sends the
 message as an offline message (sets [enableOfflineMessaging]([MetaRtmSendMessageOptions
 enableOfflineMessaging]) as YES) when the specified user is offline, does the method return YES
 when the user is back online. <li> For now we only cache 200 offline messages for up to seven days
 for each message receiver. When the number of the cached messages reaches this limit, the newest
 message overrides the oldest one.
 */
@property(nonatomic, assign, readonly) BOOL isOfflineMessage;

/**
 Creates and initializes a text message to be sent.

 @param text A text message of less than 32 KB.

 @return An MetaRtmMessage instance.

 */
- (instancetype _Nonnull)initWithText:(NSString *_Nonnull)text;
@end

/**
 Attributes of a peer-to-peer or channel raw message. Inherited from MetaRtmMessage.
 */
__attribute__((visibility("default"))) @interface MetaRtmRawMessage : MetaRtmMessage

/**
 Meta RTM raw message content. Must not exceed 32 KB in length.
 */
@property(nonatomic, nonnull) NSData *rawData;

/**
 Creates and initializes a raw message to be sent.

 @param rawData A raw message of less than 32 KB.
 @param description A brief text description of the raw message. If you set a text description,
 ensure that the size of the raw message and the description combined does not exceed 32 KB.
 @return An MetaRtmMessage instance.
 */
- (instancetype _Nonnull)initWithRawData:(NSData *_Nonnull)rawData
                             description:(NSString *_Nonnull)description;
@end

/**
 The interface for setting and retrieving attributes of a file message. Inherited from
 MetaRtmMessage.
 */
__attribute__((visibility("default"))) @interface MetaRtmFileMessage : MetaRtmMessage

/**
 The size of the uploaded file in bytes.
 */
@property(nonatomic, assign, readonly) long long size;

/**
 The media ID of the uploaded file.

 - The media ID is automatically populated once the file is uploaded to the file server.
 - The media ID is valid for 7 days because the file server keeps all uploaded files for 7 days
 only.
 */
@property(nonatomic, nonnull, readonly) NSString *mediaId;

/**
 The thumbnail of the uploaded file.

 **NOTE**
 The size of `thumbnail` and `fileName` combined must not exceed 32 KB.
 */
@property(nonatomic, copy, nonnull) NSData *thumbnail;

/**
 The name of the uploaded file.

 **NOTE**
 The size of `thumbnail` and `fileName` combined must not exceed 32 KB.
 */
@property(nonatomic, copy, nonnull) NSString *fileName;
@end

/**
 The interface for setting and retrieving attributes of an image message. Inherited from
 MetaRtmMessage.
 */
__attribute__((visibility("default"))) @interface MetaRtmImageMessage : MetaRtmMessage

/**
 The size of the uploaded image in bytes.
 */
@property(nonatomic, assign, readonly) long long size;

/**
 The media ID of the uploaded image.

 **NOTE**

 - The media ID is automatically populated once the image is uploaded to the file server.
 - The media ID is valid for 7 days because the file server keeps all uploaded files for 7 days
 only.
 */
@property(nonatomic, nonnull, readonly) NSString *mediaId;

/**
 The thumbnail data of the uploaded image.

 **NOTE**
 The size of `thumbnail` and `fileName` combined must not exceed 32 KB.
 */
@property(nonatomic, copy, nonnull) NSData *thumbnail;

/**
 The file name of the uploaded image.

 **NOTE**
 The size of `thumbnail` and `fileName` combined must not exceed 32 KB.
 */
@property(nonatomic, copy, nonnull) NSString *fileName;

/**
 The height of the uploaded image.

 **NOTE**

 - If the uploaded image is in JPG, JPEG, BMP, or PNG format, the SDK automatically calculates the
 width and height of the image.
 - Image height that is set by the user overrides the height calculated by the SDK.
 - Is 0 if the SDK does not support the format of the uploaded image.
 */
@property(nonatomic, assign) int height;

/**
 The width of the uploaded image.

 **NOTE**

 - If the uploaded image is in JPG, JPEG, BMP, or PNG format, the SDK automatically calculates the
 width and height of the image.
 - Image width that is set by the user overrides the width calculated by the SDK.
 - Is 0 if the SDK does not support the format of the uploaded image.
 */
@property(nonatomic, assign) int width;

/**
 The height of the thumbnail.

 **NOTE**
 You need to work out the height of the thumbnail by yourself, because the SDK does not work out the
 value for you.
 */
@property(nonatomic, assign) int thumbnailHeight;

/**
 The width of the thumbnail.

 **NOTE**
 You need to work out the width of the thumbnail by yourself, because the SDK does not work out the
 value for you.
 */
@property(nonatomic, assign) int thumbnailWidth;
@end

/**
 Data structure indicating the online status of a user.
 */
__attribute__((visibility("default"))) @interface MetaRtmPeerOnlineStatus : NSObject

/**
 The user ID of the specified user.
 */
@property(nonatomic, copy, nonnull) NSString *peerId;

/**
 The online status of the peer. **DEPRECATED** as of v1.2.0. Use `state` instead.

 - YES: The user is online (the user has logged in the Meta RTM system).
 - NO: The user is offline (the user has logged out of the Meta RTM system, has not logged in, or
 has failed to logged in).
*/
@property(nonatomic, assign) BOOL isOnline;

/**
 The online state of the peer. See MetaRtmPeerOnlineState.

 **NOTE**

 - The server will never return the `unreachable` state, if you <i>query</i> the online status of
 specified peer(s) ([queryPeersOnlineStatus]([MetaRtmKit queryPeersOnlineStatus:completion:])). See
 also: [MetaRtmSubscriptionRequestBlock](MetaRtmSubscriptionRequestBlock).
 - The server may return the `unreachable` state, if you <i>subscribe to</i> the online status of
 specified peer(s) ([subscribePeersOnlineStatus]([MetaRtmKit
 subscribePeersOnlineStatus:completion:])). See also: [PeersOnlineStatusChanged]([MetaRtmDelegate
 rtmKit:PeersOnlineStatusChanged:]).
 */
@property(nonatomic, assign, readonly) MetaRtmPeerOnlineState state;
@end

/**
 Data structure indicating the member count of a channel.
 */
__attribute__((visibility("default"))) @interface MetaRtmChannelMemberCount : NSObject

/**
 The ID of the channel.
 */
@property(nonatomic, copy, nonnull) NSString *channelId;

/**
 The current member count of the channel.

 **NOTE** `count` is 0 if a channel with the specified `channelId` is not found.
 */
@property(nonatomic, assign) int count;
@end

/**
 An interface representing the upload progress or download progress.
 */
__attribute__((visibility("default"))) @interface MetaRtmMediaOperationProgress : NSObject

/**
 The total size of the file or image being loaded.
 */
@property(nonatomic, assign) long long totalSize;

/**
 The size of the loaded part of the file or image.
 */
@property(nonatomic, assign) long long currentSize;
@end

/**
 The MetaRtmChannelDelegate protocol enables Meta RTM channel callback event notifications to your
 app.
 */
@protocol MetaRtmChannelDelegate;

/**
 The MetaRtmCallDelegate protocol enables Meta RTM call callback event notifications to your app.
 */
@protocol MetaRtmCallDelegate;

/**
 The MetaRtmDelegate protocol enables Meta RTM callback event notifications to your app.
 */
@protocol MetaRtmDelegate <NSObject>
@optional

/**
 Occurs when the connection state between the SDK and the Meta RTM system changes.

 @param kit An [MetaRtmKit](MetaRtmKit) instance.
 @param state The new connection state. See MetaRtmConnectionState.
 @param reason The reason for the connection state change. See MetaRtmConnectionChangeReason.
 */
- (void)rtmKit:(MetaRtmKit *_Nonnull)kit
    connectionStateChanged:(MetaRtmConnectionState)state
                    reason:(MetaRtmConnectionChangeReason)reason;

/**
 Occurs when receiving a peer-to-peer message.

 @param kit An [MetaRtmKit](MetaRtmKit) instance.
 @param message The received message. Ensure that you check the `type` property when receiving the
 message instance: If the message type is `MetaRtmMessageTypeRaw`, you need to downcast the received
 instance from MetaRtmMessage to MetaRtmRawMessage. See MetaRtmMessageType.
 @param peerId The user ID of the sender.
 */
- (void)rtmKit:(MetaRtmKit *_Nonnull)kit
    messageReceived:(MetaRtmMessage *_Nonnull)message
           fromPeer:(NSString *_Nonnull)peerId;

/**
 Occurs when receiving a peer-to-peer file message.

 @param kit An [MetaRtmKit](MetaRtmKit) instance.
 @param message The received peer-to-peer file message. See MetaRtmFileMessage.
 @param peerId The ID of the message sender.
 */
- (void)rtmKit:(MetaRtmKit *_Nonnull)kit
    fileMessageReceived:(MetaRtmFileMessage *_Nonnull)message
               fromPeer:(NSString *_Nonnull)peerId;

/**
 Occurs when receiving a peer-to-peer image message.

 @param kit An [MetaRtmKit](MetaRtmKit) instance.
 @param message The received peer-to-peer image message. See MetaRtmImageMessage.
 @param peerId The ID of the message sender.
 */
- (void)rtmKit:(MetaRtmKit *_Nonnull)kit
    imageMessageReceived:(MetaRtmImageMessage *_Nonnull)message
                fromPeer:(NSString *_Nonnull)peerId;

/**
 Reports the progress of an ongoing upload task.

 **NOTE**

 - If the upload task is ongoing, the SDK returns this callback once every second.
 - If the upload task comes to a halt, the SDK stops returning this callback until the task is going
 again.

 @param kit An [MetaRtmKit](MetaRtmKit) instance.
 @param requestId The unique ID of the upload request.
 @param progress The progress of the ongoing upload task. See MetaRtmMediaOperationProgress.
 */
- (void)rtmKit:(MetaRtmKit *_Nonnull)kit
                media:(long long)requestId
    uploadingProgress:(MetaRtmMediaOperationProgress *_Nonnull)progress;

/**
 Reports the progress of an ongoing download task.

 **NOTE**

 - If the download task is ongoing, the SDK returns this callback once every second.
 - If the download task comes to a halt, the SDK stops returning this callback until the task is
 going again.

 @param kit An [MetaRtmKit](MetaRtmKit) instance.
 @param requestId The unique ID of the download request.
 @param progress The progress of the ongoing download task. See MetaRtmMediaOperationProgress.
 */
- (void)rtmKit:(MetaRtmKit *_Nonnull)kit
                  media:(long long)requestId
    downloadingProgress:(MetaRtmMediaOperationProgress *_Nonnull)progress;

/**
 Occurs when the online status of the peers, to whom you subscribe, changes.

 - When the subscription to the online status of specified peer(s) succeeds, the SDK returns this
 callback to report the online status of peers, to whom you subscribe.
 - When the online status of the peers, to whom you subscribe, changes, the SDK returns this
 callback to report whose online status has changed.
 - If the online status of the peers, to whom you subscribe, changes when the SDK is reconnecting to
 the server, the SDK returns this callback to report whose online status has changed when
 successfully reconnecting to the server.

 @param kit An [MetaRtmKit](MetaRtmKit) instance.
 @param onlineStatus An array of peers' online states. See MetaRtmPeerOnlineStatus.
 */
- (void)rtmKit:(MetaRtmKit *_Nonnull)kit
    PeersOnlineStatusChanged:(NSArray<MetaRtmPeerOnlineStatus *> *_Nonnull)onlineStatus;

/**
 Occurs when the RTM server detects that the RTM token has exceeded the 24-hour validity period and
 when the SDK is in the `MetaRtmConnectionStateReconnecting` state.

 - This callback occurs only when the SDK is reconnecting to the server. You will not receive this
 callback when the SDK is in the `MetaRtmConnectionStateConnected` state.
 - When receiving this callback, generate a new RTM Token on the server and call the
 [renewToken]([MetaRtmKit renewToken:completion:]) method to pass the new Token on to the server.

 @param kit An MetaRtmKit instance.
 */
- (void)rtmKitTokenDidExpire:(MetaRtmKit *_Nonnull)kit;
@end

/**
Log Filter types.
 */
typedef NS_ENUM(NSInteger, MetaRtmLogFilter) {

  /**
0: Do not output any log information.
   */
  MetaRtmLogFilterOff = 0,

  /**
0x000f: Output CRITICAL, ERROR, WARNING, and INFO level log information.
   */
  MetaRtmLogFilterInfo = 0x000f,

  /**
0x000e: Output CRITICAL, ERROR, and WARNING level log information.
   */
  MetaRtmLogFilterWarn = 0x000e,

  /**
0x000c: Output CRITICAL and ERROR level log information.
   */
  MetaRtmLogFilterError = 0x000c,

  /**
0x0008: Output CRITICAL level log information.
   */
  MetaRtmLogFilterCritical = 0x0008,

  /**
0x80f: RESERVED FOR FUTURE USE
   */
  MetaRtmLogFilterMask = 0x80f,
};

/**
 A data structure holding an RTM attribute and its value.
 */
__attribute__((visibility("default"))) @interface MetaRtmAttribute : NSObject

/**
 The attribute name. Must be visible characters and not exceed 32 Bytes in length.
 */
@property(nonatomic, copy, nonnull) NSString *key;

/**
 The attribute value. Must not exceed 8 KB in length.
 */
@property(nonatomic, copy, nonnull) NSString *value;

@end

/**
 A data structure holding an RTM channel attribute and its value.
 */
__attribute__((visibility("default"))) @interface MetaRtmChannelAttribute : NSObject

/**
 The key of channel attribute. Must be visible characters and not exceed 32 Bytes.
 */
@property(nonatomic, copy, nonnull) NSString *key;

/**
 The value of the channel attribute. Must not exceed 8 KB in length.
 */
@property(nonatomic, copy, nonnull) NSString *value;

/**
 The ID of the user who makes the latest update to the channel attribute.
 */
@property(nonatomic, copy, nonnull) NSString *lastUpdateUserId;

/**
 Timestamp of when the channel attribute was last updated in milliseconds.
 */
@property(nonatomic, assign, readonly) long long lastUpdateTs;
@end

/**
 Returns the result of the [setLocalUserAttributes]([MetaRtmKit setLocalUserAttributes:completion:])
 <p><li><i>errorCode:</i> See MetaRtmProcessAttributeErrorCode.
 */
typedef void (^MetaRtmSetLocalUserAttributesBlock)(MetaRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [addOrUpdateLocalUserAttributes]([MetaRtmKit
 addOrUpdateLocalUserAttributes:completion:]) method call. <p><li><i>errorCode:</i> See
 MetaRtmProcessAttributeErrorCode.
 */
typedef void (^MetaRtmAddOrUpdateLocalUserAttributesBlock)(
    MetaRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [deleteLocalUserAttributesByKeys]([MetaRtmKit
 deleteLocalUserAttributesByKeys:completion:]) method call. <p><li><i>errorCode:</i>
 MetaRtmProcessAttributeErrorCode.
 */
typedef void (^MetaRtmDeleteLocalUserAttributesBlock)(MetaRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [clearLocalUserAttributesWithCompletion]([MetaRtmKit
 clearLocalUserAttributesWithCompletion:]) method call. <p><li><i>errorCode:</i> See
 MetaRtmProcessAttributeErrorCode.
 */
typedef void (^MetaRtmClearLocalUserAttributesBlock)(MetaRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [getUserAttributes]([MetaRtmKit getUserAllAttributes:completion:]) or the
 [getUserAttributesByKeys]([MetaRtmKit getUserAttributes:ByKeys:completion:]) method call.
 <p><li><i>attributes:</i> An array of RtmAttibutes. See MetaRtmAttribute. <p><li><i>userId:</i> The
 User ID of the specified user. <p><li><i>errorCode:</i> See MetaRtmProcessAttributeErrorCode.
 */
typedef void (^MetaRtmGetUserAttributesBlock)(NSArray<MetaRtmAttribute *> *_Nullable attributes,
                                              NSString * _Nonnull userId,
                                              MetaRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [getChannelMemberCount]([MetaRtmKit getChannelMemberCount:completion:])
 method call. <p><li><i>channelMemberCounts:</i> An array of MetaRtmChannelMemberCount. See
 MetaRtmChannelMemberCount. <p><li><i>errorCode:</i> See MetaRtmChannelMemberCountErrorCode.
 */
typedef void (^MetaRtmChannelMemberCountBlock)(
                                               NSArray<MetaRtmChannelMemberCount *> * _Nullable channelMemberCounts,
    MetaRtmChannelMemberCountErrorCode errorCode);

/**
 Returns the result of the [setLocalUserAttributes]([MetaRtmKit
 setChannel:Attributes:Options:completion:]) <p><li><i>errorCode:</i> See
 MetaRtmProcessAttributeErrorCode.
 */
typedef void (^MetaRtmSetChannelAttributesBlock)(MetaRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [addOrUpdateChannelAttributes]([MetaRtmKit
 addOrUpdateChannel:Attributes:Options:completion:]) method call. <p><li><i>errorCode:</i> See
 MetaRtmProcessAttributeErrorCode.
 */
typedef void (^MetaRtmAddOrUpdateChannelAttributesBlock)(
    MetaRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [deleteChannelAttributesByKeys]([MetaRtmKit
 deleteChannel:AttributesByKeys:Options:completion:]) method call. <p><li><i>errorCode:</i>
 MetaRtmProcessAttributeErrorCode.
 */
typedef void (^MetaRtmDeleteChannelAttributesBlock)(MetaRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [clearChannelAttributesWithCompletion]([MetaRtmKit
 clearChannel:Options:AttributesWithCompletion:]) method call. <p><li><i>errorCode:</i> See
 MetaRtmProcessAttributeErrorCode.
 */
typedef void (^MetaRtmClearChannelAttributesBlock)(MetaRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [getChannelAttributes]([MetaRtmKit getChannelAllAttributes:completion:])
 or the [getChannelAttributesByKeys]([MetaRtmKit getChannelAttributes:ByKeys:completion:]) method
 call. <p><li><i>attributes:</i> An array of MetaRtmChannelAttibute. See MetaRtmChannelAttibute.
 <p><li><i>errorCode:</i> See MetaRtmProcessAttributeErrorCode.
 */
typedef void (^MetaRtmGetChannelAttributesBlock)(
    NSArray<MetaRtmChannelAttribute *> *_Nullable attributes,
    MetaRtmProcessAttributeErrorCode errorCode);

/**
 Message sending options.
 */
__attribute__((visibility("default"))) @interface MetaRtmSendMessageOptions : NSObject

/**
 Whether to set the message as an offline message.

 - YES: Set the message as an offline message.
 - NO: (default) Do not set the message as an offline message.

 **NOTE**

 This setting applies to the peer-to-peer message only, not to the channel message.
 */
@property(nonatomic, assign) BOOL enableOfflineMessaging;
/**
 <b>PRIVATE BETA</b> Whether to save the message to message history.

 - YES: Save the message to message history.
 - NO: (default) Do not save the message to message history.
 */
@property(nonatomic, assign) BOOL enableHistoricalMessaging;
@end

/**
 Channel attribute-specific options.
 */
__attribute__((visibility("default"))) @interface MetaRtmChannelAttributeOptions : NSObject

/**
 Indicates whether or not to notify all channel members of a channel attribute change.

 **NOTE**

 This flag is valid only within the current method call.

 - YES: Notify all channel members of a channel attribute change.
 - NO: (Default) Do not notify all channel members of a channel attribute change.
 */
@property(nonatomic, assign) BOOL enableNotificationToChannelMembers;
@end

/**
 The entry point of the Meta RTM system.
 */
__attribute__((visibility("default"))) @interface MetaRtmKit : NSObject

/**
 MetaRtmDelegate enables Meta RTM callback event notifications to your app.
 */
@property(atomic, weak, nullable) id<MetaRtmDelegate> metaRtmDelegate;

/**
 **DEPRECATED** The property for managing channels for the local user.
 */
@property(atomic, readonly, nullable)
    NSMutableDictionary<NSString *, MetaRtmChannel *> *channels __deprecated;

@property(atomic, strong, nullable) MetaRtmCallKit *rtmCallKit;

/**
 Creates and initializes an `MetaRtmKit` instance.

 The Meta RTM SDK supports creating multiple `MetaRtmKit` instances. All methods in the `MetaRtmKit`
 class, except the [destroyChannelWithId](destroyChannelWithId:) method, are executed
 asynchronously.

 @param appId The App ID issued to you from the Meta Console. Apply for a new App ID from Meta if it
 is missing from your kit.

 @param delegate MetaRtmDelegate invokes callbacks to be passed to the app on Meta RTM SDK runtime
 events.

 @return - An `MetaRtmKit` instance if this method call succeeds.
 - `nil` if this method call fails for the reason that the length of the `appId` is not 32
 characters.

 */
- (instancetype _Nullable)initWithAppId:(NSString *_Nonnull)appId
                               delegate:(id<MetaRtmDelegate> _Nullable)delegate;

/**
 Logs in the Meta RTM system.

 **NOTE**

 - If you log in with the same user ID from a different instance, you will be kicked out of your
 previous login and removed from previously joined channels.
 - The call frequency limit for this method is two queries per second.
 - Only after you successfully call this method and receives the `MetaRtmLoginErrorOk` error code,
 can you call the key RTM methods except:

  - [createChannelWithId]([MetaRtmKit createChannelWithId:delegate:])
  - [initWithText]([MetaRtmMessage initWithText:])
  - [getRtmCallKit]([MetaRtmKit getRtmCallKit])
  - [initWithCalleeId]([MetaRtmLocalInvitation initWithCalleeId:])

 After the app calls this method, the local user receives the
 [connectionStateChanged]([MetaRtmDelegate rtmKit:connectionStateChanged:reason:]) callback and
 switches to the `MetaRtmConnectionStateConnecting` state.

 - Success: The local user receives the [MetaRtmLoginBlock](MetaRtmLoginBlock) and
 [connectionStateChanged]([MetaRtmDelegate rtmKit:connectionStateChanged:reason:]) callbacks, and
 switches to the `MetaRtmConnectionStateConnected` state.
 - Failure: The local user receives the [MetaRtmLoginBlock](MetaRtmLoginBlock) and
 [connectionStateChanged]([MetaRtmDelegate rtmKit:connectionStateChanged:reason:]) callbacks, and
 switches to the `MetaRtmConnectionStateDisconnected` state.

 @param token A token generated by the app server and used to log in the Meta RTM system. `token` is
 used when dynamic authentication is enabled. Set `token` as `nil` at the integration and test
 stages.

 @param userId The user ID of the user logging in the Meta RTM system. The string length must be
 less than 64 bytes with the following character scope:

 - All lowercase English letters: a to z
 - All uppercase English letters: A to Z
 - All numeric characters: 0 to 9
 - The space character.
 - Punction characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
 ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ","

 **NOTE**

 A `userId` cannot be empty, nil, or "null".

 @param completionBlock [MetaRtmLoginBlock](MetaRtmLoginBlock) returns the result of this method
 call. See MetaRtmLoginErrorCode for the error codes.

 */
- (void)loginByToken:(NSString *_Nullable)token
                user:(NSString *_Nonnull)userId
          completion:(MetaRtmLoginBlock _Nullable)completionBlock;

/**
 Logs out of the Meta RTM system.

 - Success: The local user receives the [MetaRtmLogoutBlock](MetaRtmLogoutBlock) and
 [connectionStateChanged]([MetaRtmDelegate rtmKit:connectionStateChanged:reason:]) callbacks, and
 switches to the `MetaRtmConnectionStateDisConnected` state.
 - Failure: The local user receives the [MetaRtmLogoutBlock](MetaRtmLogoutBlock) callback.

 @param completionBlock [MetaRtmLogoutBlock](MetaRtmLogoutBlock) returns the result of this method
 call. See MetaRtmLogoutErrorCode for the error codes.
 */
- (void)logoutWithCompletion:(MetaRtmLogoutBlock _Nullable)completionBlock;

/**
 Renews the current RTM Token.

 You are required to renew your Token when receiving the [rtmKitTokenDidExpire]([MetaRtmDelegate
 rtmKitTokenDidExpire:]) callback, and the [MetaRtmRenewTokenBlock](MetaRtmRenewTokenBlock) callback
 returns the result of this method call. The call frequency limit for this method is two queries per
 second.

 @param token Your new RTM Token.
 @param completionBlock [MetaRtmRenewTokenBlock](MetaRtmRenewTokenBlock) returns the result of this
 method call.

 - *token:* Your new RTM Token.
 - *errorCode:* See MetaRtmRenewTokenErrorCode for the error codes.
*/
- (void)renewToken:(NSString *_Nonnull)token
        completion:(MetaRtmRenewTokenBlock _Nullable)completionBlock;

/**
 Sends a peer-to-peer message to a specified peer user.

 **DEPRECATED**

 We do not recommend using this method to send a peer-to-peer message. Use [sendMessage]([MetaRtmKit
 sendMessage:toPeer:sendMessageOptions:completion:]) instead.

 - Success:
    - The local user receives the [MetaRtmSendPeerMessageBlock](MetaRtmSendPeerMessageBlock)
 callback.
    - The specified remote user receives the [messageReceived]([MetaRtmDelegate
 rtmKit:messageReceived:fromPeer:]) callback.
 - Failure: The local user receives the [MetaRtmSendPeerMessageBlock](MetaRtmSendPeerMessageBlock)
 callback with an error. See MetaRtmSendPeerMessageErrorCode for the error codes.

 **NOTE**

 You can send messages, including peer-to-peer and channel messages, at a maximum speed of 60
 queries per second.

 @param message The message to be sent. For information about creating a message, see
 MetaRtmMessage.
 @param peerId The ID of the remote user.
 @param completionBlock [MetaRtmSendPeerMessageBlock](MetaRtmSendPeerMessageBlock) returns the
 result of this method call. See MetaRtmSendPeerMessageErrorCode for the error codes.
 */
- (void)sendMessage:(MetaRtmMessage *_Nonnull)message
             toPeer:(NSString *_Nonnull)peerId
         completion:(MetaRtmSendPeerMessageBlock _Nullable)completionBlock;

/**
 Downloads a file or image from the Meta server to the local memory by media ID.

 **NOTE**

 - This method applies to scenarios requiring quick access to the downloaded file or image.
 - The SDK releases the downloaded file or image immediately after returning the
 [MetaRtmDownloadMediaToMemoryBlock](MetaRtmDownloadMediaToMemoryBlock) callback.

 @param mediaId The media ID of the file or image on the Meta server.
 @param requestId The unique ID to identify one request.
 @param completionBlock [MetaRtmDownloadMediaToMemoryBlock](MetaRtmDownloadMediaToMemoryBlock)
 returns the result of this method call. See MetaRtmDownloadMediaErrorCode for the error codes.
 */
- (void)downloadMediaToMemory:(NSString *_Nonnull)mediaId
                  withRequest:(long long *_Nonnull)requestId
                   completion:(MetaRtmDownloadMediaToMemoryBlock _Nullable)completionBlock;

/**
 Downloads a file or image from the Meta server to a specified local directory by media ID.

 @param mediaId The media ID of the file or image on the Meta server.
 @param filePath The full path to the downloaded file or image. Must be in UTF-8.
 @param requestId The unique ID of this download request.
 @param completionBlock [MetaRtmDownloadMediaToFileBlock](MetaRtmDownloadMediaToFileBlock) returns
 the result of this method call. See MetaRtmDownloadMediaErrorCode for the error codes.
 */
- (void)downloadMedia:(NSString *_Nonnull)mediaId
               toFile:(NSString *_Nonnull)filePath
          withRequest:(long long * _Nonnull)requestId
           completion:(MetaRtmDownloadMediaToFileBlock _Nullable)completionBlock;

/**
 Gets an MetaRtmFileMessage instance by uploading a file to the Meta server.

 The SDK returns the result with the [MetaRtmUploadFileMediaBlock](MetaRtmUploadFileMediaBlock)
 callback. If success, this callback returns a corresponding MetaRtmMessage instance, and then you
 can downcast it to MetaRtmFileMessage according to its type.

 **NOTE**

 - If you have at hand the media ID of a file on the Meta server, you can call
 [createFileMessageByMediaId]([MetaRtmKit createFileMessageByMediaId:]) to create an
 MetaRtmFileMessage instance.
 - To cancel an ongoing upload task, call [cancelMediaUpload]([MetaRtmKit
 cancelMediaUpload:completion:]).

 @param filePath The full path to the local file to upload. Must be in UTF-8.
 @param requestId The unique ID of this upload request.
 @param completionBlock [MetaRtmUploadFileMediaBlock](MetaRtmUploadFileMediaBlock) returns the
 result of this method call. See MetaRtmUploadMediaErrorCode for the error codes.
 */
- (void)createFileMessageByUploading:(NSString *_Nonnull)filePath
                         withRequest:(long long * _Nonnull)requestId
                          completion:(MetaRtmUploadFileMediaBlock _Nullable)completionBlock;

/**
 Gets an MetaRtmImageMessage instance by uploading an image to the Meta server.

 The SDK returns the result by the [MetaRtmUploadImageMediaBlock](MetaRtmUploadImageMediaBlock)
 callback. If success, this callback returns a corresponding MetaRtmMessage instance, and then you
 can downcast it to MetaRtmImageMessage according to its type.

 - If the uploaded image is in JPEG, JPG, BMP, or PNG format, the SDK calculates the width and
 height of the image. You can get the calculated width and height from the received
 MetaRtmImageMessage instance.
 - Otherwise, you need to set the width and height of the uploaded image within the received
 MetaRtmImageMessage instance by yourself.

 **NOTE**

 - If you have at hand the media ID of an image on the Meta server, you can call
 [createImageMessageByMediaId]([MetaRtmKit createImageMessageByMediaId:]) to create an
 MetaRtmImageMessage instance.
 - To cancel an ongoing upload task, call [cancelMediaUpload]([MetaRtmKit
 cancelMediaUpload:completion:]).

 @param filePath The full path to the local image to upload. Must be in UTF-8.
 @param requestId The unique ID of the upload request.
 @param completionBlock [MetaRtmUploadImageMediaBlock](MetaRtmUploadImageMediaBlock) returns the
 result of this method call. See MetaRtmUploadMediaErrorCode for the error codes.
 */
- (void)createImageMessageByUploading:(NSString *_Nonnull)filePath
                          withRequest:(long long * _Nonnull)requestId
                           completion:(MetaRtmUploadImageMediaBlock _Nullable)completionBlock;

/**
 Cancels an ongoing file or image download task by request ID.

 **NOTE**
 You can only cancel an ongoing download task. After a download task completes, the corresponding
 request ID is no longer valid and hence you cannot cancel it.

 @param requestId The unique Id to identify one request
 @param completionBlock [MetaRtmCancelMediaBlock](MetaRtmCancelMediaBlock) returns the result of
 this method call. See MetaRtmCancelMediaErrorCode for the error codes.
 */
- (void)cancelMediaDownload:(long long)requestId
                 completion:(MetaRtmCancelMediaBlock _Nullable)completionBlock;

/**
 Cancels an ongoing file or image upload task by request ID.

 **NOTE**
 You can only cancel an ongoing upload task. After an upload task completes, you cannot cancel it
 and the corresponding request ID is no longer valid.

 @param requestId The unique ID of the upload request to cancel.
 @param completionBlock [MetaRtmCancelMediaBlock](MetaRtmCancelMediaBlock) returns the result of
 this method call. See MetaRtmCancelMediaErrorCode for the error codes.
 */
- (void)cancelMediaUpload:(long long)requestId
               completion:(MetaRtmCancelMediaBlock _Nullable)completionBlock;

/**
 Creates an MetaRtmFileMessage instance by media ID.

 - If you have at hand the media ID of a file on the Meta server, you can call this method to create
 an MetaRtmFileMessage instance.
 - If you do not have a media ID, then you must call [createFileMessageByUploading]([MetaRtmKit
 createFileMessageByUploading:withRequest:completion:]) to get a corresponding MetaRtmFileMessage
 instance by uploading a file to the Meta RTM server.

 @param mediaId The media ID of an uploaded file on the Meta server.
 @return An MetaRtmFileMessage instance.
 */
- (MetaRtmFileMessage *_Nullable)createFileMessageByMediaId:(NSString *_Nonnull)mediaId;

/**
 Creates an MetaRtmImageMessage instance by media ID.

 - If you have at hand the media ID of an image on the Meta server, you can call this method to
 create an MetaRtmImageMessage instance.
 - If you do not have a media ID, then you must call [createFileMessageByUploading]([MetaRtmKit
 createImageMessageByUploading:withRequest:completion:]) to get a corresponding MetaRtmImageMessage
 instance by uploading an image to the Meta RTM server.

 @param mediaId The media ID of an uploaded image on the Meta server.
 @return An MetaRtmImageMessage instance.
 */
- (MetaRtmImageMessage * _Nullable)createImageMessageByMediaId:(NSString *_Nonnull)mediaId;

/**
 Sends an (offline) peer-to-peer message to a specified peer user.

 This method allows you to send a message to a specified user when the user is offline. If you set a
 message as an offline message and the specified user is offline when you send it, the RTM server
 caches it. Please note that for now we only cache 200 offline messages for up to seven days for
 each receiver. When the number of the cached messages reaches this limit, the newest message
 overrides the oldest one.

 If you use this method to send off a <i>text</i> message that starts off with
 META_RTM_ENDCALL_PREFIX\_\<channelId\>\_\<your additional information\>, then this method is
 compatible with the endCall method of the legacy Meta Signaling SDK. Replace \<channelId\> with the
 channel ID from which you want to leave (end call), and replace \<your additional information\>
 with any additional information. Note that you must not put any "_" (underscore) in your additional
 information but you can set \<your additional information\> as empty "".

 - Success:
   - The local user receives the [MetaRtmSendPeerMessageBlock](MetaRtmSendPeerMessageBlock)
 callback.
   - The specified remote user receives the [messageReceived]([MetaRtmDelegate
 rtmKit:messageReceived:fromPeer:]) callback.
 - Failure: The local user receives the [MetaRtmSendPeerMessageBlock](MetaRtmSendPeerMessageBlock)
 callback with an error. See MetaRtmSendPeerMessageErrorCode for the error codes.

 **NOTE**

 You can send messages, including peer-to-peer and channel messages, at a maximum speed of 60
 queries per second.

 @param message The message to be sent. For information about creating a message, see
 MetaRtmMessage.
 @param peerId The user ID of the remote user. The string length must be less than 64 bytes with the
 following character scope:

 - The 26 lowercase English letters: a to z
 - The 26 uppercase English letters: A to Z
 - The 10 numbers: 0 to 9
 - Space
 - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]",
 "^", "_", " {", "}", "|", "~", ","

 **NOTE**

 A `peerId` cannot be empty, nil, or "null".

 @param options Options when sending the message to a peer. See MetaRtmSendMessageOptions.
 @param completionBlock [MetaRtmSendPeerMessageBlock](MetaRtmSendPeerMessageBlock) returns the
 result of this method call. See MetaRtmSendPeerMessageErrorCode for the error codes.
 */
- (void)sendMessage:(MetaRtmMessage *_Nonnull)message
                toPeer:(NSString *_Nonnull)peerId
    sendMessageOptions:(MetaRtmSendMessageOptions *_Nonnull)options
            completion:(MetaRtmSendPeerMessageBlock _Nullable)completionBlock;

/**
 Creates an Meta RTM channel.

 **NOTE**

 You can create multiple `MetaRtmChannel` instances in an `MetaRtmKit` instance. But you can only
 join a maximum of 20 channels at the same time. As a good practice, Agore recommends calling the
 [destroyChannelWithId]([MetaRtmKit destroyChannelWithId:]) method to release all resources of an
 RTM channel that you no longer use.

 @param channelId The unique channel name of the Meta RTM session. The string length must not exceed
 64 bytes with the following character scope:

 - All lowercase English letters: a to z
 - All uppercase English letters: A to Z
 - All numeric characters: 0 to 9
 - The space character.
 - Punction characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
 ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ","

 **NOTE**

 A `channelId` cannot be empty, nil, or "null".

 @param delegate [MetaRtmChannelDelegate](MetaRtmChannelDelegate) invokes callbacks to be passed to
 the app on Meta RTM SDK runtime events.

 @return - An [MetaRtmChannel](MetaRtmChannel) instance if this method call succeeds.
 - `nil` if this method call fails for reasons such as the `channelId` is invalid or a channel with
 the same `channelId` already exists.

*/
- (MetaRtmChannel *_Nullable)createChannelWithId:(NSString *_Nonnull)channelId
                                        delegate:(id<MetaRtmChannelDelegate> _Nullable)delegate;

/**
 Destroys a specified local [MetaRtmChannel](MetaRtmChannel) instance.

 **NOTE**

 Do not call this method in any of your callbacks.

 @param channelId The channel ID of the channel to be destroyed.
*/
- (BOOL)destroyChannelWithId:(NSString *_Nonnull)channelId;

/**
 Gets the MetaRtmCallKit instance.

 @return The MetaRtmCallKit instance.
 */
- (MetaRtmCallKit *_Nullable)getRtmCallKit;

/**
 Queries the online status of the specified user(s).

 - Online: The user has logged in the Meta RTM system.
 - Offline: The user has logged out of the Meta RTM system.

 @param peerIds User IDs of the specified users.
 @param completionBlock [MetaRtmQueryPeersOnlineBlock](MetaRtmQueryPeersOnlineBlock) returns the
 result of this method call.

 - *peerOnlineStatus:* A list of the specified users' online status. See MetaRtmPeerOnlineStatus.
 - *errorCode:* See MetaRtmQueryPeersOnlineBlock.
*/
- (void)queryPeersOnlineStatus:(NSArray<NSString *> *_Nonnull)peerIds
                    completion:(MetaRtmQueryPeersOnlineBlock _Nullable)completionBlock;

/**
 Substitutes the local user's attributes with new ones.

 For [setLocalUserAttributes]([MetaRtmKit setLocalUserAttributes:completion:]),
 [addOrUpdateLocalUserAttributes]([MetaRtmKit addOrUpdateLocalUserAttributes:completion:]),
 [deleteLocalUserAttributesByKeys]([MetaRtmKit deleteLocalUserAttributesByKeys:completion:]) and
 [clearLocalUserAttributes]([MetaRtmKit clearLocalUserAttributesWithCompletion:]) taken together:
 the limit is 10 queries every five seconds.

 @param attributes The new attributes. See MetaRtmAttribute.
 @param completionBlock [MetaRtmSetLocalUserAttributesBlock](MetaRtmSetLocalUserAttributesBlock)
 returns the result of this method call.
 */
- (void)setLocalUserAttributes:(NSArray<MetaRtmAttribute *> *_Nullable)attributes
                    completion:(MetaRtmSetLocalUserAttributesBlock _Nullable)completionBlock;

/**
 Adds or updates the local user's attribute(s).

 For [setLocalUserAttributes]([MetaRtmKit setLocalUserAttributes:completion:]),
 [addOrUpdateLocalUserAttributes]([MetaRtmKit addOrUpdateLocalUserAttributes:completion:]),
 [deleteLocalUserAttributesByKeys]([MetaRtmKit deleteLocalUserAttributesByKeys:completion:]) and
 [clearLocalUserAttributes]([MetaRtmKit clearLocalUserAttributesWithCompletion:]) taken together:
 the limit is 10 queries every five seconds.

 This method updates the local user's attribute(s) if it finds that the attribute(s) has/have the
 same key(s), or adds attribute(s) to the local user if it does not.

 @param attributes The attrubutes to be added or updated. See MetaRtmAttribute 。
 @param completionBlock
 [MetaRtmAddOrUpdateLocalUserAttributesBlock](MetaRtmAddOrUpdateLocalUserAttributesBlock) returns
 the result of this method call.
 */
- (void)addOrUpdateLocalUserAttributes:(NSArray<MetaRtmAttribute *> *_Nullable)attributes
                            completion:(MetaRtmAddOrUpdateLocalUserAttributesBlock _Nullable)
                                           completionBlock;

/**
 Deletes the local user's attributes using attribute keys.

 For [setLocalUserAttributes]([MetaRtmKit setLocalUserAttributes:completion:]),
 [addOrUpdateLocalUserAttributes]([MetaRtmKit addOrUpdateLocalUserAttributes:completion:]),
 [deleteLocalUserAttributesByKeys]([MetaRtmKit deleteLocalUserAttributesByKeys:completion:]) and
 [clearLocalUserAttributes]([MetaRtmKit clearLocalUserAttributesWithCompletion:]) taken together:
 the limit is 10 queries every five seconds.

 @param attributeKeys An array of the attribute keys to be deleted.
 @param completionBlock
 [MetaRtmDeleteLocalUserAttributesBlock](MetaRtmDeleteLocalUserAttributesBlock) returns the result
 of this method call.
 */
- (void)deleteLocalUserAttributesByKeys:(NSArray<NSString *> *_Nullable)attributeKeys
                             completion:
                                 (MetaRtmDeleteLocalUserAttributesBlock _Nullable)completionBlock;

/**
 Clears all attributes of the local user.

 For [setLocalUserAttributes]([MetaRtmKit setLocalUserAttributes:completion:]),
 [addOrUpdateLocalUserAttributes]([MetaRtmKit addOrUpdateLocalUserAttributes:completion:]),
 [deleteLocalUserAttributesByKeys]([MetaRtmKit deleteLocalUserAttributesByKeys:completion:]) and
 [clearLocalUserAttributes]([MetaRtmKit clearLocalUserAttributesWithCompletion:]) taken together:
 the limit is 10 queries every five seconds.

 @param completionBlock [MetaRtmClearLocalUserAttributesBlock](MetaRtmClearLocalUserAttributesBlock)
 returns the result of this method call.
 */
- (void)clearLocalUserAttributesWithCompletion:
    (MetaRtmClearLocalUserAttributesBlock _Nullable)completionBlock;

/**
 Gets all attributes of a specified user.

 For [getUserAttributes]([MetaRtmKit getUserAllAttributes:completion:]) and
 [getUserAttributesByKeys]([MetaRtmKit getUserAttributes:ByKeys:completion:]) taken together, the
 call frequency limit is 40 queries every five seconds.

 @param userId The user ID of the specified user.
 @param completionBlock [MetaRtmGetUserAttributesBlock](MetaRtmGetUserAttributesBlock) returns the
 result of this method call.
 */
- (void)getUserAllAttributes:(NSString *_Nonnull)userId
                  completion:(MetaRtmGetUserAttributesBlock _Nullable)completionBlock;

/**
 Gets the attributes of a specified user using attribute keys.

 For [getUserAttributes]([MetaRtmKit getUserAllAttributes:completion:]) and
 [getUserAttributesByKeys]([MetaRtmKit getUserAttributes:ByKeys:completion:]) taken together, the
 call frequency limit is 40 queries every five seconds.

 @param userId The user ID of the specified user.
 @param attributeKeys An array of the attribute keys.
 @param completionBlock [MetaRtmGetUserAttributesBlock](MetaRtmGetUserAttributesBlock) returns the
 result of this method call.
 */
- (void)getUserAttributes:(NSString * _Nonnull)userId
                   ByKeys:(NSArray<NSString *> *_Nullable)attributeKeys
               completion:(MetaRtmGetUserAttributesBlock _Nullable)completionBlock;

/**
 Gets the member count of specified channel(s).

 **NOTE**

 - The call frequency limit for this method is one query per second.
 - We do not support getting the member counts of more than 32 channels in one method call.
 - You do not have to join the specified channel(s) to call this method.

 @param channelIds An array of the specified channel ID(s).
 @param completionBlock [MetaRtmChannelMemberCountBlock](MetaRtmChannelMemberCountBlock) returns the
 result of this method call.
 */
- (void)getChannelMemberCount:(NSArray<NSString *> *_Nonnull)channelIds
                   completion:(MetaRtmChannelMemberCountBlock _Nullable)completionBlock;

/**
 Resets the attributes of a specified channel.

 - You do not have to join the specified channel to reset its attributes.
 - The attributes of a channel will be cleared if the channel remains empty (has no members) for a
 couple of minutes.
 - If more than one user can update the channel attributes, then Agore recommends calling
 [getChannelAttributes]([MetaRtmKit getChannelAllAttributes:completion:]) to update the cache before
 calling this method.
 - For [setChannelAttributes]([MetaRtmKit setChannel:Attributes:Options:completion:]),
 [addOrUpdateChannelAttributes]([MetaRtmKit addOrUpdateChannel:Attributes:Options:completion:]),
 [deleteChannelAttributesByKeys]([MetaRtmKit deleteChannel:AttributesByKeys:Options:completion:])
 and [clearChannelAttributes]([MetaRtmKit clearChannel:Options:AttributesWithCompletion:]) taken
 together: the limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param attributes An array of the attributes. See MetaRtmChannelAttribute.
 @param options Options for this attribute operation. See MetaRtmChannelAttributeOptions.
 @param completionBlock [MetaRtmSetLocalUserAttributesBlock](MetaRtmSetLocalUserAttributesBlock)
 returns the result of this method call.
 */
- (void)setChannel:(NSString *_Nonnull)channelId
        Attributes:(NSArray<MetaRtmChannelAttribute *> *_Nullable)attributes
           Options:(MetaRtmChannelAttributeOptions *_Nonnull)options
        completion:(MetaRtmSetChannelAttributesBlock _Nullable)completionBlock;

/**
 Adds or updates the attribute(s) of a specified channel.

 This method updates the specified channel's attribute(s) if it finds that the attribute(s) has/have
 the same key(s), or adds attribute(s) to the channel if it does not.

 - You do not have to join the specified channel to update its attributes.
 - The attributes of a channel will be cleared if the channel remains empty (has no members) for a
 couple of minutes.
 - If more than one user can update the channel attributes, then Agore recommends calling
 [getChannelAttributes]([MetaRtmKit getChannelAllAttributes:completion:]) to update the cache before
 calling this method.
 - For [setChannelAttributes]([MetaRtmKit setChannel:Attributes:Options:completion:]),
 [addOrUpdateChannelAttributes]([MetaRtmKit addOrUpdateChannel:Attributes:Options:completion:]),
 [deleteChannelAttributesByKeys]([MetaRtmKit deleteChannel:AttributesByKeys:Options:completion:])
 and [clearChannelAttributes]([MetaRtmKit clearChannel:Options:AttributesWithCompletion:]) taken
 together: the limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param attributes An array of the attributes. See MetaRtmChannelAttribute.
 @param options Options for this attribute operation. See MetaRtmChannelAttributeOptions.
 @param completionBlock
 [MetaRtmAddOrUpdateLocalUserAttributesBlock](MetaRtmAddOrUpdateLocalUserAttributesBlock) returns
 the result of this method call.
 */
- (void)addOrUpdateChannel:(NSString *_Nonnull)channelId
                Attributes:(NSArray<MetaRtmChannelAttribute *> *_Nullable)attributes
                   Options:(MetaRtmChannelAttributeOptions *_Nonnull)options
                completion:(MetaRtmAddOrUpdateChannelAttributesBlock _Nullable)completionBlock;

/**
 Deletes the attributes of a specified channel by attribute keys.

 - You do not have to join the specified channel to delete its attributes.
 - The attributes of a channel will be cleared if the channel remains empty (has no members) for a
 couple of minutes.
 - If more than one user can update the channel attributes, then Agore recommends calling
 [getChannelAttributes]([MetaRtmKit getChannelAllAttributes:completion:]) to update the cache before
 calling this method.
 - For [setChannelAttributes]([MetaRtmKit setChannel:Attributes:Options:completion:]),
 [addOrUpdateChannelAttributes]([MetaRtmKit addOrUpdateChannel:Attributes:Options:completion:]),
 [deleteChannelAttributesByKeys]([MetaRtmKit deleteChannel:AttributesByKeys:Options:completion:])
 and [clearChannelAttributes]([MetaRtmKit clearChannel:Options:AttributesWithCompletion:]) taken
 together: the limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param attributeKeys An array of the attribute keys.
 @param options Options for this attribute operation. See MetaRtmChannelAttributeOptions.
 @param completionBlock
 [MetaRtmDeleteLocalUserAttributesBlock](MetaRtmDeleteLocalUserAttributesBlock) returns the result
 of this method call.
 */
- (void)deleteChannel:(NSString *_Nonnull)channelId
     AttributesByKeys:(NSArray<NSString *> *_Nullable)attributeKeys
              Options:(MetaRtmChannelAttributeOptions *_Nonnull)options
           completion:(MetaRtmDeleteChannelAttributesBlock _Nullable)completionBlock;

/**
 Clears all attributes of a specified channel.

 - You do not have to join the specified channel to clear its attributes.
 - The attributes of a channel will be cleared if the channel remains empty (has no members) for a
 couple of minutes.
 - For [getChannelAttributes]([MetaRtmKit getChannelAllAttributes:completion:]) and
 [getChannelAttributesByKeys]([MetaRtmKit getChannelAttributes:ByKeys:completion:]) taken together,
 the call frequency limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param options Options for this attribute operation. See MetaRtmChannelAttributeOptions.
 @param completionBlock [MetaRtmClearLocalUserAttributesBlock](MetaRtmClearLocalUserAttributesBlock)
 returns the result of this method call.
 */
- (void)clearChannel:(NSString *_Nonnull)channelId
                     Options:(MetaRtmChannelAttributeOptions *_Nonnull)options
    AttributesWithCompletion:(MetaRtmClearChannelAttributesBlock _Nullable)completionBlock;

/**
 Gets all attributes of a specified channel.

 - You do not have to join the specified channel to get its attributes.
 - For [getChannelAttributes]([MetaRtmKit getChannelAllAttributes:completion:]) and
 [getChannelAttributesByKeys]([MetaRtmKit getChannelAttributes:ByKeys:completion:]) taken together,
 the call frequency limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param completionBlock [MetaRtmGetUserAttributesBlock](MetaRtmGetUserAttributesBlock) returns the
 result of this method call.
 */
- (void)getChannelAllAttributes:(NSString *_Nonnull)channelId
                     completion:(MetaRtmGetChannelAttributesBlock _Nullable)completionBlock;

/**
 Gets the attributes of a specified channel by attribute keys.

 - You do not have to join the specified channel to get its attributes.
 - For [getChannelAttributes]([MetaRtmKit getChannelAllAttributes:completion:]) and
 [getChannelAttributesByKeys]([MetaRtmKit getChannelAttributes:ByKeys:completion:]) taken together,
 the call frequency limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param attributeKeys An array of the attribute keys.
 @param completionBlock [MetaRtmGetUserAttributesBlock](MetaRtmGetUserAttributesBlock) returns the
 result of this method call.
 */
- (void)getChannelAttributes:(NSString *_Nonnull)channelId
                      ByKeys:(NSArray<NSString *> *_Nullable)attributeKeys
                  completion:(MetaRtmGetChannelAttributesBlock _Nullable)completionBlock;

/**
 Subscribes to the online status of the specified user(s).

 - When the method call succeeds, the SDK returns the [PeersOnlineStatusChanged]([MetaRtmDelegate
 rtmKit:PeersOnlineStatusChanged:]) callback to report the online status of peers, to whom you
 subscribe.
 - When the online status of the peers, to whom you subscribe, changes, the SDK returns the
 [PeersOnlineStatusChanged]([MetaRtmDelegate rtmKit:PeersOnlineStatusChanged:]) callback to report
 whose online status has changed.
 - If the online status of the peers, to whom you subscribe, changes when the SDK is reconnecting to
 the server, the SDK returns the [PeersOnlineStatusChanged]([MetaRtmDelegate
 rtmKit:PeersOnlineStatusChanged:]) callback to report whose online status has changed when
 successfully reconnecting to the server.

 **NOTE**

 - When you log out of the Meta RTM system, all the status that you subscribe to will be cleared. To
 keep the original subscription after you re-log in the system, you need to redo the whole
 subscription process.
 - When the SDK reconnects to the server from the state of being interupted, the SDK automatically
 subscribes to the peers and states before the interruption without human intervention.

 @param peerIds User IDs of the specified users.
 @param completionBlock [MetaRtmSubscriptionRequestBlock](MetaRtmSubscriptionRequestBlock) returns
 the result of this method call.
 */
- (void)subscribePeersOnlineStatus:(NSArray<NSString *> *_Nonnull)peerIds
                        completion:(MetaRtmSubscriptionRequestBlock _Nullable)completionBlock;

/**
 Unsubscribes from the online status of the specified user(s).

 @param peerIds User IDs of the specified users.
 @param completionBlock MetaRtmUnsubscriptionRequestBlock returns the result of this method call.
 */
- (void)unsubscribePeersOnlineStatus:(NSArray<NSString *> *_Nonnull)peerIds
                          completion:(MetaRtmSubscriptionRequestBlock _Nullable)completionBlock;

/**
 Gets a list of the peers, to whose specific status you have subscribed.

 @param option The status type, to which you have subscribed. See MetaRtmPeerSubscriptionOptions.
 @param completionBlock
 [MetaRtmQueryPeersBySubscriptionOptionBlock](MetaRtmQueryPeersBySubscriptionOptionBlock) returns
 the result of this method call.
 */
- (void)queryPeersBySubscriptionOption:(MetaRtmPeerSubscriptionOptions)option
                            completion:(MetaRtmQueryPeersBySubscriptionOptionBlock _Nullable)
                                           completionBlock;

/**
 Provides the technical preview functionalities or special customizations by configuring the SDK
 with JSON options.

 **NOTE**

 The JSON options are not public by default. Meta is working on making commonly used JSON options
 public in a standard way. Contact [support@meta.io](mailto:support@meta.io) for more information.

 @param parameters SDK options in the JSON format.
 @return
 - 0: Success.
 - &ne;0: Failure.
 */
- (int)setParameters:(NSString *_Nonnull)parameters;

/**
 Specifies the default path to the SDK log file.

 **NOTE**

 - Ensure that the directory holding the log file exists and is writable.
 - Ensure that you call this method immediately after calling the [initWithAppId]([MetaRtmKit
 initWithAppId:delegate:]) method, otherwise the output log may be incomplete.
 - The default log file location is as follows:
   - iOS: `App Sandbox/Library/caches/metartm.log`
   - macOS
    - Sandbox enabled: `App Sandbox/Library/Logs/metartm.log`, for example
 `/Users/<username>/Library/Containers/<App Bundle Identifier>/Data/Library/Logs/metartm.log`.
    - Sandbox disabled: `~/Library/Logs/metartm.log`.

 @param logFile The absolute file path to the log file. The string of the `logFile` is in UTF-8.
 @return - 0: Success.
 - &ne;0: Failure.
 */
- (int)setLogFile:(NSString *_Nonnull)logFile;

/**
 Sets the log file size in KB.

 The SDK has two log files, each with a default size of 512 KB. So, if you set fileSizeInBytes as
 1024 KB, the SDK outputs log files with a total maximum size of 2 MB.

 **NOTE**

 File size settings of less than 512 KB or greater than 10 MB will not take effect.

 @param fileSize The SDK log file size (KB).
 @return - 0: Success.
 - &ne;0: Failure.
 */
- (int)setLogFileSize:(int)fileSize;

/**
 Sets the output log level of the SDK.

 You can use one or a combination of the filters. The log level follows the sequence of OFF,
 CRITICAL, ERROR, WARNING, and INFO. Choose a level to see the logs preceding that level. If, for
 example, you set the log level to WARNING, you see the logs within levels CRITICAL, ERROR, and
 WARNING.

 @param filter The log filter level. See MetaRtmLogFilter.
 @return - 0: Success.
 - &ne;0: Failure.
 */
- (int)setLogFilters:(MetaRtmLogFilter)filter;

/**
 Gets the version of the Meta RTM SDK.

 @return The RTM SDK version.
 */
+ (NSString *_Nonnull)getSDKVersion;

@end

#pragma mark channel

/**
Error codes related to sending a channel message.
 */
typedef NS_ENUM(NSInteger, MetaRtmSendChannelMessageErrorCode) {

  /**
0: The server receives the channel message.
   */
  MetaRtmSendChannelMessageErrorOk = 0,

  /**
1: The user fails to send the channel message state.
   */
  MetaRtmSendChannelMessageErrorFailure = 1,

  /**
2: The SDK does not receive a response from the server in 10 seconds. The current timeout is set as
10 seconds. Possible reasons: The user is in the `MetaRtmConnectionStateAborted` or
`MetaRtmConnectionStateReconnecting` state.
   */
  MetaRtmSendChannelMessageErrorTimeout = 2,

  /**
3: The method call frequency exceeds the limit of 60 queries per second (channel and peer messages
taken together).
  */
  MetaRtmSendChannelMessageTooOften = 3,

  /**
4: The message is null or exceeds 32 KB in length.
   */
  MetaRtmSendChannelMessageInvalidMessage = 4,

  /**
101: The SDK is not initialized.
   */
  MetaRtmSendChannelMessageErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before sending out a channel message.
   */
  MetaRtmSendChannelMessageNotLoggedIn = 102,
};

/**
Error codes related to joining a channel.
 */
typedef NS_ENUM(NSInteger, MetaRtmJoinChannelErrorCode) {

  /**
0: The user joins the channel successfully.
   */
  MetaRtmJoinChannelErrorOk = 0,

  /**
1: The user fails to join the channel.
   */
  MetaRtmJoinChannelErrorFailure = 1,

  /**
2: **RESERVED FOR FUTURE USE**
   */
  MetaRtmJoinChannelErrorRejected = 2,

  /**
3: The user fails to join the channel because the argument is invalid.
   */
  MetaRtmJoinChannelErrorInvalidArgument = 3,

  /**
4: A timeout occurs when joining the channel. The current timeout is set as five seconds. Possible
reasons: The user is in the `MetaRtmConnectionStateAborted` or `MetaRtmConnectionStateReconnecting`
state.
   */
  MetaRtmJoinChannelErrorTimeout = 4,

  /**
5: The number of the RTM channels you are in exceeds the limit of 20.
   */
  MetaRtmJoinChannelErrorExceedLimit = 5,

  /**
6: The user is joining or has joined the channel.
   */
  MetaRtmJoinChannelErrorAlreadyJoined = 6,

  /**
7: The method call frequency exceeds the limit of 50 queries every three seconds.
   */
  MetaRtmJoinChannelErrorTooOften = 7,

  /**
8: The method call frequency exceeds the limit of 2 queries per 5 seconds for the same channel.
   */
  MetaRtmJoinSameChannelErrorTooOften = 8,

  /**
101: The SDK is not initialized.
   */
  MetaRtmJoinChannelErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before joining the channel.
   */
  MetaRtmJoinChannelErrorNotLoggedIn = 102,
};

/**
Error codes related to leaving a channel.
 */
typedef NS_ENUM(NSInteger, MetaRtmLeaveChannelErrorCode) {

  /**
0: The user leaves the channel successfully.
   */
  MetaRtmLeaveChannelErrorOk = 0,

  /**
1: The user fails to leave the channel.
   */
  MetaRtmLeaveChannelErrorFailure = 1,

  /**
2: **RESERVED FOR FUTURE USE**
   */
  MetaRtmLeaveChannelErrorRejected = 2,

  /**
3: The user is not in the channel.
   */
  MetaRtmLeaveChannelErrorNotInChannel = 3,

  /**
101: The SDK is not initialized.
   */
  MetaRtmLeaveChannelErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before leaving the channel.
   */
  MetaRtmLeaveChannelErrorNotLoggedIn = 102,
};

/**
Error codes related to retrieving a channel member list.
*/
typedef NS_ENUM(NSInteger, MetaRtmGetMembersErrorCode) {

  /**
0: The user retrieves a member list of the channel successfully.
   */
  MetaRtmGetMembersErrorOk = 0,

  /**
1: The user fails to retrieve a member list of the channel.
   */
  MetaRtmGetMembersErrorFailure = 1,

  /**
2: **RESERVED FOR FUTURE USE**
   */
  MetaRtmGetMembersErrorRejected = 2,

  /**
3: A timeout occurs when retreiving a member list of the channel. The current timeout is set as five
seconds. Possible reasons: The user is in the `MetaRtmConnectionStateAborted` or
`MetaRtmConnectionStateReconnecting` state.
   */
  MetaRtmGetMembersErrorTimeout = 3,

  /**
4: The method call frequency exceeds the limit of five queries every two seconds.
   */
  MetaRtmGetMembersErrorTooOften = 4,

  /**
5: The user is not in channel.
   */
  MetaRtmGetMembersErrorNotInChannel = 5,

  /**
101: The SDK is not initialized.
   */
  MetaRtmGetMembersErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([MetaRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([MetaRtmKit loginByToken:user:completion:]) does not succeed
before retrieving a member list.
   */
  MetaRtmGetMembersErrorNotLoggedIn = 102,
};

/**
Attributes of an Meta RTM channel member.
 */
__attribute__((visibility("default"))) @interface MetaRtmMember : NSObject

/**
The user ID of the member in the channel.
 */
@property(nonatomic, copy, nonnull) NSString *userId;

/**
The channel ID.
 */
@property(nonatomic, copy, nonnull) NSString *channelId;
@end

/**
 Returns the result of the [joinWithCompletion]([MetaRtmChannel joinWithCompletion:]) method call.
 <p><i>errorCode:</i> See MetaRtmJoinChannelErrorCode for the error codes.
 */
typedef void (^MetaRtmJoinChannelBlock)(MetaRtmJoinChannelErrorCode errorCode);

/**
 Returns the result of the [leaveWithCompletion]([MetaRtmChannel leaveWithCompletion:]) method call.
 <p><i>errorCode:</i> See MetaRtmLeaveChannelErrorCode for the error codes.
 */
typedef void (^MetaRtmLeaveChannelBlock)(MetaRtmLeaveChannelErrorCode errorCode);

/** Returns the result of the [sendMessage]([MetaRtmChannel sendMessage:completion:]) method call.
 * <p><i>errorCode:</i> See MetaRtmSendChannelMessageErrorCode for the error codes.
 */
typedef void (^MetaRtmSendChannelMessageBlock)(MetaRtmSendChannelMessageErrorCode errorCode);

/**
 Returns the result of the [getMembersWithCompletion]([MetaRtmChannel getMembersWithCompletion:])
 method call. <p><li><i>members:</i> The member list. See MetaRtmMember. <li><i>errorCode:</i> See
 MetaRtmGetMembersErrorCode for the error codes.
*/
typedef void (^MetaRtmGetMembersBlock)(NSArray<MetaRtmMember *> *_Nullable members,
                                       MetaRtmGetMembersErrorCode errorCode);

/**
 The MetaRtmChannelDelegate protocol enables callback event notifications to your app.

 The SDK uses delegate callbacks in the MetaRtmChannelDelegate protocol to report
 MetaRtmChannelDelegate runtime events to the app.
 */
@protocol MetaRtmChannelDelegate <NSObject>
@optional

/**
 Occurs when a user joins the channel.

 When a remote user calls the [joinWithCompletion]([MetaRtmChannel joinWithCompletion:]) method and
 successfully joins the channel, the local user receives this callback.

 **NOTE**

 This callback is disabled when the number of the channel members exceeds 512.

 @param channel The channel that the user joins. See MetaRtmChannel.
 @param member The user joining the channel. See MetaRtmMember.
 */
- (void)channel:(MetaRtmChannel *_Nonnull)channel memberJoined:(MetaRtmMember *_Nonnull)member;

/**
 Occurs when a channel member leaves the channel.

 When a remote channel member calls the [leaveWithCompletion]([MetaRtmChannel leaveWithCompletion:])
 method and successfully leaves the channel, the local user receives this callback.

 **NOTE**

 This callback is disabled when the number of the channel members exceeds 512.

 @param channel The channel that the user leaves. See MetaRtmChannel.
 @param member The channel member that leaves the channel. See MetaRtmMember.
 */
- (void)channel:(MetaRtmChannel *_Nonnull)channel memberLeft:(MetaRtmMember *_Nonnull)member;

/**
 Occurs when receiving a channel message.

 When a remote channel member calls the [sendMessage]([MetaRtmChannel sendMessage:completion:])
 method and successfully sends out a channel message, the local user receives this callback.

 @param channel The channel, to which the local user belongs. See MetaRtmChannel.
 @param message The received channel message. See MetaRtmMessage. Ensure that you check the `type`
 property when receiving the message instance: If the message type is `MetaRtmMessageTypeRaw`, you
 need to downcast the received instance from MetaRtmMessage to MetaRtmRawMessage. See
 MetaRtmMessageType.
 @param member The message sender. See MetaRtmMember.
 */
- (void)channel:(MetaRtmChannel *_Nonnull)channel
    messageReceived:(MetaRtmMessage *_Nonnull)message
         fromMember:(MetaRtmMember *_Nonnull)member;

/**
 Occurs when receiving a channel file message.

 @param channel The channel, to which the local user belongs. See MetaRtmChannel.
 @param message The received channel file message. See MetaRtmFileMessage".
 @param member The message sender. See MetaRtmMember.
 */
- (void)channel:(MetaRtmChannel *_Nonnull)channel
    fileMessageReceived:(MetaRtmFileMessage *_Nonnull)message
             fromMember:(MetaRtmMember *_Nonnull)member;

/**
 Occurs when receiving a channel image message.

 @param channel The channel, to which the local user belongs. See MetaRtmChannel.
 @param message The received channel image message. See MetaRtmImageMessage.
 @param member The message sender. See MetaRtmMember.
 */
- (void)channel:(MetaRtmChannel *_Nonnull)channel
    imageMessageReceived:(MetaRtmImageMessage *_Nonnull)message
              fromMember:(MetaRtmMember *_Nonnull)member;

/**
 Occurs when channel attributes are updated, and returns all attributes of the channel.

 **NOTE**

 This callback is enabled only when the user, who updates the attributes of the channel, sets
 [enableNotificationToChannelMembers]([MetaRtmChannelAttributeOptions
 enableNotificationToChannelMembers]) as YES. Also note that this flag is valid only within the
 current channel attribute method call.

 @param channel The channel, to which the local user belongs. See MetaRtmChannel.
 @param attributes An array of MetaRtmChannelAttribute. See MetaRtmChannelAttribute.
 */
- (void)channel:(MetaRtmChannel *_Nonnull)channel
    attributeUpdate:(NSArray<MetaRtmChannelAttribute *> *_Nonnull)attributes;

/**
 Occurs when the number of the channel members changes, and returns the new number.

 **NOTE**

 - When the number of channel members &le; 512, the SDK returns this callback when the number
 changes and at a MAXIMUM speed of once per second.
 - When the number of channel members exceeds 512, the SDK returns this callback when the number
 changes and at a MAXIMUM speed of once every three seconds.
 - You will receive this callback when successfully joining an RTM channel, so Agore recommends
 implementing this callback to receive timely updates on the number of the channel members.

 @param channel The channel, to which the local user belongs. See MetaRtmChannel.
 @param count Member count of this channel.
 */
- (void)channel:(MetaRtmChannel *_Nonnull)channel memberCount:(int)count;

@end

/**
 Meta RTM channel methods.
 */
__attribute__((visibility("default"))) @interface MetaRtmChannel : NSObject

/**
 An [MetaRtmKit](MetaRtmKit) instance.
 */
@property(atomic, readonly, nonnull) MetaRtmKit *kit;

/**
 MetaRtmChannelDelegate enables Meta RTM channel callback event notifications to your app.
 */
@property(nonatomic, weak, nullable) id<MetaRtmChannelDelegate> channelDelegate;

/**
 Joins a channel.

 **NOTE**

 You can join a maximum of 20 RTM channels at the same time. When the number of the channels you
join exceeds the limit, you receive the `MetaRtmJoinChannelErrorCodeExceedLimit` error code.

 - The [MetaRtmJoinChannelBlock](MetaRtmJoinChannelBlock) callback returns the result of this method
call.
 - When the local user successfully joins the channel, all remote users in the channel receive the
[memberJoined]([MetaRtmChannelDelegate channel:memberJoined:]) callback.

@param completionBlock [MetaRtmJoinChannelBlock](MetaRtmJoinChannelBlock) returns the result of this
method call. See MetaRtmJoinChannelErrorCode for the error codes.
 */
- (void)joinWithCompletion:(MetaRtmJoinChannelBlock _Nullable)completionBlock;

/**
 Leaves a channel.

 - The [MetaRtmLeaveChannelBlock](MetaRtmLeaveChannelBlock) callback returns the result of this
 method call.
 - When the local user successfully leaves the channel, all remote users in the channel receive the
 [memberLeft]([MetaRtmChannelDelegate channel:memberLeft:]) callback.

 @param completionBlock [MetaRtmLeaveChannelBlock](MetaRtmLeaveChannelBlock) returns the result of
 this method call. See MetaRtmLeaveChannelErrorCode for the error codes.
 */
- (void)leaveWithCompletion:(MetaRtmLeaveChannelBlock _Nullable)completionBlock;

/**
 **DEPRECATED** Allows a channel member to send a message to all members in the channel.

 Meta does not recommend using this method for sending a channel message. Use
 [sendMessage]([MetaRtmChannel sendMessage:sendMessageOptions:completion:]) instead.

 - The [MetaRtmSendChannelMessageBlock](MetaRtmSendChannelMessageBlock) callback returns the result
 of this method call.
 - When the message arrives, all remote members in the channel receive the
 [messageReceived]([MetaRtmChannelDelegate channel:messageReceived:fromMember:]) callback.

 **NOTE**

 You can send messages, including peer-to-peer and channel messages, at a maximum speed of 60
 queries per second.

 @param message The message to be sent. See [MetaRtmMessage](MetaRtmMessage).
 @param completionBlock [MetaRtmSendChannelMessageBlock](MetaRtmSendChannelMessageBlock) returns the
 result of this method call. See MetaRtmSendChannelMessageErrorCode for the error codes.
 */
- (void)sendMessage:(MetaRtmMessage *_Nonnull)message
         completion:(MetaRtmSendChannelMessageBlock _Nullable)completionBlock;

/**
 Allows a channel member to send a message to all members in the channel.

 - The [MetaRtmSendChannelMessageBlock](MetaRtmSendChannelMessageBlock) callback returns the result
 of this method call.
 - When the message arrives, all remote members in the channel receive the
 [messageReceived]([MetaRtmChannelDelegate channel:messageReceived:fromMember:]) callback.

 **NOTE**

 You can send messages, including peer-to-peer and channel messages, at a maximum speed of 60
 queries per second.

 @param message The message to be sent. See [MetaRtmMessage](MetaRtmMessage).
 @param options Options when sending a channel message. See MetaRtmSendMessageOptions.
 @param completionBlock [MetaRtmSendChannelMessageBlock](MetaRtmSendChannelMessageBlock) returns the
 result of this method call. See MetaRtmSendChannelMessageErrorCode for the error codes.
 */
- (void)sendMessage:(MetaRtmMessage *_Nonnull)message
    sendMessageOptions:(MetaRtmSendMessageOptions *_Nonnull)options
            completion:(MetaRtmSendChannelMessageBlock _Nullable)completionBlock;

/**
 Retrieves a member list of the channel.

 **NOTE**

 You can call this method at a maximum speed of five queries every two seconds.

 @param completionBlock [MetaRtmGetMembersBlock](MetaRtmGetMembersBlock) returns the result of this
 method call (the member list if success). See MetaRtmGetMembersErrorCode for the error codes.
 */
- (void)getMembersWithCompletion:(MetaRtmGetMembersBlock _Nullable)completionBlock;
@end
