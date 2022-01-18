//
//  WJEView.swift
//  WJE
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#if os(iOS)
import UIKit
#else
import Cocoa
#endif

#if os(iOS)
typealias WJEView = UIView
typealias WJEColor = UIColor
typealias WJESize = CGSize
#else
typealias WJEView = NSView
typealias WJEColor = NSColor
typealias WJESize = NSSize
#endif

extension WJEView {
    #if os(macOS)
    func layoutIfNeeded() {
        self.layoutSubtreeIfNeeded()
    }
    
    var backgroundColor: WJEColor {
        set {
            if self.layer == nil {
                self.wantsLayer = true
            }
            
            self.layer?.backgroundColor = newValue.cgColor
        }
        
        get {
            var color: WJEColor?
            if let layerColor = self.layer?.backgroundColor {
                color = WJEColor(cgColor: layerColor)
            }
            
            if let value = color {
                return value
            } else {
                return WJEColor.clear
            }
        }
    }
    #endif
}

#if os(iOS)
typealias WJEScrollViewDelegate = UIScrollViewDelegate

class WJEScrollView: UIScrollView {
    override init(frame frameRect: CGRect) {
        super.init(frame: frameRect)
        doInitSettings()
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
        doInitSettings()
    }
    
    init() {
        super.init(frame: CGRect(x: 0, y: 0, width: 0, height: 0))
        doInitSettings()
    }
}

#else
protocol WJEScrollViewDelegate: NSObjectProtocol {
    func scrollViewDidScroll(_ scrollView: WJEScrollView)
}

class WJEScrollView: NSScrollView {
    
    fileprivate var contentViewBoundsObserver: Any?
    weak var delegate: WJEScrollViewDelegate?
    
    var contentOffset: CGPoint {
        set {
            documentView?.scroll(newValue)
        }
        get {
            return documentVisibleRect.origin
        }
    }
    
    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        doInitSettings()
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
        doInitSettings()
    }
    
    init() {
        super.init(frame: NSRect(x: 0, y: 0, width: 0, height: 0))
        doInitSettings()
    }
    
    deinit {
        if let contentViewBoundsObserver = contentViewBoundsObserver {
            NotificationCenter.default.removeObserver(contentViewBoundsObserver)
            self.contentViewBoundsObserver = nil
        }
    }
    
    func scrollToTop() {
        guard let documentView = self.documentView else {
            return
        }
        
        if documentView.isFlipped {
            documentView.scroll(.zero)
        } else {
            let maxHeight = max(bounds.height, documentView.bounds.height)
            documentView.scroll(NSPoint(x: 0, y: maxHeight))
        }
    }
}
#endif

extension WJEScrollView {
    func removeAllItemViews() {
        #if os(iOS)
        for subView in self.subviews {
            subView.removeFromSuperview()
        }
        #else
        guard let view = self.documentView else {
            return
        }
        
        for subView in view.subviews {
            subView.removeFromSuperview()
        }
        #endif
    }
}

private extension WJEScrollView {
    func doInitSettings() {
        translatesAutoresizingMaskIntoConstraints = false
        #if os(iOS)
        alwaysBounceHorizontal = false
        showsHorizontalScrollIndicator = false
        alwaysBounceVertical = false
        showsVerticalScrollIndicator = false
        #else
        self.wantsLayer = true
        self.layer?.backgroundColor = NSColor.clear.cgColor
        self.drawsBackground = false
        
        let view = NSView(frame: NSRect(x: 0, y: 0, width: 0, height: 0))
        self.documentView = view
        verticalScrollElasticity = .automatic
        horizontalScrollElasticity = .automatic
        
        contentView.postsBoundsChangedNotifications = true
        guard contentViewBoundsObserver == nil else {
            return
        }
        let center = NotificationCenter.default
        contentViewBoundsObserver = center.addObserver(forName: NSView.boundsDidChangeNotification,
                                                       object: contentView,
                                                       queue: nil) { [weak self] (notify) in
                                                        if let strongSelf = self {
                                                            strongSelf.delegate?.scrollViewDidScroll(strongSelf)
                                                        }
        }
        #endif
    }
}

