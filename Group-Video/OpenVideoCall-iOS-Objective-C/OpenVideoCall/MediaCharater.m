//
//  MediaCharater.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2019 Wuji. All rights reserved.
//

#import "MediaCharater.h"

@implementation MediaCharater
+ (NSString *)updateToLegalMediaStringFromString:(NSString *)string {
    NSCharacterSet *legalMediaCharacterSet = [NSCharacterSet characterSetWithCharactersInString:@"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$%&()+,-:;<=.>?@[]^_`{|}~"];
    NSArray *separatedArray = [string componentsSeparatedByCharactersInSet:legalMediaCharacterSet.invertedSet];
    NSString *legalString = [separatedArray componentsJoinedByString:@""];
    return legalString;
}
@end
