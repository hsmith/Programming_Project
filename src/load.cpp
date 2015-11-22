#include "note.h"

int main(){
	Note *n = new Note();

	std::cout << n->search_tags("keyword") << std::endl;
	std::cout << n->search_folders("two") << std::endl;
	std::cout << n->search_keyword("keyword") << std::endl;
}