//
//  engine_event_handler.hpp
//  Meta-Mac-Tutorial-C++
//
//  Created by liuming on 2021/10/19.
//  Copyright © 2021 Meta.co. All rights reserved.
//

#ifndef engine_event_handler_hpp
#define engine_event_handler_hpp
#include "IMetaRtcEngine.h"
#include "IMetaMediaEngine.h"
#include <stdio.h>
#import <Foundation/Foundation.h>

@protocol RTCEngineEventDelegate <NSObject>
- (void)joinChannel:(NSString *)channel uid:(NSUInteger)uid elapsed:(int)elapsed;
- (void)userDidOffline:(NSUInteger)uid reason:(meta::rtc::USER_OFFLINE_REASON_TYPE)reason;
- (void)user:(NSUInteger)uid muteVideo:(BOOL)mute;
- (void)userJoined:(NSUInteger) uid elapsed:(int)elapsed;
@end

namespace meta {
namespace rtc {
class RTCEngineEventHandler:public IRtcEngineEventHandler {
public:
    __weak id<RTCEngineEventDelegate> _delegate;
    protected:
    void onJoinChannelSuccess(const char *channel, uid_t uid, int elapsed) override;
    void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) override;
    void onUserMuteVideo(uid_t uid, bool muted) override;
    void onUserJoined(uid_t uid, int elapsed) override;
};
}
}

#endif /* engine_event_handler_hpp */
