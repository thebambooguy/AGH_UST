#pragma once
#include <vector>
#include <string>
#include <vector>
#include "Player.h"
#include "Enemy.h"

using namespace std;

class Level
{
	vector <string> levelData; //tablica string�w w kt�rej znajduj� si� wczytany z pliku �wiat
	vector <Enemy> enemies; //tablica obiekt�w klasy Enemy, znajduj� sie tam informacje dotycz�ce naszych przeciwnikow

public:
	Level();
	void load(string fileName, Player &player);
	void print();
	void movePlayer(char input, Player &player);
	char getTile(int x, int y);
	void setTile(int x, int y, char tile);
	void processPlayerMove(Player &player, int targetX, int targetY);
	void battleMonster(Player &player, int targetX, int targetY);

};

