#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KWHT  "\x1B[37m"

  void create_board(void);
  void display(void);
  void player_A_move(void);
  void player_B_move(void);
  int check(void);
  void save(void);
  void load(void);

  char board[3][3], ref[3][3];
  int count=1, esc=0;

//*** MAIN() ***
int main(void) {

  int res;
  char sv, ld;

  printf("\nLoad game from file: Y/N?\n");
  ld = getchar();
  ld = toupper(ld);

  if (ld=='Y') {
    load();
    printf("Board from file is:\n");
  }//if(ld)
  else {
    create_board();
    printf("Initial board is: \n");
  }//else

  display();
  res = check();

  //THE GAME LOOP:
  while(!res && count<10) {
    if (count%2) player_A_move();
    else player_B_move();

    display();
    res = check();
    if (res || esc) break;

    if (count>=9) {
      printf("The board is a draw. \n");
      break;
    }
    count++;
  }//while(!res)
  //END OF GAME LOOP

  if (res==1) printf("\n*** Player A wins! ***\n");
  if (res==2) printf("\n*** Player B wins! ***\n");

  printf("\nSave game to file: Y/N?\n");
  sv = getchar();
  sv = getchar(); //Single statement "sv=getchar();" did not wait to enter sv but finish the program
  sv = toupper(sv);
  if (sv=='Y') save();

  return 0;
}//*** END OF MAIN() ***


void create_board(){
  int i, j;

  for(i=0; i<3; i++) for(j=0; j<3; j++) board[i][j]=ref[i][j]='_';
}


void player_A_move(){
  int x, y, lresA=1;

  printf("Enter player_A's Row-Column coordinates (1-3; 0 0 to quit):");

  while(lresA) {
    scanf("%d %d", &x, &y);
    x--;
    y--;

    if (x==-1 && y==-1) {
      esc=1;
      lresA=0;
      break;
    }

    if (board[x][y]=='_') {
      board[x][y]='X';
      lresA=0;
    }//if()
    else printf("Invalid move! Enter other coordinates:\n");
  }//while(lresA)

  printf("%sPlayer_A's move (%sX%s): \n",KGRN,KRED,KGRN);
}


void player_B_move(){
  int x, y, lresB=1;

  printf("Enter player_B's Row-Column coordinates (1-3; 0 0 to quit):");

  while(lresB) {
    scanf("%d %d", &x, &y);
    x--;
    y--;

    if (x==-1 && y==-1) {
      esc=1;
      lresB=0;
      break;
    }

    if(board[x][y]=='_') {
      board[x][y]='O';
      lresB=0;
    }//if()
    else printf("Invalid move! Enter other coordinates:\n");
  }//while(lresB)

  printf("%sPlayer_B's move (%sO%s): \n", KYEL, KRED, KYEL);
}


void display(){
  int i, j;

  for(i=0; i<3; i++){
    for(j=0; j<3; j++) { 
      if (ref[i][j]!=board[i][j]) printf("%s%c ", KRED, board[i][j]);
      else {
        switch (board[i][j]){
          case 'X':
            printf("%s%c ", KGRN, board[i][j]);
            break;
          case 'O':
            printf("%s%c ", KYEL, board[i][j]);
            break;
          default :
            printf("%s%c ", KWHT, board[i][j]);
        }//switch()
      }//else
      ref[i][j] = board[i][j];
    }//for(j)
    printf("%s\n", KWHT);
  }//for(i)

  printf("\n");
}


int check(){
  int i, j, outpt1, outpt2, outpt3, lres=0, win1, win2, win3, win=0;

  //*** Row test ***
  for (i=0; i<3; i++) {
    if (board[i][0]=='X' && board[i][1]=='X' && board[i][2]=='X') {
      outpt1=1;
      win1=0;
      break;
    }//if ([i][0])
    else {
      if (board[i][0]=='O' && board[i][1]=='O' && board[i][2]=='O') {
        outpt1=1;
        win1=1;
        break;
      }// else if ([i][0])
      else {
        outpt1=0;
        win1=0;
      }//else else
    }//else (board[i][0])
  }//for (i)
  //*** End of Row test ***
		     
  //*** Column test ***
  for (i=0; i<3; i++) {
    if (board[0][i]=='X' && board[1][i]=='X' && board[2][i]=='X') {
      outpt2=1;
      win2=0;
      break;
    }//if ([i][0])
    else {
      if (board[0][i]=='O' && board[1][i]=='O' && board[2][i]=='O') {
        outpt2=1;
        win2=1;
        break;
      }//if ([0][i])
      else {
        outpt2=0;
        win2=0;
      }//else else
    }//else
  }//for (i)
  //*** End of Column test ***

  //*** Diagonal test ***
  if ((board[0][0]=='X' && board[1][1]=='X' && board[2][2]=='X') || (board[2][0]=='X' && board[1][1]=='X' && board[0][2]=='X')) {
    outpt3=1;
    win3=0;
  }//if ([00][11][22] || [20][11][02]) for X
  else {
    if ((board[0][0]=='O' && board[1][1]=='O' && board[2][2]=='O') || (board[2][0]=='O' && board[1][1]=='O' && board[0][2]=='O')) {
      outpt3=1;
      win3=1;
    }//if ([00][11][22] || [20][11][02]) for O
    else {
      outpt3=0;
      win3=0;
    }//else else
  }//else 
  //*** End of Diagonal test ***

  //*** Is game complete? ***
  if (outpt1 || outpt2 || outpt3) lres=1;

  //*** Who is the winner? ***
  if (win1 || win2 || win3) win=1;

  return lres+win;
}


void save (void) {
  FILE *fp;
  char name[100];
  register int i, j;

  do {
    printf("\nEnter filename to save:\n");
    scanf("%s", name);
  } while (name[0]==' ');

  if ((fp=fopen(name, "wb"))==NULL) {
    printf("\nCannot open file.\n");
    return;
  }

  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
      if (fwrite(&board[i][j], sizeof(&board[i][j]), 1, fp)!=1) printf ("Error writing to file.\n");
    }//for(j)
  }//for(i)

  fclose(fp);
}


void load (void) {
  FILE *fp;
  char name[100];
  register int i, j;
  int x=0, y=0;

  printf("\nEnter filename to load:\n");
  scanf("%s", name);

  if ((fp=fopen(name, "rb"))==NULL) {
    printf("\nCannot open file.\n");
    return;
  }

  create_board();

  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
      if (fread(&board[i][j], sizeof(&board[i][j]), 1, fp)!=1) {
        if (feof(fp)) break;
        printf ("Error writing to file.\n");
      }
      ref[i][j]=board[i][j];
      if (ref[i][j]=='X') x++;
      if (ref[i][j]=='O') y++;
    }//for(j)
  }//for(i)

  count = count+x+y;
  printf("Count is %d\n", count);
  fclose(fp);
}
