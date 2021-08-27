//
//  VideoChatViewController.swift
//  Wuji iOS Tutorial
//
//  Created by 3 on 2020/12/17.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import UIKit
import WujiRTCFramework

class VideoChatViewController: UIViewController {
    @IBOutlet weak var localContainer: UIView!
    @IBOutlet weak var remoteContainer: UIView!
    @IBOutlet weak var remoteVideoMutedIndicator: UIImageView!
    @IBOutlet weak var localVideoMutedIndicator: UIView!
    @IBOutlet weak var micButton: UIButton!
    @IBOutlet weak var cameraButton: UIButton!
    
    weak var logVC: LogViewController?
    var wujiKit: WujiRtcEngineKit!
    var localVideo: WujiRtcVideoCanvas?
    var remoteVideo: WujiRtcVideoCanvas?
    
    var isRemoteVideoRender: Bool = true {
        didSet {
            if let it = localVideo, let view = it.view {
                if view.superview == localContainer {
                    remoteVideoMutedIndicator.isHidden = isRemoteVideoRender
                    remoteContainer.isHidden = !isRemoteVideoRender
                } else if view.superview == remoteContainer {
                    localVideoMutedIndicator.isHidden = isRemoteVideoRender
                }
            }
        }
    }
    
    var isLocalVideoRender: Bool = false {
        didSet {
            if let it = localVideo, let view = it.view {
                if view.superview == localContainer {
                    localVideoMutedIndicator.isHidden = isLocalVideoRender
                } else if view.superview == remoteContainer {
                    remoteVideoMutedIndicator.isHidden = isLocalVideoRender
                }
            }
        }
    }
    
    var isStartCalling: Bool = true {
        didSet {
            if isStartCalling {
                micButton.isSelected = false
            }
            micButton.isHidden = !isStartCalling
            cameraButton.isHidden = !isStartCalling
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // This is our usual steps for joining
        // a channel and starting a call.
        initializeWujiEngine()
        setupVideo()
        setupLocalVideo()
        joinChannel()
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        guard let identifier = segue.identifier else {
            return
        }
        
        if identifier == "EmbedLogViewController",
            let vc = segue.destination as? LogViewController {
            self.logVC = vc
        }
    }
    
    func initializeWujiEngine() {
        // init WujiRtcEngineKit
        wujiKit = WujiRtcEngineKit.sharedEngine(withAppId: AppID, delegate: self)
    }

    func setupVideo() {
        // In simple use cases, we only need to enable video capturing
        // and rendering once at the initialization step.
        // Note: audio recording and playing is enabled by default.
        wujiKit.enableVideo()
        
        // Set video configuration
        // Please go to this page for detailed explanation
        wujiKit.setVideoEncoderConfiguration(WujiVideoEncoderConfiguration(size: WujiVideoDimension640x360,
                                                                             frameRate: .fps15,
                                                                             bitrate: WujiVideoBitrateStandard,
                                                                             orientationMode: .adaptative))
    }
    
    func setupLocalVideo() {
        // This is used to set a local preview.
        // The steps setting local and remote view are very similar.
        // But note that if the local user do not have a uid or do
        // not care what the uid is, he can set his uid as ZERO.
        // Our server will assign one and return the uid via the block
        // callback (joinSuccessBlock) after
        // joining the channel successfully.
        let view = UIView(frame: CGRect(origin: CGPoint(x: 0, y: 0), size: localContainer.frame.size))
        localVideo = WujiRtcVideoCanvas()
        localVideo!.view = view
        localVideo!.renderMode = .hidden
        localVideo!.uid = 0
        localContainer.addSubview(localVideo!.view!)
        wujiKit.setupLocalVideo(localVideo)
        wujiKit.startPreview()
    }
    
    func joinChannel() {
        // Set audio route to speaker
        wujiKit.setDefaultAudioRouteToSpeakerphone(true)
        
        // 1. Users can only see each other after they join the
        // same channel successfully using the same app id.
        // 2. One token is only valid for the channel name that
        // you use to generate this token.
        wujiKit.joinChannel(byToken: Token, channelId: "demoChannel1", info: nil, uid: 0) { [unowned self] (channel, uid, elapsed) -> Void in
            // Did join channel "demoChannel1"
            self.isLocalVideoRender = true
            self.logVC?.log(type: .info, content: "did join channel")
        }
        isStartCalling = true
        UIApplication.shared.isIdleTimerDisabled = true
    }
    
    func leaveChannel() {
        // leave channel and end chat
        wujiKit.leaveChannel(nil)
        WujiRtcEngineKit.destroy()
        
        isRemoteVideoRender = false
        isLocalVideoRender = false
        isStartCalling = false
        UIApplication.shared.isIdleTimerDisabled = false
        self.logVC?.log(type: .info, content: "did leave channel")
    }
    
    @IBAction func didClickHangUpButton(_ sender: UIButton) {
        sender.isSelected.toggle()
        if sender.isSelected {
            leaveChannel()
            removeFromParent(localVideo)
            localVideo = nil
            removeFromParent(remoteVideo)
            remoteVideo = nil
        } else {
            initializeWujiEngine()
            setupVideo()
            setupLocalVideo()
            joinChannel()
        }
    }
    
    @IBAction func didClickMuteButton(_ sender: UIButton) {
        sender.isSelected.toggle()
        // mute local audio
        wujiKit.muteLocalAudioStream(sender.isSelected)
    }
    
    @IBAction func didClickSwitchCameraButton(_ sender: UIButton) {
        sender.isSelected.toggle()
        wujiKit.switchCamera()
    }
    
    @IBAction func didClickLocalContainer(_ sender: Any) {
        switchView(localVideo)
        switchView(remoteVideo)
    }
    
    func removeFromParent(_ canvas: WujiRtcVideoCanvas?) -> UIView? {
        if let it = canvas, let view = it.view {
            let parent = view.superview
            if parent != nil {
                view.removeFromSuperview()
                return parent
            }
        }
        return nil
    }
    
    func switchView(_ canvas: WujiRtcVideoCanvas?) {
        let parent = removeFromParent(canvas)
        if parent == localContainer {
            canvas!.view!.frame.size = remoteContainer.frame.size
            remoteContainer.addSubview(canvas!.view!)
        } else if parent == remoteContainer {
            canvas!.view!.frame.size = localContainer.frame.size
            localContainer.addSubview(canvas!.view!)
        }
    }
}

extension VideoChatViewController: WujiRtcEngineDelegate {
    
    /// Callback to handle the event when the first frame of a remote video stream is decoded on the device.
    /// - Parameters:
    ///   - engine: RTC engine instance
    ///   - uid: user id
    ///   - size: the height and width of the video frame
    ///   - elapsed: Time elapsed (ms) from the local user calling JoinChannel method until the SDK triggers this callback.
    func rtcEngine(_ engine: WujiRtcEngineKit, firstRemoteVideoDecodedOfUid uid:UInt, size:CGSize, elapsed:Int) {
        isRemoteVideoRender = true
        
        var parent: UIView = remoteContainer
        if let it = localVideo, let view = it.view {
            if view.superview == parent {
                parent = localContainer
            }
        }
        
        // Only one remote video view is available for this
        // tutorial. Here we check if there exists a surface
        // view tagged as this uid.
        if remoteVideo != nil {
            return
        }
        
        let view = UIView(frame: CGRect(origin: CGPoint(x: 0, y: 0), size: parent.frame.size))
        remoteVideo = WujiRtcVideoCanvas()
        remoteVideo!.view = view
        remoteVideo!.renderMode = .hidden
        remoteVideo!.uid = uid
        parent.addSubview(remoteVideo!.view!)
        wujiKit.setupRemoteVideo(remoteVideo!)
    }
    
    /// Occurs when a remote user (Communication)/host (Live Broadcast) leaves a channel.
    /// - Parameters:
    ///   - engine: RTC engine instance
    ///   - uid: ID of the user or host who leaves a channel or goes offline.
    ///   - reason: Reason why the user goes offline
    func rtcEngine(_ engine: WujiRtcEngineKit, didOfflineOfUid uid:UInt, reason:WujiUserOfflineReason) {
        isRemoteVideoRender = false
        if let it = remoteVideo, it.uid == uid {
            removeFromParent(it)
            remoteVideo = nil
        }
    }
    
    /// Occurs when a remote user’s video stream playback pauses/resumes.
    /// - Parameters:
    ///   - engine: RTC engine instance
    ///   - muted: YES for paused, NO for resumed.
    ///   - byUid: User ID of the remote user.
    func rtcEngine(_ engine: WujiRtcEngineKit, didVideoMuted muted:Bool, byUid:UInt) {
        isRemoteVideoRender = !muted
    }
    
    /// Reports a warning during SDK runtime.
    /// - Parameters:
    ///   - engine: RTC engine instance
    ///   - warningCode: Warning code
    func rtcEngine(_ engine: WujiRtcEngineKit, didOccurWarning warningCode: WujiWarningCode) {
        logVC?.log(type: .warning, content: "did occur warning, code: \(warningCode.rawValue)")
    }
    
    /// Reports an error during SDK runtime.
    /// - Parameters:
    ///   - engine: RTC engine instance
    ///   - errorCode: Error code
    func rtcEngine(_ engine: WujiRtcEngineKit, didOccurError errorCode: WujiErrorCode) {
        logVC?.log(type: .error, content: "did occur error, code: \(errorCode.rawValue)")
    }
}
