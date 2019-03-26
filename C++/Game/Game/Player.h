#pragma once
class Player
{
	int level;
	int health;
	int attack;
	int experience;
	int x;
	int y;
public:
	Player();
	void init(int _level, int _health, int _attack, int _experience);
	int getHealth();
	int getAttack();
	int getLevel();
	int getExp();
	void getPosition(int &_x, int &_y);
	void setHealth(int hp);
	void setExp(int exp);
	void setPosition(int _x, int _y);
	void levelUP();
};

