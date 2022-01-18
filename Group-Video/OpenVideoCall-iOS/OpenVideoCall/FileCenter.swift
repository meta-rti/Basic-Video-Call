//
//  FileCenter.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import Foundation

class FileCenter {
    static func logDirectory() -> String {
        let directory = documentDirectory() + "/Portions Copyright (c) 2020 meta-rti. All rights reserved.Logs"
        checkAndCreateDirectory(at: directory)
        return directory
    }
    
    static func logFilePath() -> String {
        return logDirectory() + "/Portions Copyright (c) 2020 meta-rti. All rights reserved.-rtc.log"
    }
    
    static func audioFilePath() -> String {
        return Bundle.main.path(forResource: "audioTest", ofType: "mp3")!
    }
}

private extension FileCenter {
    static func documentDirectory() -> String {
        return NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true).first!
    }
    
    static func checkAndCreateDirectory(at path: String) {
        var isDirectory: ObjCBool = false
        let exists = FileManager.default.fileExists(atPath: path, isDirectory: &isDirectory)
        if !exists || !isDirectory.boolValue {
            try? FileManager.default.createDirectory(atPath: path, withIntermediateDirectories: true, attributes: nil)
        }
    }
}
