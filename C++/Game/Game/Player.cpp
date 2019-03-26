#include "Player.h"
#include <iostream>

using namespace std;

//Konstruktor domy�lny klasy Player, kt�ry tworzy obiekt.
Player::Player()
{
}

//Funkcja inicjalizuj�ca gracza i przypisuj�ca pocz�tkowe warto�ci jego atrybutom.
void Player::init(int _level, int _health, int _attack, int _experience) {
	level = _level;
	health = _health;
	attack = _attack;
	experience = _experience;
}

//Gettery
int Player::getHealth() { return health; }
int Player::getAttack() { return attack; }
int Player::getLevel() { return level; }
int Player::getExp() { return experience; }
void Player::getPosition(int &_x, int &_y) {
	_x = x;
	_y = y;
}

//Settery
void Player::setHealth(int hp) { health = hp; }
void Player::setExp(int exp) { experience += exp; }
void Player::setPosition(int _x, int _y) {
	x = _x;
	y = _y;
}

//Funkcja odpowiedzialna za zdobywanie kolejnego poziomu przez nasz� posta�.
//W funkcji mamy tablic�, kt�rej elementami s� warto�ci do�wiadczenia jakie trzeba mie� by zdoby� nast�pny poziom.
//Iteratorem funckji jest nasz aktualny poziom. Po przekroczeniu odpowiedniej warto�ci, nasz poziom zwi�ksza si� 
//o jeden, odzyskujemy troch� �ycia i nasza si�a ataku jest wi�ksza.  
void Player::levelUP() {

	int required_experience[] = { 10, 50, 80, 120, 150 , 200 , 250 , 350 , 500 , 700 , 1000 };
	while (experience >= required_experience[level]) {
		cout << endl << "You gain a level" << endl;
		level += 1;
		health += 30;
		attack += 8;
	}
}