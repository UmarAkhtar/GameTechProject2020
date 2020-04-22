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
	
	skyboxModel = make_shared<Model>("../GameTechProject/cube.obj");


	const Uint8* keys = SDL_GetKeyboardState(NULL);


	gameObjects.push_back(Model("../GameTechProject/models/Wall/Ship.obj"));										// [0] Ship Environment
	gameObjects.push_back(Model("../GameTechProject/models/Wall/Door.obj"));											// [1] Doors
	gameObjects.push_back(Model("../GameTechProject/models/chargers/health/SciFi_Health.obj"));							// [2] Health charger
	gameObjects.push_back(Model("../GameTechProject/models/chargers/ammo/SciFi_Ammo.obj"));								// [3] Ammo charger
	gameObjects.push_back(Model("../GameTechProject/models/Bay/bed/SciFi_Bed.obj"));									// [4] Beds
	gameObjects.push_back(Model("../GameTechProject/models/gun/gun.obj"));												// [5] Gun
	gameObjects.push_back(Model("../GameTechProject/models/dockingBay/Spaceship.obj"));									// [6] Small ship
	gameObjects.push_back(Model("../GameTechProject/models/dockingBay/Luminaris_OBJ.obj"));								// [7] Big ship
	gameObjects.push_back(Model("../GameTechProject/cube.obj"));														// [8] Cube for light
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

	ourShader->setVec3("pointLights[24].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[24].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[24].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[24].constant", 1.0f);
	ourShader->setFloat("pointLights[24].linear", 0.09);
	ourShader->setFloat("pointLights[24].quadratic", 0.032);

	ourShader->setVec3("pointLights[25].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[25].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[25].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[25].constant", 1.0f);
	ourShader->setFloat("pointLights[25].linear", 0.09);
	ourShader->setFloat("pointLights[25].quadratic", 0.032);

	ourShader->setVec3("pointLights[26].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[26].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[26].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[26].constant", 1.0f);
	ourShader->setFloat("pointLights[26].linear", 0.09);
	ourShader->setFloat("pointLights[26].quadratic", 0.032);

	ourShader->setVec3("pointLights[27].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[27].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[27].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[27].constant", 1.0f);
	ourShader->setFloat("pointLights[27].linear", 0.09);
	ourShader->setFloat("pointLights[27].quadratic", 0.032);

	ourShader->setVec3("pointLights[28].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[28].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[28].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[28].constant", 1.0f);
	ourShader->setFloat("pointLights[28].linear", 0.09);
	ourShader->setFloat("pointLights[28].quadratic", 0.032);

	ourShader->setVec3("pointLights[29].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[29].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[29].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[29].constant", 1.0f);
	ourShader->setFloat("pointLights[29].linear", 0.09);
	ourShader->setFloat("pointLights[29].quadratic", 0.032);

	ourShader->setVec3("pointLights[30].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[30].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[30].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[30].constant", 1.0f);
	ourShader->setFloat("pointLights[30].linear", 0.09);
	ourShader->setFloat("pointLights[30].quadratic", 0.032);

	ourShader->setVec3("pointLights[31].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[31].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[31].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[31].constant", 1.0f);
	ourShader->setFloat("pointLights[31].linear", 0.09);
	ourShader->setFloat("pointLights[31].quadratic", 0.032);

	ourShader->setVec3("pointLights[32].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[32].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[32].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[32].constant", 1.0f);
	ourShader->setFloat("pointLights[32].linear", 0.09);
	ourShader->setFloat("pointLights[32].quadratic", 0.032);

	ourShader->setVec3("pointLights[33].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[33].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[33].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[33].constant", 1.0f);
	ourShader->setFloat("pointLights[33].linear", 0.09);
	ourShader->setFloat("pointLights[33].quadratic", 0.032);

	ourShader->setVec3("pointLights[34].ambient", 0.02f, 0.0f, 0.0f);
	ourShader->setVec3("pointLights[34].diffuse", 0.3f, 0.3f, 0.3f);
	ourShader->setVec3("pointLights[34].specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("pointLights[34].constant", 1.0f);
	ourShader->setFloat("pointLights[34].linear", 0.09);
	ourShader->setFloat("pointLights[34].quadratic", 0.032);
	
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
	//doorOneHeight = testDoorVectorDown;
	//doorTwoHeight = testDoorVectorDown;

	doorOneHeight = yAxisDown;
	doorTwoHeight = yAxisDown;
	eye = {-67.0, 1.3, 3.3 };
	at = { 0.0, 0.0, -1.0 };
	up = { 0.0, 1.0, 0.0 };
	thePlayer = player(1,eye.x, eye.y, eye.z, glm::vec3(0, 0, 0));
	environment = 
	{
		Entity_OBB(-0.5,1.0,1,-14.5, 1.0, -3.6, glm::vec3(0,0,45)),
		Entity_OBB(0.01,0.01,1,5, 1.0, -15, glm::vec3(0,0,0))
		
	};
	doors =
	{
		Supply_Point(0.2, 5.0, doorOneHeight, -8.0, glm::vec3(0,90,0), true),
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
			if (key1Found == true /*&& (keys[SDL_SCANCODE_E])*/)
			{
				cout << "Door open" << endl << endl;
				//doorOneHeight = testDoorVectorUp;
				doors[0] = Supply_Point(0.2, 5.0, doorOneHeight, -8.0, glm::vec3(0, 90, 0), true);
				doorOneHeight = yAxisUp;
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Key not found" <<endl;			
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
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


	
	cout << eye.x << " " << eye.y << " " << eye.z << endl;

	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f * DEG_TO_RADIAN), 800.0f / 600.0f, 0.1f, 150.0f);

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


	ourShader->setVec3("viewPos", at);
	ourShader->setVec3("pointLights[0].position", modelStack.top() * glm::vec4(lightPosition[0], 1.0));
	ourShader->setVec3("pointLights[1].position", modelStack.top() * glm::vec4(lightPosition[1], 1.0));
	ourShader->setVec3("pointLights[2].position", modelStack.top() * glm::vec4(lightPosition[2], 1.0));
	ourShader->setVec3("pointLights[3].position", modelStack.top() * glm::vec4(lightPosition[3], 1.0));
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
	ourShader->setVec3("pointLights[23].position", modelStack.top() * glm::vec4(lightPosition[23], 1.0));
	ourShader->setVec3("pointLights[24].position", modelStack.top() * glm::vec4(lightPosition[24], 1.0));
	ourShader->setVec3("pointLights[25].position", modelStack.top() * glm::vec4(lightPosition[25], 1.0));
	ourShader->setVec3("pointLights[26].position", modelStack.top() * glm::vec4(lightPosition[26], 1.0));
	ourShader->setVec3("pointLights[27].position", modelStack.top() * glm::vec4(lightPosition[27], 1.0));
	ourShader->setVec3("pointLights[28].position", modelStack.top() * glm::vec4(lightPosition[28], 1.0));
	ourShader->setVec3("pointLights[29].position", modelStack.top() * glm::vec4(lightPosition[29], 1.0));
	ourShader->setVec3("pointLights[30].position", modelStack.top() * glm::vec4(lightPosition[30], 1.0));
	ourShader->setVec3("pointLights[31].position", modelStack.top() * glm::vec4(lightPosition[31], 1.0));
	ourShader->setVec3("pointLights[32].position", modelStack.top() * glm::vec4(lightPosition[32], 1.0));
	ourShader->setVec3("pointLights[33].position", modelStack.top() * glm::vec4(lightPosition[33], 1.0));
	



	modelStack.push(modelStack.top());																							//Ship Environment
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(0.0f, 0.0f, 0.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[0].modelDraw(*ourShader);
	modelStack.pop();

	spawnBeds();
	spawnDoors();
	spawnChargers();
		
	cubeShader->use();
	cubeShader->setMat4("projection", projection);
	cubeShader->setMat4("view", view);			//Doesnt actually need to be passed it, will dfault itself.

	for (int i = 0; i < 34; i++)																									//Lights
	{

		modelStack.push(modelStack.top());																							
		modelStack.top() = glm::translate(modelStack.top(), lightPosition[i]);
		modelStack.top() = glm::scale(modelStack.top(), glm::vec3(0.05f, 0.05f, 0.05f));
		cubeShader->setMat4("modelView", modelStack.top());
		gameObjects[8].modelDraw(*ourShader);
		modelStack.pop();
	}

	SDL_GL_SwapWindow(window);  //Swap buffers
}

void sceneManager::spawnBeds()
{
	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-70.0f, 0.0f, -7.0f));							// Blender x= x, y = z, z = y
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-67.5f, 0.0f, -7.0f));							// Blender x= x, y = z, z = y
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-65.0f, 0.0f, -7.0f));							// Blender x= x, y = z, z = y
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-62.5f, 0.0f, -7.0f));							// Blender x= x, y = z, z = y
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-70.0f, 0.0f, 2.0f));							// Blender x= x, y = z, z = y
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-67.5f, 0.0f, 2.0f));							// Blender x= x, y = z, z = y
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-65.0f, 0.0f, 2.0f));							// Blender x= x, y = z, z = y
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-62.5f, 0.0f, 2.0f));							// Blender x= x, y = z, z = y
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180.0f * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[4].modelDraw(*ourShader);
	modelStack.pop();
}

void sceneManager::spawnDoors()
{
	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.0f, 0.0f, -0.5f));							// Blender x= x, y = z, z = y
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-14.0f, 0.0f, -9.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(22.0f, 0.0f, 11.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(49.0f, 0.0f, 26.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(49.0f, 0.0f, 38.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(11.0f, 0.0f, -23.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-11.0f, 0.0f, 11.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.0f, 0.0f, -3.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.0f, 0.0f, -21.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-11.0f, 0.0f, 23.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.0f, 0.0f, -15.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-50.0f, 0.0f, -21.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.0f, 0.0f, -33.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.0f, 0.0f, -31.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.0f, 0.0f, -18.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.0f, 0.0f, -13.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(25.0f, 0.0f, -18.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(25.0f, 0.0f, -13.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-59.5f, 0.0f, -1.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-19.5f, 0.0f, -1.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-1.5f, 0.0f, -37.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-5.5f, 0.0f, -16.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-1.5f, 0.0f, 8.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(12.5f, 0.0f, 8.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(27.5f, 0.0f, 17.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-16.5f, 0.0f, 29.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-28.5f, 0.0f, 29.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.5f, 0.0f, 29.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.5f, 0.0f, 41.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.5f, 0.0f, 41.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(15.f, 0.0f, 41.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
}

void sceneManager::spawnChargers()
{	
	modelStack.push(modelStack.top());																								// Health corridor 1
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-54.05f, -1.0f, -2.3f));							
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Ammo corridor 1
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-50.05f, -1.0f, -2.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Health corridor 2
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-55.05f, -1.0f, -20.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();
	
	modelStack.push(modelStack.top());																								// Ammo Room 2
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-44.05f, -1.0f, -32.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Ammo Room 4
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-0.3f, -1.0f, -33.2f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Health room 4
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(11.3f, -1.0f, -33.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(270 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Health corridor 5
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(10.3f, -1.0f, -17.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Ammo corridor 5
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(29.3f, -1.0f, -16.1f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(270 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Ammo corridor 6
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(2.7f, -1.0f, -3.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());																								// Health room  9
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.7f, -1.0f, 9.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Ammo corridor 7
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-14.3f, -1.0f, 9.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Health room  16
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-15.3f, -1.0f, 20.8f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Health corriddor 12
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-33.0f, -1.0f, 27.7f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Ammo corridor 12
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-33.0f, -1.0f, 30.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Health corriddor 11
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-33.0f, -1.0f, 39.7f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Ammo corridor 11
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-33.0f, -1.0f, 42.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());																								// Health docking
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-51.0f, -1.0f, 21.7f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Ammo docking
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-42.0f, -1.0f, 42.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Health room 13
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(8.0f, -1.0f, 33.7f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Ammo room 13
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(12.0f, -1.0f, 33.7f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Ammo Room 12
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(44.7f, -1.0f, 34.8f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																								// Health room 12
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(54.0f, -1.0f, 27.7f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[2].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());																								// Ammo corridor 9
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(30.7f, -1.0f, 18.3f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(2.0, 2.0, 2.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(180 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[3].modelDraw(*ourShader);
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

