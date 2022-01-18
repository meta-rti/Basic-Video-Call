//
//  Message.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import UIKit

enum MessageType {
    case info, alert
    
    func color() -> UIColor {
        switch self {
        case .info: return UIColor(hex: 0x444444, alpha: 0.6)
        case .alert: return UIColor(hex: 0xff3c32, alpha: 0.6)
        }
    }
}

struct Message {
    var text: String
    var type: MessageType = .info
    
    init(text: String, type: MessageType) {
        self.text = text
        self.type = type
    }
}
    
