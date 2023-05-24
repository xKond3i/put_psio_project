#include "Camera.h"

Camera::Camera()
{
	viewGame  = new sf::View(sf::FloatRect(0, 760, 1920, 1080));
	viewHUD   = new sf::View();
	viewMenu  = new sf::View();
	viewPause = new sf::View();
}

Camera::~Camera()
{
	delete viewGame;
	delete viewHUD;
	delete viewMenu;
	delete viewPause;
}

void Camera::update()
{

}

void Camera::move(float x, float y)
{
	viewGame->move(x, y);
	sf::Vector2f center = viewGame->getCenter();
	sf::Vector2f size = viewGame->getSize();

	float left = center.x - size.x / 2;
	float right = center.x + size.x / 2;

	if (left < 0) viewGame->move(-left, 0);
	else if (right > 3200) viewGame->move(3200 - right, 0);
}
