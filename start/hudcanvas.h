#pragma once

#ifndef HUDCANVAS_H
#define HUDCANVAS_H


#include <scene.h>
#include <mesh.h>
#include <timer.h>

#include "ui.h"

class HudCanvas : public Canvas
{
public:
	HudCanvas();
	virtual ~HudCanvas();

	virtual void update(float deltatime);

	void addCoin(std::string message);
	void addHealth(std::string message);
	void addTimer(std::string message);

private:
	UITextField* _textCoin;
	UITextField* _textHealth;
	UITextField* _textTimer;
};

#endif /* end HUDCANVAS_H */
