#include <SFML\Graphics.hpp>
#include <gameConsole.h>
#include <vector>
#include <iostream>


Model::Model(View& view)
{
	Level *level = new Level(5);
	level->setType(5);
	level->init(view);
} // end constructor

Level& Model::getLevel()
{
	return level;
}

void Model::updateView(View& view)
{
	// Update the center of the view

	sf::RenderWindow& window = view.getWindow();
	sf::Sprite& player = level.getPlayer().getSprite();
	sf::Vector2f& position = view.getViewposition();

	if(player.getPosition().x + player.getTextureRect().width / 2 > view.getScreendimensions().x/2)
			position.x = player.getPosition().x + 16;
	else
		position.x = view.getScreendimensions().x/2;
		
	position.y = view.getScreendimensions().y/2;

	view.getView().setCenter(position);
	view.update();

	sf::RectangleShape ziel;
	sf::RectangleShape flagge;
	ziel.setFillColor(sf::Color::Blue);
	ziel.setSize(sf::Vector2f(5, 60));
	ziel.setPosition(sf::Vector2f(level.getGoal().x, level.getGoal().y - ziel.getSize().y));
	flagge.setFillColor(sf::Color::Blue);
	flagge.setSize(sf::Vector2f(30,20));
	flagge.setPosition(sf::Vector2f(level.getGoal().x, level.getGoal().y - ziel.getSize().y));

	sf::RectangleShape easter;
	sf::RectangleShape eFlagge;
	easter.setFillColor(sf::Color::Yellow);
	easter.setSize(sf::Vector2f(5, 50));
	easter.setPosition(sf::Vector2f(level.getEasterEggCondition().x, level.getEasterEggCondition().y - easter.getSize().y));
	eFlagge.setFillColor(sf::Color::Yellow);
	eFlagge.setSize(sf::Vector2f(30,20));
	eFlagge.setPosition(sf::Vector2f(level.getEasterEggCondition().x, level.getEasterEggCondition().y - easter.getSize().y));
	// Update window

	sf::Texture easterTexture;
	sf::Sprite easterSprite;
	if(!easterTexture.loadFromFile("easteregg.png"))
	{
		std::cout << "Could not load easteregg.png" << std::endl;
	}
	easterSprite.setTexture(easterTexture);
	easterSprite.setPosition(level.getEasterEggPosition());

	window.clear();	

	window.draw(level.getSprite());
	for(int i = 0; i < level.getEnemies().size(); i++)
	{
		window.draw(level.getEnemies()[i].getSprite());
	} // end for 

	for(int i = 0; i < level.getPlatforms().size(); i++)
	{
		window.draw(*level.getPlatforms()[i]);
	} // end for 

	window.draw(ziel);
	window.draw(flagge);
	window.draw(easter);
	window.draw(eFlagge);
	if(level.getEasterEgg())
	{
		window.draw(easterSprite);
	}
	window.draw(level.getPlayer().getSprite());	
	window.display();
} // end function