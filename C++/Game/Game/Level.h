#pragma once
#include <vector>
#include <string>
#include <vector>
#include "Player.h"
#include "Enemy.h"

using namespace std;

class Level
{
	vector <string> levelData; //tablica stringów w której znajdujê siê wczytany z pliku œwiat
	vector <Enemy> enemies; //tablica obiektów klasy Enemy, znajduj¹ sie tam informacje dotycz¹ce naszych przeciwnikow

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

