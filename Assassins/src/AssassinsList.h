// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef _assassinslist_h
#define _assassinslist_h

#include <fstream>
#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

class AssassinsList {
public:
    AssassinsList(istream& input);
    ~AssassinsList();
    void printGameRing();
    void printGraveyard();
    bool isAlive(string& player);
    bool isDead(string& player);
    bool isGameOver();
    string winner();
    void eliminate(string& player);

private:

};

#endif
