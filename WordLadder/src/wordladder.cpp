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
#include "stack.h"
#include "vector.h"
#include "lexicon.h"

using namespace std;

Stack<string> createLadder(Lexicon&, string&, string&);
void displayChain(Stack<string>&);

int main() {
    setConsoleSize(750, 450);
    setConsoleFont("Courier New-16");
    setConsoleEcho(true);

    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    string word1;
    string word2;
    cin >> word1 >> word2;

    Lexicon dict("dictionary.txt");

    Stack<string> ladder = createLadder(dict, word1, word2);

    if(ladder.isEmpty()){
        cout << "No word ladder found from " << word2 << " back to " << word1 << endl;
    } else {
        cout << "Ladder from " << word2 << " back to " << word1 << endl;
        displayChain(ladder);
    }

    cout << "Have a nice day." << endl;
    return 0;
}

Stack<string> createLadder(Lexicon& dict, string& src, string& trg){
    Queue<Stack<string> > queue;
    bool complete = false;

    Stack<string> init;
    init.push(src);
    queue.enqueue(init);

    HashSet<string> usedWords;
    usedWords.add(src);
    Stack<string> currentChain;
    Stack<string> newChain;
    string last, test;
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

void displayChain(Stack<string>& chain){
    while(!chain.isEmpty()){
        cout << chain.pop() << " ";
    }
    cout << endl;
}
