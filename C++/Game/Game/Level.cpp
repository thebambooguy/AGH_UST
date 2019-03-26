#include "Level.h"
#include <fstream>
#include <iostream>
#include <conio.h>

using namespace std;

//Konstruktor domyœlny klasy Level, tworz¹cy obiekt tej klasy
Level::Level()
{
}

//Funkcja odpowiedzialna za pobieranie œwiata z pliku tekstowego i przetwarzaj¹ca go.
//Wgrywa ona dany level do tablicy stringów, odczytuje poszczególne znaki i w zale¿noœci od niego,
//ustawia pocz¹tkow¹ pozycjê gracza, oraz tworzy tablicê z przeciwnikami.
void Level::load(string fileName, Player &player) {

	fstream file;
	file.open(fileName, ios::in);
	if (file.good() == false) {
		cout << "Nie udalo sie wczytac pliku!"; //w przypadku b³êdu, wyœwetl wiadomoœæ ¿e nie uda³o siê otworzyæ pliku
	}

	//wgrywamy linijka po linijce, wybrany œwiat, do naszej tablicy levelData

	string line;
	while (getline(file, line)) {
		levelData.push_back(line);
	}

	file.close(); //nie musi tu byæ, po wyjsciu z funkcji automatycznie zamknie plik

	//przetwarzanie wybranego œwiata

	char tile;
	for (int i = 0; i < levelData.size(); i++) { //pêtla, która leci po ka¿dym rzêdzie
		for (int j = 0; j < levelData[i].size(); j++) { //pêtla, która leci po ka¿dej literce
			tile = levelData[i][j];
			switch (tile) {
			case '@': //Player
				player.setPosition(j, i);
				break;
			case 'g': //Goblin
				enemies.push_back(Enemy("Goblin", tile, 5, 3, 10));
				enemies.back().setPosition(j, i); 
				//natrafiaj¹c w pliku na znak, który odpowiada potworowi, tworzymy konkretny obiekt klasy Enemy
				//dodajemy nowego przeciwnika na koniec tablicy i za pomoc¹ funkcji back()
				//odwo³ujemy siê do niego i przekazujemy jego pozycjê do konkretnych zmiennych
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

//Funkcja wypisuj¹ca na ekran wczytany z pliku œwiat.
void Level::print() {
	system("cls");
	for (int i = 0; i < levelData.size(); i++) {
		cout << levelData[i] << endl;
	}

}

//Przci¹¿ony operator, który w przypadku wciœniêcia odpowiedniego klawisza wypisze nam na ekran
//informacje o poziomie naszej postaci,jego ¿yciu, sile ataku, i posiadanym doœwiadczeniu. 
ostream & operator<< (ostream &wyjscie, Player &player) {

	return wyjscie << "Player's level: " << player.getLevel() << endl << "Player's health: " << player.getHealth()
		<< endl << "Player's attack: " << player.getAttack() << endl << "Player's exp: "
		<< player.getExp() << endl;
}

//Funckja, która odpowiada za ruch postaci w grze, oraz interakcjê z ni¹ (wyjœcie z gry w dowolnym momencie czy te¿ wyœwietlenie
//statystyk naszej postaci). W zale¿noœci od argumentu, który zostanie do niej przekazany z funkcji PlayerMove() w klasie GameSystem,
//w t¹ stronê bêdziemy próbowali siê udaæ, do takich indeksów naszej tablicy bêdziemy chcieli siê dostaæ..
void Level::movePlayer(char input, Player &player) {

	int playerX, playerY;
	
	player.getPosition(playerX, playerY);
	char moveTile;

	switch (input) {
		case 'w':
				
				moveTile = getTile(playerX, playerY - 1); 
				//Y-1 to ruch w górê, poniewa¿ im mniejszy indeks tablicy odpowiedzialn za kolumny tym wy¿ej siê przesuwamy
				processPlayerMove(player, playerX, playerY - 1);
		
			break;
		case 's':
				moveTile = getTile(playerX, playerY + 1); 
				//Y+1 to ruch w dó³, poniewa¿ im wiêkszy indeks tablicy odpowiedzialny za kolumny tym ni¿ej siê przesuwamy
				processPlayerMove(player, playerX, playerY + 1);
			break;
		case 'a':
			
				moveTile = getTile(playerX - 1, playerY); 
				//X-1 to ruch w lewo, X to indeks odpowiedzialny za literki, pierwszym indeksem ka¿dej kolummny jest 0
				//czyli musimy zmniejszaæ indeks tablicy, jeœli chcemy poruszyæ siê postaci¹ w tê stronê
				processPlayerMove(player, playerX - 1, playerY);
				break;
			case 'd':
				
				moveTile = getTile(playerX + 1, playerY);
				//X+1 to ruch w prawo, X to indeks odpowiedzialny za literki, przesuwamy siê do koñæa tablicy odpowiedzialnej za literki
				//czyli musimy zwiêkszaæ indeks tablicy, jeœli chcemy poruszyæ siê postaci¹ w tê stronê
				processPlayerMove(player, playerX +1, playerY);
					break;
			case 'q':
				
				//wyjœcie z gry, które trzeba potwierdziæ konkretnym przyciskiem
				
				cout << "Czy na pewno chcesz wyjsc? t/n" << endl;
				char end_game;
				cin >> end_game;
				if (end_game == 't') {
					exit(0);
				}
				break;
			case 'i':
				cout << player;
				
				//przeci¹¿ony operator dla klasy Player
				
				char i; i = _getch();
				break;
				default:
					cout << "Zly przycisk!" << endl;
					break;
				}
			}

//Funkcja przetwarzaj¹ca ruch naszej postaci. Wykorzystujemy j¹ potem w funkcji movePlayer().
//Sprawdza ona miejsce, w które chcemy przesun¹æ siê nasz¹ postaci¹. 
void Level::processPlayerMove(Player &player, int targetX, int targetY) {

	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		
		//jesli znakiem w nastêpnym polu jest kropka, to oznacza, ¿e mo¿emy siê tam przesun¹æ. Po wykonanym ruchu poprzedni¹ pozycjê gracza
		//musimy zmieniæ w '.',a w nowym miejscu musi pojawiæ siê znak wskazuj¹cy na nasz¹ postaæ 
		
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':

		//w przypadku # nic siê nie dziejê, ma to na celu uniemo¿liwienie naszej postaci przechodzenie przez œciany
		
		break;
	default:
		
		//kazdy inny znak od '.' i '#' w miejscu, do którego chcemy siê udaæ nasz¹ postaci, oznacza przeciwnika 
		//co oznacza ¿e musimy wywo³aæ wtedy funkcjê odpowiedzialn¹ za walkê
		
		battleMonster(player, targetX, targetY);
	}
}

//Funkcja zwracaj¹c znak z tablicy stringów.
//Potrzebna do poruszania siê naszej postaci i walki z przeciwnikami.
char Level::getTile(int x, int y) {
	return levelData[y][x];
}

//Funkcja ustawiaj¹ca dany znak w wybranym przez nasz miejscu w tablicy stringów.
//Potrzebna przy walce z przeciwnikami - po zabiciu potwora, wstawiamy np w jego miejsce '.'
//Tak samo jest przy poruszaniu - robi¹c krok naprzód postaci¹, w miejsce gdzie staliœmy wstawiamy kropkê,
//natomiast w miejsce gdzie chcemy siê udaæ wstawiamy znak symbolizuj¹cy nasz¹ postaæ.
void Level::setTile(int x, int y, char tile) {
	levelData[y][x] = tile;
}

//Funkcja odpowiedzialna za walkê z potworem. Pobiera ona z tablicy przeciwników po³o¿enie ka¿dego potwora.
//Sprawdza czy kolejny ruch naszej postaci i nowe po³ozenie postaci jest takie samo jak po³o¿enie wroga.
//Jeœli tak, to rozpoczyna siê walka, nasza postac atakuje pierwsza, a potem jest kolej danego przeciwnika.
//Korzysta z funkcji setTile(), by w przypadku naszej b¹dŸ œmierci przeciwnika, odpowiednia zaaktualizowaæ planszê.
//Sprawdza równie¿ czy nasz g³ówny przeciwnik - Smok nie zosta³ pokonany. Koñczy grê jeœli znak w miejscu pocz¹tkowego po³o¿enia smoka to '.' 
void Level::battleMonster(Player &player, int targetX, int targetY) {

	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	for (int i = 0; i < enemies.size(); i++) {

		enemies[i].getPosition(enemyX, enemyY);

		//przechodzimy przez cala tablice z przeciwnikami, porownujemy wspolrzedne miejsca do ktorego chcemy sie udaæ z wspolrzednymi polozenia przeciwnikow
		//i dowiadujemy sie dzieki temu na jakiego potwora natrafilismy

		if (targetX == enemyX && targetY == enemyY) {
			
			//jeœli indeksy w tablicy, w miejscu do którego chcemy siê przesun¹æ s¹ takie jak 
			//indeksy odpowiadaj¹ce po³o¿eniu jakiegoœ konkretnego przeciwnika, to ropoczynamy z nim walkê
				
			int players_attack = enemies[i].get_e_health() - player.getAttack();
				cout << "You attacked. Enemy's HP: " << players_attack << endl;
				enemies[i].set_e_health(players_attack);
				
				//system walki - nasza postaæ atakujê jako pierwsza  
				
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

						//jesli nazwa przciwnika to "Dragon" i jego ¿ycie jest mniejsze od 0
						//wyswietl napisy koncowe dla wygranej i pozniej zakoncz gre

					}
						
					player.setExp(enemies[i].get_exp_value());
					return; 

					//w przypadku pokonania przeciwnika wyjdŸ z funkcji,po to by martwy przeciwnik nie zadawa³ obra¿en naszej postaci
					//walka polega na odjêciu od aktualnego ¿ycia si³y ataku, jeœli ¿ycie jest mniejsza od zera, przeciwnik lub nasza postaæ ginie
					//jeœli pokonamy smoka to wyczyœæ ekran, wyœwietl napisy koñcowe w przypadku wygranej i zakoñcz grê
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

					//w przypadku, gdy nasze ¿ycie bedzie mniejsze od 0
					//zamien nasz znak w 'x' i wyswietl napisy koncowe dla porazki
					//i zakoncz gre

				}

				return; 
		
				//przerywam dzia³anie funkcji battleMonster() i zwracam wartosci po jednej rundzie, potem np moge odejsc - WA¯NE!!!!
		
		}
	}
}
