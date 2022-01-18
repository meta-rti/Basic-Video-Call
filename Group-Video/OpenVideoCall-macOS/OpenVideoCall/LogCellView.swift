//
//  LogCellView.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import Cocoa

class LogCellView: NSTableCellView {
    
    @IBOutlet weak var colorView: NSView!
    @IBOutlet weak var messageLabel: NSTextField!
    
    override func draw(_ dirtyRect: NSRect) {
        super.draw(dirtyRect)
        
        colorView?.layer?.cornerRadius = 2
        
        messageLabel?.usesSingleLineMode = false
        messageLabel?.cell?.wraps = true
        messageLabel?.cell?.isScrollable = false
    }
    
    func set(with message: Message) {
        messageLabel.stringValue = message.text
        
        colorView?.wantsLayer = true
        colorView?.layer?.backgroundColor = message.type.color().cgColor
    }
}
