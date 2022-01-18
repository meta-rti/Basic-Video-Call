//
//  AppID.m
//  Meta Mac Tutorial Objective-C
//
//  Created by 3 on 2020/12/17.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <Foundation/Foundation.h>

NSString *const AppID = @"123";
/* assign Token to nil if you have not enabled app certificate
 * before you deploy your own token server, you can easily generate a temp token for dev use
 */
/* 如果没有打开鉴权Token, 这里的token值给nil就好
 * 临时Token. 请注意生成Token时指定的频道名, 该Token只允许加入对应的频道
 */
NSString *const Token = @"";
