#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>
#include <list>

class Note{
	public:
		Note(std::string name,
			std::string content,
			std::string folder,
			std::list<std::string> tags);

		int search_tags(std::string tag);
		int search_folder(std::string folder);
		int search_keyword(std::string keyword);
		
		std::string getFileLine();

		void add_tag(std::string tag);
		void add_folder(std::string folder);

		void debug_print();
	private:
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

int Note::search_tags(std::string tag){
	std::list<std::string>::iterator it;

	for (it = tags.begin(); it != tags.end(); ++it){
		std::string t = *it;

		//std::cout << t << ' ';
		if(t == tag){
			return 1;
		}
	}
	return 0;
}

/*int Note::search_folder(std::string folder){
	std::list<std::string>::iterator it;

	for (it = tags.begin(); it != tags.end(); ++it){
		std::string f = *it;

		//std::cout << f << ' ';
		if(f == folder){
			return 1;
		}
	}
	return 0;
}*/

int Note::search_keyword(std::string keyword){
	if(content.find(keyword) != std::string::npos){
		return 1;
	}
	return 0;
}

void Note::add_tag(std::string tag){
	bool in_list = false;
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

/*void Note::add_folder(std::string folder){
	bool in_list = false;
	for(std::list<std::string>::iterator it = folder.begin(); it != folder.end(); ++it){
   		if(folder == *it){
   			in_list = true;
   			break;
   		}
	}
	if(!in_list){
		folder.push_back(folder);
	}
}*/

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

#endif

