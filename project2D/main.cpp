#include "Application2D.h"

int main() {
	
	auto app = new Application2D();
	app->run("AIE", 1920, 1080, true);
	delete app;

	// app->run("AIE", (app->m_resX, app->m_resY, true);

	return 0;
}