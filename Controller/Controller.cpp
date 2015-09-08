#include <gameConsole.h>
#include <iostream>

Controller::Controller(Model& model, View& view):model(model),view(view),movespeed(2.0f),jumpspeed(10.0f),vMultiplicatorNormal(4.0f),vMultiplicatorRunning(vMultiplicatorNormal * 2)
{
	defeat = false;
	victory = false;
	right = false;
	left = false;
}

void Controller::start()
{	
	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1.f / 60.f);

	// Game Loop
	while (view.getWindow().isOpen())
    {
        sf::Event event;
        while (view.getWindow().pollEvent(event))
        {
			switch (event.type)
			{
			case sf::Event::Closed:
				view.getWindow().close();
				break;
			default:
				break;
			} // end switch
        } // end while

		timeSinceLastUpdate += clock.restart();

	    while (timeSinceLastUpdate > timePerFrame)
	    {
			timeSinceLastUpdate -= timePerFrame; 

		    playerMovement();
	    }

		frameCounter +=  frameSpeed * clock.restart().asSeconds();

		if(frameCounter >= switchFrame) 
		{
			frameCounter = 0;
			auto player = model.getLevel().getPlayer();
			player.setSourceX(player.getSourceX() + 1);
		}// end if

		model.updateView(view);
    } // end while
} // end function


void Controller::playerMovement()
{
	Character& player = model.getLevel().getPlayer();
	auto enemies= model.getLevel().getEnemies();
	sf::Vector2f& velocity = player.getVelocity();

	velocity.x = 0;

	// Player Movement Up
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !player.getJumpstate() && !defeat && !victory) 
	{
		player.setJumpstate(true);
		velocity.y = -jumpspeed; 
	} // end if

	// Player Movement Left

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& !playerCollisionLeft() && !victory && !defeat) 
	{
		velocity.x = -movespeed;
	} // end if
	// Player Movement Right

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !playerCollisionRight() && !victory && !defeat) 
	{
		velocity.x = movespeed;
	} // end if
	
	// Player Movement Down
	if((player.getSprite().getPosition().y + player.getSprite().getTextureRect().height < GROUNDHEIGHT || velocity.y < 0))
	{
		velocity.y += GRAVITY;
	} // end if
	else
	{
		player.setJumpstate(false);
		player.getSprite().setPosition(player.getSprite().getPosition().x, GROUNDHEIGHT - player.getSprite().getTextureRect().height);
		velocity.y = 0;
	}

	int health = 0;
	for(int i = 0; i < enemies.size(); i++)
	{
		if(detectCollisionBottom(player, enemies[i]))
		{
			player.setJumpstate(false);
			health = player.getHealth() - 1;
			player.setHealth(health);
			std::cout << "Deine verbleibende Gesundheit ist: " << player.getHealth() << std::endl;
			player.getSprite().setPosition(sf::Vector2f(player.getSprite().getPosition().x, 
				player.getSprite().getPosition().y - enemies[i].getSprite().getTextureRect().height));
			velocity.y = -velocity.y/1.5;
		}
	}

	for(int i = 0; i < enemies.size(); i++)
	{
		if(detectCollisionRight(player, enemies[i]))
		{
			player.setJumpstate(false);
			left = false;
			right = true;
		}
		if(detectCollisionLeft(player, enemies[i]))
		{
			player.setJumpstate(false);
			right = false;
			left = true;
		}
		else
		{
			right = false;
			left = false;
		}
	}

	std::vector<sf::RectangleShape*> platform;
	platform = model.getLevel().getPlatforms();
	for(int i = 0; i < platform.size(); i++)
	{
		if(detectPlatformCollisionBottom(player, platform[i]))
		{
			player.setJumpstate(false);
			player.getSprite().setPosition(player.getSprite().getPosition().x, platform[i]->getPosition().y - 32);
			velocity.y = 0;
		}
	}

	if(player.getSprite().getPosition().x + player.getSprite().getTextureRect().width >= model.getLevel().getGoal().x)
	{
		std::cout << "GEWONNEN!" << std::endl;
		victory = true;
		model.getLevel().setVictory(victory);
	}

	if(player.getSprite().getPosition().x + player.getSprite().getTextureRect().width / 2 <= model.getLevel().getEasterEggCondition().x 
			&& (player.getSprite().getPosition().y + player.getSprite().getTextureRect().height / 2 <= model.getLevel().getEasterEggCondition().y))
	{
		std::cout << "EASTEREGG GEFUNDEN" << std::endl;
		model.getLevel().setEasterEgg(true);
	}

	if(player.getSprite().getPosition().y + player.getSprite().getTextureRect().height >= GROUNDHEIGHT || player.getHealth() < 0)
	{
		std::cout << "VERLOREN!" << std::endl;
		player.setHealth(3);
		//defeat = true; //disabled due to presentation purposes
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
		player.move(player.getVelocity().x * vMultiplicatorRunning, player.getVelocity().y);
	else 
		player.move(player.getVelocity().x * vMultiplicatorNormal, player.getVelocity().y);
} // end function


bool Controller::playerCollisionLeft()
{
	Character player = model.getLevel().getPlayer();
	auto enemies= model.getLevel().getEnemies();

	for(int i = 0; i < enemies.size(); i++)
	{
		if(detectCollisionLeft(player, enemies[i]))
			return true;
		else
			return false;		
	}
}

bool Controller::playerCollisionRight()
{
	Character player = model.getLevel().getPlayer();
	auto enemies= model.getLevel().getEnemies();

	for(int i = 0; i < enemies.size(); i++)
	{
		if(detectCollisionRight(player, enemies[i]))
			return true;
		else
			return false;		
	}
}

bool Controller::detectCollisionBottom(Animated& _player, Animated& _object)
{
	float pTop = _player.getSprite().getPosition().y;
	float pLeft = _player.getSprite().getPosition().x;
	float pRight = _player.getSprite().getPosition().x + _player.getSprite().getTextureRect().width;
	float pDown = _player.getSprite().getPosition().y + _player.getSprite().getTextureRect().height;

	float eTop = _object.getSprite().getPosition().y;
	float eLeft = _object.getSprite().getPosition().x;
	float eRight = _object.getSprite().getPosition().x + _object.getSprite().getTextureRect().width;
	float eDown = _object.getSprite().getPosition().y + _object.getSprite().getTextureRect().height;

	if(pDown > eTop && pDown < eDown && pRight > eLeft && pLeft < eRight)
	{
		//std::cout << "Kollision am arsch des Spielers" << std::endl;
		return true;
	}
	else
		return false;
}

bool Controller::detectCollisionLeft(Animated& _player, Animated& _object)
{
	float pTop = _player.getSprite().getPosition().y;
	float pLeft = _player.getSprite().getPosition().x;
	float pRight = _player.getSprite().getPosition().x + _player.getSprite().getTextureRect().width;
	float pDown = _player.getSprite().getPosition().y + _player.getSprite().getTextureRect().height;

	float eTop = _object.getSprite().getPosition().y;
	float eLeft = _object.getSprite().getPosition().x;
	float eRight = _object.getSprite().getPosition().x + _object.getSprite().getTextureRect().width;
	float eDown = _object.getSprite().getPosition().y + _object.getSprite().getTextureRect().height;

	if(pLeft <= eRight && pLeft >= eLeft && pDown <= eDown && pDown >= eTop)
	{
		std::cout << "Kollision Links des Spielers" << std::endl;
		return true;
	}
	else
		return false;
}

bool Controller::detectCollisionRight(Animated& _player, Animated& _object)
{
	float pTop = _player.getSprite().getPosition().y;
	float pLeft = _player.getSprite().getPosition().x;
	float pRight = _player.getSprite().getPosition().x + _player.getSprite().getTextureRect().width;
	float pDown = _player.getSprite().getPosition().y + _player.getSprite().getTextureRect().height;

	float eTop = _object.getSprite().getPosition().y;
	float eLeft = _object.getSprite().getPosition().x;
	float eRight = _object.getSprite().getPosition().x + _object.getSprite().getTextureRect().width;
	float eDown = _object.getSprite().getPosition().y + _object.getSprite().getTextureRect().height;

	if(pRight >= eLeft && pRight <= eRight && pDown <= eDown && pDown >= eTop)
	{
		std::cout << "Kollision rechts des Spielers" << std::endl;
		return true;
	}
	else
		return false;
}

bool Controller::detectPlatformCollisionBottom(Animated& _player, sf::RectangleShape *_platform)
{
	float pTop = _player.getSprite().getPosition().y;
	float pLeft = _player.getSprite().getPosition().x;
	float pRight = _player.getSprite().getPosition().x + _player.getSprite().getTextureRect().width;
	float pDown = _player.getSprite().getPosition().y + _player.getSprite().getTextureRect().height;

	float eTop = _platform->getPosition().y;
	float eLeft = _platform->getPosition().x;
	float eRight = _platform->getPosition().x + _platform->getSize().x;
	float eDown = _platform->getPosition().y + _platform->getSize().y;

	if(pDown > eTop && pDown < eDown && pRight > eLeft && pLeft < eRight)
	{
		//std::cout << "Kollision mit Plattform und Spieler" << std::endl;
		return true;
	}
	else
		return false;
}