//
//  SettingsViewController.swift
//  OpenVideoCall
//
//  Created by 3 on 2020/12/16.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import UIKit
import WujiRTCFramework

protocol SettingsVCDataSource: NSObjectProtocol {
    func settingsVCNeedSettings() -> Settings
}

protocol SettingsVCDelegate: NSObjectProtocol {
    func settingsVC(_ vc: SettingsViewController, didSelect dimension: CGSize)
    func settingsVC(_ vc: SettingsViewController, didSelect frameRate: WujiVideoFrameRate)
}

class SettingsViewController: UITableViewController {
    
    @IBOutlet weak var frameRateLabel: UILabel!
    @IBOutlet weak var frameRatePickerView: UIPickerView!
    @IBOutlet weak var dimensionCollectionView: UICollectionView!
    
    private var settings: Settings {
        return dataSource!.settingsVCNeedSettings()
    }
    
    private var selectedDimension: CGSize = CGSize.defaultDimension() {
        didSet {
            dimensionCollectionView?.reloadData()
        }
    }
    
    private var selectedFrameRate: WujiVideoFrameRate = WujiVideoFrameRate.defaultValue {
        didSet {
            frameRateLabel?.text = selectedFrameRate.description
        }
    }
    
    private let dimensionList: [CGSize] = CGSize.validDimensionList()
    private let frameRateList: [WujiVideoFrameRate] = WujiVideoFrameRate.validList()
    
    weak var delegate: SettingsVCDelegate?
    weak var dataSource: SettingsVCDataSource?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        selectedDimension = settings.dimension
        selectedFrameRate = settings.frameRate
        updateCollectionViewLayout()
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let frameRateChooseIndexSection = 1
        if indexPath.section == frameRateChooseIndexSection {
            tableView.deselectRow(at: indexPath, animated: true)
            doFrameRatePressed()
        }
    }
    
    override func tableView(_ tableView: UITableView, viewForHeaderInSection section: Int) -> UIView? {
        let view = UIView()
        view.backgroundColor = UIColor(red: 229.0 / 255.0, green: 229.0 / 255.0, blue: 229.0 / 255.0, alpha: 1)
        return view
    }
    
    deinit {
        delegate?.settingsVC(self, didSelect: selectedDimension)
        delegate?.settingsVC(self, didSelect: selectedFrameRate)
    }
}

private extension SettingsViewController {
    func doFrameRatePressed() {
        frameRatePickerView.isHidden.toggle()
        if let row = frameRateList.index(of: selectedFrameRate) {
            frameRatePickerView.selectRow(row, inComponent: 0, animated: true)
        }
    }
    
    func updateCollectionViewLayout() {
        let itemInteritemSpacing: CGFloat = 8
        let collectionViewInteritemSpacing: CGFloat = 19
        let width = Double((UIScreen.main.bounds.width - (collectionViewInteritemSpacing * 2) - (itemInteritemSpacing * 2)) / 3)
        let height = 40.0
        let layout = UICollectionViewFlowLayout()
        layout.minimumLineSpacing = 16
        layout.minimumInteritemSpacing = itemInteritemSpacing
        layout.itemSize = CGSize(width: width, height: height)
        dimensionCollectionView.setCollectionViewLayout(layout, animated: true)
    }
}

extension SettingsViewController: UICollectionViewDataSource {
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return dimensionList.count
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "DimensionCell", for: indexPath) as! DimensionCell
        let dimension = dimensionList[indexPath.row]
        cell.update(with: dimension, isSelected: (dimension == selectedDimension))
        return cell
    }
}

extension SettingsViewController: UICollectionViewDelegate {
    func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        let dimension = dimensionList[indexPath.row]
        selectedDimension = dimension
    }
}

extension SettingsViewController: UIPickerViewDataSource {
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return frameRateList.count
    }
}

extension SettingsViewController: UIPickerViewDelegate {
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        let frameRate = frameRateList[row]
        selectedFrameRate = frameRate
        frameRatePickerView.isHidden.toggle()
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return frameRateList[row].description
    }
    
    func pickerView(_ pickerView: UIPickerView, attributedTitleForRow row: Int, forComponent component: Int) -> NSAttributedString? {
        frameRatePickerView.subviews[0].backgroundColor = UIColor.lightGray
        frameRatePickerView.subviews[1].backgroundColor = UIColor.clear
        let frameRate = frameRateList[row].description
        return NSAttributedString(string: frameRate, attributes: [NSAttributedString.Key.foregroundColor: UIColor.black])
    }
}

extension SettingsViewController {
    override func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 16
    }
}
