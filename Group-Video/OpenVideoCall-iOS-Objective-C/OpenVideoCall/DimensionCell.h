//
//  ProfileCell.h
//  OpenVideoCall
//
//  Created by GongYuhua on 2016/9/12.
//  Copyright © 2020年 Wuji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WujiRTCFramework_Debug/WujiRTCFramework_Debug.h>

@interface DimensionCell : UICollectionViewCell
- (void)updateWithDimension:(CGSize)dimension isSelected:(BOOL)isSelected;
@end
