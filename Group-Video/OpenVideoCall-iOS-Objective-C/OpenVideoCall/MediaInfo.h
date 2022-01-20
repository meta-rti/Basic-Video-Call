//
//  MediaInfo.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MediaInfo : NSObject
@property (assign, nonatomic) CGSize dimension;
@property (assign, nonatomic) NSInteger fps;
- (instancetype)initWithDimension:(CGSize)dimension fps:(NSInteger)fps;
@end
