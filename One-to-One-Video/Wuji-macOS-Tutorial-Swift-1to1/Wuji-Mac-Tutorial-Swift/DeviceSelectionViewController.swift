//
//  DeviceSelectionViewController.swift
//  Wuji Mac Tutorial Swift
//
//  Created by 3 on 2020/12/18.
//  Copyright © 2020 Wuji.io. All rights reserved.
//

import Cocoa
import WujiRTCFramework

class DeviceSelectionViewController: NSViewController {
    @IBOutlet weak var microphoneSelection: NSPopUpButton!
    @IBOutlet weak var speakerSelection: NSPopUpButton!
    @IBOutlet weak var cameraSelection: NSPopUpButton!
    
    var connectedRecordingDevices: [WujiRtcDeviceInfo]!
    var connectedPlaybackDevices: [WujiRtcDeviceInfo]!
    var connectedVideoCaptureDevices: [WujiRtcDeviceInfo]!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.preferredContentSize = NSMakeSize(500, 250)
        loadDevicesInPopUpButtons()
    }
    
    func loadDevicesInPopUpButtons() {
        microphoneSelection.removeAllItems()
        speakerSelection.removeAllItems()
        cameraSelection.removeAllItems()
    
        connectedRecordingDevices = WujiKit.enumerateDevices(.audioRecording)
        for device in connectedRecordingDevices {
            if let title = device.deviceName {
                microphoneSelection.addItem(withTitle: title)
            }
        }
    
        connectedPlaybackDevices = WujiKit.enumerateDevices(.audioPlayout)
        for device in connectedPlaybackDevices {
            if let title = device.deviceName {
                speakerSelection.addItem(withTitle: title)
            }
        }
        
        connectedVideoCaptureDevices = WujiKit.enumerateDevices(.videoCapture)
        for device in connectedVideoCaptureDevices {
            if let title = device.deviceName {
                cameraSelection.addItem(withTitle: title)
            }
        }
        // Populate the NSPopUpButtons with the enumerated device list
    }
    
    @IBAction func didClickConfirmButton(_ sender: NSButton) {
        if let deviceId = connectedRecordingDevices[microphoneSelection.indexOfSelectedItem].deviceId {
            WujiKit.setDevice(.audioRecording, deviceId: deviceId)
        }
        if let deviceId = connectedPlaybackDevices[speakerSelection.indexOfSelectedItem].deviceId {
            WujiKit.setDevice(.audioPlayout, deviceId: deviceId)
        }
        if let deviceId = connectedVideoCaptureDevices[cameraSelection.indexOfSelectedItem].deviceId {
            WujiKit.setDevice(.videoCapture, deviceId: deviceId)
        }
        // Set the devices
        self.dismiss(self)
    }
}

extension DeviceSelectionViewController: WujiRtcEngineDelegate {
    @objc(rtcEngine:device:type:stateChanged:) func rtcEngine(_ engine: WujiRtcEngineKit, device deviceId: String, type deviceType: WujiMediaDeviceType, stateChanged state: Int) {
        loadDevicesInPopUpButtons()
        // Repopulate NSPopUpButtons if a device is plugged in or removed
    }
}
