#ifndef RECT_H
#define RECT_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SHADER.h"
#include <iostream>

class Rect {
public:
	Rect(glm::vec3 pos, unsigned int width, unsigned int height, float wwidth, float wheight);
	void update(float dt, glm::vec3 sharpos, float sharybuff);
	void update(float dt, bool keys[]);
	void render(Shader* shader);

	glm::vec3 getPos();
	float getXMID();
	float getYMID();

protected:
	glm::vec3 m_pos;
	unsigned int VAO, VBO;
	float x_mid;
	float y_mid;
	float movement_speed;
private:
	void aiCheck(glm::vec3 rectpos, float rectybuff, glm::vec3 sharpos);
	int dir; //just for "ai"
};


#endif