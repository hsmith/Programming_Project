//Notes++ Command Line UI

#include "../include/notes++.h"
#include "load.cpp"
#include "fts.cpp"
#include "datamanager.cpp"

using namespace std;

int main(){
    system("clear");
    // All this funky formatting from <https://en.wikipedia.org/wiki/ANSI_escape_code#graphics>
    cout<<"\033[1;93m╔═════════════════════════════════════════════╗" << endl
                  <<"║             Welcome to Notes++:             ║" << endl << "║\033[0m"
                  <<"\033[3;93m The Next Iteration in Note Oganization (TM) \033[0m" << "\033[1;93m║" <<  endl
                  <<"╚═════════════════════════════════════════════╝\033[0m" << endl <<endl;

    bool continuity = true;

    string currentFolder = "";
    vector<string> commands;
    list<string>::iterator iter;
    list<Note>::iterator iter_note;

    // Consts for printing table data
    const char separator = ' ';
    const int width = 25;

    // Load masterfile and the global variables.
    load("masterfile");
    list_comparer();
    cout << endl;
    cout << "\033[1mType your command or 'help' if you need it.\033[0m"<<endl;
    while(continuity){
        if(currentFolder == ""){
            cout << "\033[1m: \033[0m";
        }else{
            cout<< "\033[1m(" <<  currentFolder << "): \033[0m";
        }
        
        //Record the command for inspection
        string line, keyword;
        getline(cin, line);
        istringstream record(line);
        //Reading String by String
        while(record>>keyword){
            commands.push_back(keyword);
        }
        
        // Check for discrepencies
        list_comparer();
        
        //help command is typed, provide a list of legal commands
        if(commands[0].compare("help") == 0 && commands.size() == 1){
            cout << endl <<"   In Notes++, you manage, create, and search notes using commands. Below is a list of legal commands. "<<endl;
            cout <<"┌───────────────────┄ \033[1mnew FILE\033[0m : create FILE in the current directory. ┄─────────────────────────────────┐"<<endl
                 <<"├──────────────────┄ \033[1mopen FILE\033[0m : opens FILE in the current directory. ┄──────────────────────────────────┤"<<endl
                 <<"├────────────────────┄ \033[1mrm FILE\033[0m : removes FILE in current directory. ┄────────────────────────────────────┤"<<endl
                 <<"├───────────┄ \033[1mmkdir FOLDERNAME\033[0m : create new folder with name FOLDERNAME. ┄───────────────────────────────┤"<<endl
                 <<"├─────────────┄ \033[1msearch KEYWORD\033[0m : searches all notes (name, tags, folders, or body text) for KEYWORD. ┄───┤"<<endl
                 <<"├──┄ \033[1mmv FILENAME TO_FOLDERNAME\033[0m : move a file: FILENAME to a folder: FOLDERNAME. ┄────────────────────────┤"<<endl               
                 <<"├───────────┄ \033[1mtag add FILE TAG\033[0m : adds TAG to FILE. ┄─────────────────────────────────────────────────────┤"<<endl
                 <<"├────────────┄ \033[1mtag rm FILE TAG\033[0m : removes TAG to FILE. ┄──────────────────────────────────────────────────┤"<<endl
                 <<"├───────────────────┄ \033[1mls notes\033[0m : lists all notes by name in current directory. ┄─────────────────────────┤"<<endl
                 <<"├────────────────────┄ \033[1mls tags\033[0m : lists all tags currently being used.  ┄─────────────────────────────────┤"<<endl
                 <<"├───────────────┄ \033[1mls tags FILE\033[0m : lists all tags currently associated with FILE in current directory. ┄───┤"<<endl
                 <<"├─────────────────┄ \033[1mls folders\033[0m : list all folders currently being used. ┄────────────────────────────────┤"<<endl
                 <<"└───────────────────────┄ \033[1mexit\033[0m : exits the program. ┄────────────────────────────────────────────────────┘"<<endl;
            commands.clear();
        }
        
        //Change Directory - Seems to work
        else if(commands[0].compare("cd") == 0 && commands.size() == 2){

            // Run the terminal command, see if theres an error, and act accordingly
            int exists = system(("cd ../notes/" + commands[1]).c_str());
            
            if(commands[1].compare("../") == 0){
                currentFolder = "";
                //cout<<"Changed the current directory to root." <<endl;
            }else{
                if(exists == 0){        
                    currentFolder = commands[1];
                    //cout<<"Changed the current directory to: "<<currentFolder <<endl;
                }else{
                    cout << "Error: That folder doesn't exist yet." << endl;
                }
            }
            commands.clear();
        }
        
        // Make new file in the current directory - Seems to work
        else if(commands[0].compare("new") == 0 && commands.size() == 2){
            //cout<<"The user wants to create a new FILE with the name: "<<commands[1]<<endl;
            
            vector<Note> specifiedFolder;

            // This will make sure the file has an extension
            if(commands[1].find('.')!=std::string::npos){
                //Go through the folder and make sure that there will be no duplicate
                bool file_exists = false;
                for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
                    
                    if((*iter_note).folder.compare(currentFolder) == 0){

                        string compare = commands[1];

                        if (compare.compare((*iter_note).name) != 0){
                            continue;
                        }else{
                            cout<< endl << "ERROR: File name already exists.";
                            file_exists = true;
                            break;
                        }
                    }

                } 

                if(!file_exists){
                    Note n(commands[1],currentFolder);
                    notes_list.push_back(n);
                    int pass = system(("gedit ../notes/" + currentFolder + "/"+commands[1]).c_str());
                    if(pass==0){
                        //cout << "New file created.";
                    }else{
                        cout << "Error: there was a problem creating a new file.";
                    }

                }
            }else{
                cout << "ERROR: No file extension given.";
            }

            commands.clear();
            cout<<endl;

        }

        // Opens file - Seems to work
        else if(commands[0].compare("open") == 0 && commands.size() == 2){
            //cout<<"The user wants to create a new FILE with the name: "<<commands[1]<<endl;

            bool exists = false;
            for(iter_note = notes_list.begin(); iter_note !=  notes_list.end(); iter_note++){
                if((*iter_note).compare_note(commands[1],currentFolder)){
                    exists = true;
                    break;
                }
            }
            if (exists){
                int working = system(("gedit ../notes/" + currentFolder + "/"+commands[1]).c_str());
                if (working != 0){
                    cout << "ERROR: File does not exist.";
                }else{
                    //cout << "File opened.";
                }
            }else{
                cout << "ERROR: File does not exist.";
            }
            
            

            commands.clear();
            cout<<endl;

        }

        // Remove file in the current directory - NOT YET WORKING
        else if(commands[0].compare("rm") == 0 && commands.size() == 2){
            for(iter_note = notes_list.begin(); iter_note !=  notes_list.end(); iter_note++){
                if((*iter_note).compare_note(commands[1],currentFolder)){
                    //cout << "Removing file." << endl;
                    int exists = system(("rm ../notes/" + currentFolder + "/" + commands[1]).c_str());
                    if(exists == 0){
                        notes_list.erase(iter_note);
                    }else{
                        cout << "ERROR: Folder name already exists." << endl;
                    }
                    
                    break;
                }
            }
            commands.clear();
        }
        
        // Make new folder - Seems to work
        else if(commands[0].compare("mkdir") == 0 && commands.size() == 2){
            //cout<<"The user wants to create a new folder with the FOLDERNAME: "<<commands[1];
            if(commands[1] == "notes"){
                cout << "ERROR: Notes is a reserved folder name.";
            }else{

                if(currentFolder != ""){
                    // NESTED FOLDERS CURRENTLY NOT IMPLEMENTED
                    cout << "ERROR: Nested folders currently not implemented.";
                }else{
                    int exists = system(("mkdir ../notes/" + commands[1]).c_str());
                    if(exists == 0){
                        folder_list.push_back(commands[1]);
                    }else{
                        cout << "ERROR: Folder name already exists." << endl;
                    }
                }
            }
            commands.clear();
        }
        
        // Moving files, needs more test cases
        else if(commands[0].compare("mv") == 0 && commands.size() == 3){
            //cout<<"The user wants to move FILENAME: "<<commands[1] <<" to FOLDERNAME: " <<commands[2]<<endl;
            string fileName = commands[1];
            string folderName = commands[2];
            
            //Does the file exist?
            vector<Note> noteExistsArray;

            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
                
                if((*iter_note).name.compare(fileName) == 0){
                    noteExistsArray.push_back(*iter_note);
                }
                
                else{
                    continue;
                }
            }
            
            if(noteExistsArray.size() == 0){
                cout<<"ERROR: That note does not exist!" << endl;
                commands.clear();
                continue;

            }
            

            //Does the folder exist
            vector<Note> folderExistsArray;
            
            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
                if((*iter_note).folder.compare(folderName) == 0){
                    folderExistsArray.push_back(*iter_note);
                }else{
                    continue;
                }
            }            

            if(folderExistsArray.size() == 0){
                cout<<"ERROR: That folder does not exist!" << endl;
                commands.clear();
                continue;

            }
            /*// If the folder we want to move to is the root folder then don't worry about this.
            if (commands[2] == "../"){
            }*/
        
            //Go through notes list and find all the notes in FOLDERNAME, add them to a vector
            vector<Note> specifiedFolder;
            
            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
                
                if((*iter_note).folder.compare(folderName) == 0){
                    specifiedFolder.push_back(*iter_note);
                }
            }

            // Find which note we are looking for  
            Note *n;          
            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
                string name = commands[1];

                if((*iter_note).compare_note(name,currentFolder)){
                    n = &(*iter_note);
                }
            }

            //Go through the folder and make sure that there will be no duplicate
            bool file_exists = false; 
            for(int i = 0; i < specifiedFolder.size(); i++){
                string compare = commands[1];
                if (compare.compare(specifiedFolder[i].name) != 0){
                    if(n){
                        n->folder = commands[2]; 
                        if(commands[2] == "../") n->folder = "";
                    }
                    cout << "Moving file.";
                    system(("mv ../notes/" + currentFolder + "/"+commands[1] +" ../notes/" + commands[2]+"/").c_str());
                }
                
                else{
                    file_exists = true;
                    cout << "ERROR: File name exists.";
                    break;
                }
            }

            commands.clear();
            cout << endl;
        }
        
        // Add a tag to a file - Seems to work
        else if(commands[0].compare("tag") == 0 && commands[1].compare("add") == 0 && commands.size() == 4){
            //cout<<"The user wants to add a TAG: " <<commands[3] <<" to FILE: "<<commands[2];
            
            string file = commands[2];
            string tag  = commands[3];
            
            bool found = false;
            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
                if((*iter_note).name == file && (*iter_note).folder == currentFolder){

                    (*iter_note).add_tag(tag);
                    found = true;
                    break;
                }
            }
            if(found){
                cout << "Tag added.";  
            }else{
                cout << "ERROR: note not found.";  
            }
            //debug_printer();
            commands.clear();
            cout<<endl;

        }
        
        // Remove tag from file, not currenlty implemented
        else if(commands[0].compare("tag") == 0 && commands[1].compare("rm") == 0 && commands.size() == 4){
            //cout<<"The user wants to remove a TAG: " <<commands[3] <<" to FILE: "<<commands[2];
            
            bool note_found = false;
            

            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
                Note n = *iter_note;
                if(n.compare_note(commands[2],currentFolder)){
                    
                    note_found = true;
                    
                    if(n.search_tags(commands[3])){
                        cout << "Removing tag from note." << endl;
                        n.tags.remove(commands[3]);
                        notes_list.erase(iter_note);
                        notes_list.push_back(n);
                    }else{
                        cout << "ERROR: tag not found." << endl;

                    }
                }
            }
            //debug_printer();
            if(!note_found){
                cout << "ERROR: note not found." << endl;
            }
            
            commands.clear();

        }

        
        //Exit Command
        else if(commands[0].compare("exit") == 0 && commands.size() == 1){
            commands.clear();
            continuity = false;
        }

        // TODO improve table layout printing
        //Print Notes
        else if(commands[0].compare("ls") == 0 && commands[1].compare("notes") == 0 && commands.size() == 2){
            //cout<<"The user wants to print out NOTES!" <<endl;
            int count = 0;
            //cout << "note";
            if(notes_list.size() == 0){
                cout << "No notes were found.";
                commands.clear();
                cout<<endl;
                continue;
            }

            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
 
                // Only print out the notes in the folder that we are in
                if(currentFolder == ""){
                    // This syntax prints out a formatted table.
                    if(count == 3){
                            count = 0;
                            cout<<endl;
                    }
                    cout << left << setw(width) << setfill(separator) << (*iter_note).name;
                }else{
                    if((*iter_note).folder == currentFolder){
                        if(count == 3){
                            count = 0;
                            cout<<endl;
                        }
                        cout << left << setw(width) << setfill(separator) << (*iter_note).name;
                    }

                        
                }
                count++;
            }
            cout << endl;
            commands.clear();
        }


        //Print Tags
        else if(commands[0].compare("ls") == 0 && commands[1].compare("tags") == 0 && commands.size() == 2){
            //cout<<"The user wants to print out TAGS!" <<endl;
            int count  = 0;

            if(tags_list.size() == 0){
                cout << "No tags were found.";
                commands.clear();
                cout<<endl;
                continue;
            }

            for(iter = tags_list.begin(); iter != tags_list.end(); iter++){
                if(count == 3){
                    count = 0;
                    cout<<endl;
                }
                cout << left << setw(width) << setfill(separator) << (*iter);
                count++;
            }
            cout << endl;
            commands.clear();

        }

        //Print Tags associated with a Note
        else if(commands[0].compare("ls") == 0 && commands[1].compare("tags") == 0 && commands.size() == 3){
            //cout<<"The user wants to print out TAGS!" <<endl;
            int count  = 0;

            if(tags_list.size() == 0){
                cout << "No tags were found.";
                commands.clear();
                cout<<endl;
                continue;
            }

            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
                Note n = *iter_note;

                /*// Catch if there are no tags in the note
                if(n.tags.size() == 0){
                    cout << "That note does not exist or it doesn't have any tags." << endl;
                    break;
                }*/

                // If we find the note, print all the tags associated with it then break.
                if(n.compare_note(commands[2],currentFolder)){

                    for(iter = n.tags.begin(); iter != n.tags.end(); iter++){
                        if(count == 3){
                            count = 0;
                            cout<<endl;
                        }
                        cout << left << setw(width) << setfill(separator) << (*iter);
                        count++;
                    }
                    break;
                }
            }
            cout << endl;
            commands.clear();

        }
        
        //Print Folders
        else if(commands[0].compare("ls") == 0 && commands[1].compare("folders") == 0 && commands.size() == 2){
            //cout<<"The user wants to print out FOLDERS!" <<endl;
            int count = 0;
            
            if(folder_list.size() == 0){
                cout << "No folders were found.";
                commands.clear();
                cout<<endl;
                continue;
            }  
            for(iter = folder_list.begin(); iter != folder_list.end(); iter++){
                if(count == 3){
                    count = 0;
                    cout<<endl;
                }
                cout << left << setw(width) << setfill(separator) << (*iter);
                count++;
            }
            cout << endl;
            commands.clear();
        }

        // Search
        else if(commands[0].compare("search") == 0){
            int count = 0;
            cout << "The following files were found using search term:" << endl;

            keyword = commands[1];
            bool none_found = true;
            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
                // This is the note we are working with.
                Note n = (*iter_note);

                // Load all notes contents from text files and search through everything
                n.content = load_contents(n);
                if(n.search_tags(keyword) || n.search_folder(keyword) || n.search_name(keyword) || n.search_content(keyword)){
                    if(n.search_tags(keyword)){
                        cout << endl << "═ \033[1mTAG MATCH\033[0m ══════════════════════════════════════" << endl;
                    }else if(n.search_folder(keyword)){
                        cout << endl << "═ \033[1mFOLDER MATCH\033[0m ═══════════════════════════════════" << endl;
                    }else if(n.search_name(keyword)){
                        cout << endl << "═ \033[1mNAME MATCH\033[0m ═════════════════════════════════════" << endl;
                    }else if(n.search_content(keyword)){
                        cout << endl << "═ \033[1mBODY MATCH\033[0m ═════════════════════════════════════" << endl;
                    }
                    cout << "Filename: '" << n.name << "', in folder: '" << n.folder << "'" <<endl;
                    cout << "──────────────────────────────────────────────────" << endl;

                    // If we found the keyword in the body, highlight it
                    if(n.search_content(keyword)){
                        int keyword_location = n.content.find(keyword);

                        // This takes care of the rare cases when the keyword is too close to the edge to display
                        int pre_offset = 10;
                        int post_offset = 50;
                        if(keyword_location < 10) pre_offset = keyword_location;
                        if((n.content.length()-keyword_location) < post_offset) post_offset = (n.content.length()-keyword_location) ;

                        // TODO remove ... if body text doesn't require them
                        cout << "..." << n.content.substr(keyword_location-pre_offset,pre_offset) 
                         << "\033[107;30m" << n.content.substr(keyword_location,keyword.length()) << "\033[0m"
                         << n.content.substr(keyword_location+keyword.length(),post_offset) << "..." << endl;
                    }else{
                        // The random substr numbers are to get the display to line up with the body matching print out.
                        cout << n.content.substr(0,50+keyword.length()+10+3) << "..." << endl;
                    }
                    cout << "══════════════════════════════════════════════════" << endl << endl;

                    none_found = false;
                }
                
            }
            if(none_found){
                cout << "None, no matches were found." << endl;
            }
            commands.clear();
        }

        else if(commands[0].compare("debug") == 0){
            for(iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++){
               (*iter_note).debug_print();
            }
            commands.clear();
        }
        
        //Invalid input, clear the "Scanner" and Print out Invalid Statement
        else{
            cout<<"ERROR: Invalid input. Try 'help' to see a list of legal commands."<<endl;
            commands.clear();
        }

        //debug_printer();
        list_comparer();
        //debug_printer();
        SaveMasterFile();
        //debug_printer();

        
    }
    
    cout<<"You are done!"<<endl;
    return 1;
}