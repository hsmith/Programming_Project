#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <iostream>
#include <string>
#include <list>

void SaveNote(std::string name,		//Takes data, creates note and adds it to stack.
				std::string content,
				std::string folder,
				std::list<std::string> tags){
	
	Note n(name, content, folder, tags);	
	notes_list.push_back(n);
	folder_list.push_back(folder);
	std::list<std::string>::iterator tagit;
	for (tagit = tags.begin(); tagit != tags.end(); ++noteit)
	{
		bool exists = 0;
		std::list<std::string>::iterator taglistit;
		for (taglistit = tag_list.begin(); taglistit != tag_list.end(); ++noteit)
		{
			if(*taglistit == *tagit)
			{
				exists = 0;
				break;
			}
		}

		if(!exists)
		{
			tag_list.push_back(*tagit);
		}
	}
	SaveMasterFile(notes_list);
}

void DelNote(std::list<Note> &noteList, Note n)			//iterates through note stack to check is filename matches, removes note from stack.
{
	std::list<Note>::iterator noteit;
	for (noteit = noteList.begin(); noteit != noteList.end(); ++noteit)
	{
		Note e = *noteit;
		if(n.compare(e))
			(
				noteit.erase();
			)

		//OS specific delete file.
	}
	
	SaveMasterFile(notes_list);
}

void SaveMasterFile(std::list<Note> noteList)
{
std::ofstream newfile;
	newfile.open("matserfile.txt", std::ofstream::trunc);
	newfile << "#Masterfile \n \n";
	
	newfile << "#Tags \n";
	std::list<std::string>::iterator it;				TODO: Change iterator names.
	for (it = tag_list.begin(); it != tag_list.end(); ++it)				Take data from note class and store into tag and folder list.
	{
		newfile << *it << "\n";	
	}
	newfile << "\n";

	newfile << "#Folders \n";
	for (it = folder_list.begin(); it != folder_list.end(); ++it)
	{
		newfile << *it << "\n";
	}
	newfile << "\n";	

	newfile << "#Notes \n";
	std::list<Note>::iterator noteIt;
	for (noteIt = noteList.begin(); noteIt != noteList.end(); ++noteIt)		//Iterates through noteList per loop.
	{
		
	}

	newfile.close();

}

#endif


