#include <SFML/Graphics.hpp>
#include <View.h>
#include <iostream>

// View //

View::View(sf::Vector2f screendimensions)
{
	setScreendimensions(screendimensions);

	init();
} // end constructor

View::View(float x, float y)
{
	setScreendimensions(sf::Vector2f(x,y));

	init();
}

View::View()
{
	setScreendimensions(sf::Vector2f(800,480));

	init();
}

void View::setScreendimensions(sf::Vector2f _screendimensions)
{
	if(_screendimensions.x < 0) _screendimensions.x = abs(_screendimensions.x);
	if(_screendimensions.y < 0) _screendimensions.y = abs(_screendimensions.y);

	screendimensions = _screendimensions;
}

sf::Vector2f& View::getViewposition()
{
	return viewposition;
}

sf::Vector2f View::getScreendimensions()
{
	return screendimensions;
}

sf::RenderWindow& View::getWindow()
{
	return window;
}

sf::View& View::getView()
{
	return view;
}

void View::init()
{
	view.reset(sf::FloatRect(0, 0, this->screendimensions.x, this->screendimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	view.setCenter(this->screendimensions.x/2, this->screendimensions.y/2);

	window.create(sf::VideoMode(this->screendimensions.x,this->screendimensions.y), "Wrath of Furtwangen");
	std::cout << "y: " << this->screendimensions.y << std::endl;
	window.setView(view);
} // end constructor

void View::update()
{
	// Update center of view
	view.setCenter(viewposition);
	// Update window
	window.setView(view);
}