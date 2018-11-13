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

class GlobalFunctions {
public:
	static std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> result = std::vector<std::string>();
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			result.push_back(item);
		}
		return result;
	}
};

struct IpAddress {
	std::string addres;

	IpAddress(std::string _addres) {
		addres = _addres;
	}

	sockaddr_in format() {
		sockaddr_in ip = sockaddr_in();
		std::vector<std::string> addrs = GlobalFunctions::split(addres, '.');
		ip.sin_addr.S_un.S_un_b.s_b1 = std::stoi(addrs[0]);
		ip.sin_addr.S_un.S_un_b.s_b2 = std::stoi(addrs[1]);
		ip.sin_addr.S_un.S_un_b.s_b3 = std::stoi(addrs[2]);
		ip.sin_addr.S_un.S_un_b.s_b4 = std::stoi(addrs[3]);
		return ip;
	}
};

class Socket
{
public:
	Socket(IpAddress _ip, int _port);
	Socket(SOCKET _s, sockaddr_in _d, bool _r = false);
	~Socket();

	void create();
	void destroy();

	SOCKET getSocket();
	sockaddr_in getData();

	bool isRunning();

private:
	SOCKET _socket;
	sockaddr_in _data;

	bool _running;
};