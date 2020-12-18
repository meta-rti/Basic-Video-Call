//
//  Wuji_Mac_Tutorial_Swift_Tests.swift
//  Wuji-Mac-Tutorial-Swift-Tests
//
//  Created by 3 on 2020/12/18.
//  Copyright © 2020 Wuji.io. All rights reserved.
//

import XCTest
@testable import Wuji_Mac_Tutorial_Swift
import WujiRtcKit

class Wuji_Mac_Tutorial_Swift_Tests: XCTestCase {

    override func setUpWithError() throws {
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }

    override func tearDownWithError() throws {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
    }

    func testExample() throws {
        _ = WujiRtcEngineKit.sharedEngine(withAppId: "", delegate: nil)
    }

    func testPerformanceExample() throws {
        // This is an example of a performance test case.
        measure {
            // Put the code you want to measure the time of here.
        }
    }

}
