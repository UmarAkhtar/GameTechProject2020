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
	void update();

	int windowWidth;
	int windowHeight;


public:
	sceneManager(int windowWidth, int windowHeight); // constructor	
	~sceneManager();

	void draw();


	stack<glm::mat4> model;			// Stack


	SDL_GLContext context;
	SDL_Window* window;
	SDL_Window* setupRC(SDL_GLContext& context);

	shared_ptr<Shader> ourShader;
	shared_ptr<Model> ourModel;

	shared_ptr<Model> skyboxModel;
	shared_ptr<Shader> skyboxShader;

	GLuint skybox;
	GLuint loadSkybox(const char* fname[6], GLuint* texID);
	const char* cubeTexFiles[6] = {
			"../GameTechProject/skybox/back.bmp",
			"../GameTechProject/skybox/front.bmp",
			"../GameTechProject/skybox/right.bmp",
			"../GameTechProject/skybox/left.bmp",
			"../GameTechProject/skybox/top.bmp",
			"../GameTechProject/skybox/bottom.bmp"
	};

};

#endif // !SCENE_MANAGER