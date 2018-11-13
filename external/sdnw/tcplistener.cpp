#include "tcplistener.h"

TcpListener::TcpListener(int _port){
	_socket = new Socket(IpAddress("127.0.0.1"), _port);
	_socket->create();
}

TcpListener::~TcpListener(){
	this->terminate();
}

bool TcpListener::bindListener(std::function<void(Socket*)> _newConnection, std::function<void(Socket*)> _lostConnection){
	if (bind(_socket->getSocket(), (SOCKADDR*)(&_socket->getData()), sizeof(_socket->getData())) == SOCKET_ERROR) {
		printf("Binding failed\n");
		return false;
	}

	if (listen(_socket->getSocket(), 3) == SOCKET_ERROR) {
		printf("Listening failed\n");
		return false;
	}

	_OnNewConnection = _newConnection;
	_OnLostConnection = _lostConnection;

	_listenThread = std::thread(&TcpListener::_listen, this);
	
	return true;
}

void TcpListener::terminate(){
	//_listenThread.join(); // TODO: stop thread from running (call std::terminate in thread)
	// TODO: shutdown(_clientSocket, SD_SEND) are you closing connection on right way?
	delete _socket;
}

void TcpListener::_listen() {
	while (true) {
		sockaddr_in data;
		int size = sizeof(struct sockaddr_in);
		SOCKET socket = accept(_socket->getSocket(), (struct sockaddr *)&data, &size);
		if (socket == INVALID_SOCKET) {
			printf("accept failed with error code : %d", WSAGetLastError());
		}

		this->_OnNewConnection(new Socket(socket, data, false));
	}
}
