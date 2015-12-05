#include "../include/notes++.h"

void load(const char* filename){
	std::cout << "Loading Master File..." << std::endl;
	
	// Load file line by line.
	std::ifstream infile(filename);
	std::cout << "Master File Loaded!" << std::endl << std::endl;
	std::string line;

	// Used for finding elements in lists.
	std::list<std::string>::iterator findIter; 
	if(infile.is_open()){
		bool notes = false, tags = false, folders = false;
		while(getline(infile,line)){
			// Skip everything until we get to #notes.
			if(line.length() <= 0) continue;
			if(line[0] == '/' && line[1] == '/') continue;
			if(line.substr(0,5) == "#Tags"){
				tags = true;
				continue;
			}
			if(line.substr(0,8) == "#Folders"){
				tags = false;
				folders = true;
				continue;
			}
			if(line.substr(0,6) == "#Notes"){
				folders = false;
				notes = true;
				continue;
			}

			if(tags){
				tags_list.push_back(line);
			}
			if(folders){
				folder_list.push_back(line);
			}
			if(notes){
				//std::cout << line << std::endl;

				// Variables to store relevant info from line.
				std::string note_name;
				std::string note_path;
				std::string note_folder;
				std::list<std::string> note_tags;

				std::string temp;

				// 0 is name, 1 is folders, 2 is tags
				int parsing = 0;
				for(int i = 0; i < line.length(); i++){
					switch(parsing){
						case 0:
							// At end of note name incr parsing.
							if(line[i] == ';'){
								parsing++;
								continue;
							}	
							note_name += line[i];						
							break;
						case 1:
							if(line[i] == ';'){
								// At the end of folders save the last folder and incr parsing.
								if(temp.length() > 0){
									note_folder = temp;

									// If the folder isn't already in the list, add it.
									findIter = std::find(folder_list.begin(), folder_list.end(), note_folder);
									if(findIter == folder_list.end()){
										folder_list.push_back(temp);
									}

									temp = "";
								}
								parsing++;
							}else{
								temp += line[i];
							}
							break;
						case 2:
							// If the folder isn't already in the list, add it.
							bool tag_exists = true;
							findIter = std::find(tags_list.begin(), tags_list.end(), note_folder);
							if(findIter == folder_list.end()){
								tag_exists = false;
							}

							if(line[i] == ';'){
								// At the end of folders save the last folder and incr parsing.
								if(temp.length() > 0){
									note_tags.push_back(temp);
									
									if(!tag_exists) tags_list.push_back(temp);
									
									temp = "";
								}
								parsing++;
							}else if(line[i] == ','){
								// At a comma save the previous folder.
								if(temp.length() > 0){
									note_tags.push_back(temp);

									if(!tag_exists) tags_list.push_back(temp);

									temp = "";
								}
							}else{
								temp += line[i];
							}
							break;
					}
				}

				Note n(note_name,"asdf",note_folder,note_tags);
				
				n.debug_print();
				notes_list.push_back(n);
			}
		}
		std::cout << std::endl << "Master File loaded successfully!" << std::endl;
		infile.close();
	}
}

//using namespace std;
/*int main(){

	load("masterfile");
	list<Note>::iterator it = notes_list.begin();
	
	Note n = (*it);
	n.debug_print();
	Note m = (*++it);
	m.debug_print();
	cout << n.compare_note(n);

	list<string>::iterator fit;
	for (fit = tags_list.begin(); fit != tags_list.end(); ++fit){
		std::string f = *fit;

		std::cout << f << " - ";
	}
	std::cout << endl;
	std::cout << endl;
	for (fit = folder_list.begin(); fit != folder_list.end(); ++fit){
		std::string f = *fit;

		std::cout << f << " - ";
	}
	std::cout << endl;
}*/

	
