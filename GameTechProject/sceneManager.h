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
#include "SDL_ttf.h"
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
	void spawnBeds();
	void spawnDoors();
	void spawnChargers();
	void spawnKeys();
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveRight(glm::vec3 pos, GLfloat angle, GLfloat d);
	void doorCollision(const Uint8* keys);
	void keyCollision(const Uint8* keys);


	int windowWidth;
	int windowHeight;
	TTF_Font* font = TTF_OpenFont("MavenPro-Regular.ttf", 25);

public:
	sceneManager(int windowWidth, int windowHeight); // constructor	
	~sceneManager();
	void draw();
	void update();


	SoundManager* sm;
	HSAMPLE* samples = NULL;
	
	
	stack<glm::mat4> modelStack;			// Stack
	SDL_GLContext context;
	SDL_Window* window;
	SDL_Window* setupRC(SDL_GLContext& context);
	int health = 100;
	bool key1Found, key2Found, key3Found, key4Found, key5Found, key6Found, key7Found, key8Found, key9Found, key10Found, key11Found, key12Found = false;
	shared_ptr<Shader> ourShader;
	shared_ptr<Model> ourModel;
	
	player thePlayer;
	vector<Entity_OBB> environment;
	//vector<Supply_Point> doors;
	vector<Entity_OBB> doors;
	vector<Supply_Point> supplyPoints;
	vector<Entity_Sphere> keyCards;
	//vector<Enemy> enemies;
	//vector<Node> nodesList;
	collisionHandler theCollisionHandler;
	vector<Model> gameObjects;
	shared_ptr<Shader> cubeShader;

	shared_ptr<Model> skyboxModel;
	shared_ptr<Shader> skyboxShader;

	GLuint skybox;
	GLuint loadSkybox(const char* fname[6], GLuint* texID);
	const char* cubeTexFiles[6] = {
			/*"../GameTechProject/skybox/blue/back.bmp",
			"../GameTechProject/skybox/blue/front.bmp",
			"../GameTechProject/skybox/blue/right.bmp",
			"../GameTechProject/skybox/blue/left.bmp",
			"../GameTechProject/skybox/blue/top.bmp",
			"../GameTechProject/skybox/blue/bottom.bmp"*/

			"../GameTechProject/skybox/lightblue/back.bmp",
			"../GameTechProject/skybox/lightblue/front.bmp",
			"../GameTechProject/skybox/lightblue/right.bmp",
			"../GameTechProject/skybox/lightblue/left.bmp",
			"../GameTechProject/skybox/lightblue/top.bmp",
			"../GameTechProject/skybox/lightblue/bottom.bmp"
	};

	glm::vec3 eye;
	glm::vec3 at;
	
	glm::vec3 up;
	GLfloat rotation;
	GLint x, y, z = 0;

	bool menu = false;
	bool walking = false;
	GLfloat yoffset, yoffset1, yoffset2 = 0;
	float mouseX, mouseY;
	

	glm::vec4 lightPos{ 0.0f, 15.0f, 2.0f, 1.0f };

	Shader::materialStruct material = {
	{0.2f, 0.4f, 0.2f, 1.0f}, // ambient
	{0.5f, 1.0f, 0.5f, 1.0f}, // diffuse
	{0.2f, 0.2f, 0.2f, 0.2f}, // specular
	1.0f  // shininess
	};

	
	glm::vec3 lightPosition[34] = {
	   glm::vec3(-69.0f, 2.9f, -3.0f),
	   glm::vec3(-55.0f, 2.9f, -1.0f),
	   glm::vec3(-30.0f, 2.9f, -1.0f),
	   glm::vec3(-34.0f, 2.9f, -10.0f),
	   glm::vec3(-33.0f, 2.9f, -19.0f),
	   glm::vec3(-52.0f, 2.9f, -19.0f),
	   glm::vec3(-49.0f, 2.9f, -28.0f),
	   glm::vec3(-34.0f, 2.9f, -28.0f),
	   glm::vec3(-35.0f, 2.9f, -37.0f),
	   glm::vec3(-8.0f, 2.9f, -37.0f),
	   glm::vec3(5.0f, 2.9f, -37.0f),
	   glm::vec3(4.0f, 2.9f, -25.0f),
	   glm::vec3(-1.0f, 2.9f, -16.5f),
	   glm::vec3(24.0f, 2.9f, -16.0f),
	   glm::vec3(24.0f, 2.9f, -25.0f),
	   glm::vec3(24.0f, 2.9f, -7.0f),
	   glm::vec3(4.0f, 2.9f, -7.0f),
	   glm::vec3(-13.0f, 2.9f, -16.0f),
	   glm::vec3(-13.0f, 2.9f, -4.0f),
	   glm::vec3(-10.0f, 2.9f, 7.0f),
	   glm::vec3(6.0f, 2.9f, 5.0f),
	   glm::vec3(21.0f, 2.9f, 8.0f),
	   glm::vec3(21.0f, 2.9f, 47.0f),
	   glm::vec3(50.0f, 2.9f, 21.0f),
	   glm::vec3(50.0f, 2.9f, 32.0f),
	   glm::vec3(21.0f, 2.9f, 41.0f),
	   glm::vec3(10.0f, 2.9f, 38.0f),
	   glm::vec3(-4.0f, 2.9f, 41.0f),
	   glm::vec3(-31.0f, 2.9f, 41.0f),
	   glm::vec3(-48.0f, 2.9f, 31.0f),
	   glm::vec3(-32.0f, 2.9f, 29.0f),
	   glm::vec3(-23.0f, 2.9f, 29.0f),
	   glm::vec3(-10.0f, 2.9f, 29.0f),
	   glm::vec3(-10.0f, 2.9f, 17.0f),
	};

	glm::vec3 keyPosition[11] =
	{
		glm::vec3(-63.0f, 0.0f, -1.0f),
		glm::vec3(-44.0f, 0.0f, -28.0f),
		glm::vec3(7.0f, 0.0f, -36.0f),
		glm::vec3(-10.0f, 0.0f, -14.0f),
		glm::vec3(28.0f, 0.0f, -6.0f),
		glm::vec3(40.0f, 0.0f, 17.0f),
		glm::vec3(54.0f, 0.0f, 20.0f),
		glm::vec3(55.0f, 0.0f, 41.0f),
		glm::vec3(2.0f, 0.0f, 41.0f),
		glm::vec3(6.0f, 0.0f, 32.0f),
		glm::vec3(-21.0f, 0.0f, 26.0f),
	};


	//glm::vec3 doorOneHeight;// = testDoorVectorDown;														//Will need one of these vars for each door
	//glm::vec3 doorTwoHeight;
	glm::vec3 testDoorVectorDown = { 5.3, 1, -10 };
	glm::vec3 testDoorVectorMid = { 5.3, 1.5, -10 };
	glm::vec3 testDoorVectorUp = { 5.3, 3, -10 };
	
	float doorOneHeight;
	float doorTwoHeight;
	float doorThreeHeight;
	float doorFourHeight;
	float doorFiveHeight;
	float doorSixHeight;
	float doorSevenHeight;
	float doorEightHeight;
	float doorNineHeight;
	float doorTenHeight;
	float door11Height;
	float door12Height;
	float door13Height;
	float door14Height;
	float door15Height;
	float door16Height;
	float door17Height;
	float door18Height;
	float door19Height;
	float door20Height;
	float door21Height;
	float door22Height;
	float door23Height;
	float door24Height;
	float door25Height;
	float door26Height;
	float door27Height;
	float door28Height;
	float door29Height;
	float door30Height;


	float yAxis;
	float yAxisUp = 2.8f;
	float yAxisDown = 0.0;


	glm::vec2 rayMouseTest;
};

#endif // !SCENEMANAGER_H
