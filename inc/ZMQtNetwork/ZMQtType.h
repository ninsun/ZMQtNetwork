/**
 *
 * Copyright (C) Ninsun, All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ZMQtNetwork_ZMQtType_h__
#define ZMQtNetwork_ZMQtType_h__

#include <zmq.hpp>

#ifndef ZMQ_HWM
#define ZMQ_HWM -1000
#endif
#ifndef ZMQ_SWAP
#define ZMQ_SWAP -1001
#endif
#ifndef ZMQ_MCAST_LOOP
#define ZMQ_MCAST_LOOP -1002
#endif
#ifndef ZMQ_RECOVERY_IVL_MSEC
#define ZMQ_RECOVERY_IVL_MSEC -1003
#endif

namespace ZMQtNetwork
{
    char* getTypeName(int type)
    {
        switch(type)
        {
        case ZMQ_PAIR:
            return "ZMQ_PAIR";
        case ZMQ_PUB:
            return "ZMQ_PUB";
        case ZMQ_SUB:
            return "ZMQ_SUB";
        case ZMQ_REQ:
            return "ZMQ_REQ";
        case ZMQ_REP:
            return "ZMQ_REP";
        case ZMQ_DEALER:
            return "ZMQ_DEALER";
        case ZMQ_ROUTER:
            return "ZMQ_ROUTER";
        case ZMQ_PULL:
            return "ZMQ_PULL";
        case ZMQ_PUSH:
            return "ZMQ_PUSH";
        case ZMQ_XPUB:
            return "ZMQ_XPUB";
        case ZMQ_XSUB:
            return "ZMQ_XSUB";
        default:
            return "unknow";
        }
    }

    char* getSockoptName(int opt)
    {
        switch(opt)
        {
        case ZMQ_HWM:
            return "ZMQ_HWM";
        case ZMQ_SWAP:
            return "ZMQ_SWAP";
        case ZMQ_AFFINITY:
            return "ZMQ_AFFINITY";
        case ZMQ_IDENTITY:
            return "ZMQ_IDENTITY";
        case ZMQ_SUBSCRIBE:
            return "ZMQ_SUBSCRIBE";
        case ZMQ_RATE:
            return "ZMQ_RATE";
        case ZMQ_RECOVERY_IVL:
            return "ZMQ_RECOVERY_IVL";
        case ZMQ_MCAST_LOOP:
            return "ZMQ_MCAST_LOOP";
        case ZMQ_SNDBUF:
            return "ZMQ_SNDBUF";
        case ZMQ_RCVBUF:
            return "ZMQ_RCVBUF";
        case ZMQ_RCVMORE:
            return "ZMQ_RCVMORE";
        case ZMQ_EVENTS:
            return "ZMQ_EVENTS";
        case ZMQ_TYPE:
            return "ZMQ_TYPE";
        case ZMQ_LINGER:
            return "ZMQ_LINGER";
        case ZMQ_RECONNECT_IVL:
            return "ZMQ_RECONNECT_IVL";
        case ZMQ_BACKLOG:
            return "ZMQ_BACKLOG";
        case ZMQ_RECOVERY_IVL_MSEC:
            return "ZMQ_RECOVERY_IVL_MSEC";
        case ZMQ_RECONNECT_IVL_MAX:
            return "ZMQ_RECONNECT_IVL_MAX";
        default:
            return "unknow";
        }
    }
}

#endif // ZMQtNetwork_ZMQtType_h__
