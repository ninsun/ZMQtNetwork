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

#include "ZMQtMessage.h"
#include "ZMQtSocket.h"

#include <QtCore/QDebug>

#include <zmq.hpp>

namespace ZMQtNetwork
{
    ZMQtMessage::ZMQtMessage()
    {

    }

    ZMQtMessage::~ZMQtMessage()
    {

    }

    int ZMQtMessage::send( ZMQtSocket *socket, int flags )
    {
        if (socket && socket->getSocket())
        {
            zmq::message_t _msg;
            bool _success = false;
            QByteArray _data;
            QListIterator<QByteArray> _messageIt(m_messageList);
            try
            {
                while(_messageIt.hasNext())
                {
                    _data = _messageIt.next();
                    _msg.rebuild(_data.size());
                    memcpy(_msg.data(), _data.data(), _data.size());
                    if (_messageIt.hasNext())
                    {
                        _success = socket->getSocket()->send(_msg, ZMQ_SNDMORE);
                    }
                    else
                    {
                        _success = socket->getSocket()->send(_msg, ZMQ_NOBLOCK);
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

    int ZMQtMessage::recv( ZMQtSocket *socket, int flags )
    {
        if (socket && socket->getSocket())
        {
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
                    _success = socket->getSocket()->recv(&_msg, ZMQ_NOBLOCK);
                    if (_success)
                    {
                        // 收到数据, 记录这条数据
                        m_messageList << QByteArray((const char *)_msg.data(), _msg.size());
                        // 获取是否还有数据需要接收
#if (ZMQ_VERSION_MAJOR == 3)
                        socket->getSocket()->getsockopt(ZMQ_RCVMORE, &_more, &_more_size);
#else
                        socket->getSocket()->getsockopt(ZMQ_RCVMORE, &_more64, &_more64_size);
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

}
