//
//  WindowItem.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import Cocoa

class WindowItem: NSCollectionViewItem {
    
    @IBOutlet weak var cImageView: NSImageView!
    
    var image: NSImage? {
        didSet {
            cImageView.image = image
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.wantsLayer = true
        self.view.layer?.backgroundColor = NSColor.black.cgColor
    }
}
