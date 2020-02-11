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
#include "Model.h"
#include <stack>



using namespace std;

class sceneManager
{
private:
	void glewInitilisation();
	void loadModel();
	void loadShader();
	

	int windowWidth;
	int windowHeight;


public:
	sceneManager(int windowWidth, int windowHeight); // constructor	
	~sceneManager();

	void draw();
	void update();
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveRight(glm::vec3 pos, GLfloat angle, GLfloat d);

	stack<glm::mat4> model;			// Stack


	SDL_GLContext context;
	SDL_Window* window;
	SDL_Window* setupRC(SDL_GLContext& context);

	shared_ptr<Shader> ourShader;
	shared_ptr<Model> ourModel;

	shared_ptr<Model> skyboxModel;
	shared_ptr<Shader> skyboxShader;
	
	shared_ptr<Model> playerModel;

	GLuint skybox;
	GLuint loadSkybox(const char* fname[6], GLuint* texID);
	const char* cubeTexFiles[6] = {
			"../GameTechProject/skybox/town-skybox/back.bmp",
			"../GameTechProject/skybox/town-skybox/front.bmp",
			"../GameTechProject/skybox/town-skybox/right.bmp",
			"../GameTechProject/skybox/town-skybox/left.bmp",
			"../GameTechProject/skybox/town-skybox/top.bmp",
			"../GameTechProject/skybox/town-skybox/bottom.bmp"
	};

	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	GLfloat rotation;
};

#endif // !SCENE_MANAGER