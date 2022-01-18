//
//  WJEButton.swift
//  WJEButton
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import Cocoa

typealias WJETextAlignment = NSTextAlignment

class WJEButton: NSButton {
    enum WJETrackingAreaType {
        case `default`, custom(NSTrackingArea)
    }
    
    required init(coder: NSCoder) {
        super.init(coder: coder)!
        self.wantsLayer = true
    }
    
    func setTitle(_ title: String, with color: NSColor, alignment: WJETextAlignment = .center) {
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
