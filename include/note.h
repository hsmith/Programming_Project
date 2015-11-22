#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>
#include <list>

class Note{
	public:
		Note(std::string content,
			std::list<std::string> tags,
		 	std::list<std::string> folders);

		int search_tags(std::string tag);
		int search_folders(std::string folder);
		int search_keyword(std::string keyword);

	private:
		std::string content;
		std::list<std::string> tags;
		std::list<std::string> folders;
};

Note::Note(){
	content = "Blah blah blah note keyword 123";
	
	tags.push_back("one");
	tags.push_back("two");
	tags.push_back("three");

	folders.push_back("fone");
	folders.push_back("ftwo");
	folders.push_back("fthree");

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
int Note::search_folders(std::string folder){
	std::list<std::string>::iterator it;

	for (it = tags.begin(); it != tags.end(); ++it){
		std::string f = *it;

		//std::cout << f << ' ';
		if(f == folder){
			return 1;
		}
	}
	return 0;
}
int Note::search_keyword(std::string keyword){
	if(content.find(keyword) != std::string::npos){
		return 1;
	}
	return 0;
}

#endif

