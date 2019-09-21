#include <iostream>
#include <fstream>

//Taþmayý kontrol et
#define DECK_SIZE 1000

using namespace std;

struct deck {
	int *list;
	int top;
	void push(int value);
	int pull();
	bool isempty();
};

void deck::push(int value) {
	list[top + 1] = value;
	top++;
}

int deck::pull() {
	int value = list[top];
	top--;

	return value;
}

bool deck::isempty() {
	bool empty = false;
	if (top < 0) {
		empty = true;
	}
	return empty;
}

int main(int argc, char* argv[]) {
	ifstream game;
	
	if(argc > 0 ){
		//Argc kullanmak zorunda olduðum icin
	}
	
	game.open(argv[1]);
	int tableDeckCount=0, playerDeckCount=0;
	game >> tableDeckCount >> playerDeckCount;

	deck table;
	table.list = new int[DECK_SIZE];
	for (int i = 0; i < tableDeckCount; i++) {
		game >> table.list[i];
	}
	table.top = tableDeckCount - 1;
	
	deck player1;
	player1.list = new int[DECK_SIZE];

	for (int i = 0; i < playerDeckCount; i++) {
		game >> player1.list[i];
	}
	player1.top = playerDeckCount - 1;

	deck player2;
	player2.list = new int[DECK_SIZE];

	for (int i = 0; i < playerDeckCount; i++) {
		game >> player2.list[i];
	}
	player2.top = playerDeckCount - 1;

	//Game starting

	bool game_finished = false;
	int bin=0;

	int table_value;


	while (!table.isempty()&&!player1.isempty() && !player2.isempty()) {
		//Player 1 is starting
		table_value = table.pull();
		
		int control=table_value;

		//Absolute value
		if (table_value < 0) {
			control = table_value * -1;
		}
		
		for (int i = 0; i < control; i++) {			
			if (table_value > 0) {
				if (!player2.isempty()) {
					if (player2.list[player2.top] > player1.list[player1.top]) {
						player1.push(player2.pull());
					}
					else {
						//Bin
						player2.top--;
						bin++;
					}
				}
				else {
					game_finished = true;
					break;
				}
			}
			else {
				//Player1 den KONTROL pulladýðýný oraya player2 ye pushlayacaksýn
				if (!player1.isempty()) {
					if (player1.list[player1.top] > player2.list[player2.top]) {
						player2.push(player1.pull());
					}
					else {
						//Bin
						player1.top--;
						bin++;
					}
				}
				else {
					game_finished = true;
				}
			}
		}

		
		if (table.isempty()) {
			break;
		}
		else if (game_finished == true) {
			break;
		}
		else {
			//Player 2 is playing
			table_value = table.pull();
			control = table_value;
			//mutlak deðer
			if (table_value < 0) {
				control = table_value*-1;
			}
			
			for (int i = 0; i < control; i++) {
				if (table_value > 0) {
					//player1 ->player2
					if (!player1.isempty()) {
						if (player1.list[player1.top] > player2.list[player2.top]) {
							player2.push(player1.pull());							
						}
						else {
						//binleri pulla			hepsiniDÝKKAT
						player1.top--;
						bin++;
						}										   
					}
					else {
						game_finished = true;
						break;
					}
				}
				else {
					//player2 ->player1
					if (!player2.isempty()) {
						if (player2.list[player2.top] > player1.list[player1.top]) {
							player1.push(player2.pull());
						}
						else {
							player2.top--;
							bin++;
						}

					}
					else {
						game_finished = true;
						break;
					}


				}
			}
		}
	}
	   	 
	
	cout << bin << endl;

	return 0;
}
