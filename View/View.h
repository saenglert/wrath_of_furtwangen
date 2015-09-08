#include <SFML/Graphics.hpp>

class View
{
private:
	sf::Vector2f screendimensions;
	sf::Vector2f viewposition;
	// Complete Window
	sf::RenderWindow window;
	// Displayed excerpt of the window
	sf::View view;
public:
	View(sf::Vector2f screendimensions);
	View(float x, float y);
	View();

	void setScreendimensions(sf::Vector2f screendimensions);

	sf::Vector2f& getViewposition();
	sf::Vector2f getScreendimensions();
	sf::RenderWindow& getWindow();
	sf::View& getView();

	void init();
	void update();
}; // end class