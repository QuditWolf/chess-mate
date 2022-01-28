#include<stdio.h>
#include<stdlib.h>
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


int isclean(){
//returns if path is clean  0/1
//also if the landing ends on a capture  2
	return 1;
}

int ischeck(){
	return 1;
//checks if post current move is a check against self   0 if it is
//if not, checks if current move results in check to opponent 1 if normal, 2 if offensive check
}

int isvalid(const char move[]){
	char piece = move[0];
	int x1= move[1] - 'A' + 1;
	int y1 = move[2] - '0';
	int x2= move[3] - 'A' + 1;
	int y2 = move[4] - '0';
	// check for coord in bounds 1 <= x <= 8 
	int d = abs(x2-x1)*10 + abs(y2-y1);
	//printf("deviation %d %d %d %d %d \n", d,x1,y1,x2,y2);
	switch((piece)) {                         // could be used to generalize color    // - 'a' + 1)%('A' - 1)){
		case 'P':
			if (d==1 && board[x2][y2]==' ') return isclean(move) && ischeck(move); //one move forward
			else if ( d==11 && board[x2][y2]!=' ') return isclean(move) && ischeck(move); //capture diagnal
			else if ( y1==2 && d==2 && board[x2][y2]==' ') return isclean(move) && ischeck(move); //first move
			break;
		case 'p':
			if (d==1 && board[x2][y2]==' ') return isclean(move) && ischeck(move); //one move forward
			else if ( d==11 && board[x2][y2]!=' ') return isclean(move) && ischeck(move); //capture diagnal
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
}
void makemove(const char move[5]){
	//remove the piece and find if themove is valid
	if(isvalid(move)){
		//rmpiece(move[0]);
	       	//printf("putting piece \n");
		putpiece(move+1,move[0]);
		//strcpe(moves[movesn++],move);
	}
	else
		printf("not valid\n");
}	

void initboard(){
	board[0][0]='O';
       	// board labelling
	for(int _x = 1; _x < 9; _x++){
		board[0][_x]=(char)(_x + '0');
	}
	for(int _x = 1; _x < 9; _x++){
		board[_x][0]=(char)(_x + 'A' - 1);
	}
	for(int _x = 1; _x < 9; _x++){
		for(int _y = 1; _y < 9; _y++){
			board[_x][_y]=((_x+_y)%2==0)?254:' ';
		}
	}

	for (int _x=1; _x < 9; _x++){
		board[_x][2]='P';
		board[_x][7]='p';
	}
	char wpiece[]= "RNBQKBNR";
	char bpiece[]= "rnbkqbnr";
	for(int _x = 1; _x < 9; _x++){
		board[_x][8]=bpiece[_x-1];
		board[_x][1]=wpiece[_x-1];
	}

}

void makeboard(){			//not used now rebuilds entire board from memory
	initboard();
	/*for( int i = 1; i <= movesn; i++){
		char* move = moves[i];
		char piece=move[0];
		makemove(move);
	}*/
}

int prelimcheck(char move[5]){
	char piece = move[0];
	int x1= move[1] - 'A' + 1;
	int y1 = move[2] - '0';
	int x2= move[3] - 'A' + 1;
	int y2 = move[4] - '0';
	if (piece!=board[x1][y1]){
		printf("Piece entered not at position\n");
		return 0;
	}
	//printf("%d %d %d %d",x1,y1,x2,y2);
	if ( x1 > 8 || y1 > 8 || x2 > 8 || y2 > 8 || x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 ){
		printf("Positions entered not in bounds ( 1 <= x,y <= 8 )");
		return 0;
	}
	return 1;
}
char _move[5];
void getmove(){
	do {
	printf("Enter Move:");
	scanf("%s",_move);
	} while (!prelimcheck(_move));
}



int main(){
	initboard();
	//makeboard();
	makemove("PD2D4");
	showboard();
	getmove();
	makemove(_move);
	showboard();
	//int loc = wherepiece('k');
	//printf("%d %d", loc/10,loc%10);
}
