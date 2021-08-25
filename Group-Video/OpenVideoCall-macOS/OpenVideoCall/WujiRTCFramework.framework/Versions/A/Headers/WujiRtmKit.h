//
//  WujiRtmKit.h
//  WujiRtmKit
//
//  Copyright (c) 2020 Wuji.io. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WujiRtmCallKit.h"

/**
 The `WujiRtmKit` class is the entry point of the Wuji RTM SDK.
 */
@class WujiRtmKit;
/**
 The WujiRtmMessage class provides Wuji RTM message methods that can be invoked by your app.
 */
@class WujiRtmMessage;

@class WujiRtmFileMessage;

@class WujiRtmImageMessage;
/**
 The WujiRtmChannel class provides Wuji RTM channel methods that can be invoked by your app.
 */
@class WujiRtmChannel;
/**
 The WujiRtmCallKit class provides Wuji RTM call methods that can be invoked by your app.
 */
@class WujiRtmCallKit;

/**
 WujiRtmPeerOnlineStatus provides the online status of a specified user.
 */
@class WujiRtmPeerOnlineStatus;

/**
 The prefix for ending a call. You can use it with the [sendMessage]([WujiRtmKit
 sendMessage:toPeer:sendMessageOptions:completion:]) method to be compatible with the endCall method
 of the legacy Wuji Signaling SDK.
 */
static NSString *const WujiRtmEndcallPrefix = @"WujiRTMLegacyEndcallCompatibleMessagePrefix";

/**
Message types.
 */
typedef NS_ENUM(NSInteger, WujiRtmMessageType) {

  /**
0: Undefined message type.
   */
  WujiRtmMessageTypeUndefined = 0,

  /**
1: A text message.
   */
  WujiRtmMessageTypeText = 1,

  /**
2: A raw message.
   */
  WujiRtmMessageTypeRaw = 2,

  /**
3: A file message. The size of a file message must be less than 32 KB.
   */
  WujiRtmMessageTypeFile = 3,

  /**
4: An image message. The size of an image message must be less than 32 KB.
   */
  WujiRtmMessageTypeImage = 4,
};

/**
Error codes related to sending a peer-to-peer message.
 */
typedef NS_ENUM(NSInteger, WujiRtmSendPeerMessageErrorCode) {

  /**
0: The specified user receives the peer-to-peer message.
   */
  WujiRtmSendPeerMessageErrorOk = 0,

  /**
1: The user fails to send the peer-to-peer message.
   */
  WujiRtmSendPeerMessageErrorFailure = 1,

  /**
2: A timeout occurs when sending the peer-to-peer message. The current timeout is set as 10 seconds.
Possible reasons: The user is in the `WujiRtmConnectionStateAborted` or
`WujiRtmConnectionStateReconnecting` state.
   */
  WujiRtmSendPeerMessageErrorTimeout = 2,

  /**
3: The user is offline and has not received the peer-to-peer message.
   */
  WujiRtmSendPeerMessageErrorPeerUnreachable = 3,

  /**
4: The specified user is offline and does not receive the peer-to-peer message, but the server has
cached the message and will send the message to the specified user when he/she is back online.
   */
  WujiRtmSendPeerMessageErrorCachedByServer = 4,

  /**
5: The method call frequency exceeds the limit of 60 queries per second (channel and peer messages
taken together).
   */
  WujiRtmSendPeerMessageErrorTooOften = 5,

  /**
6: The user ID is invalid.
   */
  WujiRtmSendPeerMessageErrorInvalidUserId = 6,

  /**
7: The message is null or exceeds 32 KB in length.
   */
  WujiRtmSendPeerMessageErrorInvalidMessage = 7,
  /**
8: The message receiver‘s SDK is of an earlier version and hence cannot recognize this message.
   */
  WujiRtmSendPeerMessageErrorImcompatibleMessage = 8,

  /**
101: The SDK is not initialized.
   */
  WujiRtmSendPeerMessageErrorNotInitialized = 101,

  /**
102: The sender does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before sending the peer-to-peer message.
   */
  WujiRtmSendPeerMessageErrorNotLoggedIn = 102,
};

/**
Connection states between the SDK and the Wuji RTM system.
 */
typedef NS_ENUM(NSInteger, WujiRtmConnectionState) {

  /**
  1: The initial state. The SDK is disconnected from the Wuji RTM system.
  <p>When the user calls the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method, the
  SDK starts to log in the Wuji RTM system, triggers the [connectionStateChanged]([WujiRtmDelegate
  rtmKit:connectionStateChanged:reason:]) callback, and switches to the
  `WujiRtmConnectionStateConnecting` state.
   */
  WujiRtmConnectionStateDisconnected = 1,

  /**
  2: The SDK is logging in the Wuji RTM system.
  <p><li>Success: The SDK triggers the [connectionStateChanged]([WujiRtmDelegate
  rtmKit:connectionStateChanged:reason:]) callback and switches to the
  `WujiRtmConnectionStateConnected` state. <li>Failure: The SDK triggers the
  [connectionStateChanged]([WujiRtmDelegate rtmKit:connectionStateChanged:reason:]) callback and
  switches to the `WujiRtmConnectionStateDisConnected` state.
  */
  WujiRtmConnectionStateConnecting = 2,

  /**
  3: The SDK has logged in the Wuji RTM system.
  <p><li>If the connection between the SDK and the Wuji RTM system is interrupted because of network
  issues, the SDK triggers the [connectionStateChanged]([WujiRtmDelegate
  rtmKit:connectionStateChanged:reason:]) callback and switches to the
  `WujiRtmConnectionStateReconnecting` state. <li>If the login is banned by the server because, for
  example, another instance logs in the Wuji RTM system with the same user ID, the SDK triggers the
  [connectionStateChanged]([WujiRtmDelegate rtmKit:connectionStateChanged:reason:]) callback and
  switches to the `WujiRtmConnectionStateAborted` state. <li>If the user calls the
  [logoutWithCompletion]([WujiRtmKit logoutWithCompletion:]) method to log out of the Wuji RTM
  system and receives `WujiRtmLogoutErrorOk`, the SDK triggers the
  [connectionStateChanged]([WujiRtmDelegate rtmKit:connectionStateChanged:reason:]) callback and
  switches to the `WujiRtmConnectionStateDisconnected` state.
  */
  WujiRtmConnectionStateConnected = 3,

  /**
  4: The connection state between the SDK and the Wuji RTM system is interrupted due to network
  issues, and the SDK keeps re-logging in the Wuji RTM system. <p><li>If the SDK successfully
  re-logs in the Wuji RTM system, it triggers the [connectionStateChanged]([WujiRtmDelegate
  rtmKit:connectionStateChanged:reason:]) callback and switches to the
  `WujiRtmConnectionStateConnected` state. The SDK automatically adds the user back to the
  channel(s) he or she was in when the connection was interrupted, and synchronizes the local user's
  attributes with the server. <li>If the SDK fails to re-log in the Wuji RTM system, the SDK stays
  in the `WujiRtmConnectionStateReconnecting` state and keeps re-logging in the system.
  */
  WujiRtmConnectionStateReconnecting = 4,

  /**
  5: The SDK gives up logging in the Wuji RTM system, mainly because another instance has logged in
  the Wuji RTM system with the same user ID. <p>You must call the [logoutWithCompletion]([WujiRtmKit
  logoutWithCompletion:]) method before calling the [loginByToken]([WujiRtmKit
  loginByToken:user:completion:]) method to log in the Wuji RTM system again.
  */
  WujiRtmConnectionStateAborted = 5,
};

/**
Reasons for a connection state change.
 */
typedef NS_ENUM(NSInteger, WujiRtmConnectionChangeReason) {

  /**
1: The SDK is logging in the Wuji RTM system.
   */
  WujiRtmConnectionChangeReasonLogin = 1,

  /**
2: The SDK has logged in the Wuji RTM system.
   */
  WujiRtmConnectionChangeReasonLoginSuccess = 2,

  /**
3: The SDK fails to log in the Wuji RTM system.
   */
  WujiRtmConnectionChangeReasonLoginFailure = 3,

  /**
4: The login has timed out for 10 seconds, and the SDK stops logging in.
   */
  WujiRtmConnectionChangeReasonLoginTimeout = 4,

  /**
5: The connection between the SDK and the Wuji RTM system is interrupted for more than four seconds.
   */
  WujiRtmConnectionChangeReasonInterrupted = 5,

  /**
6: The user has called the [logoutWithCompletion]([WujiRtmKit logoutWithCompletion:]) method to log
out of the Wuji RTM system.
   */
  WujiRtmConnectionChangeReasonLogout = 6,

  /**
7: Login is banned by the Wuji RTM server.
   */
  WujiRtmConnectionChangeReasonBannedByServer = 7,

  /**
8: Another instance has logged in the Wuji RTM system with the same user ID.
   */
  WujiRtmConnectionChangeReasonRemoteLogin = 8,
};

/**
Error codes related to login.
 */
typedef NS_ENUM(NSInteger, WujiRtmLoginErrorCode) {

  /**
0: Login succeeds. No error occurs.
   */
  WujiRtmLoginErrorOk = 0,

  /**
1: Login fails for reasons unknown.
   */
  WujiRtmLoginErrorUnknown = 1,

  /**
2: Login is rejected by the server.
   */
  WujiRtmLoginErrorRejected = 2,

  /**
3: Invalid login arguments.
   */
  WujiRtmLoginErrorInvalidArgument = 3,

  /**
4: The App ID is invalid.
   */
  WujiRtmLoginErrorInvalidAppId = 4,

  /**
5: The token is invalid.
   */
  WujiRtmLoginErrorInvalidToken = 5,

  /**
6: The token has expired, and hence login is rejected.
   */
  WujiRtmLoginErrorTokenExpired = 6,

  /**
7: Unauthorized login.
   */
  WujiRtmLoginErrorNotAuthorized = 7,

  /**
8: The user has already logged in or is logging in the Wuji RTM system, or the user has not called
the [logoutWithCompletion]([WujiRtmKit logoutWithCompletion:]) method to leave the
`WujiRtmConnectionStateAborted` state.
   */
  WujiRtmLoginErrorAlreadyLogin = 8,

  /**
9: The login times out. The current timeout is set as six seconds.
   */
  WujiRtmLoginErrorTimeout = 9,

  /**
10: The call frequency of the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method
exceeds the limit of two queries per second.
   */
  WujiRtmLoginErrorLoginTooOften = 10,

  /**
101: The SDK is not initialized.
   */
  WujiRtmLoginErrorLoginNotInitialized = 101,
};

/**
Error codes related to logout.
 */
typedef NS_ENUM(NSInteger, WujiRtmLogoutErrorCode) {

  /**
0: Logout succeeds. No error occurs.
   */
  WujiRtmLogoutErrorOk = 0,

  /**
1: **RESERVED FOR FUTURE USE**
   */
  WujiRtmLogoutErrorRejected = 1,

  /**
101: The SDK is not initialized.
   */
  WujiRtmLogoutErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before the user logs out of the Wuji RTM system.
   */
  WujiRtmLogoutErrorNotLoggedIn = 102,
};

/**
Error codes related to querying the online status of the specified peer(s).
 */
typedef NS_ENUM(NSInteger, WujiRtmQueryPeersOnlineErrorCode) {

  /**
0: The method call succeeds.
   */
  WujiRtmQueryPeersOnlineErrorOk = 0,

  /**
1: The method call fails.
   */
  WujiRtmQueryPeersOnlineErrorFailure = 1,

  /**
2: The method call fails. The argument is invalid.
   */
  WujiRtmQueryPeersOnlineErrorInvalidArgument = 2,

  /**
3: **RESERVED FOR FUTURE USE**
   */
  WujiRtmQueryPeersOnlineErrorRejected = 3,

  /**
4: The SDK has not received a response from the server for 10 seconds. The current timeout is set as
10 seconds. Possible reasons: The user is in the `WujiRtmConnectionStateAborted` or
`WujiRtmConnectionStateReconnecting` state.
   */
  WujiRtmQueryPeersOnlineErrorTimeout = 4,

  /**
5: The method call frequency of this method exceeds the limit of 10 queries every five seconds.
   */
  WujiRtmQueryPeersOnlineErrorTooOften = 5,

  /**
101: The SDK is not initialized.
   */
  WujiRtmQueryPeersOnlineErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before querying the online status.
   */
  WujiRtmQueryPeersOnlineErrorNotLoggedIn = 102,
};

/**
Error codes related to attrubute operations.
 */
typedef NS_ENUM(NSInteger, WujiRtmProcessAttributeErrorCode) {

  /**
0: The attribute operation succeeds.
   */
  WujiRtmAttributeOperationErrorOk = 0,

  /**
1: **DEPRECATED**
   */
  WujiRtmAttributeOperationErrorNotReady = 1,

  /**
2: The attribute operation fails.
   */
  WujiRtmAttributeOperationErrorFailure = 2,

  /**
3: The argument you put for this attribute operation is invalid.
   */
  WujiRtmAttributeOperationErrorInvalidArgument = 3,

  /**
4: The attribute size exceeds the limit. <p><li> For user attribute operations: The user's overall
attribute size would exceed the limit of 16 KB, one of the user's attributes would exceeds 8 KB in
size, or the number of this user's attributes would exceed 32 after this attribute operation.<li>
For channel attribute operations: The channel's overall attribute size would exceed the limit of 32
KB, one of the channel attributes would exceed 8 KB in size, or the number of this channel's
attributes would exceed 32 after this attribute operation.
   */
  WujiRtmAttributeOperationErrorSizeOverflow = 4,

  /**
5: The method call frequency exceeds the limit.<p><li>For [setLocalUserAttributes]([WujiRtmKit
setLocalUserAttributes:completion:]), [addOrUpdateLocalUserAttributes]([WujiRtmKit
addOrUpdateLocalUserAttributes:completion:]), [deleteLocalUserAttributesByKeys]([WujiRtmKit
deleteLocalUserAttributesByKeys:completion:]) and [clearLocalUserAttributes]([WujiRtmKit
clearLocalUserAttributesWithCompletion:]) taken together: the limit is 10 queries every five
seconds.<li>For [getUserAttributes]([WujiRtmKit getUserAllAttributes:completion:]) and
[getUserAttributesByKeys]([WujiRtmKit getUserAttributes:ByKeys:completion:]) taken together, the
limit is 40 queries every five seconds.<li>For [setChannelAttributes]([WujiRtmKit
setChannel:Attributes:Options:completion:]), [addOrUpdateChannelAttributes]([WujiRtmKit
addOrUpdateChannel:Attributes:Options:completion:]), [deleteChannelAttributesByKeys]([WujiRtmKit
deleteChannel:AttributesByKeys:Options:completion:]) and [clearChannelAttributes]([WujiRtmKit
clearChannel:Options:AttributesWithCompletion:]) taken together: the limit is 10 queries every five
seconds.<li>For [getChannelAllAttributes]([WujiRtmKit getChannelAllAttributes:completion:]) and
[getChannelAttributesByKeys]([WujiRtmKit getChannelAttributes:ByKeys:completion:]) taken together,
the limit is 10 queries every five seconds.
   */
  WujiRtmAttributeOperationErrorTooOften = 5,

  /**
6: The specified user is not found, either because the user is offline or because the user does not
exist.
   */
  WujiRtmAttributeOperationErrorUserNotFound = 6,

  /**
7: A timeout occurs in the attribute-related operation. The current timeout is set as five seconds.
Possible reasons: The user is in the `WujiRtmConnectionStateAborted` or
`WujiRtmConnectionStateReconnecting` state.
   */
  WujiRtmAttributeOperationErrorTimeout = 7,

  /**
101: The SDK is not initialized.
   */
  WujiRtmAttributeOperationErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before the attribute operation.
   */
  WujiRtmAttributeOperationErrorNotLoggedIn = 102,
};

/**
Error codes related to renewing the token.
 */
typedef NS_ENUM(NSInteger, WujiRtmRenewTokenErrorCode) {

  /**
0: The token-renewing operation succeeds.
   */
  WujiRtmRenewTokenErrorOk = 0,

  /**
1: Common unknown failure.
   */
  WujiRtmRenewTokenErrorFailure = 1,

  /**
2: The method call fails. The argument is invalid.
   */
  WujiRtmRenewTokenErrorInvalidArgument = 2,

  /**
3: **RESERVED FOR FUTURE USE**
   */
  WujiRtmRenewTokenErrorRejected = 3,

  /**
4: The method call frequency of exceeds the limit of two queries per second.
   */
  WujiRtmRenewTokenErrorTooOften = 4,

  /**
5: The token has expired.
   */
  WujiRtmRenewTokenErrorTokenExpired = 5,

  /**
6: The token is invalid.
   */
  WujiRtmRenewTokenErrorInvalidToken = 6,

  /**
101: The SDK is not initialized.
   */
  WujiRtmRenewTokenErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before renewing the token.
   */
  WujiRtmRenewTokenErrorNotLoggedIn = 102,
};

/**
Error codes related to retrieving the channel member count of specified channel(s).
 */
typedef NS_ENUM(NSInteger, WujiRtmChannelMemberCountErrorCode) {

  /**
0: The operation succeeds.
   */
  WujiRtmChannelMemberCountErrorOk = 0,

  /**
1: Unknown common failure.
   */
  WujiRtmChannelMemberCountErrorFailure = 1,

  /**
2: One or several of your channel IDs is invalid.
   */
  WujiRtmChannelMemberCountErrorInvalidArgument = 2,

  /**
3: The method call frequency exceeds the limit of one query per second.
   */
  WujiRtmChannelMemberCountErrorTooOften = 3,

  /**
4: A timeout occurs during this operation. The current timeout is set as five seconds.
   */
  WujiRtmChannelMemberCountErrorTimeout = 4,

  /**
5: The number of the channels that you query is greater than 32.
   */
  WujiRtmChannelMemberCountErrorExceedLimit = 5,

  /**
101: The SDK is not initialized.
   */
  WujiRtmChannelMemberCountErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  WujiRtmChannelMemberCountErrorNotLoggedIn = 102,
};

/**
Error codes related to subscribing to or unsubscribing from the status of specified peer(s).
 */
typedef NS_ENUM(NSInteger, WujiRtmPeerSubscriptionStatusErrorCode) {

  /**
0: The method call succeeds, or the operation succeeds.
   */
  WujiRtmPeerSubscriptionStatusErrorOk = 0,

  /**
1: Common failure. The user fails to subscribe to or unsubscribe from the status of the specified
peer(s).
   */
  WujiRtmPeerSubscriptionStatusErrorFailure = 1,

  /**
2: The method call fails. The argument is invalid.
   */
  WujiRtmPeerSubscriptionStatusErrorInvalidArgument = 2,

  /**
3: **RESERVED FOR FUTURE USE**
   */
  WujiRtmPeerSubscriptionStatusErrorRejected = 3,

  /**
4: The SDK fails to receive a response from the server in 10 seconds. The current timeout is set as
10 seconds. Possible reasons: The user is in the \ref wuji::rtm::CONNECTION_STATE_ABORTED
"CONNECTION_STATE_ABORTED" or \ref wuji::rtm::CONNECTION_STATE_RECONNECTING
"CONNECTION_STATE_RECONNECTING" state.
   */
  WujiRtmPeerSubscriptionStatusErrorTimeout = 4,

  /**
5: The method call frequency exceeds the limit of 10 subscribes every five seconds.
   */
  WujiRtmPeerSubscriptionStatusErrorTooOften = 5,

  /**
6: The number of peers, to whom you subscribe, exceeds the limit of 512.
   */
  WujiRtmPeerSubscriptionStatusErrorOverflow = 6,

  /**
101: The SDK is not initialized.
   */
  WujiRtmPeerSubscriptionStatusErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  WujiRtmPeerSubscriptionStatusErrorNotLoggedIn = 102,
};

/**
Error codes related to getting a list of the peer(s) by suscription option type.
 */
typedef NS_ENUM(NSInteger, WujiRtmQueryPeersBySubscriptionOptionErrorCode) {

  /**
0: The method call succeeds, or the operation succeeds.
   */
  WujiRtmQueryPeersBySubscriptionOptionErrorOk = 0,

  /**
1: Common failure. The user fails to query peer(s) by subscription option type.
   */
  WujiRtmQueryPeersBySubscriptionOptionErrorFailure = 1,

  /**
2: The SDK fails to receive a response from the server in 5 seconds. The current timeout is set as 5
seconds. Possible reasons: The user is in the `WujiRtmConnectionStateAborted` or
`WujiRtmConnectionStateReconnecting` state.
   */
  WujiRtmQueryPeersBySubscriptionOptionErrorTimeout = 2,

  /**
3: The method call frequency exceeds the limit of 10 subscribes every five seconds.
   */
  WujiRtmQueryPeersBySubscriptionOptionErrorTooOften = 3,

  /**
101: The SDK is not initialized.
   */
  WujiRtmQueryPeersBySubscriptionOptionErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  WujiRtmQueryPeersBySubscriptionOptionErrorNotLoggedIn = 102,
};

/**
Error codes related to downloading a file or image.
 */
typedef NS_ENUM(NSInteger, WujiRtmDownloadMediaErrorCode) {

  /**
0: The method call succeeds, or the operation succeeds.
   */
  WujiRtmDownloadMediaErrorOk = 0,

  /**
1: Unknown common failure.
   */
  WujiRtmDownloadMediaErrorFailure = 1,

  /**
2: An argument you put is invalid. For example, `mediaId` is in the wrong format or `filePath` is
set as `null`.
   */
  WujiRtmDownloadMediaErrorInvalidArgument = 2,

  /**
3: A timeout occurs. The current timeout is set as 120 seconds. The SDK assumes that a timeout
occurs if it has not detected any file transmission between the SDK and the file server for 120
seconds.
   */
  WujiRtmDownloadMediaErrorTimeout = 3,
  /**
4: The file or image to download does not exist, either because the media ID you input is incorrect
or because the validity of the media ID has expired.
   */
  WujiRtmDownloadMediaErrorNotExist = 4,
  /**
5: You have exceeded the upper limit for file download. You can initiate a maximum of nine file
download or upload tasks at the same time (download and upload tasks count together).
   */
  WujiRtmDownloadMediaErrorConcurrencyLimitExceeded = 5,
  /**
6: The file or image download task is aborted for either of the following reasons:<p><li>The
receiver is in the `WujiRtmConnectionStateAborted` state.</li><li>The receiver has cancelled the
download task.</li></p>
   */
  WujiRtmDownloadMediaErrorInterrupted = 6,

  /**
101: The SDK is not initialized.
   */
  WujiRtmDownloadMediaErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  WujiRtmDownloadMediaErrorNotLoggedIn = 102,
};

/**
Error codes related to uploading a file or image.
 */
typedef NS_ENUM(NSInteger, WujiRtmUploadMediaErrorCode) {

  /**
0: The method call succeeds, or the operation succeeds.
   */
  WujiRtmUploadMediaErrorOk = 0,

  /**
1: Unknown common failure.
   */
  WujiRtmUploadMediaErrorFailure = 1,

  /**
2: The argument you put is invalid.
   */
  WujiRtmUploadMediaErrorInvalidArgument = 2,

  /**
3: A timeout occurs. The current timeout is set as 120 seconds. The SDK assumes that a timeout
occurs if it has not detected any file transmission between the SDK and the file server for 120
seconds.
   */
  WujiRtmUploadMediaErrorTimeout = 3,
  /**
4: The size of the file or image to upload exceeds 30 MB.
   */
  WujiRtmUploadMediaErrorSizeOverflow = 4,
  /**
5: You have exceeded the upper limit for file upload. You can initiate a maximum of nine file upload
or download tasks at the same time (upload and download tasks count together).
   */
  WujiRtmUploadMediaErrorConcurrencyLimitExceeded = 5,
  /**
6: The file or image upload task is aborted for either of the following reasons:<p><li>The user in
the `WujiRtmConnectionStateAborted` state. </li><li>The user has cancelled the upload task.</li></p>
   */
  WujiRtmUploadMediaErrorInterrupted = 6,

  /**
101: The SDK is not initialized.
   */
  WujiRtmUploadMediaErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  WujiRtmUploadMediaErrorNotLoggedIn = 102,
};

/**
Error codes related to cancelling a download task or cancelling an upload task.
 */
typedef NS_ENUM(NSInteger, WujiRtmCancelMediaErrorCode) {

  /**
0: The method call succeeds, or the operation succeeds.
   */
  WujiRtmCancelMediaErrorOk = 0,

  /**
1: Unknown common failure.
   */
  WujiRtmCancelMediaErrorFailure = 1,

  /**
2: The task to cancel does not exist. You can only cancel an ongoing download or upload task. If the
download or upload task completes, the corresponding `requestId` is no longer valid.
   */
  WujiRtmCancelMediaErrorNotExist = 2,

  /**
101: The SDK is not initialized.
   */
  WujiRtmCancelMediaErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before this operation.
   */
  WujiRtmCancelMediaErrorNotLoggedIn = 102,
};

/**
The online states of a peer.
 */
typedef NS_ENUM(NSInteger, WujiRtmPeerOnlineState) {
  /**
0: The peer is online.
   */
  WujiRtmPeerOnlineStateOnline = 0,
  /**
1: The peer is temporarily unreachable (the server has not received a packet from the SDK for more
than six seconds).
   */
  WujiRtmPeerOnlineStateUnreachable = 1,
  /**
2: The peer is offline (the sdk has not logged in the Wuji RTM system, or it has logged out of the
system, or the server has not received a packet from the SDK for more than 30 seconds).
   */
  WujiRtmPeerOnlineStateOffline = 2,
};

/**
Subscription types.
 */
typedef NS_ENUM(NSInteger, WujiRtmPeerSubscriptionOptions) {
  /**
0: Takes out a subscription to the online status of specified user(s).
   */
  WujiRtmPeerSubscriptionOnlineStatus = 0,
};

/**
 Returns the result of the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method call.
 <p><i>errorCode:<i> Login error code. See WujiRtmLoginErrorCode.
 */
typedef void (^WujiRtmLoginBlock)(WujiRtmLoginErrorCode errorCode);

/**
 Indicates the results of calling the [logoutWithCompletion]([WujiRtmKit logoutWithCompletion:])
 method call. <p><i>errorCode:<i> Logout error code. See WujiRtmLogoutErrorCode.
 */
typedef void (^WujiRtmLogoutBlock)(WujiRtmLogoutErrorCode errorCode);

/**
 Returns the result of the [sendMessage]([WujiRtmKit sendMessage:toPeer:completion:]) method call.
 <p><i>errorCode:<i> Error code of sending the peer-to-peer message. See
 WujiRtmSendPeerMessageErrorCode.
 */
typedef void (^WujiRtmSendPeerMessageBlock)(WujiRtmSendPeerMessageErrorCode errorCode);

/**
 Returns the result of the [queryPeersOnlineStatus]([WujiRtmKit queryPeersOnlineStatus:completion:])
 method call. <p><li><i>peerOnlineStatus:</i> A list of the specified users' online status. See
 WujiRtmPeerOnlineStatus. <li><i>errorCode:</i> See WujiRtmQueryPeersOnlineErrorCode.
 */
typedef void (^WujiRtmQueryPeersOnlineBlock)(NSArray<WujiRtmPeerOnlineStatus *> *peerOnlineStatus,
                                             WujiRtmQueryPeersOnlineErrorCode errorCode);

/**
 Returns the result of the [renewToken]([WujiRtmKit renewToken:completion:]) method call.
 <p><li><i>token</i> Your new Token. <li><i>errorCode:</i> See WujiRtmRenewTokenErrorCode.
 */
typedef void (^WujiRtmRenewTokenBlock)(NSString *token, WujiRtmRenewTokenErrorCode errorCode);

/**
 Returns the result of the [subscribePeersOnlineStatus]([WujiRtmKit
 subscribePeersOnlineStatus:completion:]) or [unsubscribePeersOnlineStatus]([WujiRtmKit
 unsubscribePeersOnlineStatus:completion:]) method call. <p><i>errorCode:</i> See
 WujiRtmPeerSubscriptionStatusErrorCode.
 */
typedef void (^WujiRtmSubscriptionRequestBlock)(WujiRtmPeerSubscriptionStatusErrorCode errorCode);

/**
 Returns the result of the [queryPeersBySubscriptionOption]([WujiRtmKit
 queryPeersBySubscriptionOption:completion:]) method call. <p><i>errorCode:</i> See
 WujiRtmQueryPeersBySubscriptionOptionErrorCode.
 */
typedef void (^WujiRtmQueryPeersBySubscriptionOptionBlock)(
    NSArray<NSString *> *peers, WujiRtmQueryPeersBySubscriptionOptionErrorCode errorCode);

/**
 Returns the result of the [downloadMediaToMemory]([WujiRtmKit
 downloadMediaToMemory:withRequest:completion:]) method call. <p><li><i>requestId:</i> The unique ID
 of the download request.<li><i>data:</i> The downloaded file or image.<li><i>errorCode:</i> See
 WujiRtmDownloadMediaErrorCode.
 */
typedef void (^WujiRtmDownloadMediaToMemoryBlock)(long long requestId,
                                                  NSData *data,
                                                  WujiRtmDownloadMediaErrorCode errorCode);

/**
 Returns the result of the [downloadMediaToFile]([WujiRtmKit
 downloadMedia:toFile:withRequest:completion:]) method call. <p><li><i>requestId:</i> The unique ID
 of the download request.<li><i>errorCode:</i> See WujiRtmDownloadMediaErrorCode.
 */
typedef void (^WujiRtmDownloadMediaToFileBlock)(long long requestId,
                                                WujiRtmDownloadMediaErrorCode errorCode);

/**
 Returns the result of the [createFileMessageByUploading]([WujiRtmKit
 createFileMessageByUploading:withRequest:completion:]). <p><li><i>requestId:</i> The unique ID of
 the upload request.<li><i>fileMessage:</i> An WujiRtmFileMessage object. <i>errorCode:</i> See
 WujiRtmUploadMediaErrorCode.
 */
typedef void (^WujiRtmUploadFileMediaBlock)(long long requestId,
                                            WujiRtmFileMessage *fileMessage,
                                            WujiRtmUploadMediaErrorCode errorCode);
/**
 Returns the result of the [createImageMessageByUploading]([WujiRtmKit
 createImageMessageByUploading:withRequest:completion:]) method call. <p><li><i>requestId:</i> The
 unique ID of the upload request.<li><i>imageMessage:</i> An WujiRtmImageMessage object.
 <i>errorCode:</i> See WujiRtmUploadMediaErrorCode.
 */
typedef void (^WujiRtmUploadImageMediaBlock)(long long requestId,
                                             WujiRtmImageMessage *imageMessage,
                                             WujiRtmUploadMediaErrorCode errorCode);

/**
 Returns the result of the [cancelMediaDownload]([WujiRtmKit cancelMediaDownload:completion:]) or
 [cancelMediaUpload]([WujiRtmKit cancelMediaUpload:completion:]) method call.
 <p><li><i>requestId:</i> The unique ID of the cancel request.<i>errorCode:</i> See
 WujiRtmCancelMediaErrorCode.
 */
typedef void (^WujiRtmCancelMediaBlock)(long long requestId, WujiRtmCancelMediaErrorCode errorCode);

/**
Attributes of a peer-to-peer or channel text message.
 */
__attribute__((visibility("default"))) @interface WujiRtmMessage : NSObject

/**
 Wuji RTM message type. See WujiRtmMessageType. Text messages only.
 */
@property(nonatomic, assign, readonly) WujiRtmMessageType type;

/**
 Wuji RTM message content. Must not exceed 32 KB in length.
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
 message as an offline message (sets [enableOfflineMessaging]([WujiRtmSendMessageOptions
 enableOfflineMessaging]) as YES) when the specified user is offline, does the method return YES
 when the user is back online. <li> For now we only cache 200 offline messages for up to seven days
 for each message receiver. When the number of the cached messages reaches this limit, the newest
 message overrides the oldest one.
 */
@property(nonatomic, assign, readonly) BOOL isOfflineMessage;

/**
 Creates and initializes a text message to be sent.

 @param text A text message of less than 32 KB.

 @return An WujiRtmMessage instance.

 */
- (instancetype _Nonnull)initWithText:(NSString *_Nonnull)text;
@end

/**
 Attributes of a peer-to-peer or channel raw message. Inherited from WujiRtmMessage.
 */
__attribute__((visibility("default"))) @interface WujiRtmRawMessage : WujiRtmMessage

/**
 Wuji RTM raw message content. Must not exceed 32 KB in length.
 */
@property(nonatomic, nonnull) NSData *rawData;

/**
 Creates and initializes a raw message to be sent.

 @param rawData A raw message of less than 32 KB.
 @param description A brief text description of the raw message. If you set a text description,
 ensure that the size of the raw message and the description combined does not exceed 32 KB.
 @return An WujiRtmMessage instance.
 */
- (instancetype _Nonnull)initWithRawData:(NSData *_Nonnull)rawData
                             description:(NSString *_Nonnull)description;
@end

/**
 The interface for setting and retrieving attributes of a file message. Inherited from
 WujiRtmMessage.
 */
__attribute__((visibility("default"))) @interface WujiRtmFileMessage : WujiRtmMessage

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
 WujiRtmMessage.
 */
__attribute__((visibility("default"))) @interface WujiRtmImageMessage : WujiRtmMessage

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
__attribute__((visibility("default"))) @interface WujiRtmPeerOnlineStatus : NSObject

/**
 The user ID of the specified user.
 */
@property(nonatomic, copy, nonnull) NSString *peerId;

/**
 The online status of the peer. **DEPRECATED** as of v1.2.0. Use `state` instead.

 - YES: The user is online (the user has logged in the Wuji RTM system).
 - NO: The user is offline (the user has logged out of the Wuji RTM system, has not logged in, or
 has failed to logged in).
*/
@property(nonatomic, assign) BOOL isOnline;

/**
 The online state of the peer. See WujiRtmPeerOnlineState.

 **NOTE**

 - The server will never return the `unreachable` state, if you <i>query</i> the online status of
 specified peer(s) ([queryPeersOnlineStatus]([WujiRtmKit queryPeersOnlineStatus:completion:])). See
 also: [WujiRtmSubscriptionRequestBlock](WujiRtmSubscriptionRequestBlock).
 - The server may return the `unreachable` state, if you <i>subscribe to</i> the online status of
 specified peer(s) ([subscribePeersOnlineStatus]([WujiRtmKit
 subscribePeersOnlineStatus:completion:])). See also: [PeersOnlineStatusChanged]([WujiRtmDelegate
 rtmKit:PeersOnlineStatusChanged:]).
 */
@property(nonatomic, assign, readonly) WujiRtmPeerOnlineState state;
@end

/**
 Data structure indicating the member count of a channel.
 */
__attribute__((visibility("default"))) @interface WujiRtmChannelMemberCount : NSObject

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
__attribute__((visibility("default"))) @interface WujiRtmMediaOperationProgress : NSObject

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
 The WujiRtmChannelDelegate protocol enables Wuji RTM channel callback event notifications to your
 app.
 */
@protocol WujiRtmChannelDelegate;

/**
 The WujiRtmCallDelegate protocol enables Wuji RTM call callback event notifications to your app.
 */
@protocol WujiRtmCallDelegate;

/**
 The WujiRtmDelegate protocol enables Wuji RTM callback event notifications to your app.
 */
@protocol WujiRtmDelegate <NSObject>
@optional

/**
 Occurs when the connection state between the SDK and the Wuji RTM system changes.

 @param kit An [WujiRtmKit](WujiRtmKit) instance.
 @param state The new connection state. See WujiRtmConnectionState.
 @param reason The reason for the connection state change. See WujiRtmConnectionChangeReason.
 */
- (void)rtmKit:(WujiRtmKit *_Nonnull)kit
    connectionStateChanged:(WujiRtmConnectionState)state
                    reason:(WujiRtmConnectionChangeReason)reason;

/**
 Occurs when receiving a peer-to-peer message.

 @param kit An [WujiRtmKit](WujiRtmKit) instance.
 @param message The received message. Ensure that you check the `type` property when receiving the
 message instance: If the message type is `WujiRtmMessageTypeRaw`, you need to downcast the received
 instance from WujiRtmMessage to WujiRtmRawMessage. See WujiRtmMessageType.
 @param peerId The user ID of the sender.
 */
- (void)rtmKit:(WujiRtmKit *_Nonnull)kit
    messageReceived:(WujiRtmMessage *_Nonnull)message
           fromPeer:(NSString *_Nonnull)peerId;

/**
 Occurs when receiving a peer-to-peer file message.

 @param kit An [WujiRtmKit](WujiRtmKit) instance.
 @param message The received peer-to-peer file message. See WujiRtmFileMessage.
 @param peerId The ID of the message sender.
 */
- (void)rtmKit:(WujiRtmKit *_Nonnull)kit
    fileMessageReceived:(WujiRtmFileMessage *_Nonnull)message
               fromPeer:(NSString *_Nonnull)peerId;

/**
 Occurs when receiving a peer-to-peer image message.

 @param kit An [WujiRtmKit](WujiRtmKit) instance.
 @param message The received peer-to-peer image message. See WujiRtmImageMessage.
 @param peerId The ID of the message sender.
 */
- (void)rtmKit:(WujiRtmKit *_Nonnull)kit
    imageMessageReceived:(WujiRtmImageMessage *_Nonnull)message
                fromPeer:(NSString *_Nonnull)peerId;

/**
 Reports the progress of an ongoing upload task.

 **NOTE**

 - If the upload task is ongoing, the SDK returns this callback once every second.
 - If the upload task comes to a halt, the SDK stops returning this callback until the task is going
 again.

 @param kit An [WujiRtmKit](WujiRtmKit) instance.
 @param requestId The unique ID of the upload request.
 @param progress The progress of the ongoing upload task. See WujiRtmMediaOperationProgress.
 */
- (void)rtmKit:(WujiRtmKit *_Nonnull)kit
                media:(long long)requestId
    uploadingProgress:(WujiRtmMediaOperationProgress *_Nonnull)progress;

/**
 Reports the progress of an ongoing download task.

 **NOTE**

 - If the download task is ongoing, the SDK returns this callback once every second.
 - If the download task comes to a halt, the SDK stops returning this callback until the task is
 going again.

 @param kit An [WujiRtmKit](WujiRtmKit) instance.
 @param requestId The unique ID of the download request.
 @param progress The progress of the ongoing download task. See WujiRtmMediaOperationProgress.
 */
- (void)rtmKit:(WujiRtmKit *_Nonnull)kit
                  media:(long long)requestId
    downloadingProgress:(WujiRtmMediaOperationProgress *_Nonnull)progress;

/**
 Occurs when the online status of the peers, to whom you subscribe, changes.

 - When the subscription to the online status of specified peer(s) succeeds, the SDK returns this
 callback to report the online status of peers, to whom you subscribe.
 - When the online status of the peers, to whom you subscribe, changes, the SDK returns this
 callback to report whose online status has changed.
 - If the online status of the peers, to whom you subscribe, changes when the SDK is reconnecting to
 the server, the SDK returns this callback to report whose online status has changed when
 successfully reconnecting to the server.

 @param kit An [WujiRtmKit](WujiRtmKit) instance.
 @param onlineStatus An array of peers' online states. See WujiRtmPeerOnlineStatus.
 */
- (void)rtmKit:(WujiRtmKit *_Nonnull)kit
    PeersOnlineStatusChanged:(NSArray<WujiRtmPeerOnlineStatus *> *_Nonnull)onlineStatus;

/**
 Occurs when the RTM server detects that the RTM token has exceeded the 24-hour validity period and
 when the SDK is in the `WujiRtmConnectionStateReconnecting` state.

 - This callback occurs only when the SDK is reconnecting to the server. You will not receive this
 callback when the SDK is in the `WujiRtmConnectionStateConnected` state.
 - When receiving this callback, generate a new RTM Token on the server and call the
 [renewToken]([WujiRtmKit renewToken:completion:]) method to pass the new Token on to the server.

 @param kit An WujiRtmKit instance.
 */
- (void)rtmKitTokenDidExpire:(WujiRtmKit *_Nonnull)kit;
@end

/**
Log Filter types.
 */
typedef NS_ENUM(NSInteger, WujiRtmLogFilter) {

  /**
0: Do not output any log information.
   */
  WujiRtmLogFilterOff = 0,

  /**
0x000f: Output CRITICAL, ERROR, WARNING, and INFO level log information.
   */
  WujiRtmLogFilterInfo = 0x000f,

  /**
0x000e: Output CRITICAL, ERROR, and WARNING level log information.
   */
  WujiRtmLogFilterWarn = 0x000e,

  /**
0x000c: Output CRITICAL and ERROR level log information.
   */
  WujiRtmLogFilterError = 0x000c,

  /**
0x0008: Output CRITICAL level log information.
   */
  WujiRtmLogFilterCritical = 0x0008,

  /**
0x80f: RESERVED FOR FUTURE USE
   */
  WujiRtmLogFilterMask = 0x80f,
};

/**
 A data structure holding an RTM attribute and its value.
 */
__attribute__((visibility("default"))) @interface WujiRtmAttribute : NSObject

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
__attribute__((visibility("default"))) @interface WujiRtmChannelAttribute : NSObject

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
 Returns the result of the [setLocalUserAttributes]([WujiRtmKit setLocalUserAttributes:completion:])
 <p><li><i>errorCode:</i> See WujiRtmProcessAttributeErrorCode.
 */
typedef void (^WujiRtmSetLocalUserAttributesBlock)(WujiRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [addOrUpdateLocalUserAttributes]([WujiRtmKit
 addOrUpdateLocalUserAttributes:completion:]) method call. <p><li><i>errorCode:</i> See
 WujiRtmProcessAttributeErrorCode.
 */
typedef void (^WujiRtmAddOrUpdateLocalUserAttributesBlock)(
    WujiRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [deleteLocalUserAttributesByKeys]([WujiRtmKit
 deleteLocalUserAttributesByKeys:completion:]) method call. <p><li><i>errorCode:</i>
 WujiRtmProcessAttributeErrorCode.
 */
typedef void (^WujiRtmDeleteLocalUserAttributesBlock)(WujiRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [clearLocalUserAttributesWithCompletion]([WujiRtmKit
 clearLocalUserAttributesWithCompletion:]) method call. <p><li><i>errorCode:</i> See
 WujiRtmProcessAttributeErrorCode.
 */
typedef void (^WujiRtmClearLocalUserAttributesBlock)(WujiRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [getUserAttributes]([WujiRtmKit getUserAllAttributes:completion:]) or the
 [getUserAttributesByKeys]([WujiRtmKit getUserAttributes:ByKeys:completion:]) method call.
 <p><li><i>attributes:</i> An array of RtmAttibutes. See WujiRtmAttribute. <p><li><i>userId:</i> The
 User ID of the specified user. <p><li><i>errorCode:</i> See WujiRtmProcessAttributeErrorCode.
 */
typedef void (^WujiRtmGetUserAttributesBlock)(NSArray<WujiRtmAttribute *> *_Nullable attributes,
                                              NSString *userId,
                                              WujiRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [getChannelMemberCount]([WujiRtmKit getChannelMemberCount:completion:])
 method call. <p><li><i>channelMemberCounts:</i> An array of WujiRtmChannelMemberCount. See
 WujiRtmChannelMemberCount. <p><li><i>errorCode:</i> See WujiRtmChannelMemberCountErrorCode.
 */
typedef void (^WujiRtmChannelMemberCountBlock)(
    NSArray<WujiRtmChannelMemberCount *> *channelMemberCounts,
    WujiRtmChannelMemberCountErrorCode errorCode);

/**
 Returns the result of the [setLocalUserAttributes]([WujiRtmKit
 setChannel:Attributes:Options:completion:]) <p><li><i>errorCode:</i> See
 WujiRtmProcessAttributeErrorCode.
 */
typedef void (^WujiRtmSetChannelAttributesBlock)(WujiRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [addOrUpdateChannelAttributes]([WujiRtmKit
 addOrUpdateChannel:Attributes:Options:completion:]) method call. <p><li><i>errorCode:</i> See
 WujiRtmProcessAttributeErrorCode.
 */
typedef void (^WujiRtmAddOrUpdateChannelAttributesBlock)(
    WujiRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [deleteChannelAttributesByKeys]([WujiRtmKit
 deleteChannel:AttributesByKeys:Options:completion:]) method call. <p><li><i>errorCode:</i>
 WujiRtmProcessAttributeErrorCode.
 */
typedef void (^WujiRtmDeleteChannelAttributesBlock)(WujiRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [clearChannelAttributesWithCompletion]([WujiRtmKit
 clearChannel:Options:AttributesWithCompletion:]) method call. <p><li><i>errorCode:</i> See
 WujiRtmProcessAttributeErrorCode.
 */
typedef void (^WujiRtmClearChannelAttributesBlock)(WujiRtmProcessAttributeErrorCode errorCode);

/**
 Returns the result of the [getChannelAttributes]([WujiRtmKit getChannelAllAttributes:completion:])
 or the [getChannelAttributesByKeys]([WujiRtmKit getChannelAttributes:ByKeys:completion:]) method
 call. <p><li><i>attributes:</i> An array of WujiRtmChannelAttibute. See WujiRtmChannelAttibute.
 <p><li><i>errorCode:</i> See WujiRtmProcessAttributeErrorCode.
 */
typedef void (^WujiRtmGetChannelAttributesBlock)(
    NSArray<WujiRtmChannelAttribute *> *_Nullable attributes,
    WujiRtmProcessAttributeErrorCode errorCode);

/**
 Message sending options.
 */
__attribute__((visibility("default"))) @interface WujiRtmSendMessageOptions : NSObject

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
__attribute__((visibility("default"))) @interface WujiRtmChannelAttributeOptions : NSObject

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
 The entry point of the Wuji RTM system.
 */
__attribute__((visibility("default"))) @interface WujiRtmKit : NSObject

/**
 WujiRtmDelegate enables Wuji RTM callback event notifications to your app.
 */
@property(atomic, weak, nullable) id<WujiRtmDelegate> wujiRtmDelegate;

/**
 **DEPRECATED** The property for managing channels for the local user.
 */
@property(atomic, readonly, nullable)
    NSMutableDictionary<NSString *, WujiRtmChannel *> *channels __deprecated;

@property(atomic, strong, nullable) WujiRtmCallKit *rtmCallKit;

/**
 Creates and initializes an `WujiRtmKit` instance.

 The Wuji RTM SDK supports creating multiple `WujiRtmKit` instances. All methods in the `WujiRtmKit`
 class, except the [destroyChannelWithId](destroyChannelWithId:) method, are executed
 asynchronously.

 @param appId The App ID issued to you from the Wuji Console. Apply for a new App ID from Wuji if it
 is missing from your kit.

 @param delegate WujiRtmDelegate invokes callbacks to be passed to the app on Wuji RTM SDK runtime
 events.

 @return - An `WujiRtmKit` instance if this method call succeeds.
 - `nil` if this method call fails for the reason that the length of the `appId` is not 32
 characters.

 */
- (instancetype _Nullable)initWithAppId:(NSString *_Nonnull)appId
                               delegate:(id<WujiRtmDelegate> _Nullable)delegate;

/**
 Logs in the Wuji RTM system.

 **NOTE**

 - If you log in with the same user ID from a different instance, you will be kicked out of your
 previous login and removed from previously joined channels.
 - The call frequency limit for this method is two queries per second.
 - Only after you successfully call this method and receives the `WujiRtmLoginErrorOk` error code,
 can you call the key RTM methods except:

  - [createChannelWithId]([WujiRtmKit createChannelWithId:delegate:])
  - [initWithText]([WujiRtmMessage initWithText:])
  - [getRtmCallKit]([WujiRtmKit getRtmCallKit])
  - [initWithCalleeId]([WujiRtmLocalInvitation initWithCalleeId:])

 After the app calls this method, the local user receives the
 [connectionStateChanged]([WujiRtmDelegate rtmKit:connectionStateChanged:reason:]) callback and
 switches to the `WujiRtmConnectionStateConnecting` state.

 - Success: The local user receives the [WujiRtmLoginBlock](WujiRtmLoginBlock) and
 [connectionStateChanged]([WujiRtmDelegate rtmKit:connectionStateChanged:reason:]) callbacks, and
 switches to the `WujiRtmConnectionStateConnected` state.
 - Failure: The local user receives the [WujiRtmLoginBlock](WujiRtmLoginBlock) and
 [connectionStateChanged]([WujiRtmDelegate rtmKit:connectionStateChanged:reason:]) callbacks, and
 switches to the `WujiRtmConnectionStateDisconnected` state.

 @param token A token generated by the app server and used to log in the Wuji RTM system. `token` is
 used when dynamic authentication is enabled. Set `token` as `nil` at the integration and test
 stages.

 @param userId The user ID of the user logging in the Wuji RTM system. The string length must be
 less than 64 bytes with the following character scope:

 - All lowercase English letters: a to z</li>
 - All uppercase English letters: A to Z</li>
 - All numeric characters: 0 to 9</li>
 - The space character.</li>
 - Punction characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
 ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ","

 **NOTE**

 A `userId` cannot be empty, nil, or "null".

 @param completionBlock [WujiRtmLoginBlock](WujiRtmLoginBlock) returns the result of this method
 call. See WujiRtmLoginErrorCode for the error codes.

 */
- (void)loginByToken:(NSString *_Nullable)token
                user:(NSString *_Nonnull)userId
          completion:(WujiRtmLoginBlock _Nullable)completionBlock;

/**
 Logs out of the Wuji RTM system.

 - Success: The local user receives the [WujiRtmLogoutBlock](WujiRtmLogoutBlock) and
 [connectionStateChanged]([WujiRtmDelegate rtmKit:connectionStateChanged:reason:]) callbacks, and
 switches to the `WujiRtmConnectionStateDisConnected` state.
 - Failure: The local user receives the [WujiRtmLogoutBlock](WujiRtmLogoutBlock) callback.

 @param completionBlock [WujiRtmLogoutBlock](WujiRtmLogoutBlock) returns the result of this method
 call. See WujiRtmLogoutErrorCode for the error codes.
 */
- (void)logoutWithCompletion:(WujiRtmLogoutBlock _Nullable)completionBlock;

/**
 Renews the current RTM Token.

 You are required to renew your Token when receiving the [rtmKitTokenDidExpire]([WujiRtmDelegate
 rtmKitTokenDidExpire:]) callback, and the [WujiRtmRenewTokenBlock](WujiRtmRenewTokenBlock) callback
 returns the result of this method call. The call frequency limit for this method is two queries per
 second.

 @param token Your new RTM Token.
 @param completionBlock [WujiRtmRenewTokenBlock](WujiRtmRenewTokenBlock) returns the result of this
 method call.

 - *token:* Your new RTM Token.
 - *errorCode:* See WujiRtmRenewTokenErrorCode for the error codes.
*/
- (void)renewToken:(NSString *_Nonnull)token
        completion:(WujiRtmRenewTokenBlock _Nullable)completionBlock;

/**
 Sends a peer-to-peer message to a specified peer user.

 **DEPRECATED**

 We do not recommend using this method to send a peer-to-peer message. Use [sendMessage]([WujiRtmKit
 sendMessage:toPeer:sendMessageOptions:completion:]) instead.

 - Success:
    - The local user receives the [WujiRtmSendPeerMessageBlock](WujiRtmSendPeerMessageBlock)
 callback.
    - The specified remote user receives the [messageReceived]([WujiRtmDelegate
 rtmKit:messageReceived:fromPeer:]) callback.
 - Failure: The local user receives the [WujiRtmSendPeerMessageBlock](WujiRtmSendPeerMessageBlock)
 callback with an error. See WujiRtmSendPeerMessageErrorCode for the error codes.

 **NOTE**

 You can send messages, including peer-to-peer and channel messages, at a maximum speed of 60
 queries per second.

 @param message The message to be sent. For information about creating a message, see
 WujiRtmMessage.
 @param peerId The ID of the remote user.
 @param completionBlock [WujiRtmSendPeerMessageBlock](WujiRtmSendPeerMessageBlock) returns the
 result of this method call. See WujiRtmSendPeerMessageErrorCode for the error codes.
 */
- (void)sendMessage:(WujiRtmMessage *_Nonnull)message
             toPeer:(NSString *_Nonnull)peerId
         completion:(WujiRtmSendPeerMessageBlock _Nullable)completionBlock;

/**
 Downloads a file or image from the Wuji server to the local memory by media ID.

 **NOTE**

 - This method applies to scenarios requiring quick access to the downloaded file or image.
 - The SDK releases the downloaded file or image immediately after returning the
 [WujiRtmDownloadMediaToMemoryBlock](WujiRtmDownloadMediaToMemoryBlock) callback.

 @param mediaId The media ID of the file or image on the Wuji server.
 @param requestId The unique ID to identify one request.
 @param completionBlock [WujiRtmDownloadMediaToMemoryBlock](WujiRtmDownloadMediaToMemoryBlock)
 returns the result of this method call. See WujiRtmDownloadMediaErrorCode for the error codes.
 */
- (void)downloadMediaToMemory:(NSString *_Nonnull)mediaId
                  withRequest:(long long *)requestId
                   completion:(WujiRtmDownloadMediaToMemoryBlock _Nullable)completionBlock;

/**
 Downloads a file or image from the Wuji server to a specified local directory by media ID.

 @param mediaId The media ID of the file or image on the Wuji server.
 @param filePath The full path to the downloaded file or image. Must be in UTF-8.
 @param requestId The unique ID of this download request.
 @param completionBlock [WujiRtmDownloadMediaToFileBlock](WujiRtmDownloadMediaToFileBlock) returns
 the result of this method call. See WujiRtmDownloadMediaErrorCode for the error codes.
 */
- (void)downloadMedia:(NSString *_Nonnull)mediaId
               toFile:(NSString *_Nonnull)filePath
          withRequest:(long long *)requestId
           completion:(WujiRtmDownloadMediaToFileBlock _Nullable)completionBlock;

/**
 Gets an WujiRtmFileMessage instance by uploading a file to the Wuji server.

 The SDK returns the result with the [WujiRtmUploadFileMediaBlock](WujiRtmUploadFileMediaBlock)
 callback. If success, this callback returns a corresponding WujiRtmMessage instance, and then you
 can downcast it to WujiRtmFileMessage according to its type.

 **NOTE**

 - If you have at hand the media ID of a file on the Wuji server, you can call
 [createFileMessageByMediaId]([WujiRtmKit createFileMessageByMediaId:]) to create an
 WujiRtmFileMessage instance.
 - To cancel an ongoing upload task, call [cancelMediaUpload]([WujiRtmKit
 cancelMediaUpload:completion:]).

 @param filePath The full path to the local file to upload. Must be in UTF-8.
 @param requestId The unique ID of this upload request.
 @param completionBlock [WujiRtmUploadFileMediaBlock](WujiRtmUploadFileMediaBlock) returns the
 result of this method call. See WujiRtmUploadMediaErrorCode for the error codes.
 */
- (void)createFileMessageByUploading:(NSString *_Nonnull)filePath
                         withRequest:(long long *)requestId
                          completion:(WujiRtmUploadFileMediaBlock _Nullable)completionBlock;

/**
 Gets an WujiRtmImageMessage instance by uploading an image to the Wuji server.

 The SDK returns the result by the [WujiRtmUploadImageMediaBlock](WujiRtmUploadImageMediaBlock)
 callback. If success, this callback returns a corresponding WujiRtmMessage instance, and then you
 can downcast it to WujiRtmImageMessage according to its type.

 - If the uploaded image is in JPEG, JPG, BMP, or PNG format, the SDK calculates the width and
 height of the image. You can get the calculated width and height from the received
 WujiRtmImageMessage instance.
 - Otherwise, you need to set the width and height of the uploaded image within the received
 WujiRtmImageMessage instance by yourself.

 **NOTE**

 - If you have at hand the media ID of an image on the Wuji server, you can call
 [createImageMessageByMediaId]([WujiRtmKit createImageMessageByMediaId:]) to create an
 WujiRtmImageMessage instance.
 - To cancel an ongoing upload task, call [cancelMediaUpload]([WujiRtmKit
 cancelMediaUpload:completion:]).

 @param filePath The full path to the local image to upload. Must be in UTF-8.
 @param requestId The unique ID of the upload request.
 @param completionBlock [WujiRtmUploadImageMediaBlock](WujiRtmUploadImageMediaBlock) returns the
 result of this method call. See WujiRtmUploadMediaErrorCode for the error codes.
 */
- (void)createImageMessageByUploading:(NSString *_Nonnull)filePath
                          withRequest:(long long *)requestId
                           completion:(WujiRtmUploadImageMediaBlock _Nullable)completionBlock;

/**
 Cancels an ongoing file or image download task by request ID.

 **NOTE**
 You can only cancel an ongoing download task. After a download task completes, the corresponding
 request ID is no longer valid and hence you cannot cancel it.

 @param requestId The unique Id to identify one request
 @param completionBlock [WujiRtmCancelMediaBlock](WujiRtmCancelMediaBlock) returns the result of
 this method call. See WujiRtmCancelMediaErrorCode for the error codes.
 */
- (void)cancelMediaDownload:(long long)requestId
                 completion:(WujiRtmCancelMediaBlock _Nullable)completionBlock;

/**
 Cancels an ongoing file or image upload task by request ID.

 **NOTE**
 You can only cancel an ongoing upload task. After an upload task completes, you cannot cancel it
 and the corresponding request ID is no longer valid.

 @param requestId The unique ID of the upload request to cancel.
 @param completionBlock [WujiRtmCancelMediaBlock](WujiRtmCancelMediaBlock) returns the result of
 this method call. See WujiRtmCancelMediaErrorCode for the error codes.
 */
- (void)cancelMediaUpload:(long long)requestId
               completion:(WujiRtmCancelMediaBlock _Nullable)completionBlock;

/**
 Creates an WujiRtmFileMessage instance by media ID.

 - If you have at hand the media ID of a file on the Wuji server, you can call this method to create
 an WujiRtmFileMessage instance.
 - If you do not have a media ID, then you must call [createFileMessageByUploading]([WujiRtmKit
 createFileMessageByUploading:withRequest:completion:]) to get a corresponding WujiRtmFileMessage
 instance by uploading a file to the Wuji RTM server.

 @param mediaId The media ID of an uploaded file on the Wuji server.
 @return An WujiRtmFileMessage instance.
 */
- (WujiRtmFileMessage *)createFileMessageByMediaId:(NSString *_Nonnull)mediaId;

/**
 Creates an WujiRtmImageMessage instance by media ID.

 - If you have at hand the media ID of an image on the Wuji server, you can call this method to
 create an WujiRtmImageMessage instance.
 - If you do not have a media ID, then you must call [createFileMessageByUploading]([WujiRtmKit
 createImageMessageByUploading:withRequest:completion:]) to get a corresponding WujiRtmImageMessage
 instance by uploading an image to the Wuji RTM server.

 @param mediaId The media ID of an uploaded image on the Wuji server.
 @return An WujiRtmImageMessage instance.
 */
- (WujiRtmImageMessage *)createImageMessageByMediaId:(NSString *_Nonnull)mediaId;

/**
 Sends an (offline) peer-to-peer message to a specified peer user.

 This method allows you to send a message to a specified user when the user is offline. If you set a
 message as an offline message and the specified user is offline when you send it, the RTM server
 caches it. Please note that for now we only cache 200 offline messages for up to seven days for
 each receiver. When the number of the cached messages reaches this limit, the newest message
 overrides the oldest one.

 If you use this method to send off a <i>text</i> message that starts off with
 WUJI_RTM_ENDCALL_PREFIX\_\<channelId\>\_\<your additional information\>, then this method is
 compatible with the endCall method of the legacy Wuji Signaling SDK. Replace \<channelId\> with the
 channel ID from which you want to leave (end call), and replace \<your additional information\>
 with any additional information. Note that you must not put any "_" (underscore) in your additional
 information but you can set \<your additional information\> as empty "".

 - Success:
   - The local user receives the [WujiRtmSendPeerMessageBlock](WujiRtmSendPeerMessageBlock)
 callback.
   - The specified remote user receives the [messageReceived]([WujiRtmDelegate
 rtmKit:messageReceived:fromPeer:]) callback.
 - Failure: The local user receives the [WujiRtmSendPeerMessageBlock](WujiRtmSendPeerMessageBlock)
 callback with an error. See WujiRtmSendPeerMessageErrorCode for the error codes.

 **NOTE**

 You can send messages, including peer-to-peer and channel messages, at a maximum speed of 60
 queries per second.

 @param message The message to be sent. For information about creating a message, see
 WujiRtmMessage.
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

 @param options Options when sending the message to a peer. See WujiRtmSendMessageOptions.
 @param completionBlock [WujiRtmSendPeerMessageBlock](WujiRtmSendPeerMessageBlock) returns the
 result of this method call. See WujiRtmSendPeerMessageErrorCode for the error codes.
 */
- (void)sendMessage:(WujiRtmMessage *_Nonnull)message
                toPeer:(NSString *_Nonnull)peerId
    sendMessageOptions:(WujiRtmSendMessageOptions *_Nonnull)options
            completion:(WujiRtmSendPeerMessageBlock _Nullable)completionBlock;

/**
 Creates an Wuji RTM channel.

 **NOTE**

 You can create multiple `WujiRtmChannel` instances in an `WujiRtmKit` instance. But you can only
 join a maximum of 20 channels at the same time. As a good practice, Agore recommends calling the
 [destroyChannelWithId]([WujiRtmKit destroyChannelWithId:]) method to release all resources of an
 RTM channel that you no longer use.

 @param channelId The unique channel name of the Wuji RTM session. The string length must not exceed
 64 bytes with the following character scope:

 - All lowercase English letters: a to z</li>
 - All uppercase English letters: A to Z</li>
 - All numeric characters: 0 to 9</li>
 - The space character.</li>
 - Punction characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
 ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ","

 **NOTE**

 A `channelId` cannot be empty, nil, or "null".

 @param delegate [WujiRtmChannelDelegate](WujiRtmChannelDelegate) invokes callbacks to be passed to
 the app on Wuji RTM SDK runtime events.

 @return - An [WujiRtmChannel](WujiRtmChannel) instance if this method call succeeds.
 - `nil` if this method call fails for reasons such as the `channelId` is invalid or a channel with
 the same `channelId` already exists.

*/
- (WujiRtmChannel *_Nullable)createChannelWithId:(NSString *_Nonnull)channelId
                                        delegate:(id<WujiRtmChannelDelegate> _Nullable)delegate;

/**
 Destroys a specified local [WujiRtmChannel](WujiRtmChannel) instance.

 **NOTE**

 Do not call this method in any of your callbacks.

 @param channelId The channel ID of the channel to be destroyed.
*/
- (BOOL)destroyChannelWithId:(NSString *_Nonnull)channelId;

/**
 Gets the WujiRtmCallKit instance.

 @return The WujiRtmCallKit instance.
 */
- (WujiRtmCallKit *_Nullable)getRtmCallKit;

/**
 Queries the online status of the specified user(s).

 - Online: The user has logged in the Wuji RTM system.
 - Offline: The user has logged out of the Wuji RTM system.

 @param peerIds User IDs of the specified users.
 @param completionBlock [WujiRtmQueryPeersOnlineBlock](WujiRtmQueryPeersOnlineBlock) returns the
 result of this method call.

 - *peerOnlineStatus:* A list of the specified users' online status. See WujiRtmPeerOnlineStatus.
 - *errorCode:* See WujiRtmQueryPeersOnlineBlock.
*/
- (void)queryPeersOnlineStatus:(NSArray<NSString *> *_Nonnull)peerIds
                    completion:(WujiRtmQueryPeersOnlineBlock _Nullable)completionBlock;

/**
 Substitutes the local user's attributes with new ones.

 For [setLocalUserAttributes]([WujiRtmKit setLocalUserAttributes:completion:]),
 [addOrUpdateLocalUserAttributes]([WujiRtmKit addOrUpdateLocalUserAttributes:completion:]),
 [deleteLocalUserAttributesByKeys]([WujiRtmKit deleteLocalUserAttributesByKeys:completion:]) and
 [clearLocalUserAttributes]([WujiRtmKit clearLocalUserAttributesWithCompletion:]) taken together:
 the limit is 10 queries every five seconds.

 @param attributes The new attributes. See WujiRtmAttribute.
 @param completionBlock [WujiRtmSetLocalUserAttributesBlock](WujiRtmSetLocalUserAttributesBlock)
 returns the result of this method call.
 */
- (void)setLocalUserAttributes:(NSArray<WujiRtmAttribute *> *_Nullable)attributes
                    completion:(WujiRtmSetLocalUserAttributesBlock _Nullable)completionBlock;

/**
 Adds or updates the local user's attribute(s).

 For [setLocalUserAttributes]([WujiRtmKit setLocalUserAttributes:completion:]),
 [addOrUpdateLocalUserAttributes]([WujiRtmKit addOrUpdateLocalUserAttributes:completion:]),
 [deleteLocalUserAttributesByKeys]([WujiRtmKit deleteLocalUserAttributesByKeys:completion:]) and
 [clearLocalUserAttributes]([WujiRtmKit clearLocalUserAttributesWithCompletion:]) taken together:
 the limit is 10 queries every five seconds.

 This method updates the local user's attribute(s) if it finds that the attribute(s) has/have the
 same key(s), or adds attribute(s) to the local user if it does not.

 @param attributes The attrubutes to be added or updated. See WujiRtmAttribute 。
 @param completionBlock
 [WujiRtmAddOrUpdateLocalUserAttributesBlock](WujiRtmAddOrUpdateLocalUserAttributesBlock) returns
 the result of this method call.
 */
- (void)addOrUpdateLocalUserAttributes:(NSArray<WujiRtmAttribute *> *_Nullable)attributes
                            completion:(WujiRtmAddOrUpdateLocalUserAttributesBlock _Nullable)
                                           completionBlock;

/**
 Deletes the local user's attributes using attribute keys.

 For [setLocalUserAttributes]([WujiRtmKit setLocalUserAttributes:completion:]),
 [addOrUpdateLocalUserAttributes]([WujiRtmKit addOrUpdateLocalUserAttributes:completion:]),
 [deleteLocalUserAttributesByKeys]([WujiRtmKit deleteLocalUserAttributesByKeys:completion:]) and
 [clearLocalUserAttributes]([WujiRtmKit clearLocalUserAttributesWithCompletion:]) taken together:
 the limit is 10 queries every five seconds.

 @param attributeKeys An array of the attribute keys to be deleted.
 @param completionBlock
 [WujiRtmDeleteLocalUserAttributesBlock](WujiRtmDeleteLocalUserAttributesBlock) returns the result
 of this method call.
 */
- (void)deleteLocalUserAttributesByKeys:(NSArray<NSString *> *_Nullable)attributeKeys
                             completion:
                                 (WujiRtmDeleteLocalUserAttributesBlock _Nullable)completionBlock;

/**
 Clears all attributes of the local user.

 For [setLocalUserAttributes]([WujiRtmKit setLocalUserAttributes:completion:]),
 [addOrUpdateLocalUserAttributes]([WujiRtmKit addOrUpdateLocalUserAttributes:completion:]),
 [deleteLocalUserAttributesByKeys]([WujiRtmKit deleteLocalUserAttributesByKeys:completion:]) and
 [clearLocalUserAttributes]([WujiRtmKit clearLocalUserAttributesWithCompletion:]) taken together:
 the limit is 10 queries every five seconds.

 @param completionBlock [WujiRtmClearLocalUserAttributesBlock](WujiRtmClearLocalUserAttributesBlock)
 returns the result of this method call.
 */
- (void)clearLocalUserAttributesWithCompletion:
    (WujiRtmClearLocalUserAttributesBlock _Nullable)completionBlock;

/**
 Gets all attributes of a specified user.

 For [getUserAttributes]([WujiRtmKit getUserAllAttributes:completion:]) and
 [getUserAttributesByKeys]([WujiRtmKit getUserAttributes:ByKeys:completion:]) taken together, the
 call frequency limit is 40 queries every five seconds.

 @param userId The user ID of the specified user.
 @param completionBlock [WujiRtmGetUserAttributesBlock](WujiRtmGetUserAttributesBlock) returns the
 result of this method call.
 */
- (void)getUserAllAttributes:(NSString *)userId
                  completion:(WujiRtmGetUserAttributesBlock _Nullable)completionBlock;

/**
 Gets the attributes of a specified user using attribute keys.

 For [getUserAttributes]([WujiRtmKit getUserAllAttributes:completion:]) and
 [getUserAttributesByKeys]([WujiRtmKit getUserAttributes:ByKeys:completion:]) taken together, the
 call frequency limit is 40 queries every five seconds.

 @param userId The user ID of the specified user.
 @param attributeKeys An array of the attribute keys.
 @param completionBlock [WujiRtmGetUserAttributesBlock](WujiRtmGetUserAttributesBlock) returns the
 result of this method call.
 */
- (void)getUserAttributes:(NSString *)userId
                   ByKeys:(NSArray<NSString *> *_Nullable)attributeKeys
               completion:(WujiRtmGetUserAttributesBlock _Nullable)completionBlock;

/**
 Gets the member count of specified channel(s).

 **NOTE**

 - The call frequency limit for this method is one query per second.
 - We do not support getting the member counts of more than 32 channels in one method call.
 - You do not have to join the specified channel(s) to call this method.

 @param channelIds An array of the specified channel ID(s).
 @param completionBlock [WujiRtmChannelMemberCountBlock](WujiRtmChannelMemberCountBlock) returns the
 result of this method call.
 */
- (void)getChannelMemberCount:(NSArray<NSString *> *_Nonnull)channelIds
                   completion:(WujiRtmChannelMemberCountBlock _Nullable)completionBlock;

/**
 Resets the attributes of a specified channel.

 - You do not have to join the specified channel to reset its attributes.
 - The attributes of a channel will be cleared if the channel remains empty (has no members) for a
 couple of minutes.
 - If more than one user can update the channel attributes, then Agore recommends calling
 [getChannelAttributes]([WujiRtmKit getChannelAllAttributes:completion:]) to update the cache before
 calling this method.
 - For [setChannelAttributes]([WujiRtmKit setChannel:Attributes:Options:completion:]),
 [addOrUpdateChannelAttributes]([WujiRtmKit addOrUpdateChannel:Attributes:Options:completion:]),
 [deleteChannelAttributesByKeys]([WujiRtmKit deleteChannel:AttributesByKeys:Options:completion:])
 and [clearChannelAttributes]([WujiRtmKit clearChannel:Options:AttributesWithCompletion:]) taken
 together: the limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param attributes An array of the attributes. See WujiRtmChannelAttribute.
 @param options Options for this attribute operation. See WujiRtmChannelAttributeOptions.
 @param completionBlock [WujiRtmSetLocalUserAttributesBlock](WujiRtmSetLocalUserAttributesBlock)
 returns the result of this method call.
 */
- (void)setChannel:(NSString *_Nonnull)channelId
        Attributes:(NSArray<WujiRtmChannelAttribute *> *_Nullable)attributes
           Options:(WujiRtmChannelAttributeOptions *_Nonnull)options
        completion:(WujiRtmSetChannelAttributesBlock _Nullable)completionBlock;

/**
 Adds or updates the attribute(s) of a specified channel.

 This method updates the specified channel's attribute(s) if it finds that the attribute(s) has/have
 the same key(s), or adds attribute(s) to the channel if it does not.

 - You do not have to join the specified channel to update its attributes.
 - The attributes of a channel will be cleared if the channel remains empty (has no members) for a
 couple of minutes.
 - If more than one user can update the channel attributes, then Agore recommends calling
 [getChannelAttributes]([WujiRtmKit getChannelAllAttributes:completion:]) to update the cache before
 calling this method.
 - For [setChannelAttributes]([WujiRtmKit setChannel:Attributes:Options:completion:]),
 [addOrUpdateChannelAttributes]([WujiRtmKit addOrUpdateChannel:Attributes:Options:completion:]),
 [deleteChannelAttributesByKeys]([WujiRtmKit deleteChannel:AttributesByKeys:Options:completion:])
 and [clearChannelAttributes]([WujiRtmKit clearChannel:Options:AttributesWithCompletion:]) taken
 together: the limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param attributes An array of the attributes. See WujiRtmChannelAttribute.
 @param options Options for this attribute operation. See WujiRtmChannelAttributeOptions.
 @param completionBlock
 [WujiRtmAddOrUpdateLocalUserAttributesBlock](WujiRtmAddOrUpdateLocalUserAttributesBlock) returns
 the result of this method call.
 */
- (void)addOrUpdateChannel:(NSString *_Nonnull)channelId
                Attributes:(NSArray<WujiRtmChannelAttribute *> *_Nullable)attributes
                   Options:(WujiRtmChannelAttributeOptions *_Nonnull)options
                completion:(WujiRtmAddOrUpdateChannelAttributesBlock _Nullable)completionBlock;

/**
 Deletes the attributes of a specified channel by attribute keys.

 - You do not have to join the specified channel to delete its attributes.
 - The attributes of a channel will be cleared if the channel remains empty (has no members) for a
 couple of minutes.
 - If more than one user can update the channel attributes, then Agore recommends calling
 [getChannelAttributes]([WujiRtmKit getChannelAllAttributes:completion:]) to update the cache before
 calling this method.
 - For [setChannelAttributes]([WujiRtmKit setChannel:Attributes:Options:completion:]),
 [addOrUpdateChannelAttributes]([WujiRtmKit addOrUpdateChannel:Attributes:Options:completion:]),
 [deleteChannelAttributesByKeys]([WujiRtmKit deleteChannel:AttributesByKeys:Options:completion:])
 and [clearChannelAttributes]([WujiRtmKit clearChannel:Options:AttributesWithCompletion:]) taken
 together: the limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param attributeKeys An array of the attribute keys.
 @param options Options for this attribute operation. See WujiRtmChannelAttributeOptions.
 @param completionBlock
 [WujiRtmDeleteLocalUserAttributesBlock](WujiRtmDeleteLocalUserAttributesBlock) returns the result
 of this method call.
 */
- (void)deleteChannel:(NSString *_Nonnull)channelId
     AttributesByKeys:(NSArray<NSString *> *_Nullable)attributeKeys
              Options:(WujiRtmChannelAttributeOptions *_Nonnull)options
           completion:(WujiRtmDeleteChannelAttributesBlock _Nullable)completionBlock;

/**
 Clears all attributes of a specified channel.

 - You do not have to join the specified channel to clear its attributes.
 - The attributes of a channel will be cleared if the channel remains empty (has no members) for a
 couple of minutes.
 - For [getChannelAttributes]([WujiRtmKit getChannelAllAttributes:completion:]) and
 [getChannelAttributesByKeys]([WujiRtmKit getChannelAttributes:ByKeys:completion:]) taken together,
 the call frequency limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param options Options for this attribute operation. See WujiRtmChannelAttributeOptions.
 @param completionBlock [WujiRtmClearLocalUserAttributesBlock](WujiRtmClearLocalUserAttributesBlock)
 returns the result of this method call.
 */
- (void)clearChannel:(NSString *_Nonnull)channelId
                     Options:(WujiRtmChannelAttributeOptions *_Nonnull)options
    AttributesWithCompletion:(WujiRtmClearChannelAttributesBlock _Nullable)completionBlock;

/**
 Gets all attributes of a specified channel.

 - You do not have to join the specified channel to get its attributes.
 - For [getChannelAttributes]([WujiRtmKit getChannelAllAttributes:completion:]) and
 [getChannelAttributesByKeys]([WujiRtmKit getChannelAttributes:ByKeys:completion:]) taken together,
 the call frequency limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param completionBlock [WujiRtmGetUserAttributesBlock](WujiRtmGetUserAttributesBlock) returns the
 result of this method call.
 */
- (void)getChannelAllAttributes:(NSString *_Nonnull)channelId
                     completion:(WujiRtmGetChannelAttributesBlock _Nullable)completionBlock;

/**
 Gets the attributes of a specified channel by attribute keys.

 - You do not have to join the specified channel to get its attributes.
 - For [getChannelAttributes]([WujiRtmKit getChannelAllAttributes:completion:]) and
 [getChannelAttributesByKeys]([WujiRtmKit getChannelAttributes:ByKeys:completion:]) taken together,
 the call frequency limit is 10 queries every five seconds.

 @param channelId The ID of the specified channel.
 @param attributeKeys An array of the attribute keys.
 @param completionBlock [WujiRtmGetUserAttributesBlock](WujiRtmGetUserAttributesBlock) returns the
 result of this method call.
 */
- (void)getChannelAttributes:(NSString *_Nonnull)channelId
                      ByKeys:(NSArray<NSString *> *_Nullable)attributeKeys
                  completion:(WujiRtmGetChannelAttributesBlock _Nullable)completionBlock;

/**
 Subscribes to the online status of the specified user(s).

 - When the method call succeeds, the SDK returns the [PeersOnlineStatusChanged]([WujiRtmDelegate
 rtmKit:PeersOnlineStatusChanged:]) callback to report the online status of peers, to whom you
 subscribe.
 - When the online status of the peers, to whom you subscribe, changes, the SDK returns the
 [PeersOnlineStatusChanged]([WujiRtmDelegate rtmKit:PeersOnlineStatusChanged:]) callback to report
 whose online status has changed.
 - If the online status of the peers, to whom you subscribe, changes when the SDK is reconnecting to
 the server, the SDK returns the [PeersOnlineStatusChanged]([WujiRtmDelegate
 rtmKit:PeersOnlineStatusChanged:]) callback to report whose online status has changed when
 successfully reconnecting to the server.

 **NOTE**

 - When you log out of the Wuji RTM system, all the status that you subscribe to will be cleared. To
 keep the original subscription after you re-log in the system, you need to redo the whole
 subscription process.
 - When the SDK reconnects to the server from the state of being interupted, the SDK automatically
 subscribes to the peers and states before the interruption without human intervention.

 @param peerIds User IDs of the specified users.
 @param completionBlock [WujiRtmSubscriptionRequestBlock](WujiRtmSubscriptionRequestBlock) returns
 the result of this method call.
 */
- (void)subscribePeersOnlineStatus:(NSArray<NSString *> *_Nonnull)peerIds
                        completion:(WujiRtmSubscriptionRequestBlock _Nullable)completionBlock;

/**
 Unsubscribes from the online status of the specified user(s).

 @param peerIds User IDs of the specified users.
 @param completionBlock WujiRtmUnsubscriptionRequestBlock returns the result of this method call.
 */
- (void)unsubscribePeersOnlineStatus:(NSArray<NSString *> *_Nonnull)peerIds
                          completion:(WujiRtmSubscriptionRequestBlock _Nullable)completionBlock;

/**
 Gets a list of the peers, to whose specific status you have subscribed.

 @param option The status type, to which you have subscribed. See WujiRtmPeerSubscriptionOptions.
 @param completionBlock
 [WujiRtmQueryPeersBySubscriptionOptionBlock](WujiRtmQueryPeersBySubscriptionOptionBlock) returns
 the result of this method call.
 */
- (void)queryPeersBySubscriptionOption:(WujiRtmPeerSubscriptionOptions)option
                            completion:(WujiRtmQueryPeersBySubscriptionOptionBlock _Nullable)
                                           completionBlock;

/**
 Provides the technical preview functionalities or special customizations by configuring the SDK
 with JSON options.

 **NOTE**

 The JSON options are not public by default. Wuji is working on making commonly used JSON options
 public in a standard way. Contact [support@wuji.io](mailto:support@wuji.io) for more information.

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
 - Ensure that you call this method immediately after calling the [initWithAppId]([WujiRtmKit
 initWithAppId:delegate:]) method, otherwise the output log may be incomplete.
 - The default log file location is as follows:
   - iOS: `App Sandbox/Library/caches/wujirtm.log`
   - macOS
    - Sandbox enabled: `App Sandbox/Library/Logs/wujirtm.log`, for example
 `/Users/<username>/Library/Containers/<App Bundle Identifier>/Data/Library/Logs/wujirtm.log`.
    - Sandbox disabled: `~/Library/Logs/wujirtm.log`.

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

 @param filter The log filter level. See WujiRtmLogFilter.
 @return - 0: Success.
 - &ne;0: Failure.
 */
- (int)setLogFilters:(WujiRtmLogFilter)filter;

/**
 Gets the version of the Wuji RTM SDK.

 @return The RTM SDK version.
 */
+ (NSString *)getSDKVersion;

@end

#pragma mark channel

/**
Error codes related to sending a channel message.
 */
typedef NS_ENUM(NSInteger, WujiRtmSendChannelMessageErrorCode) {

  /**
0: The server receives the channel message.
   */
  WujiRtmSendChannelMessageErrorOk = 0,

  /**
1: The user fails to send the channel message state.
   */
  WujiRtmSendChannelMessageErrorFailure = 1,

  /**
2: The SDK does not receive a response from the server in 10 seconds. The current timeout is set as
10 seconds. Possible reasons: The user is in the `WujiRtmConnectionStateAborted` or
`WujiRtmConnectionStateReconnecting` state.
   */
  WujiRtmSendChannelMessageErrorTimeout = 2,

  /**
3: The method call frequency exceeds the limit of 60 queries per second (channel and peer messages
taken together).
  */
  WujiRtmSendChannelMessageTooOften = 3,

  /**
4: The message is null or exceeds 32 KB in length.
   */
  WujiRtmSendChannelMessageInvalidMessage = 4,

  /**
101: The SDK is not initialized.
   */
  WujiRtmSendChannelMessageErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before sending out a channel message.
   */
  WujiRtmSendChannelMessageNotLoggedIn = 102,
};

/**
Error codes related to joining a channel.
 */
typedef NS_ENUM(NSInteger, WujiRtmJoinChannelErrorCode) {

  /**
0: The user joins the channel successfully.
   */
  WujiRtmJoinChannelErrorOk = 0,

  /**
1: The user fails to join the channel.
   */
  WujiRtmJoinChannelErrorFailure = 1,

  /**
2: **RESERVED FOR FUTURE USE**
   */
  WujiRtmJoinChannelErrorRejected = 2,

  /**
3: The user fails to join the channel because the argument is invalid.
   */
  WujiRtmJoinChannelErrorInvalidArgument = 3,

  /**
4: A timeout occurs when joining the channel. The current timeout is set as five seconds. Possible
reasons: The user is in the `WujiRtmConnectionStateAborted` or `WujiRtmConnectionStateReconnecting`
state.
   */
  WujiRtmJoinChannelErrorTimeout = 4,

  /**
5: The number of the RTM channels you are in exceeds the limit of 20.
   */
  WujiRtmJoinChannelErrorExceedLimit = 5,

  /**
6: The user is joining or has joined the channel.
   */
  WujiRtmJoinChannelErrorAlreadyJoined = 6,

  /**
7: The method call frequency exceeds the limit of 50 queries every three seconds.
   */
  WujiRtmJoinChannelErrorTooOften = 7,

  /**
8: The method call frequency exceeds the limit of 2 queries per 5 seconds for the same channel.
   */
  WujiRtmJoinSameChannelErrorTooOften = 8,

  /**
101: The SDK is not initialized.
   */
  WujiRtmJoinChannelErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before joining the channel.
   */
  WujiRtmJoinChannelErrorNotLoggedIn = 102,
};

/**
Error codes related to leaving a channel.
 */
typedef NS_ENUM(NSInteger, WujiRtmLeaveChannelErrorCode) {

  /**
0: The user leaves the channel successfully.
   */
  WujiRtmLeaveChannelErrorOk = 0,

  /**
1: The user fails to leave the channel.
   */
  WujiRtmLeaveChannelErrorFailure = 1,

  /**
2: **RESERVED FOR FUTURE USE**
   */
  WujiRtmLeaveChannelErrorRejected = 2,

  /**
3: The user is not in the channel.
   */
  WujiRtmLeaveChannelErrorNotInChannel = 3,

  /**
101: The SDK is not initialized.
   */
  WujiRtmLeaveChannelErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before leaving the channel.
   */
  WujiRtmLeaveChannelErrorNotLoggedIn = 102,
};

/**
Error codes related to retrieving a channel member list.
*/
typedef NS_ENUM(NSInteger, WujiRtmGetMembersErrorCode) {

  /**
0: The user retrieves a member list of the channel successfully.
   */
  WujiRtmGetMembersErrorOk = 0,

  /**
1: The user fails to retrieve a member list of the channel.
   */
  WujiRtmGetMembersErrorFailure = 1,

  /**
2: **RESERVED FOR FUTURE USE**
   */
  WujiRtmGetMembersErrorRejected = 2,

  /**
3: A timeout occurs when retreiving a member list of the channel. The current timeout is set as five
seconds. Possible reasons: The user is in the `WujiRtmConnectionStateAborted` or
`WujiRtmConnectionStateReconnecting` state.
   */
  WujiRtmGetMembersErrorTimeout = 3,

  /**
4: The method call frequency exceeds the limit of five queries every two seconds.
   */
  WujiRtmGetMembersErrorTooOften = 4,

  /**
5: The user is not in channel.
   */
  WujiRtmGetMembersErrorNotInChannel = 5,

  /**
101: The SDK is not initialized.
   */
  WujiRtmGetMembersErrorNotInitialized = 101,

  /**
102: The user does not call the [loginByToken]([WujiRtmKit loginByToken:user:completion:]) method,
or the method call of [loginByToken]([WujiRtmKit loginByToken:user:completion:]) does not succeed
before retrieving a member list.
   */
  WujiRtmGetMembersErrorNotLoggedIn = 102,
};

/**
Attributes of an Wuji RTM channel member.
 */
__attribute__((visibility("default"))) @interface WujiRtmMember : NSObject

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
 Returns the result of the [joinWithCompletion]([WujiRtmChannel joinWithCompletion:]) method call.
 <p><i>errorCode:</i> See WujiRtmJoinChannelErrorCode for the error codes.
 */
typedef void (^WujiRtmJoinChannelBlock)(WujiRtmJoinChannelErrorCode errorCode);

/**
 Returns the result of the [leaveWithCompletion]([WujiRtmChannel leaveWithCompletion:]) method call.
 <p><i>errorCode:</i> See WujiRtmLeaveChannelErrorCode for the error codes.
 */
typedef void (^WujiRtmLeaveChannelBlock)(WujiRtmLeaveChannelErrorCode errorCode);

/** Returns the result of the [sendMessage]([WujiRtmChannel sendMessage:completion:]) method call.
 * <p><i>errorCode:</i> See WujiRtmSendChannelMessageErrorCode for the error codes.
 */
typedef void (^WujiRtmSendChannelMessageBlock)(WujiRtmSendChannelMessageErrorCode errorCode);

/**
 Returns the result of the [getMembersWithCompletion]([WujiRtmChannel getMembersWithCompletion:])
 method call. <p><li><i>members:</i> The member list. See WujiRtmMember. <li><i>errorCode:</i> See
 WujiRtmGetMembersErrorCode for the error codes.
*/
typedef void (^WujiRtmGetMembersBlock)(NSArray<WujiRtmMember *> *_Nullable members,
                                       WujiRtmGetMembersErrorCode errorCode);

/**
 The WujiRtmChannelDelegate protocol enables callback event notifications to your app.

 The SDK uses delegate callbacks in the WujiRtmChannelDelegate protocol to report
 WujiRtmChannelDelegate runtime events to the app.
 */
@protocol WujiRtmChannelDelegate <NSObject>
@optional

/**
 Occurs when a user joins the channel.

 When a remote user calls the [joinWithCompletion]([WujiRtmChannel joinWithCompletion:]) method and
 successfully joins the channel, the local user receives this callback.

 **NOTE**

 This callback is disabled when the number of the channel members exceeds 512.

 @param channel The channel that the user joins. See WujiRtmChannel.
 @param member The user joining the channel. See WujiRtmMember.
 */
- (void)channel:(WujiRtmChannel *_Nonnull)channel memberJoined:(WujiRtmMember *_Nonnull)member;

/**
 Occurs when a channel member leaves the channel.

 When a remote channel member calls the [leaveWithCompletion]([WujiRtmChannel leaveWithCompletion:])
 method and successfully leaves the channel, the local user receives this callback.

 **NOTE**

 This callback is disabled when the number of the channel members exceeds 512.

 @param channel The channel that the user leaves. See WujiRtmChannel.
 @param member The channel member that leaves the channel. See WujiRtmMember.
 */
- (void)channel:(WujiRtmChannel *_Nonnull)channel memberLeft:(WujiRtmMember *_Nonnull)member;

/**
 Occurs when receiving a channel message.

 When a remote channel member calls the [sendMessage]([WujiRtmChannel sendMessage:completion:])
 method and successfully sends out a channel message, the local user receives this callback.

 @param channel The channel, to which the local user belongs. See WujiRtmChannel.
 @param message The received channel message. See WujiRtmMessage. Ensure that you check the `type`
 property when receiving the message instance: If the message type is `WujiRtmMessageTypeRaw`, you
 need to downcast the received instance from WujiRtmMessage to WujiRtmRawMessage. See
 WujiRtmMessageType.
 @param member The message sender. See WujiRtmMember.
 */
- (void)channel:(WujiRtmChannel *_Nonnull)channel
    messageReceived:(WujiRtmMessage *_Nonnull)message
         fromMember:(WujiRtmMember *_Nonnull)member;

/**
 Occurs when receiving a channel file message.

 @param channel The channel, to which the local user belongs. See WujiRtmChannel.
 @param message The received channel file message. See WujiRtmFileMessage".
 @param member The message sender. See WujiRtmMember.
 */
- (void)channel:(WujiRtmChannel *_Nonnull)channel
    fileMessageReceived:(WujiRtmFileMessage *_Nonnull)message
             fromMember:(WujiRtmMember *_Nonnull)member;

/**
 Occurs when receiving a channel image message.

 @param channel The channel, to which the local user belongs. See WujiRtmChannel.
 @param message The received channel image message. See WujiRtmImageMessage.
 @param member The message sender. See WujiRtmMember.
 */
- (void)channel:(WujiRtmChannel *_Nonnull)channel
    imageMessageReceived:(WujiRtmImageMessage *_Nonnull)message
              fromMember:(WujiRtmMember *_Nonnull)member;

/**
 Occurs when channel attributes are updated, and returns all attributes of the channel.

 **NOTE**

 This callback is enabled only when the user, who updates the attributes of the channel, sets
 [enableNotificationToChannelMembers]([WujiRtmChannelAttributeOptions
 enableNotificationToChannelMembers]) as YES. Also note that this flag is valid only within the
 current channel attribute method call.

 @param channel The channel, to which the local user belongs. See WujiRtmChannel.
 @param attributes An array of WujiRtmChannelAttribute. See WujiRtmChannelAttribute.
 */
- (void)channel:(WujiRtmChannel *_Nonnull)channel
    attributeUpdate:(NSArray<WujiRtmChannelAttribute *> *_Nonnull)attributes;

/**
 Occurs when the number of the channel members changes, and returns the new number.

 **NOTE**

 - When the number of channel members &le; 512, the SDK returns this callback when the number
 changes and at a MAXIMUM speed of once per second.
 - When the number of channel members exceeds 512, the SDK returns this callback when the number
 changes and at a MAXIMUM speed of once every three seconds.
 - You will receive this callback when successfully joining an RTM channel, so Agore recommends
 implementing this callback to receive timely updates on the number of the channel members.

 @param channel The channel, to which the local user belongs. See WujiRtmChannel.
 @param count Member count of this channel.
 */
- (void)channel:(WujiRtmChannel *_Nonnull)channel memberCount:(int)count;

@end

/**
 Wuji RTM channel methods.
 */
__attribute__((visibility("default"))) @interface WujiRtmChannel : NSObject

/**
 An [WujiRtmKit](WujiRtmKit) instance.
 */
@property(atomic, readonly, nonnull) WujiRtmKit *kit;

/**
 WujiRtmChannelDelegate enables Wuji RTM channel callback event notifications to your app.
 */
@property(nonatomic, weak, nullable) id<WujiRtmChannelDelegate> channelDelegate;

/**
 Joins a channel.

 **NOTE**

 You can join a maximum of 20 RTM channels at the same time. When the number of the channels you
join exceeds the limit, you receive the `WujiRtmJoinChannelErrorCodeExceedLimit` error code.

 - The [WujiRtmJoinChannelBlock](WujiRtmJoinChannelBlock) callback returns the result of this method
call.
 - When the local user successfully joins the channel, all remote users in the channel receive the
[memberJoined]([WujiRtmChannelDelegate channel:memberJoined:]) callback.

@param completionBlock [WujiRtmJoinChannelBlock](WujiRtmJoinChannelBlock) returns the result of this
method call. See WujiRtmJoinChannelErrorCode for the error codes.
 */
- (void)joinWithCompletion:(WujiRtmJoinChannelBlock _Nullable)completionBlock;

/**
 Leaves a channel.

 - The [WujiRtmLeaveChannelBlock](WujiRtmLeaveChannelBlock) callback returns the result of this
 method call.
 - When the local user successfully leaves the channel, all remote users in the channel receive the
 [memberLeft]([WujiRtmChannelDelegate channel:memberLeft:]) callback.

 @param completionBlock [WujiRtmLeaveChannelBlock](WujiRtmLeaveChannelBlock) returns the result of
 this method call. See WujiRtmLeaveChannelErrorCode for the error codes.
 */
- (void)leaveWithCompletion:(WujiRtmLeaveChannelBlock _Nullable)completionBlock;

/**
 **DEPRECATED** Allows a channel member to send a message to all members in the channel.

 Wuji does not recommend using this method for sending a channel message. Use
 [sendMessage]([WujiRtmChannel sendMessage:sendMessageOptions:completion:]) instead.

 - The [WujiRtmSendChannelMessageBlock](WujiRtmSendChannelMessageBlock) callback returns the result
 of this method call.
 - When the message arrives, all remote members in the channel receive the
 [messageReceived]([WujiRtmChannelDelegate channel:messageReceived:fromMember:]) callback.

 **NOTE**

 You can send messages, including peer-to-peer and channel messages, at a maximum speed of 60
 queries per second.

 @param message The message to be sent. See [WujiRtmMessage](WujiRtmMessage).
 @param completionBlock [WujiRtmSendChannelMessageBlock](WujiRtmSendChannelMessageBlock) returns the
 result of this method call. See WujiRtmSendChannelMessageErrorCode for the error codes.
 */
- (void)sendMessage:(WujiRtmMessage *_Nonnull)message
         completion:(WujiRtmSendChannelMessageBlock _Nullable)completionBlock;

/**
 Allows a channel member to send a message to all members in the channel.

 - The [WujiRtmSendChannelMessageBlock](WujiRtmSendChannelMessageBlock) callback returns the result
 of this method call.
 - When the message arrives, all remote members in the channel receive the
 [messageReceived]([WujiRtmChannelDelegate channel:messageReceived:fromMember:]) callback.

 **NOTE**

 You can send messages, including peer-to-peer and channel messages, at a maximum speed of 60
 queries per second.

 @param message The message to be sent. See [WujiRtmMessage](WujiRtmMessage).
 @param options Options when sending a channel message. See WujiRtmSendMessageOptions.
 @param completionBlock [WujiRtmSendChannelMessageBlock](WujiRtmSendChannelMessageBlock) returns the
 result of this method call. See WujiRtmSendChannelMessageErrorCode for the error codes.
 */
- (void)sendMessage:(WujiRtmMessage *_Nonnull)message
    sendMessageOptions:(WujiRtmSendMessageOptions *_Nonnull)options
            completion:(WujiRtmSendChannelMessageBlock _Nullable)completionBlock;

/**
 Retrieves a member list of the channel.

 **NOTE**

 You can call this method at a maximum speed of five queries every two seconds.

 @param completionBlock [WujiRtmGetMembersBlock](WujiRtmGetMembersBlock) returns the result of this
 method call (the member list if success). See WujiRtmGetMembersErrorCode for the error codes.
 */
- (void)getMembersWithCompletion:(WujiRtmGetMembersBlock _Nullable)completionBlock;
@end
