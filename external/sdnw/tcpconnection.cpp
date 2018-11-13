#include "tcpconnection.h"

TcpConnection::TcpConnection(Socket * _socket){
	this->_socket = _socket;
}

TcpConnection::~TcpConnection(){
	this->terminate();
}

void TcpConnection::start(std::function<void(std::string)> _receiveData){
	_OnReceiveData = _receiveData;
	_listenThread = std::thread(&TcpConnection::_listen, this);
}

void TcpConnection::sendData(std::string _message){
	const char* buffer = _message.c_str();
	if (send(_socket->getSocket(), buffer, (int)strlen(buffer), 0) == SOCKET_ERROR) {
		// TODO: add on client disconect callback
		std::cout << "Could not send message" << std::endl;
	}
}

void TcpConnection::terminate(){
	delete _socket;
}

void TcpConnection::_listen(){
	int result = 0;
	char buffer[1028];
	while (true) {
		result = recv(_socket->getSocket(), buffer, 1028, 0);

		if (result > 0) {
			std::string _message = "";
			for (int i = 0; i < result; i++) {
				_message += buffer[i];
			}
			_OnReceiveData(_message); // <-- callback
		}
		else {
			printf("TERMINATING THREAD! recv failed: %d\n", WSAGetLastError());
			_socket->destroy();
			break;
		}
	}
}
