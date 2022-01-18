//
//  DeviceSelectionViewController.swift
//  Meta Mac Tutorial Swift
//
//  Created by 3 on 2020/12/18.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import Cocoa
import MetaRTCFramework

class DeviceSelectionViewController: NSViewController {
    @IBOutlet weak var microphoneSelection: NSPopUpButton!
    @IBOutlet weak var speakerSelection: NSPopUpButton!
    @IBOutlet weak var cameraSelection: NSPopUpButton!
    
    var connectedRecordingDevices: [MetaRtcDeviceInfo]!
    var connectedPlaybackDevices: [MetaRtcDeviceInfo]!
    var connectedVideoCaptureDevices: [MetaRtcDeviceInfo]!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.preferredContentSize = NSMakeSize(500, 250)
        loadDevicesInPopUpButtons()
    }
    
    func loadDevicesInPopUpButtons() {
        microphoneSelection.removeAllItems()
        speakerSelection.removeAllItems()
        cameraSelection.removeAllItems()
    
        connectedRecordingDevices = MetaKit.enumerateDevices(.audioRecording)
        for device in connectedRecordingDevices {
            if let title = device.deviceName {
                microphoneSelection.addItem(withTitle: title)
            }
        }
    
        connectedPlaybackDevices = MetaKit.enumerateDevices(.audioPlayout)
        for device in connectedPlaybackDevices {
            if let title = device.deviceName {
                speakerSelection.addItem(withTitle: title)
            }
        }
        
        connectedVideoCaptureDevices = MetaKit.enumerateDevices(.videoCapture)
        for device in connectedVideoCaptureDevices {
            if let title = device.deviceName {
                cameraSelection.addItem(withTitle: title)
            }
        }
        // Populate the NSPopUpButtons with the enumerated device list
    }
    
    @IBAction func didClickConfirmButton(_ sender: NSButton) {
        if let deviceId = connectedRecordingDevices[microphoneSelection.indexOfSelectedItem].deviceId {
            MetaKit.setDevice(.audioRecording, deviceId: deviceId)
        }
        if let deviceId = connectedPlaybackDevices[speakerSelection.indexOfSelectedItem].deviceId {
            MetaKit.setDevice(.audioPlayout, deviceId: deviceId)
        }
        if let deviceId = connectedVideoCaptureDevices[cameraSelection.indexOfSelectedItem].deviceId {
            MetaKit.setDevice(.videoCapture, deviceId: deviceId)
        }
        // Set the devices
        self.dismiss(self)
    }
}

extension DeviceSelectionViewController: MetaRtcEngineDelegate {
    @objc(rtcEngine:device:type:stateChanged:) func rtcEngine(_ engine: MetaRtcEngineKit, device deviceId: String, type deviceType: MetaMediaDeviceType, stateChanged state: Int) {
        loadDevicesInPopUpButtons()
        // Repopulate NSPopUpButtons if a device is plugged in or removed
    }
}
