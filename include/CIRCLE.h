#ifndef CIRCLE_H
#define CIRCLE_H

#include "RECT.h"
#include <cstdlib>

class Circle : public Rect {
public:
	Circle(glm::vec3 pos, unsigned int width, unsigned int height, float wwidth, float wheight);

	void update(float dt);
	glm::vec3 getVelocity();
	void setVelocity(glm::vec3 vel);
private:
	double timeCreated;
	glm::vec3 velocity;

};




#endif