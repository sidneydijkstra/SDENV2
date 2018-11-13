#pragma once

#ifndef EDITORSAVER_H
#define EDITORSAVER_H


#include <scene.h>
#include <mesh.h>
#include <timer.h>
#include <fstream>

class EditorSaver
{
public:
	EditorSaver();
	virtual ~EditorSaver();

	void saveNewFile(std::string data);
	std::string openSaveFile();

private:
};

#endif /* end EDITORSAVER_H */
