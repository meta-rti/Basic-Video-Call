//
//  ChatMessageCell.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

import UIKit

class MessageCell: UITableViewCell {
    
    @IBOutlet weak var colorView: UIView!
    @IBOutlet weak var messageLabel: UILabel!
    
    func set(with message: Message) {
        colorView.backgroundColor = message.type.color()
        messageLabel.text = message.text
    }
}
