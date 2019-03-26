#pragma once
#include <string>


using namespace std; //musimy to miec aby string e_name dzialal - inaczej wyskakuje blad
//nieznany specyfikator prze³¹czania

class Enemy
{
	string e_name;
	char e_tile;
	int e_health;
	int e_attack;
	int exp_value;
	int x;
	int y;

public:
	Enemy( string name, char tile, int health, int attack,int exp_val);
	string get_e_name();
	int get_e_health();
	int get_e_attack();
	int get_exp_value();
	int get_e_Tile();
	void getPosition(int &_x, int &_y);
	void set_e_health( int e_hp);
	void setPosition(int _x, int _y);
	

};

