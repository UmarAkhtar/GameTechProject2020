#include "sceneManager.h"
#define DEG_TO_RADIAN 0.017453293

GLint x, y, z = 0;

vector<Model> gameObjects;

bool walking = false;

GLfloat yoffset, yoffset1, yoffset2 = 0;

bool key1Found, key2Found = false;

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

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	
	for (int i = 0; i < 2; i++)
	{
	gameObjects.push_back(Model("../GameTechProject/models/Wall/SciFi_Wall.obj"));
	}

	
	skyboxModel = make_shared<Model>("../GameTechProject/cube.obj");
}

void sceneManager::initMusic()
{
	sm = new SoundManager(3);
	sm->init();
	samples = new HSAMPLE[3];
	// Following comment is from source basstest file!
	/* Load a sample from "file" and give it a max of 3 simultaneous
	playings using playback position as override decider */
	samples[0] = sm->loadSample("Trot.wav");
	samples[1] = sm->loadSample("Simple Blues.wav");
	samples[2] = sm->loadSample("fot.wav");

	/*HCHANNEL ch = BASS_SampleGetChannel(samples[1], FALSE);
	sm->setAttributes(0, &ch, 0, 0.01, 0);
	if (!BASS_ChannelPlay(ch, FALSE))
		cout << "Can't play sample" << endl;*/
	






}

void sceneManager::loadShader()
{
	ourShader = make_shared<Shader>("shader.vs", "shader.fs");
	skyboxShader = make_shared<Shader>("cubeMap.vert", "cubeMap.frag");
}


void sceneManager::update()
{

	//cout << walking << endl;
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W])
	{

walking = true;

		eye = moveForward(eye, rotation, 0.1f);
		
	
	}
	else
	{
		walking = false;
	}


	
	
	if (keys[SDL_SCANCODE_S])
	{
		eye = moveForward(eye, rotation, -0.1f);
		walking = true;
	}
	if (keys[SDL_SCANCODE_A])
	{
		eye = moveRight(eye, rotation, -0.1f);
		walking = true;
	}
	if (keys[SDL_SCANCODE_D])
	{
		eye = moveRight(eye, rotation, 0.1f);
		walking = true;
	}

	if (keys[SDL_SCANCODE_Q])
	{
		rotation -= 1.0f;
	}
	if (keys[SDL_SCANCODE_E])
	{
		rotation += 1.0f;
	}
	if (keys[SDL_SCANCODE_R])
	{
		eye.y += 0.1f;
	}
	if (keys[SDL_SCANCODE_F])
	{
		eye.y -= 0.1f;
	}


	if (keys[SDL_SCANCODE_1])
	{
		health -= 1;
		Sleep(100);
		cout << health << endl;
	}


	if (keys[SDL_SCANCODE_O] && key1Found)
	{

		while(yoffset <= 3)
		{
			yoffset += 0.01f;
		}
		
	
				
				
	}

	if (keys[SDL_SCANCODE_P])
	{

		while (yoffset1 <= 3)
		{
			yoffset1 += 0.01f;
		}
	}

	if (keys[SDL_SCANCODE_K] && key2Found)
	{

		while (yoffset2 <= 3)
		{
			yoffset2 += 0.01f;
		}
	}

	if (keys[SDL_SCANCODE_2])
	{
		key1Found = true;
		Sleep(300);
		cout << "Key 1 Found, Open the door infront of you1" << endl;
		Sleep(300);
	}

	if (keys[SDL_SCANCODE_3])
	{
		key2Found = true;
		Sleep(300);
		cout << "Key 2 Found, Open the door on your left" << endl;
		Sleep(300);
	}
	
	
}

glm::vec3 sceneManager::moveForward(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + d * std::sin(rotation * DEG_TO_RADIAN), pos.y, pos.z - d * std::cos(rotation * DEG_TO_RADIAN));
}


glm::vec3 sceneManager::moveRight(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + d * std::cos(rotation * DEG_TO_RADIAN), pos.y, pos.z + d * std::sin(rotation * DEG_TO_RADIAN));
}



	





sceneManager::sceneManager(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight)
{
	eye.x = 6.0f;
	eye.y = 1.3f;
	eye.z = 0.0f;
	at.x = 0.0f;
	at.y = 1.0f;
	at.z = -1.0f;
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	window = setupRC(context);
	glewInitilisation();
	loadShader();
	loadModel();
	loadSkybox(cubeTexFiles, &skybox);
	initMusic();
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




	if (walking == true)
	{
		HCHANNEL ch = BASS_SampleGetChannel(samples[2], FALSE);
		sm->setAttributes(0, &ch, 0, 1.0, 0);
		if (!BASS_ChannelPlay(ch, FALSE))
			cout << "Can't play sample" << endl;
	}



	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f * DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);

	glm::mat4 view(1.0);
	model.push(view);

	
	at = moveForward(eye, rotation, 1.0f);
	model.top() = glm::lookAt(eye, at, up);

	drawSkybox(projection, view);
	
	ourShader->use();
	ourShader->setMat4("projection", projection);
	ourShader->setMat4("view", view);
    
	
	
	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(2.75, 1, -25.2));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f,-0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();


	firstRoom();


	hallwayFromFirstRoom();


ourShader->setMat4("model", model.top());


SDL_GL_SwapWindow(window);  //Swap buffers
}

void sceneManager::drawSkybox(glm::mat4 &projection, glm::mat4 &view)
{
	glDepthMask(GL_FALSE);
	glm::mat3 mvRotOnlyMat3 = glm::mat3(model.top());
	model.push(glm::mat4(mvRotOnlyMat3));

	glCullFace(GL_FRONT);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
	skyboxShader->use();
	skyboxShader->setMat4("projection", projection);
	skyboxShader->setMat4("view", view);

	model.top() = glm::scale(model.top(), glm::vec3(20.5f, 20.5f, 20.5f));
	skyboxShader->setMat4("model", model.top());
	skyboxModel->modelDraw(*skyboxShader);
	glCullFace(GL_BACK);
	model.pop();
	glDepthMask(GL_TRUE);
}

void sceneManager::hallwayFromFirstRoom()
{
	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -9.8));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -12.3));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -14.8));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -17.4));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -20));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -22.5));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -25));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	///////////

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -9.8));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());

	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -12.3));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());

	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -14.8));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());

	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -17.4));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());

	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -20));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());

	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1 +  yoffset2, -22.5));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -25));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();
	///////////

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(5.3, 1 +  yoffset1, -27.5));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();
}

void sceneManager::firstRoom()
{
	model.push(model.top());
	gameObjects[0].setPosition(glm::vec3(0, 1, 0));
	model.top() = glm::translate(model.top(), gameObjects[0].getPosition());
	ourShader->setMat4("model", model.top());
	gameObjects[0].modelDraw(*ourShader);
	model.pop();


	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(0, 1, -2.5));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(0, 1, -5));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(0, 1, -7.5));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(2.8, 1, -10));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(5.3, 1 +  yoffset, -10));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(7.8, 1, -10));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(10.3, 1, -10));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[0].setPosition(glm::vec3(13.2, 1, 0));
	model.top() = glm::translate(model.top(), gameObjects[0].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[0].modelDraw(*ourShader);
	model.pop();


	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(13.2, 1, -2.5));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(13.2, 1, -5));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(13.2, 1, -7.5));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(2.8, 1, 2.8));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(5.3, 1, 2.8));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(7.8, 1, 2.8));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();

	model.push(model.top());
	gameObjects[1].setPosition(glm::vec3(10.3, 1, 2.8));
	model.top() = glm::translate(model.top(), gameObjects[1].getPosition());
	model.top() = glm::rotate(model.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("model", model.top());
	gameObjects[1].modelDraw(*ourShader);
	model.pop();
}

SDL_Window* sceneManager::setupRC(SDL_GLContext& context)
{
	SDL_Window* window;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "Unable to initialize SDL " << endl;;


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); 

	// Create 800x600 window
	window = SDL_CreateWindow("The Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) // Check window was created OK
		cout << "Unable to create window" << endl;

	context = SDL_GL_CreateContext(window); // Create opengl context and attach to window
	SDL_GL_SetSwapInterval(1); // set swap buffers to sync with monitor's vertical refresh rate
	return window;
}

GLuint sceneManager::loadSkybox(const char* fname[6], GLuint* texID)
{
	glGenTextures(1, texID); // generate texture ID
	GLenum sides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
						GL_TEXTURE_CUBE_MAP_POSITIVE_X,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
						GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Y };
	SDL_Surface* tmpSurface;

	glBindTexture(GL_TEXTURE_CUBE_MAP, *texID); // bind texture and set parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	GLuint externalFormat;
	for (int i = 0; i < 6; i++)
	{
		// load file - using core SDL library
		tmpSurface = SDL_LoadBMP(fname[i]);
		if (!tmpSurface)
		{
			std::cout << "Error loading bitmap" << std::endl;
			return *texID;
		}

		// skybox textures should not have alpha (assuming this is true!)
		SDL_PixelFormat* format = tmpSurface->format;
		externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;

		glTexImage2D(sides[i], 0, GL_RGB, tmpSurface->w, tmpSurface->h, 0,
			externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
		// texture loaded, free the temporary buffer
		SDL_FreeSurface(tmpSurface);
	}
	return *texID;
}


