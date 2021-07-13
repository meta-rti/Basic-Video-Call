//
//  WujiExtension.swift
//  OpenLive
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import WujiRTCFramework

extension WujiErrorCode {
    var description: String {
        var text: String
        switch self {
        case .joinChannelRejected: text = "join channel rejected"
        case .leaveChannelRejected: text = "leave channel rejected"
        case .invalidAppId: text = "invalid app id"
        case .invalidToken: text = "invalid token"
        case .invalidChannelId: text = "invalid channel id"
        default: text = "\(self.rawValue)"
        }
        return text
    }
}

extension WujiWarningCode {
    var description: String {
        var text: String
        switch self {
        case .invalidView: text = "invalid view"
        default: text = "\(self.rawValue)"
        }
        return text
    }
}

extension CGSize {
    static func defaultDimension() -> CGSize {
        return WujiVideoDimension640x360
    }
    
    static func validDimensionList() -> [CGSize] {
        return [WujiVideoDimension160x120,
                WujiVideoDimension240x180,
                WujiVideoDimension320x240,
                WujiVideoDimension640x360,
                WujiVideoDimension640x480,
                WujiVideoDimension960x720]
    }
}

extension WujiVideoFrameRate {
    var description: String {
        switch self {
        case .fps1:    return "1 fps"
        case .fps7:    return "7 fps"
        case .fps10:   return "10 fps"
        case .fps15:   return "15 fps"
        case .fps24:   return "24 fps"
        case .fps30:   return "30 fps"
        default:       return "unsported"
        }
    }
    
    var value: Int {
        switch self {
        case .fps1:    return 1
        case .fps7:    return 7
        case .fps10:   return 10
        case .fps15:   return 15
        case .fps24:   return 24
        case .fps30:   return 30
        default:       return -1
        }
    }
    
    static var defaultValue = WujiVideoFrameRate.fps15
    
    static func validList() -> [WujiVideoFrameRate] {
        return [.fps1,
                .fps7,
                .fps10,
                .fps15,
                .fps24,
                .fps30]
    }
}

extension WujiNetworkQuality {
    func description() -> String {
        switch self {
        case .excellent: return "excellent"
        case .good:      return "good"
        case .poor:      return "poor"
        case .bad:       return "bad"
        case .vBad:      return "very bad"
        case .down:      return "down"
        case .unknown:   return "unknown"
        case .unsupported: return "unsupported"
        case .detecting: return "detecting"
        default:         return "unknown"
        }
    }
}
