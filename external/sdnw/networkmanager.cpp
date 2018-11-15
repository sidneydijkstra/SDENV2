#include "networkmanager.h"

NetworkManager* NetworkManager::_instance = NULL;
NetworkManager::~NetworkManager() {
	if (_instance)
		delete this->_instance;
}

NetworkManager::NetworkManager() {
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 1), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
	}else {
		printf("WSAStartup succes\n");
	}

	this->_running = false;
}

void NetworkManager::update() {
	if(_running)
		_client->update();
}

void NetworkManager::handleData(std::string _message){
	OnReceiveData.run(_message);
}

NetworkManager* NetworkManager::getInstance() {
	if (!NetworkManager::_instance){
		NetworkManager::_instance = new NetworkManager();
	}
	return NetworkManager::_instance;
}

bool NetworkManager::init(IpAddress _ip, int _port){
	this->_running = true;

	_client = new TcpClient(_ip, _port);
	return _client->connectClient([this](std::string _message) {
		this->handleData(_message);
	});
}