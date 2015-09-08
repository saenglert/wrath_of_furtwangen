#include <gameConsole.h>

int main()
{
	View view;

	Model model(view);

	model.getLevel().setPlayer(20.0, 300.0, 1);
	model.getLevel().getPlayer().setHealth(3);
	model.getLevel().addEnemy(250, FLOORHEIGHT - 3*BLOCKHEIGHT -32, 2);
	model.getLevel().addEnemy(1120, FLOORHEIGHT -32, 2);
	model.getLevel().addEnemy(1195, FLOORHEIGHT  - BLOCKHEIGHT - 100 -32, 3);
	model.getLevel().addEnemy(model.getLevel().getEasterEggCondition().x + 100, model.getLevel().getEasterEggCondition().y - 32, 3);

	model.getLevel().addEnemy(1520, GROUNDHEIGHT -32, 3);

	Controller controller(model,view);

	controller.start();

    return 0;
} // end main function