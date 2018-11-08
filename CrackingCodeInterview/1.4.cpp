#include <iostream>
#include <string>
#include <map>

bool isAnagram(std::string s1, std::string s2) {

	return true; //sortString(s1) == sortString(s2);
}

bool isAnagramMethod2(std::string s1, std::string s2) {

	std::map<char, int> charCountS1;
	std::map<char, int> charCountS2;

	for (int i=0; i < s1.length(); i++) {
		char c = s1[i];
		if (charCountS1.count(c) {
			charCountS1[c]++;
		} else {
			charCountS1[c] = 1;
		}
	}

	for (int i=0; i < s2.length(); i++) {
		char c = s1[i];
		if (charCountS2.count(c) {
			charCountS2[c]++;
		} else {
			charCountS2[c] = 1;
		}
	}

	std::map<char, int>::iterator it; 
	for (it=charCountS1.begin(); it != charCountS1.end(); it++) {
		char c = it->first;
		int count = it->second;
		if (!charCountS2.count(c))
			return false;
		if (charCountS2[c] != count)
			return false;
	}
	return true;
}

int main() {

	return 0;
}