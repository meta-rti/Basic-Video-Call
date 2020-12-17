//
//  CommonExtensions.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import UIKit

extension UIColor {
    static var AGTextGray: UIColor {
        return UIColor(red: 102.0 / 255.0, green: 102.0 / 255.0, blue: 102.0 / 255.0, alpha: 1)
    }
    
    static var AGGray: UIColor {
        return UIColor(red: 204.0 / 255.0, green: 204.0 / 255.0, blue: 204.0 / 255.0, alpha: 1)
    }
    
    static var AGBlue: UIColor {
        return UIColor(red: 0, green: 106.0 / 255.0, blue: 216.0 / 255.0, alpha: 1)
    }
    
    convenience init(hex: Int, alpha: CGFloat = 1) {
        func transform(_ input: Int, offset: Int = 0) -> CGFloat {
            let value = (input >> offset) & 0xff
            return CGFloat(value) / 255
        }
        
        self.init(red: transform(hex, offset: 16),
                  green: transform(hex, offset: 8),
                  blue: transform(hex),
                  alpha: alpha)
    }
}

extension CGSize {
    func fixedSize(with reference: CGSize) -> CGSize {
        if reference.width > reference.height {
            return fixedLandscapeSize()
        } else {
            return fixedPortraitSize()
        }
    }
    
    func fixedLandscapeSize() -> CGSize {
        let width = self.width
        let height = self.height
        if width < height {
            return CGSize(width: height, height: width)
        } else {
            return self
        }
    }
    
    func fixedPortraitSize() -> CGSize {
        let width = self.width
        let height = self.height
        if width > height {
            return CGSize(width: height, height: width)
        } else {
            return self
        }
    }
    
    func fixedSize() -> CGSize {
        let width = self.width
        let height = self.height
        if width < height {
            return CGSize(width: height, height: width)
        } else {
            return self
        }
    }
}
