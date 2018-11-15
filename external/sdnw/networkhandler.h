#pragma once

#include "networkmanager.h"
#include "package.h"

class NetworkHandler
{
public:
	~NetworkHandler();

	static NetworkHandler* getInstance();

	void listen(std::string _id, std::function<void(Package)> _callback);
	void send(Package _pack);

	bool isRunning() { return NetworkManager::getInstance()->isRunning(); };

private:
	static NetworkHandler* _instance;
	NetworkHandler();

	struct PackageListener {
		PackageListener(std::string _id, std::function<void(Package)> _callback) { id = _id; callback = _callback; };
		std::string id;
		std::function<void(Package)> callback;
	};

	std::vector<PackageListener> _listeners;

	void _listen(std::string _data);

};

