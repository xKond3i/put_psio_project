#include "Camera.h"

Camera::Camera()
{
	viewGame  = new sf::View();
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
