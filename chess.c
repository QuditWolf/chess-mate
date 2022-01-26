#include<stdio.h>
#define MAX_MOVES 16000
char board[9][9]; //one indexing //can add third dimension for backprop
char moves[MAX_MOVES][5]; //find a better way to do this
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

int putpiece(const char where[4],char piece){       // put a piece somewhere
	int x1= where[0] - 'A' + 1;
	int y1 = where[1] - '0';
	int x2= where[2] - 'A' + 1;
	int y2 = where[3] - '0';
	//printf("putting at %d %d",x,y);
	if (board[x1][y1]!=piece) return -1;
	else {
		board[x1][y1]=' ';
		board[x2][y2]=piece;
		return 1;
	}

}

void putmove(const char move[5]){ 		//wrapper on putpiece for entire moves
	putpiece(move+1,move[0]);
}

char wherepiece(char piece){
	int x,y;
	int found=0;
	for(x = 1; x < 9; x++){
		for(y = 1; y < 9; y++){
			if (board[x][y] == piece){ 
				return (10*x+y);
			}
		}
	}
	return -1;
}

int rmpiece(char piece){       // find a piece and remove
	//printf("getting executed \n");
	int found=wherepiece(piece);
	int x,y;
	if (found!=-1){
		x=found/10;
		y=found%10;
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

int isvalid(const char move[]){
	char piece = move[0];
	int x1= move[0] - 'A' + 1;
	int y1 = move[1] - '0';
	int x2= move[2] - 'A' + 1;
	int y2 = move[3] - '0';
	int buf = 1 - 'a';
	// check for coord in bounds 1 <= x <= 8 
	int d = abs(x2-x1)*10 + abs(y2-y1);
	switch((piece)) {                         // could be used to generalize color    // - 'a' + 1)%('A' - 1)){
		case 'P':
			if (d==1 && board[x2][y2]==' ') return isclean(move) && ischeck(move); //one move forward
			else if ( d=11 && board[x2][y2]!=' ') return isclean(move) && ischeck(move); //capture diagnal
			else if ( y1==2 && d==2 && board[x2][y2]==' ') return isclean(move) && ischeck(move); //first move
			break;
		case 'p':
			if (d==1 && board[x2][y2]==' ') return isclean(move) && ischeck(move); //one move forward
			else if ( d=11 && board[x2][y2]!=' ') return isclean(move) && ischeck(move); //capture diagnal
			else if ( y1==7 && d==2 && board[x2][y2]==' ') return isclean(move) && ischeck(move); //first move
			break;
			//printf("pawn encountered");
		case 'R':
		case 'r':
			if ((d/10)==0 || !(d%10) ) return isclean(move) && ischeck(move);
			break;
		case 'N':
		case 'n':
			if (d==12 || d==21) return ischeck(move);
			break;
		case 'K':
		case 'k':
			if ( (d%10 <= 1) && (d/10 <= 1) && (d > 0) ) return ischeck(move);
			break;
		case 'Q':
		case 'q':
			if (((d/10)==0 || !(d%10) ) || !(d%11))  return isclean(move) && ischeck(move);
			break;

	}

	return 1;
}
void makemove(const char move[5]){
	//remove the piece and find if themove is valid
	if(isvalid(move)){
		//rmpiece(move[0]);
	       	putpiece(move+1,move[0]);
		//strcpe(moves[movesn++],move);
	}
}	

void initboard(){
	board[0][0]='O';
       	// board labelling
	for(int _x = 1; _x < 9; _x++){
		board[_x][0]=(char)(_x + '0');
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

int main(){
	initboard();
	//makeboard();
	makemove("pD2D4");
	showboard();
	//int loc = wherepiece('k');
	//printf("%d %d", loc/10,loc%10);
}
