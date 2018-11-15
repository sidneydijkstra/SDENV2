/**
* @file action.h
*
* @brief The Action header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <vector>
#include <functional>

// TODO: remove callback with -= (error: cant compare callbacks)

/**
* @brief The Action class
*/

class ActionT0 {
public:
	ActionT0() { ///< @brief Constructor of the Action
		_callbacks = std::vector<std::function<void()>>();
	};
	~ActionT0() { ///< @brief Destructor of the Action

	};

	ActionT0& operator+=(const std::function<void()> _func) {
		_callbacks.push_back(_func);
	};

	void clear() {
		_callbacks.clear();
	};

	void run() {
		for (size_t i = 0; i < _callbacks.size(); i++) {
			_callbacks[i]();
		}
	};

private:
	std::vector<std::function<void()>> _callbacks;
};

template<class T1> 
class ActionT1{
	public:
		ActionT1<T1>() { ///< @brief Constructor of the Action
			_callbacks = std::vector<std::function<void(T1)>>();
		};
		~ActionT1() { ///< @brief Destructor of the Action
	
		};

		ActionT1& operator+=(const std::function<void(T1)> _func) {
			_callbacks.push_back(_func);
		};

		void clear() {
			_callbacks.clear();
		};

		void run(T1 _t1) {
			for (size_t i = 0; i < _callbacks.size(); i++){
				_callbacks[i](_t1);
			}
		};

	private:
		std::vector<std::function<void(T1)>> _callbacks;
};

#endif /* end ACTION_H */