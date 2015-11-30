//MineSweeper! (Simulated GUI by C-lang)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
//initialize
int N/*matrix base*/,num/*number of bombs*/,moves/*total moves*/;
int left=-233/*number of left bombs*/;
int CurrentRow, CurrentCol;//current row & current column
int openedBlank = 0; 

//struct the graphic boxes
struct mine_box {
char type; 
char beMarked; 
char beOpened; 
} mine_array[20][20];

//import location
void gotoxy(int x,int y)
{   CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
    HANDLE    hConsoleOut;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
    csbiInfo.dwCursorPosition.X = x;
    csbiInfo.dwCursorPosition.Y = y;
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

//define what to print if a box is opened
//Attention: All the characters printed are Full-width characters. DO NOT use Half-width characters or the UI may not display properly.
void printBox(struct mine_box mb)
{
if(mb.beOpened == 0 && mb.beMarked == 0)
printf("■");//Normal box
else if(mb.beMarked == 1)
printf("△");//Flag
else if(mb.beMarked == 2)
printf("？");//Question
else
switch(mb.type) {
case '*':
printf("⊕");//Bomb
break;
//print numbers
case 0:
printf("０");
break;
case 1:
printf("１");
break;
case 2:
printf("２");
break;
case 3:
printf("３");
break;
case 4:
printf("４");
break;
case 5:
printf("５");
break;
case 6:
printf("６");
break;
case 7:
printf("７");
break;
case 8:
printf("８");
break;
}
}

//define move method
void MoveTo(int row, int col)
{
CurrentRow = row;
CurrentCol = col;
gotoxy(CurrentCol*4+2,CurrentRow*2+1);
}

//refresh the screen
void refreshScreen(int state)
{
int i, j;
gotoxy(0, 0);
printf("┏━");
for(i = 1; i < N; i++)
printf("┳━");
printf("┓\n");
for(i = 0; i < N; i++) {
printf("┃");
for(j = 0; j < N; j++) {
if(state == -1 && mine_array[i][j].beMarked == 1 && mine_array[i][j].type != '*') {
printf("＃┃"); //wrong mark
continue; 
} 
if(state != 0) { 
mine_array[i][j].beOpened = 1;
mine_array[i][j].beMarked = 0;
}
printBox(mine_array[i][j]);
printf("┃");
}
if(i < N-1) {
printf("\n┣");
for(j = 1; j < N; j++) {
printf("━╋");
}
printf("━┫\n");
}
else {
printf("\n┗");
for(j = 1; j < N; j++) {
printf("━┻");
}
printf("━┛\n");
}
}
printf("Number of Bombs:");printf("%d    ",num);
if(left>=0) 
{
printf("Number of Left:");printf("%d\n",left);
}
else 
{
printf("Number of Flags are more than that of Bombs! Please correct your choice!");
}
printf("Total Moves:");
printf("%d\n",moves);
printf("Press:\nA for Left，D for Right，W for Forward，S for Backward，X for Open，C for Mark，Q for Exit\n");
}

//main operation methods
void MoveLeft()
{
if(CurrentCol > 0) {
CurrentCol --;
moves++;
refreshScreen(0);
MoveTo(CurrentRow, CurrentCol);
}
}

void MoveRight()
{
if(CurrentCol < N-1) {
CurrentCol ++;
moves++;
refreshScreen(0);
MoveTo(CurrentRow, CurrentCol);
}
}

void MoveUp()
{
if(CurrentRow > 0) {
CurrentRow --;
moves++;
refreshScreen(0);
MoveTo(CurrentRow, CurrentCol);
}
}

void MoveDown()
{
if(CurrentRow < N-1) {
CurrentRow ++;
moves++;
refreshScreen(0);
MoveTo(CurrentRow, CurrentCol);
}
}

int openMine()
{
int saveRow = CurrentRow, saveCol = CurrentCol,i,j;
if(mine_array[CurrentRow][CurrentCol].beOpened)//if the box has been opened
return 0;

mine_array[CurrentRow][CurrentCol].beOpened = 1;
mine_array[CurrentRow][CurrentCol].beMarked = 0;
if(mine_array[CurrentRow][CurrentCol].type == '*') {//if the bomb be opened
refreshScreen(-1);
MoveTo(N+2, 0);
printf("Failed!\n"); 
exit(2);
}
printBox(mine_array[CurrentRow][CurrentCol]);
//print state
MoveTo(CurrentRow, CurrentCol);
return 1;
}

void markMine()
{
if(mine_array[CurrentRow][CurrentCol].beOpened == 1)
return;
if(mine_array[CurrentRow][CurrentCol].beMarked == 0)
{
mine_array[CurrentRow][CurrentCol].beMarked = 1;
left--;
}
else if(mine_array[CurrentRow][CurrentCol].beMarked == 1)
{
mine_array[CurrentRow][CurrentCol].beMarked = 2;
left++;
}
else if(mine_array[CurrentRow][CurrentCol].beMarked ==2)
mine_array[CurrentRow][CurrentCol].beMarked = 0;
printBox(mine_array[CurrentRow][CurrentCol]);
MoveTo(CurrentRow, CurrentCol);
}


main()
{
int i, j, row, col, count;
printf("Matrix: (Max:10*10)\n");
scanf("%u", &N);
if(N>10) 
{
printf("Out!\n");
return -1;
}
printf("Bombs: ");
scanf("%u", &num);
if(left=-233)left=num;

if(num > N*N) {
printf("Out!\n");
return -1;
}

//set the bombs appeared randomly.
memset((void*)mine_array, 0, N*N*sizeof(struct mine_box));//set the memory stack of mines
srand((unsigned)time(NULL));
for(i=0; i<num; i++) {
row = rand()%N;//random rows
col = rand()%N;//random columns
if(mine_array[row][col].type == 0)
mine_array[row][col].type = '*';
else
i--;
}
//get the number of bombs around(3*3) one box
for(row=0; row<N; row++)
{
for(col = 0; col < N; col++) {
if(mine_array[row][col].type == '*') {
for(i = row-1; i <= row+1; i++) {
for(j = col-1; j <= col+1; j++) {
if(i >= 0 && j >= 0 && i < N && j < N && mine_array[i][j].type != '*')
mine_array[i][j].type ++;
}
}
}
}
} 

refreshScreen(0);
MoveTo(N/2, N/2); 
//get keyboard input
do {
switch(getch()) {
case 'a':
case 'A':
MoveLeft();
break;
case 's':
case 'S':
MoveDown();
break;
case 'd':
case 'D':
MoveRight();
break;
case 'w':
case 'W':
MoveUp();
break;
case 'x':
case 'X':
if(openMine() == 1) {
if(++openedBlank == N*N-num) { //if success
refreshScreen(1);
MoveTo(N+2, 0);
printf("Success!\n");
exit(0);
}
}
break;
case 'c':
case 'C':
markMine();
refreshScreen(0);
break;
case 'q':
case 'Q':
MoveTo(N+2, 0);
printf("Quit?(y/n)");
if(getch() == 'y')
return 0; 
}
} while(1);//loop until fail(return 2) or succeed(return 0)
}
//End
