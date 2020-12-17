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
    var roomName: String?
    var encryptionType: EncryptionType?
    var dimension = CGSize.defaultDimension()
    var frameRate = WujiVideoFrameRate.defaultValue
}
