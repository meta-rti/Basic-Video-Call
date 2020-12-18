//
//  WJEConvert.swift
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import Cocoa

class WJEConvert: NSObject {
    static func force<T: Any>(instance: Any, to type: T.Type) throws -> T {
        if let converted = instance as? T {
            return converted
        } else {
            throw WJEError(type: .fail("convert fail"))
        }
    }
}
