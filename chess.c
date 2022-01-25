#include<stdio.h>
#include<cstring>
#define MAX_MOVES 16000
char board[9][9]; //one indexing //can add third dimension for backprop
char moves[MAX_MOVES][3]; //find a better way to do this
int movesn=0;


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

void putpiece(const char where[2],char piece){       // put a piece somewhere
	int y = where[0] - 'A' + 1;
	int x = where[1] - '0';
	//printf("putting at %d %d",x,y);
	board[x][y]=piece;
}

void putmove(const char move[3]){ 		//wrapper on putpiece for entire moves
	putpiece(move+1,move[0]);
}

bool rmpiece(char piece){       // find a piece and remove
	int found=0;
	int x,y;
	for(x = 1; x < 9; x++){
		for(y = 1; y < 9; y++){
			if (board[x][y] == piece){ 
				found=1;
				goto founded;
			}
		}
	}
founded:
	if (found){
		//printf("putting at %d %d",x,y);
		board[x][y]=' ';
		if (board[x][y]==' ')
			board[x][y]=((x+y)%2==0)?254:' ';
		printf("piece found at %d %d",x,y);
		return 1;
	}
	else {
		printf("error, %c piece not found\n",piece);
		return 0;
	}
}
void makemove(const char move[3]){
	//printf("making move of %c\n",move[0]);
	if(rmpiece(move[0]) && isvalid(move)) putpiece(move+1,move[0]);
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
void makeboard(){			//not used now rebuilds entire board from memory
	initboard();
	for( int i = 1; i <= movesn; i++){
		char* move = moves[i];
		char piece=move[0];
		makemove(move);
	}
}
bool isvalid(char move[], char piece){
	return 1;
}
int main(){
	initboard();
	//makeboard();
	makemove("kD4");
	showboard();
}
