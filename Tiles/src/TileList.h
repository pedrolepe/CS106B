/*
 * Author: Mitchell Douglass
 * Class: CS106B
 * Instructor: Marty Stepp
 * Date 10 - 19 -13
 *
 * This is the interface declaration of a TileList data structure that stores Tile objects
 * and manipulates according to rules of the specific client application.
 *
 */

#ifndef _tilelist_h
#define _tilelist_h

//import necesary libraries
#include <iostream>
#include <ostream>
#include <string>
#include "gobjects.h"
#include "gwindow.h"
#include "strlib.h"
#include "Tile.h"
using namespace std;

/*
 * This class is an encapsulation of a data structure which holds Tile objects
 * and manipulates them based on set rules. Tiles are representative of rectangles
 * in the 2 dimentional plane. In particular, Tiles are painted to the 2D plane in
 * a particular order, allowing some rectangles to fully or partially cover
 * previously drawn rectangles. This class provides functionality for manipulating
 * these tiles, including rasing particular rectangles to the "top", lowering
 * rectangles to the "bottom", and removing the top or all rectangles in contact
 * with any point on the plane.
 */
class TileList {
public:
    /*
     * This constructor initializes the initial size and capacity of the TileList
     */
    TileList();

    /*
     * Destructor needs to deallocate the memory still being held by the
     * TileList at the end of the TileList's scope.
     */
    ~TileList();

    /*
     * Adds the given tile Object to the end of the TileList. This tile
     * will therefore be painted last and will apear on "top" with
     * reference to all other tiles.
     */
    void addTile(Tile tile);

    /*
     * Iteratively paint every tile in this TileList to the provided window.
     */
    void drawAll(GWindow& window);

    /*
     * Moves the top most tile that also contains the coordinates (x, y) to
     * the front of the list, effectively causing the Tile to be painted
     * first and appear on "bottom"
     */
    void lower(int x, int y);

    /*
     * Moves the top most tile that also contains the coordinates (x, y) to
     * the end of the list, effectively causing the Tile to be painted
     * last and appear on "top"
     */
    void raise(int x, int y);

    /*
     * Removes topmost Tile which also contains coordinate (x, y) from the
     * TileList completely so that it is no longer painted.
     */
    void remove(int x, int y);

    /*
     * Removes all Tile elements which contain coordintates (x, y) from the
     * TileList completely so that they are no longer painted.
     */
    void removeAll(int x, int y);

private:
    /*
     * this Tile array holds the Tiles within this tile list
     */
    Tile* m_array;

    /*
     * Determines the size of m_array at any given instant during program execution
     */
    int m_capacity;


    /*
     * Reflects the effective size of the TileList data strucure and represents
     * the number of Tile's effectively contained in the list.
     */
    int m_size;

    /*
     * This helper method identifies the maximum of all indexes of Tiles which
     * contain the coordinate (x, y)
     */
    int indexOfTopTile(int x, int y);

    /*
     * Increases the capacity of the m_array by a factor or 2 to accomodate
     * more elements.
     */
    void grow();

    /*
     * Reduces the capacity of the m_array by a factor of 2 to conserve memory
     */
    void shrink();

    /*
     * Removes the elemnt of TileList stored at the specified index and shifts the
     * remaining elements leftward to fill opening
     */
    void removeAtIndex(int removeIndex);
};

#endif
