#include "Camera.h"

Camera::Camera(sf::IntRect bounds_)
{
	viewGame  = new sf::View(sf::FloatRect(0, 776, 1920, 1080));
	viewHUD   = new sf::View();
	viewMenu  = new sf::View();
	viewPause = new sf::View();

	mapBounds = bounds_;
}

Camera::~Camera()
{
	delete viewGame;
	delete viewHUD;
	delete viewMenu;
	delete viewPause;
}

void Camera::update(sf::Time time)
{
	float t = time.asMilliseconds() / 1000.0;

	sf::Vector2f state = pos + (target - pos) * t * speed;
	viewGame->setCenter(state);
	pos = state;

	std::cout << "[" << t << "] ";
	std::cout << pos.x << " " << pos.y;
	std::cout << " -> " << state.x << " " << state.y;
	std::cout << " -> " << target.x << " " << target.y << "\n";

	sf::Vector2f center = viewGame->getCenter();
	sf::Vector2f size = viewGame->getSize();

	float left = center.x - size.x / 2;
	float right = center.x + size.x / 2;
	float top = center.y - size.y / 2;
	float bottom = center.y + size.y / 2;

	if (left < mapBounds.left) viewGame->move(-left, 0);
	else if (right > (mapBounds.left + mapBounds.width)) viewGame->move(mapBounds.width - right, 0);
	if (top < mapBounds.top) viewGame->move(0, -top);
	else if (bottom > (mapBounds.top + mapBounds.height)) viewGame->move(0, mapBounds.height - bottom);
}

void Camera::moveTo(sf::Vector2f target_)
{
	target = target_;
	// pos = viewGame->getCenter();
}
