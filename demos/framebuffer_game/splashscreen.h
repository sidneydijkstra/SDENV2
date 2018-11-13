
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <entity.h>

class SplashScreen : public Entity
{
public:
	SplashScreen();
	~SplashScreen();

	void update(float deltatime);

private:
};

#endif /* end SPLASHSCREEN_H */
