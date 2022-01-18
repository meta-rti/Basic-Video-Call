//
//  VideoEngine.swift
//  Meta-iOS-Tutorial-SwiftUI-1to1
//
//  Created by 3 on 2020/12/17.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import MetaRTCFramework

class VideoEngine: NSObject {
    // init MetaRtcEngineKit
    lazy var metaEngine = MetaRtcEngineKit.sharedEngine(withAppId: AppID, delegate: self)
    var contentView: ContentView?
}

extension VideoEngine: MetaRtcEngineDelegate {
    func rtcEngine(_ engine: MetaRtcEngineKit, didJoinChannel channel: String, withUid uid: UInt, elapsed: Int) {
        contentView?.log(content: "did join channel")
    }
    
    func rtcEngine(_ engine: MetaRtcEngineKit, didLeaveChannelWith stats: MetaChannelStats) {
        contentView?.log(content: "did leave channel")
        contentView?.isLocalAudioMuted = false
    }
    
    func rtcEngine(_ engine: MetaRtcEngineKit, didJoinedOfUid uid: UInt, elapsed: Int) {
        contentView?.isRemoteInSession = true
    }
    
    func rtcEngine(_ engine: MetaRtcEngineKit, didOfflineOfUid uid: UInt, reason: MetaUserOfflineReason) {
        contentView?.isRemoteInSession = false
    }
    
    func rtcEngine(_ engine: MetaRtcEngineKit, firstRemoteVideoDecodedOfUid uid: UInt, size: CGSize, elapsed: Int) {
        // Only one remote video view is available for this
        // tutorial. Here we check if there exists a surface
        // view tagged as this uid.
        let videoCanvas = MetaRtcVideoCanvas()
        videoCanvas.view = contentView?.remoteCanvas.rendererView
        videoCanvas.renderMode = .hidden
        videoCanvas.uid = uid
        metaEngine.setupRemoteVideo(videoCanvas)

        contentView?.isRemoteVideoMuted = false
    }
    
    func rtcEngine(_ engine: MetaRtcEngineKit, didVideoMuted muted:Bool, byUid:UInt) {
        contentView?.isRemoteVideoMuted = muted
    }
    
    func rtcEngine(_ engine: MetaRtcEngineKit, didOccurWarning warningCode: MetaWarningCode) {
        contentView?.log(content: "did occur warning: \(warningCode.rawValue)")
    }
    
    func rtcEngine(_ engine: MetaRtcEngineKit, didOccurError errorCode: MetaErrorCode) {
        contentView?.log(content: "did occur error: \(errorCode.rawValue)")
    }
}
