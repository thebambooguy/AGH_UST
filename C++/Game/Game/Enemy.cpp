#include "Enemy.h"

//Konstruktor parametryczny klasy Enemy, tworz¹cy obiekt tej klasy i przypisuj¹cy
//od razu jej atrybutom jakieœ konkretne wartoœci. Wykorzystujemy go potem przy
//tworzeniu tablicy obiektów z przeciwnikami. Jego zastosowanie znacznie u³atwia
//stworzenie takiej tablicy
Enemy::Enemy(string name, char tile, int health, int attack, int exp_val)
{
	e_name = name;
	e_tile = tile;
	e_health = health;
	e_attack = attack;
	exp_value = exp_val;

}

//Gettery
string Enemy::get_e_name() { return e_name; }
int Enemy::get_e_health() { return e_health; }
int Enemy::get_e_attack() { return e_attack; }
int Enemy::get_exp_value() { return exp_value; }
int Enemy::get_e_Tile() { return e_tile; }
void Enemy::getPosition(int &_x, int &_y) {
	_x = x;
	_y = y;
}
//Settery
void Enemy::set_e_health(int e_hp) { e_health = e_hp; }
void Enemy::setPosition(int _x, int _y) {
	x = _x;
	y = _y;
}
