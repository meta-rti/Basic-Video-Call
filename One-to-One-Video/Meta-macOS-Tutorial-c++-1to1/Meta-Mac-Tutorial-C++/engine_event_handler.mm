//
//  engine_event_handler.cpp
//  Meta-Mac-Tutorial-C++
//
//  Created by liuming on 2021/10/19.
//  Copyright © 2021 Meta.co. All rights reserved.
//

#include "engine_event_handler.h"
namespace meta {
namespace rtc {

void RTCEngineEventHandler::onUserJoined(uid_t uid, int elapsed) {
    if (_delegate) {
        [_delegate userJoined:uid elapsed:elapsed];
    }
}
void RTCEngineEventHandler::onJoinChannelSuccess(const char *channel, uid_t uid, int elapsed){
    if (_delegate) {
        [_delegate joinChannel:[NSString stringWithCString:channel encoding:NSUTF8StringEncoding] uid:uid elapsed:elapsed];
    }
}
void RTCEngineEventHandler::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) {
    if (_delegate) {
        [_delegate userDidOffline:uid reason:reason];
    }
}
void RTCEngineEventHandler::onUserMuteVideo(uid_t uid, bool muted) {
    if (_delegate) {
        [_delegate user:uid muteVideo:muted];
    }
}
}
}

