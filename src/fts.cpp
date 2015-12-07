using namespace std;

vector<string> file_tree_walker()
{
    //char *dot[] = {".", 0};
    //char **paths = argc > 1 ? argv + 1 : dot;

    vector<string> data;
    
    char* s[2];
    s[0]="../notes";
    s[1]= NULL;
    FTS *tree = fts_open(s, FTS_NOCHDIR, 0);
    
    if (!tree) 
	{
        perror("fts_open");
        //return 1;
    	}

    FTSENT *node;
	
    while ((node = fts_read(tree)))
	{
        	if (node->fts_level >= 0 && (node->fts_name[0] == '.' || node->fts_name[node->fts_namelen - 1] == '~'))
		{
            		fts_set(tree, node, FTS_SKIP);
		}
        	else if (node->fts_info & FTS_F) 
		{
            		/*printf("Got file named %s at depth %d, "
                	"accessible via %s from the current directory "
		        "or via %s from the original starting directory\n\n",
		        node->fts_name, node->fts_level,
		        node->fts_accpath, node->fts_path);*/
                data.push_back(node->fts_name);
           
            string directory=node->fts_accpath;
            string fileNameTemp=node->fts_name;
            
            int size= fileNameTemp.length();
            directory.erase(directory.length()-size-1, directory.length());
         
            int temp=directory.find_last_of("/");
            string folder= directory.substr(temp+1,directory.length());
            if(folder == "notes"){
                folder = "";
            }
         
            
            data.push_back(folder);
            
            
		    	/* if fts_open is not given FTS_NOCHDIR,
		     	* fts may change the program's current working directory */
        	}
    	}
    if (errno) 
	{
        perror("fts_read");
        //return 1;
    	}

    if (fts_close(tree)) 
	{
        perror("fts_close");
        //return 1;
    	}

    return data;
}


void list_comparer(){
    vector<string> fileFolder;

    // Store all changes here so that we can simultaniously remove entries that don't exist and add new files that we dont have
    list<Note> temp_storage;

    fileFolder=file_tree_walker();
    int length=fileFolder.size();
    string fileName;
    string folderName;

    // If there are no detected files, create a help file.
    if(length == 0){
/*        cout << endl << "\033[3mNOTICE: No files were found.\033[0m" << endl << endl;                
        cout << endl << "Creating readme.txt file..." << endl << endl;  

        std::ofstream newfile;
        newfile.open("../notes/README.txt", std::ofstream::trunc);
        newfile << "Test Test";

        newfile.close();
*/
        folder_list.clear();
        notes_list.clear();
        tags_list.clear();
/*
        Note n("README.txt","");
        notes_list.push_back(n);*/
        return;

    }
    for (int i=0; i<length; i++)
    {
        bool missing=true;
        fileName=fileFolder[i];
        folderName=fileFolder[i+1];
        i=i+1;
        
        for(list<Note>::iterator iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++)
        {
            if (((*iter_note).compare_note(fileName, folderName))){
                missing = false;
                temp_storage.push_back(*iter_note);
            }
        }
        if (missing)
        {
            Note n(fileName, folderName);
            temp_storage.push_back(n);
        }
        
    }

    // Check if any changes were made
    if (notes_list.size() == 0 && length != 0){
        notes_list = temp_storage;
        //cout << endl << "\033[3mNOTICE: Discrepencies were found and corrected.\033[0m" << endl << endl; 

    }

    list<Note>::iterator iter_note = notes_list.begin();
    for(list<Note>::iterator temp_note = temp_storage.begin(); temp_note != temp_storage.end(); temp_note++){
        //cout << (*temp_note).name << " - " << (*iter_note).name << endl;

        if(!(*temp_note).compare_note(*iter_note)){
            notes_list = temp_storage;
            //cout << endl << "\033[3mNOTICE: Discrepencies were found and corrected.\033[0m" << endl << endl;                

            break;
        }
    }

    //Redo the folder list and tags list with new note data
    folder_list.clear();
    tags_list.clear();

    for(list<Note>::iterator iter_note = notes_list.begin(); iter_note !=  notes_list.end(); iter_note++){
        

        list<string>::iterator findIter = std::find(folder_list.begin(), folder_list.end(), (*iter_note).folder);
        if(findIter == folder_list.end()){
            folder_list.push_back((*iter_note).folder); 
        }
        

        for(list<string>::iterator iter = (*iter_note).tags.begin(); iter !=  (*iter_note).tags.end(); iter++){
            // Add tags to the list but ignore repeats
            findIter = std::find(tags_list.begin(), tags_list.end(), *iter);
            if(findIter == tags_list.end()){
                tags_list.push_back(*iter);
            }
        }
    }

    //cout << endl;
    //cout << endl;
    
}
/*
int main(){
    vector<string> test;
    test=file_tree_walker();
    int length=test.size();
    
    for (int i=0; i<length; i++){
        
        cout << test[i]<< " ";
    }
    
    load ("masterfile");
    
    list_comparer();
    return 0;
    
}*/
