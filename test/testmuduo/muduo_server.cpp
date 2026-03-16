/*
muduo网络库给用户提供了两个主要的类
TcpServer:用于编写服务器程序的
TcpClient:用于编写客户端程序的
*/
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
#include <string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;


class ChatServer 
{
public:
    ChatServer(EventLoop *loop,               // 事件循环
            const InetAddress &listenAddr, // IP+Port
               const string &nameArg)         // 服务器的名字
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        // 给服务器注册用户连接的创建和断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

        // 给服务器注册用户读写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置服务器端的线程数量 1个I/O线程  3个worker线程
        _server.setThreadNum(4);
    }

    // 开启事件循环
    void start()
    {
        _server.start();
    }

private:
    // 专门处理用户的连接创建和断开  epoll  listenfd  accept
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "state:online" << endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "state:offline" << endl;
            conn->shutdown();
        }
    } 
    // 专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn, //连接
                   Buffer *buffer,    // 缓冲区
                   Timestamp time) // 接收到数据的时间信息
    {
        string buf=buffer->retrieveAllAsString();
        cout<<"recv data:"<<buf<<" time:"<<time.toString()<<endl;
        conn->send(buf);
    }
    TcpServer _server;
    EventLoop *_loop;
};

int main()
{
    EventLoop loop;//epoll
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop,addr,"ChatServer");

    server.start();
    loop.loop();
 
    return 0;
}