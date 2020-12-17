//
//  AppDelegate.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2020年 Wuji. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.orientation = UIInterfaceOrientationMaskPortrait;
    return YES;
}

- (UIInterfaceOrientationMask)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window {
    return self.orientation;
}
@end
