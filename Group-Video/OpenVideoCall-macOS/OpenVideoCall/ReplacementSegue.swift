//
//  ReplacementSegue.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import Cocoa

class ReplacementSegue: NSStoryboardSegue {
    override func perform() {
        (sourceController as AnyObject).view.window?.contentViewController = destinationController as? NSViewController
    }
}
