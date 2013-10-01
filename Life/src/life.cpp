// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
using namespace std;

void printWelcome();
void initGrid(Grid<int>&);
void playGame(Grid<int>&);
void displayGrid(Grid<int>&);
void tickGrid(Grid<int>&);
void animateGrid(Grid<int>&, int);
void advanceGrid(Grid<int>&);

int main() {
    setConsoleSize(800, 800);

    Grid<int> lifeGrid;

    printWelcome();

    initGrid(lifeGrid);

    playGame(lifeGrid);

    cout << "Have a nice Life!" << endl;
    return 0;
}

void printWelcome(){
    cout << "Welcome to the CS 106B Game of Life,\n"
         << "a simulation of the lifecycle of a bacteria colony.\n"
         << "Cells (X) lve and die by the following rules:\n"
         << "- A Cell with 1 or fewer neighbors dies.\n"
         << "- Locations with 2 neighbors remain stable.\n"
         << "- Locations with 3 neighbors will create life.\n"
         << "- A cell with 4 or more neighbors dies.\n"
         << endl;
}

void initGrid(Grid<int>& grid){
    ifstream input;
    int row, col;
    string line;

    cout << "Enter grid input file name: ";
    cin >> line;
    openFile(input, line);

    getline(input, line);
    row = stringToInteger(line);
    getline(input, line);
    col = stringToInteger(line);

    grid.resize(row, col);

    for(int i=0; i<row; i++){
        getline(input, line);
        for(int j=0; j<col; j++){
            if(line[j] == 'X'){
                grid[i][j] = 1;
            }
        }
    }
}

void playGame(Grid<int>& grid){
    string usrIn = "d";
    bool cont = true;

    displayGrid(grid);

    while(cont){
        cout << "a)nimate, t)ick, q)uit? :";
        cin >> usrIn;
        if(usrIn == "a"){
            int frames;
            cout << "How many frames? :";
            cin >> usrIn;
            frames = stringToInteger(usrIn);
            animateGrid(grid, frames);
        }else if(usrIn == "t"){
            tickGrid(grid);
        }else if(usrIn == "q"){
            cont = false;
        }
    }
}

void tickGrid(Grid<int>& grid){
    advanceGrid(grid);
    displayGrid(grid);
}

void animateGrid(Grid<int>& grid, int frames){
    for(int i=0; i<frames; i++){
        pause(50);
        advanceGrid(grid);
        clearConsole();
        displayGrid(grid);
    }
}

void advanceGrid(Grid<int>& grid){
    Grid<int> temp(grid.numRows(), grid.numCols());

    for(int row=0; row<grid.numRows(); row++){
        for(int col=0; col<grid.numCols(); col++){
            if(grid[row][col] == 1){
                if(temp.inBounds(row-1, col)){
                    temp[row-1][col]++;
                }
                if(temp.inBounds(row-1, col+1)){
                    temp[row-1][col+1]++;
                }
                if(temp.inBounds(row, col+1)){
                    temp[row][col+1]++;
                }
                if(temp.inBounds(row+1, col+1)){
                    temp[row+1][col+1]++;
                }
                if(temp.inBounds(row+1, col)){
                    temp[row+1][col]++;
                }
                if(temp.inBounds(row+1, col-1)){
                    temp[row+1][col-1]++;
                }
                if(temp.inBounds(row, col-1)){
                    temp[row][col-1]++;
                }
                if(temp.inBounds(row-1, col-1)){
                    temp[row-1][col-1]++;
                }
            }
        }
    }

    for(int row=0; row<grid.numRows(); row++){
        for(int col=0; col<grid.numCols(); col++){
            if(temp[row][col] <= 1){
                temp[row][col] = 0;
            }else if(temp[row][col] == 2){
                temp[row][col] = grid[row][col];
            }else if(temp[row][col] == 3){
                temp[row][col] = 1;
            }else if(temp[row][col] >= 4){
                temp[row][col] =  0;
            }
        }
    }

    grid = temp;
}

void displayGrid(Grid<int>& grid){
    for(int row=0; row<grid.numRows(); row++){
        for(int col=0; col<grid.numCols(); col++){
            int cell = grid[row][col];
            if(cell == 0){
                cout << "-";
            }else if(cell == 1){
                cout << "X";
            }else{
                cout << "\nasking to display cell with value not 0 and not 1" << endl;
            }
        }
        cout << endl;
    }
}
