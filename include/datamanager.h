#ifndef DATAMANAGER_H
#define DATAMANAGER_H

void SaveMasterFile();

void SaveNote(std::string name,		//Takes data, creates note and adds it to stack.
				std::string content,
				std::string folder,
				std::list<std::string> tags){
	
	Note n(name, content, folder, tags);	
	notes_list.push_back(n);
	folder_list.push_back(folder);
	std::list<std::string>::iterator tagit;
	for (tagit = tags.begin(); tagit != tags.end(); ++tagit)
	{
		bool exists = 0;
		std::list<std::string>::iterator taglistit;
		for (taglistit = tags_list.begin(); taglistit != tags_list.end(); ++tagit)
		{
			if(*taglistit == *tagit)
			{
				exists = 0;
				break;
			}
		}

		if(!exists)
		{
			tags_list.push_back(*tagit);
		}
	}
	SaveMasterFile();
}

void DelNote(std::list<Note> &noteList, Note n)			//iterates through note stack to check is filename matches, removes note from stack.
{
	std::list<Note>::iterator noteit;
	for (noteit = noteList.begin(); noteit != noteList.end(); ++noteit)
	{
		Note e = *noteit;
		if(n.compare_note(e))
			{
				noteList.erase(noteit);
			}

		//OS specific delete file.
	}
	
	SaveMasterFile();
}

void SaveMasterFile()
{
	std::ofstream newfile;
	newfile.open("masterfile", std::ofstream::trunc);
	newfile << "#Masterfile \n \n";
	
	newfile << "#Tags \n";
	std::list<std::string>::iterator it;							//	TODO: Change iterator names.
	for (it = tags_list.begin(); it != tags_list.end(); ++it)			//	Take data from note class and store into tag and folder list.
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
	for (noteIt = notes_list.begin(); noteIt != notes_list.end(); ++noteIt)		//Iterates through tags_list per loop.
	{
		newfile << (*noteIt).getFileLine();
	}

	newfile.close();

}

#endif


