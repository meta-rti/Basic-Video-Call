//
//  ProfileCell.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "DimensionCell.h"
#import "CommonExtension.h"

@interface DimensionCell()
@property (weak, nonatomic) IBOutlet UILabel *dimensionLabel;
@end

@implementation DimensionCell
- (void)updateWithDimension:(CGSize)dimension isSelected:(BOOL)isSelected {
    self.dimensionLabel.text = [NSString stringWithFormat:@"%.0fx%.0f", dimension.width, dimension.height];
    self.dimensionLabel.textColor = isSelected ? UIColor.whiteColor : UIColor.WJTextGray;
    self.dimensionLabel.backgroundColor = isSelected ? UIColor.WJBlue : UIColor.whiteColor;
    self.dimensionLabel.layer.borderColor = isSelected ? UIColor.WJBlue.CGColor : UIColor.WJGray.CGColor;
}
@end
