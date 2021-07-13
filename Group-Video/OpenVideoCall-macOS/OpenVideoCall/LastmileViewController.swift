//
//  LastmileViewController.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import Cocoa
import WujiRTCFramework

protocol LastmileVCDelegate: NSObjectProtocol {
    func lastmileVCNeedClose(_ lastmileVC: LastmileViewController)
}

protocol LastmileVCDataSource: NSObjectProtocol {
    func lastmileVCNeedWujiKit() -> WujiRtcEngineKit
}

class LastmileViewController: NSViewController {
    
    @IBOutlet weak var titleLabel: NSTextField!
    @IBOutlet weak var qualityLabel: NSTextField!
    @IBOutlet weak var rttLabel: NSTextField!
    @IBOutlet weak var uplinkLabel: NSTextField!
    @IBOutlet weak var downlinkLabel: NSTextField!
    @IBOutlet weak var activityView: NSProgressIndicator!
    
    @IBOutlet weak var lineView0: NSView!
    @IBOutlet weak var lineView1: NSView!
    @IBOutlet weak var lineView2: NSView!
    @IBOutlet weak var lineView3: NSView!
    @IBOutlet weak var lineView4: NSView!
    
    private var isLastmileProbeTesting = false {
        didSet {
            if isLastmileProbeTesting {
                let config = WujiLastmileProbeConfig()
                config.probeUplink = true
                config.probeDownlink = true
                config.expectedUplinkBitrate = 5000
                config.expectedDownlinkBitrate = 5000
                wujiKit.startLastmileProbeTest(config)
                activityView?.isHidden = false
                activityView?.startAnimation(nil)
                self.titleLabel.stringValue = "Testing..."
            } else {
                wujiKit.stopLastmileProbeTest()
                activityView?.stopAnimation(nil)
                activityView?.isHidden = true
                self.titleLabel.stringValue = "Test result"
            }
        }
    }
    
    private var wujiKit: WujiRtcEngineKit {
        return dataSource!.lastmileVCNeedWujiKit()
    }
    
    weak var dataSource: LastmileVCDataSource?
    
    var delegate: LastmileVCDelegate?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        updateViews()
        wujiKit.delegate = self
        isLastmileProbeTesting = true
    }
    
    deinit {
        isLastmileProbeTesting = false
    }
    
    @IBAction func doBackPressed(_ sender: NSButton) {
        delegate?.lastmileVCNeedClose(self)
    }
    
    private func updateViews() {
        view.layer?.backgroundColor = NSColor.white.cgColor
        
        lineView0.layer?.backgroundColor = NSColor.WJGray.cgColor
        lineView1.layer?.backgroundColor = NSColor.WJGray.cgColor
        lineView2.layer?.backgroundColor = NSColor.WJGray.cgColor
        lineView3.layer?.backgroundColor = NSColor.WJGray.cgColor
        lineView4.layer?.backgroundColor = NSColor.WJGray.cgColor
    }
}

extension LastmileViewController: WujiRtcEngineDelegate {
    /// Reports the last mile network quality of the local user once every two seconds before the user joins a channel.
    /// - Parameters:
    ///   - engine: the Wuji engine
    ///   - quality: An enum describing the network quality. Possible values are: Unknown = 0, Excellent = 1, Good = 2, Poor = 3, Bad = 4, VBad = 5, Down = 6, Unsupported = 7, Detecting = 8.
    func rtcEngine(_ engine: WujiRtcEngineKit, lastmileQuality quality: WujiNetworkQuality) {
        qualityLabel.stringValue = quality.description()
    }
    
    /// Reports the last-mile network probe result.
    func rtcEngine(_ engine: WujiRtcEngineKit, lastmileProbeTest result: WujiLastmileProbeResult) {
        rttLabel.stringValue = "\(result.rtt) ms"
        uplinkLabel.stringValue = result.uplinkReport.description()
        downlinkLabel.stringValue = result.downlinkReport.description()
        isLastmileProbeTesting = false
    }
}
