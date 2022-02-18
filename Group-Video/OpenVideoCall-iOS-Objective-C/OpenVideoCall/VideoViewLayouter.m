//
//  VideoViewLayouter.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "VideoViewLayouter.h"

static NSString * video_Item_Identifier= @"Identifier";

@interface VideoViewLayouter ()<UICollectionViewDelegate,UICollectionViewDataSource>
@property (assign, nonatomic) NSInteger MaxPeerCount;
@property (strong, nonatomic) NSMutableArray<NSLayoutConstraint *> *layoutConstraints;
@property (strong, nonatomic) UICollectionView * collectionView;
@property (strong, nonatomic) VideoCollectionLayout * layout;
@property (readonly, nonatomic) NSArray<UIView *> *allViews;

@end

@implementation VideoViewLayouter


- (NSMutableArray<NSLayoutConstraint *> *)layoutConstraints {
    if (!_layoutConstraints) {
        _layoutConstraints = [[NSMutableArray<NSLayoutConstraint *> alloc] init];
    }
    return _layoutConstraints;
}

- (UICollectionView *) collectionView {
    if (_collectionView == nil) {
        self.layout = [[VideoCollectionLayout alloc] init];
        self.layout.sectionInsets = UIEdgeInsetsMake(5, 5, 5, 5);
        
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectZero
                                             collectionViewLayout:self.layout];
        _collectionView.showsHorizontalScrollIndicator = NO;
        _collectionView.showsVerticalScrollIndicator = NO;
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        _collectionView.backgroundColor = [UIColor colorWithWhite:1.0f alpha:0];
        [_collectionView registerClass:[VideoCollectionCell class] forCellWithReuseIdentifier:video_Item_Identifier];
        
        _collectionView.translatesAutoresizingMaskIntoConstraints = NO;
        
        }
    return _collectionView;
}

- (instancetype)init {
    if (self = [super init]) {
        self.MaxPeerCount = 10000;
    }
    return self;
}

- (void)layoutVideoViews {
    if (!self.selfView || !self.containerView ) {
        return;
    }
    
    [self.selfView removeFromSuperview];
    for (UIView *view in self.videoViews) {
        [view removeFromSuperview];
    }
    [self.collectionView removeFromSuperview];
    
    [NSLayoutConstraint deactivateConstraints:self.layoutConstraints];
    [self.layoutConstraints removeAllObjects];
    
    
    NSMutableArray *allViews = [[NSMutableArray alloc] init];
    if (self.selfView) {
        [allViews addObject:self.selfView];
    }
    if (self.videoViews) {
        [allViews addObjectsFromArray:self.videoViews];
    }
  
    _allViews = [allViews copy];
    
    NSInteger count = self.videoViews.count;
    if (count == 0) {
        NSArray *fullViewLayouts = [self layoutFullSessionView:self.selfView inContainerView:self.containerView];
        [self.layoutConstraints addObjectsFromArray:fullViewLayouts];
        
    } else if (count == 1) {
        UIView *peerView = self.videoViews.firstObject;
        NSArray *fullViewLayouts = [self layoutFullSessionView:peerView inContainerView:self.containerView];
        [self.layoutConstraints addObjectsFromArray:fullViewLayouts];
        
        NSArray *cornerViewLayouts = [self layoutCornerSessionView:self.selfView inContainerView:self.containerView];
        [self.layoutConstraints addObjectsFromArray:cornerViewLayouts];
        
    } else {
        if (self.fullView) {
            NSArray *fullViewLayouts = [self layoutFullSessionView:self.fullView inContainerView:self.containerView];
            [self.layoutConstraints addObjectsFromArray:fullViewLayouts];
            
            NSMutableArray *smallViews = [[NSMutableArray alloc] init];
            for (UIView *view in self.videoViews) {
                if (view != self.fullView && smallViews.count < self.MaxPeerCount) {
                    [smallViews addObject:view];
                }
            }
            if (smallViews.count < self.MaxPeerCount && self.fullView != self.selfView) {
                [smallViews addObject:self.selfView];
            }
            _allViews = [smallViews copy];
            NSArray *smallViewLayouts = [self layoutSmallSessionViews:smallViews inContainerView:self.containerView];
            [self.layoutConstraints addObjectsFromArray:smallViewLayouts];
            
        } else {
            NSArray *layouts = [self layoutEqualSessionViews:self.allViews inContainerView:self.containerView];
            [self.layoutConstraints addObjectsFromArray:layouts];
        }
    }
    
    if (self.layoutConstraints.count) {
        [NSLayoutConstraint activateConstraints:self.layoutConstraints];
    }
    if (count >= 4) {
        [self.collectionView reloadData];
    }
}

- (NSInteger)responseIndexOfLocation:(CGPoint)location {
    if (!self.selfView || !self.containerView || self.fullView) {
        return -1;
    }
    
    NSMutableArray *allViews = [[NSMutableArray alloc] init];
    [allViews addObject:self.selfView];
    [allViews addObjectsFromArray:self.videoViews];
    
    for (NSInteger index = 0; index < allViews.count; ++index) {
        UIView *view = allViews[index];
        if (view.superview == self.containerView && CGRectContainsPoint(view.frame, location)) {
            return index;
        }
    }
    
    return -1;
}

- (NSArray<NSLayoutConstraint *> *)layoutFullSessionView:(UIView *)view inContainerView:(UIView *)container {
    NSMutableArray *layouts = [[NSMutableArray alloc] init];
    [container addSubview:view];
    
    NSArray<NSLayoutConstraint *> *constraintsH = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|[view]|" options:0 metrics:nil views:@{@"view": view}];
    NSArray<NSLayoutConstraint *> *constraintsV = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|[view]|" options:0 metrics:nil views:@{@"view": view}];
    [layouts addObjectsFromArray:constraintsH];
    [layouts addObjectsFromArray:constraintsV];
    
    return [layouts copy];
}

- (NSArray<NSLayoutConstraint *> *)layoutCornerSessionView:(UIView *)view inContainerView:(UIView *)container {
    NSMutableArray *layouts = [[NSMutableArray alloc] init];
    [container addSubview:view];
    
    NSLayoutConstraint *right = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:container attribute:NSLayoutAttributeRight multiplier:1 constant:-5];
    NSLayoutConstraint *top = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:container attribute:NSLayoutAttributeTop multiplier:1 constant:64];
    NSLayoutConstraint *width = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1 constant:120];
    NSLayoutConstraint *height = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1 constant:120];
    
    [layouts addObjectsFromArray:@[right, top, width, height]];
    
    return layouts;
}

- (NSArray<NSLayoutConstraint *> *)layoutSmallSessionViews:(NSArray<UIView *> *)smallViews inContainerView:(UIView *)container {
    
    self.layout.layoutMode = VideoCollectionLayoutSmall;
    [container addSubview:self.collectionView];
    
    
    NSMutableArray *layouts = [[NSMutableArray alloc] init];
    NSLayoutConstraint *scrollTop = [NSLayoutConstraint constraintWithItem:self.collectionView
                                                                 attribute:NSLayoutAttributeTop
                                                                 relatedBy:NSLayoutRelationEqual
                                                                    toItem:container
                                                                 attribute:NSLayoutAttributeTop
                                                                multiplier:1
                                                                  constant:80];
    
    NSLayoutConstraint *scrollLeft = [NSLayoutConstraint constraintWithItem:self.collectionView
                                                                  attribute:NSLayoutAttributeLeft
                                                                  relatedBy:NSLayoutRelationEqual
                                                                     toItem:container
                                                                  attribute:NSLayoutAttributeLeft
                                                                 multiplier:1
                                                                   constant:0];
    NSLayoutConstraint *viewWidth = [NSLayoutConstraint constraintWithItem:self.collectionView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1 constant:CGRectGetWidth(container.frame)];
    NSLayoutConstraint *viewHeight = [NSLayoutConstraint constraintWithItem:self.collectionView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1 constant:120];

    [layouts addObjectsFromArray:@[scrollTop,scrollLeft,viewWidth,viewHeight]];
    [self.collectionView reloadData];
    return [layouts copy];
}

- (NSArray<NSLayoutConstraint *> *)layoutEqualSessionViews:(NSArray<UIView *> *)allViews inContainerView:(UIView *)container {
    NSMutableArray *layouts = [[NSMutableArray alloc] init];
    NSUInteger viewCount = allViews.count;
    
    if (viewCount == 1) {
        [layouts addObjectsFromArray:[self layoutFullSessionView:allViews.firstObject inContainerView:container]];
    } else if (viewCount == 2) {
        UIView *firstView = allViews.firstObject;
        UIView *lastView = allViews.lastObject;
        [container addSubview:firstView];
        [container addSubview:lastView];
        
        NSArray<NSLayoutConstraint *> *h1 = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|[view]|" options:0 metrics:nil views:@{@"view": firstView}];
        NSArray<NSLayoutConstraint *> *h2 = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|[view]|" options:0 metrics:nil views:@{@"view": lastView}];
        NSArray<NSLayoutConstraint *> *v = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|[view1]-1-[view2]|" options:0 metrics:nil views:@{@"view1": firstView, @"view2": lastView}];
        NSLayoutConstraint *equal = [NSLayoutConstraint constraintWithItem:firstView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:lastView attribute:NSLayoutAttributeHeight multiplier:1 constant:0];
        
        [layouts addObjectsFromArray:h1];
        [layouts addObjectsFromArray:h2];
        [layouts addObjectsFromArray:v];
        [layouts addObject:equal];
        
    } else if (viewCount == 3) {
        UIView *firstView = allViews.firstObject;
        UIView *secondView = allViews[1];
        UIView *lastView = allViews.lastObject;
        [container addSubview:firstView];
        [container addSubview:secondView];
        [container addSubview:lastView];
        
        NSArray<NSLayoutConstraint *> *h1 = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|[view1]-1-[view2]|" options:0 metrics:nil views:@{@"view1": firstView, @"view2": secondView}];
        NSArray<NSLayoutConstraint *> *v1 = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|[view1]-1-[view2]|" options:0 metrics:nil views:@{@"view1": firstView, @"view2": lastView}];
        NSLayoutConstraint *left = [NSLayoutConstraint constraintWithItem:lastView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:container attribute:NSLayoutAttributeLeft multiplier:1 constant:0];
        NSLayoutConstraint *top = [NSLayoutConstraint constraintWithItem:secondView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:container attribute:NSLayoutAttributeTop multiplier:1 constant:0];
        NSLayoutConstraint *equalWidth1 = [NSLayoutConstraint constraintWithItem:firstView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:secondView attribute:NSLayoutAttributeWidth multiplier:1 constant:0];
        NSLayoutConstraint *equalWidth2 = [NSLayoutConstraint constraintWithItem:firstView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:lastView attribute:NSLayoutAttributeWidth multiplier:1 constant:0];
        NSLayoutConstraint *equalHeight1 = [NSLayoutConstraint constraintWithItem:firstView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:secondView attribute:NSLayoutAttributeHeight multiplier:1 constant:0];
        NSLayoutConstraint *equalHeight2 = [NSLayoutConstraint constraintWithItem:firstView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:lastView attribute:NSLayoutAttributeHeight multiplier:1 constant:0];
        
        [layouts addObjectsFromArray:h1];
        [layouts addObjectsFromArray:v1];
        [layouts addObjectsFromArray:@[left, top, equalWidth1, equalWidth2, equalHeight1, equalHeight2]];
        
    } else if (viewCount >= 4) {
        self.layout.layoutMode = VideoCollectionLayoutFull;
        [self.containerView addSubview:self.collectionView];
        NSLayoutConstraint *scrollTop = [NSLayoutConstraint constraintWithItem:self.collectionView
                                                                     attribute:NSLayoutAttributeTop
                                                                     relatedBy:NSLayoutRelationEqual
                                                                        toItem:container
                                                                     attribute:NSLayoutAttributeTop
                                                                    multiplier:1
                                                                      constant:0];
        
        NSLayoutConstraint *scrollLeft = [NSLayoutConstraint constraintWithItem:self.collectionView
                                                                      attribute:NSLayoutAttributeLeft
                                                                      relatedBy:NSLayoutRelationEqual
                                                                         toItem:container
                                                                      attribute:NSLayoutAttributeLeft
                                                                     multiplier:1
                                                                       constant:0];
        
        NSLayoutConstraint *scrollRight = [NSLayoutConstraint constraintWithItem:self.collectionView
                                                                       attribute:NSLayoutAttributeRight
                                                                       relatedBy:NSLayoutRelationEqual
                                                                          toItem:container
                                                                       attribute:NSLayoutAttributeRight
                                                                      multiplier:1
                                                                        constant:0];
        NSLayoutConstraint *scrollBottom = [NSLayoutConstraint constraintWithItem:self.collectionView
                                                                        attribute:NSLayoutAttributeBottom
                                                                        relatedBy:NSLayoutRelationEqual
                                                                           toItem:container
                                                                        attribute:NSLayoutAttributeBottom
                                                                       multiplier:1
                                                                         constant:0];
        [layouts addObjectsFromArray:@[scrollTop,scrollLeft,scrollRight,scrollBottom]];
        
    }
    
    return [layouts copy];
}

#pragma mark-
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.allViews.count;
}
- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    VideoCollectionCell * cell = [collectionView dequeueReusableCellWithReuseIdentifier:video_Item_Identifier forIndexPath:indexPath];
   [cell addVideoView:self.allViews[indexPath.item]];
    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    if (self.delegate && [self.delegate respondsToSelector:@selector(viewLayouter:didSeleted:)]) {
        [self.delegate viewLayouter:self didSeleted:indexPath.item];
    }
}
@end

@interface VideoCollectionLayout ()
@property(nonatomic,assign)NSInteger currentX;
@property(nonatomic,assign)NSInteger currentY;
@property(nonatomic,assign)NSInteger contentWidth;
@property(nonatomic,assign)NSInteger contentHeight;
@end

@implementation VideoCollectionLayout

- (void)prepareLayout {
    [super prepareLayout];
    //    self.layoutMode = VideoCollectionLayoutSmall;
    self.currentX = 0;
    self.currentY = 0;
    _contentWidth = 0;
    _contentHeight = 0;
    NSInteger count = [self.collectionView numberOfItemsInSection:0];
    for (NSInteger i = 0; i < count; i++) {
        NSIndexPath * indexPath = [NSIndexPath indexPathForItem:i inSection:0];
        UICollectionViewLayoutAttributes * attributes = [self layoutAttributesForItemAtIndexPath:indexPath];
        [self.attributesArray addObject:attributes];
        _contentWidth = MAX(CGRectGetMaxX(attributes.frame) + self.sectionInsets.right , _contentWidth);
        _contentHeight = MAX(CGRectGetMaxY(attributes.frame) + self.sectionInsets.bottom,_contentHeight);
    }
}

- (UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    UICollectionViewLayoutAttributes * attributes = [UICollectionViewLayoutAttributes layoutAttributesForCellWithIndexPath:indexPath];
    CGSize itemSize = [self itemSize];
    NSInteger x = self.sectionInsets.left;
    NSInteger y = self.sectionInsets.top;
    if (self.layoutMode ==  VideoCollectionLayoutFull) {
        NSInteger col = indexPath.item % 2;
        x = self.sectionInsets.left +  (itemSize.width + self.sectionInsets.left ) * col ;
        y = self.currentY + self.sectionInsets.top ;
        if (col == 1) {
            self.currentY = y + itemSize.height;
        }
    } else {
        y = self.sectionInsets.top;
        x = self.currentX + self.sectionInsets.left;
        self.currentX = x + itemSize.width;
        
    }
    attributes.frame = CGRectMake(x, y, itemSize.width, itemSize.height);
    NSLog(@" layout size = %@",NSStringFromCGRect(attributes.frame));
    return attributes;
}

- (CGSize)collectionViewContentSize {
    return CGSizeMake(_contentWidth, _contentHeight);
}

- (NSArray<__kindof UICollectionViewLayoutAttributes *> *)layoutAttributesForElementsInRect:(CGRect)rect {
    return _attributesArray;
}
#pragma mark -
- (NSMutableArray *)attributesArray {
    if (_attributesArray == nil) {
        _attributesArray = [[NSMutableArray alloc] init];
    }
    return _attributesArray;
}
- (CGSize)itemSize {
    if (self.layoutMode == VideoCollectionLayoutFull) {
        int itemWidth = (CGRectGetWidth(self.collectionView.frame) - 15) / 2;
        int itemHeight = (CGRectGetHeight(self.collectionView.frame) - 10) / 2;
        return CGSizeMake(itemWidth, itemHeight);
    }
    return CGSizeMake(110, 110);
}
@end

@interface VideoCollectionCell()
@property(nonatomic,strong)UIView * videoView;
@property(nonatomic,strong)NSMutableArray * layouts;
@end
@implementation VideoCollectionCell
- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.layouts = [[NSMutableArray alloc] init];
    }
    return self;
}
- (void)addVideoView:(UIView *)videoView {
    [videoView removeFromSuperview];
    [self removeVideoViewLayout];
    self.videoView = videoView;
    videoView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.contentView addSubview:videoView];
    [self.layouts addObjectsFromArray:[self layoutVideoView]];
    if (self.layouts.count) {
        [NSLayoutConstraint activateConstraints:self.layouts];
    }
}

- (void)prepareForReuse {
    [super prepareForReuse];
}

- (void)removeVideoViewLayout{
    if (self.layouts.count) {
        [NSLayoutConstraint deactivateConstraints:self.layouts];
        [self.layouts removeAllObjects];
    }
    [self.layouts removeAllObjects];
}

- (NSArray *)layoutVideoView {
    NSLayoutConstraint *top = [NSLayoutConstraint constraintWithItem:self.videoView
                                                                 attribute:NSLayoutAttributeTop
                                                                 relatedBy:NSLayoutRelationEqual
                                                                    toItem:self.contentView
                                                                 attribute:NSLayoutAttributeTop
                                                                multiplier:1
                                                                  constant:0];
    
    NSLayoutConstraint *left = [NSLayoutConstraint constraintWithItem:self.videoView
                                                                  attribute:NSLayoutAttributeLeft
                                                                  relatedBy:NSLayoutRelationEqual
                                                                     toItem:self.contentView
                                                                  attribute:NSLayoutAttributeLeft
                                                                 multiplier:1
                                                                   constant:0];
    
    NSLayoutConstraint *right  = [NSLayoutConstraint constraintWithItem:self.videoView
                                                                       attribute:NSLayoutAttributeRight
                                                                       relatedBy:NSLayoutRelationEqual
                                                                          toItem:self.contentView
                                                                       attribute:NSLayoutAttributeRight
                                                                      multiplier:1
                                                                        constant:0];
    NSLayoutConstraint *bottom = [NSLayoutConstraint constraintWithItem:self.videoView
                                                                     attribute:NSLayoutAttributeBottom
                                                                     relatedBy:NSLayoutRelationEqual
                                                                        toItem:self.contentView
                                                                     attribute:NSLayoutAttributeBottom
                                                                    multiplier:1
                                                                      constant:0] ;
    return @[top,left,right,bottom];
}
@end

