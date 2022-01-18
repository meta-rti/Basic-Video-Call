//
//  LastmileViewController.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import UIKit
import MetaRTCFramework

protocol LastmileVCDataSource: NSObjectProtocol {
    func lastmileVCNeedMetaKit() -> MetaRtcEngineKit
}

class LastmileViewController: UITableViewController {
    
    @IBOutlet weak var qualityLabel: UILabel!
    @IBOutlet weak var rttLabel: UILabel!
    @IBOutlet weak var uplinkLabel: UILabel!
    @IBOutlet weak var downlinkLabel: UILabel!
    
    private var metaKit: MetaRtcEngineKit {
        return dataSource!.lastmileVCNeedMetaKit()
    }
    
    private var isLastmileProbeTesting = false {
        didSet {
            if isLastmileProbeTesting {
                let config = MetaLastmileProbeConfig()
                config.probeUplink = true
                config.probeDownlink = true
                config.expectedUplinkBitrate = 5000
                config.expectedDownlinkBitrate = 5000
                metaKit.startLastmileProbeTest(config)
                activityView?.startAnimating()
                self.title = "Testing..."
            } else {
                metaKit.stopLastmileProbeTest()
                activityView?.stopAnimating()
                self.title = "Test result"
            }
        }
    }
    
    private var activityView: UIActivityIndicatorView?
    
    weak var dataSource: LastmileVCDataSource?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        addActivityView()
        metaKit.delegate = self
        isLastmileProbeTesting = true
        view.backgroundColor = UIColor.white
    }
       
    deinit {
        isLastmileProbeTesting = false
    }
}

extension LastmileViewController: MetaRtcEngineDelegate {
    /// Reports the last mile network quality of the local user once every two seconds before the user joins a channel.
    /// - Parameters:
    ///   - engine: the Portions Copyright (c) 2020 meta-rti. All rights reserved. engine
    ///   - quality: An enum describing the network quality. Possible values are: Unknown = 0, Excellent = 1, Good = 2, Poor = 3, Bad = 4, VBad = 5, Down = 6, Unsupported = 7, Detecting = 8.
    func rtcEngine(_ engine: MetaRtcEngineKit, lastmileQuality quality: MetaNetworkQuality) {
        qualityLabel.text = quality.description()
    }
    
    /// Reports the last-mile network probe result.
    func rtcEngine(_ engine: MetaRtcEngineKit, lastmileProbeTest result: MetaLastmileProbeResult) {
        rttLabel.text = "\(result.rtt) ms"
        uplinkLabel.text = result.uplinkReport.description()
        downlinkLabel.text = result.downlinkReport.description()
        isLastmileProbeTesting = false
    }
}

extension LastmileViewController {
    func addActivityView() {
        let activityView = UIActivityIndicatorView(style: .white)
        let rightItem = UIBarButtonItem(customView: activityView)
        navigationItem.rightBarButtonItem = rightItem
        self.activityView = activityView
    }
}

extension MetaLastmileProbeOneWayResult {
    func description() -> String {
        return "\(packetLossRate)"
    }
}
