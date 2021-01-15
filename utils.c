#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

extern bool isCheck(char[8][8], char);
extern char statesGrid[8][8][1000];
extern int ctr;
int ewCtr, ebCtr;
char eatenWhite[16], eatenBlack[16];
bool hasMoved[8][8];
bool canCastle(char grid[8][8], int row, int col, int toRow, int toCol, char turn);
char getLower(char c);

char nextTurn(char turn){
    return (turn=='W'?'B':'W');
}

char getColor(int row, int col)
{
    return (row+col)%2?'W':'B';
}

bool isEmpty(char grid[8][8], int row, int col){
    return grid[row][col]=='.'||grid[row][col]=='-';
}

char getSide(char piece)
{
    if('a'<=piece && piece<='z')
        return 'W';
    return 'B';
}

void checkPromotion(char grid[8][8], int row, int col, int toRow, int toCol, char promote){
    char piece=grid[row][col], promotion='\0';
    if((getLower(piece)=='p')&&((getSide(piece)=='W'&&toRow==0)||(getSide(piece)=='B'&&toRow==7)))
    {
        if(promote=='r')
            promotion='R';
        if(promote=='n')
            promotion='N';
        if(promote=='b')
            promotion='B';
        if(promote=='q')
            promotion='Q';

        if(getSide(piece)=='W')
            promotion=getLower(promotion);

        grid[row][col]=promotion;
    }
}

void move(char grid[8][8], int row, int col, int toRow, int toCol, char promote){
    if(promote)
        checkPromotion(grid,row,col,toRow,toCol,promote);
    hasMoved[row][col]=true;
    hasMoved[toRow][toCol]=true;
    grid[toRow][toCol] = grid[row][col];
    grid[row][col]=getColor(row, col)=='W'?'.':'-';
    if(!isEmpty(grid, toRow, toCol)){
        char piece=grid[toRow][toCol];
        if(getSide(piece)=='W')
            eatenWhite[ewCtr++]=piece;
        else
            eatenBlack[ebCtr++]=piece;
    }
}

bool notMovedPawn(int row, int col, int turn){
    return (turn=='W'&&row==6)||(turn=='B'&&row==1);
}

int getRow(char r){
    return 8-(r-'0');
}

int getCol(char c){
    return c-'a';
}

char getLower(char c)
{
    return c>='a'&&c<='z'?c:c-'A'+'a';
}

bool isValidInput(char in[])
{
    if(strlen(in)>5||(in[0]<'a'||in[0]>'z'||in[1]<'1'||in[1]>'9')
                   ||(in[2]<'a'||in[2]>'z'||in[3]<'1'||in[3]>'9'))
                        return false;
    return true;
}

bool isEnPassent(char grid[8][8], int row, int col, int toRow, int toCol, char turn){
    int sign=(turn=='W'?-1:1);
    if(toRow!=row+1*sign||abs(toCol-col)!=1)
        return false;
    char currentPawn=grid[toRow-sign][toCol],
         assumedPawn=statesGrid[toRow+sign][toCol][ctr-1];
    bool flag = (assumedPawn!='.'&&assumedPawn!='-'&&getLower(assumedPawn)=='p'&&getSide(assumedPawn)!=turn)
              &&(currentPawn!='.'&&currentPawn!='-'&&getLower(currentPawn)=='p'&&getSide(currentPawn)!=turn);
    if(flag){
        if(turn=='B')
            eatenWhite[ewCtr++]='p';
        else
            eatenBlack[ebCtr++]='P';
        grid[toRow-sign][toCol]=getColor(row, col)=='W'?'-':'.';
    }
    return flag;
}

bool checkPawnMove(char grid[8][8], int row, int col, int toRow, int toCol, char turn, bool mainTurn)
{
    int sign=(turn=='W'?-1:1);
    return  (  (mainTurn&&isEnPassent(grid, row, col, toRow, toCol, turn))
            ||((toRow==row+1*sign)
            &&((toCol==col&&isEmpty(grid, toRow, toCol))
              ||((int)abs(toCol-col)==1&&!isEmpty(grid, toRow, toCol)&&getSide(grid[toRow][toCol])!=getSide(grid[row][col]))))
            ||(toRow==row+2*sign&&toCol==col&&notMovedPawn(row, col, turn)));
}

bool checkRookMove(char grid[8][8], int row, int col, int toRow, int toCol)
{
    if(toRow!=row&&toCol!=col)
        return false;
    int dx[4]= {1,-1,0,0};
    int dy[4]= {0,0,1,-1};
    for(int j=0; j<4; j++)
    {
        for(int i=1; i<=8; i++)
        {
            if(row+i*dx[j]==toRow&&col+i*dy[j]==toCol)
                return true;
            if(!isEmpty(grid, row+i*dx[j], col+i*dy[j]))
                break;
        }
    }
    return false;
}

bool checkBishopMove(char grid[8][8], int row, int col, int toRow, int toCol)
{
    if(abs(toRow-row)!=abs(toCol-col))
        return false;
    int dx[4]= {1,1,-1,-1};
    int dy[4]= {1,-1,1,-1};
    for(int j=0; j<4; j++)
    {
        for(int i=1; i<=8; i++)
        {
            if(row+i*dx[j]==toRow&&col+i*dy[j]==toCol)
                return true;
            if(!isEmpty(grid, row+i*dx[j], col+i*dy[j]))
                break;
        }
    }
    return false;
}

bool checkKnightMove(char grid[8][8], int row, int col, int toRow, int toCol)
{
    return (abs(toRow-row)==2&&abs(toCol-col)==1)||(abs(toRow-row)==1&&abs(toCol-col)==2);
}

bool checkQueenMove(char grid[8][8], int row, int col, int toRow, int toCol)
{
    return checkBishopMove(grid, row, col, toRow, toCol)||checkRookMove(grid, row, col, toRow, toCol);
}

bool checkKingMove(char grid[8][8], int row, int col, int toRow, int toCol, bool mainTurn)
{
    char piece=grid[row][col], tmp=grid[toRow][toCol];
    grid[row][col]=(getColor(row,col)=='W'?'-':'.');
    grid[toRow][toCol]=piece;
    bool flag=abs(toRow-row)<=1&&abs(toCol-col)<=1&&!isCheck(grid, getSide(piece));
    grid[row][col]=piece;
    grid[toRow][toCol]=tmp;
    return flag||(mainTurn&&!isCheck(grid, getSide(piece))&&canCastle(grid,row,col,toRow,toCol,getSide(piece)));
}

bool isValid(char grid[8][8], char in[], char turn, bool mainTurn)
{
    if(!isValidInput(in))
        return false;

    int   row=getRow(in[1]),   col=getCol(in[0]),
        toRow=getRow(in[3]), toCol=getCol(in[2]);
    if(isEmpty(grid, row, col))
        return false;

    char piece=grid[row][col], toCell=grid[toRow][toCol];
    if(getSide(piece)!=turn||(!isEmpty(grid, toRow, toCol)&&getSide(toCell)==turn))
        return false;

    if(mainTurn){
        grid[row][col]=(getColor(row, col)=='W'?'-':'.');
        grid[toRow][toCol]=piece;
        bool flag=isCheck(grid, turn);
        grid[toRow][toCol]=toCell;
        grid[row][col]=piece;
        if(flag)
            return false;
    }

    switch(getLower(piece))
    {
        case 'p':
            return checkPawnMove(grid, row, col, toRow, toCol, turn, mainTurn);
        case 'k':
            return checkKingMove(grid, row, col, toRow, toCol, mainTurn);
        case 'n':
            return checkKnightMove(grid, row, col, toRow, toCol);
        case 'b':
            return checkBishopMove(grid, row, col, toRow, toCol);
        case 'r':
            return checkRookMove(grid, row, col, toRow, toCol);
        case 'q':
            return checkQueenMove(grid, row, col, toRow, toCol);
        default:
            return false;
    }
}

bool canCastle(char grid[8][8], int row, int col, int toRow, int toCol, char turn){
    bool flag;
    if(turn=='W'){
        if(row!=7||col!=4||toRow!=7||(toCol!=2&&toCol!=6))
            return false;
        if(toCol==2){
            flag = !hasMoved[7][0]&&isEmpty(grid,7,1)&&isEmpty(grid,7,2)&&isEmpty(grid,7,3)&&!hasMoved[7][4];
            if(flag)
                move(grid,7,0,7,3,0);
        }
        else{
            flag = !hasMoved[7][4]&&isEmpty(grid,7,5)&&isEmpty(grid,7,6)&&!hasMoved[7][7];
            if(flag)
                move(grid,7,7,7,5,0);
        }
    }
    else{
        if(row!=0||col!=4||toRow!=0||(toCol!=2&&toCol!=6))
            return false;
        if(toCol==2){
            flag = !hasMoved[0][0]&&isEmpty(grid,0,1)&&isEmpty(grid,0,2)&&isEmpty(grid,0,3)&&!hasMoved[0][4];
            if(flag)
                move(grid,0,0,0,3,0);
        }
        else{
            flag = !hasMoved[0][4]&&isEmpty(grid,0,5)&&isEmpty(grid,0,6)&&!hasMoved[0][7];
            if(flag)
                move(grid,0,7,0,5,0);
        }
    }
    return flag;
}
