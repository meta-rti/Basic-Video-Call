package io.wuji.openvcall.model;


import co.wuji.rtc.IRtcEngineEventHandler;

public interface BeforeCallEventHandler extends WJEventHandler {
    void onLastmileQuality(int quality);

    void onLastmileProbeResult(IRtcEngineEventHandler.LastmileProbeResult result);
}
