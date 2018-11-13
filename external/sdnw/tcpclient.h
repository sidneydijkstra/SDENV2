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

class TcpClient : TcpObject {
public:
	TcpClient(IpAddress _ip, int _port);
	~TcpClient();

	bool connectClient(std::function<void(std::string)> _receiveData);
	void sendData(std::string _message);

	void terminate();

private:
	// callbacks
	std::function<void(std::string)> _OnReceiveData;

	void _listen();
};
