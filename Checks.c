#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

extern bool isEmpty(char grid[8][8], int, int);
extern char getLower(char);
extern char getSide(char);
extern char nextTurn(char);
extern bool isValid(char grid[8][8], char[], char, bool);
extern char getColor(int, int);

bool isCheck(char grid[8][8], char turn){
    int rowK;
    char colK;
    for(int i=0;i<8;i++)
    for(int j=0;j<8;j++){
        if(!isEmpty(grid, i, j)
           &&getLower(grid[i][j])=='k'
           &&getSide(grid[i][j])==turn){
               rowK=7-i, colK='a'+j;
               break;
        }
    }
    bool flag=false;
    for(char colX='a';colX<='h';colX++){
        for(int rowX=0;rowX<=7;rowX++){
            char trial[5]={colX, '1'+rowX, colK, '1'+rowK};
            flag|=isValid(grid, trial, nextTurn(turn), false);
        }
    }
    return flag;
}

bool cantMove(char grid[8][8], char turn){
    bool flag=true;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            for(int k=0;k<8;k++)
                for(int l=0;l<8;l++){
                    char trial[5]={'a'+i, '1'+j, 'a'+k, '1'+l};
                    flag&=!isValid(grid, trial, turn, false);
                }
    return flag;
}
