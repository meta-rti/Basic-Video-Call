//
//  ProfileCell.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MetaRTCFramework/MetaRTCFramework.h>

@interface DimensionCell : UICollectionViewCell
- (void)updateWithDimension:(CGSize)dimension isSelected:(BOOL)isSelected;
@end
