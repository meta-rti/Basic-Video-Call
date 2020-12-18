//
//  AppDelegate.swift
//  Wuji Mac Tutorial Swift
//
//  Created by 3 on 2020/12/18.
//  Copyright © 2020 Wuji.io. All rights reserved.
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {
    func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool {
        return true
    }
}

