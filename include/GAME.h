#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "SHADER.h"
#include "RECT.h"
#include "CIRCLE.h"
#include "ANIM.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game {
public:
	GameState state;
	bool keys[1024];
	unsigned int m_width, m_height;

	Game(unsigned int width, unsigned int height);
	~Game();

	void init();
	//game loop
	void processInput(float dt);
	void update(float dt);
	void render();

	void rp_detect(Circle* circle, Rect* rect, bool isleft);
	bool gm_ov(Circle* circle);

private:
	Rect* firstRect;
	Rect* secondRect;
	Circle* shar;
	Shader* shader;
	Anim* anima;
};


#endif