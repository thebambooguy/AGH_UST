#include "GameSystem.h"
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

//Funkcja, pozwalaj�ca nam na ci�g�� gr�. Mowa tu o ruchu postaci, 
//aktualizowaniu �wiata na bie��co, oraz w przypadku posiadania odpowiedniej
//ilo�ci do�wiadczenia, awansowaniu postaci na kolejny level.
void GameSystem::playGame(){
	bool isDone = false;
	while (isDone != true) {
		level.print();
		playerMove();
		player.levelUP();
	}
}

//Funkcja, kt�ra pokazuj� mo�liwe do wci�ni�cia klawisze i przekazuj� wci�ni�ty klawisz
//do funkcji w klasie Level, kt�ra jest odpowiedzialna za ruch naszej postaci 
void GameSystem::playerMove() {
	char input;
	cout << "End game (q), Player's stats (i), Enter a move command (w/s/a/d): " << endl;
	input = _getch();
	// dodane po to aby nie wciskac za kazdym razemm 'enter' po wybraniu kierunku ruchu
	//potrzebna do tego dodatkowa biblioteka - conio.h
	level.movePlayer(input, player);
}

//Funckja odpowiedzialna za menu gry. W menu gry mo�emy wybra� �wiat i zacz�� gra�, 
//przeczyta� instrukcj�, oraz zagl�dn�� do bestiariusza, by lepiej przygotowa� si� do gry
void GameSystem::gameMenu() {
	
	system("cls");
	cout << "	DRAGON ASCII SLAYER		" << endl << endl;
	cout << "1. Start Game " << endl;
	cout << "2. Instruction" << endl;
	cout << "3. Bestiary" << endl;
	cout << "4. Exit" << endl;
	char menu; menu = _getch();
	string levelFileName{};
	switch (menu) {
	case '1':
		system("cls");
		cout << "Choose level: " << endl << endl << "1. Forest - Easy" << endl << "2. City - Medium" << endl << "3. Castle - Hard" << endl << "4. Dragon's cave - Impossible" << endl;
		char lev; lev = _getch(); 
		//w zaleznosci od wcisnietego klawisza, w takim swiecie rozgrywana bedzie gra
		switch (lev) {
			case '1':
				levelFileName = "level1.txt";
			break;
			case '2':
				levelFileName = "level2.txt";
			break;
			case '3':
				levelFileName = "level3.txt";
			break;
			case '4':
				levelFileName = "level4.txt";
			break;
			default:
			system("cls");
			cout << "You pressed a wrong button."  << endl << "You need to start your game again and choose a level from the existing ones.";
			char d; d = _getch();
			gameMenu();
			break;
		}

		level.load(levelFileName, player);
		//wczytanie wybranego przez nas swiata z pliku
		system("cls");
		cout << "You are a medieval knight who was sent by the king to kill the Dragon." << endl << "As the best knight and hero in the eyes of the people, you agree." << endl
			<< "Nobody has succeeded so far. The Dragon has threatened the whole kingdom" << endl << "for a long time, he is the cause of all evil and he is the one responsible" << endl
			<< "for monsters. You must get to the Dragon's cave and kill him. Legends say" << endl << "that after killing the Dragon you will gain his power and all his treasures." << endl << endl
			<< "Are you ready...???";
		char d; d = _getch();
		system("cls");
		playGame();
		break;
	case '2':
		system("cls");
		cout << "Move command: 'w' - up, 's' - down, 'a' - left, 'd' - right" << endl << "Depending on what you press, player will move in that direction." << endl << endl;
		cout << "Player's stats: 'i'" << endl << "If you press 'i' you will be able to see your current level," << endl << "amount of health and strength of your attack." << endl << endl;
		cout << "Exit the game: 'q'" << endl << "If you press 'q' you will be asked to confirm your decision." << endl << "After that, you will exit the game." << endl << endl;
		cout << "Your mission is to kill the Dragon. If you kill him, you will complete" << endl <<  "your mission and you end the game. If you die earlier, you will need" << endl << "to start your journey from beggining.";
			char e; e = _getch();
			gameMenu();
			break;
	case '3':
		Bestiary();
		// miejsce w ktorym zostaje stworzony obiekt klasy Bestiary
		char f; f = _getch();
		gameMenu();
			break;
	case '4':
		exit(0);
	}
}

//Konstruktor, ktory zestawia nam gr�. Inicjalizuj� player'a i uruchamia menu gry.
//Jako jedyny wyst�puje w Game.cpp.
GameSystem::GameSystem() {

	player.init(1, 100, 10, 0);
	gameMenu();
}
