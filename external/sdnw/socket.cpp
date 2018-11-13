#include "socket.h"

Socket::Socket(IpAddress _ip, int _port){
	_data = _ip.format();
	_data.sin_port = _port;
	_data.sin_family = AF_INET;

	_running = false;
}

Socket::Socket(SOCKET _s, sockaddr_in _d, bool _r){
	_socket = _s;
	_data = _d;
	_running = _r;
}

Socket::~Socket(){
	this->destroy();
}

void Socket::create(){
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == INVALID_SOCKET) {
		printf("Socket creation failed: %d\n", WSAGetLastError());
		return;
	}
	_running = true;
}

void Socket::destroy(){
	closesocket(_socket);
	_running = false;
}

SOCKET Socket::getSocket(){
	return _socket;
}

sockaddr_in Socket::getData(){
	return _data;
}

bool Socket::isRunning(){
	return _running;
}
