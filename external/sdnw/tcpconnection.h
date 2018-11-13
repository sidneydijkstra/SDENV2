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

#include "tcpobject.h"

class TcpConnection : TcpObject{
public:
	TcpConnection(Socket* _socket);
	~TcpConnection();

	void start(std::function<void(std::string)> _receiveData);
	void sendData(std::string _message);
	void terminate();

private:
	std::function<void(std::string)> _OnReceiveData;

	void _listen();
};
