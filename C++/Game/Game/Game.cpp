// Game.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "GameSystem.h"

using namespace std;

int main()
{
	//w głównej funkcji mamy tylko konstruktor klasy GameSystem
	//ma to na celu zadbanie o estetykę programu
	//klasa "GameSystem" została stworzona w tym samym celu
	//Zawiera ona w sobie najważniejsze funkcje z innych klas
	//które potrzebne są do funkcjonowania gry
	GameSystem();
    return 0;
}

