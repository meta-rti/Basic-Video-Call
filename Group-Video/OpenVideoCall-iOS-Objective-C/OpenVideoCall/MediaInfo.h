//
//  MediaInfo.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2019 Wuji. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MediaInfo : NSObject
@property (assign, nonatomic) CGSize dimension;
@property (assign, nonatomic) NSInteger fps;
- (instancetype)initWithDimension:(CGSize)dimension fps:(NSInteger)fps;
@end
