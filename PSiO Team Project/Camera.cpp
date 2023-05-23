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
