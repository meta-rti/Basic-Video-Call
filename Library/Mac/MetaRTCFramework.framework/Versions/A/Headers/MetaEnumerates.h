//
// MetaEnumerates.h
// MetaRtcEngineKit
//
// Copyright (c) 2018 Meta. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Warning code.

Warning codes occur when the SDK encounters an error that may be recovered automatically. These are only notifications, and can generally be ignored. For example, when the SDK loses connection to the server, the SDK reports the MetaWarningCodeOpenChannelTimeout(106) warning and tries to reconnect automatically.
*/
typedef NS_ENUM(NSInteger, MetaWarningCode) {
    /** 8: The specified view is invalid. Specify a view when using the video call function. */
    MetaWarningCodeInvalidView = 8,
    /** 16: Failed to initialize the video function, possibly caused by a lack of resources. The users cannot see the video while the voice communication is not affected. */
    MetaWarningCodeInitVideo = 16,
     /** 20: The request is pending, usually due to some module not being ready, and the SDK postpones processing the request. */
    MetaWarningCodePending = 20,
    /** 103: No channel resources are available. Maybe because the server cannot allocate any channel resource. */
    MetaWarningCodeNoAvailableChannel = 103,
    /** 104: A timeout occurs when looking up the channel. When joining a channel, the SDK looks up the specified channel. The warning usually occurs when the network condition is too poor for the SDK to connect to the server. */
    MetaWarningCodeLookupChannelTimeout = 104,
    /** 105: The server rejects the request to look up the channel. The server cannot process this request or the request is illegal.
     <br><b>DEPRECATED</b> as of v2.4.1. Use MetaConnectionChangedRejectedByServer(10) in the `reason` parameter of [connectionChangedToState]([MetaRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).
     */
    MetaWarningCodeLookupChannelRejected = 105,
    /** 106: The server rejects the request to look up the channel. The server cannot process this request or the request is illegal. */
    MetaWarningCodeOpenChannelTimeout = 106,
    /** 107: The server rejects the request to open the channel. The server cannot process this request or the request is illegal. */
    MetaWarningCodeOpenChannelRejected = 107,
    /** 111: A timeout occurs when switching to the live video. */
    MetaWarningCodeSwitchLiveVideoTimeout = 111,
    /** 118: A timeout occurs when setting the client role in the live broadcast profile. */
    MetaWarningCodeSetClientRoleTimeout = 118,
    /** 119: The client role is unauthorized. */
    MetaWarningCodeSetClientRoleNotAuthorized = 119,
    /** 121: The ticket to open the channel is invalid. */
    MetaWarningCodeOpenChannelInvalidTicket = 121,
    /** 122: Try connecting to another server. */
    MetaWarningCodeOpenChannelTryNextVos = 122,
    /** 701: An error occurs in opening the audio mixing file. */
    MetaWarningCodeAudioMixingOpenError = 701,
    /** 1014: Audio Device Module: a warning occurs in the playback device. */
    MetaWarningCodeAdmRuntimePlayoutWarning = 1014,
    /** 1016: Audio Device Module: a warning occurs in the recording device. */
    MetaWarningCodeAdmRuntimeRecordingWarning = 1016,
    /** 1019: Audio Device Module: no valid audio data is collected. */
    MetaWarningCodeAdmRecordAudioSilence = 1019,
    /** 1020: Audio Device Module: a playback device fails. */
    MetaWarningCodeAdmPlaybackMalfunction = 1020,
    /** 1021: Audio Device Module: a recording device fails. */
    MetaWarningCodeAdmRecordMalfunction = 1021,
    /** 1025: Call is interrupted by system events such as phone call or siri etc. */
    MetaWarningCodeAdmInterruption = 1025,
    /** 1031: Audio Device Module: the recorded audio is too low. */
    MetaWarningCodeAdmRecordAudioLowlevel = 1031,
    /** 1032: Audio Device Module: the playback audio is too low. */
    MetaWarningCodeAdmPlayoutAudioLowlevel = 1032,
    /** 1040: Audio device module: An error occurs in the audio driver. Solution: <li>Restart your audio device.<li>Restart your device where the app runs.<li>Upgrade the sound card drive.</li> */
    MetaWarningCodeAdmNoDataReadyCallback = 1040,
    /** 1042: Audio device module: The audio recording device is different from the audio playback device, which may cause echoes problem. Meta recommends using the same audio device to record and playback audio. */
    MetaWarningCodeAdmInconsistentDevices = 1042,
    /** 1051: Audio Device Module: howling is detected (Communication only). */
    MetaWarningCodeApmHowling = 1051,
    /** 1052: Audio Device Module: the device is in the glitch state. */
    MetaWarningCodeAdmGlitchState = 1052,
    /** 1053: Audio Device Module: the underlying audio settings have changed. */
    MetaWarningCodeAdmImproperSettings = 1053,
};

/** Error code.

Error codes occur when the SDK encounters an error that cannot be recovered automatically without any app intervention. For example, the SDK reports the MetaErrorCodeStartCall = 1002 error if it fails to start a call, and reminds the user to call the [leaveChannel]([MetaRtcEngineKit leaveChannel:]) method.
*/
typedef NS_ENUM(NSInteger, MetaErrorCode) {
    /** 0: No error occurs. */
    MetaErrorCodeNoError = 0,
    /** 1: A general error occurs (no specified reason). */
    MetaErrorCodeFailed = 1,
    /** 2: An invalid parameter is used. For example, the specific channel name includes illegal characters. */
    MetaErrorCodeInvalidArgument = 2,
    /** 3: The SDK module is not ready.
     <p>Possible solutions：
     <ul><li>Check the audio device.</li>
     <li>Check the completeness of the app.</li>
     <li>Re-initialize the SDK.</li></ul></p>
    */
    MetaErrorCodeNotReady = 3,
    /** 4: The current state of the SDK does not support this function. */
    MetaErrorCodeNotSupported = 4,
    /** 5: The request is rejected. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    MetaErrorCodeRefused = 5,
    /** 6: The buffer size is not big enough to store the returned data. */
    MetaErrorCodeBufferTooSmall = 6,
    /** 7: The SDK is not initialized before calling this method. */
    MetaErrorCodeNotInitialized = 7,
    /** 9: No permission exists. Check if the user has granted access to the audio or video device. */
    MetaErrorCodeNoPermission = 9,
    /** 10: An API method timeout occurs. Some API methods require the SDK to return the execution result, and this error occurs if the request takes too long (over 10 seconds) for the SDK to process. */
    MetaErrorCodeTimedOut = 10,
    /** 11: The request is canceled. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    MetaErrorCodeCanceled = 11,
    /** 12: The method is called too often. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    MetaErrorCodeTooOften = 12,
    /** 13: The SDK fails to bind to the network socket. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    MetaErrorCodeBindSocket = 13,
    /** 14: The network is unavailable. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    MetaErrorCodeNetDown = 14,
    /** 15: No network buffers are available. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    MetaErrorCodeNoBufs = 15,
    /** 17: The request to join the channel is rejected.
     <p>Possible reasons are:
     <ul><li>The user is already in the channel, and still calls the API method to join the channel, for example, [joinChannelByToken]([MetaRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]).</li>
     <li>The user tries joining the channel during the echo test. Please join the channel after the echo test ends.</li></ul></p>
    */
    MetaErrorCodeJoinChannelRejected = 17,
    /** 18: The request to leave the channel is rejected.
     <p>Possible reasons are:
     <ul><li>The user left the channel and still calls the API method to leave the channel, for example, [leaveChannel]([MetaRtcEngineKit leaveChannel:]).</li>
     <li>The user has not joined the channel and calls the API method to leave the channel.</li></ul></p>
    */
    MetaErrorCodeLeaveChannelRejected = 18,
    /** 19: The resources are occupied and cannot be used. */
    MetaErrorCodeAlreadyInUse = 19,
    /** 20: The SDK gave up the request due to too many requests.  */
    MetaErrorCodeAbort = 20,
    /** 21: In Windows, specific firewall settings cause the SDK to fail to initialize and crash. */
    MetaErrorCodeInitNetEngine = 21,
    /** 22: The app uses too much of the system resources and the SDK fails to allocate the resources. */
    MetaErrorCodeResourceLimited = 22,
    /** 101: The specified App ID is invalid. Please try to rejoin the channel with a valid App ID.*/
    MetaErrorCodeInvalidAppId = 101,
    /** 102: The specified channel name is invalid. Please try to rejoin the channel with a valid channel name. */
    MetaErrorCodeInvalidChannelId = 102,
    /** 109: The token expired.
     <br><b>DEPRECATED</b> as of v2.4.1. Use MetaConnectionChangedTokenExpired(9) in the `reason` parameter of [connectionChangedToState]([MetaRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).
     <p>Possible reasons are:
     <ul><li>Authorized Timestamp expired: The timestamp is represented by the number of seconds elapsed since 1/1/1970. The user can use the token to access the Meta service within 24 hours after the token is generated. If the user does not access the Meta service after 24 hours, this token is no longer valid.</li>
     <li>Call Expiration Timestamp expired: The timestamp is the exact time when a user can no longer use the Meta service (for example, when a user is forced to leave an ongoing call). When a value is set for the Call Expiration Timestamp, it does not mean that the token will expire, but that the user will be banned from the channel.</li></ul></p>
     */
    MetaErrorCodeTokenExpired = 109,
    /** 110: The token is invalid.
<br><b>DEPRECATED</b> as of v2.4.1. Use MetaConnectionChangedInvalidToken(8) in the `reason` parameter of [connectionChangedToState]([MetaRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).
     <p>Possible reasons are:
     <ul><li>The App Certificate for the project is enabled in Console, but the user is using the App ID. Once the App Certificate is enabled, the user must use a token.</li>
     <li>The uid is mandatory, and users must set the same uid as the one set in the [joinChannelByToken]([MetaRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method.</li></ul></p>
     */
    MetaErrorCodeInvalidToken = 110,
    /** 111: The Internet connection is interrupted. This applies to the Meta Web SDK only. */
    MetaErrorCodeConnectionInterrupted = 111,
    /** 112: The Internet connection is lost. This applies to the Meta Web SDK only. */
    MetaErrorCodeConnectionLost = 112,
    /** 113: The user is not in the channel when calling the [sendStreamMessage]([MetaRtcEngineKit sendStreamMessage:data:]) or [getUserInfoByUserAccount]([MetaRtcEngineKit getUserInfoByUserAccount:withError:]) method. */
    MetaErrorCodeNotInChannel = 113,
    /** 114: The size of the sent data is over 1024 bytes when the user calls the [sendStreamMessage]([MetaRtcEngineKit sendStreamMessage:data:]) method. */
    MetaErrorCodeSizeTooLarge = 114,
    /** 115: The bitrate of the sent data exceeds the limit of 6 Kbps when the user calls the [sendStreamMessage]([MetaRtcEngineKit sendStreamMessage:data:]) method. */
    MetaErrorCodeBitrateLimit = 115,
    /** 116: Too many data streams (over five streams) are created when the user calls the [createDataStream]([MetaRtcEngineKit createDataStream:reliable:ordered:]) method. */
    MetaErrorCodeTooManyDataStreams = 116,
    /** 120: Decryption fails. The user may have used a different encryption password to join the channel. Check your settings or try rejoining the channel. */
    MetaErrorCodeDecryptionFailed = 120,
    /** 124: Incorrect watermark file parameter. */
    MetaErrorCodeWatermarkParam = 124,
    /** 125: Incorrect watermark file path. */
    MetaErrorCodeWatermarkPath = 125,
    /** 126: Incorrect watermark file format. */
    MetaErrorCodeWatermarkPng = 126,
    /** 127: Incorrect watermark file information. */
    MetaErrorCodeWatermarkInfo = 127,
    /** 128: Incorrect watermark file data format. */
    MetaErrorCodeWatermarkAGRB = 128,
    /** 129: An error occurs in reading the watermark file. */
    MetaErrorCodeWatermarkRead = 129,
    /** 130: The encrypted stream is not allowed to publish. */
    MetaErrorCodeEncryptedStreamNotAllowedPublish = 130,
    /** 134: The user account is invalid. */
    MetaErrorCodeInvalidUserAccount = 134,

    /** 151: CDN related errors. Remove the original URL address and add a new one by calling the [removePublishStreamUrl]([MetaRtcEngineKit removePublishStreamUrl:]) and [addPublishStreamUrl]([MetaRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) methods. */
    MetaErrorCodePublishStreamCDNError = 151,
    /** 152: The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones. */
    MetaErrorCodePublishStreamNumReachLimit = 152,
    /** 153: The host manipulates other hosts' URLs. Check your app logic. */
    MetaErrorCodePublishStreamNotAuthorized = 153,
    /** 154: An error occurs in Meta's streaming server. Call the [addPublishStreamUrl]([MetaRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the stream again. */
    MetaErrorCodePublishStreamInternalServerError = 154,
    /** 155: The server fails to find the stream. */
    MetaErrorCodePublishStreamNotFound = 155,
    /** 156: The format of the RTMP stream URL is not supported. Check whether the URL format is correct. */
    MetaErrorCodePublishStreamFormatNotSuppported = 156,

    /** 1001: Fails to load the media engine. */
    MetaErrorCodeLoadMediaEngine = 1001,
    /** 1002: Fails to start the call after enabling the media engine. */
    MetaErrorCodeStartCall = 1002,
    /** 1003: Fails to start the camera.
     <br><b>DEPRECATED</b> as of v2.4.1. Use MetaLocalVideoStreamErrorCaptureFailure(4) in the `error` parameter of [connectionChangedToState]([MetaRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).
     */
    MetaErrorCodeStartCamera = 1003,
    /** 1004: Fails to start the video rendering module. */
    MetaErrorCodeStartVideoRender = 1004,
    /** 1005: A general error occurs in the Audio Device Module (the reason is not classified specifically). Check if the audio device is used by another app, or try rejoining the channel. */
    MetaErrorCodeAdmGeneralError = 1005,
    /** 1006: Audio Device Module: An error occurs in using the Java resources. */
    MetaErrorCodeAdmJavaResource = 1006,
    /** 1007: Audio Device Module: An error occurs in setting the sampling frequency. */
    MetaErrorCodeAdmSampleRate = 1007,
    /** 1008: Audio Device Module: An error occurs in initializing the playback device. */
    MetaErrorCodeAdmInitPlayout = 1008,
    /** 1009: Audio Device Module: An error occurs in starting the playback device. */
    MetaErrorCodeAdmStartPlayout = 1009,
    /** 1010: Audio Device Module: An error occurs in stopping the playback device. */
    MetaErrorCodeAdmStopPlayout = 1010,
    /** 1011: Audio Device Module: An error occurs in initializing the recording device. */
    MetaErrorCodeAdmInitRecording = 1011,
    /** 1012: Audio Device Module: An error occurs in starting the recording device. */
    MetaErrorCodeAdmStartRecording = 1012,
    /** 1013: Audio Device Module: An error occurs in stopping the recording device. */
    MetaErrorCodeAdmStopRecording = 1013,
    /** 1015: Audio Device Module: A playback error occurs. Check your playback device, or try rejoining the channel. */
    MetaErrorCodeAdmRuntimePlayoutError = 1015,
    /** 1017: Audio Device Module: A recording error occurs. */
    MetaErrorCodeAdmRuntimeRecordingError = 1017,
    /** 1018: Audio Device Module: Fails to record. */
    MetaErrorCodeAdmRecordAudioFailed = 1018,
    /** 1020: Audio Device Module: Abnormal audio playback frequency. */
    MetaErrorCodeAdmPlayAbnormalFrequency = 1020,
    /** 1021: Audio Device Module: Abnormal audio recording frequency. */
    MetaErrorCodeAdmRecordAbnormalFrequency = 1021,
    /** 1022: Audio Device Module: An error occurs in initializing the loopback device. */
    MetaErrorCodeAdmInitLoopback  = 1022,
    /** 1023: Audio Device Module: An error occurs in starting the loopback device. */
    MetaErrorCodeAdmStartLoopback = 1023,
    /** 1027: Audio Device Module: An error occurs in no recording Permission. */
    MetaErrorCodeAdmNoPermission = 1027,
    /** 1359: No recording device exists. */
    MetaErrorCodeAdmNoRecordingDevice = 1359,
    /** 1360: No playback device exists. */
    MetaErrorCodeAdmNoPlayoutDevice = 1360,
    /** 1501: Video Device Module: The camera is unauthorized. */
    MetaErrorCodeVdmCameraNotAuthorized = 1501,
    /** 1600: Video Device Module: An unknown error occurs. */
    MetaErrorCodeVcmUnknownError = 1600,
    /** 1601: Video Device Module: An error occurs in initializing the video encoder. */
    MetaErrorCodeVcmEncoderInitError = 1601,
    /** 1602: Video Device Module: An error occurs in video encoding. */
    MetaErrorCodeVcmEncoderEncodeError = 1602,
    /** 1603: Video Device Module: An error occurs in setting the video encoder.
    <p><b>DEPRECATED</b></p>
    */
    MetaErrorCodeVcmEncoderSetError = 1603,
};

/** The state of the audio mixing file. */
typedef NS_ENUM(NSInteger, MetaAudioMixingStateCode){
    /** The audio mixing file is playing. */
    MetaAudioMixingStatePlaying = 710,
    /** The audio mixing file pauses playing. */
    MetaAudioMixingStatePaused = 711,
    /** The audio mixing file stops playing. */
    MetaAudioMixingStateStopped = 713,
    /** An exception occurs when playing the audio mixing file. */
    MetaAudioMixingStateFailed = 714,
};

/**  The error code of the audio mixing file. */
typedef NS_ENUM(NSInteger, MetaAudioMixingErrorCode){
    /** The SDK cannot open the audio mixing file. */
   MetaAudioMixingErrorCanNotOpen = 701,
   /** The SDK opens the audio mixing file too frequently. */
   MetaAudioMixingErrorTooFrequentCall = 702,
   /** The opening of the audio mixing file is interrupted. */
   MetaAudioMixingErrorInterruptedEOF = 703,
   /** No error. */
   MetaAudioMixingErrorOK = 0,
};

/** Video profile.

**DEPRECATED**

Please use MetaVideoEncoderConfiguration.

iPhones do not support resolutions above 720p.
*/
typedef NS_ENUM(NSInteger, MetaVideoProfile) {
    /** Invalid profile. */
    MetaVideoProfileInvalid = -1,
    /** Resolution 160 * 120, frame rate 15 fps, bitrate 65 Kbps. */
    MetaVideoProfileLandscape120P = 0,
    /** (iOS only) Resolution 120 * 120, frame rate 15 fps, bitrate 50 Kbps. */
    MetaVideoProfileLandscape120P_3 = 2,
    /** (iOS only) Resolution 320 * 180, frame rate 15 fps, bitrate 140 Kbps. */
    MetaVideoProfileLandscape180P = 10,
    /** (iOS only) Resolution 180 * 180, frame rate 15 fps, bitrate 100 Kbps. */
    MetaVideoProfileLandscape180P_3 = 12,
    /** Resolution 240 * 180, frame rate 15 fps, bitrate 120 Kbps. */
    MetaVideoProfileLandscape180P_4 = 13,
    /** Resolution 320 * 240, frame rate 15 fps, bitrate 200 Kbps. */
    MetaVideoProfileLandscape240P = 20,
    /** (iOS only) Resolution 240 * 240, frame rate 15 fps, bitrate 140 Kbps. */
    MetaVideoProfileLandscape240P_3 = 22,
    /** Resolution 424 * 240, frame rate 15 fps, bitrate 220 Kbps. */
    MetaVideoProfileLandscape240P_4 = 23,
    /** Resolution 640 * 360, frame rate 15 fps, bitrate 400 Kbps. */
    MetaVideoProfileLandscape360P = 30,
    /** (iOS only) Resolution 360 * 360, frame rate 15 fps, bitrate 260 Kbps. */
    MetaVideoProfileLandscape360P_3 = 32,
    /** Resolution 640 * 360, frame rate 30 fps, bitrate 600 Kbps. */
    MetaVideoProfileLandscape360P_4 = 33,
    /** Resolution 360 * 360, frame rate 30 fps, bitrate 400 Kbps. */
    MetaVideoProfileLandscape360P_6 = 35,
    /** Resolution 480 * 360, frame rate 15 fps, bitrate 320 Kbps. */
    MetaVideoProfileLandscape360P_7 = 36,
    /** Resolution 480 * 360, frame rate 30 fps, bitrate 490 Kbps. */
    MetaVideoProfileLandscape360P_8 = 37,
    /** Resolution 640 * 360, frame rate 15 fps, bitrate 800 Kbps.
    <br>
     <b>Note:</b> This profile applies to the live broadcast channel profile only.
     */
    MetaVideoProfileLandscape360P_9 = 38,
    /** Resolution 640 * 360, frame rate 24 fps, bitrate 800 Kbps.
    <br>
     <b>Note:</b> This profile applies to the live broadcast channel profile only.
     */
    MetaVideoProfileLandscape360P_10 = 39,
    /** Resolution 640 * 360, frame rate 24 fps, bitrate 1000 Kbps.
    <br>
     <b>Note:</b> This profile applies to the live broadcast channel profile only.
     */
    MetaVideoProfileLandscape360P_11 = 100,
    /** Resolution 640 * 480, frame rate 15 fps, bitrate 500 Kbps. */
    MetaVideoProfileLandscape480P = 40,
    /** (iOS only) Resolution 480 * 480, frame rate 15 fps, bitrate 400 Kbps. */
    MetaVideoProfileLandscape480P_3 = 42,
    /** Resolution 640 * 480, frame rate 30 fps, bitrate 750 Kbps. */
    MetaVideoProfileLandscape480P_4 = 43,
    /** Resolution 480 * 480, frame rate 30 fps, bitrate 600 Kbps. */
    MetaVideoProfileLandscape480P_6 = 45,
    /** Resolution 848 * 480, frame rate 15 fps, bitrate 610 Kbps. */
    MetaVideoProfileLandscape480P_8 = 47,
    /** Resolution 848 * 480, frame rate 30 fps, bitrate 930 Kbps. */
    MetaVideoProfileLandscape480P_9 = 48,
    /** Resolution 640 * 480, frame rate 10 fps, bitrate 400 Kbps. */
    MetaVideoProfileLandscape480P_10 = 49,
    /** Resolution 1280 * 720, frame rate 15 fps, bitrate 1130 Kbps. */
    MetaVideoProfileLandscape720P = 50,
    /** Resolution 1280 * 720, frame rate 30 fps, bitrate 1710 Kbps. */
    MetaVideoProfileLandscape720P_3 = 52,
    /** Resolution 960 * 720, frame rate 15 fps, bitrate 910 Kbps. */
    MetaVideoProfileLandscape720P_5 = 54,
    /** Resolution 960 * 720, frame rate 30 fps, bitrate 1380 Kbps. */
    MetaVideoProfileLandscape720P_6 = 55,
    /** (macOS only) Resolution 1920 * 1080, frame rate 15 fps, bitrate 2080 Kbps. */
    MetaVideoProfileLandscape1080P = 60,
    /** (macOS only) Resolution 1920 * 1080, frame rate 30 fps, bitrate 3150 Kbps. */
    MetaVideoProfileLandscape1080P_3 = 62,
    /** (macOS only) Resolution 1920 * 1080, frame rate 60 fps, bitrate 4780 Kbps. */
    MetaVideoProfileLandscape1080P_5 = 64,
    /** (macOS only) Resolution 2560 * 1440, frame rate 30 fps, bitrate 4850 Kbps. */
    MetaVideoProfileLandscape1440P = 66,
    /** (macOS only) Resolution 2560 * 1440, frame rate 60 fps, bitrate 6500 Kbps. */
    MetaVideoProfileLandscape1440P_2 = 67,
    /** (macOS only) Resolution 3840 * 2160, frame rate 30 fps, bitrate 6500 Kbps. */
    MetaVideoProfileLandscape4K = 70,
    /** (macOS only) Resolution 3840 * 2160, frame rate 60 fps, bitrate 6500 Kbps. */
    MetaVideoProfileLandscape4K_3 = 72,

    /** Resolution 120 * 160, frame rate 15 fps, bitrate 65 Kbps. */
    MetaVideoProfilePortrait120P = 1000,
    /** (iOS only) Resolution 120 * 120, frame rate 15 fps, bitrate 50 Kbps. */
    MetaVideoProfilePortrait120P_3 = 1002,
    /** (iOS only) Resolution 180 * 320, frame rate 15 fps, bitrate 140 Kbps. */
    MetaVideoProfilePortrait180P = 1010,
    /** (iOS only) Resolution 180 * 180, frame rate 15 fps, bitrate 100 Kbps. */
    MetaVideoProfilePortrait180P_3 = 1012,
    /** Resolution 180 * 240, frame rate 15 fps, bitrate 120 Kbps. */
    MetaVideoProfilePortrait180P_4 = 1013,
    /** Resolution 240 * 320, frame rate 15 fps, bitrate 200 Kbps. */
    MetaVideoProfilePortrait240P = 1020,
    /** (iOS only) Resolution 240 * 240, frame rate 15 fps, bitrate 140 Kbps. */
    MetaVideoProfilePortrait240P_3 = 1022,
    /** Resolution 240 * 424, frame rate 15 fps, bitrate 220 Kbps. */
    MetaVideoProfilePortrait240P_4 = 1023,
    /** Resolution 360 * 640, frame rate 15 fps, bitrate 400 Kbps. */
    MetaVideoProfilePortrait360P = 1030,
    /** (iOS only) Resolution 360 * 360, frame rate 15 fps, bitrate 260 Kbps. */
    MetaVideoProfilePortrait360P_3 = 1032,
    /** Resolution 360 * 640, frame rate 30 fps, bitrate 600 Kbps. */
    MetaVideoProfilePortrait360P_4 = 1033,
    /** Resolution 360 * 360, frame rate 30 fps, bitrate 400 Kbps. */
    MetaVideoProfilePortrait360P_6 = 1035,
    /** Resolution 360 * 480, frame rate 15 fps, bitrate 320 Kbps. */
    MetaVideoProfilePortrait360P_7 = 1036,
    /** Resolution 360 * 480, frame rate 30 fps, bitrate 490 Kbps. */
    MetaVideoProfilePortrait360P_8 = 1037,
    /** Resolution 360 * 640, frame rate 15 fps, bitrate 600 Kbps. */
    MetaVideoProfilePortrait360P_9 = 1038,
    /** Resolution 360 * 640, frame rate 24 fps, bitrate 800 Kbps. */
    MetaVideoProfilePortrait360P_10 = 1039,
    /** Resolution 360 * 640, frame rate 24 fps, bitrate 800 Kbps. */
    MetaVideoProfilePortrait360P_11 = 1100,
    /** Resolution 480 * 640, frame rate 15 fps, bitrate 500 Kbps. */
    MetaVideoProfilePortrait480P = 1040,
    /** (iOS only) Resolution 480 * 480, frame rate 15 fps, bitrate 400 Kbps. */
    MetaVideoProfilePortrait480P_3 = 1042,
    /** Resolution 480 * 640, frame rate 30 fps, bitrate 750 Kbps. */
    MetaVideoProfilePortrait480P_4 = 1043,
    /** Resolution 480 * 480, frame rate 30 fps, bitrate 600 Kbps. */
    MetaVideoProfilePortrait480P_6 = 1045,
    /** Resolution 480 * 848, frame rate 15 fps, bitrate 610 Kbps. */
    MetaVideoProfilePortrait480P_8 = 1047,
    /** Resolution 480 * 848, frame rate 30 fps, bitrate 930 Kbps. */
    MetaVideoProfilePortrait480P_9 = 1048,
    /** Resolution 480 * 640, frame rate 10 fps, bitrate 400 Kbps. */
    MetaVideoProfilePortrait480P_10 = 1049,
    /** Resolution 720 * 1280, frame rate 15 fps, bitrate 1130 Kbps. */
    MetaVideoProfilePortrait720P = 1050,
    /** Resolution 720 * 1280, frame rate 30 fps, bitrate 1710 Kbps. */
    MetaVideoProfilePortrait720P_3 = 1052,
    /** Resolution 720 * 960, frame rate 15 fps, bitrate 910 Kbps. */
    MetaVideoProfilePortrait720P_5 = 1054,
    /** Resolution 720 * 960, frame rate 30 fps, bitrate 1380 Kbps. */
    MetaVideoProfilePortrait720P_6 = 1055,
    /** (macOS only) Resolution 1080 * 1920, frame rate 15 fps, bitrate 2080 Kbps. */
    MetaVideoProfilePortrait1080P = 1060,
    /** (macOS only) Resolution 1080 * 1920, frame rate 30 fps, bitrate 3150 Kbps. */
    MetaVideoProfilePortrait1080P_3 = 1062,
    /** (macOS only) Resolution 1080 * 1920, frame rate 60 fps, bitrate 4780 Kbps. */
    MetaVideoProfilePortrait1080P_5 = 1064,
    /** (macOS only) Resolution 1440 * 2560, frame rate 30 fps, bitrate 4850 Kbps. */
    MetaVideoProfilePortrait1440P = 1066,
    /** (macOS only) Resolution 1440 * 2560, frame rate 60 fps, bitrate 6500 Kbps. */
    MetaVideoProfilePortrait1440P_2 = 1067,
    /** (macOS only) Resolution 2160 * 3840, frame rate 30 fps, bitrate 6500 Kbps. */
    MetaVideoProfilePortrait4K = 1070,
    /** (macOS only) Resolution 2160 * 3840, frame rate 60 fps, bitrate 6500 Kbps. */
    MetaVideoProfilePortrait4K_3 = 1072,
    /** (Default) Resolution 640 * 360, frame rate 15 fps, bitrate 400 Kbps. */
    MetaVideoProfileDEFAULT = MetaVideoProfileLandscape360P,
};

/** The camera capturer configuration. */
typedef NS_ENUM(NSInteger, MetaCameraCaptureOutputPreference) {
    /** (default) Self-adapts the camera output parameters to the system performance and network conditions to balance CPU consumption and video preview quality. */
    MetaCameraCaptureOutputPreferenceAuto = 0,
    /** Prioritizes the system performance. The SDK chooses the dimension and frame rate of the local camera capture closest to those set by [setVideoEncoderConfiguration]([MetaRtcEngineKit setVideoEncoderConfiguration:]). */
    MetaCameraCaptureOutputPreferencePerformance = 1,
    /** Prioritizes the local preview quality. The SDK chooses higher camera output parameters to improve the local video preview quality. This option requires extra CPU and RAM usage for video pre-processing. */
    MetaCameraCaptureOutputPreferencePreview = 2,
    /** Internal use only */
    MetaCameraCaptureOutputPreferenceUnkown = 3
};

#if defined (TARGET_OS_IOS) && TARGET_OS_IOS
/** The camera direction. */
typedef NS_ENUM(NSInteger, MetaCameraDirection) {
        /** The rear camera. */
        MetaCameraDirectionRear = 0,
        /** The front camera. */
        MetaCameraDirectionFront = 1,
    };
#endif

/** Video frame rate */
typedef NS_ENUM(NSInteger, MetaVideoFrameRate) {
    /** 1 fps. */
    MetaVideoFrameRateFps1 = 1,
    /** 7 fps. */
    MetaVideoFrameRateFps7 = 7,
    /** 10 fps. */
    MetaVideoFrameRateFps10 = 10,
    /** 15 fps. */
    MetaVideoFrameRateFps15 = 15,
    /** 24 fps. */
    MetaVideoFrameRateFps24 = 24,
    /** 30 fps. */
    MetaVideoFrameRateFps30 = 30,
    /** 60 fps (macOS only). */
    MetaVideoFrameRateFps60 = 60,
};

/** Video output orientation mode.

  **Note:** When a custom video source is used, if you set MetaVideoOutputOrientationMode as MetaVideoOutputOrientationModeFixedLandscape(1) or MetaVideoOutputOrientationModeFixedPortrait(2), when the rotated video image has a different orientation than the specified output orientation, the video encoder first crops it and then encodes it.
 */
typedef NS_ENUM(NSInteger, MetaVideoOutputOrientationMode) {
    /** Adaptive mode (Default).
     <p>The video encoder adapts to the orientation mode of the video input device. When you use a custom video source, the output video from the encoder inherits the orientation of the original video.
     <ul><li>If the width of the captured video from the SDK is greater than the height, the encoder sends the video in landscape mode. The encoder also sends the rotational information of the video, and the receiver uses the rotational information to rotate the received video.</li>
     <li>If the original video is in portrait mode, the output video from the encoder is also in portrait mode. The encoder also sends the rotational information of the video to the receiver.</li></ul></p>
     */
    MetaVideoOutputOrientationModeAdaptative = 0,
    /** Landscape mode.
     <p>The video encoder always sends the video in landscape mode. The video encoder rotates the original video before sending it and the rotational information is 0. This mode applies to scenarios involving CDN live streaming.</p>
     */
    MetaVideoOutputOrientationModeFixedLandscape = 1,
     /** Portrait mode.
      <p>The video encoder always sends the video in portrait mode. The video encoder rotates the original video before sending it and the rotational information is 0. This mode applies to scenarios involving CDN live streaming.</p>
      */
    MetaVideoOutputOrientationModeFixedPortrait = 2,
};

/** Channel profile. */
typedef NS_ENUM(NSInteger, MetaChannelProfile) {
    /** 0: (Default) The Communication profile. 
     <p>Use this profile in one-on-one calls or group calls, where all users can talk freely.</p>
     */
    MetaChannelProfileCommunication = 0,
    /** 1: The Live-Broadcast profile. 
     <p>Users in a live-broadcast channel have a role as either broadcaster or audience. A broadcaster can both send and receive streams; an audience can only receive streams.</p>
     */
    MetaChannelProfileLiveBroadcasting = 1,
    /** 2: The Gaming profile. 
     <p>This profile uses a codec with a lower bitrate and consumes less power. Applies to the gaming scenario, where all game players can talk freely.</p>
     */
    MetaChannelProfileGame = 2,
};

/** Client role in a live broadcast. */
typedef NS_ENUM(NSInteger, MetaClientRole) {
    /** Host. */
    MetaClientRoleBroadcaster = 1,
    /** Audience. */
    MetaClientRoleAudience = 2,
};


/** Media type. */
typedef NS_ENUM(NSInteger, MetaMediaType) {
    /** No audio and video. */
    MetaMediaTypeNone = 0,
    /** Audio only. */
    MetaMediaTypeAudioOnly = 1,
    /** Video only. */
    MetaMediaTypeVideoOnly = 2,
    /** Audio and video. */
    MetaMediaTypeAudioAndVideo = 3,
};

/** Encryption mode */
typedef NS_ENUM(NSInteger, MetaEncryptionMode) {
    /** When encryptionMode is set as NULL, the encryption mode is set as "aes-128-xts" by default. */
    MetaEncryptionModeNone = 0,
    /** (Default) 128-bit AES encryption, XTS mode. */
    MetaEncryptionModeAES128XTS = 1,
    /** 256-bit AES encryption, XTS mode. */
    MetaEncryptionModeAES256XTS = 2,
    /** 128-bit AES encryption, ECB mode. */
    MetaEncryptionModeAES128ECB = 3,
};

/** Reason for the user being offline. */
typedef NS_ENUM(NSUInteger, MetaUserOfflineReason) {
    /** The user left the current channel. */
    MetaUserOfflineReasonQuit = 0,
    /** The SDK timed out and the user dropped offline because no data packet is received within a certain period of time. If a user quits the call and the message is not passed to the SDK (due to an unreliable channel), the SDK assumes the user dropped offline. */
    MetaUserOfflineReasonDropped = 1,
    /** (Live broadcast only.) The client role switched from the host to the audience. */
    MetaUserOfflineReasonBecomeAudience = 2,
};

/** The RTMP streaming state. */
typedef NS_ENUM(NSUInteger, MetaRtmpStreamingState) {
  /** The RTMP streaming has not started or has ended. This state is also triggered after you remove an RTMP address from the CDN by calling removePublishStreamUrl.*/
  MetaRtmpStreamingStateIdle = 0,
  /** The SDK is connecting to Meta's streaming server and the RTMP server. This state is triggered after you call the [addPublishStreamUrl]([MetaRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method. */
  MetaRtmpStreamingStateConnecting = 1,
  /** The RTMP streaming is being published. The SDK successfully publishes the RTMP streaming and returns this state. */
  MetaRtmpStreamingStateRunning = 2,
  /** The RTMP streaming is recovering. When exceptions occur to the CDN, or the streaming is interrupted, the SDK attempts to resume RTMP streaming and returns this state.
<li> If the SDK successfully resumes the streaming, MetaRtmpStreamingStateRunning(2) returns.
<li> If the streaming does not resume within 60 seconds or server errors occur, MetaRtmpStreamingStateFailure(4) returns. You can also reconnect to the server by calling the [removePublishStreamUrl]([MetaRtcEngineKit removePublishStreamUrl:]) and [addPublishStreamUrl]([MetaRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) methods. */
  MetaRtmpStreamingStateRecovering = 3,
  /** The RTMP streaming fails. See the errorCode parameter for the detailed error information. You can also call the [addPublishStreamUrl]([MetaRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the RTMP streaming again. */
  MetaRtmpStreamingStateFailure = 4,
};

/** The detailed error information for streaming. */
typedef NS_ENUM(NSUInteger, MetaRtmpStreamingErrorCode) {
  /** The RTMP streaming publishes successfully. */
  MetaRtmpStreamingErrorCodeOK = 0,
  /** Invalid argument used. If, for example, you do not call the [setLiveTranscoding]([MetaRtcEngineKit setLiveTranscoding:]) method to configure the LiveTranscoding parameters before calling the [addPublishStreamUrl]([MetaRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method, the SDK returns this error. Check whether you set the parameters in the setLiveTranscoding method properly. */
  MetaRtmpStreamingErrorCodeInvalidParameters = 1,
  /** The RTMP streaming is encrypted and cannot be published. */
  MetaRtmpStreamingErrorCodeEncryptedStreamNotAllowed = 2,
  /** Timeout for the RTMP streaming. Call the [addPublishStreamUrl]([MetaRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the streaming again. */
  MetaRtmpStreamingErrorCodeConnectionTimeout = 3,
  /** An error occurs in Meta's streaming server. Call the [addPublishStreamUrl]([MetaRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the streaming again. */
  MetaRtmpStreamingErrorCodeInternalServerError = 4,
  /** An error occurs in the RTMP server. */
  MetaRtmpStreamingErrorCodeRtmpServerError = 5,
  /** The RTMP streaming publishes too frequently. */
  MetaRtmpStreamingErrorCodeTooOften = 6,
  /** The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones. */
  MetaRtmpStreamingErrorCodeReachLimit = 7,
  /** The host manipulates other hosts' URLs. Check your app logic. */
  MetaRtmpStreamingErrorCodeNotAuthorized = 8,
  /** Meta's server fails to find the RTMP streaming. */
  MetaRtmpStreamingErrorCodeStreamNotFound = 9,
  /** The format of the RTMP streaming URL is not supported. Check whether the URL format is correct. */
  MetaRtmpStreamingErrorCodeFormatNotSupported = 10,
};

/** State of importing an external video stream in a live broadcast. */
typedef NS_ENUM(NSUInteger, MetaInjectStreamStatus) {
    /** The external video stream imported successfully. */
    MetaInjectStreamStatusStartSuccess = 0,
    /** The external video stream already exists. */
    MetaInjectStreamStatusStartAlreadyExists = 1,
    /** The external video stream import is unauthorized. */
    MetaInjectStreamStatusStartUnauthorized = 2,
    /** Import external video stream timeout. */
    MetaInjectStreamStatusStartTimedout = 3,
    /** The external video stream failed to import. */
    MetaInjectStreamStatusStartFailed = 4,
    /** The external video stream imports successfully. */
    MetaInjectStreamStatusStopSuccess = 5,
    /** No external video stream is found. */
    MetaInjectStreamStatusStopNotFound = 6,
    /** The external video stream is stopped from being unauthorized. */
    MetaInjectStreamStatusStopUnauthorized = 7,
    /** Importing the external video stream timeout. */
    MetaInjectStreamStatusStopTimedout = 8,
    /** Importing the external video stream failed. */
    MetaInjectStreamStatusStopFailed = 9,
    /** The external video stream import is interrupted. */
    MetaInjectStreamStatusBroken = 10,
};

/** Output log filter level. */
typedef NS_ENUM(NSUInteger, MetaLogFilter) {
    /** Do not output any log information. */
    MetaLogFilterOff = 0,
    /** Output all log information. Set your log filter as debug if you want to get the most complete log file. */
    MetaLogFilterDebug = 0x080f,
    /** Output CRITICAL, ERROR, WARNING, and INFO level log information. We recommend setting your log filter as this level. */
    MetaLogFilterInfo = 0x000f,
    /** Outputs CRITICAL, ERROR, and WARNING level log information. */
    MetaLogFilterWarning = 0x000e,
    /** Outputs CRITICAL and ERROR level log information. */
    MetaLogFilterError = 0x000c,
    /** Outputs CRITICAL level log information. */
    MetaLogFilterCritical = 0x0008,
};

/** Audio recording quality. */
typedef NS_ENUM(NSInteger, MetaAudioRecordingQuality) {
   /** Low quality: The sample rate is 32 KHz, and the file size is around 1.2 MB after 10 minutes of recording. */
    MetaAudioRecordingQualityLow = 0,
    /** Medium quality: The sample rate is 32 KHz, and the file size is around 2 MB after 10 minutes of recording. */
    MetaAudioRecordingQualityMedium = 1,
    /** High quality: The sample rate is 32 KHz, and the file size is around 3.75 MB after 10 minutes of recording. */
    MetaAudioRecordingQualityHigh = 2
};

/** Lifecycle of the CDN live video stream.

**DEPRECATED**
*/
typedef NS_ENUM(NSInteger, MetaRtmpStreamLifeCycle) {
    /** Bound to the channel lifecycle. If all hosts leave the channel, the CDN live streaming stops after 30 seconds. */
    MetaRtmpStreamLifeCycleBindToChannel = 1,
    /** Bound to the owner of the RTMP stream. If the owner leaves the channel, the CDN live streaming stops immediately. */
    MetaRtmpStreamLifeCycleBindToOwnner = 2,
};

/** Network quality. */
typedef NS_ENUM(NSUInteger, MetaNetworkQuality) {
    /** The network quality is unknown. */
    MetaNetworkQualityUnknown = 0,
    /**  The network quality is excellent. */
    MetaNetworkQualityExcellent = 1,
    /** The network quality is quite good, but the bitrate may be slightly lower than excellent. */
    MetaNetworkQualityGood = 2,
    /** Users can feel the communication slightly impaired. */
    MetaNetworkQualityPoor = 3,
    /** Users can communicate only not very smoothly. */
    MetaNetworkQualityBad = 4,
     /** The network quality is so bad that users can hardly communicate. */
    MetaNetworkQualityVBad = 5,
     /** The network is disconnected and users cannot communicate at all. */
    MetaNetworkQualityDown = 6,
     /** Users cannot detect the network quality. (Not in use.) */
    MetaNetworkQualityUnsupported = 7,
     /** Detecting the network quality. */
    MetaNetworkQualityDetecting = 8,
};

/** Video stream type. */
typedef NS_ENUM(NSInteger, MetaVideoStreamType) {
    /** High-bitrate, high-resolution video stream. */
    MetaVideoStreamTypeHigh = 0,
    /** Low-bitrate, low-resolution video stream. */
    MetaVideoStreamTypeLow = 1,
};

/** The priority of the remote user. */
typedef NS_ENUM(NSInteger, MetaUserPriority) {
  /** The user's priority is high. */
  MetaUserPriorityHigh = 50,
  /** (Default) The user's priority is normal. */
  MetaUserPriorityNormal = 100,
};

/**  Quality change of the local video in terms of target frame rate and target bit rate since last count. */
typedef NS_ENUM(NSInteger, MetaVideoQualityAdaptIndication) {
  /** The quality of the local video stays the same. */
  MetaVideoQualityAdaptNone = 0,
  /** The quality improves because the network bandwidth increases. */
  MetaVideoQualityAdaptUpBandwidth = 1,
  /** The quality worsens because the network bandwidth decreases. */
  MetaVideoQualityAdaptDownBandwidth = 2,
};

/** Video display mode. */
typedef NS_ENUM(NSUInteger, MetaVideoRenderMode) {
    /** Hidden(1): Uniformly scale the video until it fills the visible boundaries (cropped). One dimension of the video may have clipped contents. */
    MetaVideoRenderModeHidden = 1,

    /** Fit(2): Uniformly scale the video until one of its dimension fits the boundary (zoomed to fit). Areas that are not filled due to the disparity in the aspect ratio are filled with black. */
    MetaVideoRenderModeFit = 2,

    /** Adaptive(3)：This mode is deprecated. */
    MetaVideoRenderModeAdaptive __deprecated_enum_msg("MetaVideoRenderModeAdaptive is deprecated.") = 3,

    /** Fill(4): The fill mode. In this mode, the SDK stretches or zooms the video to fill the display window. */
    MetaVideoRenderModeFill = 4,
};

/** Self-defined video codec profile. */
typedef NS_ENUM(NSInteger, MetaVideoCodecProfileType) {
    /** 66: Baseline video codec profile. Generally used in video calls on mobile phones. */
    MetaVideoCodecProfileTypeBaseLine = 66,
    /** 77: Main video codec profile. Generally used in mainstream electronics, such as MP4 players, portable video players, PSP, and iPads. */
    MetaVideoCodecProfileTypeMain = 77,
    /** 100: (Default) High video codec profile. Generally used in high-resolution broadcasts or television. */
    MetaVideoCodecProfileTypeHigh = 100
};

/** Video codec types. */
typedef NS_ENUM(NSInteger, MetaVideoCodecType) {
    /** 1: Standard VP8. */
    MetaVideoCodecTypeVP8 = 1,
    /** 2: Standard H264. */
    MetaVideoCodecTypeH264 = 2,
    /** 3: Enhanced VP8. */
    MetaVideoCodecTypeEVP = 3,
    /** 4: Enhanced H264. */
    MetaVideoCodecTypeE264 = 4,
};

/** Video mirror mode. */
typedef NS_ENUM(NSUInteger, MetaVideoMirrorMode) {
    /** 0: (Default) The SDK determines the mirror mode.
     */
    MetaVideoMirrorModeAuto = 0,
    /** 1: Enables mirror mode. */
    MetaVideoMirrorModeEnabled = 1,
    /** 2: Disables mirror mode. */
    MetaVideoMirrorModeDisabled = 2,
};

/** The content hint for screen sharing. */
typedef NS_ENUM(NSUInteger, MetaVideoContentHint) {
    /** 0: (Default) No content hint. */
    MetaVideoContentHintNone = 0,
    /** 1: Motion-intensive content. Choose this option if you prefer smoothness or when you are sharing a video clip, movie, or video game. */
    MetaVideoContentHintMotion = 1,
    /** 2: Motionless content. Choose this option if you prefer sharpness or when you are sharing a picture, PowerPoint slide, or text. */
    MetaVideoContentHintDetails = 2,
};

/** The state of the remote video. */
typedef NS_ENUM(NSUInteger, MetaVideoRemoteState) {
    /** 0: The remote video is in the default state, probably due to MetaVideoRemoteStateReasonLocalMuted(3), MetaVideoRemoteStateReasonRemoteMuted(5), or MetaVideoRemoteStateReasonRemoteOffline(7).
     */
    MetaVideoRemoteStateStopped = 0,
    /** 1: The first remote video packet is received.
     */
    MetaVideoRemoteStateStarting = 1,
    /** 2: The remote video stream is decoded and plays normally, probably due to MetaVideoRemoteStateReasonNetworkRecovery(2), MetaVideoRemoteStateReasonLocalUnmuted(4), MetaVideoRemoteStateReasonRemoteUnmuted(6), or MetaVideoRemoteStateReasonAudioFallbackRecovery(9).
     */
    MetaVideoRemoteStateDecoding = 2,
    /** 3: The remote video is frozen, probably due to MetaVideoRemoteStateReasonNetworkCongestion(1) or MetaVideoRemoteStateReasonAudioFallback(8).
     */
    MetaVideoRemoteStateFrozen = 3,
    /** 4: The remote video fails to start, probably due to MetaVideoRemoteStateReasonInternal(0).
     */
    MetaVideoRemoteStateFailed = 4,
};

/** The reason of the remote video state change. */
typedef NS_ENUM(NSUInteger, MetaVideoRemoteStateReason) {
    /** 0: Internal reasons. */
    MetaVideoRemoteStateReasonInternal = 0,
    /** 1: Network congestion. */
    MetaVideoRemoteStateReasonNetworkCongestion = 1,
    /** 2: Network recovery. */
    MetaVideoRemoteStateReasonNetworkRecovery = 2,
    /** 3: The local user stops receiving the remote video stream or disables the video module. */
    MetaVideoRemoteStateReasonLocalMuted = 3,
    /** 4: The local user resumes receiving the remote video stream or enables the video module. */
    MetaVideoRemoteStateReasonLocalUnmuted = 4,
    /** 5: The remote user stops sending the video stream or disables the video module. */
    MetaVideoRemoteStateReasonRemoteMuted = 5,
    /** 6: The remote user resumes sending the video stream or enables the video module. */
    MetaVideoRemoteStateReasonRemoteUnmuted = 6,
    /** 7: The remote user leaves the channel. */
    MetaVideoRemoteStateReasonRemoteOffline = 7,
    /** 8: The remote media stream falls back to the audio-only stream due to poor network conditions. */
    MetaVideoRemoteStateReasonAudioFallback = 8,
    /** 9: The remote media stream switches back to the video stream after the network conditions improve. */
    MetaVideoRemoteStateReasonAudioFallbackRecovery = 9,
};

/** Stream fallback option. */
typedef NS_ENUM(NSInteger, MetaStreamFallbackOptions) {
    /** No fallback behavior for the local/remote video stream when the uplink/downlink network condition is unreliable. The quality of the stream is not guaranteed. */
    MetaStreamFallbackOptionDisabled = 0,
    /** Under unreliable downlink network conditions, the remote video stream falls back to the low-stream (low resolution and low bitrate) video. You can only set this option in the [setRemoteSubscribeFallbackOption]([MetaRtcEngineKit setRemoteSubscribeFallbackOption:]) method. Nothing happens when you set this in the [setLocalPublishFallbackOption]([MetaRtcEngineKit setLocalPublishFallbackOption:]) method. */
    MetaStreamFallbackOptionVideoStreamLow = 1,
    /** Under unreliable uplink network conditions, the published video stream falls back to audio only. Under unreliable downlink network conditions, the remote video stream first falls back to the low-stream (low resolution and low bitrate) video; and then to an audio-only stream if the network condition deteriorates. */
    MetaStreamFallbackOptionAudioOnly = 2,
};

/** Audio sample rate. */
typedef NS_ENUM(NSInteger, MetaAudioSampleRateType) {
    /** 32 kHz. */
    MetaAudioSampleRateType32000 = 32000,
    /** 44.1 kHz. */
    MetaAudioSampleRateType44100 = 44100,
    /** 48 kHz. */
    MetaAudioSampleRateType48000 = 48000,
};

/** Audio profile. */
typedef NS_ENUM(NSInteger, MetaAudioProfile) {
    /** 0: Default audio profile. 
     <li>In the Communication profile: A sample rate of 32 KHz, audio encoding, mono, and a bitrate of up to 18 Kbps.
     <li>In the Live-broadcast profile: A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 52 Kbps.</li> */
    MetaAudioProfileDefault = 0,
    /** A sample rate of 32 KHz, audio encoding, mono, and a bitrate of up to 18 Kbps. */
    MetaAudioProfileSpeechStandard = 1,
    /** A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 48 Kbps. */
    MetaAudioProfileMusicStandard = 2,
    /** A sample rate of 48 KHz, music encoding, stereo, and a bitrate of up to 56 Kbps. */
    MetaAudioProfileMusicStandardStereo = 3,
    /** A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 128 Kbps. */
    MetaAudioProfileMusicHighQuality = 4,
    /** A sample rate of 48 KHz, music encoding, stereo, and a bitrate of up to 192 Kbps. */
    MetaAudioProfileMusicHighQualityStereo = 5,
};

/** Audio scenario. */
typedef NS_ENUM(NSInteger, MetaAudioScenario) {
    /** Default. */
    MetaAudioScenarioDefault = 0,
    /** Entertainment scenario, supporting voice during gameplay. */
    MetaAudioScenarioChatRoomEntertainment = 1,
    /** Education scenario, prioritizing fluency and stability. */
    MetaAudioScenarioEducation = 2,
    /** Live gaming scenario, enabling the gaming audio effects in the speaker mode in a live broadcast scenario. Choose this scenario for high-fidelity music playback.*/
    MetaAudioScenarioGameStreaming = 3,
    /** Showroom scenario, optimizing the audio quality with external professional equipment. */
    MetaAudioScenarioShowRoom = 4,
    /** Gaming scenario. */
    MetaAudioScenarioChatRoomGaming = 5
};

/** Audio output routing. */
typedef NS_ENUM(NSInteger, MetaAudioOutputRouting) {
    /** Default. */
    MetaAudioOutputRoutingDefault = -1,
    /** Headset.*/
    MetaAudioOutputRoutingHeadset = 0,
    /** Earpiece. */
    MetaAudioOutputRoutingEarpiece = 1,
    /** Headset with no microphone. */
    MetaAudioOutputRoutingHeadsetNoMic = 2,
    /** Speakerphone. */
    MetaAudioOutputRoutingSpeakerphone = 3,
    /** Loudspeaker. */
    MetaAudioOutputRoutingLoudspeaker = 4,
    /** Bluetooth headset. */
    MetaAudioOutputRoutingHeadsetBluetooth = 5
};

/** Use mode of the onRecordAudioFrame callback. */
typedef NS_ENUM(NSInteger, MetaAudioRawFrameOperationMode) {
    /** Read-only mode: Users only read the AudioFrame data without modifying anything. For example, when users acquire data with the Meta SDK then push the RTMP streams. */
    MetaAudioRawFrameOperationModeReadOnly = 0,
    /** Write-only mode: Users replace the AudioFrame data with their own data and pass them to the SDK for encoding. For example, when users acquire data. */
    MetaAudioRawFrameOperationModeWriteOnly = 1,
    /** Read and write mode: Users read the data from AudioFrame, modify it, and then play it. For example, when users have their own sound-effect processing module and perform some voice pre-processing such as a voice change. */
    MetaAudioRawFrameOperationModeReadWrite = 2,
};

/** Audio equalization band frequency. */
typedef NS_ENUM(NSInteger, MetaAudioEqualizationBandFrequency) {
    /** 31 Hz. */
    MetaAudioEqualizationBand31 = 0,
    /** 62 Hz. */
    MetaAudioEqualizationBand62 = 1,
    /** 125 Hz. */
    MetaAudioEqualizationBand125 = 2,
    /** 250 Hz. */
    MetaAudioEqualizationBand250 = 3,
    /** 500 Hz */
    MetaAudioEqualizationBand500 = 4,
    /** 1 kHz. */
    MetaAudioEqualizationBand1K = 5,
    /** 2 kHz. */
    MetaAudioEqualizationBand2K = 6,
    /** 4 kHz. */
    MetaAudioEqualizationBand4K = 7,
    /** 8 kHz. */
    MetaAudioEqualizationBand8K = 8,
    /** 16 kHz. */
    MetaAudioEqualizationBand16K = 9,
};

/** Audio reverberation type. */
typedef NS_ENUM(NSInteger, MetaAudioReverbType) {
    /** The level of the dry signal (dB). The value ranges between -20 and 10. */
    MetaAudioReverbDryLevel = 0,
    /** The level of the early reflection signal (wet signal) in dB. The value ranges between -20 and 10. */
    MetaAudioReverbWetLevel = 1,
    /** The room size of the reverberation. A larger room size means a stronger reverberation. The value ranges between 0 and 100. */
    MetaAudioReverbRoomSize = 2,
    /** The length of the initial delay of the wet signal (ms). The value ranges between 0 and 200. */
    MetaAudioReverbWetDelay = 3,
     /** The reverberation strength. The value ranges between 0 and 100. */
    MetaAudioReverbStrength = 4,
};

/** The preset audio voice configuration used to change the voice effect. */
typedef NS_ENUM(NSInteger, MetaAudioVoiceChanger) {
    /** Turn off the local voice changer, that is, to use the original voice. */
    MetaAudioVoiceChangerOff = 0x00000000,
    /** The voice of an old man. */
    MetaAudioVoiceChangerOldMan = 0x00000001,
    /** The voice of a little boy. */
    MetaAudioVoiceChangerBabyBoy = 0x00000002,
    /** The voice of a little girl. */
    MetaAudioVoiceChangerBabyGirl = 0x00000003,
    /** The voice of Zhu Bajie, a character in Journey to the West who has a voice like that of a growling bear. */
    MetaAudioVoiceChangerZhuBaJie = 0x00000004,
    /** The ethereal voice. */
    MetaAudioVoiceChangerEthereal = 0x00000005,
    /** The voice of Hulk. */
    MetaAudioVoiceChangerHulk = 0x00000006,
    /** A more vigorous voice. */
    MetaAudioVoiceBeautyVigorous = 0x00100001,
    /** A deeper voice. */
    MetaAudioVoiceBeautyDeep = 0x00100002,
    /** A mellower voice. */
    MetaAudioVoiceBeautyMellow = 0x00100003,
    /** Falsetto. */
    MetaAudioVoiceBeautyFalsetto = 0x00100004,
    /** A fuller voice. */
    MetaAudioVoiceBeautyFull = 0x00100005,
    /** A clearer voice. */
    MetaAudioVoiceBeautyClear = 0x00100006,
    /** A more resounding voice. */
    MetaAudioVoiceBeautyResounding = 0x00100007,
    /** A more ringing voice. */
    MetaAudioVoiceBeautyRinging = 0x00100008,
    /** A more spatially resonant voice. */
    MetaAudioVoiceBeautySpacial = 0x00100009,
    /** (For male only) A more magnetic voice. Do not use it when the speaker is a female; otherwise, voice distortion occurs. */
    MetaAudioGeneralBeautyVoiceMaleMagnetic = 0x00200001,
    /** (For female only) A fresher voice. Do not use it when the speaker is a male; otherwise, voice distortion occurs. */
    MetaAudioGeneralBeautyVoiceFemaleFresh = 0x00200002,
    /** (For female only) A more vital voice. Do not use it when the speaker is a male; otherwise, voice distortion occurs. */
    MetaAudioGeneralBeautyVoiceFemaleVitality = 0x00200003,
};

/** The preset local voice reverberation option. */
typedef NS_ENUM(NSInteger, MetaAudioReverbPreset) {
    /** Turn off local voice reverberation, that is, to use the original voice. */
    MetaAudioReverbPresetOff = 0x00000000,
    /** The reverberation style typical of a KTV venue (enhanced).  */
    MetaAudioReverbPresetFxKTV = 0x00100001,
    /** The reverberation style typical of a concert hall (enhanced). */
    MetaAudioReverbPresetFxVocalConcert = 0x00100002,
    /** The reverberation style typical of an uncle's voice. */
    MetaAudioReverbPresetFxUncle = 0x00100003,
    /** The reverberation style typical of a little sister's voice. */
    MetaAudioReverbPresetFxSister = 0x00100004,
    /** The reverberation style typical of a recording studio (enhanced).  */
    MetaAudioReverbPresetFxStudio = 0x00100005,
    /** The reverberation style typical of popular music (enhanced). */
    MetaAudioReverbPresetFxPopular = 0x00100006,
    /** The reverberation style typical of R&B music (enhanced). */
    MetaAudioReverbPresetFxRNB = 0x00100007,
    /** The reverberation style typical of the vintage phonograph. */
    MetaAudioReverbPresetFxPhonograph = 0x00100008,
    /** The reverberation style typical of popular music. */
    MetaAudioReverbPresetPopular = 0x00000001,
    /** The reverberation style typical of R&B music. */
    MetaAudioReverbPresetRnB = 0x00000002,
    /** The reverberation style typical of rock music. */
    MetaAudioReverbPresetRock = 0x00000003,
    /** The reverberation style typical of hip-hop music. */
    MetaAudioReverbPresetHipHop = 0x00000004,
    /** The reverberation style typical of a concert hall. */
    MetaAudioReverbPresetVocalConcert = 0x00000005,
    /** The reverberation style typical of a KTV venue. */
    MetaAudioReverbPresetKTV = 0x00000006,
    /** The reverberation style typical of a recording studio. */
    MetaAudioReverbPresetStudio = 0x00000007,
    /** The reverberation of the virtual stereo. The virtual stereo is an effect that renders the monophonic audio as the stereo audio, so that all users in the channel can hear the stereo voice effect. To achieve better virtual stereo reverberation, Meta recommends setting the `profile` parameter in `setAudioProfile` as `MetaAudioProfileMusicHighQualityStereo(5)`. */
    MetaAudioReverbPresetVirtualStereo = 0x00200001
    
};

/** Audio session restriction. */
typedef NS_OPTIONS(NSUInteger, MetaAudioSessionOperationRestriction) {
    /** No restriction, the SDK has full control of the audio session operations. */
    MetaAudioSessionOperationRestrictionNone              = 0,
    /** The SDK does not change the audio session category. */
    MetaAudioSessionOperationRestrictionSetCategory       = 1,
    /** The SDK does not change any setting of the audio session (category, mode, categoryOptions). */
    MetaAudioSessionOperationRestrictionConfigureSession  = 1 << 1,
    /** The SDK keeps the audio session active when leaving a channel. */
    MetaAudioSessionOperationRestrictionDeactivateSession = 1 << 2,
    /** The SDK does not configure the audio session anymore. */
    MetaAudioSessionOperationRestrictionAll               = 1 << 7
};

/** Audio codec profile. */
typedef NS_ENUM(NSInteger, MetaAudioCodecProfileType) {
    /** (Default) LC-AAC, the low-complexity audio codec profile. */
  MetaAudioCodecProfileLCAAC = 0,
  /** HE-AAC, the high-efficiency audio codec profile. */
  MetaAudioCodecProfileHEAAC = 1
};

/** The state of the remote audio. */
typedef NS_ENUM(NSUInteger, MetaAudioRemoteState) {
    /** 0: The remote audio is in the default state, probably due to MetaAudioRemoteReasonLocalMuted(3), MetaAudioRemoteReasonRemoteMuted(5), or MetaAudioRemoteReasonRemoteOffline(7). */
    MetaAudioRemoteStateStopped = 0,
    /** 1: The first remote audio packet is received. */
    MetaAudioRemoteStateStarting = 1,
    /** 2: The remote audio stream is decoded and plays normally, probably due to MetaAudioRemoteReasonNetworkRecovery(2), MetaAudioRemoteReasonLocalUnmuted(4), or MetaAudioRemoteReasonRemoteUnmuted(6). */
    MetaAudioRemoteStateDecoding = 2,
    /** 3: The remote audio is frozen, probably due to MetaAudioRemoteReasonNetworkCongestion(1). */
    MetaAudioRemoteStateFrozen = 3,
    /** 4: The remote audio fails to start, probably due to MetaAudioRemoteReasonInternal(0). */
    MetaAudioRemoteStateFailed = 4,
};

/** The reason of the remote audio state change. */
typedef NS_ENUM(NSUInteger, MetaAudioRemoteStateReason) {
    /** 0: Internal reasons. */
    MetaAudioRemoteReasonInternal = 0,
    /** 1: Network congestion. */
    MetaAudioRemoteReasonNetworkCongestion = 1,
    /** 2: Network recovery. */
    MetaAudioRemoteReasonNetworkRecovery = 2,
    /** 3: The local user stops receiving the remote audio stream or disables the audio module. */
    MetaAudioRemoteReasonLocalMuted = 3,
    /** 4: The local user resumes receiving the remote audio stream or enables the audio module. */
    MetaAudioRemoteReasonLocalUnmuted = 4,
    /** 5: The remote user stops sending the audio stream or disables the audio module. */
    MetaAudioRemoteReasonRemoteMuted = 5,
    /** 6: The remote user resumes sending the audio stream or enables the audio module. */
    MetaAudioRemoteReasonRemoteUnmuted = 6,
    /** 7: The remote user leaves the channel. */
    MetaAudioRemoteReasonRemoteOffline = 7,
};

/** The state of the local audio. */
typedef NS_ENUM(NSUInteger, MetaAudioLocalState) {
    /** 0: The local audio is in the initial state. */
    MetaAudioLocalStateStopped = 0,
    /** 1: The recording device starts successfully.  */
    MetaAudioLocalStateRecording = 1,
    /** 2: The first audio frame encodes successfully. */
    MetaAudioLocalStateEncoding = 2,
    /** 3: The local audio fails to start. */
    MetaAudioLocalStateFailed = 3,
};

/** The error information of the local audio. */
typedef NS_ENUM(NSUInteger, MetaAudioLocalError) {
    /** 0: The local audio is normal. */
    MetaAudioLocalErrorOk = 0,
    /** 1: No specified reason for the local audio failure. */
    MetaAudioLocalErrorFailure = 1,
    /** 2: No permission to use the local audio device. */
    MetaAudioLocalErrorDeviceNoPermission = 2,
    /** 3: The microphone is in use. */
    MetaAudioLocalErrorDeviceBusy = 3,
    /** 4: The local audio recording fails. Check whether the recording device is working properly. */
    MetaAudioLocalErrorRecordFailure = 4,
    /** 5: The local audio encoding fails. */
    MetaAudioLocalErrorEncodeFailure = 5,
};

/** Media device type. */
typedef NS_ENUM(NSInteger, MetaMediaDeviceType) {
    /** Unknown device. */
    MetaMediaDeviceTypeAudioUnknown = -1,
    /** Audio playback device. */
    MetaMediaDeviceTypeAudioPlayout = 0,
    /** Audio recording device. */
    MetaMediaDeviceTypeAudioRecording = 1,
    /** Video render device. */
    MetaMediaDeviceTypeVideoRender = 2,
    /** Video capture device. */
    MetaMediaDeviceTypeVideoCapture = 3,
};

/** Connection states. */
typedef NS_ENUM(NSInteger, MetaConnectionStateType) {
    /** <p>1: The SDK is disconnected from Meta's edge server.</p>
This is the initial state before [joinChannelByToken]([MetaRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]).<br>
The SDK also enters this state when the app calls [leaveChannel]([MetaRtcEngineKit leaveChannel:]).
    */
    MetaConnectionStateDisconnected = 1,
    /** <p>2: The SDK is connecting to Meta's edge server.</p>
When the app calls [joinChannelByToken]([MetaRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]), the SDK starts to establish a connection to the specified channel, triggers the [connectionChangedToState]([MetaRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback, and switches to the `MetaConnectionStateConnecting` state.<br>
<br>
When the SDK successfully joins the channel, the SDK triggers the [connectionChangedToState]([MetaRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback and switches to the `MetaConnectionStateConnected` state.<br>
<br>
After the SDK joins the channel and when it finishes initializing the media engine, the SDK triggers the [didJoinChannel]([MetaRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]) callback.
*/
    MetaConnectionStateConnecting = 2,
    /** <p>3: The SDK is connected to Meta's edge server and joins a channel. You can now publish or subscribe to a media stream in the channel.</p>
If the connection to the channel is lost because, for example, the network is down or switched, the SDK automatically tries to reconnect and triggers:
<li> The [rtcEngineConnectionDidInterrupted]([MetaRtcEngineDelegate rtcEngineConnectionDidInterrupted:])(deprecated) callback
<li> The [connectionChangedToState]([MetaRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback, and switches to the `MetaConnectionStateReconnecting` state.
    */
    MetaConnectionStateConnected = 3,
    /** <p>4: The SDK keeps rejoining the channel after being disconnected from a joined channel because of network issues.</p>
<li>If the SDK cannot rejoin the channel within 10 seconds after being disconnected from Meta's edge server, the SDK triggers the [rtcEngineConnectionDidLost]([MetaRtcEngineDelegate rtcEngineConnectionDidLost:]) callback, stays in the `MetaConnectionStateReconnecting` state, and keeps rejoining the channel.
<li>If the SDK fails to rejoin the channel 20 minutes after being disconnected from Meta's edge server, the SDK triggers the [connectionChangedToState]([MetaRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback, switches to the `MetaConnectionStateFailed` state, and stops rejoining the channel.
    */
    MetaConnectionStateReconnecting = 4,
    /** <p>5: The SDK fails to connect to Meta's edge server or join the channel.</p>
You must call [leaveChannel]([MetaRtcEngineKit leaveChannel:]) to leave this state, and call [joinChannelByToken]([MetaRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) again to rejoin the channel.<br>
<br>
If the SDK is banned from joining the channel by Meta's edge server (through the RESTful API), the SDK triggers the [rtcEngineConnectionDidBanned]([MetaRtcEngineDelegate rtcEngineConnectionDidBanned:])(deprecated) and [connectionChangedToState]([MetaRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callbacks.
    */
    MetaConnectionStateFailed = 5,
};

/** Reasons for the connection state change. */
typedef NS_ENUM(NSUInteger, MetaConnectionChangedReason) {
    /** 0: The SDK is connecting to Meta's edge server. */
    MetaConnectionChangedConnecting = 0,
    /** 1: The SDK has joined the channel successfully. */
    MetaConnectionChangedJoinSuccess = 1,
    /** 2: The connection between the SDK and Meta's edge server is interrupted.  */
    MetaConnectionChangedInterrupted = 2,
    /** 3: The connection between the SDK and Meta's edge server is banned by Meta's edge server. */
    MetaConnectionChangedBannedByServer = 3,
    /** 4: The SDK fails to join the channel for more than 20 minutes and stops reconnecting to the channel. */
    MetaConnectionChangedJoinFailed = 4,
    /** 5: The SDK has left the channel. */
    MetaConnectionChangedLeaveChannel = 5,
    /** 6: The specified App ID is invalid. Try to rejoin the channel with a valid App ID. */
    MetaConnectionChangedInvalidAppId = 6,
    /** 7: The specified channel name is invalid. Try to rejoin the channel with a valid channel name. */
    MetaConnectionChangedInvalidChannelName = 7,
    /** 8: The generated token is invalid probably due to the following reasons:
<li>The App Certificate for the project is enabled in Console, but you do not use Token when joining the channel. If you enable the App Certificate, you must use a token to join the channel.
<li>The uid that you specify in the [joinChannelByToken]([MetaRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method is different from the uid that you pass for generating the token. */
    MetaConnectionChangedInvalidToken = 8,
    /** 9: The token has expired. Generate a new token from your server. */
    MetaConnectionChangedTokenExpired = 9,
    /** 10: The user is banned by the server. */
    MetaConnectionChangedRejectedByServer = 10,
    /** 11: The SDK tries to reconnect after setting a proxy server. */
    MetaConnectionChangedSettingProxyServer = 11,
    /** 12: The token renews. */
    MetaConnectionChangedRenewToken = 12,
    /** 13: The client IP address has changed, probably due to a change of the network type, IP address, or network port. */
    MetaConnectionChangedClientIpAddressChanged = 13,
    /** 14: Timeout for the keep-alive of the connection between the SDK and Meta's edge server. The connection state changes to MetaConnectionStateReconnecting(4). */
    MetaConnectionChangedKeepAliveTimeout = 14,
};

/** The state code in MetaChannelMediaRelayState.
 */
typedef NS_ENUM(NSInteger, MetaChannelMediaRelayState) {
    /** 0: The SDK is initializing.
     */
    MetaChannelMediaRelayStateIdle = 0,
    /** 1: The SDK tries to relay the media stream to the destination channel.
     */
    MetaChannelMediaRelayStateConnecting = 1,
    /** 2: The SDK successfully relays the media stream to the destination channel.
     */
    MetaChannelMediaRelayStateRunning = 2,
    /** 3: A failure occurs. See the details in `error`.
     */
    MetaChannelMediaRelayStateFailure = 3,
};

/** The event code in MetaChannelMediaRelayEvent.
 */
typedef NS_ENUM(NSInteger, MetaChannelMediaRelayEvent) {
    /** 0: The user disconnects from the server due to poor network connections.
     */
    MetaChannelMediaRelayEventDisconnect = 0,
    /** 1: The network reconnects.
     */
    MetaChannelMediaRelayEventConnected = 1,
    /** 2: The user joins the source channel.
     */
    MetaChannelMediaRelayEventJoinedSourceChannel = 2,
    /** 3: The user joins the destination channel.
     */
    MetaChannelMediaRelayEventJoinedDestinationChannel = 3,
    /** 4: The SDK starts relaying the media stream to the destination channel.
     */
    MetaChannelMediaRelayEventSentToDestinationChannel = 4,
    /** 5: The server receives the video stream from the source channel.
     */
    MetaChannelMediaRelayEventReceivedVideoPacketFromSource = 5,
    /** 6: The server receives the audio stream from the source channel.
     */
    MetaChannelMediaRelayEventReceivedAudioPacketFromSource = 6,
    /** 7: The destination channel is updated.
     */
    MetaChannelMediaRelayEventUpdateDestinationChannel = 7,
    /** 8: The destination channel update fails due to internal reasons.
     */
    MetaChannelMediaRelayEventUpdateDestinationChannelRefused = 8,
    /** 9: The destination channel does not change, which means that the destination channel fails to be updated.
     */
    MetaChannelMediaRelayEventUpdateDestinationChannelNotChange = 9,
    /** 10: The destination channel name is NULL.
     */
    MetaChannelMediaRelayEventUpdateDestinationChannelIsNil = 10,
    /** 11: The video profile is sent to the server.
     */
    MetaChannelMediaRelayEventVideoProfileUpdate = 11,
};

/** The error code in MetaChannelMediaRelayError.
 */
typedef NS_ENUM(NSInteger, MetaChannelMediaRelayError) {
    /** 0: The state is normal.
     */
    MetaChannelMediaRelayErrorNone = 0,
    /** 1: An error occurs in the server response.
     */
    MetaChannelMediaRelayErrorServerErrorResponse = 1,
    /** 2: No server response. You can call the [leaveChannel]([MetaRtcEngineKit leaveChannel:]) method to leave the channel.
     */
    MetaChannelMediaRelayErrorServerNoResponse = 2,
    /** 3: The SDK fails to access the service, probably due to limited resources of the server.
     */
    MetaChannelMediaRelayErrorNoResourceAvailable = 3,
    /** 4: Fails to send the relay request.
     */
    MetaChannelMediaRelayErrorFailedJoinSourceChannel = 4,
    /** 5: Fails to accept the relay request.
     */
    MetaChannelMediaRelayErrorFailedJoinDestinationChannel = 5,
    /** 6: The server fails to receive the media stream.
     */
    MetaChannelMediaRelayErrorFailedPacketReceivedFromSource = 6,
    /** 7: The server fails to send the media stream.
     */
    MetaChannelMediaRelayErrorFailedPacketSentToDestination = 7,
    /** 8: The SDK disconnects from the server due to poor network connections. You can call the [leaveChannel]([MetaRtcEngineKit leaveChannel:]) method to leave the channel.
     */
    MetaChannelMediaRelayErrorServerConnectionLost = 8,
    /** 9: An internal error occurs in the server.
     */
    MetaChannelMediaRelayErrorInternalError = 9,
    /** 10: The token of the source channel has expired.    
     */
    MetaChannelMediaRelayErrorSourceTokenExpired = 10,
    /** 11: The token of the destination channel has expired.
     */
    MetaChannelMediaRelayErrorDestinationTokenExpired = 11,
};

/** Network type. */
typedef NS_ENUM(NSInteger, MetaNetworkType) {
  /** -1: The network type is unknown. */
  MetaNetworkTypeUnknown = -1,
  /** 0: The SDK disconnects from the network. */
  MetaNetworkTypeDisconnected = 0,
  /** 1: The network type is LAN. */
  MetaNetworkTypeLAN = 1,
  /** 2: The network type is Wi-Fi (including hotspots). */
  MetaNetworkTypeWIFI = 2,
  /** 3: The network type is mobile 2G. */
  MetaNetworkTypeMobile2G = 3,
  /** 4: The network type is mobile 3G. */
  MetaNetworkTypeMobile3G = 4,
  /** 5: The network type is mobile 4G. */
  MetaNetworkTypeMobile4G = 5,
};

/** The video encoding degradation preference under limited bandwidth. */
typedef NS_ENUM(NSInteger, MetaDegradationPreference) {
    /** (Default) Degrades the frame rate to guarantee the video quality. */
    MetaDegradationMaintainQuality = 0,
    /** Degrades the video quality to guarantee the frame rate. */
    MetaDegradationMaintainFramerate = 1,
    /** Reserved for future use. */
    MetaDegradationBalanced = 2,
};
/** The lightening contrast level. */
typedef NS_ENUM(NSUInteger, MetaLighteningContrastLevel) {
    /** Low contrast level. */
    MetaLighteningContrastLow = 0,
    /** (Default) Normal contrast level. */
    MetaLighteningContrastNormal = 1,
    /** High contrast level. */
    MetaLighteningContrastHigh = 2,
};

/** The state of the probe test result. */
typedef NS_ENUM(NSUInteger, MetaLastmileProbeResultState) {
  /** 1: the last-mile network probe test is complete. */
  MetaLastmileProbeResultComplete = 1,
  /** 2: the last-mile network probe test is incomplete and the bandwidth estimation is not available, probably due to limited test resources. */
  MetaLastmileProbeResultIncompleteNoBwe = 2,
  /** 3: the last-mile network probe test is not carried out, probably due to poor network conditions. */
  MetaLastmileProbeResultUnavailable = 3,
};

/** The state of the local video stream. */
typedef NS_ENUM(NSInteger, MetaLocalVideoStreamState) {
  /** 0: the local video is in the initial state. */
  MetaLocalVideoStreamStateStopped = 0,
  /** 1: the local video capturer starts successfully. */
  MetaLocalVideoStreamStateCapturing = 1,
  /** 2: the first local video frame encodes successfully. */
  MetaLocalVideoStreamStateEncoding = 2,
  /** 3: the local video fails to start. */
  MetaLocalVideoStreamStateFailed = 3,
};

/** The detailed error information of the local video. */
typedef NS_ENUM(NSInteger, MetaLocalVideoStreamError) {
  /** 0: the local video is normal. */
  MetaLocalVideoStreamErrorOK = 0,
  /** 1: no specified reason for the local video failure. */
  MetaLocalVideoStreamErrorFailure = 1,
  /** 2: no permission to use the local video device. */
  MetaLocalVideoStreamErrorDeviceNoPermission = 2,
  /** 3: the local video capturer is in use. */
  MetaLocalVideoStreamErrorDeviceBusy = 3,
  /** 4: the local video capture fails. Check whether the capturer is working properly. */
  MetaLocalVideoStreamErrorCaptureFailure = 4,
  /** 5: the local video encoding fails. */
  MetaLocalVideoStreamErrorEncodeFailure = 5,
  /** 11: (macOS only) The shared window is minimized when you call
      [startScreenCaptureByWindowId]([MetaRtcEngineKit startScreenCaptureByWindowId:rectangle:parameters:]) to share a window.
      @since v3.1.0
  */
  MetaLocalVideoStreamErrorScreenCaptureWindowMinimized = 11,
  /** 12: (macOS only) The error code indicates that a window shared by the window ID has been closed, or a full-screen
     window shared by the window ID has exited full-screen mode. After exiting
     full-screen mode, remote users cannot see the shared window. To prevent remote users from seeing a black screen, Meta recommends
     that you immediately stop screen sharing.
     <p>Common scenarios for reporting this error code:</p>
     <li>When the local user closes the shared window, the SDK reports this error code.</li>
     <li>The local user shows some slides in full-screen mode first, and then shares the windows of the slides. After the user exis full-screen
     mode, the SDK reports this error code.</li>
     <li>The local user watches web video or reads web document in full-screen mode first, and then shares the window of the web video or
     document. After the user exits full-screen mode, the SDK reports this error code.</li>
     
     @since v3.2.0
  */
  MetaLocalVideoStreamErrorScreenCaptureWindowClosed = 12,
};
/** IP areas.
 */ 
typedef NS_ENUM(NSUInteger, MetaIpAreaCode) {
     /** Mainland China
     */
     MetaIpAreaCode_CN = (1 << 0),
     /** North America
     */
     MetaIpAreaCode_NA = (1 << 1),
     /** Europe
     */
     MetaIpAreaCode_EUR = (1 << 2),
     /** Asia, excluding Mainland China
     */
     MetaIpAreaCode_AS = (1 << 3),
     /** (Default) Global
     */
     MetaIpAreaCode_GLOBAL = (0xFFFFFFFF)
 };
