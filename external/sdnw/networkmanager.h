#pragma once

#include "tcpclient.h"
#include "tcplistener.h"
#include "tcpconnection.h"
#include "networkaction.h"

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

class NetworkManager{ // TODO: build group connection logic in difrent class or in TcpListener
	public:

		static NetworkManager* getInstance();
		NetworkActionT1<std::string> OnReceiveData;

		~NetworkManager();

		bool init(IpAddress _ip, int _port);

		void sendData(std::string _message) {
			_client->sendData(_message);
		}

	private:
		static NetworkManager* NetworkManager::_instance;
		NetworkManager();
		
		void handleData(std::string _message);

		bool _running;
		TcpClient* _client;
};