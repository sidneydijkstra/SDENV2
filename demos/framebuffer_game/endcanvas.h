
#ifndef ENDCANVAS_H
#define ENDCANVAS_H

#include <ui.h>
#include "savemanager.h"

class EndCanvas : public Canvas {
public:
	EndCanvas();
	~EndCanvas();

	virtual void update();

	void loadScore();
	void updateText();
	UIButton* _back;

private:
	UIImage* _background;

	UITextField* _title;
	UITextField* _highscore1;
	UITextField* _highscore2;
	UITextField* _highscore3;
	UITextField* _highscore4;
	UITextField* _highscore5;
};

#endif /* end ENDCANVAS_H */
