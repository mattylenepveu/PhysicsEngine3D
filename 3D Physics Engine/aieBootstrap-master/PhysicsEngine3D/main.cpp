// Includes(s)
#include "PhysicsEngine3DApp.h"
#include <crtdbg.h>

//--------------------------------------------------------------------------------
// Main function that runs the application.
//
// Return:
//		Returns 0 (or false) when we close application.
//--------------------------------------------------------------------------------
int main() 
{
	// Detects any memory leaks throughout the project
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Creates a "new" PhysicsEngine3DApp so we can run application
	auto app = new PhysicsEngine3DApp();

	// Initializes the application and loops it
	app->run("AIE", 1280, 720, false);

	// Deallocates the app pointer to prevent memory leaks
	delete app;

	// Returns 0 (or false) to end the application
	return 0;
}