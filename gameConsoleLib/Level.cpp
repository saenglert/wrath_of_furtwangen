#include <SFML/Graphics.hpp>
#include <gameConsole.h>
#include <iostream>

Level::Level():Object(0, 0, 5)
{
	victory = false;
	easterEgg = false;
	setPlayer();

	goal = sf::Vector2f(SCREENWIDTH - 420, FLOORHEIGHT);
	easterEggPosition = sf::Vector2f(250, 25);
	easterEggCondition = sf::Vector2f(350, 50);

	createSmallPyramid(sf::Vector2f(100, FLOORHEIGHT - BLOCKHEIGHT));
	createStairs(5, sf::Vector2f(500, FLOORHEIGHT - 2*BLOCKHEIGHT));
	createReverseStairs(5, sf::Vector2f(980, FLOORHEIGHT - 2*BLOCKHEIGHT - 100));
	createStairs(5, sf::Vector2f(500, FLOORHEIGHT - 2*BLOCKHEIGHT - 200));
	createReverseStairs(4, sf::Vector2f(980, FLOORHEIGHT - 2*BLOCKHEIGHT - 300));
	createPlatform(sf::Vector2f(250, BLOCKHEIGHT), sf::Vector2f(300, 50));
	createPlatform(sf::Vector2f(SMALLBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1200, FLOORHEIGHT - 2*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(SMALLBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1300, FLOORHEIGHT - 2*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(SMALLBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1350, FLOORHEIGHT - 4*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1200, FLOORHEIGHT - 6*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(SMALLBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1350, FLOORHEIGHT - 8*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1450, FLOORHEIGHT - 8*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1550, FLOORHEIGHT - 4*BLOCKHEIGHT));

	createPlatform(sf::Vector2f(1030, BLOCKHEIGHT), sf::Vector2f(0, FLOORHEIGHT));
	createPlatform(sf::Vector2f(100, BLOCKHEIGHT), sf::Vector2f(1100, FLOORHEIGHT));
	createPlatform(sf::Vector2f(1000, BLOCKHEIGHT), sf::Vector2f(1600, FLOORHEIGHT));
}

Level::Level(int type):Object(0, 0, type)
{
	victory = false;
	easterEgg = false;
	setPlayer();

	goal = sf::Vector2f(SCREENWIDTH - 420, FLOORHEIGHT);
	easterEggPosition = sf::Vector2f(250, 25);
	easterEggCondition = sf::Vector2f(350, 50);

	createSmallPyramid(sf::Vector2f(100, FLOORHEIGHT - BLOCKHEIGHT));
	createStairs(5, sf::Vector2f(500, FLOORHEIGHT - 2*BLOCKHEIGHT));
	createReverseStairs(5, sf::Vector2f(980, FLOORHEIGHT - 2*BLOCKHEIGHT - 100));
	createStairs(5, sf::Vector2f(500, FLOORHEIGHT - 2*BLOCKHEIGHT - 200));
	createReverseStairs(4, sf::Vector2f(980, FLOORHEIGHT - 2*BLOCKHEIGHT - 300));
	createPlatform(sf::Vector2f(250, BLOCKHEIGHT), sf::Vector2f(300, 50));
	createPlatform(sf::Vector2f(SMALLBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1200, FLOORHEIGHT - 2*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(SMALLBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1300, FLOORHEIGHT - 2*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(SMALLBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1350, FLOORHEIGHT - 4*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1200, FLOORHEIGHT - 6*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(SMALLBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1350, FLOORHEIGHT - 8*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1450, FLOORHEIGHT - 8*BLOCKHEIGHT));
	createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(1550, FLOORHEIGHT - 4*BLOCKHEIGHT));
	
	createPlatform(sf::Vector2f(1030, BLOCKHEIGHT), sf::Vector2f(0, FLOORHEIGHT));
	createPlatform(sf::Vector2f(100, BLOCKHEIGHT), sf::Vector2f(1100, FLOORHEIGHT));
	createPlatform(sf::Vector2f(1000, BLOCKHEIGHT), sf::Vector2f(1600, FLOORHEIGHT));
}

std::vector<sf::RectangleShape*> Level::getPlatforms()
{
	return platforms;
}

void Level::setVictory(bool _victory)
{
	victory = _victory;
}

bool Level::getVictory()
{
	return victory;
}


const sf::Vector2f& Level::getGoal()
{
	return goal;
}

std::vector<Animated>& Level::getEnemies()
{
	return enemies;
} // end function

int Level::getEnemiesSize()
{
	return enemies.size();
} // end function

sf::Vector2f Level::getEasterEggCondition()
{
	return easterEggCondition;
}

sf::Vector2f Level::getEasterEggPosition()
{
	return easterEggPosition;
}

bool Level::getEasterEgg()
{
	return easterEgg;
}

void Level::setEasterEgg(bool _easterEgg)
{
	easterEgg = _easterEgg;
}

void Level::addEnemy(int type)
{
	//Insert the new enemie before the end of enemies
	enemies.insert(enemies.begin(), Animated(type));
	//The vector only saves a copy of the inserted element
	//Therefore pointers need to be reset
	for(int i = 0; i < enemies.size(); i++) enemies[i].initSprite();
} // end function

void Level::addEnemy(float x, float y, int type)
{
	//Insert the new enemie before the end of enemies
	enemies.insert(enemies.begin(), Animated(x,y,type));
	//The vector only saves a copy of the inserted element
	//Therefore pointers need to be reset
	for(int i = 0; i < enemies.size(); i++) enemies[i].initSprite();
}

void Level::addPlatform(sf::RectangleShape *_platform)
{
	//Insert the new platform at the end of platform
	platforms.insert(platforms.end(), _platform);
}

void Level::removeEnemy(int _id)
{	
	for(int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i].getId() == _id)
		{
			//Erasing an object from a vector requires an iterator
			//Iterator points @ begin of enemies
			std::vector<Animated>::iterator iterator = enemies.begin();
			//Increase iterator so it points towards the desired object
			iterator += i;
			//Erase object at iterators position in enemies
			enemies.erase(iterator);
		} // end if
	} // end for
}

void Level::init()
{
	player.initSprite();
	initTexture();
	initSprite();
}

void Level::init(View& view)
{
	player.initSprite();
	initTexture();
	initSprite();
	getSprite().setScale(1.0f, view.getScreendimensions().y / getTexture().getSize().y);
}

void Level::setPlayer()
{
	player = Character(1);
	player.initSprite();
} // end function

void Level::setPlayer(int _type)
{
	player = Character(_type);
	player.initSprite();
} // end function

void Level::setPlayer(float _x, float _y, int _type)
{
	player = Character(_x, _y, _type);
	player.initSprite();
} // end function

Character& Level::getPlayer()
{
	return player;
} // end function

void Level::createPlatform(sf::Vector2f _size, sf::Vector2f _position)
{
	sf::RectangleShape * platform = new sf::RectangleShape;
	platform->setFillColor(sf::Color(PLATFORMCOLOR_R, PLATFORMCOLOR_G, PLATFORMCOLOR_B));
	platform->setSize(_size);
	platform->setPosition(_position);
	addPlatform(platform);
}

void Level::createStairs(int number, sf::Vector2f startPosition)
{
	for(int i = 0; i < number; i++)
	{
		createPlatform(sf::Vector2f(SMALLBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(startPosition.x + i*STAIRWIDTH, startPosition.y - i*STAIRHEIGHT));
	}
}

void Level::createReverseStairs(int _number, sf::Vector2f _startPosition)
{
	for(int i = 0; i < _number; i++)
	{
		createPlatform(sf::Vector2f(SMALLBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(_startPosition.x - i*STAIRWIDTH, _startPosition.y - i*STAIRHEIGHT));
	}
}

void Level::createSmallPyramid(sf::Vector2f position)
{
	for(int i = 0; i < 3; i++)
		createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(position.x + i * BIGBLOCKLENGTH, position.y));
	
	for(int i = 0; i < 2; i++)
		createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(position.x + SMALLBLOCKLENGTH + i * BIGBLOCKLENGTH, position.y - BLOCKHEIGHT));

	createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(position.x + BIGBLOCKLENGTH, position.y - 2* BLOCKHEIGHT));
}

void Level::createBigPyramid(sf::Vector2f position)
{
	for(int i = 0; i < 5; i++)
		createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(position.x + i * BIGBLOCKLENGTH, position.y));
	
	for(int i = 0; i < 4; i++)
		createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(position.x + SMALLBLOCKLENGTH + i * BIGBLOCKLENGTH, position.y - BLOCKHEIGHT));

	for(int i = 0; i < 3; i++)
		createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(position.x + SMALLBLOCKLENGTH + i * BIGBLOCKLENGTH + 50, position.y - 2 * BLOCKHEIGHT));

	for(int i = 0; i < 2; i++)
		createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(position.x + SMALLBLOCKLENGTH + i * BIGBLOCKLENGTH + 100, position.y - 3 * BLOCKHEIGHT));

	createPlatform(sf::Vector2f(BIGBLOCKLENGTH, BLOCKHEIGHT), sf::Vector2f(position.x + BIGBLOCKLENGTH + 100, position.y - 4* BLOCKHEIGHT));
}