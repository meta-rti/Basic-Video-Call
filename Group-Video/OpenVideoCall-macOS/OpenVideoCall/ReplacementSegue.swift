//
//  ReplacementSegue.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import Cocoa

class ReplacementSegue: NSStoryboardSegue {
    override func perform() {
        (sourceController as AnyObject).view.window?.contentViewController = destinationController as? NSViewController
    }
}
