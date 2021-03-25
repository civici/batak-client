#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>

#undef MOUSE_MOVED

SOCKET connection;

SOCKET openconn();
