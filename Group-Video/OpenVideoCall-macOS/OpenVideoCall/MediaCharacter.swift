//
//  MediaCharacter.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import Foundation

struct MediaCharacter {
    
    fileprivate static let legalMediaCharacterSet: CharacterSet = {
        return CharacterSet(charactersIn: "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$%&()+,-:;<=.>?@[]^_`{|}~")
    }()
    
    static func updateToLegalMediaString(from string: String) -> String {
        let legalSet = MediaCharacter.legalMediaCharacterSet
        let separatedArray = string.components(separatedBy: legalSet.inverted)
        let legalString = separatedArray.joined(separator: "")
        return legalString
    }
}
