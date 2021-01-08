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
    printf("%s turn\n", turn=='W'?"White's":"Black's");
    while(1){
        memset(in, 0, sizeof(char)*1000);
        printf("\nEnter your move: ");
        scanf("%s", in);
        if(in[0]=='S'){
            save();
            continue;
        }
        if(in[0]=='L'){
            load();
            return;
        }
        if(!isValidInput(in)){
            printf("\nIncorrect format!\nPlease enter input in the form X#X#\nWhere X indicates the column letter and # indicates the row number\n");
            continue;
        }
        if(!isValid(grid, in, turn))
            printf("Invalid Move!\n");
        else
            break;
    }
    move(grid, getRow(in[1]), getCol(in[0]), getRow(in[3]), getCol(in[2]));
    turn=(turn=='W'?'B':'W');
}


bool check(char board[8][8],char player){
    //search for the king
    int KPlace[2]; // first index for y axis second for the x axis
                   // x=0 y=0 means top left and when x is increasing we are going down and y increasing we are going right
    for (int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(player=='B'){
              if(board[i][j]=='K'){
                KPlace[0]=i;
                KPlace[1]=j;
              }
            }
            else if(player=='W'){
                if(board[i][j]=='k'){
                    KPlace[0]=i;
                    KPlace[1]=j;
              }
            }
        }
    }
    //search for A rock or Queen threating our king (clockwise)
    int x=KPlace[0],y=KPlace[1];
    //check getting out of the board x<8 &&x>0 && y<8 && y>0
    //check right
    while(y<8){
        y++;
        if(player=='B'){
            if(board[x][y]=='r'||board[x][y]=='q'){
                return true;
            }
        }
        if(player=='W'){
            if(board[x][y]=='R'||board[x][y]=='Q'){
                return true;
            }
        }
        if(board[x][y]!='.' && board[x][y]!='-' ){
            break;
        }

    }


     x=KPlace[0],y=KPlace[1]; //returning to our king

    //check down
    while(x<8){
        x++;
    if(player=='B'){
        if(board[x][y]=='r'||board[x][y]=='q'){
            return true;
        }
    }
    if(player=='W'){
        if(board[x][y]=='R'||board[x][y]=='Q'){
            return true;
        }
    }
    if(board[x][y]!='.' && board[x][y]!='-' ){
        break;
    }

    }
     x=KPlace[0],y=KPlace[1]; //returning to our king

    //check left
    while(y>0){
            y--;
        if(player=='B'){
            if(board[x][y]=='r'||board[x][y]=='q'){
                return true;
            }
        }
        if(player=='W'){
            if(board[x][y]=='R'||board[x][y]=='Q'){
                return true;
            }
        }
        if(board[x][y]!='.' && board[x][y]!='-' ){
            break;
        }

    }

      x=KPlace[0],y=KPlace[1]; //returning to our king

    //check up
    while(x>0){
        x--;
    if(player=='B'){
        if(board[x][y]=='r'||board[x][y]=='q'){
            return true;
        }
    }
    if(player=='W'){
        if(board[x][y]=='R'||board[x][y]=='Q'){
            return true;
        }
    }
    if(board[x][y]!='.' && board[x][y]!='-' ){
        break;
    }

    }

     // search for a Bishop or Queen threating our King [clockwise]

     x=KPlace[0],y=KPlace[1]; //returning to our king
     //check right up diagonal
     while(x>0 && y<8){
        x--;
        y++;
        if(player=='B'){
            if(board[x][y]=='b'||board[x][y]=='q'){
                return true;
                }
            }
        if(player=='W'){
            if(board[x][y]=='B'||board[x][y]=='Q'){
                return true;
            }
        }
        if(board[x][y]!='.' && board[x][y]!='-' ){
            break;
        }
     }

      x=KPlace[0],y=KPlace[1]; //returning to our king
     //check right down diagonal
     while(x<8 && y<8){
        x++;
        y++;
        if(player=='B'){
            if(board[x][y]=='b'||board[x][y]=='q'){
                return true;
                }
            }
        if(player=='W'){
            if(board[x][y]=='B'||board[x][y]=='Q'){
                return true;
            }
        }
        if(board[x][y]!='.' && board[x][y]!='-' ){
            break;
        }
     }

      x=KPlace[0],y=KPlace[1]; //returning to our king
     //check left down diagonal
     while(x<8 && y>0){
        x++;
        y--;
        if(player=='B'){
            if(board[x][y]=='b'||board[x][y]=='q'){
                return true;
                }
            }
            if(player=='W'){
                if(board[x][y]=='B'||board[x][y]=='Q'){
                    return true;
                }
            }
            if(board[x][y]!='.' && board[x][y]!='-' ){
                break;
            }
     }

     x=KPlace[0],y=KPlace[1]; //returning to our king
     //check left up diagonal
     while(x>0 && y>0){
        x--;
        y--;
        if(player=='B'){
            if(board[x][y]=='b'||board[x][y]=='q'){
                return true;
                }
            }
        if(player=='W'){
            if(board[x][y]=='B'||board[x][y]=='Q'){
                return true;
            }
        }
        if(board[x][y]!='.' && board[x][y]!='-' ){
            break;
        }
     }

     x=KPlace[0],y=KPlace[1]; //returning to our king
     // search for a Knight threating our King [clockwise]
    //check for player color
    //2up and one right
    if(player=='B'){
        if(board[x-2][y+1]=='n'){
            return true;
        }
    }else if(player=='W'){
        if(board[x-2][y+1]=='N'){
            return true;
        }
    }
    //1up and two right
    if(player=='B'){
        if(board[x-1][y+2]=='n'){
            return true;
        }
    }else if(player=='W'){
        if(board[x-1][y+2]=='N'){
            return true;
        }
    }
    //1 down and two right
    if(player=='B'){
        if(board[x+1][y+2]=='n'){
            return true;
        }
    }else if(player=='W'){
        if(board[x+1][y+2]=='N'){
            return true;
        }
    }

    //2 down and 1 right
    if(player=='B'){
        if(board[x+2][y+1]=='n'){
            return true;
        }
    }else if(player=='W'){
        if(board[x+2][y+1]=='N'){
            return true;
        }
    }
    //2 down and 1 left
    if(player=='B'){
        if(board[x+2][y-1]=='n'){
            return true;
        }
    }else if(player=='W'){
        if(board[x+2][y-1]=='N'){
            return true;
        }
    }
    //1 down and 2 left
    if(player=='B'){
        if(board[x+1][y-2]=='n'){
            return true;
        }
    }else if(player=='W'){
        if(board[x+1][y-2]=='N'){
            return true;
        }
    }
    //1 up and 2 left
    if(player=='B'){
        if(board[x-1][y-2]=='n'){
            return true;
        }
    }else if(player=='W'){
        if(board[x-1][y-2]=='N'){
            return true;
        }
    }
    //2 up and 1 left
    if(player=='B'){
        if(board[x-2][y-1]=='n'){
            return true;
        }
    }else if(player=='W'){
        if(board[x-2][y-1]=='N'){
            return true;
        }
    }
    //check for pawn up right or up left for white
    //check for pawn down right or down left for black
    //start for black player meaning to check for white pawn (search down)
    if(player=='B'){
        if(board[x+1][y+1]=='p'){
            return true;
        }
        if(board[x+1][y-1]=='p'){
            return true;
        }
    }
    //look up for white player
    else if(player=='W'){
        if(board[x-1][y+1]=='P'){
            return true;
        }
        if(board[x-1][y-1]=='P'){
            return true;
        }
    }

    //if it passed all this tests then its not checked
    return false;
}

int main()
{
    while(true){
        printGrid();
        readMovements();
        system("cls");
    }
    return 0;
}
