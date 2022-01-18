//
//  RoomOptionsViewController.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

import UIKit

struct RoomOptions {
    var isDebugMode: Bool = false
}

protocol RoomOptionsVCDataSource: NSObjectProtocol {
    func roomOptionsVCNeedOptions() -> RoomOptions
}

protocol RoomOptionsVCDelegate: NSObjectProtocol {
    func roomOptionsVC(_ vc: RoomOptionsViewController, debugModeDid enable: Bool)
}

class RoomOptionsViewController: UITableViewController {
    
    @IBOutlet weak var debugSwitch: UISwitch!
    
    weak var delegate: RoomOptionsVCDelegate?
    weak var dataSource: RoomOptionsVCDataSource?
    
    var options: RoomOptions {
        return dataSource!.roomOptionsVCNeedOptions()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        debugSwitch.isOn = options.isDebugMode
    }
    
    override func tableView(_ tableView: UITableView, viewForHeaderInSection section: Int) -> UIView? {
        let view = UIView()
        view.backgroundColor = UIColor(red: 229.0 / 255.0, green: 229.0 / 255.0, blue: 229.0 / 255.0, alpha: 1)
        return view
    }
    
    @IBAction func doDebugPressed(_ sender: UISwitch) {
        let debugMode = sender.isOn
        delegate?.roomOptionsVC(self, debugModeDid: debugMode)
    }
}

extension RoomOptionsViewController {
    override func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 16
    }
}
