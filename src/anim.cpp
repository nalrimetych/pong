#include "ANIM.h"
#include <cmath>

Anim::Anim(glm::vec3 pos, float radius, int vCount, float wwidth, float wheight) {
	m_pos = pos;
	mw_width = wwidth;
	mw_height = wheight;
	secPhase = false;
	scallito = 1;
	float angle = 360.0f / vCount;
	int triangleCount = vCount - 2;
	std::vector<glm::vec3> temp;
	for (int i = 0; i < vCount; i++)
	{
	    float currentAngle = angle * i;
	    float x = (radius/wwidth) * cos(glm::radians(currentAngle));
	    float y = (radius/wheight) * sin(glm::radians(currentAngle));
	    float z = 0.0f;

	    temp.push_back(glm::vec3(x, y, z));
	}
	for (int i = 0; i < triangleCount; i++)
	{
	    vertices.push_back(temp[0]);
	    vertices.push_back(temp[i + 1]);
	    vertices.push_back(temp[i + 2]);
	}


	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // asd

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(0);

}

void Anim::render(Shader* shader) {
	glm::mat4 model = glm::mat4(1.0f);
	shader->use();
	model = glm::mat4(1.0f);
	model = glm::translate(model, m_pos);
	model = glm::scale(model, glm::vec3(scallito));
	shader->setMat4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void Anim::update(float dt, bool& exist) {

	if(secPhase)
		change(dt, -1);
	else
		change(dt, 1);

	if(secPhase)
		m_pos = glm::vec3(0.0f);



	if(scallito < 0)
		exist = false;
}

void Anim::change(float dt, int cifra) {
	scallito += (2000*cifra)* dt;
	if(scallito/2 >= sqrt((mw_width*mw_width) + (mw_height*mw_height))) {
		secPhase = true;
	}

}