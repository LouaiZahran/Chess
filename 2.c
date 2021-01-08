#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

char getColor(int row, int col)
{
    return (row+col)%2?'W':'B';
}

void move(char grid[8][8], int row, int col, int toRow, int toCol){
    grid[toRow][toCol] = grid[row][col];
    grid[row][col]=getColor(row, col)=='W'?'.':'-';
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

bool isCheck(char grid[8][8], char side)
{
    return false;
}

bool isEmpty(char grid[8][8], int row, int col)
{
    return grid[row][col]=='.'||grid[row][col]=='-';
}

char getLower(char c)
{
    return c>='a'&&c<='z'?c:c-'A'+'a';
}
char getSide(char piece)
{
    if('a'<=piece && piece<='z')
        return 'W';
    return 'B';
}

bool isValidInput(char in[])
{
    if(strlen(in)!=4||(in[0]<'a'||in[0]>'z'||in[1]<'1'||in[1]>'9')
                    ||(in[2]<'a'||in[2]>'z'||in[3]<'1'||in[3]>'9'))
                        return false;
    return true;
}

bool checkPawnMove(char grid[8][8], int row, int col, int toRow, int toCol, char turn)
{
    int sign=(turn=='W'?-1:1);
    return (((toRow==row+1*sign)
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

bool checkKingMove(char grid[8][8], int row, int col, int toRow, int toCol)
{
    char piece=grid[row][col], tmp=grid[toRow][toCol];
    grid[row][col]=(getColor(row,col)=='W'?'-':'.');
    grid[toRow][toCol]=piece;
    bool flag=abs(toRow-row)<=1&&abs(toCol-col)<=1&&!isCheck(grid, getSide(piece));
    grid[row][col]=piece;
    grid[toRow][toCol]=tmp;
    return flag;
}

bool isValid(char grid[8][8], char in[], char turn)
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

    switch(getLower(piece))
    {
        case 'p':
            return checkPawnMove(grid, row, col, toRow, toCol, turn);
        case 'k':
            return checkKingMove(grid, row, col, toRow, toCol);
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
