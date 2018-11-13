#include "networkhandler.h"

NetworkHandler* NetworkHandler::_instance = NULL;
NetworkHandler::NetworkHandler(){
	NetworkManager::getInstance()->OnReceiveData += [this](std::string _data) { 
		this->_listen(_data); 
	};
}

NetworkHandler::~NetworkHandler(){
}

NetworkHandler * NetworkHandler::getInstance(){
	if (_instance == NULL)
		_instance = new NetworkHandler();
	return _instance;
}

void NetworkHandler::listen(std::string _id, std::function<void(Package)> _callback){
	_listeners.push_back(PackageListener(_id, _callback));
}

void NetworkHandler::send(Package _pack){ // TODO: add a try when formating package
	NetworkManager::getInstance()->sendData(_pack.format());
}

void NetworkHandler::_listen(std::string _data){
	Package pack = Package::format(_data);
	for (size_t i = 0; i < _listeners.size(); i++){
		PackageListener p = _listeners[i];
		if (pack.getName() == p.id) {
			p.callback(pack);
		}
	}
}
