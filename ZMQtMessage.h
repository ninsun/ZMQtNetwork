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

#ifndef ZMQtNetwork_ZMQtMessage_h__
#define ZMQtNetwork_ZMQtMessage_h__

#include <QtCore/QList>
#include <QtCore/QByteArray>

#include "zmqtnetwork_global.h"

namespace ZMQtNetwork
{
    class ZMQtSocket;

    //! 此类不是线程安全的, 请不要在不同线程中同时调用此类的任何方法.
    //! 如需在不同线程中处理请自行处理线程同步
    class ZMQTNETWORKSHARED_EXPORT ZMQtMessage
    {
    public:
        ZMQtMessage();
        ~ZMQtMessage();

    public:
        //! 从消息队列头部插入数据
        void prepend(const QByteArray &data) { m_messageList.prepend(data); }
        //! 从消息队列尾部插入数据
        void append(const QByteArray &data) { m_messageList.append(data); }
        //! 将数据插入到index位置, 原位置数据以及后续数据将依次后移
        void insert(int index, const QByteArray &data) { m_messageList.insert(index, data); }
        //! 清空消息队列
        void clear() { m_messageList.clear(); }

    public:
        //! 获取消息队列中index位置的数据
        QByteArray message(int index) { return m_messageList.value(index); }
        //! 获取消息队列中数据的个数
        int count() { return m_messageList.size(); }
        //! 获取整个消息列表
        const QList<QByteArray> & messageList() const { return m_messageList; }

    private:
        QList<QByteArray> m_messageList;
    };
}
#endif // ZMQtNetwork_ZMQtMessage_h__
