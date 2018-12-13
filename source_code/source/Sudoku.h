/*
Program Name: Sudoku Final Project
Creator: Ryan Grady
Class: CS 172-1
*/

#ifndef SUDOKU_H_
#define SUDOKU_H_
#include <iomanip>
#include <iostream>
#define N 9
using namespace std;

class Sudoku{
    private:
    int grid[N][N];
    int copyGrid[N][N];
    public:
    Sudoku(int difficulty);
    Sudoku();
    void fill_values(int n);
    bool rand_generator(int nums[N]);
    void print();
    void print_board(int type);
    bool solve_game();
    bool isEmpty(int grid[][N], int &i, int &j);
    bool check_row(int grid[N][N], int i, int j);
    bool check_col(int grid[N][N], int i, int j);
    bool check_box(int grid[N][N], int i, int j, int m);
    bool check_board(int grid[][N], int i, int j, int m);
};
#endif