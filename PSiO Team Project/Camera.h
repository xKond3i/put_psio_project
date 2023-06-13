#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// OTHER libraries
#include <string>
#include <map>

class Camera
{
private:
	/* ---------- VARIABLES ---------- */
	// CAMERA movement INTERPOLATION
	sf::Vector2f target = { 0, 0 };
	float speed = 1;

	// VIEW managing
	sf::VideoMode windowSize;
	std::map<std::string, sf::View*> views;

	unsigned int current = 0;
	float scale = 3;



	/* ---------- METHODS ---------- */
	void setupViews();

public:
	Camera(sf::VideoMode windowSize);
	~Camera();

	/* ---------- VARIABLES ---------- */
	static std::string GAME;
	static std::string UI;



	/* ---------- METHODS ---------- */
	void moveTo(sf::Vector2f target_);

	void fixToBounds(sf::IntRect mapBounds);

	sf::View* getView(std::string name);



	void handleEvents(sf::Event event);

	void update(sf::Time time);		 // logic EXCEPT physics take place here!
	void fixedUpdate(sf::Time time); // physics take place here.

	// void draw();
};
