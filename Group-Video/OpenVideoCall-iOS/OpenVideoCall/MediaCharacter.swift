//
//  MediaCharacter.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import Foundation

struct MediaCharacter {
    
    fileprivate static let legalMediaCharacterSet: NSCharacterSet = {
        return NSCharacterSet(charactersIn: "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$%&()+,-:;<=.>?@[]^_`{|}~")
    }()
    
    static func updateToLegalMediaString(from string: String) -> String {
        let legalSet = MediaCharacter.legalMediaCharacterSet
        let separatedArray = string.components(separatedBy: legalSet.inverted)
        let legalString = separatedArray.joined(separator: "")
        return legalString
    }
}