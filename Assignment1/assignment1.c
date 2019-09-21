#include <iostream>
#include <fstream>

#define PLUS 1
#define MINUS 2
#define CROSS 3
#define DIVIDE 4

/*
0- output kontrol edilecek -
1- instruction 2. satýrý okumuyor 
2- dosya isimleri
3- newler delete edilecek
*/

using namespace std;
struct shape {
	int coordinate[2];
	int br;
	char type;
};

// Koordinatlarý tutmak için 1
struct cisim {
	int error_flag;
	int lenght;
	int *points[2];
};

bool own(cisim* myList, int ok,int x,int y){

	bool own = true;

	for (int i = 0; i < myList[ok].lenght; i++) {
		if (x == myList[ok].points[0][i]-1 && y == myList[ok].points[1][i] - 1) {
			own =false;
			break;
		}
	}
	
	return own;
}

void put_grid(int grid_row, int grid_col, int** dimensional, shape data, int number_row, int order,cisim* myList) {
		
		//Satýr sayýsý kadar cisim structý açtýk ve koordinatlarý dolduruyoruz		
		int i = order; // Kaçýncý sýrada olduðunu tutuyoruz
		myList[i].error_flag = 0; //Default olarak atama yaptýk

		//Boyut hesaplama
		if (data.type == '+') {
			myList[i].lenght = (data.br) * 4 + 1;
		}
		else if(data.type=='x'){
			myList[i].lenght = (data.br) * 4 + 1;
		}
		else if (data.type == '-') {
			myList[i].lenght = (data.br) * 2 + 1;
		}
		else if (data.type == '/') {
			myList[i].lenght = (data.br) * 2 + 1;
		}

		//cout << i << "." <<"length :"<< myList[i].lenght << endl;
		myList[i].points[0] = new int[myList[i].lenght];
		myList[i].points[1] = new int[myList[i].lenght];

		//Koordinat doldurma
		if (data.type == '+') {
			//Merkezleri atadýk
			myList[i].points[0][0] = data.coordinate[0];
			myList[i].points[1][0] = data.coordinate[1];

			int r;
			for (r = 1; r <= data.br; r++) {
				myList[i].points[0][r] = (data.coordinate[0]) + r;
				myList[i].points[1][r] = data.coordinate[1];
			}

			int l;
			for (l = 1; l <= data.br; l++) {
				myList[i].points[0][r + l - 1] = data.coordinate[0] - l;
				myList[i].points[1][r + l - 1] = data.coordinate[1];
			}

			int u;
			for (u = 1; u <= data.br; u++) {
				myList[i].points[0][r+l+u-2] = data.coordinate[0];
				myList[i].points[1][r+l+u-2] = data.coordinate[1] + u;
			}

			int d;
			for (d = 1; d <= data.br; d++) {
				myList[i].points[0][r + l + u + d - 3] = data.coordinate[0];
				myList[i].points[1][r + l + u + d - 3] = data.coordinate[1]-d;
			}
		}
		else if(data.type=='-'){
			//Merkezleri atadýk
			myList[i].points[0][0] = data.coordinate[0];
			myList[i].points[1][0] = data.coordinate[1];

			int r;
			for (r = 1; r <= data.br; r++) {
				myList[i].points[0][r] = data.coordinate[0];
				myList[i].points[1][r] = data.coordinate[1]+r;
			}
		
			int l;
			for (l = 1; l <= data.br; l++) {
				myList[i].points[0][r + l - 1] = data.coordinate[0];
				myList[i].points[1][r + l - 1] = data.coordinate[1]- l;
			}
		}	
		else if (data.type == '/') {
			//Merkezleri atadýk
			myList[i].points[0][0] = data.coordinate[0];
			myList[i].points[1][0] = data.coordinate[1];

			int r;
			for (r = 1; r <= data.br; r++) {
				myList[i].points[0][r] = data.coordinate[0] - r;
				myList[i].points[1][r] = data.coordinate[1] + r;
			}

			int l;
			for (l = 1; l <= data.br; l++) {
				myList[i].points[0][r + l - 1] = data.coordinate[0] + l;
				myList[i].points[1][r + l - 1] = data.coordinate[1] - l;
			}

		}
		else if (data.type == 'x') {
			//Merkezleri atadýk
			myList[i].points[0][0] = data.coordinate[0];
			myList[i].points[1][0] = data.coordinate[1];

			int r;
			for (r = 1; r <= data.br; r++) {
				myList[i].points[0][r] = (data.coordinate[0]) + r;
				myList[i].points[1][r] = data.coordinate[1] + r;
			}

			int l;
			for (l = 1; l <= data.br; l++) {
				myList[i].points[0][r + l - 1] = data.coordinate[0] - l;
				myList[i].points[1][r + l - 1] = data.coordinate[1] - l;
			}

			int u;
			for (u = 1; u <= data.br; u++) {
				myList[i].points[0][r + l + u - 2] = data.coordinate[0] + u;
				myList[i].points[1][r + l + u - 2] = data.coordinate[1] - u;
			}

			int d;
			for (d = 1; d <= data.br; d++) {
				myList[i].points[0][r + l + u + d - 3] = data.coordinate[0] - d;
				myList[i].points[1][r + l + u + d - 3] = data.coordinate[1] + d;
			}
		}

		//Error kontrol
		for (int trace = 0; trace < myList[i].lenght; trace++) {
			int x = myList[i].points[0][trace];
			int y = myList[i].points[1][trace];

			if ( x-1 > grid_row-1 || y-1 > grid_col-1|| x <= 0 || y <= 0) {
				if (myList[i].error_flag == 0) {
					myList[i].error_flag = 1;
				}else if (myList[i].error_flag == 2) {
					myList[i].error_flag = 3;
				}
			}
			//Kontrol de bir hata var incele
			else if (x > 0 && y > 0) {
				if (dimensional[x-1][y-1] != 0) {
					if (myList[i].error_flag == 0) {
						myList[i].error_flag = 2;
					}
					else if (myList[i].error_flag == 1) {
						myList[i].error_flag = 3;
					}
				}
			}
			
			if (myList[i].error_flag == 3) {
				break;
			}
		}
		
		//Result ekrana basma
		if (myList[i].error_flag == 0) {
			for (int trace = 0; trace < myList[i].lenght; trace++) {
				int x = myList[i].points[0][trace];
				int y = myList[i].points[1][trace];
				if (data.type == '+') {
					dimensional[x - 1][y - 1] = PLUS;
				}else if (data.type == '-') {
					dimensional[x - 1][y - 1] = MINUS;
				}else if (data.type == 'x') {
					dimensional[x - 1][y - 1] = CROSS;
				}else if (data.type == '/') {
					dimensional[x - 1][y - 1] = DIVIDE;
				}			
			}
			cout << "SUCCESS: Operator " << data.type << " with size " << data.br  << " is placed on ("<< data.coordinate[0] <<"," << data.coordinate[1] << ")."<<endl;
		}
		else if (myList[i].error_flag == 1) {
			cout << "BORDER ERROR: Operator " << data.type << " with size " << data.br << " can not be placed on ( " << data.coordinate[0] << "," << data.coordinate[1] << ")."<<endl;
		}
		else if (myList[i].error_flag == 2) {
			cout << "CONFLICT ERROR: Operator " << data.type << " with size " << data.br << " can not be placed on ( " << data.coordinate[0] << "," << data.coordinate[1] << ")."<<endl;
		}
		else if (myList[i].error_flag == 3) {
			cout << "BORDER ERROR: Operator " << data.type << " with size " << data.br << " can not be placed on ( " << data.coordinate[0] << "," << data.coordinate[1] << ")."<<endl;
			cout << "CONFLICT ERROR: Operator " << data.type << " with size " << data.br << " can not be placed on ( " << data.coordinate[0] << "," << data.coordinate[1] << ")."<<endl;
		}	
}

void print_screen(int grid_row,int grid_col, int** dimensional) {
	
	cout << endl;

	for (int i = 0; i < grid_row; i++) {
		for (int j = 0; j < grid_col; j++) {			
			cout << dimensional[i][j];
		}
		cout << endl;
	}
}

int control(int ok, cisim* myList, int** dimensional, char* direction, int move_x, int move_y, int move_br, int grid_row,int grid_col) {
	//move=0:taþý  1:border  2:conflict  3:double error
	int move = 0;
	int current = 0;

	while (current != myList[ok].lenght) {
		int x = myList[ok].points[0][current]-1;
		int y = myList[ok].points[1][current]-1;
		
		//cout << "Son kontrol" << current << "x: " << x << "y: " << y <<endl;

		if (direction[2] == 'R') {
			if ( (x) < 0 || y + move_br < 0 || x > grid_row - 1 || y + move_br > grid_col - 1) {
				if (move == 0) {
					move = 1;
				}
				else if (move == 2) {
					move = 3;
					break;
				}
			}
			else if (dimensional[x][y+move_br] != 0 && own(myList,ok,x,y+move_br)){
				//Kendi olup olmadýðýný da burda kontrol et
				if (move == 0) {
					move = 2;
				}
				else if (move == 1) {
					move = 3;
					break;
				}
			}
		}else if (direction[2] == 'L') {
			if ((x) < 0 || y - move_br < 0 || x > grid_row - 1 || y - move_br > grid_col - 1) {
				if (move == 0) {
					move = 1;
				}
				else if (move == 2) {
					move = 3;
					break;
				}
			}
			else if (dimensional[x][y - move_br] != 0 && own(myList, ok, x, y - move_br)) {
				//Kendi olup olmadýðýný da burda kontrol et
				if (move == 0) {
					move = 2;
				}
				else if (move == 1) {
					move = 3;
					break;
				}
			}
		}
		else if (direction[2] == 'D') {
			if ((x - move_br) < 0 || y  < 0 || x - move_br > grid_row - 1 || y > grid_col - 1) {
				if (move == 0) {
					move = 1;
				}
				else if (move == 2) {
					move = 3;
					break;
				}
			}
			else if (dimensional[x - move_br][y] != 0 && own(myList, ok, x-move_br, y)) {
				//Kendi olup olmadýðýný da burda kontrol et
				if (move == 0) {
					move = 2;
				}
				else if (move == 1) {
					move = 3;
					break;
				}
			}

		}
		else if (direction[2] == 'U') {
			if ((x + move_br) < 0 || y  < 0 || x + move_br > grid_row - 1 || y > grid_col - 1) {
				if (move == 0) {
					move = 1;
				}
				else if (move == 2) {
					move = 3;
					break;
				}
			}
			else if (dimensional[x + move_br][y] != 0 && own(myList, ok, x + move_br, y)) {
				//Kendi olup olmadýðýný da burda kontrol et
				if (move == 0) {
					move = 2;
				}
				else if (move == 1) {
					move = 3;
					break;
				}
			}
		}
		current++;
	}
	return move;
}

void move(char* direction, int move_x, int move_y, int move_br, cisim* myList, int** dimensional, int number_row,int grid_row,int grid_col) {

	//myListte gezinti
	for (int ok = 0; ok < number_row; ok++) {
		if (myList[ok].error_flag == 0) {
			for (int i = 0; i < myList[ok].lenght;i++){
				if (myList[ok].points[0][i] == move_x && myList[ok].points[1][i] == move_y) {
					int control_value = control(ok, myList, dimensional, direction, move_x, move_y, move_br, grid_row, grid_col);
					//iþaret tesbiti yapýcaz
					char ch_type;
					int control = dimensional[myList[ok].points[0][0] - 1][myList[ok].points[1][0] - 1];
					if (control == 1) {
						ch_type = '+';
					}
					else if (control == 2) {
						ch_type = '-';
					}
					else if (control == 3) {
						ch_type = 'x';
					}
					else if (control == 4) {
						ch_type = '/';
					}
					
					if (control_value == 0){						
						//Taþýma iþlemi yap
						int move_type = dimensional[myList[ok].points[0][0]-1][myList[ok].points[1][0]-1];

						for (int a = 0; a < myList[ok].lenght; a++) {
							int x = myList[ok].points[0][a] - 1;
							int y = myList[ok].points[1][a] - 1;
							dimensional[x][y] = 0;
						}

						if (direction[2] == 'R') {
							//saða taþý
							cout << "SUCCESS: "<<ch_type<<" moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0]+move_br << ")." << endl;
							for (int a = 0; a < myList[ok].lenght; a++) {
								int x = myList[ok].points[0][a] - 1;
								int y = myList[ok].points[1][a] - 1;
								dimensional[x][y+move_br] = move_type;								
							}
							for (int a = 0; a < myList[ok].lenght; a++) {
								myList[ok].points[1][a] += move_br;
							}						
						}
						else if (direction[2] == 'L') {
							//sola taþý
							cout << "SUCCESS: " << ch_type << " moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] - move_br << ")." << endl;
							for (int a = 0; a < myList[ok].lenght; a++) {
								int x = myList[ok].points[0][a] - 1;
								int y = myList[ok].points[1][a] - 1;
								dimensional[x][y - move_br] = move_type;								
							}
							for (int a = 0; a < myList[ok].lenght; a++) {
								myList[ok].points[1][a] -= move_br;
							}
													   
						}
						else if (direction[2] =='U') {
							//yukarý taþý
							cout << "SUCCESS: " << ch_type << " moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] - move_br << "," << myList[ok].points[1][0]<< ")." << endl;
							for (int a = 0; a < myList[ok].lenght; a++) {
								int x = myList[ok].points[0][a] - 1;
								int y = myList[ok].points[1][a] - 1;
								dimensional[x - move_br][y ] = move_type;
							}
							for (int a = 0; a < myList[ok].lenght; a++) {
								myList[ok].points[0][a] -= move_br;
							}
						}
						else if (direction[2] =='D') {
							//asagý taþý
							cout << "SUCCESS: " << ch_type << " moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] + move_br << "," << myList[ok].points[1][0] << ")." << endl;
							for (int a = 0; a < myList[ok].lenght; a++) {
								int x = myList[ok].points[0][a] - 1;
								int y = myList[ok].points[1][a] - 1;
								dimensional[x + move_br][y] = move_type;
							}
							for (int a = 0; a < myList[ok].lenght; a++) {
								myList[ok].points[0][a] += move_br;
							}
						}
						//3.for döngüsüne tekrar girip hata vermemesi için break yaptýk
						break;

					}
					else if (control_value == 1) {
						if (direction[2] == 'R') {
							cout << "BORDER ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] + move_br << ")." << endl;
						}else if (direction[2] == 'L') {
							cout << "BORDER ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] - move_br << ")." << endl;
						}
						else if (direction[2] == 'U') {
							cout << "BORDER ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] - move_br << "," << myList[ok].points[1][0]  << ")." << endl;
						}
						else if (direction[2] == 'D') {
							cout << "BORDER ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] + move_br << "," << myList[ok].points[1][0]  << ")." << endl;
						}
					}
					else if (control_value == 2) {
						if (direction[2] == 'R') {
							cout << "CONFLICT ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] + move_br << ")." << endl;
						}
						else if (direction[2] == 'L') {
							cout << "CONFLICT ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] - move_br << ")." << endl;
						}
						else if (direction[2] == 'U') {
							cout << "CONFLICT ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] - move_br << "," << myList[ok].points[1][0] << ")." << endl;
						}
						else if (direction[2] == 'D') {
							cout << "CONFLICT ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] + move_br << "," << myList[ok].points[1][0] << ")." << endl;
						}
					}
					else if (control_value == 3) {
						if (direction[2] == 'R') {
							cout << "BORDER ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] + move_br << ")." << endl;
							cout << "CONFLICT ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] + move_br << ")." << endl;
						}
						else if (direction[2] == 'L') {
							cout << "BORDER ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] - move_br << ")." << endl;
							cout << "CONFLICT ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] - move_br << ")." << endl;
						}
						else if (direction[2] == 'U') {
							cout << "BORDER ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] - move_br << "," << myList[ok].points[1][0] << ")." << endl;
							cout << "CONFLICT ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] - move_br << "," << myList[ok].points[1][0] << ")." << endl;
						}
						else if (direction[2] == 'D') {
							cout << "BORDER ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] + move_br << "," << myList[ok].points[1][0] << ")." << endl;
							cout << "CONFLICT ERROR: " << ch_type << " can not be moved from (" << myList[ok].points[0][0] << "," << myList[ok].points[1][0] << ") to (" << myList[ok].points[0][0] + move_br << "," << myList[ok].points[1][0] << ")." << endl;
						}
					}
				}
			}
		}
	}
}

int main() {
	//Satýr sayýsýný öðrenmek için dosya açýp sayýp kapadýk
	fstream row_file;
	//!Dosya ismini arguman olarak alacaksýn
	row_file.open("grid.txt", ios::out | ios::in | ios::app);

	int temp = 0;
	char tempr;

	//Yerleþtirme talimat sayýsý
	int number_row=-1;

	row_file >> temp >> temp;	
	while (!row_file.eof()) {
		row_file >> tempr >> temp >> temp >> temp;
		number_row++;
	}
	row_file.close();
	
	//Structlara verileri kaydetmek için
	fstream grid;
	//!Dosya ismini arguman olarak alacaksýn
	grid.open("grid.txt", ios::out | ios::in | ios::app);

	//Satýr sayýsý kadar (number_row) alan açtým	
	shape *myShape = new shape[number_row];

	int grid_row,grid_col;
	int i = 0;
	grid >> grid_row >> grid_col;

	cout << "A grid is created: " << grid_row << " " << grid_col << endl;

	while (!grid.eof()) {
		grid >> myShape[i].type >> myShape[i].coordinate[0] >> myShape[i].coordinate[1] >> myShape[i].br;
		i++;
	}
	////Grid açma iþlemi yapýcaz	//////////////////////////////

	int **dimensional =new int*[grid_row];
	for (int k = 0; k < grid_row; k++) {
		dimensional[k] = new int[grid_col];		
	}
	for (int i = 0; i < grid_row; i++) {
		for (int j = 0; j < grid_col; j++) {
			dimensional[i][j] = 0;
		}
	}
	
	//Gridi Ekrana bas /print_screen(grid_row, grid_col, dimensional);

	//cout << "Number-row: " << number_row <<endl ;
	//Structaki koordinatlarý myListte tut ve kontrol et
	cisim *myList = new cisim[number_row];
	   
	for (int q = 0; q < number_row; q++) {
		put_grid(grid_row, grid_col, dimensional, myShape[q],number_row,q,myList);		
	}	

	print_screen(grid_row, grid_col, dimensional);

	//Move Operations
	fstream move_file;
	//!Dosya ismini arguman olarak alacaksýn
	move_file.open("instructions.txt", ios::out | ios::in | ios::app);

	char direction[5];
	int move_x, move_y, move_br;

	while (!move_file.eof()) {
		move_file >> direction >> move_x >> move_y >> move_br;
		move(direction, move_x, move_y, move_br, myList, dimensional, number_row, grid_row, grid_col);
	}

	move_file.close();

	// Control	/////////////////////////////////////////////
	print_screen(grid_row, grid_col, dimensional);
		
	//new ve dosyalarý kapatmayý unutma
	grid.close();
	getchar();
	return 0;
}
