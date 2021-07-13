//
//  WJEEventsObserver.swift
//  WJE
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

#if os(macOS)
import Cocoa
#else
import UIKit
#endif

protocol WJEEventsObserverDelegate: NSObjectProtocol {
    #if os(macOS)
    func observer(_ observer: WJEEventsObserver, didTriggerInputEvent event: NSEvent)
    #endif
}

protocol WJEEventsObserverDataSource: NSObjectProtocol {
    #if os(macOS)
    func observerNeedWindowNumber(_ observer: WJEEventsObserver) -> Int
    #endif
}

class WJEEventsObserver: NSObject {
    weak var delegate: WJEEventsObserverDelegate?
    weak var dataSource: WJEEventsObserverDataSource?
    
    #if os(macOS)
    deinit {
        NSEvent.removeMonitor(self)
    }
    #endif
}

#if os(macOS)
extension WJEEventsObserver {
    func listenCurrentWindow(inputEvents: NSEvent.EventTypeMask) {
        NSEvent.addLocalMonitorForEvents(matching: inputEvents) { [weak self] (event) -> NSEvent? in
            guard let strongSelf = self,
                let currentWindowNumber = strongSelf.dataSource?.observerNeedWindowNumber(strongSelf),
                event.windowNumber == currentWindowNumber else {
                    return event
            }
            
            strongSelf.delegate?.observer(strongSelf, didTriggerInputEvent: event)
            return event
        }
    }
}
#endif
