//
//  MainViewController.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import Cocoa
import WujiRTCFramework

class MainViewController: NSViewController {
    
    @IBOutlet weak var roomInputTextField: NSTextField!
    @IBOutlet weak var roomInputLineView: NSView!
    @IBOutlet weak var joinButton: WJEButton!
    @IBOutlet weak var settingsButton: NSButton!
    @IBOutlet weak var encryptionButton: WJEButton!
    @IBOutlet weak var encryptionTextField: NSTextField!
    @IBOutlet weak var encryptionLineView: NSView!
    @IBOutlet weak var testNetworkButton: WJEButton!
    
    // The wuji engine
    private lazy var wujiKit: WujiRtcEngineKit = {
        let engine = WujiRtcEngineKit.sharedEngine(withAppId: KeyCenter.AppId, delegate: nil)
        engine.setLogFilter(WujiLogFilter.info.rawValue)
        engine.setLogFile(FileCenter.logFilePath())
        return engine
    }()
    
    private var encryptionType = EncryptionType.xts128(nil) {
        didSet {
            encryptionButton.setTitle(encryptionType.description(), with: NSColor.WJBlue)
        }
    }
    
    private var settings = Settings()
    private var alert: WJEAlert?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        updateViews()
    }
    
    override func viewDidAppear() {
        super.viewDidAppear()
        roomInputTextField.becomeFirstResponder()
    }
    
    override func prepare(for segue: NSStoryboardSegue, sender: Any?) {
        guard let segueId = segue.identifier , !segueId.isEmpty else {
            return
        }
        
        switch segueId {
        case "mainVCToSettingsVC":
            let settingsVC = segue.destinationController as! SettingsViewController
            settingsVC.dataSource = self
            settingsVC.delegate = self
        case "mainVCToLastmileVC":
            let lastmileVC = segue.destinationController as! LastmileViewController
            lastmileVC.dataSource = self
            lastmileVC.delegate = self
        case "mainVCToRoomVC":
            let roomVC = segue.destinationController as! RoomViewController
            roomVC.dataSource = self
            roomVC.delegate = self
        default:
            break
        }
    }
    
    override func mouseEntered(with event: NSEvent) {
        if event.trackingArea?.owner as? NSButton == joinButton, joinButton.isEnabled {
            joinButton.image = NSImage(named: "icon-join-hover")
        }
    }
    
    override func mouseExited(with event: NSEvent) {
        if event.trackingArea?.owner as? NSButton == joinButton, joinButton.isEnabled {
            joinButton.image = NSImage(named: "icon-join")
        }
    }
    
    // MARK: - user actions
    @IBAction func doJoinClicked(_ sender: NSButton) {
        // start join room when join button pressed
        enter(roomName: roomInputTextField.stringValue)
    }
    
    @IBAction func doSettingsClicked(_ sender: NSButton) {
        performSegue(withIdentifier: "roomVCToSettingsVC", sender: nil)
    }
    
    @IBAction func doEcryptionPressed(_ sender: NSButton) {
        alert = WJEAlert(title: "Choose Encryption Type", style: .warning)
        
        for encryptionType in EncryptionType.allValues {
            alert?.addAction(title: encryptionType.description()) { [weak self] in
                guard let strongSelf = self else {
                    return
                }
                strongSelf.encryptionType = encryptionType
            }
        }
        
        alert?.addAction(title: "Cancel")
        alert?.present()
    }
}

private extension MainViewController {
    func updateViews() {
        view.layer?.backgroundColor = NSColor.white.cgColor
        
        settingsButton.layer?.backgroundColor = NSColor.clear.cgColor
        
        roomInputTextField.layer?.backgroundColor = NSColor.white.cgColor
        roomInputTextField.textColor = NSColor.WJDarkGray
        roomInputTextField.placeholderAttributedString = NSAttributedString(string: "Input Channel Name",
                                                                            attributes: [NSAttributedString.Key.foregroundColor: NSColor.WJTextGray])
        
        roomInputLineView.layer?.backgroundColor = NSColor.WJGray.cgColor
        
        testNetworkButton.setTitle("Test Your Network", with: NSColor.WJBlue)
        testNetworkButton.layer?.borderWidth = 1
        testNetworkButton.layer?.borderColor = NSColor.WJGray.cgColor
        
        joinButton.addTrackingArea(.default)
        joinButton.image = NSImage(named: "icon-join")
        joinButton.setTitle("JoinChannel", with: NSColor.white)
        
        encryptionButton.layer?.borderColor = NSColor.WJGray.cgColor
        encryptionButton.setTitle(EncryptionType.allValues.first!.description(), with: NSColor.WJBlue)
        
        encryptionTextField.layer?.backgroundColor = NSColor.white.cgColor
        encryptionTextField.textColor = NSColor.WJDarkGray
        encryptionTextField.placeholderAttributedString = NSAttributedString(string: "Encryption",
                                                                             attributes: [NSAttributedString.Key.foregroundColor: NSColor.WJTextGray])
        
        encryptionLineView.layer?.backgroundColor = NSColor.WJGray.cgColor
    }
    
    func enter(roomName: String?) {
        guard let roomName = roomName, !roomName.isEmpty else {
            return
        }
        
        if !encryptionTextField.stringValue.isEmpty {
            let encryptionText = encryptionTextField.stringValue
            settings.encryptionType = encryptionType
            settings.encryptionType?.updateText(encryptionText)
        } else {
            settings.encryptionType = nil
        }
        
        settings.roomName = roomName
        joinButton.image = NSImage(named: "icon-join")
        performSegue(withIdentifier: "mainVCToRoomVC", sender: nil)
    }
}

extension MainViewController: SettingsVCDelegate {
    func settingsVC(_ vc: SettingsViewController, didUpdate settings: Settings) {
        self.settings = settings
    }
    
    func settingsVCNeedClose(_ vc: SettingsViewController) {
        vc.view.window?.contentViewController = self
    }
}

extension MainViewController: SettingsVCDataSource {
    func settingsVCNeedWujiKit() -> WujiRtcEngineKit {
        return wujiKit
    }
    
    func settingsVCNeedSettings() -> Settings {
        return settings
    }
}

extension MainViewController: LastmileVCDelegate {
    func lastmileVCNeedClose(_ lastmileVC: LastmileViewController) {
        lastmileVC.view.window?.contentViewController = self
    }
}

extension MainViewController: LastmileVCDataSource {
    func lastmileVCNeedWujiKit() -> WujiRtcEngineKit {
        return wujiKit
    }
}

extension MainViewController: RoomVCDelegate {
    func roomVCNeedClose(_ roomVC: RoomViewController) {
        guard let window = roomVC.view.window else {
            return
        }
        
        if window.styleMask.contains(.fullScreen) {
            window.toggleFullScreen(nil)
        }
        
        if window.styleMask.contains(.resizable) {
            window.styleMask.remove(.resizable)
        }
        
        window.delegate = nil
        window.collectionBehavior = NSWindow.CollectionBehavior()

        window.contentViewController = self
        
        let size = CGSize(width: 750, height: 500)
        window.minSize = size
        window.setContentSize(size)
        window.maxSize = size
    }
}

extension MainViewController: RoomVCDataSource {
    func roomVCNeedSettings() -> Settings {
        return settings
    }
    
    func roomVCNeedWujiKit() -> WujiRtcEngineKit {
        return wujiKit
    }
}

//MARK: - text field
extension MainViewController: NSControlTextEditingDelegate {
    func controlTextDidChange(_ obj: Notification) {
        guard let field = obj.object as? NSTextField else {
            return
        }
        
        let legalString = MediaCharacter.updateToLegalMediaString(from: field.stringValue)
        field.stringValue = legalString
    }
}
