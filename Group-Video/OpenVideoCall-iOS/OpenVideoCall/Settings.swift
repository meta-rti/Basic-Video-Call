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
    var roomName: String?
    var encryptionType: EncryptionType?
    var dimension = CGSize.defaultDimension()
    var frameRate = MetaVideoFrameRate.defaultValue
}
