//
//  Meta_video_call.hpp
//  Meta-Mac-Tutorial-C++
//
//  Created by liuming on 2021/10/19.
//  Copyright © 2021 Meta.co. All rights reserved.
//

#ifndef Meta_video_call_hpp
#define Meta_video_call_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

#include "IMetaRtcEngine.h"
#include "IMetaMediaEngine.h"
namespace meta {
namespace rtc {

enum MediaDeviceType {
    AUDIO_UNKNOW,
    AUDIO_PLAYOUT = 0,
    AUDIO_RECORDING,
    VIDEO_RENDER,
    VIDEO_CAPTURE,
};

class DeviceInfo {
public:
    DeviceInfo();
    ~DeviceInfo();
    
    
    std::string name_ = "";
    MediaDeviceType type_ = AUDIO_UNKNOW;
    std::string deviceId_ = "";
};


class MetaVideoCall {
 
public:
    MetaVideoCall();
    ~MetaVideoCall();
    void SetEngineEventHandler(IRtcEngineEventHandler* eventHandler);
    void InitializeEngine();
    void JoinChannel(std::string& channel_name,uid_t uid);
    void LeaveChannel();
    void MuteLocalAudioStream(bool mute);
    void MuteLocalVideoStream(bool mute);
    void startScreenCaptureByDisplayId(unsigned int displayId, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams);
    void StopScreenCapture();
    void SetupLocalCanvas(VideoCanvas& canvas);
    void SetRemoteVideoCanvas(VideoCanvas& canvas);
    void StartPreview();
    void StopPreview();
    void SetVideoEncoderConfig(const VideoEncoderConfiguration& config);
    void EnableVideo();
    
private:
    IRtcEngine * engine_;
    IRtcEngineEventHandler * eventHandler_;
    
};
}
}

#endif /* Meta_video_call_hpp */
