#include <fstream>

using namespace std;

struct Player{
	string nickname;

	int wins;
	int loses;
	float percent_wins;
	float percent_loses;
};

void createPlayer(string nickname);
void deletePlayer(string nickname);
void renderPlayerData(Player p);
void renderPlayersData(Player p[], int n);
string* getAllPlayersList();
Player* getAllPlayersData();
bool playerDoesExist(string nickname);
int countPlayers();

void createPlayer(string nickname){
	ofstream file(nickname + ".txt");
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

void deletePlayer(string nickname){
	// Problem z funkcją remove
}

void renderPlayerData(Player p){
	cout << p.nickname << endl;
	cout << p.wins << endl;
	cout << p.loses << endl;
	cout << p.percent_wins << endl;
	cout << p.percent_loses << endl;
	cout << endl;
}

void renderPlayersData(Player p[]){
	int n = countPlayers();
	for(int i = 0; i < n; i++){
		renderPlayerData(p[i]);
	}
}

int countPlayers(){
	ifstream file("playerslist.txt");

	int count;

	string line;
	while(getline(file, line)){
		if(!line.empty()){
			count++;
		}
	}

	return count;
}

string* getAllPlayersList(){
	ifstream file("playerslist.txt");

	int count = countPlayers();

	string *players_list = new string[count]; // Alokacja listy graczy do pamięci
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
	int count = countPlayers();
	Player *players_data = new Player[count];
	string *players_list = getAllPlayersList();


	for(int i = 0; i < count; i++){
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

	// Zwolnienie pamięci
	delete[] players_list;

	return players_data;
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