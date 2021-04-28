//
//  ProfileCell.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import UIKit

class DimensionCell: UICollectionViewCell {
    
    @IBOutlet weak var dimensionLabel: UILabel!
    
    func update(with dimension: CGSize, isSelected: Bool) {
        dimensionLabel.text = "\(Int(dimension.width))x\(Int(dimension.height))"
        dimensionLabel.textColor = isSelected ? UIColor.white : UIColor.WJTextGray
        dimensionLabel.backgroundColor = isSelected ? UIColor.WJBlue : UIColor.white
        dimensionLabel.layer.borderColor = isSelected ? UIColor.WJBlue.cgColor : UIColor.WJGray.cgColor
    }
}
