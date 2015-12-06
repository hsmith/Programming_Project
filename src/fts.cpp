#include <fts.h>
#include <string.h>
#include <iostream>
#include <stdio.h> //To use perror
#include <cerrno> //To use errno
#include <vector>
#include "../include/notes++.h"
#include <list>
#include "load.cpp"
using namespace std;

vector<string> file_tree_walker()
{
    //char *dot[] = {".", 0};
    //char **paths = argc > 1 ? argv + 1 : dot;



   
    vector<string> data;
    
    char*s[2];
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
            		printf("Got file named %s at depth %d, "
                	"accessible via %s from the current directory "
		        "or via %s from the original starting directory\n\n",
		        node->fts_name, node->fts_level,
		        node->fts_accpath, node->fts_path);
                data.push_back(node->fts_name);
           
            string directory=node->fts_accpath;
            string fileNameTemp=node->fts_name;
            
            int size= fileNameTemp.length();
            directory.erase(directory.length()-size-1, directory.length());
         
            int temp=directory.find_last_of("/");
            string folder= directory.substr(temp+1,directory.length());
         
            
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
    fileFolder=file_tree_walker();
    int length=fileFolder.size();
    string fileName;
    string folderName;
    
    for (int i=0; i<length; i++)
    {
        cout << i<<"\n\n";
        bool missing=true;
        fileName=fileFolder[i];
        folderName=fileFolder[i+1];
        i=i+1;
        
        for(list<Note>::iterator iter_note = notes_list.begin(); iter_note != notes_list.end(); iter_note++)
        {
            if (((*iter_note).compare_note(fileName, folderName))) missing=false;
        }
        if (missing)
        {
            Note name(fileName, folderName);
            notes_list.push_back(name);
            cout <<"namsayin \n\n";
        }
        
    }
    
    
    
    
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
