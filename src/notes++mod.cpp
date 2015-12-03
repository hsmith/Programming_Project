#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

int main(){
    string body = "Testing one two three";

    string keyword = "teting";

    string buf; // Have a buffer string
    stringstream ss(body); // Insert the string into a stream

    vector<string> tokens; // Create vector to hold our words

    while (ss >> buf)
        tokens.push_back(buf);

    string word;
    for(int i = 0; i < tokens.size(); i++){
        word = tokens[i];
        for(int c = 0; c < word.length(); c++){
            cout << word[c] << endl;
        }
    }
    
}