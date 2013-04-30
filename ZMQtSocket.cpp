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

#include "ZMQtSocket.h"
#include "ZMQtContext.h"
#include "ZMQtMessage.h"
#include "ZMQtType.h"

#include <QtCore/QDebug>

#include <zmq.hpp>

namespace ZMQtNetwork
{
    ZMQtSocket::ZMQtSocket(const ZMQtContext &contex, int type)
        : m_pSocket(NULL)
    {
        open(contex, type);
    }

    ZMQtSocket::ZMQtSocket()
        : m_pSocket(NULL)
    {

    }

    ZMQtSocket::~ZMQtSocket()
    {
        close();
    }

    int ZMQtSocket::open( const ZMQtContext &contex, int type )
    {
        close();
        if (contex.getContext())
        {
            try
            {
                qDebug() << "open with type:" << ZMQtNetwork::getTypeName(type);
                m_pSocket = new zmq::socket_t(*contex.getContext(), type);

#if (ZMQ_VERSION_MAJOR == 3)
                int _hwm=1000;
                m_pSocket->setsockopt(ZMQ_SNDHWM, &_hwm, sizeof(_hwm));
                m_pSocket->setsockopt(ZMQ_RCVHWM, &_hwm, sizeof(_hwm));
#else
                quint64 _hwm=1000;
                m_pSocket->setsockopt(ZMQ_HWM, &_hwm, sizeof(_hwm));
#endif
            }
            catch (zmq::error_t &e)
            {
                m_pSocket = NULL;
                qCritical() << "socket open error [" << e.num() << "] :" << e.what();
                return -2;
            }
        }
        else
        {
            qCritical() << "context not create!";
            return -1;
        }

        return 0;
    }

    void ZMQtSocket::close()
    {
        if (m_pSocket)
        {
            delete m_pSocket;
            m_pSocket = NULL;
        }
    }

    int ZMQtSocket::bind( const QString &endpoint )
    {
        if (m_pSocket)
        {
            try
            {
                m_pSocket->bind(endpoint.toLocal8Bit().data());
            }
            catch (zmq::error_t &e)
            {
                qCritical() << "socket bind error [" << e.num() << "] :" << e.what();
                qCritical() << "with setting:" << endpoint;
                return -2;
            }

            qDebug() << "socket bind success!";
            qDebug() << "with setting:" << endpoint;
            return 0;
        }
        else
        {
            qCritical() << "socket not open!";
            return -1;
        }
    }

    int ZMQtSocket::connect( const QString &endpoint )
    {
        if (m_pSocket)
        {
            try
            {
                m_pSocket->connect(endpoint.toLocal8Bit().data());
            }
            catch (zmq::error_t &e)
            {
                qCritical() << "socket connect error [" << e.num() << "] :" << e.what();
                qCritical() << "with setting:" << endpoint;
                return -2;
            }

            qDebug() << "socket connect success!";
            qDebug() << "with setting:" << endpoint;
            return 0;
        }
        else
        {
            qCritical() << "socket not open!";
            return -1;
        }
    }

    int ZMQtSocket::setsockopt( int optName, void *optValue, size_t optLength )
    {
        if (m_pSocket)
        {
            try
            {
                m_pSocket->setsockopt(optName, optValue, optLength);
            }
            catch (zmq::error_t &e)
            {
                qWarning() << "setsockopt error [" << e.num() << "] :" << e.what();
                qWarning() << "with optName:" << ZMQtNetwork::getSockoptName(optName);
                return -2;
            }

            return 0;
        }
        else
        {
            qWarning() << "setsockopt error : socket is null";
            qWarning() << "with optName:" << ZMQtNetwork::getSockoptName(optName);
            return -1;
        }
    }

    int ZMQtSocket::getsockopt( int optName, void *optValue, size_t *optLength )
    {
        if (m_pSocket)
        {
            try
            {
                m_pSocket->getsockopt(optName, optValue, optLength);
            }
            catch (zmq::error_t &e)
            {
                qWarning() << "getsockopt error [" << e.num() << "] :" << e.what();
                qWarning() << "with optName:" << ZMQtNetwork::getSockoptName(optName);
                return -2;
            }

            return 0;
        }
        else
        {
            qWarning() << "getsockopt error : socket is null";
            qWarning() << "with optName:" << ZMQtNetwork::getSockoptName(optName);
            return -1;
        }
    }

    int ZMQtSocket::sendmsg( ZMQtMessage *msg, int flags )
    {
        if(msg)
        {
            return msg->send(this, flags);
        }
        else
        {
            qCritical() << "msssage is null";
            return -1;
        }
    }

    int ZMQtSocket::recvmsg( ZMQtMessage *msg, int flags )
    {
        if(msg)
        {
            return msg->recv(this, flags);
        }
        else
        {
            qCritical() << "msssage is null";
            return -1;
        }
    }

    int ZMQtSocket::send(const void *buf, size_t len, int flags)
    {
        if(m_pSocket)
        {
            return m_pSocket->send(buf, len,flags);
        }
        else
        {
            qCritical() << "socket is null";
            return -1;
        }
    }

    int ZMQtSocket::recv(void *buf, size_t len, int flags)
    {
        if(m_pSocket)
        {
            return m_pSocket->recv(buf, len,flags);
        }
        else
        {
            qCritical() << "socket is null";
            return -1;
        }
    }

}
