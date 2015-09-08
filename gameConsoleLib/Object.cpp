#include <SFML\Graphics.hpp>
#include <gameConsole.h>

// Object //

int Object::counter = 0;

Object::Object(float _x, float _y, int _type)
{
	counter++;
	id = counter;

	setType(_type);

	initSprite(_x,_y);
	initText();
} // end constructor

Object::Object(int _type)
{
	counter++;
	id = counter;

	setType(_type);

	initSprite(rand() % 100,rand() % 100);
	initText();
} // end constructor

Object::Object()
{
	counter++;
	id = counter;

	setType(1);

	initSprite(rand() % 100,rand() % 100);
	initText();
} // end constructor
Object::~Object()
{
}

void Object::setType(int _type)
{
	type = abs(_type);
} // end function

const int Object::getId()
{
	return id;
} // end function

int Object::getType()
{
	return type;
} // end function

sf::Sprite& Object::getSprite()
{
	return sprite;
} // end function

sf::Texture& Object::getTexture()
{
	return texture;
} // end function

sf::Text& Object::getText()
{
	return text;
} // end function

void Object::initTexture()
{

	switch (type)
	{
	case 1:
		texture.loadFromFile("player.png");
		break;
	case 2:
		texture.loadFromFile("enemy1.png");
		break;
	case 3:
		texture.loadFromFile("enemy2.png");
		break;
	case 4:
		texture.loadFromFile("background1.png");
		break;
	case 5:
		texture.loadFromFile("background2.png");
		break;
	case 6:
		texture.loadFromFile("background3.png");
		break;
	case 7:
		texture.loadFromFile("floor1.png");
		break;
	case 0:
	default:
		break;
	} // end switch
	
} // end function

void Object::initSprite(float _x, float _y)
{
	initTexture();

	sprite.setPosition(_x,_y);
	sprite.setTexture(texture);
} // end function

void Object::initSprite()
{
	sprite.setTexture(texture);
} // end function

void Object::initText()
{
	text.setString(std::to_string(id));
	text.setPosition(sprite.getPosition().x, sprite.getPosition().y - 10);
	text.setColor(sf::Color(255,255,255));
	text.setCharacterSize(18);
} // end function
