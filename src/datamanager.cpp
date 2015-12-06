void SaveMasterFile()
{
    std::ofstream newfile;
    newfile.open("masterfile", std::ofstream::trunc);
    newfile << "#Masterfile \n \n";
    
    newfile << "#Tags \n";
    std::list<std::string>::iterator it;                            //  TODO: Change iterator names.
    for (it = tags_list.begin(); it != tags_list.end(); ++it)           //  Take data from note class and store into tag and folder list.
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
    for (noteIt = notes_list.begin(); noteIt != notes_list.end(); ++noteIt)     //Iterates through tags_list per loop.
    {
        newfile << (*noteIt).getFileLine();
    }

    newfile.close();

}