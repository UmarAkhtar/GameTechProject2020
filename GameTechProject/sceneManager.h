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

	SDL_GLContext context;
	SDL_Window* window;
	SDL_Window* setupRC(SDL_GLContext& context);

	shared_ptr<Shader> ourShader;
	shared_ptr<Model> ourModel;

};

#endif // !SCENE_MANAGER