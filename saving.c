#include <stdio.h>
#include <windows.h>

extern char grid[8][8];
extern char turn;

void save()
{
    char choice;
    printf("Are you sure you want to save the current game? [Y/N] ");
    fflush(stdin);
    scanf("%c", &choice);
    if(choice!='Y'&&choice!='N'){
        printf("Invalid Choice!\n");
        save();
    }
    if(choice=='N'){
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
    printf("Saved Successfully!\n");
    fclose(fptr);
}

void load()
{
    char choice;
    printf("Are you sure you want to load the previous game? [Y/N] ");
    fflush(stdin);
    scanf("%c", &choice);
    if(choice!='Y'&&choice!='N')
    {
        printf("Invalid Choice!\n");
        save();
    }
    if(choice=='N'){
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
    printf("Loaded Successfully!\n");
    fclose(fptr);
    Sleep(1000);
}
