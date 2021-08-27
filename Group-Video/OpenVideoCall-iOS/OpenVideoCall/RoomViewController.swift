//
//  RoomViewController.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import UIKit
import WujiRTCFramework

protocol RoomVCDataSource: NSObjectProtocol {
    func roomVCNeedWujiKit() -> WujiRtcEngineKit
    func roomVCNeedSettings() -> Settings
}

class RoomViewController: UIViewController {
    
    @IBOutlet weak var containerView: WJEVideoContainer!
    @IBOutlet weak var messageTableContainerView: UIView!
    
    @IBOutlet weak var cameraButton: UIButton!
    @IBOutlet weak var audioMixingButton: UIButton!
    @IBOutlet weak var speakerPhoneButton: UIButton!
    @IBOutlet weak var beautyButton: UIButton!
    @IBOutlet weak var muteVideoButton: UIButton!
    @IBOutlet weak var muteAudioButton: UIButton!
    
    @IBOutlet var backgroundDoubleTap: UITapGestureRecognizer!
    
    private var wujiKit: WujiRtcEngineKit {
        return dataSource!.roomVCNeedWujiKit()
    }
    
    private var settings: Settings {
        return dataSource!.roomVCNeedSettings()
    }
    
    private var isSwitchCamera = true {
        didSet {
            wujiKit.switchCamera()
        }
    }
    
    private var isAudioMixing = false {
        didSet {
            guard oldValue != isAudioMixing else {
                return
            }
            audioMixingButton?.isSelected = isAudioMixing
            if isAudioMixing {
                // play music file
                wujiKit.startAudioMixing(
                    FileCenter.audioFilePath(),
                    loopback: false,
                    replace: false,
                    cycle: 1
                )
            } else {
                // stop play
                wujiKit.stopAudioMixing()
            }
        }
    }
    
    private var isBeauty = false {
        didSet {
            guard oldValue != isBeauty else {
                return
            }
            beautyButton?.isSelected = isBeauty
            var options: WujiBeautyOptions? = nil
            if isBeauty {
                options = WujiBeautyOptions()
                options?.lighteningContrastLevel = .normal
                options?.lighteningLevel = 0.7
                options?.smoothnessLevel = 0.5
                options?.rednessLevel = 0.1
            }
            // improve local render view
            wujiKit.setBeautyEffectOptions(isBeauty, options: options)
        }
    }
    
    private var isSpeakerPhone = true {
        didSet {
            guard oldValue != isSpeakerPhone else {
                return
            }
            speakerPhoneButton.isSelected = !isSpeakerPhone
            // switch playout audio route
            wujiKit.setEnableSpeakerphone(!isSpeakerPhone)
        }
    }
    
    private var isVideoMuted = false {
        didSet {
            guard oldValue != isVideoMuted else {
                return
            }
            muteVideoButton?.isSelected = isVideoMuted
            setVideoMuted(isVideoMuted, forUid: 0)
            updateSelfViewVisiable()
            // mute local video
            wujiKit.muteLocalVideoStream(isVideoMuted)
        }
    }
    
    private var isAudioMuted = false {
        didSet {
            guard oldValue != isAudioMuted else {
                return
            }
            muteAudioButton?.isSelected = isAudioMuted
            // mute local audio
            wujiKit.muteLocalAudioStream(isAudioMuted)
        }
    }
    
    private var isDebugMode = false {
        didSet {
            guard oldValue != isDebugMode else {
                return
            }
            options.isDebugMode = isDebugMode
            messageTableContainerView.isHidden = !isDebugMode
        }
    }
    
    private var videoSessions = [VideoSession]() {
        didSet {
            updateBroadcastersView()
        }
    }
    
    private let maxVideoSession = 4
    
    private weak var optionsVC: RoomOptionsViewController?
    private lazy var options = RoomOptions(isDebugMode: false)
    private var messageVC: MessageViewController?
   
    weak var dataSource: RoomVCDataSource?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = settings.roomName
        loadWujiKit()
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        guard let segueId = segue.identifier else {
            return
        }
        
        switch segueId {
        case "roomEmbedMessage":
            messageVC = segue.destination as? MessageViewController
        case "roomToOptions":
            let optionsVC = segue.destination as? RoomOptionsViewController
            optionsVC?.delegate = self
            optionsVC?.dataSource = self
            self.optionsVC = optionsVC
        default:
            break
        }
    }
    
    deinit {
        leaveChannel()
    }
    
    @IBAction func doAudioMixingPressed(_ sender: UIButton) {
        isAudioMixing.toggle()
    }
    
    @IBAction func doBeautyPressed(_ sender: UIButton) {
        isBeauty.toggle()
    }
    
    @IBAction func doSpeakerPhonePressed(_ sender: UIButton) {
        isSpeakerPhone.toggle()
    }
    
    @IBAction func doMuteVideoPressed(_ sender: UIButton) {
        isVideoMuted.toggle()
    }
    
    @IBAction func doMuteAudioPressed(_ sender: UIButton) {
        isAudioMuted.toggle()
    }
    
    @IBAction func doCameraPressed(_ sender: UIButton) {
        isSwitchCamera.toggle()
    }
}

// MARK: - WujiRtcEngineKit
private extension RoomViewController {
    func loadWujiKit() {
        // Step 1, set delegate
        wujiKit.delegate = self
        // Step 2, set communication mode
        wujiKit.setChannelProfile(.communication)
        
        // Step 3, enable the video module
        wujiKit.enableVideo()
        // set video configuration
        wujiKit.setVideoEncoderConfiguration(
            WujiVideoEncoderConfiguration(
                size: settings.dimension,
                frameRate: settings.frameRate,
                bitrate: WujiVideoBitrateStandard,
                orientationMode: .adaptative
            )
        )
        // add local render view and start preview
        addLocalSession()
        wujiKit.startPreview()
        
        // Step 4, enable encryption mode
        if let type = settings.encryptionType, let text = type.text, !text.isEmpty {
//            let config = WujiEncryptionConfig()
//            config.encryptionKey = text
//            config.encryptionMode = type.modeValue()
//            wujiKit.enableEncryption(true, encryptionConfig: config)
        }
        
        // Step 5, join channel and start group chat
        // If join  channel success, WujiKit triggers it's delegate function
        // 'rtcEngine(_ engine: WujiRtcEngineKit, didJoinChannel channel: String, withUid uid: UInt, elapsed: Int)'
        wujiKit.joinChannel(byToken: KeyCenter.Token, channelId: settings.roomName!, info: nil, uid: 0, joinSuccess: nil)
        setIdleTimerActive(false)
    }
    
    func addLocalSession() {
        let localSession = VideoSession.localSession()
        localSession.updateInfo(fps: settings.frameRate.rawValue)
        videoSessions.append(localSession)
        wujiKit.setupLocalVideo(localSession.canvas)
    }
    
    func leaveChannel() {
        // Step 1, release local WujiRtcVideoCanvas instance
        wujiKit.setupLocalVideo(nil)
        // Step 2, leave channel and end group chat
        wujiKit.leaveChannel(nil)
        WujiRtcEngineKit.destroy()
        // Step 3, please attention, stop preview after leave channel
        wujiKit.stopPreview()
        
        // Step 4, remove all render views
        for session in videoSessions {
            session.hostingView.removeFromSuperview()
        }
        videoSessions.removeAll()
        
        setIdleTimerActive(true)
    }
}

// MARK: - WujiRtcEngineDelegate
extension RoomViewController: WujiRtcEngineDelegate {
    
    /// Occurs when the local user joins a specified channel.
    /// - Parameters:
    ///   - engine: the Wuji engine
    ///   - channel: channel name
    ///   - uid: User ID. If the uid is specified in the joinChannelByToken method, the specified user ID is returned. If the user ID is not specified when the joinChannel method is called, the server automatically assigns a uid.
    ///   - elapsed: Time elapsed (ms) from the user calling the joinChannelByToken method until the SDK triggers this callback.
    func rtcEngine(_ engine: WujiRtcEngineKit, didJoinChannel channel: String, withUid uid: UInt, elapsed: Int) {
        info(string: "Join channel: \(channel)")
    }
    
    /// Occurs when the connection between the SDK and the server is interrupted.
    func rtcEngineConnectionDidInterrupted(_ engine: WujiRtcEngineKit) {
        alert(string: "Connection Interrupted")
    }
    
    /// Occurs when the SDK cannot reconnect to Wuji’s edge server 10 seconds after its connection to the server is interrupted.
    func rtcEngineConnectionDidLost(_ engine: WujiRtcEngineKit) {
        alert(string: "Connection Lost")
    }
    
    /// Reports an error during SDK runtime.
    func rtcEngine(_ engine: WujiRtcEngineKit, didOccurError errorCode: WujiErrorCode) {
        alert(string: "Occur error: \(errorCode.rawValue)")
    }
    
    // first remote video frame
    func rtcEngine(_ engine: WujiRtcEngineKit, firstRemoteVideoDecodedOfUid uid: UInt, size: CGSize, elapsed: Int) {
        guard videoSessions.count <= maxVideoSession else {
            return
        }
        
        let userSession = videoSession(of: uid)
        userSession.updateInfo(resolution: size)
        wujiKit.setupRemoteVideo(userSession.canvas)
    }
    
    // first local video frame
    func rtcEngine(_ engine: WujiRtcEngineKit, firstLocalVideoFrameWith size: CGSize, elapsed: Int) {
        if let selfSession = videoSessions.first {
            selfSession.updateInfo(resolution: size)
        }
    }
    
    // user offline
    func rtcEngine(_ engine: WujiRtcEngineKit, didOfflineOfUid uid: UInt, reason: WujiUserOfflineReason) {
        var indexToDelete: Int?
        for (index, session) in videoSessions.enumerated() where session.uid == uid {
            indexToDelete = index
            break
        }
        
        if let indexToDelete = indexToDelete {
            let deletedSession = videoSessions.remove(at: indexToDelete)
            deletedSession.hostingView.removeFromSuperview()
            
            // release canvas's view
            deletedSession.canvas.view = nil
            
            wujiKit.setupRemoteVideo(deletedSession.canvas)
        }
    }
    
    // video muted
    func rtcEngine(_ engine: WujiRtcEngineKit, didVideoMuted muted: Bool, byUid uid: UInt) {
        setVideoMuted(muted, forUid: uid)
    }
    
    // remote stat
    func rtcEngine(_ engine: WujiRtcEngineKit, remoteVideoStats stats: WujiRtcRemoteVideoStats) {
        if let session = getSession(of: stats.uid) {
            session.updateVideoStats(stats)
        }
    }
    
    // audio mixing
    func rtcEngineLocalAudioMixingDidFinish(_ engine: WujiRtcEngineKit) {
        isAudioMixing = false
    }
}

// MARK: RoomOptionsVCDelegate
extension RoomViewController: RoomOptionsVCDelegate {
    func roomOptionsVC(_ vc: RoomOptionsViewController, debugModeDid enable: Bool) {
        isDebugMode = enable
    }
}
// MARK: RoomOptionsVCDataSource
extension RoomViewController: RoomOptionsVCDataSource {
    func roomOptionsVCNeedOptions() -> RoomOptions {
        return options
    }
}

// MARK: - Private
private extension RoomViewController {
    // Update views
    func updateBroadcastersView() {
        // video views layout
        if videoSessions.count == maxVideoSession {
            containerView.reload(level: 0, animated: true)
        } else {
            var rank: Int
            var row: Int
            
            if videoSessions.count == 0 {
                containerView.removeLayout(level: 0)
                return
            } else if videoSessions.count == 1 {
                rank = 1
                row = 1
            } else if videoSessions.count == 2 {
                rank = 1
                row = 2
            } else {
                rank = 2
                row = Int(ceil(Double(videoSessions.count) / Double(rank)))
            }
            
            let itemWidth = CGFloat(1.0) / CGFloat(rank)
            let itemHeight = CGFloat(1.0) / CGFloat(row)
            let itemSize = CGSize(width: itemWidth, height: itemHeight)
            let layout = WJEVideoLayout(level: 0)
                        .itemSize(.scale(itemSize))
            
            containerView
                .listCount { [unowned self] (_) -> Int in
                    return self.videoSessions.count
                }.listItem { [unowned self] (index) -> UIView in
                    return self.videoSessions[index.item].hostingView
                }
            
            containerView.setLayouts([layout], animated: true)
        }
    }
    
    func getSession(of uid: UInt) -> VideoSession? {
        for session in videoSessions {
            if session.uid == uid {
                return session
            }
        }
        return nil
    }
    
    func videoSession(of uid: UInt) -> VideoSession {
        if let fetchedSession = getSession(of: uid) {
            return fetchedSession
        } else {
            let newSession = VideoSession(uid: uid)
            videoSessions.append(newSession)
            return newSession
        }
    }
    
    func updateSelfViewVisiable() {
        guard let selfView = videoSessions.first?.hostingView else {
            return
        }
        
        if videoSessions.count == 2 {
            selfView.isHidden = isVideoMuted
        } else {
            selfView.isHidden = false
        }
    }
    
    func setVideoMuted(_ muted: Bool, forUid uid: UInt) {
        getSession(of: uid)?.isVideoMuted = muted
    }
    
    func setIdleTimerActive(_ active: Bool) {
        UIApplication.shared.isIdleTimerDisabled = !active
    }
    
    // Log
    func info(string: String) {
        guard !string.isEmpty else {
            return
        }
        messageVC?.append(info: string)
    }
    
    func alert(string: String) {
        guard !string.isEmpty else {
            return
        }
        messageVC?.append(alert: string)
    }
}
