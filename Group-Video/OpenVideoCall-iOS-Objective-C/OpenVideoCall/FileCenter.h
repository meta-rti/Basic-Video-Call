//
//  FileCenter.h
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FileCenter : NSObject
+ (NSString *)logDirectory;
+ (NSString *)logFilePath;
+ (NSString *)audioFilePath;
@end

NS_ASSUME_NONNULL_END
