#ifndef ANIM_H
#define ANIM_H

#include <glm/glm.hpp>
#include <vector>
#include "SHADER.h"

class Anim {
public:
	Anim(glm::vec3 pos, float radius, int vCount, float wwidth, float wheight);

	void render(Shader* shader);
	void update(float dt, bool& exist);

private:
	glm::vec3 m_pos;
	std::vector<glm::vec3> vertices;
	unsigned int VAO, VBO;
	float scallito;
	float mw_width, mw_height;

	bool secPhase;
	void change(float dt, int cifra);
};



#endif