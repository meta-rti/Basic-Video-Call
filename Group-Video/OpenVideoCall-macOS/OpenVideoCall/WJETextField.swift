//
//  WJETextField.swift
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import Cocoa

class WJETextField: NSTextField {
    override func becomeFirstResponder() -> Bool {
        if let editor = self.currentEditor() as? NSTextView {
            editor.insertionPointColor = NSColor.WJBlue
        }

        return super.becomeFirstResponder()
    }
}

class WJETextFieldCell: NSTextFieldCell {
    override func edit(withFrame rect: NSRect, in controlView: NSView, editor textObj: NSText, delegate: Any?, event: NSEvent?) {
        var frame: NSRect
        
        if let newFrame = adjstedFrameToVerticallyCenterText(frame: rect) {
            frame = newFrame
        } else {
            frame = rect
        }
        
        super.edit(withFrame: frame, in: controlView, editor: textObj, delegate: delegate, event: event)
    }
    
    override func select(withFrame rect: NSRect, in controlView: NSView, editor textObj: NSText, delegate: Any?, start selStart: Int, length selLength: Int) {
        var frame: NSRect
        
        if let newFrame = adjstedFrameToVerticallyCenterText(frame: rect) {
            frame = newFrame
        } else {
            frame = rect
        }
        
        super.select(withFrame: frame, in: controlView, editor: textObj, delegate: delegate, start: selStart, length: selLength)
    }
    
    override func drawInterior(withFrame cellFrame: NSRect, in controlView: NSView) {
        var frame: NSRect
        
        if let newFrame = adjstedFrameToVerticallyCenterText(frame: cellFrame) {
            frame = newFrame
        } else {
            frame = cellFrame
        }
        
        super.drawInterior(withFrame: frame, in: controlView)
    }
    
    private func adjstedFrameToVerticallyCenterText(frame: NSRect) -> NSRect? {
        guard let fontHeight = self.font?.boundingRectForFont.size.height else {
            return nil
        }
        
        let offset = (Float(NSHeight(frame)) - ceilf(Float(fontHeight))) * 0.5
        return NSInsetRect(frame, 0, CGFloat(offset))
    }
}
