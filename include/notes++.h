#ifndef NOTEPP_H
#define NOTEPP_H

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <fts.h>
#include <stdio.h>
#include <cerrno>

std::list<std::string> folder_list;
std::list<std::string> tags_list;


//GENERAL METHOD DEFS
std::string lower(std::string s){
    // Loop through a string and return it lowercase
    std::string lower_case = "";

    for (std::string::size_type i=0; i<s.length(); ++i)
        lower_case += std::tolower(s[i]);
    return lower_case;
}

#include "note.h"

std::list<Note> notes_list;

#include "datamanager.h"


#endif