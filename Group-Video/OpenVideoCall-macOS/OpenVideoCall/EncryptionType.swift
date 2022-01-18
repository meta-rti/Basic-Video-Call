//
//  EncryptionType.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

enum EncryptionType {
    case xts128(String?), xts256(String?)
    
    static let allValues: [EncryptionType] = [.xts128(nil), .xts256(nil)]
    
    var text: String? {
        switch self {
        case .xts128(let xText): return xText
        case .xts256(let xText): return xText
        }
    }
    
    mutating func updateText(_ text: String?) {
        switch self {
        case .xts128:
            self = EncryptionType.xts128(text)
        case .xts256:
            self = EncryptionType.xts256(text)
        }
    }
    
    func modeString() -> String {
        switch self {
        case .xts128: return "aes-128-xts"
        case .xts256: return "aes-256-xts"
        }
    }
    
    func description() -> String {
        switch self {
        case .xts128: return "AES 128"
        case .xts256: return "AES 256"
        }
    }
}

