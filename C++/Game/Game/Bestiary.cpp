#include "Bestiary.h"
#include <fstream>
#include <iostream>

//Konstruktor domy�lny klasy Bestiary, kt�ry podczas tworzenia obiektu
//korzysta z poni�szych funkcji czyli od razu wczytujemy tekst z pliku i wy�wietlamy go
Bestiary::Bestiary()
{
	load("bestiary.txt");
	print();

}

//Funkcja wczytuj�ca do naszej gry bestiariusz z pliku tekstowego
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

//Funkcja, kt�ra wyczy�ci ekran i wypisze na ekran zawarto�� pobran� z pliku tekstowego
void Bestiary::print() {

	system("cls");
	for (int i = 0; i < bestiaryData.size(); i++) {
		cout << bestiaryData[i] << endl;
	}


}