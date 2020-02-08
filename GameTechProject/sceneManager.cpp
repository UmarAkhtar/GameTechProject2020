#include "sceneManager.h"
#define DEG_TO_RADIAN 0.017453293

void sceneManager::glewInitilisation()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{ 
		std::cout << "glewInit failed, aborting." << endl;
		exit(1);
	}
	cout << glGetString(GL_VERSION) << endl;
}

void sceneManager::loadModel()
{
	ourModel = make_shared<Model>("../GameTechProject/models/Barracks/ALLIED_Barracks.obj");
}

void sceneManager::loadShader()
{
	ourShader = make_shared<Shader>("shader.vs", "shader.fs");
}

void sceneManager::update()
{
}

sceneManager::sceneManager(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight)
{
	window = setupRC(context);
	glewInitilisation();
	loadShader();
	loadModel();
	draw();
}

sceneManager::~sceneManager()
{

}

void sceneManager::draw()
{
	glEnable(GL_CULL_FACE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f * DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);

	glm::mat4 view(1.0);

	ourShader->use();
	ourShader->setMat4("projection", projection);
	ourShader->setMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -10.0f, -30.0f));
	model = glm::scale(model, glm::vec3(20.5f, 20.5f, 20.5f));	
	ourShader->setMat4("model", model);
	ourModel->modelDraw(*ourShader);



	SDL_GL_SwapWindow(window);  //Swap buffers
}

SDL_Window* sceneManager::setupRC(SDL_GLContext& context)
{
	SDL_Window* window;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "Unable to initialize SDL " << endl;;

	// Request an OpenGL 3.0 context.

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // Turn on x4 multisampling anti-aliasing (MSAA)

	// Create 800x600 window
	window = SDL_CreateWindow("SDL/GLM/OpenGL Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) // Check window was created OK
		cout << "Unable to create window" << endl;

	context = SDL_GL_CreateContext(window); // Create opengl context and attach to window
	SDL_GL_SetSwapInterval(1); // set swap buffers to sync with monitor's vertical refresh rate
	return window;
}


