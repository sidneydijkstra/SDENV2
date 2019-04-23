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

	int getNetworkID() { return _networkID; };
	bool isRunning() { return _running; };

private:
	static NetworkHandler* _instance;
	NetworkHandler();

	struct PackageListener {
		PackageListener(std::string _id, std::function<void(Package)> _callback) { id = _id; callback = _callback; };
		std::string id;
		std::function<void(Package)> callback;
	};

	bool _running;
	int _networkID;
	std::vector<PackageListener> _listeners;

	void _listen(std::string _data);

};

