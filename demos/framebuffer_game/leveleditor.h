#pragma once

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H


#include <scene.h>
#include <mesh.h>
#include <timer.h>
#include "player.h"
#include "tile.h"
#include "level.h"
#include "enemy.h"
#include "editortile.h"
#include "editorcanvas.h"

#include "editorsaver.h"

class LevelEditor : public Scene
{
public:
	LevelEditor();
	virtual ~LevelEditor();

	virtual void update(float deltatime);

	void updateCamera(float deltatime);
	void updateClick(float deltatime);
	void updateHover(float deltatime);
	void updateEditor(float deltatime);

	void nextTile();
	void prefTile();

	void createMap(int sizeX, int sizeY);
	glm::vec3 calculatePosition(int x, int y, int widht, int height);

	void saveFile();
	void loadSaveFile();
	std::vector<std::string> split(const std::string & string, char delim);

	struct Tile {
		std::string name;
		const char* texture;

		Tile(std::string _name, const char* _texture) {
			name = _name;
			texture = _texture;
		}
	};
private:
	EditorCanvas* _editorcanvas;
	EditorSaver* _editorsaver;

	std::vector<EditorTile*> _map;

	std::vector<Tile> _tiles;
	int _currentTile;
	int _currentMode;
	int _currentLayer;

	int _currentEnemyModeStage;
	EditorTile* _currentEnemyTile;

	int _widht, _height;
	float _speed;
};

#endif /* end LEVELEDITOR_H */
