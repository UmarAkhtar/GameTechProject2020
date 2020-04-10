#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <SDL.h>
#include <glew.h>
#include "Shader.h"
#include "Entity.h"
#include "Entity_OBB.h"
#include "Entity_Sphere.h"
//#include "Ray.h"
#include "Supply_Point.h"
#include "player.h"
//#include "Enemy.h"
#include "collisionHandler.h"
#include "SoundManager.h"
#include "Model.h"
#include <stack>
#include <iostream>
#include <memory>

using namespace std;

class sceneManager
{
private:
	void glewInitilisation();
	void loadModel();
	void loadShader();
	void initMusic();
	void initShaders();


	int windowWidth;
	int windowHeight;


public:
	sceneManager(int windowWidth, int windowHeight); // constructor	
	~sceneManager();

	void draw();
	void middleMap();
	void secondHallwayandTwoRooms();
	void thirdHallwayintoRoom();
	void secondRoom();
	void drawSkybox(glm::mat4 &projection, glm::mat4 &view);
	void hallwayFromFirstRoom();
	void firstRoom();
	void update();
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveRight(glm::vec3 pos, GLfloat angle, GLfloat d);
	SoundManager* sm;
	HSAMPLE* samples = NULL;
	stack<glm::mat4> modelStack;			// Stack
	SDL_GLContext context;
	SDL_Window* window;
	SDL_Window* setupRC(SDL_GLContext& context);
	int health = 100;
	bool key1Found, key2Found = false;
	shared_ptr<Shader> ourShader;
	shared_ptr<Model> ourModel;
	shared_ptr<Model> cubeTest;
	shared_ptr<Model> catModel;
	shared_ptr<Model> floorRoofPlane;
	shared_ptr<Model> wallWindow;
	shared_ptr<Model> bed;
	shared_ptr<Model> ammoCharger;
	shared_ptr<Model> healthCharger;

	player thePlayer;
	vector<Entity_OBB> environment;
	vector<Supply_Point> supplyPoints;
	//vector<Enemy> enemies;
	//vector<Node> nodesList;
	collisionHandler theCollisionHandler;



	shared_ptr<Shader> cubeShader;

	shared_ptr<Model> skyboxModel;
	shared_ptr<Shader> skyboxShader;

	GLuint skybox;
	GLuint loadSkybox(const char* fname[6], GLuint* texID);
	const char* cubeTexFiles[6] = {
			"../GameTechProject/skybox/blue/back.bmp",
			"../GameTechProject/skybox/blue/front.bmp",
			"../GameTechProject/skybox/blue/right.bmp",
			"../GameTechProject/skybox/blue/left.bmp",
			"../GameTechProject/skybox/blue/top.bmp",
			"../GameTechProject/skybox/blue/bottom.bmp"
	};

	glm::vec3 eye;
	glm::vec3 at;
	
	glm::vec3 up;
	GLfloat rotation;

	//glm::mat4 light;
	float attenuationConstant = 1.0f;
	float attenuationLinear = 0.09f;
	float attenuationQuad = 0.01f;


	glm::vec4 lightPos{ 0.0f, 15.0f, 2.0f, 1.0f };

	Shader::materialStruct material0 = {
	{0.2f, 0.4f, 0.2f, 1.0f}, // ambient
	{0.5f, 1.0f, 0.5f, 1.0f}, // diffuse
	{0.0f, 0.1f, 0.0f, 1.0f}, // specular
	2.0f  // shininess
	};

	
	glm::vec3 lightPosition[23] = {
	   glm::vec3(5.0f, 2.3f, -2.5f),
	   glm::vec3(5.2f, 2.3f, -12.5f),
	   glm::vec3(5.2f, 2.3f, -22.5f),
	   glm::vec3(-1.2f, 2.3f, -22.5f),
	   glm::vec3(-5.0f, 2.3f, -12.0f),
	   glm::vec3(-5.0f, 2.3f, -20.0f),
	   glm::vec3(-5.0f, 2.3f, -25.0f),
	   glm::vec3(-10.0f, 2.3f, -15.0f),
	   glm::vec3(-10.0f, 2.3f, -25.0f),
	   glm::vec3(-15.0f, 2.3f, 21.0f),
	   glm::vec3(-15.0f, 2.3f, -31.0f),
	   glm::vec3(-15.0f, 2.3f, -37.0f),
	   glm::vec3(-7.0f, 2.3f, -37.0f),
	   glm::vec3(-7.0f, 2.3f, -47.0f),
	   glm::vec3(-2.0f, 2.3f, -48.0f),
	   glm::vec3(-2.0f, 2.3f, -39.0f),
	   glm::vec3(-2.0f, 2.3f, -29.0f),
	   glm::vec3(9.0f, 2.3f, -30.0f),
	   glm::vec3(3.0f, 2.3f, -30.0f),
	   glm::vec3(9.0f, 2.3f, -37.0f),
	   glm::vec3(3.0f, 2.3f, -37.0f),
	   glm::vec3(2.0f, 2.3f, -47.0f),
	   glm::vec3(6.0f, 2.3f, -47.0f)
	};



};

#endif // !SCENEMANAGER_H