#include <gameConsole.h>
#include <SFML\Graphics.hpp>

Animated::Animated(float _x, float _y, int _type):Object(_x,_y,_type)
{
	setSource(sf::Vector2i(1,0));
	update();
} // end constructor

Animated::Animated(int _type):Object(_type)
{
	setSource(sf::Vector2i(1,0));
	update();
} // end constructor

Animated::Animated():Object()
{
	setSource(sf::Vector2i(1,0));
	update();
} // end constructor

void Animated::setSource(sf::Vector2i _source)
{
	setSourceX(_source.x);
	setSourceY(_source.y);
} // end function

void Animated::setSourceX(int _value)
{
	if(_value < 0 || _value > 2) _value = 0;
	source.x = _value;
} // end function

void Animated::setSourceY(int _value)
{
	if(_value < 0 || _value > 3) _value = 0;
	source.y = _value;
} // end function

sf::Vector2i& Animated::getSoure()
{
	return source;
} // end function

int Animated::getSourceX()
{
	return source.y;
} // end function

int Animated::getSourceY()
{
	return source.y;
} // end function

void Animated::update()
{
	getSprite().setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
} // end function

void Animated::move(int _x, int _y)
{
	// Up
	if(_y < 0) setSourceY(3);

	// Down
	if(_y > 0) setSourceY(0);

	// Left
	if(_x < 0) setSourceY(1);
	
	// Right
	if(_x > 0) setSourceY(2);

	getSprite().move(_x,_y);
	update();
} // end function