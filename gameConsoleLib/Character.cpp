#include <gameConsole.h>
#include <iostream>

// Character // 

Character::Character(float _x, float _y, int _type, int _health):Animated(_x,_y, _type)
{
	setHealth(_health);
	setJumpstate(false);
} // end constructor 

Character::Character(float x, float y, int type):Animated(x,y, type)
{
	setHealth(1);
	setJumpstate(false);
}

Character::Character(int _type):Animated(_type)
{
	setHealth(1);
	setJumpstate(false);
} // end constructor

Character::Character():Animated()
{
	setHealth(1);
	setJumpstate(false);
} // end constructor

void Character::setHealth(int _health)
{
	health = _health;
} // end setHealth function
void Character::setJumpstate(bool state)
{
	jumpstate = state;
}

bool Character::getJumpstate()
{
	return jumpstate;
}

int Character::getHealth()
{
	return health;
} // end getHealth function
sf::Vector2f& Character::getVelocity()
{
	return velocity;
}

void Character::print()
{
	std::cout << " x: " << getSprite().getPosition().x;
	std::cout << " y: " << getSprite().getPosition().y;
	std::cout << " id: " << getId();
	std::cout << " type: " << getType();
	std::cout << " health: " << getHealth() << std::endl;
} // end function