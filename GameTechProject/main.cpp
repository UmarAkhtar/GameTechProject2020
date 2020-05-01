#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include "rt3d.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stack>
#include <Windows.h>
#include "SoundManager.h"
#include "main.h"
#include "sceneManager.h"
//#include <SDL_ttf.h>


using namespace std;


int main(int argc, char* argv[]) 
{
	sceneManager s(1000, 700);
	bool running = true; // set running to true
	SDL_Event sdlEvent;  // variable to detect SDL events
	while (running) {	// the event loop
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT)
				running = false;
		}		
		s.draw();
		s.update();		
	}


	return 0;
}