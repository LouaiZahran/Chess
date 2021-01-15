#include <stdio.h>
#include <windows.h>

extern char grid[8][8];
extern char turn;
extern char eatenWhite[16], eatenBlack[16];
extern char nextTurn(char);
extern void maintainGrid();

char choice[1000];
char statesGrid[8][8][1000];
char statesEatenW[16][1000], statesEatenB[16][1000];
int ctr, mxCtr;

void save()
{
    memset(choice, 0, sizeof(char)*1000);
    printf("Are you sure you want to save the current game? [Y/N] ");
    fflush(stdin);
    scanf("%s", choice);
    if(strlen(choice)!=1||(choice[0]!='Y'&&choice[0]!='N')){
        printf("Invalid Choice!\n");
        return save();
    }
    if(choice[0]=='N'){
        printf("Saving cancelled\n");
        return;
    }
    FILE* fptr = fopen("savedGame.txt", "w+");
    if(fptr==NULL){
        printf("Saving failed\n");
        return;
    }
    for (int i=0; i<8; i++){
        for(int j=0; j<8; j++)
            fprintf(fptr, "%c ",grid[i][j]);
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "%c", turn);
    printf("Saved Successfully!\n");
    fclose(fptr);
    Sleep(1000);
}

void load()
{
    memset(choice, 0, sizeof(char)*1000);
    printf("Are you sure you want to load the previous game? [Y/N] ");
    fflush(stdin);
    scanf("%s", choice);
    if(strlen(choice)!=1||(choice[0]!='Y'&&choice[0]!='N')){
        printf("Invalid Choice!\n");
        return load();
    }
    if(choice[0]=='N'){
        printf("Load cancelled\n");
        return;
    }
    FILE* fptr = fopen("savedGame.txt", "r+");
    if(fptr==NULL){
        printf("Load failed\n");
        return;
    }
    for (int i=0; i<8; i++){
        for(int j=0; j<8; j++)
            fscanf(fptr, "%c ", &grid[i][j]);
        fscanf(fptr, "\n");
    }
    maintainGrid();
    fscanf(fptr, "%c", &turn);
    printf("Loaded Successfully!\n");
    fclose(fptr);
    Sleep(1000);
}

void undo(){
    memset(choice, 0, sizeof(char)*1000);
    printf("Are you sure you want to undo the previous move? [Y/N] ");
    fflush(stdin);
    scanf("%s", choice);
    if(strlen(choice)!=1||(choice[0]!='Y'&&choice[0]!='N')){
        printf("Invalid Choice!\n");
        return undo();
    }
    if(choice[0]=='N'){
        printf("Undo Cancelled\n");
        Sleep(1000);
        return;
    }
    if(ctr==1){
        printf("No more moves to undo!\n");
        Sleep(1000);
        return;
    }
    ctr--;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            grid[i][j]=statesGrid[i][j][ctr];
    for(int i=0;i<16;i++)
        eatenWhite[i]=statesEatenW[i][ctr];
    for(int i=0;i<16;i++)
        eatenBlack[i]=statesEatenB[i][ctr];
    turn=nextTurn(turn);
    printf("Undone Successfully!\n");
    Sleep(1000);
}

void redo(){
    memset(choice, 0, sizeof(char)*1000);
    printf("Are you sure you want to redo the previous move? [Y/N] ");
    fflush(stdin);
    scanf("%s", choice);
    if(strlen(choice)!=1||(choice[0]!='Y'&&choice[0]!='N')){
        printf("Invalid Choice!\n");
        return redo();
    }
    if(choice[0]=='N'){
        printf("Redo Cancelled\n");
        Sleep(1000);
        return;
    }
    if(ctr==mxCtr){
        printf("No more moves to redo!\n");
        Sleep(1000);
        return;
    }
    ctr++;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            grid[i][j]=statesGrid[i][j][ctr];
    for(int i=0;i<16;i++)
        eatenWhite[i]=statesEatenW[i][ctr];
    for(int i=0;i<16;i++)
        eatenBlack[i]=statesEatenB[i][ctr];
    turn=nextTurn(turn);
    printf("Redone Successfully!\n");
    Sleep(1000);
}

void maintainGrid(){
    ctr++;
    mxCtr=ctr;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            statesGrid[i][j][ctr]=grid[i][j];
    int lenW=strlen(eatenWhite), lenB=strlen(eatenBlack);
    for(int i=0;i<lenW;i++)
        statesEatenW[i][ctr]=eatenWhite[i];
    for(int i=0;i<lenB;i++)
        statesEatenB[i][ctr]=eatenBlack[i];
}
