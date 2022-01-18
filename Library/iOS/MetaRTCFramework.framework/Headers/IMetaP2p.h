//
//  MetaRtcEngine SDK
//
//  Copyright (c) 2019 Meta.io. All rights reserved.
//

/**
 @defgroup createMetaRtcEngine Create an MetaRtcEngine
 */

#ifndef META_RTC_P2P_INTERFACE_H
#define META_RTC_P2P_INTERFACE_H

#include <string>
#include <vector>
#include "MetaBase.h"

namespace meta {
    namespace base {

        class IMetaP2pEventHandler {
        public:
            // virtual void onTrackerUpdated() = 0;
            virtual void onPeerConnected(const std::string &peerId) = 0;
            virtual void onPeerClosed(const std::string &peerId) = 0;
            virtual void onPeerMessage(const std::string &message) = 0;
        };

        //class IMetaP2p {
        //protected:
        //    virtual ~IMetaP2p() {}

        //public:
        //    // META_CPP_API static void release();

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

        //class IMetaP2pChannel {
        //public:
        //    IMetaP2pChannel() { _p2p = NULL; }

        //    virtual void onPeerConnected(const std::string &peerId) = 0;
        //    virtual void onPeerClosed(const std::string &peerId) = 0;
        //    virtual void onPeerMessage(const std::string &message) = 0;

        //    IMetaP2p *_p2p;
        //    std::string _channelId;
        //};

        class IMetaP2pTracker {
        public:
            virtual void sendP2pTrackerMessage(const std::string &remoteId, const std::string &message) = 0;
            //virtual void onRecvP2pTrackerMessage() = 0;

            std::string _channelId;
        };

        META_API void P2P_createMetaP2p(IMetaP2pEventHandler *handler, const std::string &localId);
        META_API void P2P_setChannel(IMetaP2pTracker *metaTracker, const std::vector<std::string> &vecPeerIds);
        META_API void P2P_onTimer();
        META_API void P2P_sendToPeer(const std::string &channelId, const std::string &peerId, const std::string &message);
        META_API void P2P_onRecvTrackerMsg(const std::string &channelId, const std::string &msg);

        //// META_API void P2P_setChannel(IMetaP2pChannel *channel, const std::string &channelId, const std::string &localId, const std::vector<std::string> &vecPeerIds);

        //META_API IMetaP2p *createMetaP2p(IMetaP2pChannel *channel, const std::string &videoId, const std::string &localId);

        //META_API void leaveP2pRoom(const std::string &channelId);
        //META_API void setP2pPeers(const std::string &channelId, const std::vector<std::string> &vecPeerIds);
        //META_API void connectPeer(const std::string &channelId, const std::string &peerId);
        //META_API void onRecvTrackerData(const std::string &channelId, const std::string &json);
    } //namespace base
} // namespace meta

#endif      // META_RTC_P2P_INTERFACE_H
