//
//  SettingsViewController.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "SettingsViewController.h"
#import "DimensionCell.h"
#import <MetaRTCFramework/MetaRTCFramework.h>

@interface SettingsViewController () <UICollectionViewDelegate, UICollectionViewDataSource, UIPickerViewDelegate, UIPickerViewDataSource>
@property (weak, nonatomic) IBOutlet UICollectionView *dimensionCollectionView;
@property (weak, nonatomic) IBOutlet UIPickerView *frameRatePickerView;
@property (weak, nonatomic) IBOutlet UILabel *frameRateLabel;

@property (assign, nonatomic) MetaVideoFrameRate selectedFrameRate;
@property (assign, nonatomic) CGSize selectedDimension;
@property (strong, nonatomic) Settings *settings;
@property (strong, nonatomic) NSArray *dimensionList;
@property (strong, nonatomic) NSArray *frameRateList;
@end

@implementation SettingsViewController
#pragma mark - Getter, Setter
- (NSArray *)dimensionList {
    if (!_dimensionList) {
        _dimensionList = @[@(MetaVideoDimension160x120),
                           @(MetaVideoDimension240x180),
                           @(MetaVideoDimension320x240),
                           @(MetaVideoDimension640x360),
                           @(MetaVideoDimension640x480),
                           @(MetaVideoDimension960x720)];
    }
    return _dimensionList;
}

- (NSArray *)frameRateList {
    if (!_frameRateList) {
        _frameRateList = @[@(MetaVideoFrameRateFps1),
                           @(MetaVideoFrameRateFps7),
                           @(MetaVideoFrameRateFps10),
                           @(MetaVideoFrameRateFps15),
                           @(MetaVideoFrameRateFps24),
                           @(MetaVideoFrameRateFps30)];
    }
    return _frameRateList;
}

- (Settings *)settings {
    return [self.dataSource settingsVCNeedSettings];
}

- (void)setSelectedDimension:(CGSize)selectedDimension {
    _selectedDimension = selectedDimension;
    [self.dimensionCollectionView reloadData];
}

- (void)setSelectedFrameRate:(MetaVideoFrameRate)selectedFrameRate {
    _selectedFrameRate = selectedFrameRate;
    self.frameRateLabel.text = [self descriptionOfFrameRate:selectedFrameRate];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self updateCollectionViewLayout];
    self.selectedDimension = self.settings.dimension;
    self.selectedFrameRate = self.settings.frameRate;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSInteger frameRateChooseIndexSection = 1;
    if (indexPath.section == frameRateChooseIndexSection) {
        [tableView deselectRowAtIndexPath:indexPath animated:YES];
        [self doFrameRatePressed];
    }
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    UIView *view = [[UIView alloc] init];
    view.backgroundColor = [UIColor colorWithRed:229.0 / 255.0 green:229.0 / 255.0 blue:229.0 / 255.0 alpha:1];
    return view;
}

#pragma mark - Private
- (void)doFrameRatePressed {
    self.frameRatePickerView.hidden = !self.frameRatePickerView.hidden;
    NSUInteger row = [self.frameRateList indexOfObject:@(self.selectedFrameRate)];
    [self.frameRatePickerView selectRow:row inComponent:0 animated:YES];
}

- (void)updateCollectionViewLayout {
    CGFloat itemInteritemSpacing = 8;
    CGFloat collectionViewInteritemSpacing = 19;
    CGFloat screenWidth = [UIScreen mainScreen].bounds.size.width;
    CGFloat width = ((screenWidth - (collectionViewInteritemSpacing * 2) - (itemInteritemSpacing * 2)) / 3);
    CGFloat height = 40;
    UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
    layout.minimumLineSpacing = 16;
    layout.minimumInteritemSpacing = itemInteritemSpacing;
    layout.itemSize = CGSizeMake(width, height);
    [self.dimensionCollectionView setCollectionViewLayout:layout animated:YES];
}

#pragma mark - UICollectionViewDelegate, UICollectionViewDataSource
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.dimensionList.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    DimensionCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"DimensionCell" forIndexPath:indexPath];
    CGSize dimension = [self.dimensionList[indexPath.row] CGSizeValue];
    BOOL isSelected = [self sizeIsEqual:dimension right:self.selectedDimension];
    [cell updateWithDimension:dimension isSelected:isSelected];
    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    self.selectedDimension = [self.dimensionList[indexPath.row] CGSizeValue];
    [self.delegate settingsVC:self didSelectDimension:self.selectedDimension];
}

#pragma mark - UIPickerViewDelegate, UIPickerViewDataSource
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    return self.frameRateList.count;
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    self.selectedFrameRate = [self.frameRateList[row] integerValue];
    self.frameRatePickerView.hidden = YES;
    [self.delegate settingsVC:self didSelectFrameRate:self.selectedFrameRate];
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    return [self descriptionOfFrameRate:[self.frameRateList[row] integerValue]];
}

- (NSAttributedString *)pickerView:(UIPickerView *)pickerView attributedTitleForRow:(NSInteger)row forComponent:(NSInteger)component {
    self.frameRatePickerView.subviews[0].backgroundColor = [UIColor lightGrayColor];
    self.frameRatePickerView.subviews[1].backgroundColor = [UIColor clearColor];
    NSString *frameRate = [self descriptionOfFrameRate:[self.frameRateList[row] integerValue]];
    return [[NSAttributedString alloc] initWithString:frameRate
                                           attributes:@{NSForegroundColorAttributeName: [UIColor blackColor]}];
}

#pragma mark - Others
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 16;
}

- (NSString *)descriptionOfFrameRate:(MetaVideoFrameRate)frameRate {
    switch (frameRate) {
        case MetaVideoFrameRateFps1:  return @"1 fps";     break;
        case MetaVideoFrameRateFps7:  return @"7 fps";     break;
        case MetaVideoFrameRateFps10: return @"10 fps";    break;
        case MetaVideoFrameRateFps15: return @"15 fps";    break;
        case MetaVideoFrameRateFps24: return @"24 fps";    break;
        case MetaVideoFrameRateFps30: return @"30 fps";    break;
        default:                       return @"unsported"; break;
    }
}

- (BOOL)sizeIsEqual:(CGSize)left right:(CGSize)right {
    if (left.width == right.width && left.height == right.height) {
        return YES;
    }
    return NO;
}
@end
