//
//  VideoChatViewController.swift
//  Wuji Mac Tutorial Swift
//
//  Created by 3 on 2020/12/18.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import Cocoa
import WujiRTCFramework

protocol VideoChatDelegate: NSObjectProtocol {
    func VideoChatNeedClose(_ VideoChat: VideoChatViewController)
}

var WujiKit: WujiRtcEngineKit!
weak var delegate: VideoChatDelegate?

class VideoChatViewController: NSViewController {
    @IBOutlet weak var localVideo: NSView!
    @IBOutlet weak var remoteVideo: NSView!
    @IBOutlet weak var controlButtons: NSView!
    @IBOutlet weak var remoteVideoMutedIndicator: NSImageView!
    @IBOutlet weak var localVideoMutedBg: NSImageView!
    @IBOutlet weak var localVideoMutedIndicator: NSImageView!
    
    lazy var muteAudio: Bool = false
    lazy var muteVideo: Bool = false
    lazy var screenShare: Bool = false

    override func viewDidLoad() {
        super.viewDidLoad()

        self.view.wantsLayer = true
        self.remoteVideo.wantsLayer = true
        self.localVideo.wantsLayer = true
        
        setupButtons()
        hideVideoMuted()
        initializeWujiEngine()
        setupVideo()
        setupLocalVideo()
        joinChannel()
    }

    override func viewWillAppear() {
        super.viewWillAppear()
        
        view.layer?.backgroundColor = NSColor.black.cgColor
        remoteVideo.layer?.backgroundColor = NSColor.clear.cgColor
        localVideo.layer?.backgroundColor = NSColor.clear.cgColor
    }
    
    /// Create the wuji instance.
    func initializeWujiEngine() {
        WujiKit = WujiRtcEngineKit.sharedEngine(withAppId: AppID, delegate: self)
    }
    
    func setupVideo() {
        WujiKit.enableVideo()  // Default mode is disableVideo
        
        // Set video configuration
        // Please go to this page for detailed explanation
        let configuration = WujiVideoEncoderConfiguration(size: WujiVideoDimension960x720,
                                                           frameRate: .fps15,
                                                           bitrate: WujiVideoBitrateStandard,
                                                           orientationMode: .adaptative)
        WujiKit.setVideoEncoderConfiguration(configuration)
    }
    
    func setupLocalVideo() {
        // This is used to set a local preview.
        // The steps setting local and remote view are very similar.
        // But note that if the local user do not have a uid or do
        // not care what the uid is, he can set his uid as ZERO.
        // Our server will assign one and return the uid via the block
        // callback (joinSuccessBlock) after
        // joining the channel successfully.
        let videoCanvas = WujiRtcVideoCanvas()
        videoCanvas.uid = 0
        videoCanvas.view = localVideo
        videoCanvas.renderMode = .hidden
        WujiKit.setupLocalVideo(videoCanvas)
        WujiKit.startPreview()
    }
    
    func joinChannel() {
        // 1. Users can only see each other after they join the
        // same channel successfully using the same app id.
        // 2. One token is only valid for the channel name that
        // you use to generate this token.
        WujiKit.joinChannel(byToken: Token, channelId: "demoChannel1", info:nil, uid:0) { (sid, uid, elapsed) -> Void in
            // did join channel "demoChannel1"
        }
    }
    
    @IBAction func didClickHangUpButton(_ sender: NSButton) {
        leaveChannel()
    }
    
    func leaveChannel() {
        // leave channel and end chat
        WujiKit.leaveChannel(nil)
        WujiKit.setupLocalVideo(nil)
        remoteVideo.removeFromSuperview()
        localVideo.removeFromSuperview()
        delegate?.VideoChatNeedClose(self)
        WujiRtcEngineKit.destroy()
        WujiKit = nil
        view.window!.close()
    }
    
    func setupButtons() {
        perform(#selector(hideControlButtons), with:nil, afterDelay:3)
        
        let remoteVideoTrackingArea = NSTrackingArea(rect: remoteVideo.bounds,
                                                  options: [NSTrackingArea.Options.mouseMoved, NSTrackingArea.Options.activeInActiveApp, NSTrackingArea.Options.inVisibleRect],
                                                    owner: self,
                                                 userInfo: nil)
        remoteVideo.addTrackingArea(remoteVideoTrackingArea)
    
        let controlButtonsTrackingArea = NSTrackingArea(rect: controlButtons.bounds,
                                                     options: [NSTrackingArea.Options.mouseEnteredAndExited, NSTrackingArea.Options.activeInActiveApp, NSTrackingArea.Options.inVisibleRect],
                                                     owner: self,
                                                     userInfo: nil)
        controlButtons.addTrackingArea(controlButtonsTrackingArea)
    }
    
    @objc func hideControlButtons() {
        controlButtons.isHidden = true
    }
    
    override func mouseMoved(with theEvent : NSEvent) {
        if (controlButtons.isHidden) {
            controlButtons.isHidden = false
            perform(#selector(hideControlButtons), with:nil, afterDelay:3)
        }
    }
    
    override func mouseEntered(with theEvent : NSEvent) {
        VideoChatViewController.cancelPreviousPerformRequests(withTarget: self)
    }
    
     override func mouseExited(with theEvent : NSEvent) {
        perform(#selector(hideControlButtons), with:nil, afterDelay:3)
    }
    
    @IBAction func didClickMuteButton(_ sender: NSButton) {
        muteAudio = !muteAudio
        // mute local audio
        WujiKit.muteLocalAudioStream(muteAudio)
    
        if (muteAudio) {
            sender.image = NSImage(named:"muteButtonSelected")
        } else {
            sender.image = NSImage(named:"muteButton")
        }
    }
    
    @IBAction func didClickVideoMuteButton(_ sender: NSButton) {
        muteVideo = !muteVideo
        // mute local video
        WujiKit.muteLocalVideoStream(muteVideo)
    
        if (muteVideo) {
            sender.image = NSImage(named:"videoMuteButtonSelected")
        } else {
            sender.image = NSImage(named:"videoMuteButton")
        }
        localVideo.isHidden = muteVideo
        localVideoMutedBg.isHidden = !(muteVideo)
        localVideoMutedIndicator.isHidden = !(muteVideo)
    }
    
    func hideVideoMuted() {
        remoteVideoMutedIndicator.isHidden = true
        localVideoMutedBg.isHidden = true
        localVideoMutedIndicator.isHidden = true
    }
    
    @IBAction func didClickDeviceSelectionButton(_ sender: NSButton) {
        let deviceSelectionViewController: NSViewController = {
            return self.storyboard!.instantiateController(withIdentifier: "DeviceSelectionViewController")
                as! NSViewController
        }()
        self.presentAsSheet(deviceSelectionViewController)
        // Segue to sheet view controller DeviceSelectionViewController
    }
    
    @IBAction func didClickScreenShareButton(_ sender: NSButton) {
        screenShare = !screenShare
        if (screenShare) {
            sender.image = NSImage(named:"screenShareButtonSelected")
            // Start the screen capture with default parameters
            WujiKit.startScreenCapture(byDisplayId: UInt(CGMainDisplayID()),
                                        rectangle: CGRect.zero,
                                        parameters: WujiScreenCaptureParameters())
        } else {
            sender.image = NSImage(named:"screenShareButton")
            // Stop the screen capture
            WujiKit.stopScreenCapture()
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
        if (remoteVideo.isHidden) {
            remoteVideo.isHidden = false
        }
        let videoCanvas = WujiRtcVideoCanvas()
        videoCanvas.uid = uid
        videoCanvas.view = remoteVideo
        videoCanvas.renderMode = .hidden
        WujiKit.setupRemoteVideo(videoCanvas)
    }
    
    /// Occurs when a remote user (Communication)/host (Live Broadcast) leaves a channel.
    /// - Parameters:
    ///   - engine: RTC engine instance
    ///   - uid: ID of the user or host who leaves a channel or goes offline.
    ///   - reason: Reason why the user goes offline
    func rtcEngine(_ engine: WujiRtcEngineKit, didOfflineOfUid uid:UInt, reason:WujiUserOfflineReason) {
        self.remoteVideo.isHidden = true
    }
    
    /// Occurs when a remote user’s video stream playback pauses/resumes.
    /// - Parameters:
    ///   - engine: RTC engine instance
    ///   - muted: YES for paused, NO for resumed.
    ///   - byUid: User ID of the remote user.
    func rtcEngine(_ engine: WujiRtcEngineKit, didVideoMuted muted:Bool, byUid:UInt) {
        remoteVideo.isHidden = muted
        remoteVideoMutedIndicator.isHidden = !muted
    }
}
