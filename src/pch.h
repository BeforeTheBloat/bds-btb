#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <thread>

#ifdef _WIN32

// Networking
#include <winsock2.h>
#include <ws2tcpip.h>

#endif

#ifdef linux

//Networking
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#endif

#include "logger/logger.h"
#include "event/event.h"
#include "minecraft/network/socket_abstraction.h"