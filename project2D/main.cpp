#include "Application2D.h"

int main() {
	
	auto app = new Application2D();
	app->run("AIE", SCREEN_WIDTH, SCREEN_HEIGHT, false);
	delete app;

	return 0;
}