#include "Bestiary.h"
#include <fstream>
#include <iostream>

//Konstruktor domyœlny klasy Bestiary, który podczas tworzenia obiektu
//korzysta z poni¿szych funkcji czyli od razu wczytujemy tekst z pliku i wyœwietlamy go
Bestiary::Bestiary()
{
	load("bestiary.txt");
	print();

}

//Funkcja wczytuj¹ca do naszej gry bestiariusz z pliku tekstowego
void Bestiary::load( string fileName) {


	fstream file;
	file.open(fileName, ios::in);
	if (file.good() == false) {
		cout << "Nie udalo sie wczytac pliku!";
	}

	string line;
	while (getline(file, line)) {
		bestiaryData.push_back(line);
	}

	file.close();
}

//Funkcja, która wyczyœci ekran i wypisze na ekran zawartoœæ pobran¹ z pliku tekstowego
void Bestiary::print() {

	system("cls");
	for (int i = 0; i < bestiaryData.size(); i++) {
		cout << bestiaryData[i] << endl;
	}


}