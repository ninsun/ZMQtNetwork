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

#ifndef ZMQtNetwork_ZMQtSocket_h__
#define ZMQtNetwork_ZMQtSocket_h__

#include "zmqtnetwork_global.h"

class QString;

namespace zmq
{
    class socket_t;
}

namespace ZMQtNetwork
{
    class ZMQtMessage;
    class ZMQtContext;

    //! 此类不是线程安全的, 请不要在不同线程中同时调用此类的任何方法.
    //! 如需在不同线程中处理请自行处理线程同步
    class ZMQTNETWORKSHARED_EXPORT ZMQtSocket
    {

    public:
        //! 创建一个新的socket, 需要手动打开
        ZMQtSocket();
        //! 使用相应的上下文和类型创建一个socket，并自动打开
        ZMQtSocket(const ZMQtContext &contex, int type);
        ~ZMQtSocket();

    public:
        //! 内部用公共函数, 获取zmq的socket
        zmq::socket_t* getSocket() { return m_pSocket; }
        //! 打开这个socket, 打开之前会先尝试关闭
        int open(const ZMQtContext &contex, int type);
        //! 关闭这个socket
        void close();
        //! 绑定至某个端点, 一般是服务端使用
        int bind(const QString &endpoint);
        //! 连接至某个端点, 一般是客户端使用
        int connect(const QString &endpoint);
        //! 设置socket属性
        int setsockopt(int optName, void *optValue, size_t optLength);
        //! 获取socket属性
        int getsockopt(int optName, void *optValue, size_t *optLength);

    public:
        //! 发送ZMQtMessage中的全部消息
        //! 返回0表示成功, 返回1表示发送队列已满, 负值表示失败
        int sendmsg(const ZMQtMessage &msg, int flags=0);
        //! 接受消息，逐条放置在ZMQtMessage中
        //! 返回0表示成功, 返回1表示暂无消息, 负值表示失败
        int recvmsg(ZMQtMessage *msg, int flags=0);

        //! 直接发送缓冲区中的数据
        //! 返回真正发送的字节数量
        int send(const void *buf, size_t len, int flags = 0);
        //! 向缓冲区中读取数据
        //! 返回真正接受的字节数量
        int recv(void *buf, size_t len, int flags = 0);

    private:
        zmq::socket_t *m_pSocket;
    };

}
#endif // ZMQtNetwork_ZMQtSocket_h__
