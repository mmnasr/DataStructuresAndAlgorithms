#include <iostream>
#include <map>
#include <string>

std::map<char, int> countCharsInString(std::string str) {

	std::map<char, int> charCount;
	for (int i=0; i<str.length(); i++) {
		char c = str[i];
		if (charCount.count(c)) {
			charCount[c]++;
		} else {
			charCount[c] = 1;			
		}
	}
	return charCount;
}

void printMap(std::map<char, int> map) {
	std::map<char, int>::iterator it;
	std::cout << "Printing (key,val)" << std::endl;
	for (it=map.begin(); it != map.end(); it++) {
		std::cout << "('" << it->first << "'," << it->second << ")" << std::endl;
	}
}

int main(int argc, char* argv[]) {

	std::string test = "abca01  ";
	std::map<char, int> map = countCharsInString(test);
	std::cout << "Character count for: " << test << std::endl;
	printMap(map);

	return 0;
}