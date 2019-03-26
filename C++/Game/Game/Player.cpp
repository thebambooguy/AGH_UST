#include "Player.h"
#include <iostream>

using namespace std;

//Konstruktor domyœlny klasy Player, który tworzy obiekt.
Player::Player()
{
}

//Funkcja inicjalizuj¹ca gracza i przypisuj¹ca pocz¹tkowe wartoœci jego atrybutom.
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

//Funkcja odpowiedzialna za zdobywanie kolejnego poziomu przez nasz¹ postaæ.
//W funkcji mamy tablicê, której elementami s¹ wartoœci doœwiadczenia jakie trzeba mieæ by zdobyæ nastêpny poziom.
//Iteratorem funckji jest nasz aktualny poziom. Po przekroczeniu odpowiedniej wartoœci, nasz poziom zwiêksza siê 
//o jeden, odzyskujemy trochê ¿ycia i nasza si³a ataku jest wiêksza.  
void Player::levelUP() {

	int required_experience[] = { 10, 50, 80, 120, 150 , 200 , 250 , 350 , 500 , 700 , 1000 };
	while (experience >= required_experience[level]) {
		cout << endl << "You gain a level" << endl;
		level += 1;
		health += 30;
		attack += 8;
	}
}