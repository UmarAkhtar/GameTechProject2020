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

void sceneManager::initMusic()
{
	sm = new SoundManager(2);
	sm->init();
	samples = new HSAMPLE[2];
	// Following comment is from source basstest file!
	/* Load a sample from "file" and give it a max of 3 simultaneous
	playings using playback position as override decider */
	samples[0] = sm->loadSample("Trot.wav");
	samples[1] = sm->loadSample("space.mp3");

	HCHANNEL ch = BASS_SampleGetChannel(samples[1], FALSE);
	sm->setAttributes(0, &ch, 0, 0.01, 0);
	if (!BASS_ChannelPlay(ch, FALSE))
		cout << "Can't play sample" << endl;
}

void sceneManager::loadModel()
{
	cubeTest = make_shared<Model>("../GameTechProject/cube.obj");

	skyboxModel = make_shared<Model>("../GameTechProject/cube.obj");
	floorRoofPlane = make_shared<Model>("../GameTechProject/models/Wall/SciFi_Wall_Floor_Ceiling.obj");

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	gameObjects.push_back(Model("../GameTechProject/models/Wall/SciFi_Wall_Window.obj"));								// [0] window wall section
	gameObjects.push_back(Model("../GameTechProject/models/Wall/SciFi_Wall.obj"));										// [1] single wall section
	gameObjects.push_back(Model("../GameTechProject/models/Wall/SciFi_Wall_Floor_Ceiling.obj"));						// [2] ground roof section 
	gameObjects.push_back(Model("../GameTechProject/models/Wall/SciFi_Wall_5.obj"));									// [3] 5 piece wall section 
	gameObjects.push_back(Model("../GameTechProject/models/chargers/health/SciFi_Health.obj"));							// [4] Health charger
	gameObjects.push_back(Model("../GameTechProject/models/chargers/ammo/SciFi_Ammo.obj"));								// [5] Ammo charger
	gameObjects.push_back(Model("../GameTechProject/models/Bay/bed/SciFi_Bed.obj"));									// [6] Beds
	gameObjects.push_back(Model("../GameTechProject/models/gun/gun.obj"));												// [7] Gun
	gameObjects.push_back(Model("../GameTechProject/models/dockingBay/Spaceship.obj"));									// [8] Small ship
	gameObjects.push_back(Model("../GameTechProject/models/dockingBay/Luminaris_OBJ.obj"));								// [9] Big ship
	gameObjects.push_back(Model("../GameTechProject/models/Test/Tree_frog.dae"));								// [10] TEST ANT

}

void sceneManager::loadShader()
{	
	ourShader = make_shared<Shader>("phong-tex.vert", "phong-tex.frag");
	cubeShader = make_shared<Shader>("cubeShader.vs", "cubeShader.fs");
	skyboxShader = make_shared<Shader>("cubeMap.vert", "cubeMap.frag");
}

void sceneManager::initShaders()
{

	ourShader->use();
	ourShader->setMaterial("material", material);
	//ourShader->setVec3("pointLights[0].position", lightPosition[0]);
	ourShader->setVec3("pointLights[0].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[0].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[0].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[0].constant", 0.5);
	ourShader->setFloat("pointLights[0].linear", 0.02);
	ourShader->setFloat("pointLights[0].quadratic", 0.01);
	// point light 2
	//ourShader->setVec3("pointLights[1].position", lightPosition[1]);
	ourShader->setVec3("pointLights[1].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[1].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[1].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[1].constant", 1.0f);
	ourShader->setFloat("pointLights[1].linear", 0.09);
	ourShader->setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	//ourShader->setVec3("pointLights[2].position", lightPosition[2]);
	ourShader->setVec3("pointLights[2].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[2].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[2].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[2].constant", 1.0f);
	ourShader->setFloat("pointLights[2].linear", 0.09);
	ourShader->setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	//ourShader->setVec3("pointLights[3].position", lightPosition[3]);
	ourShader->setVec3("pointLights[3].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[3].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[3].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[3].constant", 1.0f);
	ourShader->setFloat("pointLights[3].linear", 0.09);
	ourShader->setFloat("pointLights[3].quadratic", 0.032);

	ourShader->setVec3("pointLights[4].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[4].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[4].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[4].constant", 1.0f);
	ourShader->setFloat("pointLights[4].linear", 0.09);
	ourShader->setFloat("pointLights[4].quadratic", 0.032);

	ourShader->setVec3("pointLights[5].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[5].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[5].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[5].constant", 1.0f);
	ourShader->setFloat("pointLights[5].linear", 0.09);
	ourShader->setFloat("pointLights[5].quadratic", 0.032);

	ourShader->setVec3("pointLights[6].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[6].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[6].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[6].constant", 1.0f);
	ourShader->setFloat("pointLights[6].linear", 0.09);
	ourShader->setFloat("pointLights[6].quadratic", 0.032);

	ourShader->setVec3("pointLights[7].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[7].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[7].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[7].constant", 1.0f);
	ourShader->setFloat("pointLights[7].linear", 0.09);
	ourShader->setFloat("pointLights[7].quadratic", 0.032);

	ourShader->setVec3("pointLights[8].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[8].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[8].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[8].constant", 1.0f);
	ourShader->setFloat("pointLights[8].linear", 0.09);
	ourShader->setFloat("pointLights[8].quadratic", 0.032);

	ourShader->setVec3("pointLights[9].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[9].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[9].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[9].constant", 1.0f);
	ourShader->setFloat("pointLights[9].linear", 0.09);
	ourShader->setFloat("pointLights[9].quadratic", 0.032);

	ourShader->setVec3("pointLights[10].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[10].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[10].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[10].constant", 1.0f);
	ourShader->setFloat("pointLights[10].linear", 0.09);
	ourShader->setFloat("pointLights[10].quadratic", 0.032);

	ourShader->setVec3("pointLights[11].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[11].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[11].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[11].constant", 1.0f);
	ourShader->setFloat("pointLights[11].linear", 0.09);
	ourShader->setFloat("pointLights[11].quadratic", 0.032);

	ourShader->setVec3("pointLights[12].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[12].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[12].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[12].constant", 1.0f);
	ourShader->setFloat("pointLights[12].linear", 0.09);
	ourShader->setFloat("pointLights[12].quadratic", 0.032);

	ourShader->setVec3("pointLights[13].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[13].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[13].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[13].constant", 1.0f);
	ourShader->setFloat("pointLights[13].linear", 0.09);
	ourShader->setFloat("pointLights[13].quadratic", 0.032);

	ourShader->setVec3("pointLights[14].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[14].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[14].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[14].constant", 1.0f);
	ourShader->setFloat("pointLights[14].linear", 0.09);
	ourShader->setFloat("pointLights[14].quadratic", 0.032);

	ourShader->setVec3("pointLights[15].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[15].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[15].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[15].constant", 1.0f);
	ourShader->setFloat("pointLights[15].linear", 0.09);
	ourShader->setFloat("pointLights[15].quadratic", 0.032);

	ourShader->setVec3("pointLights[16].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[16].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[16].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[16].constant", 1.0f);
	ourShader->setFloat("pointLights[16].linear", 0.09);
	ourShader->setFloat("pointLights[16].quadratic", 0.032);

	ourShader->setVec3("pointLights[17].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[17].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[17].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[17].constant", 1.0f);
	ourShader->setFloat("pointLights[17].linear", 0.09);
	ourShader->setFloat("pointLights[17].quadratic", 0.032);

	ourShader->setVec3("pointLights[18].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[18].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[18].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[18].constant", 1.0f);
	ourShader->setFloat("pointLights[18].linear", 0.09);
	ourShader->setFloat("pointLights[18].quadratic", 0.032);

	ourShader->setVec3("pointLights[19].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[19].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[19].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[19].constant", 1.0f);
	ourShader->setFloat("pointLights[19].linear", 0.09);
	ourShader->setFloat("pointLights[19].quadratic", 0.032);

	ourShader->setVec3("pointLights[20].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[20].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[20].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[20].constant", 1.0f);
	ourShader->setFloat("pointLights[20].linear", 0.09);
	ourShader->setFloat("pointLights[20].quadratic", 0.032);

	ourShader->setVec3("pointLights[21].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[21].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[21].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[21].constant", 1.0f);
	ourShader->setFloat("pointLights[21].linear", 0.09);
	ourShader->setFloat("pointLights[21].quadratic", 0.032);

	ourShader->setVec3("pointLights[22].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[22].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[22].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[22].constant", 1.0f);
	ourShader->setFloat("pointLights[22].linear", 0.09);
	ourShader->setFloat("pointLights[22].quadratic", 0.032);

	ourShader->setVec3("pointLights[23].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[23].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[23].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[23].constant", 1.0f);
	ourShader->setFloat("pointLights[23].linear", 0.09);
	ourShader->setFloat("pointLights[23].quadratic", 0.032);
	
}


glm::vec3 sceneManager::moveForward(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + d * std::sin(rotation * DEG_TO_RADIAN), pos.y, pos.z - d * std::cos(rotation * DEG_TO_RADIAN));
}

glm::vec3 sceneManager::moveRight(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + d * std::cos(rotation * DEG_TO_RADIAN), pos.y, pos.z + d * std::sin(rotation * DEG_TO_RADIAN));
}

glm::vec3 sceneManager::reverseMouse(glm::vec3 windowCoords, glm::mat4 model, glm::mat4 projection, glm::vec4 view)
{
	//int mouseX = 0;
	//int mouseY = 0;
	//
	////mouseY = 800 - mouseY;

	//SDL_GetMouseState(&mouseX, &mouseY);
	//rayMouseTest = glm::vec2(mouseX, mouseY);
	//glm::vec3 mouseSource = glm::vec3(mouseX, mouseY, 1.0f);

	POINT cp;
	GetCursorPos(&cp);
	mouseX = cp.x;
	mouseY = cp.y;
	cout << "SCREEN POSITION X " << mouseX << endl;
	cout << "SCREEN POSITION Y" << mouseY << endl;
	glm::vec3 mouseCoords = glm::vec3(mouseX, windowHeight - mouseY - 1, 0.0);
	//glm::vec3 result = glm::unProject(windowCoords, model, projection, view);
	glm::vec3 result = glm::unProject(mouseCoords, model, projection, view);
	
	//cout << result.x << endl;
	//cout << result.y << endl;
	//cout << result.z << endl;
	cout << "WORLD POSITION X " << result.x << endl;
	cout << "WORLD POSITION Y" << result.y << endl;
	cout << "WORLD POSITION Z" << result.z << endl;


}



glm::vec3 sceneManager::mouseRay(glm::mat4 proj, glm::mat4 modelView)
{

	//int mouseX, mouseY = 0;
	//SDL_GetMouseState(&mouseX, &mouseY);
	//rayMouseTest = glm::vec2(mouseY, mouseY);

	POINT cp;
	GetCursorPos(&cp);
	mouseX = cp.x;
	mouseY = cp.y;

	//cout << mouseX << endl;
	//cout << mouseY << endl;
	glm::vec2 normCoords = getNormalisedCoords(mouseX, mouseX);
	glm::vec4 clipCoords = glm::vec4(normCoords.x, normCoords.y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = toEyeCoords(clipCoords, proj);
	glm::vec3 worldRay = toWorldCoords(eyeCoords, modelView);
	
	cout << "RAY IN WORLD : " << worldRay.x << endl;
	cout << "RAY IN WORLD : " << worldRay.y << endl;
	cout << "RAY IN WORLD : " << worldRay.z << endl;
	return worldRay;

}

glm::vec4 sceneManager::toEyeCoords(glm::vec4 clipCoords, glm::mat4 proj)
{
	glm::mat4 invertProj = glm::inverse(proj);
	glm::vec4 eyeCoords = invertProj * clipCoords;
	//return glm::vec4(eyeCoords);
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0, 0.0);
	//cout << "eye coords x" << eyeCoords.x << endl;
	//cout << "eye coords y" << eyeCoords.y << endl;
	return eyeCoords;
}

glm::vec2 sceneManager::getNormalisedCoords(float mouseX, float mouseY)
{
	
	float x = (2 * mouseX) / windowWidth - 1.0;
	float y = 1.0 - (2 * mouseY) / windowHeight;
	//cout << "normalised x = " << x << endl;
	//cout << "normalised y = " << y << endl;
	return glm::vec2(x, y);
}

glm::vec3 sceneManager::toWorldCoords(glm::vec4 eyeCoords, glm::mat4 modelView)
{
	glm::mat4 invertedView = glm::inverse(modelView);
	glm::vec4 worldRay = invertedView * eyeCoords;
	glm::vec3 mouseRay = glm::vec3(worldRay.x, worldRay.y, worldRay.z);
	glm::normalize(mouseRay);
	return mouseRay;
	
}


sceneManager::sceneManager(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight)
{
	//doorOneHeight = testDoorVectorDown;
	//doorTwoHeight = testDoorVectorDown;

	doorOneHeight = yAxisDown;
	doorTwoHeight = yAxisDown;
	eye = { 7.3, 1.3, -1.3 };
	at = { 0.0, 0.0, -1.0 };
	up = { 0.0, 1.0, 0.0 };
	thePlayer = player(1,eye.x, eye.y, eye.z, glm::vec3(0, 0, 0));
	environment = 
	{
		Entity_OBB(1,1,1,0, 0, 0, glm::vec3(0,90,0)),
		Entity_OBB(1,1,1,5, 0, -15, glm::vec3(0,90,0))
		
	};
	doors =
	{
		Supply_Point(0.5, 5.0, 0.0, -8.0, glm::vec3(0,90,0), true),
		Supply_Point(1.0, 4.0, 0.0, -23.0, glm::vec3(0,90,0), true),
		Supply_Point(1.0, 10.0, 0.0, -9.0, glm::vec3(0,90,0), true)
	};
	supplyPoints =
	{
		//glm::vec3(4.2f, -1.0f, -11.0f)
		Supply_Point(0.02,4.2f, 1.0f, -11.6f,glm::vec3(0,90,0),true)
	};
	testVec =
	{
		Entity_Sphere(0.5, 5.0, 0.0, -8.0, glm::vec3(0, 90, 0))
	};

	collisionHandler theCollisionHandler;
	

	window = setupRC(context);
	glewInitilisation();
	loadShader();
	initShaders();
	loadModel();
	loadSkybox(cubeTexFiles, &skybox);
	initMusic();
	
	draw();

}
void sceneManager::update()
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	/*float oldMouseX = windowWidth;
	  float oldMouseY = windowHeight;
	  POINT cp;
	  GetCursorPos(&cp);
	  mouseX = cp.x;
	  mouseY = cp.y;
	  if ((mouseX - oldMouseX) > 0) { rotation += 0.5f;  if ((mouseX - oldMouseX) > 0) rotation += 0.5f;}
	  else if ((mouseX - oldMouseX) < 0) { rotation -= 0.5f; if ((mouseX - oldMouseX) < 0) rotation -= 0.5f; }
	  SetCursorPos(windowWidth, windowHeight);*/

	
	///Handle Supply PointsE//
	for (int i = 0; i < supplyPoints.size(); i++)
	{
		if (theCollisionHandler.checkCollisionSphereVsSphere(thePlayer, supplyPoints[i]))
		{
			if ((supplyPoints[i].getType() == true) && (thePlayer.getHealth() < 110/*health cap*/))
			{
				health += 1;

			}
			else if ((supplyPoints[i].getType() == false) && (thePlayer.getAmmo() < 110/*ammo cap*/))
			{
				thePlayer.setAmmo(thePlayer.getAmmo() + 1);
			}
			cout << "playerHealth: " << thePlayer.getHealth() << " test" << endl;
			cout << "playerAmmo: " << thePlayer.getAmmo() << " test" << endl;
		}
	}

	//for (int i = 0; i < doors.size(); i++)
	//{
		//cout << "eX: " << thePlayer.getX() << "    eY: " << thePlayer.getY() << "    eZ: " << thePlayer.getZ() << endl;
		//cout << "pX: " << thePlayer.getX() << "    pY: " << thePlayer.getY() << "    pZ: " << thePlayer.getZ() << endl;
		if (theCollisionHandler.checkCollisionSphereVsSphere(thePlayer, doors[0])) /*players collides with environment[i]*/
		{
			if (key1Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				//doorOneHeight = testDoorVectorUp;
				doorOneHeight = yAxisUp;
			}
			else
			{
				cout << "Key not found" <<endl;
			}
			
		}

		if (theCollisionHandler.checkCollisionSphereVsSphere(thePlayer, doors[1])) /*players collides with environment[i]*/
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door collision" << endl << endl;
				doorTwoHeight = yAxisUp;
			}				
		}



		//if (theCollisionHandler.checkCollisionSphere((testVec[0]), rayMouseTest)) /*players collides with environment[i]*/
		//{
		//	cout << "sphere ray test" << endl;
		//}
		
	//}



	
	thePlayer.setHealth(health);
		
	if (keys[SDL_SCANCODE_Q])
	{
		rotation -= 1.0f;
	}
	if (keys[SDL_SCANCODE_E])
	{
		rotation += 1.0f;
	}
	if (keys[SDL_SCANCODE_1])
	{
		health -= 1;
		Sleep(100);
		cout << health << endl;
	}
	   	 
	if (keys[SDL_SCANCODE_W]) //forward
	{
		thePlayer.pos = moveForward(thePlayer.pos, rotation, 0.1f);
		//eye = moveForward(eye, rotation, 0.1f);
	}
	if (keys[SDL_SCANCODE_S]) //backward
	{
		thePlayer.pos = moveForward(thePlayer.pos, rotation, -0.1f);
		//eye = moveForward(eye, rotation, -0.1f);
	}
	if (keys[SDL_SCANCODE_A]) //left
	{
		thePlayer.pos = moveRight(thePlayer.pos, rotation, -0.1f);
		//eye = moveRight(eye, rotation, -0.1f);
	}
	if (keys[SDL_SCANCODE_D]) //right
	{
		thePlayer.pos = moveRight(thePlayer.pos, rotation, 0.1f);
		//eye = moveRight(eye, rotation, 0.1f);
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
		thePlayer.pos.y += 0.1f;
		//eye.y += 0.1;
	}

	for (int i = 0; i < environment.size(); i++)
	{
		//cout << "eX: " << thePlayer.getX() << "    eY: " << thePlayer.getY() << "    eZ: " << thePlayer.getZ() << endl;
		//cout << "pX: " << thePlayer.getX() << "    pY: " << thePlayer.getY() << "    pZ: " << thePlayer.getZ() << endl;
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, environment[i])) /*players collides with environment[i]*/
		{
			cout << "Environmental collision" << endl << endl;
			thePlayer.setX(eye.x);
			thePlayer.setY(eye.y);
			thePlayer.setZ(eye.z);
		}
		else
		{
			eye.x = thePlayer.getX();
			eye.y = thePlayer.getY();
			eye.z = thePlayer.getZ();
		}
	}

	

	if (keys[SDL_SCANCODE_F])
	{
		thePlayer.pos.y -= 0.1f;
		//eye.y -= 0.1;
	}


	if (keys[SDL_SCANCODE_1])
	{
		health -= 1;
		Sleep(100);
		cout << health << endl;
	}

	if (keys[SDL_SCANCODE_K])
	{
		rotation -= 1.0f;
	}
	if (keys[SDL_SCANCODE_L])
	{
		rotation += 1.0f;
	}

	//int mouseX, mouseY = 0;
	//SDL_GetMouseState(&mouseX, &mouseY);
	//rayMouseTest = glm::vec2(mouseX, mouseY);
	
	////SDL_GetRelativeMouseState(&mouseX, &mouseY);

	//if (mouseX > windowWidth/ 2 + 100)
	//{
	//	rotation += 0.5;
	//}
	////cout << mouseX <<"\n";
	//if (mouseX < windowWidth / 2 - 100)
	//{
	//	rotation -= 0.5f;
	//}

	//if (mouseY > windowHeight / 2 + 100)
	//{
	//	cout << "test";
	//	rotationY += 0.5f;
	//}

	

	//if (keys[SDL_SCANCODE_O] && key1Found)
	//{

	//	while (yoffset <= 3)
	//	{
	//		yoffset += 0.01f;
	//	}
	//}

	//if (keys[SDL_SCANCODE_P])
	//{

	//	while (yoffset1 <= 3)
	//	{
	//		yoffset1 += 0.01f;
	//	}
	//}

	//if (keys[SDL_SCANCODE_K] && key2Found)
	//{

	//	while (yoffset2 <= 3)
	//	{
	//		yoffset2 += 0.01f;
	//	}
	//}

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
sceneManager::~sceneManager()
{
	
}

void sceneManager::draw()
{
	glEnable(GL_CULL_FACE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  //if (walking == true)
	//{
	//	HCHANNEL ch = BASS_SampleGetChannel(samples[2], FALSE);
	//	sm->setAttributes(0, &ch, 0, 1.0, 0);
	//	if (!BASS_ChannelPlay(ch, FALSE))
	//		cout << "Can't play sample" << endl;
	//}

	
	//cout << eye.x << " " << eye.y << " " << eye.z << endl;

	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f * DEG_TO_RADIAN), 800.0f / 600.0f, 0.1f, 150.0f);

	glm::mat4 view(1.0f);					//Only here for skybox, nt actually needed

	glm::mat4 modelView = glm::mat4(1.0f);
	modelStack.push(modelView);
	//modelView = glm::lookAt(eye, at, up);
	

	at = moveForward(eye, rotation, 1.0f);
	modelStack.top() = glm::lookAt(eye, at, up);




	glViewport(0.f, 0.0f, windowWidth, windowHeight);
	glm::vec4 viewport = glm::vec4(0, 0, windowWidth, windowHeight);
	/////////////////////////////////////////////////////////////////////////////////// RAY
	//mouseRay(projection, modelStack.top());
	reverseMouse(glm::vec3(0, 0, 0), modelStack.top(), projection, viewport);
	//////////////////////////////////////////////////////////////////////////////////





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


	ourShader->setVec3("viewPos", at);
	ourShader->setVec3("pointLights[0].position", modelStack.top() * glm::vec4(lightPosition[0] , 1.0));	
	ourShader->setVec3("pointLights[1].position", modelStack.top() * glm::vec4(lightPosition[1] , 1.0));
	ourShader->setVec3("pointLights[2].position", modelStack.top() * glm::vec4(lightPosition[2] , 1.0));
	ourShader->setVec3("pointLights[3].position", modelStack.top() * glm::vec4(lightPosition[3] , 1.0));
	ourShader->setVec3("pointLights[4].position", modelStack.top() * glm::vec4(lightPosition[4], 1.0));
	ourShader->setVec3("pointLights[5].position", modelStack.top() * glm::vec4(lightPosition[5], 1.0));
	ourShader->setVec3("pointLights[6].position", modelStack.top() * glm::vec4(lightPosition[6], 1.0));
	ourShader->setVec3("pointLights[7].position", modelStack.top() * glm::vec4(lightPosition[7], 1.0));
	ourShader->setVec3("pointLights[8].position", modelStack.top() * glm::vec4(lightPosition[8], 1.0));
	ourShader->setVec3("pointLights[9].position", modelStack.top() * glm::vec4(lightPosition[9], 1.0));
	ourShader->setVec3("pointLights[10].position", modelStack.top() * glm::vec4(lightPosition[10], 1.0));
	ourShader->setVec3("pointLights[11].position", modelStack.top() * glm::vec4(lightPosition[11], 1.0));
	ourShader->setVec3("pointLights[12].position", modelStack.top() * glm::vec4(lightPosition[12], 1.0));
	ourShader->setVec3("pointLights[13].position", modelStack.top() * glm::vec4(lightPosition[13], 1.0));
	ourShader->setVec3("pointLights[14].position", modelStack.top() * glm::vec4(lightPosition[14], 1.0));
	ourShader->setVec3("pointLights[15].position", modelStack.top() * glm::vec4(lightPosition[15], 1.0));
	ourShader->setVec3("pointLights[16].position", modelStack.top() * glm::vec4(lightPosition[16], 1.0));
	ourShader->setVec3("pointLights[17].position", modelStack.top() * glm::vec4(lightPosition[17], 1.0));
	ourShader->setVec3("pointLights[18].position", modelStack.top() * glm::vec4(lightPosition[18], 1.0));
	ourShader->setVec3("pointLights[19].position", modelStack.top() * glm::vec4(lightPosition[19], 1.0));
	ourShader->setVec3("pointLights[20].position", modelStack.top() * glm::vec4(lightPosition[20], 1.0));
	ourShader->setVec3("pointLights[21].position", modelStack.top() * glm::vec4(lightPosition[21], 1.0));
	ourShader->setVec3("pointLights[22].position", modelStack.top() * glm::vec4(lightPosition[22], 1.0));


	
	spawnChargers();
	spawnBay();
finalMap();
bottomLeftMap();
BottomRightMap();
	middleMap();
	secondHallwayandTwoRooms();
	firstRoom();
	hallwayFromFirstRoom();
	secondRoom();
	thirdHallwayintoRoom();
	spawnShips();
		
	cubeShader->use();
	cubeShader->setMat4("projection", projection);
	cubeShader->setMat4("view", view);			//Doesnt actually need to be passed it, will dfault itself.

	for (int i = 0; i < 23; i++)
	{
		modelStack.push(modelStack.top());
		modelStack.top() = glm::translate(modelStack.top(), lightPosition[i]);
		modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.05f, 0.05f, 0.05f));
		cubeShader->setUniformMatrix4fv("modelView", glm::value_ptr(modelStack.top()));
		cubeTest->modelDraw(*ourShader);
		modelStack.pop();
	}

	SDL_GL_SwapWindow(window);  //Swap buffers
}

void sceneManager::BottomRightMap()
{
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(38.1, 1, -12.85));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(35.5, 1, -12.85));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(22.9, 1, -52.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(25.4, 3, -52.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(27.9, 1, -52.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(22.9, 1, -42.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(25.4, 1, -42.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(27.9, 1, -42.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.8, 1, -50.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.8, 1, -47.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.8, 1, -45.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(28.3, 1, -57.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(28.3, 1, -55.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(28.3, 1, -52.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20, 3, -47.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20, 1, -50.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20, 1, -45.3));

	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20, 1, -45));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	//////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(22.5, 1, -57.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(22.5, 1, -55.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();



	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(22.5, 1, -52.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
}

void sceneManager::bottomLeftMap()
{

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23, 1, -22.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(25.5, 1, -22.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(28, 1, -22.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.5, 1, -22.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(33, 3, -22.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(35.5, 1, -22.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	///////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23, 1, -33));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(25.5, 1, -33));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(28, 1, -33));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.5, 1, -33));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(33, 1, -33));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(35.5, 1, -33));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(27.5, 1, -30.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(27.5, 2, -27.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(27.5, 1, -25.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(27.5, 1, -22.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(27.5, 1, -20.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(27.5, 1, -17.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20, 1, -30.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20, 2, -27.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20, 1, -25.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.9, 1, -30.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.9, 2, -27.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.9, 1, -25.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(38.4, 1, -30.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(38.4, 1, -27.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(38.4, 1, -25.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	///////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(38.4, 1, -22.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(38.4, 1, -20.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(38.4, 1, -17.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();



	//////////







	/////////////////
	/////////////
	modelStack.push(modelStack.top());														//Ship for docking Bay
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-14.7f, 1.0f, -4.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.1, 0.1, 0.1));
	modelStack.top() = glm::rotate(modelStack.top(), float(270 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[10].modelDraw(*ourShader);
	modelStack.pop();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.4, 1, -9.88));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Ship piece

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-18.0f, 2.7f, -23.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(3.0, 3.0f, 3.0f));
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.0f, -0.10f));
	ourShader->setMat4("modelView", modelStack.top());
	floorRoofPlane->modelDraw(*ourShader);
	modelStack.pop();



	//modelStack.push(modelStack.top());
	//gameObjects[7].setPosition(glm::vec3(eye.x+0.3, eye.y, eye.z - 0.4));
	//modelStack.top() = glm::translate(modelStack.top(), gameObjects[7].getPosition());
	//modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.05f, 0.05f, 0.05f));
	//modelStack.top() = glm::rotate(modelStack.top(), float(mouseX * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	//ourShader->setMat4("modelView", modelStack.top());
	//gameObjects[7].modelDraw(*ourShader);
	//modelStack.pop();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////Floor fill 1
	groundDraw();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ???

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(7.7, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(10.2, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.7, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(7.7, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(10.2, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.7, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.4, 1, -35.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.4, 1, -32.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.4, 1, -30.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  ??

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2, 1, -25));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.4, 1, -40.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.4, 1, -42.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(15.3, 1, -45.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(17.8, 1, -45.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20.3, 3, -45.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();






	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(7.7, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(10.2, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.7, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(7.7, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(10.2, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.7, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.4, 1, -35.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(12.4, 1, -32.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(15.3, 1, -29.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(17.8, 1, -29.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20.3, 3, -29.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.3, 1, -14.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(35.6, 1, -14.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 1, -15.15));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(35.9, 1, -15.15));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 1, -12.65));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(35.9, 1, -12.65));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(33.0, 3, -9.85));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.1, 1, 1));
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	//////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 1, -32.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 1, -35.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 1, -37.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 1, -40.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 1, -42.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 1, -50.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 3, -47.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 1, -45.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20.4, 1, -52.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(17.5, 1, -50.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(17.5, 1, -47.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(17.5, 1, -45.3));

	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(17.5, 1, -45));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 1, -30.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 2, -27.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(23.18, 1, -25.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(17.5, 1, -30.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(17.5, 1, -27.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(17.5, 1, -25.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(20.4, 1, -22.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
}







void sceneManager::finalMap()
{
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(25.4, 3, -60.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(25.4, 1, -67.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(27.9, 1, -67.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.4, 1, -67.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(32.9, 1, -67.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(35.4, 1, -67.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.9, 1, -67.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(40.4, 1, -67.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(22.5, 1, -65.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(22.5, 1, -62.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();



	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(22.5, 1, -60.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 1, -65.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 3, -62.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 1, -60.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(33, 1, -65.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(33, 3, -62.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(33, 1, -60.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -65.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 3, -62.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -60.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(40.8, 1, -65.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(40.8, 3, -62.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(40.8, 1, -60.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -65.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -62.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -60.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -57.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -55.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -52.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -50.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -47.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -37.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -35.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -32.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -30.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -27.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -25.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -22.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -20.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -17.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -15.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -12.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////////////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -57.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -55.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -52.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -50.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -47.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -37.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -35.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -32.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -30.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -27.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -25.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -22.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -20.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -17.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -15.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(37.8, 1, -12.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(28, 1, -57.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.5, 1, -57.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(33, 1, -57.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(35.5, 1, -57.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(38, 1, -57.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43, 1, -37.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(38.1, 1, -37.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(35.6, 1, -37.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(33.1, 1, -37.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	///
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.2, 1, -40.15));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.2, 1, -42.65));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30.2, 1, -45.15));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(33.1, 1, -48));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(35.6, 1, -48));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(38.05, 1, -48));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.05, 1, -48));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(45.8, 1, -45.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(45.8, 1, -42.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(45.8, 1, -40.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////////////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -10));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -7.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, -2.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(43.3, 1, 0));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	//////////////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 1, -10.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 1, -7.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 1, -5.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 1, -2.55));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 1, -0.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(30, 1, -2.45));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
}
void sceneManager::groundDraw()
{


	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(6.6f, 0.0f, -3.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(6.6f, 0.0f, -13.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(6.6f, 0.0f, -23.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(6.6f, 0.0f, -33.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(6.6f, 0.0f, -43.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////Floor fill 2

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-3.4f, 0.0f, -3.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-3.4f, 0.0f, -13.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-3.4f, 0.0f, -23.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-3.4f, 0.0f, -33.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-3.4f, 0.0f, -43.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-3.4f, 0.0f, -53.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////Floor fill 3

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-13.4f, 0.0f, -3.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-13.4f, 0.0f, -13.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-13.4f, 0.0f, -23.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-13.4f, 0.0f, -33.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-13.4f, 0.0f, -43.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-13.4f, 0.0f, -53.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.5, 0.5f, 0.5f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();
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

void sceneManager::firstRoom()
{
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0, 1, 0));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0, 1, -2.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0, 1, -5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0, 1, -7.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.8, 1, -10));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.3, doorOneHeight, -10));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(7.8, 1, -10));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(10.3, 1, -10));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	/*modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(13.2, 1, 0));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();*/


	modelStack.push(modelStack.top());
	gameObjects[0].setPosition(glm::vec3(13.2, 1, -2.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[0].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[0].modelDraw(*ourShader);
	modelStack.pop();

	/*modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(13.2, 1, -5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();*/

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(13.2, 1, -7.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.8, 1, 2.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.3, 1, 2.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(7.8, 1, 2.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(10.3, 1, 2.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
}

void sceneManager::hallwayFromFirstRoom()
{
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -9.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -12.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -14.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -17.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -20));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -22.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -25));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	///////////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -9.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());

	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -12.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());

	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -14.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());

	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -17.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());

	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -20));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());

	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.5, doorTwoHeight, -22.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.5, 1, -25));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	///////////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.3, 1 + yoffset1, -27.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
}

void sceneManager::secondRoom()
{
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.62, 1, -28.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.12, 1, -28.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.38, 1, -28.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.62, 1, -17.35));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.12, 1, -17.35));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.38, 1, -17.35));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.5, 1, -25.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.5, 1, -20.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.1, 1, -25.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.1, 1, -20.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5.1, 1, -25.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5.1, 1, -20.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top()); /////// THIS IS THE DOOR FIGUERE OUT A WAY TO GET IT WORKING UMAR -UA
	gameObjects[1].setPosition(glm::vec3(-5.1, 3, -22.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);

	modelStack.pop(); //// MAYBE WONT BE NEEDED, SPEAK WITH GROUP
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.1, 3, -22.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
}

void sceneManager::secondHallwayandTwoRooms()
{
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.88, 1, -28.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.38, 1, -28.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.88, 1, -28.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.38, 1, -28.05));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////////////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.38, 1, -17.35));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.88, 1, -17.35));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.38, 1, -17.35));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.38, 1, -9.85));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelview", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.88, 1, -9.85));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.38, 1, -9.85));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	///////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.38, 1, -20.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.88, 1, -20.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.38, 1, -20.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.1, 1, -22.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.1, 1, -20.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.1, 1, -17.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.1, 1, -15.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.1, 1, -12.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.1, 1, -10.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 1, -7.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.6, 1, -10.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	/////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.6, 1, -12.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.6, 3, -15.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.6, 1, -17.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	//
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.5, 1, -12.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.5, 3, -15.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.5, 1, -17.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.5, 1, -20.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.5, 3, -22.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.5, 1, -25.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.6, 1, -20.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.6, 3, -22.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.6, 1, -25.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-15.2, 1, -20.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-15.2, 3, -22.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-15.2, 1, -25.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////////////#
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-15.2, 1, -17.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-15.2, 1, -15.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-15.2, 1, -12.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.2, 1, -17.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.2, 1, -15.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.2, 1, -12.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	///////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.2, 1, -20.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.2, 3, -22.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.2, 1, -25.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
}

void sceneManager::thirdHallwayintoRoom()
{
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-18, 1, -20.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-18, 1, -22.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-18, 1, -25.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-18, 1, -27.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-18, 1, -30.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-18, 1, -32.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-15.1, 1, -17.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.2, 1, -27.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.2, 1, -30.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.2, 1, -32.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-15.1, 3, -35.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	/////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-17.8, 1, -32.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.5, 1, -32.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(-90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	////////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-20.8, 1, -35.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-20.8, 1, -37.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-20.8, 1, -40.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-8.5, 1, -31.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	///////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.6, 1, -35.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.6, 3, -37.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.6, 1, -40.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	///////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.5, 1, -43));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-15.4, 1, -43));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-15, 1, -43));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-17.95, 1, -43));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

}

void sceneManager::middleMap()
{
	///////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -50));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -47.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(8.1, 1, -45));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.55, 1, -50));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.55, 3, -47.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.55, 1, -45));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	//////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.8, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.3, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.8, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	//
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.8, 1, -52.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.3, 1, -52.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.8, 1, -52.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.2, 1, -52.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.7, 1, -52.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.2, 1, -52.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	///
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.2, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.7, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.2, 1, -40.4));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	///////////



	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.8, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.3, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.8, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-9.8, 1, -42.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-7.3, 1, -42.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-4.8, 1, -42.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.2, 1, -42.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.7, 1, -42.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.2, 1, -42.3));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	//
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.2, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.7, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.2, 1, -34.8));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	///////////

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.7, 1, -45.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.7, 1, -47.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-12.7, 1, -50.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-1.95, 1, -45.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-1.95, 3, -47.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-1.95, 1, -50.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 1, -45.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 3, -47.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 1, -50.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	//

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.5, 1, -45.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.5, 3, -47.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.5, 1, -50.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2.4, 1, -52.9));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	///
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 1, -42.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 1, -40.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 3, -37.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-2, 3, -37.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 1, -35.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 1, -32.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 1, -30.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(-5, 1, -27.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	/////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.5, 1, -42.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.5, 1, -40.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.5, 3, -37.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.5, 3, -37.7));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.5, 1, -35.2));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.3, 1, -35.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.8, 1, -35.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.3, 1, -35.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(7.8, 1, -35.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(10.3, 1, -35.5));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	///////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(0.3, 1, -25));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(2.8, 1, -25));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(5.3, 1, -25));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(7.8, 1, -25));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(10.3, 1, -25));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////////////////
	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(13, 1, -32.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(13, 1, -30.1));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	gameObjects[1].setPosition(glm::vec3(13, 1, -27.6));
	modelStack.top() = glm::translate(modelStack.top(), gameObjects[1].getPosition());
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, -0.1f, 0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
	//////////////////
}

void sceneManager::spawnChargers()
{
	modelStack.push(modelStack.top());																							// Corridor 1 - Health
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.2f, -1.0f, -11.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());																							// Corridor 1 - Ammo
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.2f, -1.0f, -12.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[5].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																							// Corridor 2 - Health
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-5.9f, -1.0f, -11.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																							// Room 2 - Ammo
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-13.5f, -1.0f, -17.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(270.0 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[5].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																							// Room 4 - Health
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-13.0f, -1.0f, -41.2f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																							// Room 4 - Ammo
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-12.0f, -1.0f, -34.1f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[5].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																							// Corridor 5 - Health
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-3.2f, -1.0f, -40.2f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(270 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																							// Corridor 5 - Ammo
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-2.2f, -1.0f, -51.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[5].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																							// Corridor 6 - Ammo
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.5f, -1.0f, -38.65f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0 * DEG_TO_RADIAN), glm::vec3(0.0f, -0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[5].modelDraw(*ourShader);
	modelStack.pop();


}

void sceneManager::spawnBay()
{
	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(2.7f, 0.0f, 0.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0f, 1.0f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[6].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(2.7f, 0.0f, -3.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0f, 1.0f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[6].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(2.7f, 0.0f, -6.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0f, 1.0f));
	modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[6].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(10.5f, 0.0f, 0.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0f, 1.0f));
	modelStack.top() = glm::rotate(modelStack.top(), float(270 * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[6].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(10.5f, 0.0f, -3.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0f, 1.0f));
	modelStack.top() = glm::rotate(modelStack.top(), float(270 * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[6].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(10.5f, 0.0f, -6.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0f, 1.0f));
	modelStack.top() = glm::rotate(modelStack.top(), float(270 * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[6].modelDraw(*ourShader);
	modelStack.pop();
}

void sceneManager::spawnShips()
{

	//modelStack.push(modelStack.top());														//Ship for docking Bay
	//modelStack.top() = glm::translate(modelStack.top(), glm::vec3(2.7f, 0.0f, 0.3f));
	//modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.01, 0.01f, 0.01f));
	//modelStack.top() = glm::rotate(modelStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	//ourShader->setMat4("modelView", modelStack.top());
	//gameObjects[8].modelDraw(*ourShader);
	//modelStack.pop();

	modelStack.push(modelStack.top());														//Ship for docking Bay
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(161.0, -4.0f, 1.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.1, 0.1f, 0.1f));
	modelStack.top() = glm::rotate(modelStack.top(), float(0.0 * DEG_TO_RADIAN), glm::vec3(-0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[8].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());														//Ship for docking Bay
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-4.7f, 1.0f, -4.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.1, 0.1, 0.1));
	modelStack.top() = glm::rotate(modelStack.top(), float(270 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[9].modelDraw(*ourShader);
	modelStack.pop();
}
