#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <SDL.h>
#include <glew.h>
#include "Shader.h"
#include "SoundManager.h"
#include "Model.h"
#include <stack>

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
	shared_ptr<Shader> ourShader;
	shared_ptr<Model> ourModel;
	shared_ptr<Model> cubeTest;
	shared_ptr<Model> catModel;

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
	glm::vec3 yoffset;
	glm::vec3 up;
	GLfloat rotation;

	//glm::mat4 light;
	float attenuationConstant = 1.0f;
	float attenuationLinear = 0.02f;
	float attenuationQuad = 0.01f;

	/*glm::vec4 lightAmbient = { 0.3f, 0.3f, 0.3f, 1.0f };
	glm::vec4 lightDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec4 lightSpecular = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec4 lightPosition = { -5.0f, 2.0f, 2.0f, 1.0f };
	glm::vec4 lightPos = { 0.0f, 2.0f, 0.0f, 1.0f };
	glm::vec4 materialAmbient = { 0.2f, 0.4f, 0.2f, 1.0f };
	glm::vec4 materialDiffuse = { 0.5f, 1.0f, 0.5f, 1.0f };
	glm::vec4 materialSpecular = { 0.0f, 0.1f, 0.0f, 1.0f };
	GLfloat materialShininess = 1.0f;*/


	Shader::lightStruct light = {
	{1.0f, 1.0f, 1.0f, 1.0f}, // ambient
	{1.0f, 1.0f, 1.0f, 1.0f}, // diffuse
	{1.0f, 1.0f, 1.0f, 1.0f}, // specular
	{ -10.0f, 10.0f, 10.0f, 1.0f}  // position
	};

	glm::vec4 lightPos{ 0.0f, 15.0f, 2.0f, 1.0f };

	Shader::materialStruct material0 = {
	{0.2f, 0.4f, 0.2f, 1.0f}, // ambient
	{0.5f, 1.0f, 0.5f, 1.0f}, // diffuse
	{0.0f, 0.1f, 0.0f, 1.0f}, // specular
	2.0f  // shininess
	};

	glm::vec3 catPos = { 0.0f, 10.0f, -10.0f };

};

#endif // !SCENEMANAGER_H