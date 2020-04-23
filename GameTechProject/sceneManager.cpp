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


	gameObjects.push_back(Model("../GameTechProject/models/Wall/Ship.obj"));											// [0] Ship Environment
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
	doorThreeHeight = yAxisDown;
	doorFourHeight = yAxisDown;
	doorFiveHeight = yAxisDown;
	doorSixHeight = yAxisDown;
	doorSevenHeight = yAxisDown;
	doorEightHeight = yAxisDown;
	doorNineHeight = yAxisDown;
	doorTenHeight = yAxisDown;
	door11Height = yAxisDown;
	door12Height = yAxisDown;
	door13Height = yAxisDown;
	door14Height = yAxisDown;
	door15Height = yAxisDown;
	door16Height = yAxisDown;
	door17Height = yAxisDown;
	door18Height = yAxisDown;
	door19Height = yAxisDown;
	door20Height = yAxisDown;
	door21Height = yAxisDown;
	door22Height = yAxisDown;
	door23Height = yAxisDown;
	door24Height = yAxisDown;
	door25Height = yAxisDown;
	door26Height = yAxisDown;
	door27Height = yAxisDown;
	door28Height = yAxisDown;
	door29Height = yAxisDown;
	door30Height = yAxisDown;

	//eye = {-67.0, 1.3, 3.3 };
	eye = { -48.0, 1.3, 31.0 };
	at = { 0.0, 0.0, -1.0 };
	up = { 0.0, 1.0, 0.0 };
	thePlayer = player(1,eye.x, eye.y, eye.z, glm::vec3(0, 0, 0));
	environment = 
	{
		Entity_OBB(170.0, 1.0, 2.0, 5.5, 0.0, 43.5, glm::vec3(0,0,45)),									// The docking south wall
		Entity_OBB(1.0, 70.0, 2.0, -58.5, 0.0, 32.0, glm::vec3(0,0,45)),								// Docking West wall
		Entity_OBB(60.0, 1.0, 2.0, -47.0, 0.0, 20.8, glm::vec3(0,0,45)),								// Docking North wall
		Entity_OBB(1.0, 3.7, 2.0, -35.5, 0.0, 25.0, glm::vec3(0,0,45)),									// Docking East wall North of door
		Entity_OBB(1.0, 7.0, 2.0, -35.5, 0.0, 35.0, glm::vec3(0,0,45)),									// Docking East between walls


		Entity_OBB(7.0, 1.0, 2.0, -32.0, 0.0, 26.5, glm::vec3(0,0,45)),									//C12 North wall
		Entity_OBB(7.0, 1.0, 2.0, -32.0, 0.0, 31.5, glm::vec3(0,0,45)),									//C12 South wall

		Entity_OBB(7.0, 1.0, 2.0, -23.0, 0.0, 23.8, glm::vec3(0,0,45)),									// C12 North wall
	};
	doors =
	{
		Entity_OBB(1.0f, 2.0f, 1.0f, -59.5, doorOneHeight, -1.0, glm::vec3(0,0,45)),				// [0] Door bay
		Entity_OBB(5.0f, 2.0f, 1.0f, -59.5, doorOneHeight, -1.0, glm::vec3(0,0,45)),				// [1] Door bay
		Entity_OBB(2.0f, 1.0f, 1.0f, -35.0, doorTwoHeight, -3.5, glm::vec3(0,0,45)),				// [2] C1 - R1 Door
		Entity_OBB(2.0f, 5.0f, 1.0f, -35.0, doorTwoHeight, -3.5, glm::vec3(0,0,45)),				// [3] C1 - R1 Collider for door E press
		Entity_OBB(1.0f, 2.0, 1.0f, -19.5, doorThreeHeight, -1.0, glm::vec3(0,0,45)),				// [4] C1 - R8 Door
		Entity_OBB(5.0f, 2.0, 1.0f, -19.5, doorThreeHeight, -1.0, glm::vec3(0,0,45)),				// [5] C1 - R8 Collder for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, -35.0, doorFourHeight, -15.5, glm::vec3(0,0,45)),				// [6] R1 - C2 Door
		Entity_OBB(2.0f, 5.0f, 1.0f, -35.0, doorFourHeight, -15.5, glm::vec3(0,0,45)),				// [7] R1 - C2 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, -35.0, doorFiveHeight, -21.5, glm::vec3(0,0,45)),				// [8] C2 - R3 Door
		Entity_OBB(2.0f, 5.0f, 1.0f, -35.0, doorFiveHeight, -21.5, glm::vec3(0,0,45)),				// [9] C2 - R3 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, -50.0, doorSixHeight, -21.5, glm::vec3(0,0,45)),				// [10] C2 - R2 Door
		Entity_OBB(2.0f, 5.0f, 1.0f, -50.0, doorSixHeight, -21.5, glm::vec3(0,0,45)),				// [11] C2 - R2 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, -35.0, doorSevenHeight, -33.5, glm::vec3(0,0,45)),				// [12] R3 - C3 Door
		Entity_OBB(2.0f, 5.0f, 1.0f, -35.0, doorSevenHeight, -33.5, glm::vec3(0,0,45)),				// [13] R3 - C3 Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, -1.5, doorEightHeight, -37.5, glm::vec3(0,0,45)),				// [14] C3 - R4 Door
		Entity_OBB(5.0f, 1.0f, 1.0f, -1.5, doorEightHeight, -37.5, glm::vec3(0,0,45)),				// [15] C3 - R4 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, 4.0, doorNineHeight, -31.5, glm::vec3(0,0,45)),				// [16] R4 - C4 Door
		Entity_OBB(1.0f, 5.0f, 1.0f, 4.0, doorNineHeight, -31.5, glm::vec3(0,0,45)),				// [17] R4 - C4 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, 4.0, doorTenHeight, -18.5, glm::vec3(0,0,45)),					// [18] C4 - C5 Door
		Entity_OBB(1.0f, 5.0f, 1.0f, 4.0, doorTenHeight, -18.5, glm::vec3(0,0,45)),					// [19] C4 - C5 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, 4.0, door11Height, -13.5, glm::vec3(0,0,45)),					// [20] C5 - C6 Door
		Entity_OBB(1.0f, 5.0f, 1.0f, 4.0, door11Height, -13.5, glm::vec3(0,0,45)),					// [21] C5 - C6 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, 25.0, door12Height, -18.5, glm::vec3(0,0,45)),					// [22] C5 - R5 Door
		Entity_OBB(1.0f, 5.0f, 1.0f, 25.0, door12Height, -18.5, glm::vec3(0,0,45)),					// [23] C5 - R5 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, 25.0, door13Height, -13.5, glm::vec3(0,0,45)),					// [24] C5 - R6 Door
		Entity_OBB(1.0f, 5.0f, 1.0f, 25.0, door13Height, -13.5, glm::vec3(0,0,45)),					// [25] C5 - R6 Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, -5.5, door14Height, -16.0, glm::vec3(0,0,45)),					// [26] C5 - R7 Door
		Entity_OBB(5.0f, 1.0f, 1.0f, -5.5, door14Height, -16.0, glm::vec3(0,0,45)),					// [27] C5 - R7 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, -35.0, door15Height, -3.5, glm::vec3(0,0,45)),					// [27] R8 - R7 Door
		Entity_OBB(2.0f, 5.0f, 1.0f, -14.0, door15Height, -9.5, glm::vec3(0,0,45)),					// [29] R8 - R7 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, 4.0, door16Height, -0.5, glm::vec3(0,0,45)),					// [30] C6 - R9 Door
		Entity_OBB(2.0f, 5.0f, 1.0f, 4.0, door16Height, -0.5, glm::vec3(0,0,45)),					// [31] C6 - R9 Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, -1.5, door17Height, 8.0, glm::vec3(0,0,45)),					// [32] R9 - C7 Door
		Entity_OBB(5.0f, 2.0f, 1.0f, -1.5, door17Height, 8.0, glm::vec3(0,0,45)),					// [33] R9 - C7 Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, 12.5, door18Height, 8.0, glm::vec3(0,0,45)),					// [34] R9 - C8 Door
		Entity_OBB(5.0f, 2.0f, 1.0f, 12.5, door18Height, 8.0, glm::vec3(0,0,45)),					// [35] R9 - C8 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, 22.0, door19Height, 11.5, glm::vec3(0,0,45)),					// [36] R10 - C8 Door
		Entity_OBB(1.0f, 5.0f, 1.0f, 22.0, door19Height, 11.5, glm::vec3(0,0,45)),					// [37] R10 - C8 Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, 27.5, door20Height, 17.0, glm::vec3(0,0,45)),					// [38] R10 - C9 Door
		Entity_OBB(5.0f, 2.0f, 1.0f, 27.5, door20Height, 17.0, glm::vec3(0,0,45)),					// [39] R10 - C9 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, 49.0, door21Height, 26.5, glm::vec3(0,0,45)),					// [40] R11 - R12 Door
		Entity_OBB(1.0f, 5.0f, 1.0f, 49.0, door21Height, 26.5, glm::vec3(0,0,45)),					// [41] R11 - R12 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, 49.0f, door22Height, 38.5f, glm::vec3(0,0,45)),				// [42] R12 - c10 Door
		Entity_OBB(1.0f, 5.0f, 1.0f, 49.0f, door22Height, 38.5f, glm::vec3(0,0,45)),				// [43] R12 - c10 Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, 15.0f, door23Height, 41.0f, glm::vec3(0,0,45)),				// [44] C10 - R13 Door
		Entity_OBB(5.0f, 2.0f, 1.0f, 15.0f, door23Height, 41.0f, glm::vec3(0,0,45)),				// [45] C10 - R13 Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, 4.5f, door24Height, 41.0f, glm::vec3(0,0,45)),					// [46] R13 - C11 Door
		Entity_OBB(5.0f, 2.0f, 1.0f, 4.5f, door24Height, 41.0f, glm::vec3(0,0,45)),					// [47] R13 - C11 Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, -35.5f, door25Height, 41.0f, glm::vec3(0,0,45)),				// [48] C11 - Docking Door
		Entity_OBB(5.0f, 2.0f, 1.0f, -35.5f, door25Height, 41.0f, glm::vec3(0,0,45)),				// [49] C11 - Docking Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, -35.5f, door26Height, 29.0f, glm::vec3(0,0,45)),				// [50] Docking - C12 Door
		Entity_OBB(5.0f, 2.0f, 1.0f, -35.5f, door26Height, 29.0f, glm::vec3(0,0,45)),				// [51] Docking - C12 Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, -28.5f, door27Height, 29.0f, glm::vec3(0,0,45)),				// [52] C12 - R14 Door
		Entity_OBB(5.0f, 2.0f, 1.0f, -28.5f, door27Height, 29.0f, glm::vec3(0,0,45)),				// [53] C12 - R14 Collider for door E press
		Entity_OBB(1.0f, 2.0f, 1.0f, -16.5f, door28Height, 29.0f, glm::vec3(0,0,45)),				// [52] C15 - R14 Door
		Entity_OBB(5.0f, 2.0f, 1.0f, -16.5f, door28Height, 29.0f, glm::vec3(0,0,45)),				// [54] C15 - R14 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, -11.0f, door29Height, 23.5f, glm::vec3(0,0,45)),				// [55] R16 - R15 Door
		Entity_OBB(1.0f, 5.0f, 1.0f, -11.0f, door29Height, 23.5f, glm::vec3(0,0,45)),				// [56] R16 - R15 Collider for door E press
		Entity_OBB(2.0f, 1.0f, 1.0f, -11.0f, door30Height, 11.5f, glm::vec3(0,0,45)),				// [57] C7 - R16 Door
		Entity_OBB(1.0f, 5.0f, 1.0f, -11.0f, door30Height, 11.5f, glm::vec3(0,0,45)),				// [58] C7 - R16 Collider for door E press
		
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// For first door in bay Both colliders allow for uses of E to open door when key is collected
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[0])) 
		{
			if (key1Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door test" << endl << endl;
				//doorOneHeight = testDoorVectorUp;
				//doors[0] = Entity_OBB(1.0f, 1.0f, 1.0f, -59.5, doorOneHeight, -1.0, glm::vec3(0, 0, 45));
				//doorOneHeight = yAxisUp;
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " <<endl;			
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
			
		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[1])) 
		{
			if (key1Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door open" << endl << endl;
				doorOneHeight = yAxisUp;
				doors[1] = Entity_OBB(1.0f, 1.0f, 1.0f, -59.5, doorOneHeight, -1.0, glm::vec3(0, 0, 45));
				doors[0] = Entity_OBB(1.0f, 1.0f, 1.0f, -59.5, doorOneHeight, -1.0, glm::vec3(0, 0, 45));
				doorOneHeight = yAxisUp;
			}
			else
			{
				cout << "Key not found" << endl;			
			}

		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		C1 - R1

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[2]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[3]))
		{	
			if ((keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				doorTwoHeight = yAxisUp;
				doors[2] = Entity_OBB(1.5f, 1.0f, 1.0f, -35.0, doorTwoHeight, -3.5, glm::vec3(0, 0, 45));
				doors[3] = Entity_OBB(1.0f, 5.0f, 1.0f, -35.0, doorTwoHeight, -3.5, glm::vec3(0, 0, 45));				
			}
			else
			{
				cout << "Door collision" << endl;
			}
			
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		C1 - R8
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[4]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[5]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				doorThreeHeight = yAxisUp;
				doors[4] = Entity_OBB(1.0f, 5.0f, 1.0f, -19.5, doorThreeHeight, -3.5, glm::vec3(0, 0, 45));				
				doors[5] = Entity_OBB(5.0f, 5.0f, 1.0f, -19.5, doorThreeHeight, -3.5, glm::vec3(0, 0, 45));				
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	R1 - C2
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[6]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[7]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				doorFourHeight = yAxisUp;
				doors[6] = Entity_OBB(1.5f, 1.0f, 1.0f, -35.0, doorFourHeight, -15.5, glm::vec3(0, 0, 45));
				doors[7] = Entity_OBB(1.0f, 5.0f, 1.0f, -35.0, doorFourHeight, -15.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		C2 - R3
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[8]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[9]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				doorFiveHeight = yAxisUp;
				doors[8] = Entity_OBB(1.5f, 1.0f, 1.0f, -35.0, doorFiveHeight, -21.5, glm::vec3(0, 0, 45));
				doors[9] = Entity_OBB(1.0f, 5.0f, 1.0f, -35.0, doorFiveHeight, -21.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	C2 - R2
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[10]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[11]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				doorSixHeight = yAxisUp;
				doors[10] = Entity_OBB(1.5f, 1.0f, 1.0f, -50.0, doorSixHeight, -21.5, glm::vec3(0, 0, 45));
				doors[11] = Entity_OBB(1.0f, 5.0f, 1.0f, -50.0, doorSixHeight, -21.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	R3 - C3
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[12]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[13]))
		{
			if ((keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				doorSevenHeight = yAxisUp;
				doors[12] = Entity_OBB(1.5f, 1.0f, 1.0f, -50.0, doorSevenHeight, -21.5, glm::vec3(0, 0, 45));
				doors[13] = Entity_OBB(1.0f, 5.0f, 1.0f, -35.0, doorSevenHeight, -33.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	C3 - R4 Key from R3
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[14]))
		{
			if (key2Found == true && (keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[15]))
		{
			if (key2Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				doorEightHeight = yAxisUp;
				doors[14] = Entity_OBB(1.5f, 1.0f, 1.0f, -1.5, doorEightHeight, -37.5, glm::vec3(0, 0, 45));
				doors[15] = Entity_OBB(1.0f, 5.0f, 1.0f, -1.5, doorEightHeight, -37.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	R4 - C4
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[16]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[17]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door collision" << endl << endl;
				doorNineHeight = yAxisUp;
				doors[16] = Entity_OBB(1.0f, 1.0f, 1.0f, 4.0, doorNineHeight, -31.5, glm::vec3(0, 0, 45));
				doors[17] = Entity_OBB(5.0f, 1.0f, 1.0f, 4.0, doorNineHeight, -31.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// C4 - C5 Key from R4
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[18]))
		{
			if (key3Found == true && (keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[19]))
		{
			if (key3Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				doorTenHeight = yAxisUp;
				doors[18] = Entity_OBB(1.5f, 1.0f, 1.0f, 4.0, doorTenHeight, -18.5, glm::vec3(0, 0, 45));
				doors[19] = Entity_OBB(1.0f, 5.0f, 1.0f, 4.0, doorTenHeight, -18.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// C5 - C6 Key from R6 
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[20]))
		{
			if (key4Found == true && (keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[21]))
		{
			if (key4Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				door11Height = yAxisUp;
				doors[20] = Entity_OBB(1.5f, 1.0f, 1.0f, 4.0, door11Height, -13.5, glm::vec3(0, 0, 45));
				doors[21] = Entity_OBB(1.0f, 5.0f, 1.0f, 4.0, door11Height, -13.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// C5 - R5
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[22]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[23]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door collision" << endl << endl;
				door12Height = yAxisUp;
				doors[22] = Entity_OBB(1.5f, 1.0f, 1.0f, 25.0, door12Height, -18.5, glm::vec3(0, 0, 45));
				doors[23] = Entity_OBB(1.0f, 5.0f, 1.0f, 25.0, door12Height, -18.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// C5 - R6
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[24]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[25]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door collision" << endl << endl;
				door13Height = yAxisUp;
				doors[24] = Entity_OBB(1.5f, 1.0f, 1.0f, 25.0, door13Height, -13.5, glm::vec3(0, 0, 45));
				doors[25] = Entity_OBB(1.0f, 5.0f, 1.0f, 25.0, door13Height, -13.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  C5 - R7  Key from R7
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[26]))
		{
			if (key5Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door test" << endl << endl;
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}

		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[27]))
		{
			if (key5Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door open" << endl << endl;
				door14Height = yAxisUp;
				doors[26] = Entity_OBB(1.0f, 1.0f, 1.0f, -5.5, door14Height, -16.0, glm::vec3(0, 0, 45));
				doors[27] = Entity_OBB(5.0f, 1.0f, 1.0f, -5.5, door14Height, -16.0, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Key not found" << endl;
			}

		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  R8 - R7
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[28]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door test" << endl << endl;
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}

		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[29]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door open" << endl << endl;
				door15Height = yAxisUp;
				doors[28] = Entity_OBB(2.0f, 1.0f, 1.0f, -35.0, door15Height, -3.5, glm::vec3(0, 0, 45));
				doors[29] = Entity_OBB(2.0f, 5.0f, 1.0f, -14.0, door15Height, -9.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Key not found" << endl;
			}

		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  C6 - R9
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[30]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door test" << endl << endl;
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}

		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[31]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door open" << endl << endl;
				door16Height = yAxisUp;
				doors[30] = Entity_OBB(2.0f, 1.0f, 1.0f, 4.0, door16Height, -0.5, glm::vec3(0, 0, 45));
				doors[31] = Entity_OBB(2.0f, 5.0f, 1.0f, 4.0, door16Height, -0.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Key not found" << endl;
			}

		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  C7 - R9
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[32]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door test" << endl << endl;
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}

		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[33]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door open" << endl << endl;
				door17Height = yAxisUp;
				doors[32] = Entity_OBB(1.0f, 2.0f, 1.0f, -1.5, door17Height, 8.0, glm::vec3(0, 0, 45));
				doors[33] = Entity_OBB(5.0f, 2.0f, 1.0f, -1.5, door17Height, 8.0, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Key not found" << endl;
			}

		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  C7 - R9
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[34]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door test" << endl << endl;
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}

		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[35]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door open" << endl << endl;
				door18Height = yAxisUp;
				doors[34] = Entity_OBB(1.0f, 2.0f, 1.0f, 12.5, door18Height, 8.0, glm::vec3(0, 0, 45));
				doors[35] = Entity_OBB(5.0f, 2.0f, 1.0f, 12.5, door18Height, 8.0, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Key not found" << endl;
			}

		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  R10 - C8
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[36]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door test" << endl << endl;
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}

		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[37]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door open" << endl << endl;
				door19Height = yAxisUp;
				doors[36] = Entity_OBB(2.0f, 1.0f, 1.0f, 22.0, door19Height, 11.5, glm::vec3(0, 0, 45));
				doors[37] = Entity_OBB(1.0f, 5.0f, 1.0f, 22.0, door19Height, 11.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Key not found" << endl;
			}

		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  R10 - C9
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[38]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door test" << endl << endl;
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}

		}

		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[39]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door open" << endl << endl;
				door20Height = yAxisUp;
				doors[38] = Entity_OBB(1.0f, 2.0f, 1.0f, 27.5, door20Height, 17.0, glm::vec3(0, 0, 45));
				doors[39] = Entity_OBB(5.0f, 2.0f, 1.0f, 27.5, door20Height, 17.0, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Key not found" << endl;
			}

		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// R11 - R12 Key from R11
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[40]))
		{
			if (key6Found == true && (keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[41]))
		{
			if (key6Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				door21Height = yAxisUp;
				doors[40] = Entity_OBB(2.0f, 1.0f, 1.0f, 49.0, door21Height, 26.5, glm::vec3(0, 0, 45));
				doors[41] = Entity_OBB(1.0f, 5.0f, 1.0f, 49.0, door21Height, 26.5, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// R12 - C10
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[42]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[43]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door collision" << endl << endl;
				door22Height = yAxisUp;
				doors[42] = Entity_OBB(2.0f, 1.0f, 1.0f, 49.0f, door22Height, 38.5f, glm::vec3(0, 0, 45));
				doors[43] = Entity_OBB(1.0f, 5.0f, 1.0f, 49.0f, door22Height, 38.5f, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// C10 - R13 , C10 - Key for R13- C11
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[44]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[45]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door collision" << endl << endl;
				door23Height = yAxisUp;
				doors[44] = Entity_OBB(1.0f, 2.0f, 1.0f, 15.0f, door23Height, 41.0f, glm::vec3(0, 0, 45));
				doors[45] = Entity_OBB(5.0f, 2.0f, 1.0f, 15.0f, door23Height, 41.0f, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// R13 - C11 Door
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[46]))
		{
			if (key7Found == true && (keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[47]))
		{
			if (key7Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				door24Height = yAxisUp;
				doors[46] = Entity_OBB(1.0f, 2.0f, 1.0f, 4.5f, door24Height, 41.0f, glm::vec3(0, 0, 45));
				doors[47] = Entity_OBB(5.0f, 2.0f, 1.0f, 4.5f, door24Height, 41.0f, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// C11 - Docking, Key in c11 for C11
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[48]))
		{
			if (key8Found == true && (keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[49]))
		{
			if (key8Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				door25Height = yAxisUp;
				doors[48] = Entity_OBB(1.0f, 2.0f, 1.0f, -35.5f, door25Height, 41.0f, glm::vec3(0, 0, 45));
				doors[49] = Entity_OBB(5.0f, 2.0f, 1.0f, -35.5f, door25Height, 41.0f, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// C12 - Docking
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[50]))
		{
			if (key9Found == true && (keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[51]))
		{
			if (key9Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				door26Height = yAxisUp;
				doors[50] = Entity_OBB(1.0f, 2.0f, 1.0f, -35.5f, door26Height, 29.0f, glm::vec3(0, 0, 45));
				doors[51] = Entity_OBB(5.0f, 2.0f, 1.0f, -35.5f, door26Height, 29.0f, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// R14 - C12 Key in R14 
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[52]))
		{
			if (key9Found == true && (keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[53]))
		{
			if (key10Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				door27Height = yAxisUp;
				doors[52] = Entity_OBB(1.0f, 2.0f, 1.0f, -28.5f, door27Height, 29.0f, glm::vec3(0, 0, 45));
				doors[53] = Entity_OBB(5.0f, 2.0f, 1.0f, -28.5f, door27Height, 29.0f, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// R16 - R15 Key in C9
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[54]))
		{
			if (key9Found == true && (keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[55]))
		{
			if (key11Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				door28Height = yAxisUp;
				doors[54] = Entity_OBB(1.0f, 2.0f, 1.0f, -16.5f, door28Height, 29.0f, glm::vec3(0, 0, 45));
				doors[55] = Entity_OBB(5.0f, 2.0f, 1.0f, -16.5f, door28Height, 29.0f, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// C7 - R16
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[56]))
		{
			if (key9Found == true && (keys[SDL_SCANCODE_E]))
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[57]))
		{
			if (key12Found == true && (keys[SDL_SCANCODE_E]))
			{
				cout << "Door collision" << endl << endl;
				door29Height = yAxisUp;
				doors[56] = Entity_OBB(2.0f, 1.0f, 1.0f, -11.0f, door29Height, 23.5f, glm::vec3(0, 0, 45));
				doors[57] = Entity_OBB(1.0f, 5.0f, 1.0f, -11.0f, door29Height, 23.5f, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
			}

		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// C7 - R16
		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[58]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}
			else
			{
				cout << "Door " << endl;
				thePlayer.setX(eye.x);
				thePlayer.setY(eye.y);
				thePlayer.setZ(eye.z);
			}
		}


		if (theCollisionHandler.checkCollisionSphereVsOBB(thePlayer, doors[59]))
		{
			if (keys[SDL_SCANCODE_E])
			{
				cout << "Door collision" << endl << endl;
				door30Height = yAxisUp;
				doors[58] = Entity_OBB(2.0f, 1.0f, 1.0f, -11.0f, door30Height, 11.5f, glm::vec3(0, 0, 45));
				doors[59] = Entity_OBB(1.0f, 5.0f, 1.0f, -11.0f, door30Height, 11.5f, glm::vec3(0, 0, 45));
			}
			else
			{
				cout << "Door collision" << endl;
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
			/*else 
			{
				eye.x = thePlayer.getX();
				eye.y = thePlayer.getY();
				eye.z = thePlayer.getZ();
			}*/
		}
		eye.x = thePlayer.getX();
		eye.y = thePlayer.getY();
		eye.z = thePlayer.getZ();












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

	if (keys[SDL_SCANCODE_4])
	{
		key3Found = true;
		Sleep(300);
		cout << "Key 2 Found, Open the door on your left" << endl;
		Sleep(300);
	}

	if (keys[SDL_SCANCODE_5])
	{
		key4Found = true;
		Sleep(300);
		cout << "Key 2 Found, Open the door on your left" << endl;
		Sleep(300);
	}

	if (keys[SDL_SCANCODE_6])
	{
		key5Found = true;
		Sleep(300);
		cout << "Key 2 Found, Open the door on your left" << endl;
		Sleep(300);
	}
	if (keys[SDL_SCANCODE_7])
	{
		key6Found = true;
		Sleep(300);
		cout << "Key 2 Found, Open the door on your left" << endl;
		Sleep(300);
	}

	if (keys[SDL_SCANCODE_8])
	{
		key7Found = true;
		Sleep(300);
		cout << "Key 2 Found, Open the door on your left" << endl;
		Sleep(300);
	}

	if (keys[SDL_SCANCODE_9])
	{
		key8Found = true;
		Sleep(300);
		cout << "Key 2 Found, Open the door on your left" << endl;
		Sleep(300);
	}

	if (keys[SDL_SCANCODE_0])
	{
		key9Found = true;
		Sleep(300);
		cout << "Key 2 Found, Open the door on your left" << endl;
		Sleep(300);
	}

	if (keys[SDL_SCANCODE_P])
	{
		key10Found = true;
		Sleep(300);
		cout << "Key 2 Found, Open the door on your left" << endl;
		Sleep(300);
	}

	if (keys[SDL_SCANCODE_O])
	{
		key11Found = true;
		Sleep(300);
		cout << "Key 2 Found, Open the door on your left" << endl;
		Sleep(300);
	}

	if (keys[SDL_SCANCODE_M])
	{
		key12Found = true;
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

void sceneManager::spawnDoors()																												// Blender x= x, y = z, z = y
{
	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.0f, door16Height, -0.5f));														// C6 - R9
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-14.0f, door15Height, -9.5f));													// R8 -R7
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());																												// R10 - C8
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(22.0f, door19Height, 11.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(49.0f, door21Height, 26.5f));														// R11 - R12 Locked Key from R11
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																												// R12 - C10
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(49.0f, door22Height, 38.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	//modelStack.push(modelStack.top());
	//modelStack.top() = glm::translate(modelStack.top(), glm::vec3(11.0f, 0.0f, -23.5f));
	//modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	//modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	//ourShader->setMat4("modelView", modelStack.top());
	//gameObjects[1].modelDraw(*ourShader);
	//modelStack.pop();

	modelStack.push(modelStack.top());																												//C7 - R16 
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-11.0f, door30Height, 11.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
		
	modelStack.push(modelStack.top());																												//C1 - R1 
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.0f, doorTwoHeight, -3.5f));															
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																												//C2 - R3 
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.0f, doorFiveHeight, -21.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																												// R16 - R15 
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-11.0f, door29Height, 23.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.0f, doorFourHeight, -15.5f));														//R1-C2 
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													//C2 - R2
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-50.0f, doorSixHeight, -21.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													//R3 - C3
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.0f, doorSevenHeight, -33.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.0f, doorNineHeight, -31.5f));														// R4 - C4
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													// C4 - C5
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.0f, doorTenHeight, -18.5f));															
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													// C5 - C6
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.0f, door11Height, -13.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(25.0f, door12Height, -18.5f));														//C5 - R5
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													// C5 - R6 Room with c5-c6 key
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(25.0f, door13Height, -13.5f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(0 * DEG_TO_RADIAN), glm::vec3(0.10f, 0.0f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-59.5f, doorOneHeight, -1.0f));														// The bay 
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();


	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-19.5f, doorThreeHeight, -1.0f));														// C1 - R8 
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													//C3 - R4 
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-1.5f, doorEightHeight, -37.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-5.5f, door14Height, -16.0f));														//R7 - C5 Room with R7 - C5 Key
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													// R9 - C7
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-1.5f, door17Height, 8.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
		
	modelStack.push(modelStack.top());																													// R9 - C8 Door
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(12.5f, door18Height, 8.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();
		
	modelStack.push(modelStack.top());																													// R10 - C9			
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(27.5f, door20Height, 17.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													// R15 - R14 Key
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-16.5f, door28Height, 29.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													//R14 - C12 Key here				
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-28.5f, door27Height, 29.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													// C12 - Bay key found in R14
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.5f, door26Height, 29.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													// C11 - Docking Key fond in C11
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(-35.5f, door25Height, 41.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													// R13 - C11 
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(4.5f, door24Height, 41.0f));
	modelStack.top() = glm::scale(modelStack.top(), glm::vec3(1.0, 1.0, 1.0));
	modelStack.top() = glm::rotate(modelStack.top(), float(90 * DEG_TO_RADIAN), glm::vec3(0.0f, 0.10f, -0.0f));
	ourShader->setMat4("modelView", modelStack.top());
	gameObjects[1].modelDraw(*ourShader);
	modelStack.pop();

	modelStack.push(modelStack.top());																													// C10 - R13 - C10 has key for R13
	modelStack.top() = glm::translate(modelStack.top(), glm::vec3(15.f, door23Height, 41.0f));
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

