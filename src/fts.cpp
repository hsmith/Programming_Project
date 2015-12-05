#include <fts.h>
#include <string.h>
#include <iostream>
#include <stdio.h> //To use perror
#include <cerrno> //To use errno

using namespace std;

int file_tree_walker() 
{
    //char *dot[] = {".", 0};
    //char **paths = argc > 1 ? argv + 1 : dot;

	const char* s= "../ftw";
    FTS *tree = fts_open(*s, FTS_NOCHDIR, 0);

    if (!tree) 
	{
        perror("fts_open");
        return 1;
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
		    	/* if fts_open is not given FTS_NOCHDIR,
		     	* fts may change the program's current working directory */
        	}
    	}
    if (errno) 
	{
        perror("fts_read");
        return 1;
    	}

    if (fts_close(tree)) 
	{
        perror("fts_close");
        return 1;
    	}

    return 0;
}

//Find a way to make the root different from the starting directory
//Find a way to not include temp files (DONE, CYKA BLYAT)
//Find a way to show just the folder name, not the folder name and the file name
