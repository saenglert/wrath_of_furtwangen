#include <SFML\Graphics.hpp>

#define BLOCKHEIGHT 20
#define SMALLBLOCKLENGTH 50
#define BIGBLOCKLENGTH 100
#define STAIRHEIGHT 10
#define STAIRWIDTH 120
#define GRAVITY 1.0f
#define GROUNDHEIGHT 440
#define PLATFORMCOLOR_R 186
#define PLATFORMCOLOR_G 218
#define PLATFORMCOLOR_B	85
#define SCREENWIDTH 2160
#define FLOORHEIGHT 400


//View 
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


//Object
class Object
{
private:
	static int counter;
	
	int id;
	int type;
	
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Text text;
public:
	Object(float _x, float _y, int _type);
	Object(int _type);
	Object();
	~Object();

	void setType(int _type);
	
	int getType();
	const int getId();
	sf::Texture& getTexture();
	sf::Sprite& getSprite();
	sf::Text& getText();

	void initTexture();
	void initText();
	void initSprite(float x, float y);
	void initSprite();
}; // end class



//Animated
class Animated:public Object
{
private:
	// Determines the current image section used in the sprite
	sf::Vector2i source;
public:
	Animated(float x, float y, int type);
	Animated(int type);
	Animated();

	void setSource(sf::Vector2i source);
	void setSourceX(int value);
	void setSourceY(int value);

	sf::Vector2i& getSoure();
	int getSourceX();
	int getSourceY();

	void update();
	void move(int x, int y);
}; 



//Character
class Character:public Animated
{
private:
	int health;
	sf::Vector2f velocity;
	bool jumpstate;
public:
	Character(float _x, float _y, int _type, int _health);
	Character(float x, float y, int type);
	Character(int _type);
	Character();

	void setHealth(int _health);
	void setJumpstate(bool state);

	bool getJumpstate();
	int getHealth();
	sf::Vector2f& getVelocity();

	void print();
}; // end Character 



//Level
class Level: public Object
{
private:
	std::vector<Animated> enemies;
	std::vector<sf::RectangleShape*> platforms;
	sf::Vector2f goal;
	bool victory;
	sf::Vector2f easterEggPosition;
	sf::Vector2f easterEggCondition;
	bool easterEgg;
	Character player;
public:
	Level();
	Level(int type);

	void setPlayer();
	void setPlayer(int type);
	void setPlayer(float x, float y, int type);

	void setVictory(bool _victory);
	bool getVictory();

	Character& getPlayer();
	std::vector<Animated>& getEnemies();
	int getEnemiesSize();
	std::vector<sf::RectangleShape*> getPlatforms();
	const sf::Vector2f& getGoal();
	sf::Vector2f getEasterEggCondition();
	sf::Vector2f getEasterEggPosition();
	bool getEasterEgg();
	void setEasterEgg(bool _easterEgg);
	
	void addEnemy(int type);
	void addEnemy(float x, float y, int type);
	void addPlatform(sf::RectangleShape *_platform);
	void removeEnemy(int _id);
	void init();
	void init(View& view);

	void createPlatform(sf::Vector2f _size, sf::Vector2f position);
	void createStairs(int number, sf::Vector2f position);
	void createReverseStairs(int number, sf::Vector2f pPosition);
	void createSmallPyramid(sf::Vector2f position);
	void createBigPyramid(sf::Vector2f position);
};


//Model
class Model
{
private:
	Level level;
public:
	Model(View& view);
	Level& getLevel();

	void updateView(View& view);
}; // end Model class */



//Controller
class Controller
{
private:
	Model& model;
	View& view;

	const float movespeed; 
	const float jumpspeed; 
	const float vMultiplicatorNormal; 
	const float vMultiplicatorRunning;
	sf::Time timePerFrame;
	bool victory;
	bool defeat;
	bool left;
	bool right;

	// Handles player movement
	void playerMovement();
	// Detects collision between player and individual object	
	bool detectCollisionBottom(Animated& _player, Animated& _object);
	bool playerCollisionLeft();
	bool playerCollisionRight();
	bool detectCollisionLeft(Animated& _player, Animated& _object);
	bool detectCollisionRight(Animated& _player, Animated& _object);
	bool detectPlatformCollisionBottom(Animated& _player, sf::RectangleShape *_platform);

public:
	Controller(Model& model, View& view);
	
	//Start the game
	void start();
};
