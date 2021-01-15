#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char turn = 'W';
char in[1000];
char grid[8][8]=    {{'R','N','B','Q','K','B','N','R'},
                     {'P','P','P','P','P','P','P','P'},
                     {'-','.','-','.','-','.','-','.'},
                     {'.','-','.','-','.','-','.','-'},
                     {'-','.','-','.','-','.','-','.'},
                     {'.','-','.','-','.','-','.','-'},
                     {'p','p','p','p','p','p','p','p'},
                     {'r','n','b','q','k','b','n','r'}};

extern void maintainGrid();
extern void save();
extern void load();
extern void undo();
extern void redo();
extern int getRow(char);
extern int getCol(char);
extern bool isValid(char[8][8], char[], char, bool);
extern bool isValidInput(char[]);
extern void move(char[8][8], int, int, int, int, char);
extern void chooseMode();
extern bool isCheck(char[8][8], char);
extern char nextTurn(char);
extern bool cantMove(char[8][8], char);

//print chess board function
void printGrid(){
    for (int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%c ",grid[i][j]);
        }
        printf("\n");
    }
}

//read movements
void readMovements(){
    if(cantMove(grid, turn)){
        if(isCheck(grid, turn))
            printf("Checkmate!\n%s wins!", turn=='W'?"Black":"White");
        else
            printf("Stalemate!\nThe game is tied!");
        exit(0);
    }
    printf("%s turn\n", turn=='W'?"White's":"Black's");
    if(isCheck(grid, 'W'))
        printf("White's in check!\n");
    if(isCheck(grid, 'B'))
        printf("Black's in check!\n");
    while(1){
        memset(in, 0, sizeof(char)*1000);
        printf("\nEnter your move: ");
        scanf("%s", in);
        if(in[0]=='S')
            return save();
        if(in[0]=='L')
            return load();
        if(in[0]=='U')
            return undo();
        if(in[0]=='R')
            return redo();
        if(!isValidInput(in)){
            printf("\nIncorrect format!\nPlease enter input in the form X#X#\nWhere X indicates the column letter and # indicates the row number\n");
            continue;
        }
        if(!isValid(grid, in, turn, true))
            printf("Invalid Move!\n");
        else
            break;
    }
    move(grid, getRow(in[1]), getCol(in[0]), getRow(in[3]), getCol(in[2]), in[4]);
    maintainGrid();
    turn=nextTurn(turn);
}

int main()
{
    maintainGrid();
    while(true){
        printGrid();
        readMovements();
        system("cls");
    }
    return 0;
}
