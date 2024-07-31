#pragma once
#include "../../pch.h"

class SocketAbstraction {
public:
    SocketAbstraction();
    ~SocketAbstraction();

    bool openSocket(const std::string& ip, unsigned short port);
    bool sendData(const std::string& data);
    std::string receiveData(size_t bufferSize = 1024);
    void closeSocket();

    std::string GetLocalIPAddress();
private:
    int sockfd;
    struct sockaddr_in servaddr;

#ifdef _WIN32
    WSADATA wsaData;
#endif
};