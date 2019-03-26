#include "Level.h"
#include <fstream>
#include <iostream>
#include <conio.h>

using namespace std;

//Konstruktor domy�lny klasy Level, tworz�cy obiekt tej klasy
Level::Level()
{
}

//Funkcja odpowiedzialna za pobieranie �wiata z pliku tekstowego i przetwarzaj�ca go.
//Wgrywa ona dany level do tablicy string�w, odczytuje poszczeg�lne znaki i w zale�no�ci od niego,
//ustawia pocz�tkow� pozycj� gracza, oraz tworzy tablic� z przeciwnikami.
void Level::load(string fileName, Player &player) {

	fstream file;
	file.open(fileName, ios::in);
	if (file.good() == false) {
		cout << "Nie udalo sie wczytac pliku!"; //w przypadku b��du, wy�wetl wiadomo�� �e nie uda�o si� otworzy� pliku
	}

	//wgrywamy linijka po linijce, wybrany �wiat, do naszej tablicy levelData

	string line;
	while (getline(file, line)) {
		levelData.push_back(line);
	}

	file.close(); //nie musi tu by�, po wyjsciu z funkcji automatycznie zamknie plik

	//przetwarzanie wybranego �wiata

	char tile;
	for (int i = 0; i < levelData.size(); i++) { //p�tla, kt�ra leci po ka�dym rz�dzie
		for (int j = 0; j < levelData[i].size(); j++) { //p�tla, kt�ra leci po ka�dej literce
			tile = levelData[i][j];
			switch (tile) {
			case '@': //Player
				player.setPosition(j, i);
				break;
			case 'g': //Goblin
				enemies.push_back(Enemy("Goblin", tile, 5, 3, 10));
				enemies.back().setPosition(j, i); 
				//natrafiaj�c w pliku na znak, kt�ry odpowiada potworowi, tworzymy konkretny obiekt klasy Enemy
				//dodajemy nowego przeciwnika na koniec tablicy i za pomoc� funkcji back()
				//odwo�ujemy si� do niego i przekazujemy jego pozycj� do konkretnych zmiennych
				break;
			case 'B': //Bandit
				enemies.push_back(Enemy("Bandit", tile, 25, 10, 35));
				enemies.back().setPosition(j, i);
				break;
			case 'S': //Snake
				enemies.push_back(Enemy("Snake", tile, 60, 22, 75));
				enemies.back().setPosition(j, i);
				break;
			case 'O': //Ogr
				enemies.push_back(Enemy("Ogr", tile, 200, 30, 300));
				enemies.back().setPosition(j, i);
				break;
			case 'D': //Dragon
				enemies.push_back(Enemy("Dragon", tile, 500, 50, 1000));
				enemies.back().setPosition(j, i);
				break;
			default:
				break;
			}
		}
	}
}

//Funkcja wypisuj�ca na ekran wczytany z pliku �wiat.
void Level::print() {
	system("cls");
	for (int i = 0; i < levelData.size(); i++) {
		cout << levelData[i] << endl;
	}

}

//Przci��ony operator, kt�ry w przypadku wci�ni�cia odpowiedniego klawisza wypisze nam na ekran
//informacje o poziomie naszej postaci,jego �yciu, sile ataku, i posiadanym do�wiadczeniu. 
ostream & operator<< (ostream &wyjscie, Player &player) {

	return wyjscie << "Player's level: " << player.getLevel() << endl << "Player's health: " << player.getHealth()
		<< endl << "Player's attack: " << player.getAttack() << endl << "Player's exp: "
		<< player.getExp() << endl;
}

//Funckja, kt�ra odpowiada za ruch postaci w grze, oraz interakcj� z ni� (wyj�cie z gry w dowolnym momencie czy te� wy�wietlenie
//statystyk naszej postaci). W zale�no�ci od argumentu, kt�ry zostanie do niej przekazany z funkcji PlayerMove() w klasie GameSystem,
//w t� stron� b�dziemy pr�bowali si� uda�, do takich indeks�w naszej tablicy b�dziemy chcieli si� dosta�..
void Level::movePlayer(char input, Player &player) {

	int playerX, playerY;
	
	player.getPosition(playerX, playerY);
	char moveTile;

	switch (input) {
		case 'w':
				
				moveTile = getTile(playerX, playerY - 1); 
				//Y-1 to ruch w g�r�, poniewa� im mniejszy indeks tablicy odpowiedzialn za kolumny tym wy�ej si� przesuwamy
				processPlayerMove(player, playerX, playerY - 1);
		
			break;
		case 's':
				moveTile = getTile(playerX, playerY + 1); 
				//Y+1 to ruch w d�, poniewa� im wi�kszy indeks tablicy odpowiedzialny za kolumny tym ni�ej si� przesuwamy
				processPlayerMove(player, playerX, playerY + 1);
			break;
		case 'a':
			
				moveTile = getTile(playerX - 1, playerY); 
				//X-1 to ruch w lewo, X to indeks odpowiedzialny za literki, pierwszym indeksem ka�dej kolummny jest 0
				//czyli musimy zmniejsza� indeks tablicy, je�li chcemy poruszy� si� postaci� w t� stron�
				processPlayerMove(player, playerX - 1, playerY);
				break;
			case 'd':
				
				moveTile = getTile(playerX + 1, playerY);
				//X+1 to ruch w prawo, X to indeks odpowiedzialny za literki, przesuwamy si� do ko��a tablicy odpowiedzialnej za literki
				//czyli musimy zwi�ksza� indeks tablicy, je�li chcemy poruszy� si� postaci� w t� stron�
				processPlayerMove(player, playerX +1, playerY);
					break;
			case 'q':
				
				//wyj�cie z gry, kt�re trzeba potwierdzi� konkretnym przyciskiem
				
				cout << "Czy na pewno chcesz wyjsc? t/n" << endl;
				char end_game;
				cin >> end_game;
				if (end_game == 't') {
					exit(0);
				}
				break;
			case 'i':
				cout << player;
				
				//przeci��ony operator dla klasy Player
				
				char i; i = _getch();
				break;
				default:
					cout << "Zly przycisk!" << endl;
					break;
				}
			}

//Funkcja przetwarzaj�ca ruch naszej postaci. Wykorzystujemy j� potem w funkcji movePlayer().
//Sprawdza ona miejsce, w kt�re chcemy przesun�� si� nasz� postaci�. 
void Level::processPlayerMove(Player &player, int targetX, int targetY) {

	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		
		//jesli znakiem w nast�pnym polu jest kropka, to oznacza, �e mo�emy si� tam przesun��. Po wykonanym ruchu poprzedni� pozycj� gracza
		//musimy zmieni� w '.',a w nowym miejscu musi pojawi� si� znak wskazuj�cy na nasz� posta� 
		
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':

		//w przypadku # nic si� nie dziej�, ma to na celu uniemo�liwienie naszej postaci przechodzenie przez �ciany
		
		break;
	default:
		
		//kazdy inny znak od '.' i '#' w miejscu, do kt�rego chcemy si� uda� nasz� postaci, oznacza przeciwnika 
		//co oznacza �e musimy wywo�a� wtedy funkcj� odpowiedzialn� za walk�
		
		battleMonster(player, targetX, targetY);
	}
}

//Funkcja zwracaj�c znak z tablicy string�w.
//Potrzebna do poruszania si� naszej postaci i walki z przeciwnikami.
char Level::getTile(int x, int y) {
	return levelData[y][x];
}

//Funkcja ustawiaj�ca dany znak w wybranym przez nasz miejscu w tablicy string�w.
//Potrzebna przy walce z przeciwnikami - po zabiciu potwora, wstawiamy np w jego miejsce '.'
//Tak samo jest przy poruszaniu - robi�c krok naprz�d postaci�, w miejsce gdzie stali�my wstawiamy kropk�,
//natomiast w miejsce gdzie chcemy si� uda� wstawiamy znak symbolizuj�cy nasz� posta�.
void Level::setTile(int x, int y, char tile) {
	levelData[y][x] = tile;
}

//Funkcja odpowiedzialna za walk� z potworem. Pobiera ona z tablicy przeciwnik�w po�o�enie ka�dego potwora.
//Sprawdza czy kolejny ruch naszej postaci i nowe po�ozenie postaci jest takie samo jak po�o�enie wroga.
//Je�li tak, to rozpoczyna si� walka, nasza postac atakuje pierwsza, a potem jest kolej danego przeciwnika.
//Korzysta z funkcji setTile(), by w przypadku naszej b�d� �mierci przeciwnika, odpowiednia zaaktualizowa� plansz�.
//Sprawdza r�wnie� czy nasz g��wny przeciwnik - Smok nie zosta� pokonany. Ko�czy gr� je�li znak w miejscu pocz�tkowego po�o�enia smoka to '.' 
void Level::battleMonster(Player &player, int targetX, int targetY) {

	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	for (int i = 0; i < enemies.size(); i++) {

		enemies[i].getPosition(enemyX, enemyY);

		//przechodzimy przez cala tablice z przeciwnikami, porownujemy wspolrzedne miejsca do ktorego chcemy sie uda� z wspolrzednymi polozenia przeciwnikow
		//i dowiadujemy sie dzieki temu na jakiego potwora natrafilismy

		if (targetX == enemyX && targetY == enemyY) {
			
			//je�li indeksy w tablicy, w miejscu do kt�rego chcemy si� przesun�� s� takie jak 
			//indeksy odpowiadaj�ce po�o�eniu jakiego� konkretnego przeciwnika, to ropoczynamy z nim walk�
				
			int players_attack = enemies[i].get_e_health() - player.getAttack();
				cout << "You attacked. Enemy's HP: " << players_attack << endl;
				enemies[i].set_e_health(players_attack);
				
				//system walki - nasza posta� atakuj� jako pierwsza  
				
				if (enemies[i].get_e_health() <= 0) {
					setTile(targetX, targetY, '.');
					print();
					cout << "Monster died";
				
					//sprawdzamy czy po ataku, zycie przeciwnika nie jest mniejsze od 0

					if ( (enemies[i].get_e_health() <= 0 ) && (enemies[i].get_e_name() == "Dragon" ) ) {

						system("cls");
						cout << "You killed the dragon. You searched his cave for treasures," << endl
							<< "but nothing was there. You also did not receive the" << endl
							<< "dragon's strength. The only reward is the saved kingdom" << endl
							<< "and a gratitude of the king. Again... Another day of being a hero..." << endl << endl << "YOU WON!!!";
						char d; d = _getch();
						exit(0);

						//jesli nazwa przciwnika to "Dragon" i jego �ycie jest mniejsze od 0
						//wyswietl napisy koncowe dla wygranej i pozniej zakoncz gre

					}
						
					player.setExp(enemies[i].get_exp_value());
					return; 

					//w przypadku pokonania przeciwnika wyjd� z funkcji,po to by martwy przeciwnik nie zadawa� obra�en naszej postaci
					//walka polega na odj�ciu od aktualnego �ycia si�y ataku, je�li �ycie jest mniejsza od zera, przeciwnik lub nasza posta� ginie
					//je�li pokonamy smoka to wyczy�� ekran, wy�wietl napisy ko�cowe w przypadku wygranej i zako�cz gr�
				}

				int enemys_attack = player.getHealth() - enemies[i].get_e_attack();
				cout << "Enemy attacked. Your's HP: " << enemys_attack;
				player.setHealth(enemys_attack);

				//system walki - teraz zaatakowal nas przeciwnik

				if (player.getHealth() <= 0) {
					setTile( playerX, playerY, 'x');
					print();
					system("cls");
					cout << "You died. The Dragon killed you." << endl
						<< "You did not complete a task, that your king gave you." << endl
						<< "The enraged dragon, along with his army of monsters," << endl
						<< "burned the whole kingdom. Nobody survived." << endl << endl << "GAME OVER!!!";
					char d; d = _getch();
					exit(0);

					//w przypadku, gdy nasze �ycie bedzie mniejsze od 0
					//zamien nasz znak w 'x' i wyswietl napisy koncowe dla porazki
					//i zakoncz gre

				}

				return; 
		
				//przerywam dzia�anie funkcji battleMonster() i zwracam wartosci po jednej rundzie, potem np moge odejsc - WA�NE!!!!
		
		}
	}
}
