//
//  ImageBrowserItem.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import Cocoa
import Quartz.ImageKit

class ImageBrowserItem: NSObject {
    var window: Window!
    
    fileprivate override init() {
        super.init()
    }
    
    init(window: Window) {
        super.init()
        self.window = window
    }
    
    override func imageUID() -> String! {
        return "\(window.id)"
    }
    
    override func imageTitle() -> String! {
        return window.name
    }
    
    override func imageRepresentation() -> Any! {
        return window.image
    }
    
    override func imageRepresentationType() -> String! {
        return IKImageBrowserNSImageRepresentationType
    }
}
