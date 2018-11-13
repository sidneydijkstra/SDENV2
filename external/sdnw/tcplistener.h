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

class TcpListener : TcpObject{
public:
	TcpListener(int _port);
	~TcpListener();

	bool bindListener(std::function<void(Socket*)> _newConnection, std::function<void(Socket*)> _lostConnection);

	void terminate();

private:
	// callbacks
	std::function<void(Socket*)> _OnNewConnection;
	std::function<void(Socket*)> _OnLostConnection;

	void _listen();
};
