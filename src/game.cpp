#include "GAME.h"

Game::Game(unsigned int width, unsigned int height) {
	state = GAME_MENU;
	m_width = width;
	m_height = height;
}

Game::~Game() {

}

void Game::init() {
	shader = new Shader("B:/game__dev/gl/ppanim/prop/vertex.txt", "B:/game__dev/gl/ppanim/prop/fragment.txt");
	firstRect = new Rect(glm::vec3(-0.9f, 0.0f, 0.0f), 10, 100, m_width, m_height);
	secondRect = new Rect(glm::vec3(0.9f, 0.0f, 0.0f), 10, 100, m_width, m_height);
	shar = new Circle(glm::vec3(0.0f, 0.0f, 0.0f), 10, 10, m_width, m_height);
	anima = nullptr;
	//anima = new Anim(glm::vec3(1.0f, 0.0f, 0.0f), 1, 128, m_width, m_height);

}

void Game::update(float dt) {
	firstRect->update(dt, keys);
	if(shar)
		secondRect->update(dt, shar->getPos(), shar->getYMID());
	else
		secondRect->update(dt, glm::vec3(0.0f), 0.0f);

	if(!shar && !anima)
		shar = new Circle(glm::vec3(0.0f, 0.0f, 0.0f), 10, 10, m_width, m_height);

	if(shar) {
		if(shar->getVelocity().x < 0)
			rp_detect(shar, firstRect, true);
		else
			rp_detect(shar, secondRect, false);

		shar->update(dt);
		if(gm_ov(shar)) {
			anima = new Anim(shar->getPos(), 1, 128, m_width, m_height);
			shar = nullptr;
		}
	}
	if(anima) {
		bool hui = true;
		anima->update(dt, hui);
		if(!hui)
			anima = nullptr;
	}
}

void Game::processInput(float dt) {

}

void Game::render() {
	firstRect->render(shader);
	secondRect->render(shader);
	if(shar)
		shar->render(shader);
	if(anima)
		anima->render(shader);
}

void Game::rp_detect(Circle* circle, Rect* rect, bool isleft) {
	glm::vec3 cpos = circle->getPos();
	glm::vec3 cvel = circle->getVelocity();
	glm::vec3 rpos = rect->getPos();
	float c_x_buff = circle->getXMID();
	float c_y_buff = circle->getYMID();
	float r_x_buff = rect->getXMID();
	float r_y_buff = rect->getYMID();
	if((isleft&&cpos.x<rpos.x-r_x_buff) || (!isleft&&cpos.x>rpos.x+r_x_buff))
		return;
	if((isleft && cpos.x - c_x_buff <= rpos.x + r_x_buff) || (!isleft && cpos.x + c_x_buff >= rpos.x - r_x_buff)) {
		if( (cpos.y - c_y_buff <= rpos.y + r_y_buff && cpos.y - c_y_buff >= rpos.y - r_y_buff) ||
		   (cpos.y + c_y_buff <= rpos.y + r_y_buff && cpos.y + c_y_buff >= rpos.y - r_y_buff) )
		{
			float yadd;
			if(abs(rpos.y-cpos.y) > abs(r_y_buff*0.8)) {
				yadd = -(rpos.y-cpos.y)*5.0f;
				std::cout << "first" << std::endl;
			}
			else {
				yadd = cvel.y-(rpos.y-cpos.y) * 2.0f;
				std::cout << "sec" << std::endl;
			}

			circle->setVelocity(glm::vec3(-cvel.x, yadd, cvel.z));

		}
			
	}
}

bool Game::gm_ov(Circle* circle) {
	float xpos = circle->getPos().x;
	if(xpos<=-1.0f || xpos >= 1.0f)
		return true;
	return false;
}