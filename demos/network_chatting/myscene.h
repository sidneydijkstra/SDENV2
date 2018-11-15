#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H

#include <scene.h>
#include <mesh.h>
#include <timer.h>
#include <networkhandler.h>
#include <package.h>
#include <action.h>

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);
private:

	void connected();
	void getInput();
	void sendMessage(std::string _message);
	void displayMessage(Package _pack);

	Canvas* _canvas;
	UIButton* _button;
	UITextField* _message;
	UITextField* _input;

	std::vector<UITextField*> _messages;

	// network packages
	Package* p_sendMessage;
};

#endif /* end MYSCENE_H */
