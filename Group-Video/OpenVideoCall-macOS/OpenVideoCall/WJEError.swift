//
//  WJEError.swift
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import Cocoa

struct WJEError: Error {
    enum ErrorType {
        case fail(String)
        case invalidParameter(String)
        case valueNil(String)
        case unknown
    }
    
    var localizedDescription: String {
        switch type {
        case .fail(let reason):             return "\(reason)"
        case .invalidParameter(let para):   return "\(para)"
        case .valueNil(let para):           return "\(para) nil"
        case .unknown:                      return "unknown error"
        }
    }
    
    var type: ErrorType
}
