//
// WujiEnumerates.h
// WujiRtcEngineKit
//
// Copyright (c) 2018 Wuji. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Warning code.

Warning codes occur when the SDK encounters an error that may be recovered automatically. These are only notifications, and can generally be ignored. For example, when the SDK loses connection to the server, the SDK reports the WujiWarningCodeOpenChannelTimeout(106) warning and tries to reconnect automatically.
*/
typedef NS_ENUM(NSInteger, WujiWarningCode) {
    /** 8: The specified view is invalid. Specify a view when using the video call function. */
    WujiWarningCodeInvalidView = 8,
    /** 16: Failed to initialize the video function, possibly caused by a lack of resources. The users cannot see the video while the voice communication is not affected. */
    WujiWarningCodeInitVideo = 16,
     /** 20: The request is pending, usually due to some module not being ready, and the SDK postpones processing the request. */
    WujiWarningCodePending = 20,
    /** 103: No channel resources are available. Maybe because the server cannot allocate any channel resource. */
    WujiWarningCodeNoAvailableChannel = 103,
    /** 104: A timeout occurs when looking up the channel. When joining a channel, the SDK looks up the specified channel. The warning usually occurs when the network condition is too poor for the SDK to connect to the server. */
    WujiWarningCodeLookupChannelTimeout = 104,
    /** 105: The server rejects the request to look up the channel. The server cannot process this request or the request is illegal.
     <br><b>DEPRECATED</b> as of v2.4.1. Use WujiConnectionChangedRejectedByServer(10) in the `reason` parameter of [connectionChangedToState]([WujiRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).</br>
     */
    WujiWarningCodeLookupChannelRejected = 105,
    /** 106: The server rejects the request to look up the channel. The server cannot process this request or the request is illegal. */
    WujiWarningCodeOpenChannelTimeout = 106,
    /** 107: The server rejects the request to open the channel. The server cannot process this request or the request is illegal. */
    WujiWarningCodeOpenChannelRejected = 107,
    /** 111: A timeout occurs when switching to the live video. */
    WujiWarningCodeSwitchLiveVideoTimeout = 111,
    /** 118: A timeout occurs when setting the client role in the live broadcast profile. */
    WujiWarningCodeSetClientRoleTimeout = 118,
    /** 119: The client role is unauthorized. */
    WujiWarningCodeSetClientRoleNotAuthorized = 119,
    /** 121: The ticket to open the channel is invalid. */
    WujiWarningCodeOpenChannelInvalidTicket = 121,
    /** 122: Try connecting to another server. */
    WujiWarningCodeOpenChannelTryNextVos = 122,
    /** 701: An error occurs in opening the audio mixing file. */
    WujiWarningCodeAudioMixingOpenError = 701,
    /** 1014: Audio Device Module: a warning occurs in the playback device. */
    WujiWarningCodeAdmRuntimePlayoutWarning = 1014,
    /** 1016: Audio Device Module: a warning occurs in the recording device. */
    WujiWarningCodeAdmRuntimeRecordingWarning = 1016,
    /** 1019: Audio Device Module: no valid audio data is collected. */
    WujiWarningCodeAdmRecordAudioSilence = 1019,
    /** 1020: Audio Device Module: a playback device fails. */
    WujiWarningCodeAdmPlaybackMalfunction = 1020,
    /** 1021: Audio Device Module: a recording device fails. */
    WujiWarningCodeAdmRecordMalfunction = 1021,
    /** 1025: Call is interrupted by system events such as phone call or siri etc. */
    WujiWarningCodeAdmInterruption = 1025,
    /** 1031: Audio Device Module: the recorded audio is too low. */
    WujiWarningCodeAdmRecordAudioLowlevel = 1031,
    /** 1032: Audio Device Module: the playback audio is too low. */
    WujiWarningCodeAdmPlayoutAudioLowlevel = 1032,
    /** 1040: Audio device module: An error occurs in the audio driver. Solution: <li>Restart your audio device.<li>Restart your device where the app runs.<li>Upgrade the sound card drive.</li> */
    WujiWarningCodeAdmNoDataReadyCallback = 1040,
    /** 1042: Audio device module: The audio recording device is different from the audio playback device, which may cause echoes problem. Wuji recommends using the same audio device to record and playback audio. */
    WujiWarningCodeAdmInconsistentDevices = 1042,
    /** 1051: Audio Device Module: howling is detected (Communication only). */
    WujiWarningCodeApmHowling = 1051,
    /** 1052: Audio Device Module: the device is in the glitch state. */
    WujiWarningCodeAdmGlitchState = 1052,
    /** 1053: Audio Device Module: the underlying audio settings have changed. */
    WujiWarningCodeAdmImproperSettings = 1053,
};

/** Error code.

Error codes occur when the SDK encounters an error that cannot be recovered automatically without any app intervention. For example, the SDK reports the WujiErrorCodeStartCall = 1002 error if it fails to start a call, and reminds the user to call the [leaveChannel]([WujiRtcEngineKit leaveChannel:]) method.
*/
typedef NS_ENUM(NSInteger, WujiErrorCode) {
    /** 0: No error occurs. */
    WujiErrorCodeNoError = 0,
    /** 1: A general error occurs (no specified reason). */
    WujiErrorCodeFailed = 1,
    /** 2: An invalid parameter is used. For example, the specific channel name includes illegal characters. */
    WujiErrorCodeInvalidArgument = 2,
    /** 3: The SDK module is not ready.
     <p>Possible solutions：
     <ul><li>Check the audio device.</li>
     <li>Check the completeness of the app.</li>
     <li>Re-initialize the SDK.</li></ul></p>
    */
    WujiErrorCodeNotReady = 3,
    /** 4: The current state of the SDK does not support this function. */
    WujiErrorCodeNotSupported = 4,
    /** 5: The request is rejected. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    WujiErrorCodeRefused = 5,
    /** 6: The buffer size is not big enough to store the returned data. */
    WujiErrorCodeBufferTooSmall = 6,
    /** 7: The SDK is not initialized before calling this method. */
    WujiErrorCodeNotInitialized = 7,
    /** 9: No permission exists. Check if the user has granted access to the audio or video device. */
    WujiErrorCodeNoPermission = 9,
    /** 10: An API method timeout occurs. Some API methods require the SDK to return the execution result, and this error occurs if the request takes too long (over 10 seconds) for the SDK to process. */
    WujiErrorCodeTimedOut = 10,
    /** 11: The request is canceled. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    WujiErrorCodeCanceled = 11,
    /** 12: The method is called too often. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    WujiErrorCodeTooOften = 12,
    /** 13: The SDK fails to bind to the network socket. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    WujiErrorCodeBindSocket = 13,
    /** 14: The network is unavailable. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    WujiErrorCodeNetDown = 14,
    /** 15: No network buffers are available. This is for internal SDK use only, and is not returned to the app through any method or callback. */
    WujiErrorCodeNoBufs = 15,
    /** 17: The request to join the channel is rejected.
     <p>Possible reasons are:
     <ul><li>The user is already in the channel, and still calls the API method to join the channel, for example, [joinChannelByToken]([WujiRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]).</li>
     <li>The user tries joining the channel during the echo test. Please join the channel after the echo test ends.</li></ul></p>
    */
    WujiErrorCodeJoinChannelRejected = 17,
    /** 18: The request to leave the channel is rejected.
     <p>Possible reasons are:
     <ul><li>The user left the channel and still calls the API method to leave the channel, for example, [leaveChannel]([WujiRtcEngineKit leaveChannel:]).</li>
     <li>The user has not joined the channel and calls the API method to leave the channel.</li></ul></p>
    */
    WujiErrorCodeLeaveChannelRejected = 18,
    /** 19: The resources are occupied and cannot be used. */
    WujiErrorCodeAlreadyInUse = 19,
    /** 20: The SDK gave up the request due to too many requests.  */
    WujiErrorCodeAbort = 20,
    /** 21: In Windows, specific firewall settings cause the SDK to fail to initialize and crash. */
    WujiErrorCodeInitNetEngine = 21,
    /** 22: The app uses too much of the system resources and the SDK fails to allocate the resources. */
    WujiErrorCodeResourceLimited = 22,
    /** 101: The specified App ID is invalid. Please try to rejoin the channel with a valid App ID.*/
    WujiErrorCodeInvalidAppId = 101,
    /** 102: The specified channel name is invalid. Please try to rejoin the channel with a valid channel name. */
    WujiErrorCodeInvalidChannelId = 102,
    /** 109: The token expired.
     <br><b>DEPRECATED</b> as of v2.4.1. Use WujiConnectionChangedTokenExpired(9) in the `reason` parameter of [connectionChangedToState]([WujiRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).</br>
     <p>Possible reasons are:
     <ul><li>Authorized Timestamp expired: The timestamp is represented by the number of seconds elapsed since 1/1/1970. The user can use the token to access the Wuji service within 24 hours after the token is generated. If the user does not access the Wuji service after 24 hours, this token is no longer valid.</li>
     <li>Call Expiration Timestamp expired: The timestamp is the exact time when a user can no longer use the Wuji service (for example, when a user is forced to leave an ongoing call). When a value is set for the Call Expiration Timestamp, it does not mean that the token will expire, but that the user will be banned from the channel.</li></ul></p>
     */
    WujiErrorCodeTokenExpired = 109,
    /** 110: The token is invalid.
<br><b>DEPRECATED</b> as of v2.4.1. Use WujiConnectionChangedInvalidToken(8) in the `reason` parameter of [connectionChangedToState]([WujiRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).</br>
     <p>Possible reasons are:
     <ul><li>The App Certificate for the project is enabled in Console, but the user is using the App ID. Once the App Certificate is enabled, the user must use a token.</li>
     <li>The uid is mandatory, and users must set the same uid as the one set in the [joinChannelByToken]([WujiRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method.</li></ul></p>
     */
    WujiErrorCodeInvalidToken = 110,
    /** 111: The Internet connection is interrupted. This applies to the Wuji Web SDK only. */
    WujiErrorCodeConnectionInterrupted = 111,
    /** 112: The Internet connection is lost. This applies to the Wuji Web SDK only. */
    WujiErrorCodeConnectionLost = 112,
    /** 113: The user is not in the channel when calling the [sendStreamMessage]([WujiRtcEngineKit sendStreamMessage:data:]) or [getUserInfoByUserAccount]([WujiRtcEngineKit getUserInfoByUserAccount:withError:]) method. */
    WujiErrorCodeNotInChannel = 113,
    /** 114: The size of the sent data is over 1024 bytes when the user calls the [sendStreamMessage]([WujiRtcEngineKit sendStreamMessage:data:]) method. */
    WujiErrorCodeSizeTooLarge = 114,
    /** 115: The bitrate of the sent data exceeds the limit of 6 Kbps when the user calls the [sendStreamMessage]([WujiRtcEngineKit sendStreamMessage:data:]) method. */
    WujiErrorCodeBitrateLimit = 115,
    /** 116: Too many data streams (over five streams) are created when the user calls the [createDataStream]([WujiRtcEngineKit createDataStream:reliable:ordered:]) method. */
    WujiErrorCodeTooManyDataStreams = 116,
    /** 120: Decryption fails. The user may have used a different encryption password to join the channel. Check your settings or try rejoining the channel. */
    WujiErrorCodeDecryptionFailed = 120,
    /** 124: Incorrect watermark file parameter. */
    WujiErrorCodeWatermarkParam = 124,
    /** 125: Incorrect watermark file path. */
    WujiErrorCodeWatermarkPath = 125,
    /** 126: Incorrect watermark file format. */
    WujiErrorCodeWatermarkPng = 126,
    /** 127: Incorrect watermark file information. */
    WujiErrorCodeWatermarkInfo = 127,
    /** 128: Incorrect watermark file data format. */
    WujiErrorCodeWatermarkAGRB = 128,
    /** 129: An error occurs in reading the watermark file. */
    WujiErrorCodeWatermarkRead = 129,
    /** 130: The encrypted stream is not allowed to publish. */
    WujiErrorCodeEncryptedStreamNotAllowedPublish = 130,
    /** 134: The user account is invalid. */
    WujiErrorCodeInvalidUserAccount = 134,

    /** 151: CDN related errors. Remove the original URL address and add a new one by calling the [removePublishStreamUrl]([WujiRtcEngineKit removePublishStreamUrl:]) and [addPublishStreamUrl]([WujiRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) methods. */
    WujiErrorCodePublishStreamCDNError = 151,
    /** 152: The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones. */
    WujiErrorCodePublishStreamNumReachLimit = 152,
    /** 153: The host manipulates other hosts' URLs. Check your app logic. */
    WujiErrorCodePublishStreamNotAuthorized = 153,
    /** 154: An error occurs in Wuji's streaming server. Call the [addPublishStreamUrl]([WujiRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the stream again. */
    WujiErrorCodePublishStreamInternalServerError = 154,
    /** 155: The server fails to find the stream. */
    WujiErrorCodePublishStreamNotFound = 155,
    /** 156: The format of the RTMP stream URL is not supported. Check whether the URL format is correct. */
    WujiErrorCodePublishStreamFormatNotSuppported = 156,

    /** 1001: Fails to load the media engine. */
    WujiErrorCodeLoadMediaEngine = 1001,
    /** 1002: Fails to start the call after enabling the media engine. */
    WujiErrorCodeStartCall = 1002,
    /** 1003: Fails to start the camera.
     <br><b>DEPRECATED</b> as of v2.4.1. Use WujiLocalVideoStreamErrorCaptureFailure(4) in the `error` parameter of [connectionChangedToState]([WujiRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]).</br>
     */
    WujiErrorCodeStartCamera = 1003,
    /** 1004: Fails to start the video rendering module. */
    WujiErrorCodeStartVideoRender = 1004,
    /** 1005: A general error occurs in the Audio Device Module (the reason is not classified specifically). Check if the audio device is used by another app, or try rejoining the channel. */
    WujiErrorCodeAdmGeneralError = 1005,
    /** 1006: Audio Device Module: An error occurs in using the Java resources. */
    WujiErrorCodeAdmJavaResource = 1006,
    /** 1007: Audio Device Module: An error occurs in setting the sampling frequency. */
    WujiErrorCodeAdmSampleRate = 1007,
    /** 1008: Audio Device Module: An error occurs in initializing the playback device. */
    WujiErrorCodeAdmInitPlayout = 1008,
    /** 1009: Audio Device Module: An error occurs in starting the playback device. */
    WujiErrorCodeAdmStartPlayout = 1009,
    /** 1010: Audio Device Module: An error occurs in stopping the playback device. */
    WujiErrorCodeAdmStopPlayout = 1010,
    /** 1011: Audio Device Module: An error occurs in initializing the recording device. */
    WujiErrorCodeAdmInitRecording = 1011,
    /** 1012: Audio Device Module: An error occurs in starting the recording device. */
    WujiErrorCodeAdmStartRecording = 1012,
    /** 1013: Audio Device Module: An error occurs in stopping the recording device. */
    WujiErrorCodeAdmStopRecording = 1013,
    /** 1015: Audio Device Module: A playback error occurs. Check your playback device, or try rejoining the channel. */
    WujiErrorCodeAdmRuntimePlayoutError = 1015,
    /** 1017: Audio Device Module: A recording error occurs. */
    WujiErrorCodeAdmRuntimeRecordingError = 1017,
    /** 1018: Audio Device Module: Fails to record. */
    WujiErrorCodeAdmRecordAudioFailed = 1018,
    /** 1020: Audio Device Module: Abnormal audio playback frequency. */
    WujiErrorCodeAdmPlayAbnormalFrequency = 1020,
    /** 1021: Audio Device Module: Abnormal audio recording frequency. */
    WujiErrorCodeAdmRecordAbnormalFrequency = 1021,
    /** 1022: Audio Device Module: An error occurs in initializing the loopback device. */
    WujiErrorCodeAdmInitLoopback  = 1022,
    /** 1023: Audio Device Module: An error occurs in starting the loopback device. */
    WujiErrorCodeAdmStartLoopback = 1023,
    /** 1027: Audio Device Module: An error occurs in no recording Permission. */
    WujiErrorCodeAdmNoPermission = 1027,
    /** 1359: No recording device exists. */
    WujiErrorCodeAdmNoRecordingDevice = 1359,
    /** 1360: No playback device exists. */
    WujiErrorCodeAdmNoPlayoutDevice = 1360,
    /** 1501: Video Device Module: The camera is unauthorized. */
    WujiErrorCodeVdmCameraNotAuthorized = 1501,
    /** 1600: Video Device Module: An unknown error occurs. */
    WujiErrorCodeVcmUnknownError = 1600,
    /** 1601: Video Device Module: An error occurs in initializing the video encoder. */
    WujiErrorCodeVcmEncoderInitError = 1601,
    /** 1602: Video Device Module: An error occurs in video encoding. */
    WujiErrorCodeVcmEncoderEncodeError = 1602,
    /** 1603: Video Device Module: An error occurs in setting the video encoder.
    <p><b>DEPRECATED</b></p>
    */
    WujiErrorCodeVcmEncoderSetError = 1603,
};

/** The state of the audio mixing file. */
typedef NS_ENUM(NSInteger, WujiAudioMixingStateCode){
    /** The audio mixing file is playing. */
    WujiAudioMixingStatePlaying = 710,
    /** The audio mixing file pauses playing. */
    WujiAudioMixingStatePaused = 711,
    /** The audio mixing file stops playing. */
    WujiAudioMixingStateStopped = 713,
    /** An exception occurs when playing the audio mixing file. */
    WujiAudioMixingStateFailed = 714,
};

/**  The error code of the audio mixing file. */
typedef NS_ENUM(NSInteger, WujiAudioMixingErrorCode){
    /** The SDK cannot open the audio mixing file. */
   WujiAudioMixingErrorCanNotOpen = 701,
   /** The SDK opens the audio mixing file too frequently. */
   WujiAudioMixingErrorTooFrequentCall = 702,
   /** The opening of the audio mixing file is interrupted. */
   WujiAudioMixingErrorInterruptedEOF = 703,
   /** No error. */
   WujiAudioMixingErrorOK = 0,
};

/** Video profile.

**DEPRECATED**

Please use WujiVideoEncoderConfiguration.

iPhones do not support resolutions above 720p.
*/
typedef NS_ENUM(NSInteger, WujiVideoProfile) {
    /** Invalid profile. */
    WujiVideoProfileInvalid = -1,
    /** Resolution 160 * 120, frame rate 15 fps, bitrate 65 Kbps. */
    WujiVideoProfileLandscape120P = 0,
    /** (iOS only) Resolution 120 * 120, frame rate 15 fps, bitrate 50 Kbps. */
    WujiVideoProfileLandscape120P_3 = 2,
    /** (iOS only) Resolution 320 * 180, frame rate 15 fps, bitrate 140 Kbps. */
    WujiVideoProfileLandscape180P = 10,
    /** (iOS only) Resolution 180 * 180, frame rate 15 fps, bitrate 100 Kbps. */
    WujiVideoProfileLandscape180P_3 = 12,
    /** Resolution 240 * 180, frame rate 15 fps, bitrate 120 Kbps. */
    WujiVideoProfileLandscape180P_4 = 13,
    /** Resolution 320 * 240, frame rate 15 fps, bitrate 200 Kbps. */
    WujiVideoProfileLandscape240P = 20,
    /** (iOS only) Resolution 240 * 240, frame rate 15 fps, bitrate 140 Kbps. */
    WujiVideoProfileLandscape240P_3 = 22,
    /** Resolution 424 * 240, frame rate 15 fps, bitrate 220 Kbps. */
    WujiVideoProfileLandscape240P_4 = 23,
    /** Resolution 640 * 360, frame rate 15 fps, bitrate 400 Kbps. */
    WujiVideoProfileLandscape360P = 30,
    /** (iOS only) Resolution 360 * 360, frame rate 15 fps, bitrate 260 Kbps. */
    WujiVideoProfileLandscape360P_3 = 32,
    /** Resolution 640 * 360, frame rate 30 fps, bitrate 600 Kbps. */
    WujiVideoProfileLandscape360P_4 = 33,
    /** Resolution 360 * 360, frame rate 30 fps, bitrate 400 Kbps. */
    WujiVideoProfileLandscape360P_6 = 35,
    /** Resolution 480 * 360, frame rate 15 fps, bitrate 320 Kbps. */
    WujiVideoProfileLandscape360P_7 = 36,
    /** Resolution 480 * 360, frame rate 30 fps, bitrate 490 Kbps. */
    WujiVideoProfileLandscape360P_8 = 37,
    /** Resolution 640 * 360, frame rate 15 fps, bitrate 800 Kbps.
    <br>
     <b>Note:</b> This profile applies to the live broadcast channel profile only.
     */
    WujiVideoProfileLandscape360P_9 = 38,
    /** Resolution 640 * 360, frame rate 24 fps, bitrate 800 Kbps.
    <br>
     <b>Note:</b> This profile applies to the live broadcast channel profile only.
     */
    WujiVideoProfileLandscape360P_10 = 39,
    /** Resolution 640 * 360, frame rate 24 fps, bitrate 1000 Kbps.
    <br>
     <b>Note:</b> This profile applies to the live broadcast channel profile only.
     */
    WujiVideoProfileLandscape360P_11 = 100,
    /** Resolution 640 * 480, frame rate 15 fps, bitrate 500 Kbps. */
    WujiVideoProfileLandscape480P = 40,
    /** (iOS only) Resolution 480 * 480, frame rate 15 fps, bitrate 400 Kbps. */
    WujiVideoProfileLandscape480P_3 = 42,
    /** Resolution 640 * 480, frame rate 30 fps, bitrate 750 Kbps. */
    WujiVideoProfileLandscape480P_4 = 43,
    /** Resolution 480 * 480, frame rate 30 fps, bitrate 600 Kbps. */
    WujiVideoProfileLandscape480P_6 = 45,
    /** Resolution 848 * 480, frame rate 15 fps, bitrate 610 Kbps. */
    WujiVideoProfileLandscape480P_8 = 47,
    /** Resolution 848 * 480, frame rate 30 fps, bitrate 930 Kbps. */
    WujiVideoProfileLandscape480P_9 = 48,
    /** Resolution 640 * 480, frame rate 10 fps, bitrate 400 Kbps. */
    WujiVideoProfileLandscape480P_10 = 49,
    /** Resolution 1280 * 720, frame rate 15 fps, bitrate 1130 Kbps. */
    WujiVideoProfileLandscape720P = 50,
    /** Resolution 1280 * 720, frame rate 30 fps, bitrate 1710 Kbps. */
    WujiVideoProfileLandscape720P_3 = 52,
    /** Resolution 960 * 720, frame rate 15 fps, bitrate 910 Kbps. */
    WujiVideoProfileLandscape720P_5 = 54,
    /** Resolution 960 * 720, frame rate 30 fps, bitrate 1380 Kbps. */
    WujiVideoProfileLandscape720P_6 = 55,
    /** (macOS only) Resolution 1920 * 1080, frame rate 15 fps, bitrate 2080 Kbps. */
    WujiVideoProfileLandscape1080P = 60,
    /** (macOS only) Resolution 1920 * 1080, frame rate 30 fps, bitrate 3150 Kbps. */
    WujiVideoProfileLandscape1080P_3 = 62,
    /** (macOS only) Resolution 1920 * 1080, frame rate 60 fps, bitrate 4780 Kbps. */
    WujiVideoProfileLandscape1080P_5 = 64,
    /** (macOS only) Resolution 2560 * 1440, frame rate 30 fps, bitrate 4850 Kbps. */
    WujiVideoProfileLandscape1440P = 66,
    /** (macOS only) Resolution 2560 * 1440, frame rate 60 fps, bitrate 6500 Kbps. */
    WujiVideoProfileLandscape1440P_2 = 67,
    /** (macOS only) Resolution 3840 * 2160, frame rate 30 fps, bitrate 6500 Kbps. */
    WujiVideoProfileLandscape4K = 70,
    /** (macOS only) Resolution 3840 * 2160, frame rate 60 fps, bitrate 6500 Kbps. */
    WujiVideoProfileLandscape4K_3 = 72,

    /** Resolution 120 * 160, frame rate 15 fps, bitrate 65 Kbps. */
    WujiVideoProfilePortrait120P = 1000,
    /** (iOS only) Resolution 120 * 120, frame rate 15 fps, bitrate 50 Kbps. */
    WujiVideoProfilePortrait120P_3 = 1002,
    /** (iOS only) Resolution 180 * 320, frame rate 15 fps, bitrate 140 Kbps. */
    WujiVideoProfilePortrait180P = 1010,
    /** (iOS only) Resolution 180 * 180, frame rate 15 fps, bitrate 100 Kbps. */
    WujiVideoProfilePortrait180P_3 = 1012,
    /** Resolution 180 * 240, frame rate 15 fps, bitrate 120 Kbps. */
    WujiVideoProfilePortrait180P_4 = 1013,
    /** Resolution 240 * 320, frame rate 15 fps, bitrate 200 Kbps. */
    WujiVideoProfilePortrait240P = 1020,
    /** (iOS only) Resolution 240 * 240, frame rate 15 fps, bitrate 140 Kbps. */
    WujiVideoProfilePortrait240P_3 = 1022,
    /** Resolution 240 * 424, frame rate 15 fps, bitrate 220 Kbps. */
    WujiVideoProfilePortrait240P_4 = 1023,
    /** Resolution 360 * 640, frame rate 15 fps, bitrate 400 Kbps. */
    WujiVideoProfilePortrait360P = 1030,
    /** (iOS only) Resolution 360 * 360, frame rate 15 fps, bitrate 260 Kbps. */
    WujiVideoProfilePortrait360P_3 = 1032,
    /** Resolution 360 * 640, frame rate 30 fps, bitrate 600 Kbps. */
    WujiVideoProfilePortrait360P_4 = 1033,
    /** Resolution 360 * 360, frame rate 30 fps, bitrate 400 Kbps. */
    WujiVideoProfilePortrait360P_6 = 1035,
    /** Resolution 360 * 480, frame rate 15 fps, bitrate 320 Kbps. */
    WujiVideoProfilePortrait360P_7 = 1036,
    /** Resolution 360 * 480, frame rate 30 fps, bitrate 490 Kbps. */
    WujiVideoProfilePortrait360P_8 = 1037,
    /** Resolution 360 * 640, frame rate 15 fps, bitrate 600 Kbps. */
    WujiVideoProfilePortrait360P_9 = 1038,
    /** Resolution 360 * 640, frame rate 24 fps, bitrate 800 Kbps. */
    WujiVideoProfilePortrait360P_10 = 1039,
    /** Resolution 360 * 640, frame rate 24 fps, bitrate 800 Kbps. */
    WujiVideoProfilePortrait360P_11 = 1100,
    /** Resolution 480 * 640, frame rate 15 fps, bitrate 500 Kbps. */
    WujiVideoProfilePortrait480P = 1040,
    /** (iOS only) Resolution 480 * 480, frame rate 15 fps, bitrate 400 Kbps. */
    WujiVideoProfilePortrait480P_3 = 1042,
    /** Resolution 480 * 640, frame rate 30 fps, bitrate 750 Kbps. */
    WujiVideoProfilePortrait480P_4 = 1043,
    /** Resolution 480 * 480, frame rate 30 fps, bitrate 600 Kbps. */
    WujiVideoProfilePortrait480P_6 = 1045,
    /** Resolution 480 * 848, frame rate 15 fps, bitrate 610 Kbps. */
    WujiVideoProfilePortrait480P_8 = 1047,
    /** Resolution 480 * 848, frame rate 30 fps, bitrate 930 Kbps. */
    WujiVideoProfilePortrait480P_9 = 1048,
    /** Resolution 480 * 640, frame rate 10 fps, bitrate 400 Kbps. */
    WujiVideoProfilePortrait480P_10 = 1049,
    /** Resolution 720 * 1280, frame rate 15 fps, bitrate 1130 Kbps. */
    WujiVideoProfilePortrait720P = 1050,
    /** Resolution 720 * 1280, frame rate 30 fps, bitrate 1710 Kbps. */
    WujiVideoProfilePortrait720P_3 = 1052,
    /** Resolution 720 * 960, frame rate 15 fps, bitrate 910 Kbps. */
    WujiVideoProfilePortrait720P_5 = 1054,
    /** Resolution 720 * 960, frame rate 30 fps, bitrate 1380 Kbps. */
    WujiVideoProfilePortrait720P_6 = 1055,
    /** (macOS only) Resolution 1080 * 1920, frame rate 15 fps, bitrate 2080 Kbps. */
    WujiVideoProfilePortrait1080P = 1060,
    /** (macOS only) Resolution 1080 * 1920, frame rate 30 fps, bitrate 3150 Kbps. */
    WujiVideoProfilePortrait1080P_3 = 1062,
    /** (macOS only) Resolution 1080 * 1920, frame rate 60 fps, bitrate 4780 Kbps. */
    WujiVideoProfilePortrait1080P_5 = 1064,
    /** (macOS only) Resolution 1440 * 2560, frame rate 30 fps, bitrate 4850 Kbps. */
    WujiVideoProfilePortrait1440P = 1066,
    /** (macOS only) Resolution 1440 * 2560, frame rate 60 fps, bitrate 6500 Kbps. */
    WujiVideoProfilePortrait1440P_2 = 1067,
    /** (macOS only) Resolution 2160 * 3840, frame rate 30 fps, bitrate 6500 Kbps. */
    WujiVideoProfilePortrait4K = 1070,
    /** (macOS only) Resolution 2160 * 3840, frame rate 60 fps, bitrate 6500 Kbps. */
    WujiVideoProfilePortrait4K_3 = 1072,
    /** (Default) Resolution 640 * 360, frame rate 15 fps, bitrate 400 Kbps. */
    WujiVideoProfileDEFAULT = WujiVideoProfileLandscape360P,
};

/** The camera capturer configuration. */
typedef NS_ENUM(NSInteger, WujiCameraCaptureOutputPreference) {
    /** (default) Self-adapts the camera output parameters to the system performance and network conditions to balance CPU consumption and video preview quality. */
    WujiCameraCaptureOutputPreferenceAuto = 0,
    /** Prioritizes the system performance. The SDK chooses the dimension and frame rate of the local camera capture closest to those set by [setVideoEncoderConfiguration]([WujiRtcEngineKit setVideoEncoderConfiguration:]). */
    WujiCameraCaptureOutputPreferencePerformance = 1,
    /** Prioritizes the local preview quality. The SDK chooses higher camera output parameters to improve the local video preview quality. This option requires extra CPU and RAM usage for video pre-processing. */
    WujiCameraCaptureOutputPreferencePreview = 2,
    /** Internal use only */
    WujiCameraCaptureOutputPreferenceUnkown = 3
};

#if defined (TARGET_OS_IOS) && TARGET_OS_IOS
/** The camera direction. */
typedef NS_ENUM(NSInteger, WujiCameraDirection) {
        /** The rear camera. */
        WujiCameraDirectionRear = 0,
        /** The front camera. */
        WujiCameraDirectionFront = 1,
    };
#endif

/** Video frame rate */
typedef NS_ENUM(NSInteger, WujiVideoFrameRate) {
    /** 1 fps. */
    WujiVideoFrameRateFps1 = 1,
    /** 7 fps. */
    WujiVideoFrameRateFps7 = 7,
    /** 10 fps. */
    WujiVideoFrameRateFps10 = 10,
    /** 15 fps. */
    WujiVideoFrameRateFps15 = 15,
    /** 24 fps. */
    WujiVideoFrameRateFps24 = 24,
    /** 30 fps. */
    WujiVideoFrameRateFps30 = 30,
    /** 60 fps (macOS only). */
    WujiVideoFrameRateFps60 = 60,
};

/** Video output orientation mode.

  **Note:** When a custom video source is used, if you set WujiVideoOutputOrientationMode as WujiVideoOutputOrientationModeFixedLandscape(1) or WujiVideoOutputOrientationModeFixedPortrait(2), when the rotated video image has a different orientation than the specified output orientation, the video encoder first crops it and then encodes it.
 */
typedef NS_ENUM(NSInteger, WujiVideoOutputOrientationMode) {
    /** Adaptive mode (Default).
     <p>The video encoder adapts to the orientation mode of the video input device. When you use a custom video source, the output video from the encoder inherits the orientation of the original video.
     <ul><li>If the width of the captured video from the SDK is greater than the height, the encoder sends the video in landscape mode. The encoder also sends the rotational information of the video, and the receiver uses the rotational information to rotate the received video.</li>
     <li>If the original video is in portrait mode, the output video from the encoder is also in portrait mode. The encoder also sends the rotational information of the video to the receiver.</li></ul></p>
     */
    WujiVideoOutputOrientationModeAdaptative = 0,
    /** Landscape mode.
     <p>The video encoder always sends the video in landscape mode. The video encoder rotates the original video before sending it and the rotational information is 0. This mode applies to scenarios involving CDN live streaming.</p>
     */
    WujiVideoOutputOrientationModeFixedLandscape = 1,
     /** Portrait mode.
      <p>The video encoder always sends the video in portrait mode. The video encoder rotates the original video before sending it and the rotational information is 0. This mode applies to scenarios involving CDN live streaming.</p>
      */
    WujiVideoOutputOrientationModeFixedPortrait = 2,
};

/** Channel profile. */
typedef NS_ENUM(NSInteger, WujiChannelProfile) {
    /** 0: (Default) The Communication profile. 
     <p>Use this profile in one-on-one calls or group calls, where all users can talk freely.</p>
     */
    WujiChannelProfileCommunication = 0,
    /** 1: The Live-Broadcast profile. 
     <p>Users in a live-broadcast channel have a role as either broadcaster or audience. A broadcaster can both send and receive streams; an audience can only receive streams.</p>
     */
    WujiChannelProfileLiveBroadcasting = 1,
    /** 2: The Gaming profile. 
     <p>This profile uses a codec with a lower bitrate and consumes less power. Applies to the gaming scenario, where all game players can talk freely.</p>
     */
    WujiChannelProfileGame = 2,
};

/** Client role in a live broadcast. */
typedef NS_ENUM(NSInteger, WujiClientRole) {
    /** Host. */
    WujiClientRoleBroadcaster = 1,
    /** Audience. */
    WujiClientRoleAudience = 2,
};


/** Media type. */
typedef NS_ENUM(NSInteger, WujiMediaType) {
    /** No audio and video. */
    WujiMediaTypeNone = 0,
    /** Audio only. */
    WujiMediaTypeAudioOnly = 1,
    /** Video only. */
    WujiMediaTypeVideoOnly = 2,
    /** Audio and video. */
    WujiMediaTypeAudioAndVideo = 3,
};

/** Encryption mode */
typedef NS_ENUM(NSInteger, WujiEncryptionMode) {
    /** When encryptionMode is set as NULL, the encryption mode is set as "aes-128-xts" by default. */
    WujiEncryptionModeNone = 0,
    /** (Default) 128-bit AES encryption, XTS mode. */
    WujiEncryptionModeAES128XTS = 1,
    /** 256-bit AES encryption, XTS mode. */
    WujiEncryptionModeAES256XTS = 2,
    /** 128-bit AES encryption, ECB mode. */
    WujiEncryptionModeAES128ECB = 3,
};

/** Reason for the user being offline. */
typedef NS_ENUM(NSUInteger, WujiUserOfflineReason) {
    /** The user left the current channel. */
    WujiUserOfflineReasonQuit = 0,
    /** The SDK timed out and the user dropped offline because no data packet is received within a certain period of time. If a user quits the call and the message is not passed to the SDK (due to an unreliable channel), the SDK assumes the user dropped offline. */
    WujiUserOfflineReasonDropped = 1,
    /** (Live broadcast only.) The client role switched from the host to the audience. */
    WujiUserOfflineReasonBecomeAudience = 2,
};

/** The RTMP streaming state. */
typedef NS_ENUM(NSUInteger, WujiRtmpStreamingState) {
  /** The RTMP streaming has not started or has ended. This state is also triggered after you remove an RTMP address from the CDN by calling removePublishStreamUrl.*/
  WujiRtmpStreamingStateIdle = 0,
  /** The SDK is connecting to Wuji's streaming server and the RTMP server. This state is triggered after you call the [addPublishStreamUrl]([WujiRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method. */
  WujiRtmpStreamingStateConnecting = 1,
  /** The RTMP streaming is being published. The SDK successfully publishes the RTMP streaming and returns this state. */
  WujiRtmpStreamingStateRunning = 2,
  /** The RTMP streaming is recovering. When exceptions occur to the CDN, or the streaming is interrupted, the SDK attempts to resume RTMP streaming and returns this state.
<li> If the SDK successfully resumes the streaming, WujiRtmpStreamingStateRunning(2) returns.
<li> If the streaming does not resume within 60 seconds or server errors occur, WujiRtmpStreamingStateFailure(4) returns. You can also reconnect to the server by calling the [removePublishStreamUrl]([WujiRtcEngineKit removePublishStreamUrl:]) and [addPublishStreamUrl]([WujiRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) methods. */
  WujiRtmpStreamingStateRecovering = 3,
  /** The RTMP streaming fails. See the errorCode parameter for the detailed error information. You can also call the [addPublishStreamUrl]([WujiRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the RTMP streaming again. */
  WujiRtmpStreamingStateFailure = 4,
};

/** The detailed error information for streaming. */
typedef NS_ENUM(NSUInteger, WujiRtmpStreamingErrorCode) {
  /** The RTMP streaming publishes successfully. */
  WujiRtmpStreamingErrorCodeOK = 0,
  /** Invalid argument used. If, for example, you do not call the [setLiveTranscoding]([WujiRtcEngineKit setLiveTranscoding:]) method to configure the LiveTranscoding parameters before calling the [addPublishStreamUrl]([WujiRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method, the SDK returns this error. Check whether you set the parameters in the setLiveTranscoding method properly. */
  WujiRtmpStreamingErrorCodeInvalidParameters = 1,
  /** The RTMP streaming is encrypted and cannot be published. */
  WujiRtmpStreamingErrorCodeEncryptedStreamNotAllowed = 2,
  /** Timeout for the RTMP streaming. Call the [addPublishStreamUrl]([WujiRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the streaming again. */
  WujiRtmpStreamingErrorCodeConnectionTimeout = 3,
  /** An error occurs in Wuji's streaming server. Call the [addPublishStreamUrl]([WujiRtcEngineKit addPublishStreamUrl:transcodingEnabled:]) method to publish the streaming again. */
  WujiRtmpStreamingErrorCodeInternalServerError = 4,
  /** An error occurs in the RTMP server. */
  WujiRtmpStreamingErrorCodeRtmpServerError = 5,
  /** The RTMP streaming publishes too frequently. */
  WujiRtmpStreamingErrorCodeTooOften = 6,
  /** The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones. */
  WujiRtmpStreamingErrorCodeReachLimit = 7,
  /** The host manipulates other hosts' URLs. Check your app logic. */
  WujiRtmpStreamingErrorCodeNotAuthorized = 8,
  /** Wuji's server fails to find the RTMP streaming. */
  WujiRtmpStreamingErrorCodeStreamNotFound = 9,
  /** The format of the RTMP streaming URL is not supported. Check whether the URL format is correct. */
  WujiRtmpStreamingErrorCodeFormatNotSupported = 10,
};

/** State of importing an external video stream in a live broadcast. */
typedef NS_ENUM(NSUInteger, WujiInjectStreamStatus) {
    /** The external video stream imported successfully. */
    WujiInjectStreamStatusStartSuccess = 0,
    /** The external video stream already exists. */
    WujiInjectStreamStatusStartAlreadyExists = 1,
    /** The external video stream import is unauthorized. */
    WujiInjectStreamStatusStartUnauthorized = 2,
    /** Import external video stream timeout. */
    WujiInjectStreamStatusStartTimedout = 3,
    /** The external video stream failed to import. */
    WujiInjectStreamStatusStartFailed = 4,
    /** The external video stream imports successfully. */
    WujiInjectStreamStatusStopSuccess = 5,
    /** No external video stream is found. */
    WujiInjectStreamStatusStopNotFound = 6,
    /** The external video stream is stopped from being unauthorized. */
    WujiInjectStreamStatusStopUnauthorized = 7,
    /** Importing the external video stream timeout. */
    WujiInjectStreamStatusStopTimedout = 8,
    /** Importing the external video stream failed. */
    WujiInjectStreamStatusStopFailed = 9,
    /** The external video stream import is interrupted. */
    WujiInjectStreamStatusBroken = 10,
};

/** Output log filter level. */
typedef NS_ENUM(NSUInteger, WujiLogFilter) {
    /** Do not output any log information. */
    WujiLogFilterOff = 0,
    /** Output all log information. Set your log filter as debug if you want to get the most complete log file. */
    WujiLogFilterDebug = 0x080f,
    /** Output CRITICAL, ERROR, WARNING, and INFO level log information. We recommend setting your log filter as this level. */
    WujiLogFilterInfo = 0x000f,
    /** Outputs CRITICAL, ERROR, and WARNING level log information. */
    WujiLogFilterWarning = 0x000e,
    /** Outputs CRITICAL and ERROR level log information. */
    WujiLogFilterError = 0x000c,
    /** Outputs CRITICAL level log information. */
    WujiLogFilterCritical = 0x0008,
};

/** Audio recording quality. */
typedef NS_ENUM(NSInteger, WujiAudioRecordingQuality) {
   /** Low quality: The sample rate is 32 KHz, and the file size is around 1.2 MB after 10 minutes of recording. */
    WujiAudioRecordingQualityLow = 0,
    /** Medium quality: The sample rate is 32 KHz, and the file size is around 2 MB after 10 minutes of recording. */
    WujiAudioRecordingQualityMedium = 1,
    /** High quality: The sample rate is 32 KHz, and the file size is around 3.75 MB after 10 minutes of recording. */
    WujiAudioRecordingQualityHigh = 2
};

/** Lifecycle of the CDN live video stream.

**DEPRECATED**
*/
typedef NS_ENUM(NSInteger, WujiRtmpStreamLifeCycle) {
    /** Bound to the channel lifecycle. If all hosts leave the channel, the CDN live streaming stops after 30 seconds. */
    WujiRtmpStreamLifeCycleBindToChannel = 1,
    /** Bound to the owner of the RTMP stream. If the owner leaves the channel, the CDN live streaming stops immediately. */
    WujiRtmpStreamLifeCycleBindToOwnner = 2,
};

/** Network quality. */
typedef NS_ENUM(NSUInteger, WujiNetworkQuality) {
    /** The network quality is unknown. */
    WujiNetworkQualityUnknown = 0,
    /**  The network quality is excellent. */
    WujiNetworkQualityExcellent = 1,
    /** The network quality is quite good, but the bitrate may be slightly lower than excellent. */
    WujiNetworkQualityGood = 2,
    /** Users can feel the communication slightly impaired. */
    WujiNetworkQualityPoor = 3,
    /** Users can communicate only not very smoothly. */
    WujiNetworkQualityBad = 4,
     /** The network quality is so bad that users can hardly communicate. */
    WujiNetworkQualityVBad = 5,
     /** The network is disconnected and users cannot communicate at all. */
    WujiNetworkQualityDown = 6,
     /** Users cannot detect the network quality. (Not in use.) */
    WujiNetworkQualityUnsupported = 7,
     /** Detecting the network quality. */
    WujiNetworkQualityDetecting = 8,
};

/** Video stream type. */
typedef NS_ENUM(NSInteger, WujiVideoStreamType) {
    /** High-bitrate, high-resolution video stream. */
    WujiVideoStreamTypeHigh = 0,
    /** Low-bitrate, low-resolution video stream. */
    WujiVideoStreamTypeLow = 1,
};

/** The priority of the remote user. */
typedef NS_ENUM(NSInteger, WujiUserPriority) {
  /** The user's priority is high. */
  WujiUserPriorityHigh = 50,
  /** (Default) The user's priority is normal. */
  WujiUserPriorityNormal = 100,
};

/**  Quality change of the local video in terms of target frame rate and target bit rate since last count. */
typedef NS_ENUM(NSInteger, WujiVideoQualityAdaptIndication) {
  /** The quality of the local video stays the same. */
  WujiVideoQualityAdaptNone = 0,
  /** The quality improves because the network bandwidth increases. */
  WujiVideoQualityAdaptUpBandwidth = 1,
  /** The quality worsens because the network bandwidth decreases. */
  WujiVideoQualityAdaptDownBandwidth = 2,
};

/** Video display mode. */
typedef NS_ENUM(NSUInteger, WujiVideoRenderMode) {
    /** Hidden(1): Uniformly scale the video until it fills the visible boundaries (cropped). One dimension of the video may have clipped contents. */
    WujiVideoRenderModeHidden = 1,

    /** Fit(2): Uniformly scale the video until one of its dimension fits the boundary (zoomed to fit). Areas that are not filled due to the disparity in the aspect ratio are filled with black. */
    WujiVideoRenderModeFit = 2,

    /** Adaptive(3)：This mode is deprecated. */
    WujiVideoRenderModeAdaptive __deprecated_enum_msg("WujiVideoRenderModeAdaptive is deprecated.") = 3,

    /** Fill(4): The fill mode. In this mode, the SDK stretches or zooms the video to fill the display window. */
    WujiVideoRenderModeFill = 4,
};

/** Self-defined video codec profile. */
typedef NS_ENUM(NSInteger, WujiVideoCodecProfileType) {
    /** 66: Baseline video codec profile. Generally used in video calls on mobile phones. */
    WujiVideoCodecProfileTypeBaseLine = 66,
    /** 77: Main video codec profile. Generally used in mainstream electronics, such as MP4 players, portable video players, PSP, and iPads. */
    WujiVideoCodecProfileTypeMain = 77,
    /** 100: (Default) High video codec profile. Generally used in high-resolution broadcasts or television. */
    WujiVideoCodecProfileTypeHigh = 100
};

/** Video codec types. */
typedef NS_ENUM(NSInteger, WujiVideoCodecType) {
    /** 1: Standard VP8. */
    WujiVideoCodecTypeVP8 = 1,
    /** 2: Standard H264. */
    WujiVideoCodecTypeH264 = 2,
    /** 3: Enhanced VP8. */
    WujiVideoCodecTypeEVP = 3,
    /** 4: Enhanced H264. */
    WujiVideoCodecTypeE264 = 4,
};

/** Video mirror mode. */
typedef NS_ENUM(NSUInteger, WujiVideoMirrorMode) {
    /** 0: (Default) The SDK determines the mirror mode.
     */
    WujiVideoMirrorModeAuto = 0,
    /** 1: Enables mirror mode. */
    WujiVideoMirrorModeEnabled = 1,
    /** 2: Disables mirror mode. */
    WujiVideoMirrorModeDisabled = 2,
};

/** The content hint for screen sharing. */
typedef NS_ENUM(NSUInteger, WujiVideoContentHint) {
    /** 0: (Default) No content hint. */
    WujiVideoContentHintNone = 0,
    /** 1: Motion-intensive content. Choose this option if you prefer smoothness or when you are sharing a video clip, movie, or video game. */
    WujiVideoContentHintMotion = 1,
    /** 2: Motionless content. Choose this option if you prefer sharpness or when you are sharing a picture, PowerPoint slide, or text. */
    WujiVideoContentHintDetails = 2,
};

/** The state of the remote video. */
typedef NS_ENUM(NSUInteger, WujiVideoRemoteState) {
    /** 0: The remote video is in the default state, probably due to WujiVideoRemoteStateReasonLocalMuted(3), WujiVideoRemoteStateReasonRemoteMuted(5), or WujiVideoRemoteStateReasonRemoteOffline(7).
     */
    WujiVideoRemoteStateStopped = 0,
    /** 1: The first remote video packet is received.
     */
    WujiVideoRemoteStateStarting = 1,
    /** 2: The remote video stream is decoded and plays normally, probably due to WujiVideoRemoteStateReasonNetworkRecovery(2), WujiVideoRemoteStateReasonLocalUnmuted(4), WujiVideoRemoteStateReasonRemoteUnmuted(6), or WujiVideoRemoteStateReasonAudioFallbackRecovery(9).
     */
    WujiVideoRemoteStateDecoding = 2,
    /** 3: The remote video is frozen, probably due to WujiVideoRemoteStateReasonNetworkCongestion(1) or WujiVideoRemoteStateReasonAudioFallback(8).
     */
    WujiVideoRemoteStateFrozen = 3,
    /** 4: The remote video fails to start, probably due to WujiVideoRemoteStateReasonInternal(0).
     */
    WujiVideoRemoteStateFailed = 4,
};

/** The reason of the remote video state change. */
typedef NS_ENUM(NSUInteger, WujiVideoRemoteStateReason) {
    /** 0: Internal reasons. */
    WujiVideoRemoteStateReasonInternal = 0,
    /** 1: Network congestion. */
    WujiVideoRemoteStateReasonNetworkCongestion = 1,
    /** 2: Network recovery. */
    WujiVideoRemoteStateReasonNetworkRecovery = 2,
    /** 3: The local user stops receiving the remote video stream or disables the video module. */
    WujiVideoRemoteStateReasonLocalMuted = 3,
    /** 4: The local user resumes receiving the remote video stream or enables the video module. */
    WujiVideoRemoteStateReasonLocalUnmuted = 4,
    /** 5: The remote user stops sending the video stream or disables the video module. */
    WujiVideoRemoteStateReasonRemoteMuted = 5,
    /** 6: The remote user resumes sending the video stream or enables the video module. */
    WujiVideoRemoteStateReasonRemoteUnmuted = 6,
    /** 7: The remote user leaves the channel. */
    WujiVideoRemoteStateReasonRemoteOffline = 7,
    /** 8: The remote media stream falls back to the audio-only stream due to poor network conditions. */
    WujiVideoRemoteStateReasonAudioFallback = 8,
    /** 9: The remote media stream switches back to the video stream after the network conditions improve. */
    WujiVideoRemoteStateReasonAudioFallbackRecovery = 9,
};

/** Stream fallback option. */
typedef NS_ENUM(NSInteger, WujiStreamFallbackOptions) {
    /** No fallback behavior for the local/remote video stream when the uplink/downlink network condition is unreliable. The quality of the stream is not guaranteed. */
    WujiStreamFallbackOptionDisabled = 0,
    /** Under unreliable downlink network conditions, the remote video stream falls back to the low-stream (low resolution and low bitrate) video. You can only set this option in the [setRemoteSubscribeFallbackOption]([WujiRtcEngineKit setRemoteSubscribeFallbackOption:]) method. Nothing happens when you set this in the [setLocalPublishFallbackOption]([WujiRtcEngineKit setLocalPublishFallbackOption:]) method. */
    WujiStreamFallbackOptionVideoStreamLow = 1,
    /** Under unreliable uplink network conditions, the published video stream falls back to audio only. Under unreliable downlink network conditions, the remote video stream first falls back to the low-stream (low resolution and low bitrate) video; and then to an audio-only stream if the network condition deteriorates. */
    WujiStreamFallbackOptionAudioOnly = 2,
};

/** Audio sample rate. */
typedef NS_ENUM(NSInteger, WujiAudioSampleRateType) {
    /** 32 kHz. */
    WujiAudioSampleRateType32000 = 32000,
    /** 44.1 kHz. */
    WujiAudioSampleRateType44100 = 44100,
    /** 48 kHz. */
    WujiAudioSampleRateType48000 = 48000,
};

/** Audio profile. */
typedef NS_ENUM(NSInteger, WujiAudioProfile) {
    /** 0: Default audio profile. 
     <li>In the Communication profile: A sample rate of 32 KHz, audio encoding, mono, and a bitrate of up to 18 Kbps.
     <li>In the Live-broadcast profile: A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 52 Kbps.</li> */
    WujiAudioProfileDefault = 0,
    /** A sample rate of 32 KHz, audio encoding, mono, and a bitrate of up to 18 Kbps. */
    WujiAudioProfileSpeechStandard = 1,
    /** A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 48 Kbps. */
    WujiAudioProfileMusicStandard = 2,
    /** A sample rate of 48 KHz, music encoding, stereo, and a bitrate of up to 56 Kbps. */
    WujiAudioProfileMusicStandardStereo = 3,
    /** A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 128 Kbps. */
    WujiAudioProfileMusicHighQuality = 4,
    /** A sample rate of 48 KHz, music encoding, stereo, and a bitrate of up to 192 Kbps. */
    WujiAudioProfileMusicHighQualityStereo = 5,
};

/** Audio scenario. */
typedef NS_ENUM(NSInteger, WujiAudioScenario) {
    /** Default. */
    WujiAudioScenarioDefault = 0,
    /** Entertainment scenario, supporting voice during gameplay. */
    WujiAudioScenarioChatRoomEntertainment = 1,
    /** Education scenario, prioritizing fluency and stability. */
    WujiAudioScenarioEducation = 2,
    /** Live gaming scenario, enabling the gaming audio effects in the speaker mode in a live broadcast scenario. Choose this scenario for high-fidelity music playback.*/
    WujiAudioScenarioGameStreaming = 3,
    /** Showroom scenario, optimizing the audio quality with external professional equipment. */
    WujiAudioScenarioShowRoom = 4,
    /** Gaming scenario. */
    WujiAudioScenarioChatRoomGaming = 5
};

/** Audio output routing. */
typedef NS_ENUM(NSInteger, WujiAudioOutputRouting) {
    /** Default. */
    WujiAudioOutputRoutingDefault = -1,
    /** Headset.*/
    WujiAudioOutputRoutingHeadset = 0,
    /** Earpiece. */
    WujiAudioOutputRoutingEarpiece = 1,
    /** Headset with no microphone. */
    WujiAudioOutputRoutingHeadsetNoMic = 2,
    /** Speakerphone. */
    WujiAudioOutputRoutingSpeakerphone = 3,
    /** Loudspeaker. */
    WujiAudioOutputRoutingLoudspeaker = 4,
    /** Bluetooth headset. */
    WujiAudioOutputRoutingHeadsetBluetooth = 5
};

/** Use mode of the onRecordAudioFrame callback. */
typedef NS_ENUM(NSInteger, WujiAudioRawFrameOperationMode) {
    /** Read-only mode: Users only read the AudioFrame data without modifying anything. For example, when users acquire data with the Wuji SDK then push the RTMP streams. */
    WujiAudioRawFrameOperationModeReadOnly = 0,
    /** Write-only mode: Users replace the AudioFrame data with their own data and pass them to the SDK for encoding. For example, when users acquire data. */
    WujiAudioRawFrameOperationModeWriteOnly = 1,
    /** Read and write mode: Users read the data from AudioFrame, modify it, and then play it. For example, when users have their own sound-effect processing module and perform some voice pre-processing such as a voice change. */
    WujiAudioRawFrameOperationModeReadWrite = 2,
};

/** Audio equalization band frequency. */
typedef NS_ENUM(NSInteger, WujiAudioEqualizationBandFrequency) {
    /** 31 Hz. */
    WujiAudioEqualizationBand31 = 0,
    /** 62 Hz. */
    WujiAudioEqualizationBand62 = 1,
    /** 125 Hz. */
    WujiAudioEqualizationBand125 = 2,
    /** 250 Hz. */
    WujiAudioEqualizationBand250 = 3,
    /** 500 Hz */
    WujiAudioEqualizationBand500 = 4,
    /** 1 kHz. */
    WujiAudioEqualizationBand1K = 5,
    /** 2 kHz. */
    WujiAudioEqualizationBand2K = 6,
    /** 4 kHz. */
    WujiAudioEqualizationBand4K = 7,
    /** 8 kHz. */
    WujiAudioEqualizationBand8K = 8,
    /** 16 kHz. */
    WujiAudioEqualizationBand16K = 9,
};

/** Audio reverberation type. */
typedef NS_ENUM(NSInteger, WujiAudioReverbType) {
    /** The level of the dry signal (dB). The value ranges between -20 and 10. */
    WujiAudioReverbDryLevel = 0,
    /** The level of the early reflection signal (wet signal) in dB. The value ranges between -20 and 10. */
    WujiAudioReverbWetLevel = 1,
    /** The room size of the reverberation. A larger room size means a stronger reverberation. The value ranges between 0 and 100. */
    WujiAudioReverbRoomSize = 2,
    /** The length of the initial delay of the wet signal (ms). The value ranges between 0 and 200. */
    WujiAudioReverbWetDelay = 3,
     /** The reverberation strength. The value ranges between 0 and 100. */
    WujiAudioReverbStrength = 4,
};

/** The preset audio voice configuration used to change the voice effect. */
typedef NS_ENUM(NSInteger, WujiAudioVoiceChanger) {
    /** Turn off the local voice changer, that is, to use the original voice. */
    WujiAudioVoiceChangerOff = 0x00000000,
    /** The voice of an old man. */
    WujiAudioVoiceChangerOldMan = 0x00000001,
    /** The voice of a little boy. */
    WujiAudioVoiceChangerBabyBoy = 0x00000002,
    /** The voice of a little girl. */
    WujiAudioVoiceChangerBabyGirl = 0x00000003,
    /** The voice of Zhu Bajie, a character in Journey to the West who has a voice like that of a growling bear. */
    WujiAudioVoiceChangerZhuBaJie = 0x00000004,
    /** The ethereal voice. */
    WujiAudioVoiceChangerEthereal = 0x00000005,
    /** The voice of Hulk. */
    WujiAudioVoiceChangerHulk = 0x00000006,
    /** A more vigorous voice. */
    WujiAudioVoiceBeautyVigorous = 0x00100001,
    /** A deeper voice. */
    WujiAudioVoiceBeautyDeep = 0x00100002,
    /** A mellower voice. */
    WujiAudioVoiceBeautyMellow = 0x00100003,
    /** Falsetto. */
    WujiAudioVoiceBeautyFalsetto = 0x00100004,
    /** A fuller voice. */
    WujiAudioVoiceBeautyFull = 0x00100005,
    /** A clearer voice. */
    WujiAudioVoiceBeautyClear = 0x00100006,
    /** A more resounding voice. */
    WujiAudioVoiceBeautyResounding = 0x00100007,
    /** A more ringing voice. */
    WujiAudioVoiceBeautyRinging = 0x00100008,
    /** A more spatially resonant voice. */
    WujiAudioVoiceBeautySpacial = 0x00100009,
    /** (For male only) A more magnetic voice. Do not use it when the speaker is a female; otherwise, voice distortion occurs. */
    WujiAudioGeneralBeautyVoiceMaleMagnetic = 0x00200001,
    /** (For female only) A fresher voice. Do not use it when the speaker is a male; otherwise, voice distortion occurs. */
    WujiAudioGeneralBeautyVoiceFemaleFresh = 0x00200002,
    /** (For female only) A more vital voice. Do not use it when the speaker is a male; otherwise, voice distortion occurs. */
    WujiAudioGeneralBeautyVoiceFemaleVitality = 0x00200003,
};

/** The preset local voice reverberation option. */
typedef NS_ENUM(NSInteger, WujiAudioReverbPreset) {
    /** Turn off local voice reverberation, that is, to use the original voice. */
    WujiAudioReverbPresetOff = 0x00000000,
    /** The reverberation style typical of a KTV venue (enhanced).  */
    WujiAudioReverbPresetFxKTV = 0x00100001,
    /** The reverberation style typical of a concert hall (enhanced). */
    WujiAudioReverbPresetFxVocalConcert = 0x00100002,
    /** The reverberation style typical of an uncle's voice. */
    WujiAudioReverbPresetFxUncle = 0x00100003,
    /** The reverberation style typical of a little sister's voice. */
    WujiAudioReverbPresetFxSister = 0x00100004,
    /** The reverberation style typical of a recording studio (enhanced).  */
    WujiAudioReverbPresetFxStudio = 0x00100005,
    /** The reverberation style typical of popular music (enhanced). */
    WujiAudioReverbPresetFxPopular = 0x00100006,
    /** The reverberation style typical of R&B music (enhanced). */
    WujiAudioReverbPresetFxRNB = 0x00100007,
    /** The reverberation style typical of the vintage phonograph. */
    WujiAudioReverbPresetFxPhonograph = 0x00100008,
    /** The reverberation style typical of popular music. */
    WujiAudioReverbPresetPopular = 0x00000001,
    /** The reverberation style typical of R&B music. */
    WujiAudioReverbPresetRnB = 0x00000002,
    /** The reverberation style typical of rock music. */
    WujiAudioReverbPresetRock = 0x00000003,
    /** The reverberation style typical of hip-hop music. */
    WujiAudioReverbPresetHipHop = 0x00000004,
    /** The reverberation style typical of a concert hall. */
    WujiAudioReverbPresetVocalConcert = 0x00000005,
    /** The reverberation style typical of a KTV venue. */
    WujiAudioReverbPresetKTV = 0x00000006,
    /** The reverberation style typical of a recording studio. */
    WujiAudioReverbPresetStudio = 0x00000007,
    /** The reverberation of the virtual stereo. The virtual stereo is an effect that renders the monophonic audio as the stereo audio, so that all users in the channel can hear the stereo voice effect. To achieve better virtual stereo reverberation, Wuji recommends setting the `profile` parameter in `setAudioProfile` as `WujiAudioProfileMusicHighQualityStereo(5)`. */
    WujiAudioReverbPresetVirtualStereo = 0x00200001
    
};

/** Audio session restriction. */
typedef NS_OPTIONS(NSUInteger, WujiAudioSessionOperationRestriction) {
    /** No restriction, the SDK has full control of the audio session operations. */
    WujiAudioSessionOperationRestrictionNone              = 0,
    /** The SDK does not change the audio session category. */
    WujiAudioSessionOperationRestrictionSetCategory       = 1,
    /** The SDK does not change any setting of the audio session (category, mode, categoryOptions). */
    WujiAudioSessionOperationRestrictionConfigureSession  = 1 << 1,
    /** The SDK keeps the audio session active when leaving a channel. */
    WujiAudioSessionOperationRestrictionDeactivateSession = 1 << 2,
    /** The SDK does not configure the audio session anymore. */
    WujiAudioSessionOperationRestrictionAll               = 1 << 7
};

/** Audio codec profile. */
typedef NS_ENUM(NSInteger, WujiAudioCodecProfileType) {
    /** (Default) LC-AAC, the low-complexity audio codec profile. */
  WujiAudioCodecProfileLCAAC = 0,
  /** HE-AAC, the high-efficiency audio codec profile. */
  WujiAudioCodecProfileHEAAC = 1
};

/** The state of the remote audio. */
typedef NS_ENUM(NSUInteger, WujiAudioRemoteState) {
    /** 0: The remote audio is in the default state, probably due to WujiAudioRemoteReasonLocalMuted(3), WujiAudioRemoteReasonRemoteMuted(5), or WujiAudioRemoteReasonRemoteOffline(7). */
    WujiAudioRemoteStateStopped = 0,
    /** 1: The first remote audio packet is received. */
    WujiAudioRemoteStateStarting = 1,
    /** 2: The remote audio stream is decoded and plays normally, probably due to WujiAudioRemoteReasonNetworkRecovery(2), WujiAudioRemoteReasonLocalUnmuted(4), or WujiAudioRemoteReasonRemoteUnmuted(6). */
    WujiAudioRemoteStateDecoding = 2,
    /** 3: The remote audio is frozen, probably due to WujiAudioRemoteReasonNetworkCongestion(1). */
    WujiAudioRemoteStateFrozen = 3,
    /** 4: The remote audio fails to start, probably due to WujiAudioRemoteReasonInternal(0). */
    WujiAudioRemoteStateFailed = 4,
};

/** The reason of the remote audio state change. */
typedef NS_ENUM(NSUInteger, WujiAudioRemoteStateReason) {
    /** 0: Internal reasons. */
    WujiAudioRemoteReasonInternal = 0,
    /** 1: Network congestion. */
    WujiAudioRemoteReasonNetworkCongestion = 1,
    /** 2: Network recovery. */
    WujiAudioRemoteReasonNetworkRecovery = 2,
    /** 3: The local user stops receiving the remote audio stream or disables the audio module. */
    WujiAudioRemoteReasonLocalMuted = 3,
    /** 4: The local user resumes receiving the remote audio stream or enables the audio module. */
    WujiAudioRemoteReasonLocalUnmuted = 4,
    /** 5: The remote user stops sending the audio stream or disables the audio module. */
    WujiAudioRemoteReasonRemoteMuted = 5,
    /** 6: The remote user resumes sending the audio stream or enables the audio module. */
    WujiAudioRemoteReasonRemoteUnmuted = 6,
    /** 7: The remote user leaves the channel. */
    WujiAudioRemoteReasonRemoteOffline = 7,
};

/** The state of the local audio. */
typedef NS_ENUM(NSUInteger, WujiAudioLocalState) {
    /** 0: The local audio is in the initial state. */
    WujiAudioLocalStateStopped = 0,
    /** 1: The recording device starts successfully.  */
    WujiAudioLocalStateRecording = 1,
    /** 2: The first audio frame encodes successfully. */
    WujiAudioLocalStateEncoding = 2,
    /** 3: The local audio fails to start. */
    WujiAudioLocalStateFailed = 3,
};

/** The error information of the local audio. */
typedef NS_ENUM(NSUInteger, WujiAudioLocalError) {
    /** 0: The local audio is normal. */
    WujiAudioLocalErrorOk = 0,
    /** 1: No specified reason for the local audio failure. */
    WujiAudioLocalErrorFailure = 1,
    /** 2: No permission to use the local audio device. */
    WujiAudioLocalErrorDeviceNoPermission = 2,
    /** 3: The microphone is in use. */
    WujiAudioLocalErrorDeviceBusy = 3,
    /** 4: The local audio recording fails. Check whether the recording device is working properly. */
    WujiAudioLocalErrorRecordFailure = 4,
    /** 5: The local audio encoding fails. */
    WujiAudioLocalErrorEncodeFailure = 5,
};

/** Media device type. */
typedef NS_ENUM(NSInteger, WujiMediaDeviceType) {
    /** Unknown device. */
    WujiMediaDeviceTypeAudioUnknown = -1,
    /** Audio playback device. */
    WujiMediaDeviceTypeAudioPlayout = 0,
    /** Audio recording device. */
    WujiMediaDeviceTypeAudioRecording = 1,
    /** Video render device. */
    WujiMediaDeviceTypeVideoRender = 2,
    /** Video capture device. */
    WujiMediaDeviceTypeVideoCapture = 3,
};

/** Connection states. */
typedef NS_ENUM(NSInteger, WujiConnectionStateType) {
    /** <p>1: The SDK is disconnected from Wuji's edge server.</p>
This is the initial state before [joinChannelByToken]([WujiRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]).<br>
The SDK also enters this state when the app calls [leaveChannel]([WujiRtcEngineKit leaveChannel:]).
    */
    WujiConnectionStateDisconnected = 1,
    /** <p>2: The SDK is connecting to Wuji's edge server.</p>
When the app calls [joinChannelByToken]([WujiRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]), the SDK starts to establish a connection to the specified channel, triggers the [connectionChangedToState]([WujiRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback, and switches to the `WujiConnectionStateConnecting` state.<br>
<br>
When the SDK successfully joins the channel, the SDK triggers the [connectionChangedToState]([WujiRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback and switches to the `WujiConnectionStateConnected` state.<br>
<br>
After the SDK joins the channel and when it finishes initializing the media engine, the SDK triggers the [didJoinChannel]([WujiRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]) callback.
*/
    WujiConnectionStateConnecting = 2,
    /** <p>3: The SDK is connected to Wuji's edge server and joins a channel. You can now publish or subscribe to a media stream in the channel.</p>
If the connection to the channel is lost because, for example, the network is down or switched, the SDK automatically tries to reconnect and triggers:
<li> The [rtcEngineConnectionDidInterrupted]([WujiRtcEngineDelegate rtcEngineConnectionDidInterrupted:])(deprecated) callback
<li> The [connectionChangedToState]([WujiRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback, and switches to the `WujiConnectionStateReconnecting` state.
    */
    WujiConnectionStateConnected = 3,
    /** <p>4: The SDK keeps rejoining the channel after being disconnected from a joined channel because of network issues.</p>
<li>If the SDK cannot rejoin the channel within 10 seconds after being disconnected from Wuji's edge server, the SDK triggers the [rtcEngineConnectionDidLost]([WujiRtcEngineDelegate rtcEngineConnectionDidLost:]) callback, stays in the `WujiConnectionStateReconnecting` state, and keeps rejoining the channel.
<li>If the SDK fails to rejoin the channel 20 minutes after being disconnected from Wuji's edge server, the SDK triggers the [connectionChangedToState]([WujiRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callback, switches to the `WujiConnectionStateFailed` state, and stops rejoining the channel.
    */
    WujiConnectionStateReconnecting = 4,
    /** <p>5: The SDK fails to connect to Wuji's edge server or join the channel.</p>
You must call [leaveChannel]([WujiRtcEngineKit leaveChannel:]) to leave this state, and call [joinChannelByToken]([WujiRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) again to rejoin the channel.<br>
<br>
If the SDK is banned from joining the channel by Wuji's edge server (through the RESTful API), the SDK triggers the [rtcEngineConnectionDidBanned]([WujiRtcEngineDelegate rtcEngineConnectionDidBanned:])(deprecated) and [connectionChangedToState]([WujiRtcEngineDelegate rtcEngine:connectionChangedToState:reason:]) callbacks.
    */
    WujiConnectionStateFailed = 5,
};

/** Reasons for the connection state change. */
typedef NS_ENUM(NSUInteger, WujiConnectionChangedReason) {
    /** 0: The SDK is connecting to Wuji's edge server. */
    WujiConnectionChangedConnecting = 0,
    /** 1: The SDK has joined the channel successfully. */
    WujiConnectionChangedJoinSuccess = 1,
    /** 2: The connection between the SDK and Wuji's edge server is interrupted.  */
    WujiConnectionChangedInterrupted = 2,
    /** 3: The connection between the SDK and Wuji's edge server is banned by Wuji's edge server. */
    WujiConnectionChangedBannedByServer = 3,
    /** 4: The SDK fails to join the channel for more than 20 minutes and stops reconnecting to the channel. */
    WujiConnectionChangedJoinFailed = 4,
    /** 5: The SDK has left the channel. */
    WujiConnectionChangedLeaveChannel = 5,
    /** 6: The specified App ID is invalid. Try to rejoin the channel with a valid App ID. */
    WujiConnectionChangedInvalidAppId = 6,
    /** 7: The specified channel name is invalid. Try to rejoin the channel with a valid channel name. */
    WujiConnectionChangedInvalidChannelName = 7,
    /** 8: The generated token is invalid probably due to the following reasons:
<li>The App Certificate for the project is enabled in Console, but you do not use Token when joining the channel. If you enable the App Certificate, you must use a token to join the channel.
<li>The uid that you specify in the [joinChannelByToken]([WujiRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method is different from the uid that you pass for generating the token. */
    WujiConnectionChangedInvalidToken = 8,
    /** 9: The token has expired. Generate a new token from your server. */
    WujiConnectionChangedTokenExpired = 9,
    /** 10: The user is banned by the server. */
    WujiConnectionChangedRejectedByServer = 10,
    /** 11: The SDK tries to reconnect after setting a proxy server. */
    WujiConnectionChangedSettingProxyServer = 11,
    /** 12: The token renews. */
    WujiConnectionChangedRenewToken = 12,
    /** 13: The client IP address has changed, probably due to a change of the network type, IP address, or network port. */
    WujiConnectionChangedClientIpAddressChanged = 13,
    /** 14: Timeout for the keep-alive of the connection between the SDK and Wuji's edge server. The connection state changes to WujiConnectionStateReconnecting(4). */
    WujiConnectionChangedKeepAliveTimeout = 14,
};

/** The state code in WujiChannelMediaRelayState.
 */
typedef NS_ENUM(NSInteger, WujiChannelMediaRelayState) {
    /** 0: The SDK is initializing.
     */
    WujiChannelMediaRelayStateIdle = 0,
    /** 1: The SDK tries to relay the media stream to the destination channel.
     */
    WujiChannelMediaRelayStateConnecting = 1,
    /** 2: The SDK successfully relays the media stream to the destination channel.
     */
    WujiChannelMediaRelayStateRunning = 2,
    /** 3: A failure occurs. See the details in `error`.
     */
    WujiChannelMediaRelayStateFailure = 3,
};

/** The event code in WujiChannelMediaRelayEvent.
 */
typedef NS_ENUM(NSInteger, WujiChannelMediaRelayEvent) {
    /** 0: The user disconnects from the server due to poor network connections.
     */
    WujiChannelMediaRelayEventDisconnect = 0,
    /** 1: The network reconnects.
     */
    WujiChannelMediaRelayEventConnected = 1,
    /** 2: The user joins the source channel.
     */
    WujiChannelMediaRelayEventJoinedSourceChannel = 2,
    /** 3: The user joins the destination channel.
     */
    WujiChannelMediaRelayEventJoinedDestinationChannel = 3,
    /** 4: The SDK starts relaying the media stream to the destination channel.
     */
    WujiChannelMediaRelayEventSentToDestinationChannel = 4,
    /** 5: The server receives the video stream from the source channel.
     */
    WujiChannelMediaRelayEventReceivedVideoPacketFromSource = 5,
    /** 6: The server receives the audio stream from the source channel.
     */
    WujiChannelMediaRelayEventReceivedAudioPacketFromSource = 6,
    /** 7: The destination channel is updated.
     */
    WujiChannelMediaRelayEventUpdateDestinationChannel = 7,
    /** 8: The destination channel update fails due to internal reasons.
     */
    WujiChannelMediaRelayEventUpdateDestinationChannelRefused = 8,
    /** 9: The destination channel does not change, which means that the destination channel fails to be updated.
     */
    WujiChannelMediaRelayEventUpdateDestinationChannelNotChange = 9,
    /** 10: The destination channel name is NULL.
     */
    WujiChannelMediaRelayEventUpdateDestinationChannelIsNil = 10,
    /** 11: The video profile is sent to the server.
     */
    WujiChannelMediaRelayEventVideoProfileUpdate = 11,
};

/** The error code in WujiChannelMediaRelayError.
 */
typedef NS_ENUM(NSInteger, WujiChannelMediaRelayError) {
    /** 0: The state is normal.
     */
    WujiChannelMediaRelayErrorNone = 0,
    /** 1: An error occurs in the server response.
     */
    WujiChannelMediaRelayErrorServerErrorResponse = 1,
    /** 2: No server response. You can call the [leaveChannel]([WujiRtcEngineKit leaveChannel:]) method to leave the channel.
     */
    WujiChannelMediaRelayErrorServerNoResponse = 2,
    /** 3: The SDK fails to access the service, probably due to limited resources of the server.
     */
    WujiChannelMediaRelayErrorNoResourceAvailable = 3,
    /** 4: Fails to send the relay request.
     */
    WujiChannelMediaRelayErrorFailedJoinSourceChannel = 4,
    /** 5: Fails to accept the relay request.
     */
    WujiChannelMediaRelayErrorFailedJoinDestinationChannel = 5,
    /** 6: The server fails to receive the media stream.
     */
    WujiChannelMediaRelayErrorFailedPacketReceivedFromSource = 6,
    /** 7: The server fails to send the media stream.
     */
    WujiChannelMediaRelayErrorFailedPacketSentToDestination = 7,
    /** 8: The SDK disconnects from the server due to poor network connections. You can call the [leaveChannel]([WujiRtcEngineKit leaveChannel:]) method to leave the channel.
     */
    WujiChannelMediaRelayErrorServerConnectionLost = 8,
    /** 9: An internal error occurs in the server.
     */
    WujiChannelMediaRelayErrorInternalError = 9,
    /** 10: The token of the source channel has expired.    
     */
    WujiChannelMediaRelayErrorSourceTokenExpired = 10,
    /** 11: The token of the destination channel has expired.
     */
    WujiChannelMediaRelayErrorDestinationTokenExpired = 11,
};

/** Network type. */
typedef NS_ENUM(NSInteger, WujiNetworkType) {
  /** -1: The network type is unknown. */
  WujiNetworkTypeUnknown = -1,
  /** 0: The SDK disconnects from the network. */
  WujiNetworkTypeDisconnected = 0,
  /** 1: The network type is LAN. */
  WujiNetworkTypeLAN = 1,
  /** 2: The network type is Wi-Fi (including hotspots). */
  WujiNetworkTypeWIFI = 2,
  /** 3: The network type is mobile 2G. */
  WujiNetworkTypeMobile2G = 3,
  /** 4: The network type is mobile 3G. */
  WujiNetworkTypeMobile3G = 4,
  /** 5: The network type is mobile 4G. */
  WujiNetworkTypeMobile4G = 5,
};

/** The video encoding degradation preference under limited bandwidth. */
typedef NS_ENUM(NSInteger, WujiDegradationPreference) {
    /** (Default) Degrades the frame rate to guarantee the video quality. */
    WujiDegradationMaintainQuality = 0,
    /** Degrades the video quality to guarantee the frame rate. */
    WujiDegradationMaintainFramerate = 1,
    /** Reserved for future use. */
    WujiDegradationBalanced = 2,
};
/** The lightening contrast level. */
typedef NS_ENUM(NSUInteger, WujiLighteningContrastLevel) {
    /** Low contrast level. */
    WujiLighteningContrastLow = 0,
    /** (Default) Normal contrast level. */
    WujiLighteningContrastNormal = 1,
    /** High contrast level. */
    WujiLighteningContrastHigh = 2,
};

/** The state of the probe test result. */
typedef NS_ENUM(NSUInteger, WujiLastmileProbeResultState) {
  /** 1: the last-mile network probe test is complete. */
  WujiLastmileProbeResultComplete = 1,
  /** 2: the last-mile network probe test is incomplete and the bandwidth estimation is not available, probably due to limited test resources. */
  WujiLastmileProbeResultIncompleteNoBwe = 2,
  /** 3: the last-mile network probe test is not carried out, probably due to poor network conditions. */
  WujiLastmileProbeResultUnavailable = 3,
};

/** The state of the local video stream. */
typedef NS_ENUM(NSInteger, WujiLocalVideoStreamState) {
  /** 0: the local video is in the initial state. */
  WujiLocalVideoStreamStateStopped = 0,
  /** 1: the local video capturer starts successfully. */
  WujiLocalVideoStreamStateCapturing = 1,
  /** 2: the first local video frame encodes successfully. */
  WujiLocalVideoStreamStateEncoding = 2,
  /** 3: the local video fails to start. */
  WujiLocalVideoStreamStateFailed = 3,
};

/** The detailed error information of the local video. */
typedef NS_ENUM(NSInteger, WujiLocalVideoStreamError) {
  /** 0: the local video is normal. */
  WujiLocalVideoStreamErrorOK = 0,
  /** 1: no specified reason for the local video failure. */
  WujiLocalVideoStreamErrorFailure = 1,
  /** 2: no permission to use the local video device. */
  WujiLocalVideoStreamErrorDeviceNoPermission = 2,
  /** 3: the local video capturer is in use. */
  WujiLocalVideoStreamErrorDeviceBusy = 3,
  /** 4: the local video capture fails. Check whether the capturer is working properly. */
  WujiLocalVideoStreamErrorCaptureFailure = 4,
  /** 5: the local video encoding fails. */
  WujiLocalVideoStreamErrorEncodeFailure = 5,
  /** 11: (macOS only) The shared window is minimized when you call
      [startScreenCaptureByWindowId]([WujiRtcEngineKit startScreenCaptureByWindowId:rectangle:parameters:]) to share a window.
      @since v3.1.0
  */
  WujiLocalVideoStreamErrorScreenCaptureWindowMinimized = 11,
  /** 12: (macOS only) The error code indicates that a window shared by the window ID has been closed, or a full-screen
     window shared by the window ID has exited full-screen mode. After exiting
     full-screen mode, remote users cannot see the shared window. To prevent remote users from seeing a black screen, Wuji recommends
     that you immediately stop screen sharing.
     <p>Common scenarios for reporting this error code:</p>
     <li>When the local user closes the shared window, the SDK reports this error code.</li>
     <li>The local user shows some slides in full-screen mode first, and then shares the windows of the slides. After the user exis full-screen
     mode, the SDK reports this error code.</li>
     <li>The local user watches web video or reads web document in full-screen mode first, and then shares the window of the web video or
     document. After the user exits full-screen mode, the SDK reports this error code.</li>
     
     @since v3.2.0
  */
  WujiLocalVideoStreamErrorScreenCaptureWindowClosed = 12,
};
/** IP areas.
 */ 
typedef NS_ENUM(NSUInteger, WujiIpAreaCode) {
     /** Mainland China
     */
     WujiIpAreaCode_CN = (1 << 0),
     /** North America
     */
     WujiIpAreaCode_NA = (1 << 1),
     /** Europe
     */
     WujiIpAreaCode_EUR = (1 << 2),
     /** Asia, excluding Mainland China
     */
     WujiIpAreaCode_AS = (1 << 3),
     /** (Default) Global
     */
     WujiIpAreaCode_GLOBAL = (0xFFFFFFFF)
 };
