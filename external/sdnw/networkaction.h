#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>
#include <functional>

template<class T1>
class NetworkActionT1{ // TODO: make like action in C#
public:
	NetworkActionT1<T1>() {
		_callbacks = std::vector<std::function<void(T1)>>();
	};
	~NetworkActionT1(){
		
	};

	void run(T1 _value) {
		for (size_t i = 0; i < _callbacks.size(); i++){
			_callbacks[i](_value);
		}
	};

	void clear() {
		_callbacks.clear();
	}

	NetworkActionT1& operator+=(const std::function<void(T1)>& _func) {
		this->_callbacks.push_back(_func);
		return *this;
	};

	NetworkActionT1& operator-=(const std::function<void(T1)>& _func) { // TODO: remove func from list (cant compare func)
		for (size_t i = 0; i < _callbacks.size(); i++){
			if (false) {
				_callbacks.erase(_callbacks.begin(), _callbacks.begin() + i);
				return *this;
			}
		}
		return *this;
	};

private:
	std::vector<std::function<void(T1)>> _callbacks;
};

template<class T1, class T2>
class NetworkActionT2 {
public:
	NetworkActionT2<T1, T2>() {
		_callbacks = std::vector<std::function<void(T1, T2)>>();
	};
	~NetworkActionT2() {

	};

	void run(T1 _t1, T2 _t2) {
		for (size_t i = 0; i < _callbacks.size(); i++) {
			_callbacks[i](_t1, _t2);
		}
	};

	void clear() {
		_callbacks.clear();
	}

	NetworkActionT2& operator+=(const std::function<void(T1, T2)>& _func) {
		this->_callbacks.push_back(_func);
		return *this;
	};

private:
	std::vector<std::function<void(T1, T2)>> _callbacks;
};