//
//  StatisticsInfo.swift
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import Foundation
import MetaRTCFramework

struct StatisticsInfo {
    struct LocalInfo {
        var stats = MetaChannelStats()
    }
    
    struct RemoteInfo {
        var videoStats = MetaRtcRemoteVideoStats()
        var audioStats = MetaRtcRemoteAudioStats()
    }
    
    enum StatisticsType {
        case local(LocalInfo), remote(RemoteInfo)
        
        var isLocal: Bool {
            switch self {
            case .local:  return true
            case .remote: return false
            }
        }
    }
    
    var dimension = CGSize.zero
    var fps = 0
    
    var txQuality: MetaNetworkQuality = .unknown
    var rxQuality: MetaNetworkQuality = .unknown
    
    var type: StatisticsType
    
    init(type: StatisticsType) {
        self.type = type
    }
    
    mutating func updateChannelStats(_ stats: MetaChannelStats) {
        guard self.type.isLocal else {
            return
        }
        let info = LocalInfo(stats: stats)
        self.type = .local(info)
    }
    
    mutating func updateVideoStats(_ stats: MetaRtcRemoteVideoStats) {
        switch type {
        case .remote(let info):
            var new = info
            new.videoStats = stats
            self.type = .remote(new)
        default:
            break
        }
    }
    
    mutating func updateAudioStats(_ stats: MetaRtcRemoteAudioStats) {
        switch type {
        case .remote(let info):
            var new = info
            new.audioStats = stats
            self.type = .remote(new)
        default:
            break
        }
    }
    
    func description() -> String {
        var full: String
        switch type {
        case .local(let info):  full = localDescription(info: info)
        case .remote(let info): full = remoteDescription(info: info)
        }
        return full
    }
    
    func localDescription(info: LocalInfo) -> String {
        let join = "\n"
        
        let dimensionFps = "\(Int(dimension.width))×\(Int(dimension.height)), \(fps)fps"
        let quality = "Send/Recv Quality: \(txQuality.description())/\(rxQuality.description())"
        
        let lastmile = "Lastmile Delay: \(info.stats.lastmileDelay)ms"
        let videoSendRecv = "Video Send/Recv: \(info.stats.txVideoKBitrate)kbps/\(info.stats.rxVideoKBitrate)kbps"
        let audioSendRecv = "Audio Send/Recv: \(info.stats.txAudioKBitrate)kbps/\(info.stats.rxAudioKBitrate)kbps"
        
        let cpu = "CPU: App/Total \(info.stats.cpuAppUsage)%/\(info.stats.cpuTotalUsage)%"
        let sendRecvLoss = "Send/Recv Loss: \(info.stats.txPacketLossRate)%/\(info.stats.rxPacketLossRate)%"
        return dimensionFps + join + lastmile + join + videoSendRecv + join + audioSendRecv + join + cpu + join + quality +  join + sendRecvLoss
    }
    
    func remoteDescription(info: RemoteInfo) -> String {
        let join = "\n"
        
        let dimensionFpsBit = "\(Int(dimension.width))×\(Int(dimension.height)), \(fps)fps, \(info.videoStats.receivedBitrate)kbps"
        let quality = "Send/Recv Quality: \(txQuality.description())/\(rxQuality.description())"
        
        var audioQuality: MetaNetworkQuality
        if let quality = MetaNetworkQuality(rawValue: info.audioStats.quality) {
            audioQuality = quality
        } else {
            audioQuality = MetaNetworkQuality.unknown
        }
        
        let audioNet = "Audio Net Delay/Jitter: \(info.audioStats.networkTransportDelay)ms/\(info.audioStats.jitterBufferDelay)ms)"
        let audioLoss = "Audio Loss/Quality: \(info.audioStats.audioLossRate)% \(audioQuality.description())"
        
        return dimensionFpsBit + join + quality + join + audioNet + join + audioLoss
    }
}
