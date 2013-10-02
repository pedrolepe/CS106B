/**
 * Author: Mitchell Douglass
 * Class: CS106B
 * Instructor: Marty Stepp
 * Date: October 1st, 2013
 *
 * This program is a game of life simulator. Conways Game of life was
 * invented by John Conway in 1970. The game is composed of a grid of
 * an arbitrary number of rows and columns. Each "cell" in this grid
 * is either alive or dead initially. The grid then undergoes a number
 * of "generations". For each generation, each cell becomes alive or
 * dead according to the following rules:
 *
 * 1. A cell with 0 or 1 live neighbors will be dead in the next
 *    generation.
 *
 * 2. A cell with 2 live neighbors is stable and will retain it's state
 *    into the next generation.
 *
 * 3. A cell with 3 live neighbors will be living in the next generation.
 *
 * 4. A cell with 4 or more live neighbors will be dead in the next
 *    generation.
 **/

//import all of the standard and Stanford libraries
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

//declaration of function signatures
void printWelcome();
void initGrid(Grid<int>&);
void playGame(Grid<int>&);
void displayGrid(Grid<int>&);
void tickGrid(Grid<int>&);
void animateGrid(Grid<int>&, int);
void advanceGrid(Grid<int>&);

/*
 * main is called directly at the start of the program.
 */
int main() {
    setConsoleSize(800, 800);

    Grid<int> lifeGrid;

    printWelcome();

    initGrid(lifeGrid);

    playGame(lifeGrid);

    cout << "Have a nice Life!" << endl;
    return 0;
}

/*
 * print the welcome message at the top of the console
 * with instructions for the user
 */
void printWelcome(){
    cout << "Welcome to the CS 106B Game of Life,\n"
         << "a simulation of the lifecycle of a bacteria colony.\n"
         << "Cells (X) live and die by the following rules:\n"
         << "- A Cell with 1 or fewer neighbors dies.\n"
         << "- Locations with 2 neighbors remain stable.\n"
         << "- Locations with 3 neighbors will create life.\n"
         << "- A cell with 4 or more neighbors dies.\n"
         << endl;
}

/* handle the file IO: get file name from user and
 * generate the grid
 */
void initGrid(Grid<int>& grid){
    ifstream input;
    int row, col;
    string line;

    cout << "Grid input file name? ";
    cin >> line;

    openFile(input, line);

    //read the row and column from file
    getline(input, line);
    row = stringToInteger(line);
    getline(input, line);
    col = stringToInteger(line);

    grid.resize(row, col);

    /*
     * Grid cells initialize to 0 by default. So, if a '-' is
     * encountered in the file, we can ignore. If a 'X' is
     * encountered, we need to set that grid cell to 1.
     */
    for(int i=0; i<row; i++){
        getline(input, line);
        for(int j=0; j<col; j++){
            if(line[j] == 'X'){
                grid[i][j] = 1;
            }
        }
    }
}

/*
 * runs the main iterating logic of the simulation.
 * repeatedly prompts for user instruction and calls
 * appropriate handling functions.
 */
void playGame(Grid<int>& grid){
    string usrIn;
    bool cont = true;

    displayGrid(grid);

    while(cont){
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> usrIn;
        if(usrIn == "a"){
            //prompt for frames to animate
            int frames;
            cout << "How many frames? ";
            cin >> usrIn;
            frames = stringToInteger(usrIn);
            animateGrid(grid, frames);
        }else if(usrIn == "t"){
            tickGrid(grid);
        }else if(usrIn == "q"){
            //exit loop next iteration
            cont = false;
        }
    }
}

//advances grid and displays
void tickGrid(Grid<int>& grid){
    advanceGrid(grid);
    displayGrid(grid);
}

/*
 * advances and displays grif (int frames) number of times.
 * pauses for 100 milliseconds between frames.
 */
void animateGrid(Grid<int>& grid, int frames){
    for(int i=0; i<frames; i++){
        pause(100);
        advanceGrid(grid);
        clearConsole();
        displayGrid(grid);
    }
}

/*
 * takes the existing game grid, constucts a new temporary
 * grid based on the contents of the game grid and the
 * rules of The Game of Life as described above, then reassigns
 * these new contents back to the original grid.
 */

void advanceGrid(Grid<int>& grid){
    //create new temporary grid
    Grid<int> temp(grid.numRows(), grid.numCols());

    /*
     * iterate over the cells of the game grid, incrementing
     * a "neighbor count" in the cells of temp grid for all
     * live cells in game grid.
     *
     * Example:
     *
     *  grid:               temp
     *  1 0 0 1 0           0 1 2 1 1
     *  0 0 1 0 0    --\\   1 3 3 3 2
     *  0 1 0 1 0    --//   1 1 3 1 1
     *  0 0 0 0 0           1 1 2 1 1
     */
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

    /*
     * Use rules of the Game of life to convert temp into a valid
     * game grid
     */
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

    /*
     * of course, by the time grid gets back to its caller it better
     * have the updated contents
     */
    grid = temp;
}

//traverses the grid and displays according to perscribed file format
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
// why this line?: pff!! Why not this line?!?
