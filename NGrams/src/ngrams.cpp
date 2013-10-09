/*
 * Author: Mitchell Douglass
 * Class: CS106B
 * Instructor: Marty Stepp
 * Date: 10/8/13
 *
 * This project is an N-gram machine. It measures patterns in the writting of
 * a particular author and then attempts to create a sequence of words that
 * statistically resembers the original. The output of an N-gram machine is
 * eirily similar in flow and voice to the original.
 *
 * An N-gram measures the frequency of words following existing N-1 sequences
 * of words in the text. In generating text, the N-gram machine chooses a
 * random N-1 sequence of words from the text and then chooses the following
 * words based on the probability of a word following the last N-1 words
 */

//import necesary libraries
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "hashmap.h"
#include "queue.h"
#include "random.h"
#include "vector.h"

using namespace std;

//function prototypes
void createMap(ifstream&, HashMap<Queue<string>, Vector<string> >&, int);
void generateAndDisplayWords(HashMap<Queue<string>, Vector<string> >&, int);

int main() {
    setConsoleSize(750, 450);
    setConsoleFont("Courier New-16");
    setConsoleEcho(true);

    //display welcome messages and instructions to the user.
    cout << "Welcome to CS 106B Random Writer (aka 'N-Grams')." << endl
         << "This program generates random text based on a document." << endl
         << "Give me an input file and an 'N' value for groups" << endl
         << "of words, and I'll generate random text for you." << endl << endl;

    //gather initial input from user.
    string fileName;
    int N;
    cout << "input file? ";
    cin >> fileName;
    cout << "Value of N? ";
    cin >> N;

    //open a file input stream to specified file
    ifstream input;
    input.open(fileName.c_str());

    //generate the map from prefixes to lists of suffixes
    HashMap<Queue<string>, Vector<string> > map;
    createMap(input, map, N);


    int numWords;
    string output;
    bool cont = true;
    /*
     * For each iteration of the loop, the program asks for a
     * word length and then genrates a sequence of words
     * based on the map generated above
     */
    while(cont){
        cout << "# of random words to generate (0 to quit)? ";
        cin >> numWords;
        //numWords < 1 is the exit status for the program
        if(numWords < 1){
            cont = false;
        }else{
            generateAndDisplayWords(map, numWords);
        }
    }

    cout << "Exiting." << endl;
    return 0;
}

/*
 * Iterate through the input file, creating a map from all possible N-1 word prefixes
 * to suffixes. If a suffix follows a prefix more than once, it is included multiple
 * times in the sufix vector for that prefix (making it more likely to be chosen by
 * generateAndDisplayWords below).
 */
void createMap(ifstream& input, HashMap<Queue<string>, Vector<string> >& map, int N){
    Queue<string> queue;
    Queue<string> init;
    string word;
    //initialize an initial queue of N-1 words as first prefix
    for(int i=0; i<N-1; i++){
        input >> word;
        init.enqueue(word);
    }

    //start with queue = init
    queue = init;

    //until end of input, add word to prefix defined by queue
    //remove an element from the head of prefix
    //enqueue the word for use in the prefix for the next word.
    while(input >> word){
        map[queue] += word;
        queue.dequeue();
        queue.enqueue(word);
    }

    //wrap the queue around. That is, add the first N-1 words
    //as "sufixes" to the last N-1 "prefixes". This ensures
    //that generateAndSisplayWords function does not get stuck
    //with a prefix that has no available sufixes.
    for(int i=0; i<N-1; i++){
        map[queue] += init.front();
        queue.dequeue();
        queue.enqueue(init.dequeue());
    }
}

/*
 * Produces output of the N-gram machine.
 * 1. Chooses prefix from the map at random.
 * 2. prints out all the words in the given prefix
 * 3. While word count still not attained:
 *      -Choose random possible sufix from vector of
 *         sufixes maped to by the current prefix
 *      -print sufix to crean
 *      -remove first word of current prefix and append sufix
 */
void generateAndDisplayWords(HashMap<Queue<string>, Vector<string> >& map, int num){

    cout << "... ";

    int wordCount = 0;
    string word;
    Queue<string> current = map.keys().get(randomInteger(0, map.keys().size()-1));
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
