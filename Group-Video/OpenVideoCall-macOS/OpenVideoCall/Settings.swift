//
//  Settings.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import Foundation
import WujiRTCFramework

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
    var frameRate = WujiVideoFrameRate.defaultValue
    
    var recordDevice = DeviceType.record(nil)
    var speakerDevice = DeviceType.speaker(nil)
    var cameraDevice = DeviceType.camera(nil)
}
