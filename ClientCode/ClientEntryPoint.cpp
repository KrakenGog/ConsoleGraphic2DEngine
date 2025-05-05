#include "MainScene.h"


extern "C" Scene* getFirstScene() {
	return new MainScene();
}
