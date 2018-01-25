#pragma once

#ifndef EDITORCANVAS_H
#define EDITORCANVAS_H


#include <scene.h>
#include <mesh.h>
#include <timer.h>

#include "ui.h"

class EditorCanvas : public Canvas
{
public:
	EditorCanvas();
	virtual ~EditorCanvas();

	virtual void update(float deltatime);

	void addTileNameText(std::string message);
	void addModeText(std::string message);
	void addLayerText(std::string message);

private:
	UITextField* _textTile;
	UITextField* _textmode;
	UITextField* _textlayer;
};

#endif /* end EDITORCANVAS_H */
