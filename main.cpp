#include <iostream>
#include <fstream>

using namespace std;

struct Player{
	string nickname;

	float wins;
	float loses;
	float percent_wins;
	float percent_loses;
};

/*

	|---|---|---|
	| 0 | 1 | 2 |
	|---|---|---|
	| 3 | 4 | 5 |
	|---|---|---|
	| 6 | 7 | 8 |
	|---|---|---|
*/
struct Board{
	Player players[2];
	Player last_move;
	char field_values[3][3] = {{' ', ' ', ' '},
						 	   {' ', ' ', ' '},
							   {' ', ' ', ' '}};
	bool empty_fields[9] = {true, true, true, true, true, true, true, true, true};
	bool end = false;
};

Board board;


void createPlayer(string nickname);
void deletePlayer(string nickname);
void renderPlayerData(Player p);
void renderPlayersData(Player p[]);
string* getAllPlayersList();
Player* getAllPlayersData();
Player getPlayer(string nickname);
Player getPlayerByWins();
void updateWinsPlayer(string nickname);
void updateLosesPlayer(string nickname);
bool playerDoesExist(string nickname);
int countPlayers();

void renderMenu();
void renderMargin(int margin);
void renderMarginBottom(int margin);
void renderBoard();
void deletePlayerScene();
void createPlayerScene();
void choosePlayersProfileScene();
void gameScene();
void setBoardFieldValue(int field_number, char ch);
void checkWinner();
void resetBoard(bool all);

void clearWindow();

int main(){
	setlocale(LC_ALL, "");

	int option;

	while(true){
		renderMenu();

		cin >> option;

		if(option == 1){
			int n = countPlayers();

			if(n < 2){
				clearWindow();
				cout << "Aby móc zagrać musisz utworzyć co najmniej dwa profile gracza." << endl;
				continue;
			} else {
				choosePlayersProfileScene();
				gameScene();
			}
		} else if(option == 2){
			clearWindow();
			Player *players = getAllPlayersData();
			renderPlayersData(players);

			delete[] players;
			continue;
		} else if(option == 3){
			clearWindow();
			Player player = getPlayerByWins();
			renderPlayerData(player);

			continue;
		} else if(option == 4){
			createPlayerScene();
			continue;
		} else if(option == 5){
			deletePlayerScene();
			continue;
		} else if(option == 6){
			break;
		}
	}
}

void gameScene(){
	while(true){
		while(true && !board.end){
			clearWindow();
			renderBoard();

			while(true && !board.end){
				int field_number;
				cout << board.players[0].nickname << " twoja kolej. Podaj numer pola od 0 - 8: ";
				cin >> field_number;

				if(field_number < 0 || field_number > 8 || board.empty_fields[field_number] == false){
					continue;
				}

				setBoardFieldValue(field_number, 'X');
				board.last_move = board.players[0];
				break;
			}

			clearWindow();
			renderBoard();
			while(true && !board.end){
				int field_number;
				cout << board.players[1].nickname << " twoja kolej. Podaj numer pola od 0 - 8: ";
				cin >> field_number;

				if(field_number < 0 || field_number > 8 || board.empty_fields[field_number] == false){
					continue;
				}

				setBoardFieldValue(field_number, 'O');
				board.last_move = board.players[1];
				break;
			}
		}

		clearWindow();
		renderBoard();

		cout << "Wygrał " << board.last_move.nickname << endl;
		updateWinsPlayer(board.last_move.nickname);
		if(board.players[0].nickname != board.last_move.nickname){
			updateLosesPlayer(board.players[0].nickname);
		} else {
			updateLosesPlayer(board.players[1].nickname);
		}

		cout << "1. Zagraj ponownie" << endl;
		cout << "2. Wyjdz" << endl;
		cout << "Wybierz opcję: ";
		int option;
		cin >>  option;
		if(option == 1){
			resetBoard(false);
			continue;
		} else if(option == 2){
			clearWindow();
			resetBoard(true);
			break;
		}
	}
}

void deletePlayerScene(){
	while(true){
		string nickname;
		cout << "Podaj nickname: ";
		cin >> nickname;

		if(!playerDoesExist(nickname)){
			clearWindow();
			cout << "Nie znaleziono gracza o nicku " << nickname << ". Spróbuj ponownie." << endl;
			continue;
		} else {
			clearWindow();
			deletePlayer(nickname);
			break;
		}
	}
}

void createPlayerScene(){
	while(true){
		string nickname;
		cout << "Podaj nickname: ";
		cin >> nickname;

		if(playerDoesExist(nickname)){
			clearWindow();
			cout << "Podany nick " << nickname << " jest zajęty. Spróbuj ponownie." << endl;
			continue;
		} else {
			clearWindow();
			createPlayer(nickname);
			break;
		}
	}
}

void choosePlayersProfileScene(){
	while(true){
		string nickname;
		cout << "Wybierz konto gracza 1: ";
		cin >> nickname;

		if(!playerDoesExist(nickname)){
			clearWindow();
			cout << "Profil gracza o podanym nicku " << nickname << " nie istnieje. Spróbuj ponownie." << endl;
			continue;
		} else {
			clearWindow();
			board.players[0] = getPlayer(nickname);
			break;
		}
	}

	while(true){
		string nickname;
		cout << "Wybierz konto gracza 2: ";
		cin >> nickname;

		if(!playerDoesExist(nickname)){
			clearWindow();
			cout << "Profil gracza o podanym nicku " << nickname << " nie istnieje. Spróbuj ponownie." << endl;
			continue;
		} else if(nickname == board.players[0].nickname){
			clearWindow();
			cout << "Profil gracza o podanym nicku " << nickname << " został już wybrany przez twojego przeciwnika. Spróbuj ponownie." << endl;
			continue;
		} else {
			clearWindow();
			board.players[1] = getPlayer(nickname);
			break;
		}
	}
}

void renderMenu(){
	cout << "1. Start" << endl;
	cout << "2. Pokaż wszystkich graczy oraz ich statyski" << endl;
	cout << "3. Pokaż gracza z największą liczbą wygranych" << endl;
	cout << "4. Stwórz profil gracza" << endl;
	cout << "5. Usuń profil gracza" << endl;
	cout << "6. Wyjście" << endl;
	cout << "Wybierz opcję: ";
}

void renderMargin(int margin = 10){
	for(int j = 0; j < margin; j++){
		cout << " ";
	}
}

void renderMarginBottom(int margin = 10){
	for(int j = 0; j < margin; j++){
		cout << endl;
	}
}

void clearWindow(){
	for(int i = 0; i < 99; i++){
		cout << endl;
	}
}

void resetBoard(bool all){
	if(all){
		Board new_board;
		board = new_board;
	} else {
		Board new_board;
		Player one = board.players[0];
		Player two = board.players[1];
		new_board.players[0] = one;
		new_board.players[1] = two;
		board = new_board;
	}
}

void renderBoard(){

	clearWindow();

	renderMargin(2);
	cout << "Lista graczy: " << board.players[0].nickname << ", " << board.players[1].nickname << endl;
	renderMarginBottom(2);

	for(int i = 0; i < 3; i++){

		renderMargin();
		cout << "|---|---|---|" << endl;

		renderMargin();
		// Główna pętla wypisująca na ekran plansze
		for(int j = 0; j < 3; j++){
			cout << "| " << board.field_values[i][j];

			if(j < 2){
				cout << " ";
			}
		}
		cout << " |";
		cout << endl;
	}

	renderMargin();
	cout << "|---|---|---|" << endl;
	renderMarginBottom(3);
}

void checkWinner(){
	int winning_pos[8][3] = {
							{0, 1, 2},
						    {3, 4, 5},
						    {6, 7, 8},
						    {0, 3, 6},
						    {1, 4, 7},
						    {2, 5, 8},
						    {0, 4, 8},
						    {2, 4, 6}
						};

	for(int i = 0; i < 8; i++){
		if(i >= 0 || !i > 3){
			for(int j = 0; j < 8; j++){
				if((board.field_values[0][winning_pos[j][0]] == board.field_values[0][winning_pos[j][1]]) && (board.field_values[0][winning_pos[j][1]] == board.field_values[0][winning_pos[j][2]]) && !board.empty_fields[winning_pos[j][0]]){
					board.end = true;
				}
			}
		} else if(i >= 4 || !i > 5){
			for(int j = 0; j < 8; j++){
				if((board.field_values[1][winning_pos[j][0]] == board.field_values[1][winning_pos[j][1]]) && (board.field_values[1][winning_pos[j][1]] == board.field_values[1][winning_pos[j][2]]) && !board.empty_fields[winning_pos[j][0]]){
					board.end = true;
				}
			}
		} else if(i >= 6 || !i > 8){
			for(int j = 0; j < 8; j++){
				if((board.field_values[2][winning_pos[j][0]] == board.field_values[2][winning_pos[j][1]]) && (board.field_values[2][winning_pos[j][1]] == board.field_values[2][winning_pos[j][2]]) && !board.empty_fields[winning_pos[j][0]]){
					board.end = true;
				}
			}
		}
	}
}

void setBoardFieldValue(int field_number, char ch){
	if(field_number >= 0 || !field_number > 3){
		board.field_values[0][field_number] = ch;
		board.empty_fields[field_number] = false;
	} else if(field_number >= 4 || !field_number > 5){
		board.field_values[1][field_number] = ch;
		board.empty_fields[field_number] = false;
	} else if(field_number >= 6 || !field_number > 8){
		board.field_values[2][field_number] = ch;
		board.empty_fields[field_number] = false;
	}
	checkWinner();
}

void createPlayer(string nickname){
	ofstream file(nickname + ".txt");
	// ios::app po to aby plik się nie nadpisywał
	ofstream player_list("playerslist.txt", ios::app);

	file << nickname << endl;
	file << 0 << endl;
	file << 0 << endl;
	file << 0 << endl;
	file << 0 << endl;

	// Dodaj nowego gracza do listy
	player_list << nickname << endl;

	file.close();
	player_list.close();
}

void updateLosesPlayer(string nickname){
	Player *players = getAllPlayersData();
	int n = countPlayers();
	for(int i = 0; i < n; i++){
		if(players[i].nickname == nickname){

			players[i].loses += 1;
			players[i].percent_loses = (players[i].loses / (players[i].loses + players[i].wins)) * 100;
			players[i].percent_wins = (players[i].wins / (players[i].loses + players[i].wins)) * 100;
			string file_name = nickname + ".txt";
			ofstream file(file_name);

			file << players[i].nickname << endl;
			file << players[i].wins << endl;
			file << players[i].loses << endl;
			file << players[i].percent_wins << endl;
			file << players[i].percent_loses << endl;

			file.close();
		}
	}
}

void updateWinsPlayer(string nickname){
	Player *players = getAllPlayersData();
	int n = countPlayers();
	for(int i = 0; i < n; i++){
		if(players[i].nickname == nickname){

			players[i].wins += 1;
			players[i].percent_wins = (players[i].wins / (players[i].loses + players[i].wins)) * 100;
			players[i].percent_loses = (players[i].loses / (players[i].loses + players[i].wins)) * 100;
			string file_name = nickname + ".txt";
			ofstream file(file_name);

			file << players[i].nickname << endl;
			file << players[i].wins << endl;
			file << players[i].loses << endl;
			file << players[i].percent_wins << endl;
			file << players[i].percent_loses << endl;

			file.close();
		}
	}
}

Player getPlayerByWins(){
	Player *players = getAllPlayersData();
	int n = countPlayers();

	Player max = players[0];
	for(int i = 0; i < n; i++){
		if(players[i].wins > max.wins){
			max = players[i];
		}
	}

	return max;
}

void deletePlayer(string nickname){
	// Usunięcie pliku txt który zawiera dane gracza
	string player_data_file = nickname + ".txt";
	remove(player_data_file.c_str());

	// Usunięcie gracza z listy
	ofstream file("playerslist.txt");

	int n = countPlayers();
	string *players = getAllPlayersList();
	for(int i = 0; i < n; i++){
		if(players[i] != nickname){
			file << players[i] << endl;
		}
	}

	file.close();

	delete[] players;

}

void renderPlayerData(Player p){
	cout << "Nickname > " << p.nickname << endl;
	cout << "Wygrane > " << p.wins << endl;
	cout << "Przegrane > " << p.loses << endl;
	cout << "Wszystkich rozegranych: " << p.wins + p.loses << endl;
	cout << "Procent wygranych > " << p.percent_wins << endl;
	cout << "Procent przegranych > " << p.percent_loses << endl;
	cout << endl;
}

void renderPlayersData(Player p[]){
	int n = countPlayers();

	for(int i = 0; i < n; i++){
		renderPlayerData(p[i]);
	}
}

int countPlayers(){
	ifstream file("playerslist.txt", ios::app);

	int count = 0;

	string line;
	while(getline(file, line)){
		if(!line.empty()){
			count++;
		}
	}

	file.close();

	return count;
}

string* getAllPlayersList(){
	ifstream file("playerslist.txt");

	int n = countPlayers();

	string *players_list = new string[n]; // Alokacja listy graczy do pamięci
	string line;
	int i = 0;
	while(getline(file, line)){
		players_list[i] = line;
		i++;
	}

	file.close();

	return players_list;
}

Player* getAllPlayersData(){
	string *players_list = getAllPlayersList();
	Player *players_data;
	int n = countPlayers();
	players_data = new Player[n];

	for(int i = 0; i < n; i++){
		string file_name = players_list[i] + ".txt";
		ifstream file(file_name);

		Player p;
		file >> p.nickname;
		file >> p.wins;
		file >> p.loses;
		file >> p.percent_wins;
		file >> p.percent_loses;

		players_data[i] = p;

		file.close();
	}

	delete[] players_list;

	return players_data;
}

Player getPlayer(string nickname){
	Player *players = getAllPlayersData();
	int n = countPlayers();
	for(int i = 0; i < n; i++){
		if(players[i].nickname == nickname){
			return players[i];
		}
	}
}

bool playerDoesExist(string nickname){
	ifstream file("playerslist.txt");

	string line;
	while(getline(file, line)){
		if(!line.empty()){
			if(line == nickname){
				return true;
			}
		}
	}

	file.close();

	return false;
};