/*
 * Author: Mitchell Douglass
 * Class: CS106B
 * Instructor: Marty Stepp
 * Date: 10 - 19 - 13
 *
 * This file implements the functionality of the TileList data structure which is used by
 * the client tilemain.cpp file. This data structure implements an list datastructure
 * with an array as the internal collection implementation.
 *
 */

#include "TileList.h"
#include "strlib.h"

TileList::TileList() {
    //initial capacity of 10, size is zero
    m_array = new Tile[10];
    m_capacity = 10;
    m_size = 0;
}

TileList::~TileList() {
    //deallocate the array of memory
    delete[] m_array;
}

void TileList::addTile(Tile tile) {
    //check to see if capacity is full. Grow if needed.
    if(m_size == m_capacity){
        grow();
    }
    m_array[m_size] = tile;
    m_size++;
}

void TileList::drawAll(GWindow& window) {
    // iterate through all of the tiles the TileList and call their draw function
    for(int i=0; i< m_size; i++){
        m_array[i].draw(window);
    }
}

int TileList::indexOfTopTile(int x, int y) {
    // initialize index to -1
    int index = -1;
    // starting from end of list, find first Tile at (x, y), if present
    for(int i=m_size-1; i>=0; i++){
        if(m_array[i].contains(x, y)){
            index = i;
            break;
        }
    }
    return index;
}

void TileList::raise(int x, int y) {
    int index = indexOfTopTile(x, y);
    // check for case where Tile does not exist.
    if(index == -1) return;
    Tile raiseTile = m_array[index];
    // remove Tile from current position in list
    removeAtIndex(index);
    //reinsert Tile at the end of the list
    m_array[m_size] = raiseTile;
    //re increment to accomonate for the decrement in removeAtIndex function
    m_size++;
}

void TileList::lower(int x, int y) {
    int index = indexOfTopTile(x, y);
    // check for case where Tile does not exist
    if(index == -1) return;
    Tile lowerTile = m_array[index];
    // remove tile from current position in list
    removeAtIndex(index);
    //shift elements to make room for element at front of list
    for(int i=m_size+1; i>0; i--){
        m_array[i] = m_array[i-1];
    }
    //inseart at front of list
    m_array[0] = lowerTile;
    //re increment to accomonate for the decrement in removeAtIndex function
    m_size++;
}

void TileList::remove(int x, int y) {
    int index = indexOfTopTile(x, y);
    //check for case when Tile does not exist
    if(index == -1) return;
    //remove from list
    removeAtIndex(index);
    // When the size of the list has reached a quarter of the capacity, shrink capacity by factor of 2.
    // We use 1/4 because this eliminates the posibility of repetitive resizing at sizes near a power
    // of 2
    if(m_size > 10 && m_size <= m_capacity/4){
        shrink();
    }
}

void TileList::removeAll(int x, int y) {
    int index = indexOfTopTile(x, y);
    // iteratively find all Tiles which contain coordinate (x, y) and
    // remove them from the TileList entirely.
    while(index != -1){
        removeAtIndex(index);
        index = indexOfTopTile(x, y);
    }
    // When the size of the list has reached a quarter of the capacity, shrink capacity by factor of 2.
    // We use 1/4 because this eliminates the posibility of repetitive resizing at sizes near a power
    // of 2
    if(m_size > 10 && m_size <= m_capacity/4){
        shrink();
    }
}

void TileList::removeAtIndex(int removeIndex){
    // starting at specified index, pull values from
    // right index over to cover previous value
    for(int i=removeIndex; i<m_size-1; i++){
        m_array[i] = m_array[i+1];
    }
    //reduce the size of the TileList
    m_size --;
}

void TileList::grow(){
    //create new temporary array with twice the current capacity
    Tile* temp = new Tile[m_capacity*2];
    //copy element from m_array into the tempory
    for(int i=0; i<m_size; i++){
        temp[i] = m_array[i];
    }
    // deallocate the array stored at m_array
    delete[] m_array;

    //re-assign m_array to the larger array
    m_array = temp;
    // update capacity of m_array
    m_capacity = m_capacity*2;
}

void TileList::shrink(){
    //create new subarray with half the current capacity
    Tile* temp = new Tile[m_capacity/2];
    //copy elements from m_array to new temporary array
    for(int i=0; i<m_size; i++){
        temp[i] = m_array[i];
    }
    //deallocate the memory referenced by m_array
    delete[] m_array;
    //re-assign m_array
    m_array = temp;
    //update capacity
    m_capacity = m_capacity/2;
}
