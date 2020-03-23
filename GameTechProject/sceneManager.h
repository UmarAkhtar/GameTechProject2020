#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#pragma once
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
	

	int windowWidth;
	int windowHeight;


public:
	sceneManager(int windowWidth, int windowHeight); // constructor	
	~sceneManager();

	void draw();
	void secondHallwayandTwoRooms();
	void secondRoom();
	void drawSkybox(glm::mat4 &projection, glm::mat4 &view);
	void hallwayFromFirstRoom();
	void firstRoom();
	void update();
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveRight(glm::vec3 pos, GLfloat angle, GLfloat d);
	SoundManager* sm;
	HSAMPLE* samples = NULL;
	stack<glm::mat4> model;			// Stack
	SDL_GLContext context;
	SDL_Window* window;
	SDL_Window* setupRC(SDL_GLContext& context);
	int health = 100;
	bool key1Found, key2Found = false;
	shared_ptr<Shader> ourShader;
	shared_ptr<Model> ourModel;

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
};

#endif // !SCENE_MANAGER