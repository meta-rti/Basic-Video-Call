//
//  VideoChatViewController.h
//  Meta Mac Tutorial Objective-C
//
//  Created by 3 on 2020/12/17.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <MetaRTCFramework/MetaRTCFramework.h>
#import "AppID.h"
#import "DeviceSelectionViewController.h"

@interface VideoChatViewController : NSViewController <MetaRtcEngineDelegate>

@end

