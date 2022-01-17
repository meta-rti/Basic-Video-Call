package rti.meta.openvcall.model;

public class EngineConfig {
    public int mUid;

    public String mChannel;

    public void reset() {
        mChannel = null;
    }

    public EngineConfig() {
    }
}
