#include<stdio.h>
#define MAX_MOVES 16000
char board[9][9]; //one indexing //can add third dimension for backprop
char moves[MAX_MOVES][3]; //find a better way to do this
int moven=0;


void showboard(){
	for(int _y = 0; _y < 9; _y++){
		printf("+---+---+---+---+---+---+---+---+---+\n");
		for (int _x = 0; _x < 9; _x++){
			printf("| %c ",board[_x][_y]);
		}
		printf("|\n");
	}
	printf("+---+---+---+---+---+---+---+---+---+\n");
}

void putpiece(const char where[2],char piece){
	int y = where[0] - 'A' + 1;
	int x = where[1] - '0';
	//printf("putting at %d %d",x,y);
	board[x][y]=piece;
}

void initboard(){
	board[0][0]='O';
	// board labelling
	for(int _x = 1; _x < 9; _x++){
		board[_x][0]=char(_x + '0');
	}
	for(int _x = 1; _x < 9; _x++){
		board[0][_x]=(char)(_x + 'A' - 1);
	}
	for(int _x = 1; _x < 9; _x++){
		for(int _y = 1; _y < 9; _y++){
			board[_x][_y]=((_x+_y)%2==0)?254:' ';
		}
	}

	for (int _x=1; _x < 9; _x++){
		board[_x][7]='P';
		board[_x][2]='p';
	}
	char wpiece[]= "RNBQKBNR";
	char bpiece[]= "rnbkqbnr";
	for(int _x = 1; _x < 9; _x++){
		board[_x][1]=bpiece[_x-1];
		board[_x][8]=wpiece[_x-1];
	}

}
void makeboard(){
	for( int i = 0; i <= move_num
}
bool isvalid(char move[], char piece){
	return 1;
}
int main(){
	initboard();
	showboard();
}
