#include <iostream>
#include "irrKlang.h"
using namespace irrklang;


#pragma comment(lib, "irrKlang.lib")
int main()
{

	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
		return 0; // error starting up the engine

	  // play some sound stream, looped
	engine->play2D("gun.mp3", true);

	char i = 0;
	std::cin >> i; // wait for user to press some key

	engine->drop(); // delete engine



	system("pause");
}