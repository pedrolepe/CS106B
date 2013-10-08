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
#include "hashmap.h"
#include "hashset.h"
#include "map.h"
#include "queue.h"
#include "random.h"
#include "set.h"
#include "simpio.h"
#include "vector.h"

using namespace std;

void createMap(ifstream&, HashMap<Queue<string>, Vector<string> >&, int);
void generateAndDisplayWords(HashMap<Queue<string>, Vector<string> >&, int);

int main() {
    setConsoleSize(750, 450);
    setConsoleFont("Courier New-16");
    setConsoleEcho(true);


    cout << "Welcome to CS 106B Random Writer (aka 'N-Grams')." << endl
         << "This program generates random text based on a document." << endl
         << "Give me an input file and an 'N' value for groups" << endl
         << "of words, and I'll generate random text for you." << endl << endl;

    string fileName;
    int N;
    cout << "input file? ";
    cin >> fileName;
    cout << "Value of N? ";
    cin >> N;

    ifstream input;
    input.open(fileName.c_str());

    HashMap<Queue<string>, Vector<string> > map;
    createMap(input, map, N);

    int numWords;
    string output;
    bool cont = true;
    while(cont){
        cout << "# of random words to generate (0 to quit)? ";
        cin >> numWords;
        if(numWords < 1){
            cont = false;
        }else{
            generateAndDisplayWords(map, numWords);
        }
    }

    cout << "Exiting." << endl;
    return 0;
}

void createMap(ifstream& input, HashMap<Queue<string>, Vector<string> >& map, int N){
    Queue<string> queue;
    Queue<string> init;
    string word;
    for(int i=0; i<N-1; i++){
        input >> word;
        init.enqueue(word);
    }

    queue = init;

    while(input >> word){
        map[queue] += word;
        queue.dequeue();
        queue.enqueue(word);
    }

    for(int i=0; i<N-1; i++){
        map[queue] += init.front();
        queue.dequeue();
        queue.enqueue(init.dequeue());
    }
}

void generateAndDisplayWords(HashMap<Queue<string>, Vector<string> >& map, int num){

    cout << "... ";

    int wordCount = 0;
    string word;
    Vector<Queue<string> > keys = map.keys();
    Queue<string> current = keys.get(randomInteger(0, keys.size()-1));
    int size = current.size();
    for(int i=0; i<size && wordCount<num; i++){
        word = current.dequeue();
        current.enqueue(word);
        cout << word << " ";
        wordCount++;
    }

    while(wordCount<num){
        Vector<string> suffixes = map[current];
        word = suffixes.get(randomInteger(0, suffixes.size()-1));
        current.dequeue();
        current.enqueue(word);
        cout << word << " ";
        wordCount++;
    }

    cout << "..." << endl;
}
