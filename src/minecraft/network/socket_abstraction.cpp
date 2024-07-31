#include "socket_abstraction.h"

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

    return true;
}

bool SocketAbstraction::sendData(const std::string& data) {
    if (sockfd < 0) return false;
    size_t sentBytes = sendto(sockfd, data.c_str(), data.size(), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
    return sentBytes == data.size();
}

std::string SocketAbstraction::receiveData(size_t bufferSize) {
    std::vector<char> buffer(bufferSize);
    size_t receivedBytes = recv(sockfd, buffer.data(), bufferSize, 0);

    if (receivedBytes > 0) {
        return std::string(buffer.data(), receivedBytes);
    }

    return "";
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
    #ifdef _WIN32
        char hostname[256];
        if (gethostname(hostname, sizeof(hostname)) == 0) {
            struct hostent* host = gethostbyname(hostname);
            if (host) {
                return inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
            }
        }
    #elif defined(__unix__) || defined(__unix)
        struct ifaddrs* ifaddr, * ifa;
        if (getifaddrs(&ifaddr) == 0) {
            for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
                if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
                    struct sockaddr_in* sa = (struct sockaddr_in*)ifa->ifa_addr;
                    return inet_ntoa(sa->sin_addr);
                }
            }
            freeifaddrs(ifaddr);
        }
    #endif
        return "127.0.0.1";
};