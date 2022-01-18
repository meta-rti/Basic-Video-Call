package rti.meta.openvcall.model;


import co.meta.rtc.IRtcEngineEventHandler;

public interface BeforeCallEventHandler extends WJEventHandler {
    void onLastmileQuality(int quality);

    void onLastmileProbeResult(IRtcEngineEventHandler.LastmileProbeResult result);
}
