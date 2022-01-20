//
//  FileCenter.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "FileCenter.h"

@implementation FileCenter
+ (NSString *)logDirectory {
    NSString *directory = [[self documentDirectory] stringByAppendingPathComponent:@"MetaLogs"];
    [self checkAndCreateDirectoryAtPath:directory];
    return directory;
}

+ (NSString *)logFilePath {
    return [[self logDirectory] stringByAppendingPathComponent:@"Meta-rtc.log"];
}

+ (NSString *)audioFilePath {
    return [[NSBundle mainBundle] pathForResource:@"audioTest" ofType:@"mp3"];
}

+ (NSString *)documentDirectory {
    return NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject;
}

+ (void)checkAndCreateDirectoryAtPath:(NSString *)path {
    BOOL isDirectory = NO;
    BOOL exists = [[NSFileManager defaultManager] fileExistsAtPath:path isDirectory:&isDirectory];
    
    if (!exists || !isDirectory) {
        [[NSFileManager defaultManager] createDirectoryAtPath:path withIntermediateDirectories:YES attributes:nil error:nil];
    }
}
@end
