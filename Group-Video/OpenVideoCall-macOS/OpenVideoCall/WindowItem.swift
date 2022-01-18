//
//  WindowItem.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
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
