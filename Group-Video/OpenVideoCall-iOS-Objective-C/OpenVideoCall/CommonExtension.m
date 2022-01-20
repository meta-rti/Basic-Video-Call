//
//  CommonExtension.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "CommonExtension.h"

@implementation UIColor (META)
+ (UIColor *)WJTextGray {
    return [UIColor colorWithRed:102.0 / 255.0 green:102.0 / 255.0 blue:102.0 / 255.0 alpha:1];
}

+ (UIColor *)WJGray {
    return [UIColor colorWithRed:204.0 / 255.0 green:204.0 / 255.0 blue:204.0 / 255.0 alpha:1];
}

+ (UIColor *)WJBlue {
    return [UIColor colorWithRed:0 green:106.0 / 255.0 blue:216.0 / 255.0 alpha:1];
}

+ (UIColor *)WJMessageInfoColor {
    return [UIColor colorWithRed:0 green:0 blue:1 alpha:0.5];;
}
+ (UIColor *)WJMessageErrorColor {
    return [UIColor colorWithRed:1 green:0.5 blue:0 alpha:0.5];
}
@end
