#pragma once
#include "Player.h"
#include <string>
#include "Level.h"
#include "Bestiary.h"

using namespace std;

class GameSystem
{	
	Level level;
	Player player;

	//miejsce, w ktorym zostaja stworzone obiekty klasy Level i Player

public:
	GameSystem();
	void playGame();
	void playerMove();
	void gameMenu();
};

