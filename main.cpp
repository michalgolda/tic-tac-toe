#include <iostream>
#include "playerManager.cpp"

using namespace std;

// Player currentplayerOne;
// Player currentplayerTwo;

/*
	Każde pole przechowuje znak X lub O
	
	|---|---|---|
	| 1 | 2 | 3 |
	|---|---|---|
	| 4 | 5 | 6 |
	|---|---|---|
	| 7 | 8 | 9 |
	|---|---|---|
*/
struct Board{
	char field_values[3][3] = {{' ', ' ', ' '},
						 	   {' ', ' ', ' '},
							   {' ', ' ', ' '}};
};

void renderMenu();
void renderMargin(int margin);
void renderBoard(Board board);

void clearWindow();

int main(){
	setlocale(LC_ALL, "");

	int option;

	while(true){
		clearWindow();
		renderMenu();

		cin >> option;

		if(option == 1){
		} else if(option == 2){
			Player *players = getAllPlayersData();
			renderPlayersData(players);

			delete[] players;
			
			break;
		} else if(option == 3){
			string nickname;

			while(true){
				cout << "Podaj nickname: ";
				cin >> nickname;

				if(playerDoesExist(nickname)){
					clearWindow();
					cout << "Podany nick " << nickname << " jest zajęty. Spróbuj ponownie." << endl;
					continue; 
				} else {
					createPlayer(nickname);
					break;
				}
			}

			continue;
		} else if(option == 4){
			while(true){
				string nickname;
				cout << "Podaj nickname: ";
				cin >> nickname;

				if(!playerDoesExist(nickname)){
					clearWindow();
					cout << "Nie znaleziono gracza o nicku " << nickname << ". Spróbuj ponownie." << endl;
					continue; 
				} else {
					// deletePlayer(nickname);
					cout << "Ta funkcja nie jest zaimplementowana." << endl;
					break;
				}
			}
		} else if(option == 5){
			break;
		}
	}
}

void renderMenu(){
	cout << "1. Start" << endl;
	cout << "2. Pokaż wszystkich graczy oraz ich statyski" << endl;
	cout << "3. Stwórz profil gracza" << endl;
	cout << "4. Usuń profil gracza" << endl;
	cout << "5. Wyjście" << endl;
	cout << "Wybierz opcję: ";
}

// Ta funkcja ma za zadanie wygenerowanie odstępu od krawędzi okna terminala
void renderMargin(int margin = 10){
	for(int j = 0; j < margin; j++){
		cout << " ";
	}
}

void clearWindow(){
	for(int i = 0; i < 99; i++){
		cout << endl;
	}
}

void renderBoard(Board board){

	clearWindow();
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
}