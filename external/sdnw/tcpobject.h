#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>

#include <winsock2.h>
#include <windows.h>
#include <sdkddkver.h>
#include <conio.h>
#include <stdio.h>

#include <thread>

#include "socket.h"

class TcpObject{
public:
	TcpObject();
	~TcpObject();

	void terminate();

protected:
	Socket* _socket;
	std::thread _listenThread;

	void _listen();
};