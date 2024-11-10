#include<iostream>
#include <OGL3D/Game/OGame.h>

int main()
{
	try
	{
		OGame game;
		game.run();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}