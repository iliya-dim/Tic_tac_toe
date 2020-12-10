#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KWHT  "\x1B[37m"

  void create_board();
  void display();
  void player_A_move();
  void player_B_move();
  int check();

  char board[3][3], ref[3][3];
  int p=1,res;

int main(){

	create_board();

	printf("Initial board is: \n");

	display();

	//THE GAME LOOP:
	while(!res) {
		if (p%2) player_A_move();
		else player_B_move();
		display();
		res=check();
		if (res) break;
		if (p>=9) { printf("The board is a draw. \n");
			   break; }
		p++;
	}
	//END OF GAME LOOP

	if(res==1) printf("Player A wins! \n");
	if(res==2) printf("Player B wins! \n");

	return 0;
}//END OF main()-------------------<

//----------------->
void create_board(){

	int i,j;

	for(i=0;i<3;i++) for(j=0;j<3;j++) board[i][j]=ref[i][j]='_';

}
//-----------------<

//---------------->
void player_A_move(){

	int x,y,res=1;

	printf("Enter player_A's Row-Column coordinates (1-3):");

	while (res){
		scanf("%d %d",&x,&y);
		x--;
		y--;

		if (board[x][y]=='_') {	board[x][y]='X';
					res=0;}
		else printf("Invalid move! Enter other coordinates:\n");
	}
	printf("%sPlayer_A's move (%sX%s): \n",KGRN,KRED,KGRN);
}
//----------------<

//---------------->
void player_B_move(){

	int x,y,res=1;

	printf("Enter player_B's Row-Column coordinates (1-3):");

	while (res){
		scanf("%d %d",&x,&y);
		x--;
		y--;

		if (board[x][y]=='_') { board[x][y]='O';
					res=0;}
		else printf("Invalid move! Enter other coordinates:\n");
	}
	printf("%sPlayer_B's move (%sO%s): \n",KYEL,KRED,KYEL);
}
//----------------<

//------------------>
void display(){

	int i,j;

	for(i=0;i<3;i++){
		for(j=0;j<3;j++) { 
					if (ref[i][j]!=board[i][j]) printf("%s%c ",KRED,board[i][j]);
					else { switch (board[i][j]){
							case 'X':
							printf("%s%c ",KGRN,board[i][j]);
							break;
							case 'O':
							printf("%s%c ",KYEL,board[i][j]);
							break;
							default :
							printf("%s%c ",KWHT,board[i][j]);
								    }
					     }
					ref[i][j]=board[i][j];}
		printf("%s\n",KWHT);
	}
	printf("\n");

}
//------------------<

//--------->
int check(){

	int i, j, outpt1, outpt2, outpt3, res=0, win1, win2, win3, win=0;

	//Row test:
	for(i=0;i<3;i++){/*(for)*/
		if (board[i][0]=='X' && board[i][1]=='X' && board[i][2]=='X') { outpt1=1;
										win1=0;
										break;}
		else {  if (board[i][0]=='O' && board[i][1]=='O' && board[i][2]=='O') { outpt1=1;
											win1=1;
											break;}
		        else { 	outpt1=0;
				win1=0;}
		     }
	}/*(for)*/
		     
	//Column test:
	for(i=0;i<3;i++){/*(for)*/
		if (board[0][i]=='X' && board[1][i]=='X' && board[2][i]=='X') { outpt2=1;
										win2=0;
										break;}
		else {  if (board[0][i]=='O' && board[1][i]=='O' && board[2][i]=='O') { outpt2=1;
											win2=1;
											break;}
			else { outpt2=0;
				win2=0;}
		     }
	}/*(for)*/

	//Diagonal test:
	if ((board[0][0]=='X' && board[1][1]=='X' && board[2][2]=='X') || (board[2][0]=='X' && board[1][1]=='X' && board[0][2]=='X')){
		outpt3=1;
		win3=0;}
	else {/*(else)*/  if ((board[0][0]=='O' && board[1][1]=='O' && board[2][2]=='O') || (board[2][0]=='O' && board[1][1]=='O' && board[0][2]=='O'))      { outpt3=1;
		  win3=1;}
		else {   outpt3=0;
			 win3=0;}
	     }/*(else)*/ 

	if (outpt1||outpt2||outpt3) res=1;//Variable to determine if game complete
	if (win1||win2||win3) win=1;//Variable to determine winner

	return res+win;
}
//------------------<
