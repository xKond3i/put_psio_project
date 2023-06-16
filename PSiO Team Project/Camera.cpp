#include "Camera.h"

void Camera::setupViews()
{
	views[Camera::GAME] = new sf::View(sf::FloatRect(0, 0, windowSize.width, windowSize.height)); // moves with bait
	views[Camera::UI]   = new sf::View(sf::FloatRect(0, 0, windowSize.width, windowSize.height)); // still view

	views[Camera::GAME] -> zoom(1.f / scale);
	views[Camera::UI]   -> zoom(1.f / scale);

	views[Camera::GAME] -> setCenter((windowSize.width / 2 / scale), (windowSize.height / 2 / scale) + 170);
	views[Camera::UI] -> setCenter((windowSize.width / 2 / scale), (windowSize.height / 2 / scale) + 170);

	// -> start at TOP
	sf::Vector2f dest = { 0, 0 };
	views[Camera::GAME]->setCenter(dest);
}



Camera::Camera(sf::VideoMode windowSize_)
{
	windowSize = windowSize_;
	setupViews();
}

Camera::~Camera()
{
	for (auto p : views) delete p.second;
	views.clear();
}



void Camera::handleEvents(sf::Event event)
{
	if (event.type == sf::Event::Resized)
	{
		windowSize = { event.size.width, event.size.height };

		// adjust scale
		if		(windowSize.width > 1600) scale = 4;
		else if (windowSize.width > 1200) scale = 3;
		else if (windowSize.width > 900)  scale = 2.5;
		else	scale = 2; // default -> the smallest

		setupViews();
	}
}

void Camera::update(sf::Time time)
{

}

void Camera::fixedUpdate(sf::Time time)
{
	float t = time.asSeconds();

	// INTERPOLATE CAMERA MOVE
	sf::Vector2f pos = views[Camera::GAME]->getCenter();
	sf::Vector2f dest = pos + (target - pos) * t * speed; // destination
	views[Camera::GAME]->setCenter(dest);
}



void Camera::moveTo(sf::Vector2f target_)
{
	target = target_;
}

void Camera::fixToBounds(sf::IntRect mapBounds)
{
	sf::Vector2f center = views[Camera::GAME]->getCenter();
	sf::Vector2f size = views[Camera::GAME]->getSize();

	float left = center.x - size.x / 2;
	float right = center.x + size.x / 2;
	float top = center.y - size.y / 2;
	float bottom = center.y + size.y / 2;

	if (left < mapBounds.left) views[Camera::GAME]->move(-left, 0);
	else if (right > (mapBounds.left + mapBounds.width)) views[Camera::GAME]->move(mapBounds.width - right, 0);
	if (top < mapBounds.top) views[Camera::GAME]->move(0, -top);
	else if (bottom > (mapBounds.top + mapBounds.height)) views[Camera::GAME]->move(0, mapBounds.height - bottom);
}



sf::View* Camera::getView(std::string name)
{
	auto pos = views.find(name);
	if (pos != views.end()) {
		return pos->second;
	}
	return nullptr;
}



/* ---------- STATIC VALUES ---------- */
inline std::string Camera::GAME = "GAME";
inline std::string Camera::UI	= "UI";
