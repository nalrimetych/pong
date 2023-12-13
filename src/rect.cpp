#include "RECT.h"
#include <cmath>



Rect::Rect(glm::vec3 pos, unsigned int width, unsigned int height, float wwidth, float wheight) {
	m_pos = pos;
	x_mid = width / wwidth;
	y_mid = height / wheight;
	movement_speed = 1.0f;

	float vertices[] = {
		-x_mid, -y_mid, 0.0f,
		 x_mid, -y_mid, 0.0f,
		 x_mid,  y_mid, 0.0f,

		-x_mid, -y_mid, 0.0f,
		-x_mid,  y_mid, 0.0f,
		 x_mid,  y_mid, 0.0f
	};

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//POSITION ATTRIBS
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
	glEnableVertexAttribArray(0);

	dir = 0;
}

void Rect::aiCheck(glm::vec3 rectpos, float rectybuff, glm::vec3 sharpos) {
	if(sharpos.y < rectpos.y-rectybuff)
		dir = -1;
	else if(sharpos.y > rectpos.y+rectybuff)
		dir =  1;
	else if(abs(rectpos.y-sharpos.y) <= rectybuff/3) {
		dir = 0;
	}
}

void Rect::update(float dt, glm::vec3 sharpos, float sharybuff) {
	aiCheck(m_pos, y_mid, sharpos);
	if(dir==0)
		return;
	if(dir==1 && m_pos.y + y_mid >= 1.0)
		m_pos.y = 1.0 - y_mid;
	else if(dir==-1 && m_pos.y - y_mid <= -1.0)
		m_pos.y = -1.0 + y_mid;
	else
		m_pos.y += movement_speed * dt * dir;
}

void Rect::update(float dt, bool keys[]) {
	if(keys[GLFW_KEY_UP]) {
		if(m_pos.y + y_mid >= 1.0)
			m_pos.y = 1.0 - y_mid;
		else
			m_pos.y += movement_speed * dt;
	}
	if(keys[GLFW_KEY_DOWN]) {
		if(m_pos.y - y_mid <= -1.0)
			m_pos.y = -1.0 + y_mid;
		else
			m_pos.y -= movement_speed * dt;	
	}
}

void Rect::render(Shader* shader) {
	glm::mat4 model = glm::mat4(1.0f);
	shader->use();
	model = glm::mat4(1.0f);
	model = glm::translate(model, m_pos);
	shader->setMat4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

glm::vec3 Rect::getPos() {
	return m_pos;
}
float Rect::getXMID() {
	return x_mid;
}
float Rect::getYMID() {
	return y_mid;
}