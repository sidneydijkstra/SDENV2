
#ifndef MENUCANVAS_H
#define MENUCANVAS_H

#include <ui.h>
#include "savemanager.h"

class MenuCanvas : public Canvas {
public:
	MenuCanvas();
	~MenuCanvas();

	virtual void update();
	UIButton* _start;

private:
	UITextField* _title;

	UITextField* _tutorialA; // movement
	UITextField* _tutorialB; // enemys - coins
	UITextField* _tutorialC; // world

	UITextField* _creditArt;
	UITextField* _creditDev;
};

#endif /* end MENUCANVAS_H */
