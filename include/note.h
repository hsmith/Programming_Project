#ifndef NOTE_H
#define NOTE_H

class Note{
	public:
		Note(std::string name,
			std::string content,
			std::string folder,
			std::list<std::string> tags);
		Note(std::string name,
			std::string folder);


		bool search_tags(std::string tag);
		bool search_folder(std::string folder);
		bool search_keyword(std::string keyword);
		
		std::string getFileLine();

		void add_tag(std::string tag);

		void debug_print();

		bool compare_note(Note n);
		bool compare_note(std::string name, std::string folder);

		std::string name;
		std::string content;
		std::string folder;
		std::list<std::string> tags;
};

Note::Note(std::string name,
		  std::string content,
		  std::string folder,
		  std::list<std::string> tags)
{
	
	this->name = name;
	this->content = content;
	this->tags = tags;
	this->folder = folder;

}
Note::Note(std::string name,
		  std::string folder)
{
	
	this->name = name;
	this->content = "";
	this->folder = folder;

}


std::string Note::getFileLine()
{
	std::list<std::string>::iterator it;
	std::string tagString;
	
	tagString.append(name);
	tagString.append(";");
	tagString.append(folder);
	tagString.append(";");
	for(it = tags.begin(); it != tags.end(); ++it)
	{
		tagString.append(*it);
		tagString.append(",");
	}
	tagString.append("; \n");
	return tagString;
}

bool Note::search_tags(std::string tag){
	std::list<std::string>::iterator it;

	for (it = tags.begin(); it != tags.end(); ++it){
		std::string t = *it;

		//std::cout << t << ' ';
		if(t == tag){
			return true;
		}
	}
	return false;
}

bool Note::search_folder(std::string folder){
	if(folder == this->folder){
		return true;
	}
	return false;
}

bool Note::search_keyword(std::string keyword){
	if(content.find(keyword) != std::string::npos){
		return true;
	}
	return false;
}

void Note::add_tag(std::string tag){
	bool in_list = false;
	if(this->search_tags(tag)){
		return;
	}

	// Add tag to global tag list.
	bool tag_exists_global = true;
	std::list<std::string>::iterator findIter = std::find(tags_list.begin(), tags_list.end(), tag);
	if(findIter == tags_list.end()){
		tag_exists_global = false;
	}
	if(!tag_exists_global) tags_list.push_back(tag);

	// Add tag to local Note tag list							
	for(std::list<std::string>::iterator it = tags.begin(); it != tags.end(); ++it){
   		if(tag == *it){
   			in_list = true;
   			break;
   		}
	}
	if(!in_list){
		tags.push_back(tag);
	}
}

void Note::debug_print(){
	std::cout << "Note name: " << name << std::endl;
	std::cout << "Content: " << content << std::endl;
	std::cout << "Tags: ";
	for(std::list<std::string>::iterator it = tags.begin(); it != tags.end(); ++it){
	   	std::cout << *it << ", ";
	}
	std::cout << std::endl << "folder: ";
	//for(std::list<std::string>::iterator it = folder.begin(); it != folder.end(); ++it){
   	//	std::cout << *it << ", ";
   	//}
   	std::cout << folder;
	std::cout << std::endl << std::endl;
}

bool Note::compare_note(Note n){
	return  this->name == n.name && 
			this->content == n.content && 
			this->tags == n.tags && 
			this->folder == n.folder;
}
bool Note::compare_note(std::string name, std::string folder){
	return this->name == name && 
		   this->folder == folder;
}


#endif

