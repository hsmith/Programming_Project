//Notes++ Command Line UI
//Command a Menu asking the user to either:
//1) Make a File
//2) Make a Note
//3) Assign Tags
//4) Search
//5) Exit Program

//Error Check: Make sure a proper selection is made!

#include "../include/notes++.h"
#include "load.cpp"

using namespace std;

int main(){
    
    cout<<"Welcome to Notes++: The Next Iteration in Note Oganization (TM)" <<endl;
    bool continuity = true;
    string selection = "";
    vector<string> commands;
    list<string>::iterator iter;
    list<Note>::iterator iter_note;

    // Load masterfile and the global variables.
    load("masterfile");
    
    while(continuity){
        cout<<endl <<"Type your command or 'help' if you need it: ";
        
        //Record the command for inspection
        string line, keyword;
        getline(cin, line);
            istringstream record(line);
            //Reading String by String
            while(record>>keyword){
                commands.push_back(keyword);
            }
        
        //Print out the command
//        for(iter = commands.begin(); iter != commands.end(); iter++){
//            cout<< *iter << " ";
//        }
//        cout<<endl;
        
        //help command is typed, provide a list of legal commands
        if(commands[0].compare("help") == 0 && commands.size() == 1){
            cout<<endl <<"In Notes++, you manage, create, and search notes using commands. Below is a list of legal commands: "<<endl;
            cout<<endl <<"---> exit: allows you to exit the program."<<endl
            <<endl <<"---> new FILE: allows you to create a new file with name FILE."<<endl
            <<endl <<"---> mkdir FOLDERNAME: allows you to create a folder with name FOLDERNAME."<<endl
            <<endl <<"---> mv FILENAME TO_FOLDERNAME: allows you to move a specific note (FILENAME) to a specific folder (FOLDERNAME)."<<endl
            <<endl <<"---> tag add FILE TAG: allows you to add a tag (TAG) to a specific file (FILE)."<<endl
            <<endl <<"---> tag rm FILE TAG: allows you to remove a tag (TAG) to a specific file (FILE)."<<endl
            <<endl <<"---> ls notes: list all notes by name."<<endl
            <<endl <<"---> ls tags: list all tags currently being used."<<endl
            <<endl <<"---> ls folders: list all folders currently being used."<<endl;
            commands.clear();

        }
        
        else if(commands[0].compare("new") == 0 && commands.size() == 2){
            cout<<"The user wants to create a new FILE with the name: "<<commands[1];

            //Check for Duplicates, print error if so
            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
                string compare = commands[1];
                if (compare.compare((*iter_note).name) != 0){
                     continue;
                }
                
                else{
               	     cout<< endl << "ERROR: File name already exists.";
               	     break;
                }
            }

            commands.clear();
        }
        
        else if(commands[0].compare("mkdir") == 0 && commands.size() == 2){
            cout<<"The user wants to create a new folder with the FOLDERNAME: "<<commands[1];
            commands.clear();
        }
        
        else if(commands[0].compare("mv") == 0 && commands.size() == 3 && commands[2].substr(0,3).compare("TO_") == 0){
            cout<<"The user wants to move FILENAME: "<<commands[1] <<" to FOLDERNAME: " <<commands[2].substr(3);
            
            string fileName = commands[1];
            string folderName = commands[2].substr(3);
            
            //Go through notes list and find all the notes in FOLDERNAME, add them to a vector
            vector<Note> specifiedFolder;
            
            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
            
                if((*iter_note).folder.compare("folderName") == 0){
                    specifiedFolder.push_back(*iter_note);
                }
            
                else{
                    continue;
                }
            }
            
            //Go through the folder and make sure that there will be no duplicate
            for(int i = 0; i < specifiedFolder.size(); i++){
                string compare = commands[1];
                if (compare.compare(specifiedFolder[i].name) != 0){
                	continue;
                }
                
                else{
               		cout<<"File name exists.";
               		break;
                }
            }

            commands.clear();
        }
        
        else if(commands[0].compare("tag") == 0 && commands[1].compare("add") == 0 && commands.size() == 4){
            cout<<"The user wants to add a TAG: " <<commands[3] <<" to FILE: "<<commands[2];
            commands.clear();
        }
        
        else if(commands[0].compare("tag") == 0 && commands[1].compare("rm") == 0 && commands.size() == 4){
            cout<<"The user wants to remove a TAG: " <<commands[3] <<" to FILE: "<<commands[2];
            commands.clear();
        }

        
        //Exit Command
        else if(commands[0].compare("exit") == 0 && commands.size() == 1){
            commands.clear();
            continuity = false;
        }
        
        //Invalid input, clear the "Scanner" and Print out Invalid Statement
        else{
            commands.clear();
            cout<<"You have invalid input. Consider typing 'help' to see a list of eligible commands."<<endl;
        }
        
    }
    
    cout<<"You are done!";
    return 1;
}
