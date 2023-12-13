#include "CIRCLE.h"

Circle::Circle(glm::vec3 pos, unsigned int width, unsigned int height, float wwidth, float wheight) : Rect(pos, width, height, wwidth, wheight) {
	timeCreated = glfwGetTime();
	srand(time(0));
	unsigned int randm = rand()%2;
	velocity = glm::vec3(1.0f, 0.0f, 0.0f);
	if(!randm) {
		velocity.x = -velocity.x;
		velocity.y = -velocity.y;
	}
}

void Circle::update(float dt) {
	if(glfwGetTime()-timeCreated < 1.0)
		return;
	if(m_pos.y+y_mid >= 1.0f || m_pos.y-y_mid <= -1.0f)
		velocity.y = -velocity.y;

	m_pos += velocity*dt;
}

glm::vec3 Circle::getVelocity() {
	return velocity;
}
void Circle::setVelocity(glm::vec3 vel) {
	velocity = vel;
}