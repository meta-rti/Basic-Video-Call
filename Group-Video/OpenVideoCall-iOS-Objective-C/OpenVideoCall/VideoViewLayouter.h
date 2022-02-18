//
//  VideoViewLayouter.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "VideoSession.h"

@class VideoViewLayouter;
@protocol VideoViewLayouterDeletate <NSObject>
- (void)viewLayouter:(VideoViewLayouter *)layouter didSeleted:(NSInteger)index;
@end

@interface VideoViewLayouter : NSObject

@property(weak,nonatomic)id<VideoViewLayouterDeletate> delegate;
@property (strong, nonatomic) UIView *selfView;
@property (assign, nonatomic) CGSize selfSize;
@property (assign, nonatomic) CGSize targetSize;

@property (strong, nonatomic) NSArray<UIView *> *videoViews;
@property (strong, nonatomic) UIView *fullView;
@property (strong, nonatomic) UIView *containerView;

- (void)layoutVideoViews;
- (NSInteger)responseIndexOfLocation:(CGPoint)location;
@end


typedef NS_ENUM(NSInteger,VideoCollectionLayoutModel) {
    
    VideoCollectionLayoutFull,
    VideoCollectionLayoutSmall
};
@interface VideoCollectionLayout : UICollectionViewLayout
@property(nonatomic,assign)VideoCollectionLayoutModel layoutMode;
@property(nonatomic,strong)NSMutableArray * attributesArray;
@property(nonatomic,assign)UIEdgeInsets sectionInsets;
@end

@interface VideoCollectionCell : UICollectionViewCell
- (void)addVideoView:(UIView *)videoView;
@end
