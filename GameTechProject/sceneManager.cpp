#include "sceneManager.h"
#define DEG_TO_RADIAN 0.017453293



vector<Model> m;


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

void sceneManager::initMusic()
{
	sm = new SoundManager(2);
	sm->init();
	samples = new HSAMPLE[2];
	// Following comment is from source basstest file!
	/* Load a sample from "file" and give it a max of 3 simultaneous
	playings using playback position as override decider */
	samples[0] = sm->loadSample("Trot.wav");
	samples[1] = sm->loadSample("Simple Blues.wav");

	HCHANNEL ch = BASS_SampleGetChannel(samples[1], FALSE);
	sm->setAttributes(0, &ch, 0, 0.01, 0);
	if (!BASS_ChannelPlay(ch, FALSE))
		cout << "Can't play sample" << endl;
}

void sceneManager::loadModel()
{
	m.push_back(Model("../GameTechProject/models/Barracks/ALLIED_Barracks.obj"));

	cubeTest = make_shared<Model>("../GameTechProject/cube.obj");
	
	skyboxModel = make_shared<Model>("../GameTechProject/cube.obj");

	catModel = make_shared<Model>("../GameTechProject/cat.obj");
}



void sceneManager::loadShader()
{
	//ourShader = make_shared<Shader>("shader.vs", "shader.fs");
    ourShader = make_shared<Shader>("phong-tex.vert", "phong-tex.frag");
	cubeShader = make_shared<Shader>("cubeShader.vs", "cubeShader.fs");
	skyboxShader = make_shared<Shader>("cubeMap.vert", "cubeMap.frag");
}

void sceneManager::initShaders()
{	
	

	GLfloat attenuation = 1.0f;

	//ourShader->setFloat("attenuationConst", attenuationConstant);
	//ourShader->setFloat("attenuationLinear", attenuationLinear);
	//ourShader->setFloat("attenuationQuadratic", attenuationQuad);

	ourShader->use();
	//ourShader->setInt("material.diffuse", 0);
	//ourShader->setInt("material.specular", 1);


	//ourShader->setVec3("light.position", -10.0f, -10.0f, 10.0f);
	//ourShader->setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
	//ourShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	//ourShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	ourShader->setVec3("lights[0].position", lightPosition[0]);
	ourShader->setVec3("lights[0].ambient", 0.05f, 0.05f, 0.05f);
	ourShader->setVec3("lights[0].diffuse", 0.5f, 0.5f, 0.5f);
	ourShader->setVec3("lights[0].specular", 1.0f, 1.0f, 1.0f);
	ourShader->setFloat("lights[0].attenuationConst", attenuationConstant);
	ourShader->setFloat("lights[0].attenuationLinear", attenuationLinear);
	ourShader->setFloat("lights[0].attenuationQuadratic", 1.0f);

	ourShader->setVec3("lights[1].position", lightPosition[1]);
	ourShader->setVec3("lights[1].ambient", 0.05f, 0.05f, 0.05f);
	ourShader->setVec3("lights[1].diffuse", 0.5f, 0.5f, 0.5f);
	ourShader->setVec3("lights[1].specular", 1.0f, 1.0f, 1.0f);
	ourShader->setFloat("lights[1].attenuationConst", attenuationConstant);
	ourShader->setFloat("lights[1].attenuationLinear", attenuationLinear);
	ourShader->setFloat("lights[1].attenuationQuadratic", 1.0f);

	ourShader->setVec3("lights[2].position", lightPosition[2]);
	ourShader->setVec3("lights[2].ambient", 0.05f, 0.05f, 0.05f);
	ourShader->setVec3("lights[2].diffuse", 0.5f, 0.5f, 0.5f);
	ourShader->setVec3("lights[2].specular", 1.0f, 1.0f, 1.0f);
	ourShader->setFloat("lights[2].attenuationConst", attenuationConstant);
	ourShader->setFloat("lights[2].attenuationLinear", attenuationLinear);
	ourShader->setFloat("lights[2].attenuationQuadratic", 1.0f);

	ourShader->setVec3("lights[3].position", lightPosition[3]);
	ourShader->setVec3("lights[3].ambient", 0.05f, 0.05f, 0.05f);
	ourShader->setVec3("lights[3].diffuse", 0.5f, 0.5f, 0.5f);
	ourShader->setVec3("lights[3].specular", 1.0f, 1.0f, 1.0f);
	ourShader->setFloat("lights[3].attenuationConst", attenuationConstant);
	ourShader->setFloat("lights[3].attenuationLinear", attenuationLinear);
	ourShader->setFloat("lights[3].attenuationQuadratic", 1.0f);
	
		
}


void sceneManager::update()
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W])
	{
		eye = moveForward(eye, rotation, 0.1f);
	}
	if (keys[SDL_SCANCODE_S])
	{
		eye = moveForward(eye, rotation, -0.1f);
	}
	if (keys[SDL_SCANCODE_A])
	{
		eye = moveRight(eye, rotation, -0.1f);
	}
	if (keys[SDL_SCANCODE_D])
	{
		eye = moveRight(eye, rotation, 0.1f);
	}
	if (keys[SDL_SCANCODE_E])
	{
		eye.y += 0.1;
	}
	if (keys[SDL_SCANCODE_F])
	{
		eye.y -= 0.1;
	}
	if (keys[SDL_SCANCODE_K])
	{
		rotation -= 1.0f;
	}
	if (keys[SDL_SCANCODE_L])
	{
		rotation += 1.0f;
	}
	if (keys[SDL_SCANCODE_1])
	{
		health -= 1;
			Sleep(100);
			cout << health << endl;
	}

	if (keys[SDL_SCANCODE_Y])
	{
		lightPosition[1] = glm::vec4(moveForward(lightPosition[1], 0.0f, 0.1f), 1.0f);
	}

	if (keys[SDL_SCANCODE_G])
	{
		lightPosition[1] = glm::vec4(moveRight(lightPosition[1], 0.0f, -0.1f), 1.0f);
	}

	if (keys[SDL_SCANCODE_H])
	{
		lightPosition[1] = glm::vec4(moveForward(lightPosition[1], 0.0f, -0.1f), 1.0f);
	}

	if (keys[SDL_SCANCODE_J])
	{
		lightPosition[1] = glm::vec4(moveRight(lightPosition[1], 0.0f, 0.1f), 1.0);
	}

	if (keys[SDL_SCANCODE_N])
	{
		lightPosition[1].y += 0.1;
	}

	if (keys[SDL_SCANCODE_M])
	{
		lightPosition[1].y -= 0.1;
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

	eye = { 0.0, 15.0, 30.0 };
	at = { 0.0, 0.0, -1.0 };
	up = { 0.0, 1.0, 0.0 };
	window = setupRC(context);
	glewInitilisation();
	loadShader();
	initShaders();
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

	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f * DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);

	glm::mat4 view(1.0f);					//Only here for skybox, nt actually needed

	glm::mat4 modelView = glm::mat4(1.0f);
	modelStack.push(modelView);

	
	at = moveForward(eye, rotation, 1.0f);
	modelStack.top() = glm::lookAt(eye, at, up);

	glDepthMask(GL_FALSE);
	glm::mat3 mvRotOnlyMat3 = glm::mat3(modelStack.top());
	modelStack.push(glm::mat4(mvRotOnlyMat3));

	glCullFace(GL_FRONT);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
	skyboxShader->use();
	skyboxShader->setMat4("projection", projection);
	skyboxShader->setMat4("modelView", modelView);
	
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(20.5f, 20.5f, 20.5f));
	skyboxShader->setMat4("modelView", modelStack.top());
	skyboxModel->modelDraw(*skyboxShader);
	glCullFace(GL_BACK);
	modelStack.pop();
	glDepthMask(GL_TRUE);
	
	ourShader->use();
	   



	ourShader->setMat4("modelView", modelView);
	ourShader->setMat4("projection", projection);

	
	//ourShader->setMat4("view", view);

		
	glm::vec4 tmpZero = modelStack.top() * glm::vec4(lightPosition[1], 1.0);
	lightPosition[0].x = tmpZero.x;
	lightPosition[0].y = tmpZero.y;
	lightPosition[0].z = tmpZero.z;
	ourShader->setLightPos("lights[0].position", glm::value_ptr(tmpZero));
			   		 
	//glm::vec4 tmpOne = modelStack.top() * glm::vec4(lightPosition[1], 1.0);
	//lightPosition[1].x = tmpOne.x;
	//lightPosition[1].y = tmpOne.y;
	//lightPosition[1].z = tmpOne.z;
	//ourShader->setLightPos("lights[1].position", glm::value_ptr(tmpOne));
	//	
	//glm::vec4 tmpTwo = modelStack.top() * glm::vec4(lightPosition[2], 1.0);
	//lightPosition[2].x = tmpTwo.x;
	//lightPosition[2].y = tmpTwo.y;
	//lightPosition[2].z = tmpTwo.z;
	//ourShader->setLightPos("lights[2].position", glm::value_ptr(tmpTwo));

	/*glm::vec4 tmpThree = modelStack.top() * glm::vec4(lightPosition[0], 1.0);
	lightPosition[3].x = tmpThree.x;
	lightPosition[3].y = tmpThree.y;
	lightPosition[3].z = tmpThree.z;		
	ourShader->setLightPos("lights[3].position", glm::value_ptr(tmpThree));*/
		

	cubeShader->use();	
	cubeShader->setMat4("projection", projection);
	cubeShader->setMat4("view", view);			//Doesnt actually need to be passed it, will dfault itself.
	
	modelStack.push(modelStack.top());															//Cube for light position
	modelStack.top() = glm::translate(modelStack.top(), lightPosition[0]);
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.05f, 0.05f, 0.05f));
	cubeShader->setUniformMatrix4fv("modelView", glm::value_ptr(modelStack.top()));
	cubeTest->modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());															//Cube for light position
	modelStack.top() = glm::translate(modelStack.top(), lightPosition[1]);
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.05f, 0.05f, 0.05f));
	cubeShader->setUniformMatrix4fv("modelView", glm::value_ptr(modelStack.top()));
	cubeTest->modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());															//Cube for light position
	modelStack.top() = glm::translate(modelStack.top(), lightPosition[2]);
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.05f, 0.05f, 0.05f));
	cubeShader->setUniformMatrix4fv("modelView", glm::value_ptr(modelStack.top()));
	cubeTest->modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());															//Cube for light position
	modelStack.top() = glm::translate(modelStack.top(), lightPosition[3]);
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.05f, 0.05f, 0.05f));
	cubeShader->setUniformMatrix4fv("modelView", glm::value_ptr(modelStack.top()));
	cubeTest->modelDraw(*ourShader);
	modelStack.pop();



	ourShader->use();


	// render the loaded model
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(0.0f, 10.0f, -10.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(15.5f, 20.5f, 20.5f));
	ourShader->setMat4("modelView", modelStack.top());
	for (int i = 0; i < m.size(); i++)
	{
		m[i].modelDraw(*ourShader);
	}
	//modelStack.pop();


	modelStack.push(modelStack.top());															//Cube for light position
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(0.0f, 10.0f, -10.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0f, 1.0f, 1.0f));
	ourShader->setUniformMatrix4fv("modelView", glm::value_ptr(modelStack.top()));
	catModel->modelDraw(*ourShader);
	modelStack.pop();


	SDL_GL_SwapWindow(window);  //Swap buffers
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


