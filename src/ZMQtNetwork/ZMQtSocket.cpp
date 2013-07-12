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

#include "ZMQtNetwork/ZMQtSocket.h"
#include "ZMQtNetwork/ZMQtContext.h"
#include "ZMQtNetwork/ZMQtMessage.h"
#include "ZMQtNetwork/ZMQtType.h"

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

    int ZMQtSocket::sendmsg(const ZMQtMessage &msg)
    {
        if (m_pSocket)
        {
            zmq::message_t _msg;
            bool _success = false;
            QByteArray _data;
            QListIterator<QByteArray> _messageIt(msg.messageList());
            try
            {
                while(_messageIt.hasNext())
                {
                    _data = _messageIt.next();
                    _msg.rebuild(_data.size());
                    memcpy(_msg.data(), _data.data(), _data.size());
                    if (_messageIt.hasNext())
                    {
                        _success = m_pSocket->send(_msg, ZMQ_SNDMORE);
                    }
                    else
                    {
                        _success = m_pSocket->send(_msg, ZMQ_NOBLOCK);
                    }

                    if (!_success)
                    {
                        // 暂时无法发送(发送队列已经满了:发送速率过快或者没有连接到端点)
                        return 1;
                    }
                }
            }
            catch (zmq::error_t &e)
            {
                // 发送数据时出错, 返回-2
                qCritical() << "message send error [" << e.num() << "] :" << e.what();
                return -2;
            }

            // 全部数据发送完毕
            return 0;
        }
        else
        {
            qWarning() << "socket not open!";
            return -1;
        }
    }

    int ZMQtSocket::recvmsg( ZMQtMessage *msg)
    {
        if (m_pSocket)
        {
            msg->clear();
            QByteArray _data;
            zmq::message_t _msg;
            bool _success = false;
            int _more = 0;
            quint64 _more64 = 0;
            size_t _more_size = sizeof(_more);
            size_t _more64_size = sizeof(_more64);
            try
            {
                do
                {
                    _data.clear();
                    _msg.rebuild();
                    _success = m_pSocket->recv(&_msg, ZMQ_NOBLOCK);
                    if (_success)
                    {
                        // 收到数据, 记录这条数据
                        msg->append(QByteArray((const char *)_msg.data(), _msg.size()));
                        // 获取是否还有数据需要接收
#if (ZMQ_VERSION_MAJOR == 3)
                        m_pSocket->getsockopt(ZMQ_RCVMORE, &_more, &_more_size);
#else
                        m_pSocket->getsockopt(ZMQ_RCVMORE, &_more64, &_more64_size);
                        _more = static_cast<int>(_more64);
#endif
                    }
                    else
                    {
                        // 暂时没有数据, 返回1
                        return 1;
                    }
                } while(_more);
            }
            catch (zmq::error_t &e)
            {
                // 接收数据出错, 返回-2
                qCritical() << "message receive error [" << e.num() << "] :" << e.what();
                return -2;
            }

            // 数据接收完毕, 返回0
            return 0;
        }
        else
        {
            qWarning() << "socket not open!";
            return -1;
        }
    }

    int ZMQtSocket::send(const void *buf, size_t len, int flags)
    {
        if(m_pSocket)
        {
            return m_pSocket->send(buf, len, flags);
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
            return m_pSocket->recv(buf, len, flags);
        }
        else
        {
            qCritical() << "socket is null";
            return -1;
        }
    }

}
