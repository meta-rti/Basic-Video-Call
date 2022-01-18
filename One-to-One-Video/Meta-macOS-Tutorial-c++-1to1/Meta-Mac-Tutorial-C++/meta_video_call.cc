//
//  Meta_video_call.cpp
//  Meta-Mac-Tutorial-C++
//
//  Created by liuming on 2021/10/19.
//  Copyright © 2021 Meta.co. All rights reserved.
//

#include "meta_video_call.h"

namespace meta {
namespace rtc {

const std::string KAppId = "123";
const std::string KToken = "";

DeviceInfo::DeviceInfo(){}
DeviceInfo::~DeviceInfo(){}

MetaVideoCall::MetaVideoCall(){
    engine_ = createMetaRtcEngine();
}
MetaVideoCall::~MetaVideoCall(){
    if (engine_) {
        IRtcEngine::release();
        engine_ = nullptr;
    }
}
void MetaVideoCall::SetEngineEventHandler(IRtcEngineEventHandler *eventHandler) {
    eventHandler_ = eventHandler;
}
void MetaVideoCall::InitializeEngine(){
    
    RtcEngineContext context{};
    context.appId = KAppId.data();
    context.eventHandler = eventHandler_;
    engine_->initialize(context);
    
}
void MetaVideoCall::SetVideoEncoderConfig(const VideoEncoderConfiguration& config){
    engine_->setVideoEncoderConfiguration(config);
}
void MetaVideoCall::EnableVideo() {
    engine_->enableVideo();
}
void MetaVideoCall::JoinChannel(std::string& channel_name,uid_t uid){
    engine_->joinChannel(KToken.data(), channel_name.c_str(), nullptr, uid);
}
void MetaVideoCall::LeaveChannel() {
    engine_->leaveChannel();
}
void MetaVideoCall::MuteLocalVideoStream(bool mute){
    engine_->muteLocalVideoStream(mute);
}
void MetaVideoCall::MuteLocalAudioStream(bool mute){
    engine_->muteLocalAudioStream(mute);
}
void MetaVideoCall::startScreenCaptureByDisplayId(unsigned int displayId, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams){
    engine_->startScreenCaptureByDisplayId(displayId, regionRect, captureParams);
}
void MetaVideoCall::StopScreenCapture(){
    engine_->stopScreenCapture();
}
void MetaVideoCall::SetupLocalCanvas(VideoCanvas &canvas){
    engine_->setupLocalVideo(canvas);
}
void MetaVideoCall::SetRemoteVideoCanvas(VideoCanvas &canvas) {
    engine_->setupRemoteVideo(canvas);
}

void MetaVideoCall::StartPreview(){
    engine_->startPreview();
}
void MetaVideoCall::StopPreview(){
    engine_->stopPreview();
}

}
}
