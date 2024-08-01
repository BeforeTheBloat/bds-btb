#pragma once
#include "../../pch.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <unistd.h>
#endif

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>


SocketAbstraction::SocketAbstraction() : sockfd(-1) {
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        Logger::Error("WSAStartup failed");
    }
#endif
}

SocketAbstraction::~SocketAbstraction() {
    closeSocket();
#ifdef _WIN32
    WSACleanup();
#endif
}

bool SocketAbstraction::openSocket(const std::string& ip, unsigned short port) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        Logger::Error("Error creating socket");
        return false;
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr);

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        Logger::Error("Error binding socket");
        closeSocket();
        return false;
    }

    return true;
}

bool SocketAbstraction::sendData(const std::string& data) {
    if (sockfd < 0) return false;
    int sentBytes = sendto(sockfd, data.c_str(), static_cast<int>(data.size()), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
    return sentBytes == static_cast<int>(data.size());
}

std::string SocketAbstraction::receiveData(size_t bufferSize) {
    if (sockfd < 0) {
        std::cerr << "Invalid socket descriptor" << std::endl;
        return "";
    }

    std::vector<char> buffer(bufferSize);
    int receivedBytes = recv(sockfd, buffer.data(), static_cast<int>(bufferSize) - 1, 0);

    if (receivedBytes < 0) {
#ifdef _WIN32
        int errorCode = WSAGetLastError();
        std::cerr << "Error receiving data: " << errorCode << std::endl;
#else
        std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
#endif
        return "";
    }

    if (receivedBytes == 0) {
        return "";
    }

    buffer[receivedBytes] = '\0';

    // Hex output
    std::ostringstream hexStream;
    hexStream << "Received data (hex): ";
    for (int i = 0; i < receivedBytes; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << (static_cast<int>(static_cast<unsigned char>(buffer[i]))) << " ";
    }
    std::cout << hexStream.str() << std::endl;

    return std::string(buffer.data());
}

void SocketAbstraction::closeSocket() {
    if (sockfd >= 0) {
#ifdef _WIN32
        closesocket(sockfd);
#else
        close(sockfd);
#endif
        sockfd = -1;
    }
}

std::string SocketAbstraction::GetLocalIPAddress() {
    std::string ipAddress = "127.0.0.1";

#ifdef _WIN32
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        struct hostent* host = gethostbyname(hostname);
        if (host && host->h_addr_list[0]) {
            ipAddress = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
        }
    }
#else
    struct ifaddrs* ifaddr = nullptr;
    if (getifaddrs(&ifaddr) == 0) {
        for (struct ifaddrs* ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
                struct sockaddr_in* sa = (struct sockaddr_in*)ifa->ifa_addr;
                ipAddress = inet_ntoa(sa->sin_addr);
                break;
            }
        }
        freeifaddrs(ifaddr);
    }
#endif

    return ipAddress;
}
