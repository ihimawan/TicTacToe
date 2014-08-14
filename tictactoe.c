//
//  main.c
//  LAB4- TICTACTOE
//
//  Created by Indri Himawan on 7/23/14.
//  Copyright (c) 2014 Indri. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Function to check if anyone won //
int isWin (char ch, char array[][3]){
    
    int row=0;
    int col=0;
    
    // win row //
    for (row=0; row<3; row++){
        if (ch==array[row][0] && ch==array[row][1] && ch==array[row][2]){
            return 1;
        }
    }
    
    // win cols //
    for (col=0; col<3; col++){
        if (ch==array[0][col] && ch==array[1][col] && ch==array[2][col]){
            return 1;
        }
    }
    
    // win diagonal //
    if (ch==array[1][1]){
        if ((ch==array[0][0] && ch==array[2][2]) || (ch==array[2][0] && ch==array[0][2])){
            return 1;
        }
    }
    
    // if not win//
    return 0;
    
}

// Checks if the array is full //
int isFull (char array[][3], int row, int col){
    int i,j;
    for (i=0; i<row; i++){
        for (j=0; j<col; j++){
            if (array[i][j]==' '){
                return 0;
            }
        }
        
    }
    return 1;
}

// Checks if a cell is occupied //
int isOccupied (char array[][3], int row, int col){
    if (array[row][col]==' '){
        return 0;
    }
    return 1;
}

// Computer Strategy for Hard Mode //
void computer_move (char array[][3], int *x, int *y){
    
    *x=4;
    *y=4;
    
    int i, j;
    
    // Winning //
    for (i=0; i<3; i++){
        for (j=0; j<3; j++){
            if(!isOccupied(array, i, j)){
                array[i][j]='O';
                if (isWin('O', array)){
                    *x=i;
                    *y=j;
                    array[i][j]=' ';
                    break;
                }else{
                    array[i][j]=' ';
                }
            }
        }
        
    }
    
    // Blocking //
    if (*x==4){
    for (i=0; i<3; i++){
        for (j=0; j<3; j++){
            if(!isOccupied(array, i, j)){
                array[i][j]='X';
                if (isWin('X', array)){
                    *x=i;
                    *y=j;
                    array[i][j]=' ';
                    break;
                }else{
                    array[i][j]=' ';
                }
            }
        }
        
    }
    }
    
    // Can't Win or Block //
    if (*x==4){
    *x=rand()%3;
    *y=rand()%3;
        
    }
}

// -------------------------------- Main Function ------------------------------------ //
int main(void){
    
    char array[3][3];
    int i,j;
    int x,y;
    int x_comp = 0,y_comp = 0 ;
    int player_win=0, computer_win=0;
    int round=1;
    int mode;
    
    printf("This is a game of Tic Tac Toe by Indri Himawan.\n\n");
    printf("This program will generate the game until either the user or computer has two more wins than the other.\n\n");
    printf("--------------------------------\n\n");
    printf("Select Game Difficulty (0 for easy, 1 for hard) = \n");
    scanf("%d", &mode);
    printf("\n--------------------------------\n\n");
    
    /* ----- GAME LOOP ----- */
     
    while(1){
        
        // game will stop if ... //
        if (player_win-computer_win==2 || computer_win-player_win==2) {
            break;
        }

        /* ------ initializing the array ----- */
    
        for (i=0; i<3; i++){
            for (j=0; j<3; j++){
                array[i][j]=' ';
            }
        }
        
        /* ----- Printing the introduction ------ */
    
        printf("Tic Tac Toe Game Start Round %d \n\n", round);
        printf("--------------------------------\n\n");
        printf("Win count:\n");
        printf("Player=%d Computer=%d\n\n", player_win, computer_win);
        
        srand(time(0));
    
        while (!isWin('X', array) && !isWin('O', array)){
        
            /* ----- prompting user input ---- */
        
            while(1){
            
                printf("User (Y,X): ");
                scanf("%d,%d", &x,&y);
            
                if (!isOccupied(array, x-1, y-1)){
                    array[x-1][y-1]='X';
                    break;
                    
                }else{
                    printf("Cell is unavailable or already occupied. Try again. \n\n");
                }
            }
        
            /* ----- computer input ---- */
            
            if(!isFull(array,3,3)){
                
                //for easy mode//
                if (mode == 0){
                    while(1){
                        x_comp=rand()%3;
                        y_comp=rand()%3;
            
                        if (!isOccupied(array, x_comp, y_comp)){
                            array[x_comp][y_comp]='O';
                            break;
                            }
                    }
                    
                //for hard mode//
                }else if(mode == 1){
                    while(1){
                        
                        computer_move(array, &x_comp, &y_comp);
                        
                        if (!isOccupied(array, x_comp, y_comp)){
                            array[x_comp][y_comp]='O';
                            break;
                            
                        }
                    }

                    
                }
        
                printf("Computer (Y,X): %d,%d\n", x_comp+1, y_comp+1);
            
            }else{
                break;
            }
    
            /* ---- printing the array -----*/
    
            //first row//
            for (j=0; j<3; j++){
                printf("|%c", array[0][j]);
            }
    
            printf("|\n");
    
            //second row//
            for (j=0; j<3; j++){
                printf("|%c", array[1][j]);
            }
    
            printf("|\n");
    
            //third row//
            for (j=0; j<3; j++){
                printf("|%c", array[2][j]);
            }
    
            printf("|\n\n");
    
        }
    
        /* ---- Printing the result of each round ---- */
        
        if (isWin('X', array)){
            printf("\nPlayer X wins round %d!\n\n", round);
            printf("--------------------------------\n\n");
            player_win+=1;
        }else if(isWin('O', array)){
            printf("\nComputer O wins round %d!\n\n", round);
            printf("--------------------------------\n\n");
            computer_win+=1;
        }else{
            printf("\nRound %d is a draw!\n\n", round);
            printf("--------------------------------\n\n");
        }
        
        round+=1;
    }
    
    /* ---- Printing the Result of Game ---- */
    
    printf("Win count:\n");
    printf("Player=%d Computer=%d\n\n", player_win, computer_win);
    
    if (player_win>computer_win){
        printf("GAME RESULT = PLAYER WINS AGAINST COMPUTER!\n\n");
        printf("--------------------------------\n\n");
    }else{
        printf("GAME RESULT = COMPUTER WINS AGAINST PLAYER!\n\n");
        printf("--------------------------------\n\n");
    }
}
