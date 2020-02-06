#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stack>
#include <Windows.h>

#include "main.h"

class InputManager
{
private:
	const Uint8* keys = SDL_GetKeyboardState(NULL);
public:
	void update();
	void moveForward();
};
