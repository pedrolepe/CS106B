/*
 * Author: Mitchell Douglass
 * Class: CS106B
 * Instructor: Marty Stepp
 * Date: 10/8/13
 *
 * This is a program that implements word ladders. A word ladder is a sequence
 * of words, strating with a specified initial word and ending with a
 * specified word, with each step in the sequence exhibiting one changed letter.
 *
 * For example:
 *
 * data date cate cote coke
 *
 * The program uses Breadth-First search to find the shortest path between the
 * two words using the rules above.
 */

//import necesary libraries
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "hashset.h"
#include "map.h"
#include "queue.h"
#include "stack.h"
#include "lexicon.h"

using namespace std;

//function prototypes
Stack<string> createLadder(Lexicon&, string&, string&);
void displayChain(Stack<string>&);

int main() {
    setConsoleSize(750, 450);
    setConsoleFont("Courier New-16");
    setConsoleEcho(true);

    //print welcome and instructions to user
    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    //prompt for and retrieve start and end word from the user
    cout << "Please type two words: ";
    string word1;
    string word2;
    cin >> word1 >> word2;

    //creates a Lexicon object which stores words from the english dictionary.
    Lexicon dict("dictionary.txt");

    //call function createLadder, which does all the work.
    Stack<string> ladder = createLadder(dict, word1, word2);

    //createLadder will return an empty ladder if no path is found.
    //Otherwise, it will return the correct ladder.
    if(ladder.isEmpty()){
        cout << "No word ladder found from " << word2 << " back to " << word1 << endl;
    } else {
        cout << "Ladder from " << word2 << " back to " << word1 << endl;
        displayChain(ladder);
    }

    cout << "Have a nice day." << endl;
    return 0;
}

//tries to identify a ladder of words from src to trg using Beadth-First Search
Stack<string> createLadder(Lexicon& dict, string& src, string& trg){
    Queue<Stack<string> > queue;
    bool complete = false;

    //create initial stack for queue, containing source word
    //and push onto queue
    Stack<string> init;
    init.push(src);
    queue.enqueue(init);

    //usedWords keeps track of words already used
    HashSet<string> usedWords;
    usedWords.add(src);
    Stack<string> currentChain;
    Stack<string> newChain;
    string last, test;

    /*
     *This loop will iterate through the queue, adding new longer
     *ladder of words to the back of the queue if found. If a
     *ladder is identified as having the target word at it's top,
     *it is flaged as the successful ladder and returned after the
     *loop
     */

    while(!complete && !queue.isEmpty()){
        currentChain = queue.dequeue();
        last = currentChain.peek();
        if(last == trg){
            complete = true;
        }else{
            for(int i=0; i<last.length(); i++){
                for(char c='a'; c<='z'; c++){
                    test = last.substr(0,i) + c + last.substr(i+1);
                    if(dict.contains(test) && !usedWords.contains(test)){
                        newChain = currentChain;
                        newChain.push(test);
                        queue.enqueue(newChain);
                        usedWords.add(test);
                    }
                }
            }
        }
    }
    if(complete){
        return currentChain;
    }else{
        Stack<string> empty;
        return empty;
    }
}

//usefull method for displaying a queue. Notice, for this program we dont
//care if the queue is decomposed in the process.
void displayChain(Stack<string>& chain){
    while(!chain.isEmpty()){
        cout << chain.pop() << " ";
    }
    cout << endl;
}
