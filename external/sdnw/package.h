#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map> 
#include <algorithm>
#include <iterator>

#include "socket.h"

/*
					-== NETWORK PACKAGE ==-

	- supported types: int, string, float, bool
	- int:0 / string:1 / float:2 / bool:3
	- if other type is needed safe in string and self build!

	- code to test the package get, set and format logic

	// package test 1
	Package p = Package("my_package");
	p.set("level", 10);
	p.set("name", std::string("sidney"));
	p.set("level_bar", 12.45f);
	p.set("isAlive", false);

	int a = p.getInt("level");
	std::string d = p.getString("name");
	float c = p.getFloat("level_bar");
	bool b = p.getBool("isAlive");

	// package test 2
	p = Package::format("INIT,-1,0,level,16,1,name,henk,2,level_bar,16.18,3,isAlive,1");

	int i = p.getInt("level");
	std::string l = p.getString("name");
	float o = p.getFloat("level_bar");
	bool f = p.getBool("isAlive");

	// package test 3
	std::string data = p.format();

*/

static class Package{
public:
	Package(std::string _name, int _networkID);
	Package(std::string _name);
	~Package();

	std::string getName();
	int getNetworkId();

	static Package format(std::string _packageData);
	std::string format();

	// int : 0
	void set(std::string _id, int _value);
	int getInt(std::string _id);
	// string : 1
	void set(std::string _id, std::string _value);
	std::string getString(std::string _id);
	// float : 2
	void set(std::string _id, float _value);
	float getFloat(std::string _id);
	// bool : 3
	void set(std::string _id, bool _value);
	bool getBool(std::string _id);

private:
	std::string _packageName;
	int _networkID;
	std::map<int, std::map<std::string, std::string>> _data;

	void addUnkownData(int _type, std::string _id, std::string _value);
	bool contains(int _type, std::string _id);
};

