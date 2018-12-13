/*
Program Name: Sudoku Final Project
Creator: Ryan Grady
Class: CS 172-1
Date: 12-13-18
*/
#include "Sudoku.h"
#include <stdio.h>
#define N 9
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

/*
File input constructor, also default constructor. 
*/
Sudoku::Sudoku(){
    fstream fin;
    fin.open("Board.txt");
    if (fin.fail()){
        cout << "Could not open problem file." << endl;
    }
    for (int i = 0; i < N; i ++){
        for (int j = 0; j < N ; j++){
            fin >> grid[i][j];
    }
    }
}

/*
Constructor to generate puzzle without file input.
*/
Sudoku::Sudoku(int difficulty){
    srand(time(NULL));
    switch (difficulty){
        case 1:
            fill_values(30);
            print();
            break;
        case 2:
            fill_values(45);
              print();
            break;
        case 3:
            fill_values(60);
              print();
            break;
    }
}

/*
Filling the grid with random values and then removing numbers at random locations per difficulty level.
*/
void Sudoku::fill_values(int n){
    for (int i = 0; i < N; i++){
        for (int j = 0; j< N; j++){
            grid[i][j] = 0;
        }
    }
    int nums[9];
    bool logged[9] = {false,false,false,false,false,false,false,false,false};
    int temp;
    for (int i = 1; i <= 9; i ++){
        nums[i-1] = i;
    }
    for (int i = 0; i <9; i++){
        int a = rand() % 9;
        if (logged[a] == 0){
            temp = nums[i];
            nums[i] = nums[a];
            nums[a] = temp;
            logged[a] = true;
        }
    }
    rand_generator(nums);
    for (int i = 0; i < n; i++){
                int r = rand()%9;
                int c = rand()%9;
                grid[r][c] = 0;
                copyGrid[r][c] = 0;
    }
}
/*
Function, like solve_game() but inputs random numbers into the grid. 
*/
bool Sudoku::rand_generator(int nums[N]){
    int row, col; 
    if (!isEmpty(grid, row, col)) 
       return true; 

    for (int num = 0; num < 9; num++) 
    { 
        if (check_board(grid, row, col, nums[num])) 
        { 
            grid[row][col] = nums[num];
            if (solve_game()) 
                return true; 
            grid[row][col] = 0; 

        } 
    } 
    return false; 
}
/*
Console print function for debugging
*/
void Sudoku::print(){
    cout << "-------+-------+-------- " << endl;
    for(int i = 0; i < N; i++){
        cout << "|";
        for(int j = 0; j < N; j++){
            cout << grid[i][j] << " ";       
            if(j%3-2 == 0){
                cout << "| ";
            }
        }
        cout << endl;
        if(i%3-2  == 0) cout << "-------+-------+-------- " << endl;
    }   
}

/*
Print function which formats solution nicely to output file "Board.txt".
Function utilizes random access operators to not interfere with user input. 
*/
void Sudoku::print_board(int type){ 
    fstream fout;
    fout.open("Board.txt", ios::app);
    fout.seekg(81);
    if (fout.fail()){
        cout << "Could not write solution to file." << endl;
    }
    switch (type){
        case 1: 
            fout << "\n Your input rendered the following solution: \n";
            fout << "-------+-------+-------- " << endl;
            break;
        case 2:
            fout << "\n Below is your sudoku problem, Good Luck!: \n";
            fout << "-------+-------+-------- " << endl;
            break;
    }
    for(int i = 0; i < N; i++){
        fout << "|";
        for(int j = 0; j < N; j++){
            if(grid[i][j] == 1) {
                fout << grid[i][j] << " ";       
            } else{
                fout << grid[i][j] << " ";
            } if(j%3-2 == 0){
                fout << "| ";
            }
        }
        fout << endl;
        if(i%3-2  == 0) fout << "-------+-------+-------- " << endl;
    }   
    fout.close();      
}

/*
Backtracking algorithm:
Pre step: If the board is already solved, return.

1. Starting at int num = 1, check if the board has any
    conflicting 1's in the first open space. If it doesnt, put a 1 down and recursively call.
    If it does fail, clear out the digit and start with a different number.
2. Repeat this process for digis through num = 9 until the board is filled;
-Referenced GeeksForGeeks article on Sudoku solving using recursion.
 */
bool Sudoku::solve_game(){
    int row, col; 
    if (!isEmpty(grid, row, col)) 
       return true; 

    for (int num = 1; num <= 9; num++) 
    { 
        if (check_board(grid, row, col, num)) 
        { 
            grid[row][col] = num;
            if (solve_game()) 
                return true; 
            grid[row][col] = 0; 

        } 
    } 
    return false; 
} 
  
/* 
Search function to determine if sudoku puzzle has already been filled out.
*/
bool Sudoku::isEmpty(int grid[N][N], int &row, int &col) 
{ 
    for (row = 0; row < N; row++) 
        for (col = 0; col < N; col++) 
            if (grid[row][col] == 0) 
                return true; 
    return false; 
} 
  
/*
Checks if a desired number conflicts with any selected row.
*/
bool Sudoku::check_row(int grid[N][N], int row, int num) 
{ 
    for (int col = 0; col < N; col++) 
        if (grid[row][col] == num) 
            return true; 
    return false; 
} 
  
/*
Checks if a desired number conflicts with any selected column.
*/
bool Sudoku::check_col(int grid[N][N], int col, int num) 
{ 
    for (int row = 0; row < N; row++) 
        if (grid[row][col] == num) 
            return true; 
    return false; 
} 
  
/*
Checks if a desired number conflicts with any selected 3x3 box (e.g. grid[0][0]-grid[2][2]).
*/
bool Sudoku::check_box(int grid[N][N], int boxrow, int boxcol, int num) 
{ 
    for (int row = 0; row < 3; row++) 
        for (int col = 0; col < 3; col++) 
            if (grid[row+boxrow][col+boxcol] == num) 
                return true; 
    return false; 
} 
  
/*
Combines row, column, and box check functions into one function for ease of access.
*/
bool Sudoku::check_board(int grid[N][N], int row, int col, int num) 
{ 
    return !check_row(grid, row, num) && 
           !check_col(grid, col, num) && 
           !check_box(grid, row - row%3 , col - col%3, num)&& 
            grid[row][col]==0; 
} 
