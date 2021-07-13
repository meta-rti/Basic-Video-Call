//
//  VideoEngine.swift
//  Wuji-iOS-Tutorial-SwiftUI-1to1
//
//  Created by 3 on 2020/12/17.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import WujiRTCFramework

class VideoEngine: NSObject {
    // init WujiRtcEngineKit
    lazy var wujiEngine = WujiRtcEngineKit.sharedEngine(withAppId: AppID, delegate: self)
    var contentView: ContentView?
}

extension VideoEngine: WujiRtcEngineDelegate {
    func rtcEngine(_ engine: WujiRtcEngineKit, didJoinChannel channel: String, withUid uid: UInt, elapsed: Int) {
        contentView?.log(content: "did join channel")
    }
    
    func rtcEngine(_ engine: WujiRtcEngineKit, didLeaveChannelWith stats: WujiChannelStats) {
        contentView?.log(content: "did leave channel")
        contentView?.isLocalAudioMuted = false
    }
    
    func rtcEngine(_ engine: WujiRtcEngineKit, didJoinedOfUid uid: UInt, elapsed: Int) {
        contentView?.isRemoteInSession = true
    }
    
    func rtcEngine(_ engine: WujiRtcEngineKit, didOfflineOfUid uid: UInt, reason: WujiUserOfflineReason) {
        contentView?.isRemoteInSession = false
    }
    
    func rtcEngine(_ engine: WujiRtcEngineKit, firstRemoteVideoDecodedOfUid uid: UInt, size: CGSize, elapsed: Int) {
        // Only one remote video view is available for this
        // tutorial. Here we check if there exists a surface
        // view tagged as this uid.
        let videoCanvas = WujiRtcVideoCanvas()
        videoCanvas.view = contentView?.remoteCanvas.rendererView
        videoCanvas.renderMode = .hidden
        videoCanvas.uid = uid
        wujiEngine.setupRemoteVideo(videoCanvas)

        contentView?.isRemoteVideoMuted = false
    }
    
    func rtcEngine(_ engine: WujiRtcEngineKit, didVideoMuted muted:Bool, byUid:UInt) {
        contentView?.isRemoteVideoMuted = muted
    }
    
    func rtcEngine(_ engine: WujiRtcEngineKit, didOccurWarning warningCode: WujiWarningCode) {
        contentView?.log(content: "did occur warning: \(warningCode.rawValue)")
    }
    
    func rtcEngine(_ engine: WujiRtcEngineKit, didOccurError errorCode: WujiErrorCode) {
        contentView?.log(content: "did occur error: \(errorCode.rawValue)")
    }
}
