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

#ifndef ZMQtNetwork_ZMQtContext_h__
#define ZMQtNetwork_ZMQtContext_h__

#include "zmqtnetwork_global.h"

namespace zmq
{
    class context_t;
}

namespace ZMQtNetwork
{
    //! 作为单例管理器, 此类是线程安全的.
    class ZMQTNETWORKSHARED_EXPORT ZMQtContext
    {
    public:
        ZMQtContext(int io_threads=1);
        ~ZMQtContext();

    public:
        //! 内部用公共函数, 获取zmq上下文(contex)
        zmq::context_t* getContext() const { return m_pContext; }

    private:
        static zmq::context_t* m_pContext;
        static int m_iContextCount;

    };
}
#endif // ZMQtNetwork_ZMQtContext_h__
