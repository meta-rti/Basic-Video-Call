//
//  WujiRtcEngine SDK
//
//  Copyright (c) 2019 Wuji.io. All rights reserved.
//

/**
 @defgroup createWujiRtcEngine Create an WujiRtcEngine
 */

#ifndef WUJI_RTC_P2P_INTERFACE_H
#define WUJI_RTC_P2P_INTERFACE_H

#include <string>
#include <vector>
#include "WujiBase.h"

namespace wuji {
    namespace base {

        class IWujiP2pEventHandler {
        public:
            // virtual void onTrackerUpdated() = 0;
            virtual void onPeerConnected(const std::string &peerId) = 0;
            virtual void onPeerClosed(const std::string &peerId) = 0;
            virtual void onPeerMessage(const std::string &message) = 0;
        };

        //class IWujiP2p {
        //protected:
        //    virtual ~IWujiP2p() {}

        //public:
        //    // WUJI_CPP_API static void release();

        //    /** Initializes the engine.

        //  @param context RtcEngine context.
        //  @return
        //  - 0: Success.
        //  - < 0: Failure.
        //  */
        //  //virtual int initialize(const std::string &videoId, const std::string &localId) = 0;
        //    virtual void connectPeer(const std::string &remoteId) = 0;
        //    virtual void send(const std::string &peerId, const std::string &message) = 0;

        //};

        //class IWujiP2pChannel {
        //public:
        //    IWujiP2pChannel() { _p2p = NULL; }

        //    virtual void onPeerConnected(const std::string &peerId) = 0;
        //    virtual void onPeerClosed(const std::string &peerId) = 0;
        //    virtual void onPeerMessage(const std::string &message) = 0;

        //    IWujiP2p *_p2p;
        //    std::string _channelId;
        //};

        class IWujiP2pTracker {
        public:
            virtual void sendP2pTrackerMessage(const std::string &remoteId, const std::string &message) = 0;
            //virtual void onRecvP2pTrackerMessage() = 0;

            std::string _channelId;
        };

        WUJI_API void P2P_createWujiP2p(IWujiP2pEventHandler *handler, const std::string &localId);
        WUJI_API void P2P_setChannel(IWujiP2pTracker *wujiTracker, const std::vector<std::string> &vecPeerIds);
        WUJI_API void P2P_onTimer();
        WUJI_API void P2P_sendToPeer(const std::string &channelId, const std::string &peerId, const std::string &message);
        WUJI_API void P2P_onRecvTrackerMsg(const std::string &channelId, const std::string &msg);

        //// WUJI_API void P2P_setChannel(IWujiP2pChannel *channel, const std::string &channelId, const std::string &localId, const std::vector<std::string> &vecPeerIds);

        //WUJI_API IWujiP2p *createWujiP2p(IWujiP2pChannel *channel, const std::string &videoId, const std::string &localId);

        //WUJI_API void leaveP2pRoom(const std::string &channelId);
        //WUJI_API void setP2pPeers(const std::string &channelId, const std::vector<std::string> &vecPeerIds);
        //WUJI_API void connectPeer(const std::string &channelId, const std::string &peerId);
        //WUJI_API void onRecvTrackerData(const std::string &channelId, const std::string &json);
    } //namespace base
} // namespace wuji

#endif      // WUJI_RTC_P2P_INTERFACE_H
