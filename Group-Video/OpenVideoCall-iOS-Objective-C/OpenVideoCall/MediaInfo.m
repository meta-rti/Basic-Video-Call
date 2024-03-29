//
//  MediaInfo.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "MediaInfo.h"

@implementation MediaInfo
- (NSString *)description {
    return [NSString stringWithFormat:@"%ld x %ld, %ld fps", (NSInteger)self.dimension.width, (NSInteger)self.dimension.height, self.fps];
}

- (instancetype)initWithDimension:(CGSize)dimension fps:(NSInteger)fps {
    if (self = [super init]) {
        self.dimension = dimension;
        self.fps = fps;
    }
    return self;
}
@end
