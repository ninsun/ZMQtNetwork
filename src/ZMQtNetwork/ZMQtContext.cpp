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

#include "ZMQtNetwork/ZMQtContext.h"

#include <QtCore/QDebug>

#include <zmq.hpp>

namespace ZMQtNetwork
{
    zmq::context_t *ZMQtContext::m_pContext = NULL;
    int ZMQtContext::m_iContextCount = 0;

    ZMQtContext::ZMQtContext(int io_threads)
    {
        if (!m_pContext && io_threads >= 0)
        {
            try
            {
                m_pContext = new zmq::context_t(io_threads);
            }
            catch (zmq::error_t &e)
            {
                qCritical() << "context create error [" << e.num() << "] :" << e.what();
                return;
            }
        }
        ++m_iContextCount;
    }

    ZMQtContext::~ZMQtContext()
    {
        --m_iContextCount;
        if (m_iContextCount == 0 && m_pContext)
        {
            delete m_pContext;
            m_pContext = NULL;
        }
    }
}
