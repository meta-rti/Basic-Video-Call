//
//  SettingsViewController.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import Cocoa
import MetaRTCFramework

protocol SettingsVCDataSource: NSObjectProtocol {
    func settingsVCNeedSettings() -> Settings
    func settingsVCNeedMetaKit() -> MetaRtcEngineKit
}

protocol SettingsVCDelegate: NSObjectProtocol {
    func settingsVC(_ vc: SettingsViewController, didUpdate settings: Settings)
    func settingsVCNeedClose(_ vc: SettingsViewController)
}

class SettingsViewController: NSViewController {

    @IBOutlet weak var resolutionPopUpButton: NSPopUpButton!
    @IBOutlet weak var frameRatePopUpButton: NSPopUpButton!
    
    @IBOutlet weak var recordDevicePopUpButton: NSPopUpButton!
    @IBOutlet weak var speakerDevicePopUpButton: NSPopUpButton!
    @IBOutlet weak var cameraPopUpButton: NSPopUpButton!
    
    @IBOutlet weak var lineView0: NSView!
    @IBOutlet weak var lineView1: NSView!
    @IBOutlet weak var lineView2: NSView!
    
    @IBOutlet weak var lineView3: NSView!
    @IBOutlet weak var lineView4: NSView!
    @IBOutlet weak var lineView5: NSView!
    
    private var recordDevices: [MetaRtcDeviceInfo]?
    private var speakerDevices: [MetaRtcDeviceInfo]?
    private var cameraDevices: [MetaRtcDeviceInfo]?
    
    private lazy var settings: Settings = dataSource!.settingsVCNeedSettings()
    
    private var metaKit: MetaRtcEngineKit {
        return dataSource!.settingsVCNeedMetaKit()
    }
    
    weak var dataSource: SettingsVCDataSource?
    
    var delegate: SettingsVCDelegate?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        updateViews()
        loadDevices()
        loadProfileItems()
        loadFrameRateItems()
    }
    
    @IBAction func doBackPressed(_ sender: NSButton) {
        delegate?.settingsVC(self, didUpdate: settings)
        delegate?.settingsVCNeedClose(self)
    }
    
    @IBAction func doResolutionChanged(_ sender: NSPopUpButton) {
        settings.dimension = CGSize.validDimensionList()[sender.indexOfSelectedItem]
    }
    
    @IBAction func doFrameRateChanged(_ sender: NSPopUpButton) {
        settings.frameRate = MetaVideoFrameRate.validList()[sender.indexOfSelectedItem]
    }
    
    @IBAction func doRecordDeviceChanged(_ sender: NSPopUpButton) {
        if let deviceId = recordDevices?[sender.indexOfSelectedItem].deviceId {
            settings.recordDevice = .record(deviceId)
        }
    }
    
    @IBAction func doSpeakerDeviceChanged(_ sender: NSPopUpButton) {
        if let deviceId = speakerDevices?[sender.indexOfSelectedItem].deviceId {
            settings.speakerDevice = .speaker(deviceId)
        }
    }
    
    @IBAction func doCameraChanged(_ sender: NSPopUpButton) {
        if let deviceId = cameraDevices?[sender.indexOfSelectedItem].deviceId {
            settings.cameraDevice = .camera(deviceId)
        }
    }
}

private extension SettingsViewController {
    func updateViews() {
        view.wantsLayer = true
        view.layer?.backgroundColor = NSColor.white.cgColor
        
        lineView0.wantsLayer = true
        lineView1.wantsLayer = true
        lineView2.wantsLayer = true
        lineView3.wantsLayer = true
        lineView4.wantsLayer = true
        lineView5.wantsLayer = true
        
        lineView0.layer?.backgroundColor = NSColor.WJLineGray.cgColor
        lineView1.layer?.backgroundColor = NSColor.WJLineGray.cgColor
        lineView2.layer?.backgroundColor = NSColor.WJLineGray.cgColor
        lineView3.layer?.backgroundColor = NSColor.WJLineGray.cgColor
        lineView4.layer?.backgroundColor = NSColor.WJLineGray.cgColor
        lineView5.layer?.backgroundColor = NSColor.WJLineGray.cgColor
    }
    
    func updatePopUpButtonColor(_ button: NSPopUpButton) {
        let attributes = [NSAttributedString.Key.foregroundColor: NSColor.WJTextBlack]
        for item in button.itemArray {
            let title = item.title
            item.attributedTitle = NSAttributedString(string: title,
                                                      attributes: attributes)
        }
    }
}

private extension SettingsViewController {
    func loadProfileItems() {
        resolutionPopUpButton.addItems(withTitles: CGSize.validDimensionList().map { (dimension) -> String in
            return dimension.description()
        })
        resolutionPopUpButton.selectItem(withTitle: settings.dimension.description())
        updatePopUpButtonColor(resolutionPopUpButton)
    }
    
    func loadFrameRateItems() {
        frameRatePopUpButton.addItems(withTitles: MetaVideoFrameRate.validList().map { (rate) -> String in
            return rate.description
        })
        frameRatePopUpButton.selectItem(withTitle: settings.frameRate.description)
        updatePopUpButtonColor(frameRatePopUpButton)
    }
}

// MARK: - Devices
private extension SettingsViewController {
    func loadDevices() {
        loadDevice(of: settings.cameraDevice)
        loadDevice(of: settings.recordDevice)
        loadDevice(of: settings.speakerDevice)
    }
    
    func loadDevice(of type: Settings.DeviceType) {
        var wjType: MetaMediaDeviceType
        var localId: String?
        var localDevices: [MetaRtcDeviceInfo]?
        var localButton: NSPopUpButton
        
        switch type {
        case .record(let id):
            wjType = .audioRecording
            localId = id
            localDevices = metaKit.enumerateDevices(wjType)! as NSArray as? [MetaRtcDeviceInfo]
            recordDevices = localDevices
            localButton = recordDevicePopUpButton
        case .speaker(let id):
            wjType = .audioPlayout
            localId = id
            localDevices = metaKit.enumerateDevices(wjType)! as NSArray as? [MetaRtcDeviceInfo]
            speakerDevices = localDevices
            localButton = speakerDevicePopUpButton
        case .camera(let id):
//            wjType = .videoCapture
            localId = id
//            localDevices = metaKit.enumerateDevices(wjType)! as NSArray as? [MetaRtcDeviceInfo]
//            cameraDevices = localDevices
            localButton = cameraPopUpButton
        }
        
        if localId == nil {
            localId = localDevices?.first?.deviceId
        }
        
        guard let devices = localDevices,
            let deviceId = localId else {
            return
        }
        
        updatePopUpButton(localButton, withValue: deviceId, inValueList: devices)
        updatePopUpButtonColor(localButton)
    }
    
    func updatePopUpButton(_ button: NSPopUpButton, withValue value: String?, inValueList list: [MetaRtcDeviceInfo]) {
        button.removeAllItems()
        button.addItems(withTitles: list.map({ (info) -> String in
            return info.deviceName!
        }))
        
        let deviceIds = list.map { (info) -> String in
            return info.deviceId!
        }
        if let value = value, let index = deviceIds.index(of: value) {
            button.selectItem(at: index)
        }
    }
}
