//
//  Settings.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import Foundation
import MetaRTCFramework

struct Settings {
    enum DeviceType {
        case record(String?), speaker(String?), camera(String?)
        
        var deviceId: String? {
            switch self {
            case .record(let id):  return id
            case .speaker(let id): return id
            case .camera(let id):  return id
            }
        }
    }
    
    var roomName: String?
    var encryptionType: EncryptionType?
    var logViewOpen = false
    var dimension = CGSize.defaultDimension()
    var frameRate = MetaVideoFrameRate.defaultValue
    
    var recordDevice = DeviceType.record(nil)
    var speakerDevice = DeviceType.speaker(nil)
    var cameraDevice = DeviceType.camera(nil)
}
