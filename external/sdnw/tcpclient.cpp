#include "tcpclient.h"

TcpClient::TcpClient(IpAddress _ip, int _port){
	// create socket
	_socket = new Socket(_ip, _port);
	_socket->create();
}

TcpClient::~TcpClient(){
	this->terminate();
}

bool TcpClient::connectClient(std::function<void(std::string)> _receiveData){
	if (connect(_socket->getSocket(), (struct sockaddr *) &_socket->getData(), sizeof(_socket->getData())) < 0) {
		printf("Looking for connection failed: %d\n", WSAGetLastError());
		return false;
	}

	_OnReceiveData = _receiveData;

	_listenThread = std::thread(&TcpClient::_listen, this);

	return true;
}

void TcpClient::sendData(std::string _message){
	const char* buffer = _message.c_str();
	if (send(_socket->getSocket(), buffer, (int)strlen(buffer), 0) == SOCKET_ERROR) {
		// TODO: add on client disconect callback
		std::cout << "Could not send message" << std::endl;
	}
}

void TcpClient::terminate(){
	//_listenThread.join(); // TODO: stop thread from running (call std::terminate in thread)
	// TODO: shutdown(_clientSocket, SD_SEND) are you closing connection on right way?
	delete _socket;
}

void TcpClient::_listen(){
	int result = 0;
	char buffer[1028];
	while (true) {
		result = recv(_socket->getSocket(), buffer, 1028, 0);

		if (result > 0) {
			std::string _message = "";
			for (int i = 0; i < result; i++) {
				_message += buffer[i];
			}
			_OnReceiveData(_message);
		}
		else {
			printf("TERMINATING THREAD! recv failed: %d\n", WSAGetLastError());
			_socket->destroy();
			break;
		}
	}
}