//
//  WJEAlert.swift
//  WJEAlert
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import Cocoa

typealias WJEAlertStyle = NSAlert.Style
typealias AfterPressed = (() -> Void)?

class WJEAlert: NSObject {
    struct WJEAction {
        var index: Int
        var completion: AfterPressed
    }
    
    private var alert: NSAlert
    private var actionCount: Int = 0
    private var actionCountMax: Int = 3
    private lazy var actionsDic = [String: WJEAction]() // Key: action title
    
    init(title: String, style: WJEAlertStyle) {
        alert = NSAlert()
        alert.messageText = title
        alert.alertStyle = style
    }
    
    func addAction(title: String, afterPressed: AfterPressed = nil) {
        guard actionCount <= actionCountMax else {
            return
        }
        
        if let _ = actionsDic.keys.firstIndex(of: title) {
            return
        }
        
        defer {
            actionCount += 1;
        }
        
        alert.addButton(withTitle: title)
        alert.buttons[actionCount].setAccessibilityIdentifier(title)
        
        actionsDic[title] = WJEAction(index: actionCount,
                                      completion: afterPressed)
    }
    
    func present() {
        let response = alert.runModal()
        
        func callBack(index: Int) {
            let item = actionsDic.first { (key, value) -> Bool in
                return value.index == index
            }
            if let completion = item?.value.completion {
                completion()
            }
        }
        
        switch response {
        case NSApplication.ModalResponse.alertFirstButtonReturn:
            callBack(index: 0)
        case NSApplication.ModalResponse.alertSecondButtonReturn:
            callBack(index: 1)
        case NSApplication.ModalResponse.alertThirdButtonReturn:
            callBack(index: 2)
        default:
            break
        }
    }
}
