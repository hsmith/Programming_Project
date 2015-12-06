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

#include "note.h"

std::list<Note> notes_list;

#include "datamanager.h"

//GENERAL METHOD DEFS
bool in_list(std::string search_for, std::list<std::string> search_in){

}

#endif