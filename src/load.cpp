#include "../include/note.h"
#include <iostream>
#include <fstream>

std::list<Note> load(const char* filename){
	std::cout << "Loading Master File..." << std::endl;

	// List of Note objects for returning.
	std::list<Note> notes_list;
	
	// Load file line by line.
	std::ifstream infile(filename);
	std::cout << "Master File Loaded!" << std::endl << std::endl;
	std::string line;
	if(infile.is_open()){
		bool notes = false;
		while(getline(infile,line)){
			// Skip everything until we get to #notes.
			if(line.length() <= 0) continue;
			if(line[0] == '/' && line[1] == '/') continue;
			if(line.substr(0,6) == "#Notes"){
				notes = true;
				continue;
			}

			if(notes){
				//std::cout << line << std::endl;

				// Variables to store relevant info from line.
				std::string note_name;
				std::string note_path;
				std::list<std::string> note_folders;
				std::list<std::string> note_tags;
				std::string temp;

				// 0 is name, 1 is folders, 2 is tags
				int parsing = 0;
				for(int i = 0; i < line.length(); i++){
					switch(parsing){
						case 0:
							note_name += line[i];
							// At end of note name incr parsing.
							if(line[i] == ';'){
								parsing++;
							}							
							break;
						case 1:
							if(line[i] == ';'){
								// At the end of folders save the last folder and incr parsing.
								if(temp.length() > 0){
									note_folders.push_back(temp);
									temp = "";
								}
								parsing++;
							}else if(line[i] == ','){
								// At a comma save the previous folder.
								if(temp.length() > 0){
									note_folders.push_back(temp);
									temp = "";
								}
							}else{
								temp += line[i];
							}
							break;
						case 2:
							if(line[i] == ';'){
								// At the end of folders save the last folder and incr parsing.
								if(temp.length() > 0){
									note_tags.push_back(temp);
									temp = "";
								}
								parsing++;
							}else if(line[i] == ','){
								// At a comma save the previous folder.
								if(temp.length() > 0){
									note_tags.push_back(temp);
									temp = "";
								}
							}else{
								temp += line[i];
							}
							break;
					}
				}

				Note n(note_name,"asdf",note_folders,note_tags);
				//n.debug_print();
				notes_list.push_back(n);
				folder_list = note_folder;
				tag_list = note_tags;
			}
		}
		std::cout << std::endl << "Master File loaded successfully!" << std::endl;
		infile.close();
	}
	return notes_list;
}

using namespace std;
int main(){

	list<std::string> folder_list;
	list<std::folder> tag_list;
	list<Note> notes_list = load("masterfile");
	list<Note>::iterator it = notes_list.begin();
	(*it).debug_print();

	cout << (*it).compare_note(*it);

}

	
