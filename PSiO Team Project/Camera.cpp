#include "Camera.h"

Camera::Camera(sf::IntRect bounds_)
{
	viewGame  = new sf::View(sf::FloatRect(0, 776, 1920, 1080));
	viewHUD   = new sf::View();
	viewMenu  = new sf::View();
	viewPause = new sf::View();

	bounds = bounds_;
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
	sf::Vector2f center = viewGame->getCenter();
	sf::Vector2f size = viewGame->getSize();

	float left = center.x - size.x / 2;
	float right = center.x + size.x / 2;
	float top = center.y - size.y / 2;
	float bottom = center.y + size.y / 2;

	if (left < bounds.left) viewGame->move(-left, 0);
	else if (right > bounds.width) viewGame->move(bounds.width - right, 0);
	if (top < bounds.top) viewGame->move(0, -top);
	else if (bottom > bounds.height) viewGame->move(0, bounds.height - bottom);
}

void Camera::move(float x, float y)
{
	viewGame->move(x, y);
}
