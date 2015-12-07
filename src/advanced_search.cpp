#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

using namespace std;

int fancySearch(string keyword){
    string body = "Testing one two three";

    string buf; // Have a buffer string
    stringstream ss(body); // Insert the string into a stream

    vector<string> tokens; // Create vector to hold our words

    while (ss >> buf)
        tokens.push_back(buf);

    string word;
    int letter_tolerance = 1;
    for(int i = 0; i < tokens.size(); i++){
        word = tokens[i];
        int missing_letters = 0;
        
        // If the test word is longer or shorter than the search term by more than 1 letter, move to the next word.
        if(abs(word.length() - keyword.length()) > letter_tolerance){
            continue;
        }
        
        for(int c = 0; c < word.length(); c++){
            if(tolower(keyword[c]) != tolower(word[c]) && c < keyword.length()){
                if(missing_letters > letter_tolerance){
                    // This means we are on the second missing letter, so break.
                    break;
                }else{
                    missing_letters++;
                    cout << missing_letters << endl;
                }
            }

            // We need to check if our character matches the next or previous character
            if(c < keyword.length() && c > 0){
                if(tolower(keyword[c-1]) == tolower(word[c])) missing_letters--;
                if(tolower(keyword[c+1]) == tolower(word[c])) missing_letters--;
            }
        }

        // If we didn't had a matching word, return true
        if(missing_letters <= letter_tolerance){
            return true;
        }
    }
    return false;
}

int main(){
    cout << endl << fancySearch("twesting") << endl;
}