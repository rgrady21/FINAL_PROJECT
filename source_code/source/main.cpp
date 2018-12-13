/*
Program Name: Sudoku Final Project
Creator: Ryan Grady
Class: CS 172-1
Date: 12-13-18
*/
#include "Sudoku.h"
#include <iostream>
#include <fstream>
#define N 9

using namespace std;
void menu();
void generateSudoku(int d);
void solveSudoku();


void menu(bool firsttime){
    firsttime =false;
    int input;
    char y = 'y';
    char done;
    int d;
    if (firsttime){
        cout << "Welcome to Sudoku Generator/Solver!" << endl;

    }
    cout << "Enter '1' for solver menu and '2' for a problem of your own or '3' to exit!." << endl;
    cin >> input;
switch (input)  {
        case 1:
            cout << "Please place your sudoku board into 'Board.txt' with the following format:" << endl;
            for ( int i = 0 ; i < 9 ; i ++){
                for (int j = 0; j < 9 ; j++){
                    cout << "x ";
                }
                cout << endl;
            }
            cout << "The completed board will be output directly below your input!" << endl;
            cout << "Once you have typed your board into the file, type 'y' to solve." << endl;
            cin >> done;
            if (done == 'y')
            solveSudoku();
            cout << "To return to the menu again, press 'm'.";
            cin >> done;
            if (done == 'm')
            menu(firsttime);
            return;
        case 2: 
            cout << "Enter the difficulty of the puzzle you'd like to generate (1, 2, or 3): ";
            cin >> d;
            if (d <0 || d >3){
                cout << "Invalid entry.";
                return;
            }
            generateSudoku(d);
            cout << "Your sudoku problem is in the file: 'Board.txt'." << endl;
            cout << "To return to the menu again, press 'm'.";
            cin >> done;
            if (done == 'm'){
            menu(firsttime);
            } 
            return;
        case 3:
        return;

        default:
        cout << "Invalid entry, enter again." << endl;
        menu(firsttime);
    }
}

void generateSudoku(int d){
    Sudoku s1(d);
    s1.print_board(2);
}
void solveSudoku(){
     Sudoku s1;
    if (s1.solve_game() == true){
        s1.print_board(1);
    } else {
        cout << "No Solution Exists to the board you entered." << endl;
    }
    return;
}

int main(){
   menu(true);
}
