#include "Application2D.h"

int main() {
	
	auto app = new Application2D();
	app->run("AIE", 1920, 1080, false);
	delete app;

	return 0;
}