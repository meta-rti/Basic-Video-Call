//
//  WJEButton.swift
//  WJEButton
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import Cocoa

typealias AGETextAlignment = NSTextAlignment

class WJEButton: NSButton {
    enum WJETrackingAreaType {
        case `default`, custom(NSTrackingArea)
    }
    
    required init(coder: NSCoder) {
        super.init(coder: coder)!
        self.wantsLayer = true
    }
    
    func setTitle(_ title: String, with color: NSColor, alignment: AGETextAlignment = .center) {
        let paragraph = NSMutableParagraphStyle()
        paragraph.alignment = alignment
        let attributes = [NSAttributedString.Key.paragraphStyle: paragraph,
                          NSAttributedString.Key.foregroundColor: color]
        
        self.attributedTitle = NSAttributedString(string: title,
                                                  attributes: attributes)
    }
    
    func addTrackingArea(_ type: WJETrackingAreaType) {
        switch type {
        case .default:
            let trackingArea = NSTrackingArea(rect: self.bounds,
                                              options: [.mouseEnteredAndExited, .activeAlways],
                                              owner: self,
                                              userInfo: nil)
            self.addTrackingArea(trackingArea)
        case .custom(let area):
            self.addTrackingArea(area)
        }
    }
}
