#include "package.h"

Package::Package(std::string _name, int _networkID) {
	_packageName = _name;
	_networkID = _networkID;
	_data = std::map<int, std::map<std::string, std::string>>();
}

Package::Package(std::string _name) { // TODO: get network id from NetworkManager
	_packageName = _name;
	_networkID = 0;
	_data = std::map<int, std::map<std::string, std::string>>();
}

Package::~Package() {
	_data.clear();
}

std::string Package::getName() {
	return _packageName;
}

int Package::getNetworkId() {
	return _networkID;
}

Package Package::format(std::string _packageData) {
	std::vector<std::string> _packaga = GlobalFunctions::split(_packageData, ',');

	Package pack(_packaga[0], std::stoi(_packaga[1]));

	for (size_t i = 2; i < _packaga.size(); i += 3) {
		int type = std::stoi(_packaga[i]);
		std::string id = _packaga[i + 1];
		std::string value = _packaga[i + 2];

		pack.addUnkownData(type, id, value);
	}

	return pack;
}

std::string Package::format() {
	if (_data.empty())
		return "";

	std::string result = _packageName + "," + std::to_string(_networkID);

	std::for_each(_data.begin(), _data.end(), [&](const std::pair<int, std::map<std::string, std::string>>& list) {
		std::for_each(list.second.begin(), list.second.end(), [&](const std::pair<std::string, std::string>& data) {
			result += "," + std::to_string(list.first) + "," + data.first + "," + data.second;
		});
	});

	return result;
}


void Package::set(std::string _id, int _value) {
	if (this->contains(0, _id)) {
		_data.find(0)->second.find(_id)->second = std::to_string(_value);
	}
	else {
		std::map<std::string, std::string> _temp = _data.find(1) != _data.end() ? _data.find(1)->second : std::map<std::string, std::string>();
		_temp.insert(std::pair<std::string, std::string>(_id, std::to_string(_value)));
		if (_data.find(0) == _data.end()) {
			_data.insert(std::pair<int, std::map<std::string, std::string>>(0, _temp));
		}
		else {
			_data.find(0)->second = _temp;
		}
	}
}
int Package::getInt(std::string _id) {
	if (this->contains(0, _id)) {
		return std::stoi(_data.find(0)->second.find(_id)->second);
	}
	else {
		return NULL;
	}
}

void Package::set(std::string _id, std::string _value) {
	if (this->contains(1, _id)) {
		_data.find(1)->second.find(_id)->second = _value;
	}
	else {
		std::map<std::string, std::string> _temp = _data.find(1) != _data.end() ? _data.find(1)->second : std::map<std::string, std::string>();
		_temp.insert(std::pair<std::string, std::string>(_id, _value));
		if (_data.find(1) == _data.end()) {
			_data.insert(std::pair<int, std::map<std::string, std::string>>(1, _temp));
		}
		else {
			_data.find(1)->second = _temp;
		}
	}
}
std::string Package::getString(std::string _id) {
	if (this->contains(1, _id)) {
		return _data.find(1)->second.find(_id)->second;
	}
	else {
		return NULL;
	}
}

void Package::set(std::string _id, float _value) {
	if (this->contains(2, _id)) {
		_data.find(2)->second.find(_id)->second = std::to_string(_value);
	}
	else {
		std::map<std::string, std::string> _temp = _data.find(2) != _data.end() ? _data.find(2)->second : std::map<std::string, std::string>();
		_temp.insert(std::pair<std::string, std::string>(_id, std::to_string(_value)));
		if (_data.find(2) == _data.end()) {
			_data.insert(std::pair<int, std::map<std::string, std::string>>(2, _temp));
		}
		else {
			_data.find(2)->second = _temp;
		}
	}
}
float Package::getFloat(std::string _id) {
	if (this->contains(2, _id)) {
		return strtof(_data.find(2)->second.find(_id)->second.c_str(), 0);
	}
	else {
		return NULL;
	}
}

void Package::set(std::string _id, bool _value) {
	if (this->contains(3, _id)) {
		_data.find(3)->second.find(_id)->second = _value ? "1" : "0";
	}
	else {
		std::map<std::string, std::string> _temp = _data.find(3) != _data.end() ? _data.find(3)->second : std::map<std::string, std::string>();
		_temp.insert(std::pair<std::string, std::string>(_id, _value ? "1" : "0"));
		if (_data.find(3) == _data.end()) {
			_data.insert(std::pair<int, std::map<std::string, std::string>>(3, _temp));
		}
		else {
			_data.find(3)->second = _temp;
		}
	}
}
bool Package::getBool(std::string _id) {
	if (this->contains(3, _id)) {
		return _data.find(3)->second.find(_id)->second == "1" ? true : false;
	}
	else {
		return NULL;
	}
}

void Package::addUnkownData(int _type, std::string _id, std::string _value) {
	if (_type == 0) { // int
		this->set(_id, std::stoi(_value));
	}
	else if (_type == 1) { // string
		this->set(_id, std::string(_value));
	}
	else if (_type == 2) { // float
		this->set(_id, strtof(_value.c_str(), 0));
	}
	else if (_type == 3) { // bool
		this->set(_id, _value == "1" ? true : false);
	}
}

bool Package::contains(int _type, std::string _id) {
	return _data.find(_type) != _data.end() && _data.find(_type)->second.find(_id) != _data.find(_type)->second.end();
}
